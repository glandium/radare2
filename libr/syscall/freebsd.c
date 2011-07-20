#include <r_syscall.h>

/* there are LOT of magic syscalls in freebsd...ill really have to look on it */
/* jail, jail_attach, utrace, kqueue->EV_FILTER_PROC->NOTE_FORK, nfsclnt */
/* syscall-freebsd */
RSyscallItem syscalls_freebsd_x86[] = {
	{ "syscall", 0x80, 0, 4 , "sysnum" },
	{ "exit", 0x80, 1, 1 },
	{ "fork", 0x80, 2, 0 },
	{ "read", 0x80, 3, 3 },
	{ "write", 0x80, 4, 3 },
	{ "open", 0x80, 5, 3 },
	{ "close", 0x80, 6, 1 },
	{ "wait4", 0x80, 7, 3 },
	{ "old_creat", 0x80, 8, 2 },
	{ "link", 0x80, 9, 2 },
	{ "unlink", 0x80, 10, 1 },
	{ "old_execve", 0x80, 11, 3},
	{ "chdir", 0x80, 12, 1},
	{ "fchdir", 0x80, 13, 1},
	{ "mknod", 0x80, 14, 1},
	{ "chmod", 0x80, 15, 1},
	{ "chown", 0x80, 16, 1},
	{ "break", 0x80, 17, 1},
	{ "old_fsstat", 0x80, 18, 1},
	{ "old_lseek", 0x80, 19, 1},
	{ "getpid", 0x80, 20, 0},
	{ "mount", 0x80, 21, 0},
	{ "unmount", 0x80, 22, 0},
	{ "setuid", 0x80, 23, 1},
	{ "getuid", 0x80, 24, 0},
	{ "ptrace", 0x80, 26, 4},
	{ "recvmsg", 0x80, 27, 4},
	{ "sendmsg", 0x80, 28, 4},
	{ "recvfrom", 0x80, 29, 4},
	{ "accept", 0x80, 30, 4},
	{ "getpeername", 0x80, 31, 3},
	{ "getsockname", 0x80, 32, 3},
	{ "access", 0x80, 33, 2},
	{ "chflags", 0x80, 34, 2},
	{ "fchflags", 0x80, 35, 2},
	{ "sync", 0x80, 36, 0},
	{ "kill", 0x80, 37, 2},
	{ "dup", 0x80, 41, 2},
	{ "pipe", 0x80, 42, 1},
	{ "getepid", 0x80, 43, 0},
	{ "profil", 0x80, 44, 4}, /* LOLSOME! THIS IS LIKE linux oprofile! we need to hack on it! */
	{ "ktrace", 0x80, 45, 4},
	{ "getgid", 0x80, 47, 0},
	{ "signal", 0x80, 48, 2},
	{ "getlogin", 0x80, 49, 0}, /* like getuid but returns a string */
	{ "setlogin", 0x80, 50, 1}, /* like setuid but passing a string */
	{ "acct", 0x80, 51, 1}, /* given a string for file */
	{ "sigaltstack", 0x80, 53, 2}, /* alterate stack context for signals */
	{ "ioctl", 0x80, 54, 3 },
	{ "reboot", 0x80, 55, 1},
	{ "revoke", 0x80, 56, 1}, /* given a string invalidates the access to a file */
	{ "symlink", 0x80, 57, 2},
	{ "readlink", 0x80, 58, 1},
	{ "execve", 0x80, 59, 2},
	{ "umask", 0x80, 60, 1},
	{ "chroot", 0x80, 61, 1},
	{ "mmap", 0x80, 90, 6},
	{ "munmap", 0x80, 91, 1},
	{ "socketcall", 0x80, 102, 2 },
	{ "sigreturn", 0x80, 119, 1 },
	{ "clone", 0x80, 120, 4 },
	{ "mprotect", 0x80, 125, 3},
	{ "rt_sigaction", 0x80, 174, 3},
	{ "rt_sigprocmask", 0x80, 175, 3},
	{ "sysctl", 0x80, 149, 1 },
	{ "mmap2", 0x80, 192, 6},
	{ "fstat64", 0x80, 197, 2},
	{ "fcntl64", 0x80, 221, 3},
	{ "gettid", 0x80, 224, 0},
	{ "set_thread_area", 0x80, 243, 2},
	{ "get_thread_area", 0x80, 244, 2},
	{ "exit_group", 0x80, 252, 1},
	{ NULL, 0x80, 0, 0 }
};