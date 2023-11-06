#ifndef LIB_LINUX_H
#define LIB_LINUX_H

#include <linux/types.h>
#include <linux/syscalls.h>
#include <linux/version.h>
#include <asm/unistd.h>
#include <asm/current.h>
#include <asm/uaccess.h>

// Wrapper functions for Linux system calls
asmlinkage long sys_open_wrapper(const char __user *filename, int flags, umode_t mode);
asmlinkage long sys_close_wrapper(unsigned int fd);
asmlinkage long sys_read_wrapper(unsigned int fd, char __user *buf, size_t count);
asmlinkage long sys_write_wrapper(unsigned int fd, const char __user *buf, size_t count);
asmlinkage long sys_lseek_wrapper(unsigned int fd, off_t offset, unsigned int whence);
asmlinkage long sys_ioctl_wrapper(unsigned int fd, unsigned int cmd, unsigned long arg);
asmlinkage long sys_stat_wrapper(const char __user *filename, struct stat __user *statbuf);
asmlinkage long sys_fstat_wrapper(unsigned int fd, struct stat __user *statbuf);
asmlinkage long sys_mmap_wrapper(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd, unsigned long off);
asmlinkage long sys_munmap_wrapper(unsigned long addr, size_t len);
asmlinkage long sys_pipe_wrapper(int __user *filedes);
asmlinkage long sys_dup_wrapper(unsigned int oldfd);
asmlinkage long sys_dup2_wrapper(unsigned int oldfd, unsigned int newfd);

#endif // LIB_LINUX_H

