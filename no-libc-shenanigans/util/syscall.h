/*
 * Copyright © 2005-2020 Rich Felker, et al.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef SYSCALL_H
#define SYSCALL_H

static __inline long __syscall0(long n)
{
	unsigned long ret;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall1(long n, long a1)
{
	unsigned long ret;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall2(long n, long a1, long a2)
{
	unsigned long ret;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2)
						  : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall3(long n, long a1, long a2, long a3)
{
	unsigned long ret;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall4(long n, long a1, long a2, long a3, long a4)
{
	unsigned long ret;
	register long r10 __asm__("r10") = a4;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10): "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall5(long n, long a1, long a2, long a3, long a4, long a5)
{
	unsigned long ret;
	register long r10 __asm__("r10") = a4;
	register long r8 __asm__("r8") = a5;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10), "r"(r8) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
	unsigned long ret;
	register long r10 __asm__("r10") = a4;
	register long r8 __asm__("r8") = a5;
	register long r9 __asm__("r9") = a6;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10), "r"(r8), "r"(r9) : "rcx", "r11", "memory");
	return ret;
}

#ifndef __scc
#define __scc(X) ((long) (X))
typedef long syscall_arg_t;
#endif

#define __syscall1(n,a) __syscall1(n,__scc(a))
#define __syscall2(n,a,b) __syscall2(n,__scc(a),__scc(b))
#define __syscall3(n,a,b,c) __syscall3(n,__scc(a),__scc(b),__scc(c))
#define __syscall4(n,a,b,c,d) __syscall4(n,__scc(a),__scc(b),__scc(c),__scc(d))
#define __syscall5(n,a,b,c,d,e) __syscall5(n,__scc(a),__scc(b),__scc(c),__scc(d),__scc(e))
#define __syscall6(n,a,b,c,d,e,f) __syscall6(n,__scc(a),__scc(b),__scc(c),__scc(d),__scc(e),__scc(f))
#define __syscall7(n,a,b,c,d,e,f,g) __syscall7(n,__scc(a),__scc(b),__scc(c),__scc(d),__scc(e),__scc(f),__scc(g))

#define __SYSCALL_NARGS_X(a,b,c,d,e,f,g,h,n,...) n
#define __SYSCALL_NARGS(...) __SYSCALL_NARGS_X(__VA_ARGS__,7,6,5,4,3,2,1,0,)
#define __SYSCALL_CONCAT_X(a,b) a##b
#define __SYSCALL_CONCAT(a,b) __SYSCALL_CONCAT_X(a,b)
#define __SYSCALL_DISP(b,...) __SYSCALL_CONCAT(b,__SYSCALL_NARGS(__VA_ARGS__))(__VA_ARGS__)

#define syscall(...) __SYSCALL_DISP(__syscall,__VA_ARGS__)

#define SYS_read				0
#define SYS_write				1
#define SYS_open				2
#define SYS_close				3
#define SYS_stat				4
#define SYS_fstat				5
#define SYS_lstat				6
#define SYS_poll				7
#define SYS_lseek				8
#define SYS_mmap				9
#define SYS_mprotect			10
#define SYS_munmap				11
#define SYS_brk				12
#define SYS_rt_sigaction		13
#define SYS_rt_sigprocmask		14
#define SYS_rt_sigreturn		15
#define SYS_ioctl				16
#define SYS_pread64			17
#define SYS_pwrite64			18
#define SYS_readv				19
#define SYS_writev				20
#define SYS_access				21
#define SYS_pipe				22
#define SYS_select				23
#define SYS_sched_yield		24
#define SYS_mremap				25
#define SYS_msync				26
#define SYS_mincore			27
#define SYS_madvise			28
#define SYS_shmget				29
#define SYS_shmat				30
#define SYS_shmctl				31
#define SYS_dup				32
#define SYS_dup2				33
#define SYS_pause				34
#define SYS_nanosleep			35
#define SYS_getitimer			36
#define SYS_alarm				37
#define SYS_setitimer			38
#define SYS_getpid				39
#define SYS_sendfile			40
#define SYS_socket				41
#define SYS_connect			42
#define SYS_accept				43
#define SYS_sendto				44
#define SYS_recvfrom			45
#define SYS_sendmsg			46
#define SYS_recvmsg			47
#define SYS_shutdown			48
#define SYS_bind				49
#define SYS_listen				50
#define SYS_getsockname		51
#define SYS_getpeername		52
#define SYS_socketpair			53
#define SYS_setsockopt			54
#define SYS_getsockopt			55
#define SYS_clone				56
#define SYS_fork				57
#define SYS_vfork				58
#define SYS_execve				59
#define SYS_exit				60
#define SYS_wait4				61
#define SYS_kill				62
#define SYS_uname				63
#define SYS_semget				64
#define SYS_semop				65
#define SYS_semctl				66
#define SYS_shmdt				67
#define SYS_msgget				68
#define SYS_msgsnd				69
#define SYS_msgrcv				70
#define SYS_msgctl				71
#define SYS_fcntl				72
#define SYS_flock				73
#define SYS_fsync				74
#define SYS_fdatasync			75
#define SYS_truncate			76
#define SYS_ftruncate			77
#define SYS_getdents			78
#define SYS_getcwd				79
#define SYS_chdir				80
#define SYS_fchdir				81
#define SYS_rename				82
#define SYS_mkdir				83
#define SYS_rmdir				84
#define SYS_creat				85
#define SYS_link				86
#define SYS_unlink				87
#define SYS_symlink			88
#define SYS_readlink			89
#define SYS_chmod				90
#define SYS_fchmod				91
#define SYS_chown				92
#define SYS_fchown				93
#define SYS_lchown				94
#define SYS_umask				95
#define SYS_gettimeofday		96
#define SYS_getrlimit			97
#define SYS_getrusage			98
#define SYS_sysinfo			99
#define SYS_times				100
#define SYS_ptrace				101
#define SYS_getuid				102
#define SYS_syslog				103
#define SYS_getgid				104
#define SYS_setuid				105
#define SYS_setgid				106
#define SYS_geteuid			107
#define SYS_getegid			108
#define SYS_setpgid			109
#define SYS_getppid			110
#define SYS_getpgrp			111
#define SYS_setsid				112
#define SYS_setreuid			113
#define SYS_setregid			114
#define SYS_getgroups			115
#define SYS_setgroups			116
#define SYS_setresuid			117
#define SYS_getresuid			118
#define SYS_setresgid			119
#define SYS_getresgid			120
#define SYS_getpgid			121
#define SYS_setfsuid			122
#define SYS_setfsgid			123
#define SYS_getsid				124
#define SYS_capget				125
#define SYS_capset				126
#define SYS_rt_sigpending		127
#define SYS_rt_sigtimedwait	128
#define SYS_rt_sigqueueinfo	129
#define SYS_rt_sigsuspend		130
#define SYS_sigaltstack		131
#define SYS_utime				132
#define SYS_mknod				133
#define SYS_uselib				134
#define SYS_personality		135
#define SYS_ustat				136
#define SYS_statfs				137
#define SYS_fstatfs			138
#define SYS_sysfs				139
#define SYS_getpriority			140
#define SYS_setpriority			141
#define SYS_sched_setparam			142
#define SYS_sched_getparam			143
#define SYS_sched_setscheduler		144
#define SYS_sched_getscheduler		145
#define SYS_sched_get_priority_max	146
#define SYS_sched_get_priority_min	147
#define SYS_sched_rr_get_interval	148
#define SYS_mlock					149
#define SYS_munlock				150
#define SYS_mlockall				151
#define SYS_munlockall				152
#define SYS_vhangup				153
#define SYS_modify_ldt				154
#define SYS_pivot_root				155
#define SYS__sysctl				156
#define SYS_prctl					157
#define SYS_arch_prctl				158
#define SYS_adjtimex				159
#define SYS_setrlimit				160
#define SYS_chroot					161
#define SYS_sync					162
#define SYS_acct					163
#define SYS_settimeofday			164
#define SYS_mount					165
#define SYS_umount2				166
#define SYS_swapon					167
#define SYS_swapoff				168
#define SYS_reboot					169
#define SYS_sethostname			170
#define SYS_setdomainname			171
#define SYS_iopl					172
#define SYS_ioperm					173
#define SYS_create_module			174
#define SYS_init_module			175
#define SYS_delete_module			176
#define SYS_get_kernel_syms		177
#define SYS_query_module			178
#define SYS_quotactl				179
#define SYS_nfsservctl				180
#define SYS_getpmsg				181
#define SYS_putpmsg				182
#define SYS_afs_syscall			183
#define SYS_tuxcall				184
#define SYS_security				185
#define SYS_gettid					186
#define SYS_readahead				187
#define SYS_setxattr				188
#define SYS_lsetxattr				189
#define SYS_fsetxattr				190
#define SYS_getxattr				191
#define SYS_lgetxattr				192
#define SYS_fgetxattr				193
#define SYS_listxattr				194
#define SYS_llistxattr				195
#define SYS_flistxattr				196
#define SYS_removexattr			197
#define SYS_lremovexattr			198
#define SYS_fremovexattr			199
#define SYS_tkill					200
#define SYS_time					201
#define SYS_futex					202
#define SYS_sched_setaffinity		203
#define SYS_sched_getaffinity		204
#define SYS_set_thread_area		205
#define SYS_io_setup				206
#define SYS_io_destroy				207
#define SYS_io_getevents			208
#define SYS_io_submit				209
#define SYS_io_cancel				210
#define SYS_get_thread_area		211
#define SYS_lookup_dcookie			212
#define SYS_epoll_create			213
#define SYS_epoll_ctl_old			214
#define SYS_epoll_wait_old			215
#define SYS_remap_file_pages		216
#define SYS_getdents64				217
#define SYS_set_tid_address		218
#define SYS_restart_syscall		219
#define SYS_semtimedop				220
#define SYS_fadvise64				221
#define SYS_timer_create			222
#define SYS_timer_settime			223
#define SYS_timer_gettime			224
#define SYS_timer_getoverrun		225
#define SYS_timer_delete			226
#define SYS_clock_settime			227
#define SYS_clock_gettime			228
#define SYS_clock_getres			229
#define SYS_clock_nanosleep		230
#define SYS_exit_group				231
#define SYS_epoll_wait				232
#define SYS_epoll_ctl				233
#define SYS_tgkill					234
#define SYS_utimes					235
#define SYS_vserver				236
#define SYS_mbind					237
#define SYS_set_mempolicy			238
#define SYS_get_mempolicy			239
#define SYS_mq_open				240
#define SYS_mq_unlink				241
#define SYS_mq_timedsend			242
#define SYS_mq_timedreceive		243
#define SYS_mq_notify				244
#define SYS_mq_getsetattr			245
#define SYS_kexec_load				246
#define SYS_waitid					247
#define SYS_add_key				248
#define SYS_request_key			249
#define SYS_keyctl					250
#define SYS_ioprio_set				251
#define SYS_ioprio_get				252
#define SYS_inotify_init			253
#define SYS_inotify_add_watch		254
#define SYS_inotify_rm_watch		255
#define SYS_migrate_pages			256
#define SYS_openat					257
#define SYS_mkdirat				258
#define SYS_mknodat				259
#define SYS_fchownat				260
#define SYS_futimesat				261
#define SYS_newfstatat				262
#define SYS_unlinkat				263
#define SYS_renameat				264
#define SYS_linkat					265
#define SYS_symlinkat				266
#define SYS_readlinkat				267
#define SYS_fchmodat				268
#define SYS_faccessat				269
#define SYS_pselect6				270
#define SYS_ppoll					271
#define SYS_unshare				272
#define SYS_set_robust_list		273
#define SYS_get_robust_list		274
#define SYS_splice					275
#define SYS_tee					276
#define SYS_sync_file_range		277
#define SYS_vmsplice				278
#define SYS_move_pages				279
#define SYS_utimensat				280
#define SYS_epoll_pwait			281
#define SYS_signalfd				282
#define SYS_timerfd_create			283
#define SYS_eventfd				284
#define SYS_fallocate				285
#define SYS_timerfd_settime		286
#define SYS_timerfd_gettime		287
#define SYS_accept4				288
#define SYS_signalfd4				289
#define SYS_eventfd2				290
#define SYS_epoll_create1			291
#define SYS_dup3					292
#define SYS_pipe2					293
#define SYS_inotify_init1			294
#define SYS_preadv					295
#define SYS_pwritev				296
#define SYS_rt_tgsigqueueinfo		297
#define SYS_perf_event_open		298
#define SYS_recvmmsg				299
#define SYS_fanotify_init			300
#define SYS_fanotify_mark			301
#define SYS_prlimit64				302
#define SYS_name_to_handle_at			303
#define SYS_open_by_handle_at			304
#define SYS_clock_adjtime			305
#define SYS_syncfs				306
#define SYS_sendmmsg				307
#define SYS_setns				308
#define SYS_getcpu				309
#define SYS_process_vm_readv			310
#define SYS_process_vm_writev			311
#define SYS_kcmp				312
#define SYS_finit_module			313
#define SYS_sched_setattr			314
#define SYS_sched_getattr			315
#define SYS_renameat2				316
#define SYS_seccomp				317
#define SYS_getrandom				318
#define SYS_memfd_create			319
#define SYS_kexec_file_load			320
#define SYS_bpf				321
#define SYS_execveat				322
#define SYS_userfaultfd			323
#define SYS_membarrier				324
#define SYS_mlock2				325
#define SYS_copy_file_range			326
#define SYS_preadv2				327
#define SYS_pwritev2				328
#define SYS_pkey_mprotect			329
#define SYS_pkey_alloc				330
#define SYS_pkey_free				331
#define SYS_statx				332
#define SYS_io_pgetevents			333
#define SYS_rseq				334
#define SYS_pidfd_send_signal			424
#define SYS_io_uring_setup			425
#define SYS_io_uring_enter			426
#define SYS_io_uring_register			427
#define SYS_open_tree		428
#define SYS_move_mount		429
#define SYS_fsopen		430
#define SYS_fsconfig		431
#define SYS_fsmount		432
#define SYS_fspick		433
#define SYS_pidfd_open		434
#define SYS_clone3		435
#define SYS_close_range	436
#define SYS_openat2		437
#define SYS_pidfd_getfd	438
#define SYS_faccessat2		439
#define SYS_process_madvise	440
#define SYS_epoll_pwait2	441
#define SYS_mount_setattr	442
#define SYS_landlock_create_ruleset	444
#define SYS_landlock_add_rule	445
#define SYS_landlock_restrict_self	446
#define SYS_memfd_secret	447
#define SYS_process_mrelease	448
#define SYS_futex_waitv	449
#define SYS_set_mempolicy_home_node	450
#define SYS_cachestat		451
#define SYS_fchmodat2		452

/* open */
#define O_RDONLY  00
#define O_WRONLY  01
#define O_RDWR    02

#define O_CREAT        0100
#define O_EXCL         0200
#define O_NOCTTY       0400
#define O_TRUNC       01000
#define O_APPEND      02000
#define O_NONBLOCK    04000
#define O_DSYNC      010000
#define O_SYNC     04010000
#define O_RSYNC    04010000
#define O_DIRECTORY 0200000
#define O_NOFOLLOW  0400000
#define O_CLOEXEC  02000000

#define O_ASYNC      020000
#define O_DIRECT     040000
#define O_LARGEFILE       0
#define O_NOATIME  01000000
#define O_PATH    010000000
#define O_TMPFILE 020200000
#define O_NDELAY O_NONBLOCK

#define S_ISUID 04000
#define S_ISGID 02000
#define S_ISVTX 01000
#define S_IRUSR 0400
#define S_IWUSR 0200
#define S_IXUSR 0100
#define S_IRWXU 0700
#define S_IRGRP 0040
#define S_IWGRP 0020
#define S_IXGRP 0010
#define S_IRWXG 0070
#define S_IROTH 0004
#define S_IWOTH 0002
#define S_IXOTH 0001
#define S_IRWXO 0007

/* mmap */
#define MAP_SHARED     0x01
#define MAP_PRIVATE    0x02
#define MAP_SHARED_VALIDATE 0x03
#define MAP_TYPE       0x0f
#define MAP_FIXED      0x10
#define MAP_ANON       0x20
#define MAP_ANONYMOUS  MAP_ANON
#define MAP_NORESERVE  0x4000
#define MAP_GROWSDOWN  0x0100
#define MAP_DENYWRITE  0x0800
#define MAP_EXECUTABLE 0x1000
#define MAP_LOCKED     0x2000
#define MAP_POPULATE   0x8000
#define MAP_NONBLOCK   0x10000
#define MAP_STACK      0x20000
#define MAP_HUGETLB    0x40000
#define MAP_SYNC       0x80000
#define MAP_FIXED_NOREPLACE 0x100000
#define MAP_FILE       0

#define MAP_HUGE_SHIFT 26
#define MAP_HUGE_MASK  0x3f
#define MAP_HUGE_64KB  (16 << 26)
#define MAP_HUGE_512KB (19 << 26)
#define MAP_HUGE_1MB   (20 << 26)
#define MAP_HUGE_2MB   (21 << 26)
#define MAP_HUGE_8MB   (23 << 26)
#define MAP_HUGE_16MB  (24 << 26)
#define MAP_HUGE_32MB  (25 << 26)
#define MAP_HUGE_256MB (28 << 26)
#define MAP_HUGE_512MB (29 << 26)
#define MAP_HUGE_1GB   (30 << 26)
#define MAP_HUGE_2GB   (31 << 26)
#define MAP_HUGE_16GB  (34U << 26)

#define PROT_NONE      0
#define PROT_READ      1
#define PROT_WRITE     2
#define PROT_EXEC      4
#define PROT_GROWSDOWN 0x01000000
#define PROT_GROWSUP   0x02000000

#endif /* SYSCALL_H */
