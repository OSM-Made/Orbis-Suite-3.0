#include "Common.h"
#include "SocketListener.h"

struct ClientThreadParams
{
	SocketListener* socketListener;
	OrbisNetId Sock;
};

void* SocketListener::ClientThread(void* tdParam)
{
	ClientThreadParams* Params = (ClientThreadParams*)tdParam;
	SocketListener* socketListener = Params->socketListener;
	OrbisNetId Sock = Params->Sock;

	socketListener->ClientCallBack(socketListener->tdParam, Sock);

	sceNetSocketClose(Sock);
	free(Params);

	// Kill our thread and exit.
	scePthreadExit(NULL);
	return nullptr;
}

void* SocketListener::DoWork()
{
	OrbisNetSockaddrIn addr = { 0 };
	addr.sin_family = ORBIS_NET_AF_INET;
	addr.sin_addr.s_addr = ORBIS_NET_INADDR_ANY; // Any incoming address
	addr.sin_port = sceNetHtons(this->Port); // Our desired listen port

	//Make new TCP Socket
	this->Socket = sceNetSocket("Listener Socket", ORBIS_NET_AF_INET, ORBIS_NET_SOCK_STREAM, ORBIS_NET_IPPROTO_TCP);

	//Set Sending and reciving time out to 1000 ms
	int sock_timeout = 10000;
	sceNetSetsockopt(this->Socket, ORBIS_NET_SOL_SOCKET, ORBIS_NET_SO_SNDTIMEO, &sock_timeout, sizeof(sock_timeout));
	sceNetSetsockopt(this->Socket, ORBIS_NET_SOL_SOCKET, ORBIS_NET_SO_RCVTIMEO, &sock_timeout, sizeof(sock_timeout));

	if (sceNetBind(this->Socket, (OrbisNetSockaddr*)&addr, sizeof(addr)) != 0)
	{
		klog("Failed to bind Listener to port %i\n", this->Port);

		// Clean up.
		sceNetSocketClose(this->Socket);

		// Kill our thread and exit.
		scePthreadExit(NULL);
		return nullptr;
	}

	if (sceNetListen(this->Socket, 100) != 0)
	{
		klog("Failed to start listening on Socket.\n");

		// Clean up.
		sceNetSocketClose(this->Socket);

		// Kill our thread and exit.
		scePthreadExit(NULL);
		return nullptr;
	}

	while (this->ServerRunning)
	{
		// Wait fo rincoming connections.
		OrbisNetSockaddrIn ClientAddr = { 0 };
		OrbisNetSocklen_t addrlen = sizeof(OrbisNetSockaddrIn);
		auto ClientSocket = sceNetAccept(this->Socket, (OrbisNetSockaddr*)&ClientAddr, &addrlen);

		if (ClientSocket != -1)
		{
			//klog("New Connection from %i.%i.%i.%i!\n", ClientAddr.sin_addr.s_addr & 0xFF, (ClientAddr.sin_addr.s_addr >> 8) & 0xFF, (ClientAddr.sin_addr.s_addr >> 16) & 0xFF, (ClientAddr.sin_addr.s_addr >> 24) & 0xFF);

			int optval = 1;
			sceNetSetsockopt(ClientSocket, ORBIS_NET_SOL_SOCKET, ORBIS_NET_SO_NOSIGPIPE, &optval, sizeof(optval));
			// Set up thread params.
			ClientThreadParams* Params = new ClientThreadParams();
			Params->socketListener = this;
			Params->Sock = ClientSocket;

			// Create Thread to handle connection.
			OrbisPthread* Thread;
			scePthreadCreate(&Thread, NULL, &ClientThread, Params, "Client Thread");

			// Reset ClientSocket.
			ClientSocket = -1;
		}

	}

	klog("Listener Thread Exiting!\n");

	// Kill our thread and exit.
	scePthreadExit(NULL);
	return nullptr;
}

void* SocketListener::ListenThread(void* tdParam)
{
	return ((SocketListener*)tdParam)->DoWork();
}


SocketListener::SocketListener(void(*ClientCallBack)(void* tdParam, OrbisNetId Sock), void* tdParam, unsigned short Port)
{
	klog("Socket Listener.\n");
	this->ClientCallBack = ClientCallBack;
	this->tdParam = tdParam;
	this->ServerRunning = true;
	this->ThreadCleanedUp = false;
	this->Port = Port;

	scePthreadCreate(&ListenThreadHandle, NULL, &ListenThread, this, "Listen Thread");
}

SocketListener::~SocketListener()
{
	this->ServerRunning = false;
	scePthreadCancel(*ListenThreadHandle);
}