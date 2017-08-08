#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdarg.h>

#define FORMAT_ERET(r) (r < 0 ? errno = -r, -1 : r)
 
char **environ; /* pointer to array of char * strings that define the current environment variables */

void _exit() {
    
    /* ISR 80:1 
     *
     * Exit a program without cleaning up files.
     */

    asm("int $0x80" : : "a"(45), "b"(0));
}

int fork() {
    
    /* ISR 80:2
     *
     * Create a new process.
     */

    int r;
    asm("int $0x80" : "=a"(r) : "a"(2));
    return FORMAT_ERET(r);
}

int read(int file, char *ptr, int len) {
    
    /* ISR 80:3
     *
     * Read from a file.
     */

    int r;
    asm("int $0x80" : "=a"(r) : "a"(3), "b"(file), "c"(ptr), "d"(len));
    return FORMAT_ERET(r);
}

int write(int file, char *ptr, int len) {

    /* ISR 80:4
     *
     * Write to a file.
     */

    int r;
    asm("int $0x80" : "=a"(r) : "a"(4), "b"(file), "c"(ptr), "d"(len) );
    return FORMAT_ERET(r);
}

int open(const char *name, int flags, ...) {

    /* ISR 80:5
     *
     * Open a file.
     */

    va_list ap;
    int mode, r;

    va_start(ap, flags);
    mode = va_arg(ap, int);
    va_end(ap);

    asm("int $0x80" : "=a"(r) : "a"(5), "b"(name), "c"(flags), "d"(mode));
    return FORMAT_ERET(r);
}

int close(int file) {

    /* ISR 80:6
     *
     * Close a file.
     */

    int r;
    asm("int $0x80" : "=a"(r) : "a"(6), "b"(file));
    return FORMAT_ERET(r);
}

int wait(int *status) {

    /* ISR 80:7
     *
     * Wait for a child process.
     */

    int r;
    asm("int $0x80"
        : "=a"(r)
        : "a"(7), "b"(status));
    return FORMAT_ERET(r);
}

int link(char *old, char *new) {

    /* ISR 80:9
     *
     * Establish a new name for an existing file.
     */

    int r;
    asm("int $0x80"
        : "=a"(r)
        : "a"(9), "b"(old), "c"(new));
    return FORMAT_ERET(r);
}

int unlink(char *name) {

    /* ISR 80:10
     *
     * Remove a file's directory entry.
     */

    int r;
    asm("int $0x80"
        : "=a"(r)
        : "a"(10), "b"(name));
    return FORMAT_ERET(r);
}

int execve(char *name, char **argv, char **env) {

    /* ISR 80:11
     *
     * Transfer control to a new process.
     */

    int r;
    asm("int $0x80"
        : "=a"(r)
        : "a"(11), "b"(name), "c"(argv), "d"(env));
    return FORMAT_ERET(r);
}

int lseek(int file, int ptr, int dir) {

    /* ISR 80:19
     *
     * Set position in a file.
     */

    int r;
    asm("int $0x80"
        : "=a"(r)
        : "a"(19), "b"(file), "c"(ptr), "d"(dir));
    return FORMAT_ERET(r);
}

int getpid() {

    /* ISR 80:20
     *
     * Process-ID; this is sometimes used to generate strings unlikely to
     * conflict with other processes.
     */

    int r;
    asm("int $0x80"
        : "=a"(r)
        : "a"(20));
    return FORMAT_ERET(r);
}

int kill(int pid, int sig) {

    /* ISR 80:37
     *
     * Send a signal.
     */

    int r;
    asm("int $0x80"
        : "=a"(r)
        : "a"(37), "b"(pid), "c"(sig));
    return FORMAT_ERET(r);
}

clock_t times(struct tms *buf) {

    /* ISR 80:43
     *
     * Timing information for current process.
     */

    int r;
    asm("int $0x80"
        : "=a"(r)
        : "a"(43), "b"(buf));
    return FORMAT_ERET(r);
}

caddr_t sbrk(int incr) {

    /* ISR 80:45
     *
     * Increase program data space.
     */

    int r;
    asm("int $0x80"
        : "=a"(r)
        : "a"(45), "b"(incr));

    return (caddr_t)FORMAT_ERET(r);
}

int gettimeofday(struct timeval *p, void *z) {

    /* ISR 80:78
     *
     * Get timezone & seconds since 1-jan-1970.
     */

    int r;
    asm("int $0x80"
        : "=a"(r)
        : "a"(78), "b"(p), "c"(z));
    return FORMAT_ERET(r);
}

int stat(const char *file, struct stat *st) {

    /* ISR 80:106
     *
     * Status of a file (by name).
     */

    int r;
    asm("int $0x80"
        : "=a"(r)
        : "a"(106), "b"(file), "c"(st));
    return FORMAT_ERET(r);
}

int fstat(int file, struct stat *st) {

    /* ISR 80:108
     *
     * Status of an open file.
     */

    int r;
    asm("int $0x80"
        : "=a"(r)
        : "a"(108), "b"(file), "c"(st));
    return FORMAT_ERET(r);
}

int isatty(int file) {

    /* ISR 80:90
     *
     * Query whether output stream is a terminal.
     */

    int r;
    asm("int $0x80"
        : "=a"(r)
        : "a"(1000), "b"(file));
    return FORMAT_ERET(r);
}

