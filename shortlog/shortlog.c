#define FUSE_USE_VERSION 35
#include <fuse3/fuse.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#define MAX_ENTRIES 16
#define ENTRY_LEN 256

static char logbuf[MAX_ENTRIES][ENTRY_LEN];
static int head = 0, count = 0;

static int dev_getattr(const char *path, struct stat *stbuf,
                       struct fuse_file_info *fi)
{
    (void) fi;
    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") != 0)
        return -ENOENT;
    stbuf->st_mode = S_IFREG | 0666;
    stbuf->st_nlink = 1;
    stbuf->st_size = MAX_ENTRIES * ENTRY_LEN;
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

    char tmp[MAX_ENTRIES * ENTRY_LEN];
    size_t pos = 0;
    for (int i = 0; i < count; ++i) {
        int idx = (head - count + i + MAX_ENTRIES) % MAX_ENTRIES;
        pos += snprintf(tmp + pos, sizeof(tmp) - pos, "%s\n", logbuf[idx]);
        if (pos >= sizeof(tmp))
            break;
    }
    if (off >= pos)
        return 0;
    if (off + size > pos)
        size = pos - off;
    memcpy(out, tmp + off, size);
    return size;
}

static int dev_write(const char *path, const char *in, size_t size, off_t off,
                     struct fuse_file_info *fi)
{
    (void) fi;
    (void) off;
    if (strcmp(path, "/") != 0)
        return -ENOENT;
    if (size >= ENTRY_LEN)
        size = ENTRY_LEN - 1;
    memcpy(logbuf[head], in, size);
    logbuf[head][size] = '\0';
    head = (head + 1) % MAX_ENTRIES;
    if (count < MAX_ENTRIES)
        ++count;
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

