#define FUSE_USE_VERSION 35
#include <fuse3/fuse.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/sysinfo.h>

static int dev_getattr(const char *path, struct stat *stbuf,
                       struct fuse_file_info *fi)
{
    (void) fi;
    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") != 0)
        return -ENOENT;
    stbuf->st_mode = S_IFREG | 0444;
    stbuf->st_nlink = 1;
    stbuf->st_size = 0;
    return 0;
}

static int dev_open(const char *path, struct fuse_file_info *fi)
{
    (void) fi;
    if (strcmp(path, "/") != 0)
        return -ENOENT;
    return 0;
}

static int dev_read(const char *path, char *out, size_t size, off_t off,
                    struct fuse_file_info *fi)
{
    (void) fi;
    if (strcmp(path, "/") != 0)
        return -ENOENT;

    struct sysinfo info;
    sysinfo(&info);

    FILE *f;
    double load1 = 0, load5 = 0, load15 = 0;
    f = fopen("/proc/loadavg", "r");
    if (f) {
        fscanf(f, "%lf %lf %lf", &load1, &load5, &load15);
        fclose(f);
    }

    char buf[512];
    int len = snprintf(buf, sizeof(buf),
                       "uptime: %ld\nloadavg: %.2f %.2f %.2f\nmem: total %lu kB free %lu kB\n",
                       info.uptime,
                       load1, load5, load15,
                       info.totalram / 1024,
                       info.freeram / 1024);
    if (len < 0)
        len = 0;

    if (off >= len)
        return 0;
    if (off + size > len)
        size = len - off;
    memcpy(out, buf + off, size);
    return size;
}

static const struct fuse_operations dev_oper = {
    .getattr = dev_getattr,
    .open = dev_open,
    .read = dev_read,
};

int main(int argc, char *argv[])
{
    return fuse_main(argc, argv, &dev_oper, NULL);
}

