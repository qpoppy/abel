#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

// Wrapper function for open syscall
int open_wrapper(const char *pathname, int flags, mode_t mode) {
    int fd;
    asm volatile (
        "mov $2, %%rax\n\t"
        "mov %1, %%rdi\n\t"
        "mov %2, %%rsi\n\t"
        "mov %3, %%rdx\n\t"
        "syscall\n\t"
        "mov %%rax, %0\n\t"
        : "=r" (fd)
        : "r" (pathname), "r" (flags), "r" (mode)
        : "%rax", "%rdi", "%rsi", "%rdx"
    );
    return fd;
}

// Wrapper function for read syscall
ssize_t read_wrapper(int fd, void *buf, size_t count) {
    ssize_t ret;
    asm volatile (
        "mov $0, %%rax\n\t"
        "mov %1, %%rdi\n\t"
        "mov %2, %%rsi\n\t"
        "mov %3, %%rdx\n\t"
        "syscall\n\t"
        "mov %%rax, %0\n\t"
        : "=r" (ret)
        : "r" (fd), "r" (buf), "r" (count)
        : "%rax", "%rdi", "%rsi", "%rdx"
    );
    return ret;
}

// Wrapper function for write syscall
ssize_t write_wrapper(int fd, const void *buf, size_t count) {
    ssize_t ret;
    asm volatile (
        "mov $1, %%rax\n\t"
        "mov %1, %%rdi\n\t"
        "mov %2, %%rsi\n\t"
        "mov %3, %%rdx\n\t"
        "syscall\n\t"
        "mov %%rax, %0\n\t"
        : "=r" (ret)
        : "r" (fd), "r" (buf), "r" (count)
        : "%rax", "%rdi", "%rsi", "%rdx"
    );
    return ret;
}

// Wrapper function for close syscall
int close_wrapper(int fd) {
    int ret;
    asm volatile (
        "mov $3, %%rax\n\t"
        "mov %1, %%rdi\n\t"
        "syscall\n\t"
        "mov %%rax, %0\n\t"
        : "=r" (ret)
        : "r" (fd)
        : "%rax", "%rdi"
    );
    return ret;
}

// Wrapper function for mmap syscall
void *mmap_wrapper(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
    void *ret;
    asm volatile (
        "mov $9, %%rax\n\t"
        "mov %1, %%rdi\n\t"
        "mov %2, %%rsi\n\t"
        "mov %3, %%rdx\n\t"
        "mov %4, %%r10\n\t"
        "mov %5, %%r8\n\t"
        "mov $0, %%r9\n\t"
        "syscall\n\t"
        "mov %%rax, %0\n\t"
        : "=r" (ret)
        : "r" (addr), "r" (length), "r" (prot), "r" (flags), "r" (fd), "r" (offset)
        : "%rax", "%rdi", "%rsi", "%rdx", "%r10", "%r8", "%r9"
    );
    if (ret == MAP_FAILED) {
        errno = -1;
    }
    return ret;
}

// Wrapper function for munmap syscall
int munmap_wrapper(void *addr, size_t length) {
    int ret;
    asm volatile (
        "mov $11, %%rax\n\t"
        "mov %1, %%rdi\n\t"
        "mov %2, %%rsi\n\t"
        "syscall\n\t"
        "mov %%rax, %0\n\t"
        : "=r" (ret)
        : "r" (addr), "r" (length)
        : "%rax", "%rdi", "%rsi"
    );
    return ret;
}
