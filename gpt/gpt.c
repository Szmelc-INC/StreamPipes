#define FUSE_USE_VERSION 35
#include <fuse3/fuse.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#define PROMPT_MAX 1024

static char prompt[PROMPT_MAX];

static int dev_getattr(const char *path, struct stat *stbuf,
                       struct fuse_file_info *fi)
{
    (void) fi;
    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") != 0)
        return -ENOENT;
    stbuf->st_mode = S_IFREG | 0666;
    stbuf->st_nlink = 1;
    stbuf->st_size = strlen(prompt);
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
    char response[PROMPT_MAX + 64];
    int len = snprintf(response, sizeof(response),
                       "LLM not wired. Last prompt: %s\n", prompt[0] ? prompt : "<none>");
    if (off >= len)
        return 0;
    if (off + size > len)
        size = len - off;
    memcpy(out, response + off, size);
    return size;
}

static int dev_write(const char *path, const char *in, size_t size, off_t off,
                     struct fuse_file_info *fi)
{
    (void) fi;
    (void) off;
    if (strcmp(path, "/") != 0)
        return -ENOENT;
    if (size >= PROMPT_MAX)
        size = PROMPT_MAX - 1;
    memcpy(prompt, in, size);
    prompt[size] = '\0';
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

