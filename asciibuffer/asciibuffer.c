#define FUSE_USE_VERSION 35
#include <fuse3/fuse.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#define BUF_SIZE (1<<20) /* 1 MiB */

static char buffer[BUF_SIZE];
static size_t buf_size = 0;

static int dev_getattr(const char *path, struct stat *stbuf,
                       struct fuse_file_info *fi)
{
    (void) fi;
    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") != 0)
        return -ENOENT;
    stbuf->st_mode = S_IFREG | 0666;
    stbuf->st_nlink = 1;
    stbuf->st_size = buf_size;
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
    if (off >= buf_size)
        return 0;
    if (off + size > buf_size)
        size = buf_size - off;
    memcpy(out, buffer + off, size);
    return size;
}

static int dev_write(const char *path, const char *in, size_t size, off_t off,
                     struct fuse_file_info *fi)
{
    (void) fi;
    if (strcmp(path, "/") != 0)
        return -ENOENT;
    if (off >= BUF_SIZE)
        return -ENOSPC;
    if (off + size > BUF_SIZE)
        size = BUF_SIZE - off;
    memcpy(buffer + off, in, size);
    if (off + size > buf_size)
        buf_size = off + size;
    return size;
}

static const struct fuse_operations dev_oper = {
    .getattr = dev_getattr,
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
};

int main(int argc, char *argv[])
{
    return fuse_main(argc, argv, &dev_oper, NULL);
}

