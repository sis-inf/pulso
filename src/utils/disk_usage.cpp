#include <sys/statvfs.h>

double getDiskUsage() {
    struct statvfs stat;

    if (statvfs("/", &stat) != 0) {
        return -1.0;
    }

    unsigned long blocks = stat.f_blocks;
    unsigned long bfree  = stat.f_bfree;

    return (double)(blocks - bfree) / blocks * 100;
}