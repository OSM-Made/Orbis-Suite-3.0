using OrbisSuite.Common;
using OrbisSuite.Common.Database;
using OrbisSuite.Common.Dispatcher;

namespace OrbisSuiteService.Service
{
    public class TargetWatcher
    {
        private Dispatcher _dispatcher;
        private Task _TargetWatcherTask;
        private CancellationToken _TargetWatcherCancellationToken;

        public TargetWatcher(Dispatcher dispatcher)
        {
            _dispatcher = dispatcher;
            _TargetWatcherTask = Task.Run(() => DoTargetWatcher());
        }

        private async Task DoTargetWatcher()
        {
            while (true)
            {
                Parallel.ForEach(SavedTargets.Targets, Target =>
                {
                    var oldAvailable = Target.IsAvailable;
                    var OldAPIAvailable = Target.IsAPIAvailable;

                    Target.IsAvailable = Helpers.PingHost(Target.IPAddress);
                    Target.IsAPIAvailable = Helpers.TestTcpConnection(Target.IPAddress, Settings.CreateInstance().APIPort);
                    Target.SaveStatus();

                    if (Target.IsAPIAvailable)
                        SavedTargets.UpdateTargetInfo(Target.Name);
                    else
                    {
                        Target.CPUTemp = 0;
                        Target.SOCTemp = 0;
                        Target.ThreadCount = 0;
                        Target.AverageCPUUsage = 0;
                        Target.BusyCore = 0;
                        Target.RamUsage = 0;
                        Target.VRamUsage = 0;
                        Target.CurrentTitleID = "-";
                        Target.Save();
                    }

                    // Forward Target Availability.
                    if (oldAvailable != Target.IsAvailable)
                    {
                        var Packet = new ForwardPacket(ForwardPacket.PacketType.TargetAvailability, Target.IPAddress);
                        Packet.TargetAvailability.Available = Target.IsAvailable;
                        Packet.TargetAvailability.Name = Target.Name;
                        _dispatcher.ForwardPacketAll(Packet);
                    }

                    // Forward API Availability.
                    if (OldAPIAvailable != Target.IsAPIAvailable)
                    {
                        var Packet = new ForwardPacket(ForwardPacket.PacketType.TargetAPIAvailability, Target.IPAddress);
                        Packet.TargetAPIAvailability.Available = Target.IsAvailable;
                        Packet.TargetAPIAvailability.Name = Target.Name;
                        _dispatcher.ForwardPacketAll(Packet);
                    }
                });

                await Task.Delay(1000, _TargetWatcherCancellationToken);

                if (_TargetWatcherCancellationToken.IsCancellationRequested)
                    break;
            }
        }
    }
}
