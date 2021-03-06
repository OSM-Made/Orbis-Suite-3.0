#pragma once

#if defined(SOFTWARE_VERSION_NA)

/* Util */
#define addr_Xfast_syscall		                0x0
#define addr_sysvec                             0x0
#define addr_kernel_map                         0x0
#define addr_prison0                            0x0
#define addr_rootvnode                          0x0
#define addr_copyin								0x0
#define addr_copyout							0x0

/* STD Lib */
#define addr_M_TEMP                             0x0
#define addr_M_MOUNT                            0x0
#define addr_malloc								0x0
#define addr_free					    		0x0
#define addr_memcpy								0x0
#define addr_memset								0x0
#define addr_memcmp								0x0
#define addr_strlen                             0x0
#define addr_strcpy								0x0
#define addr_strncpy                            0x0
#define addr_strcmp                             0x0
#define addr_strstr                             0x0
#define addr_sprintf                            0x0
#define addr_snprintf                           0x0
#define addr_vsprintf                           0x0
#define addr_vprintf                            0x0
#define addr_sscanf                             0x0
#define addr_strdup                             0x0
#define addr_realloc                            0x0
#define addr_kprintf                            0x0

#define addr_kmem_alloc							0x0

/* Kproc */
#define addr_kproc_create					    0x0
#define addr_kproc_exit                         0x0
#define addr_kproc_resume                       0x0
#define addr_kproc_shutdown                     0x0
#define addr_kproc_start                        0x0
#define addr_kproc_suspend                      0x0
#define addr_kproc_suspend_check                0x0
#define addr_kproc_kthread_add				    0x0
#define addr_pause                              0x0
#define addr_kthread_add						0x0
#define addr_kthread_exit						0x0
#define addr_kthread_suspend					0x0
#define addr_kthread_suspend_check				0x0
#define addr_kthread_set_affinity				0x0

/* Module Offsets */
#define addr_thr_initial_libkernel              0x0
#define addr_thr_initial_libkernel_web          0x0
#define addr_thr_initial_libkernel_sys          0x0

/* Proc */
#define addr_allproc_lock                       0x0
#define addr_allproc						    0x0
#define addr_proc_kill                          0x0
#define addr_proc_rwmem							0x0
#define addr_create_thread                      0x0

/* ptrace */
#define addr_kptrace                            0x0
#define addr_kpsignal                           0x0
#define addr_kwait                              0x0
#define addr_kDelay                             0x0

/* Virtual Memory */
#define addr_vmspace_acquire_ref				0x0
#define addr_vmspace_free						0x0
#define addr_vm_map_lock_read					0x0
#define addr_vm_map_unlock_read					0x0
#define addr_vm_map_lookup_entry				0x0
#define addr_vm_map_findspace					0x0
#define addr_vm_map_insert						0x0
#define addr_vm_map_lock						0x0
#define addr_vm_map_unlock 						0x0
#define addr_vm_map_delete						0x0
#define addr_vm_map_protect						0x0

/*Mutex Locks*/
#define addr_mtx_init                           0x0
#define addr_mtx_destroy                        0x0
#define addr_mtx_lock_flags                     0x0
#define addr_mtx_unlock_flags                   0x0

#define addr__sx_slock                          0x0
#define addr__sx_sunlock                        0x0

/* Critical Sections */
#define addr_EnterCriticalSection               0x0
#define addr_ExitCriticalSection                0x0

/* Event Handling */
#define addr_eventhandler_register              0x0
#define addr_eventhandler_deregister            0x0
#define addr_eventhandler_find_list             0x0

/* Trap Hooks */
#define addr_trapHook                           0x0
#define addr_trap_fatalHook                     0x0

/* Registry Functions */
#define addr_sceRegMgrGetStr                    0x0
#define addr_sceRegMgrSetStr                    0x0
#define addr_sceRegMgrGetInt                    0x0
#define addr_sceRegMgrSetInt                    0x0
#define addr_sceRegMgrGetBin                    0x0
#define addr_sceRegMgrSetBin                    0x0

/* Flash & NVS */
#define addr_icc_nvs_read                       0x0
#define addr_icc_nvs_write                      0x0

/* Driver */
#define addr_make_dev_p                         0x0
#define addr_destroy_dev                        0x0

/* kmem */
#define addr_kmem_alloc                         0x0
#define addr_kmem_free                          0x0
#define addr_kernel_map                         0x0

/* File IO */
#define addr_vn_fullpath                        0x0
#define addr_kern_rmdir                         0x0
#define addr_kern_mkdir                         0x0
#define addr_kern_open                          0x0
#define addr_kern_mount                         0x0
#define addr_mount_argf                         0x0

#endif