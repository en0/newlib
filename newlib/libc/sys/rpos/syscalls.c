/* note these headers are all provided by newlib - you don't need to provide them */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>
 
char **environ; /* pointer to array of char * strings that define the current environment variables */

void _exit() {}
int close(int file) {}
int execve(char *name, char **argv, char **env) {}
int fork() {}
int fstat(int file, struct stat *st) {}
int getpid() {}
int isatty(int file) {}
int kill(int pid, int sig) {}
int link(char *old, char *new) {}
int lseek(int file, int ptr, int dir) {}
int open(const char *name, int flags, ...) {}
int read(int file, char *ptr, int len) {}
caddr_t sbrk(int incr) {}
int stat(const char *file, struct stat *st) {}
clock_t times(struct tms *buf) {}
int unlink(char *name) {}
int wait(int *status) {}

int write(int file, char *ptr, int len) {
    asm (
        "int $0x80"
        :
        : "a"(4), "b"(file), "c"(ptr), "d"(len) );

    return len;
}

int gettimeofday(struct timeval *p, void *z) {}
