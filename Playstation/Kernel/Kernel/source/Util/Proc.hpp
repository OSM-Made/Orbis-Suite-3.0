#pragma once

extern "C"
{
    #include <sys/proc.h>
}

proc* GetCurrentGame();
int get_proc_count();
proc *proc_find_by_name(const char *name);
proc *proc_find_by_pid(int pid);

int proc_rw_mem(proc *p, void *ptr, size_t size, void *data, size_t *n, int write);
int proc_read_mem(struct proc *p, void *ptr, size_t size, void *data, size_t *n);
int proc_write_mem(struct proc *p, void *ptr, size_t size, void *data, size_t *n);
int proc_allocate(struct proc *p, void **address, size_t size);
int proc_deallocate(proc *p, void *address, size_t size);
int proc_mprotect(proc *p, void *address, void *end, int new_prot);
uint64_t proc_alloc_size(uint64_t p);

struct Backup_Jail
{
    prison* cr_prison;
    uid_t cr_uid;
    uid_t cr_ruid;
    gid_t cr_rgid;
    gid_t cr_groups;

    vnode* fd_jdir;
    vnode* fd_rdir;
};

void proc_Jailbreak(proc* proc, Backup_Jail* jail);
void proc_RestoreJail(proc* proc, Backup_Jail jail);
