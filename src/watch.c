#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <uv.h>

// Inspired by http://nikhilm.github.io/uvbook/filesystem.html#file-change-events

char command[1024];

void run_command(uv_fs_event_t *handle, const char *filename, int events, int status) {
    char path[1024];
    size_t size = 1023;
    pid_t pid;

    // Does not handle error if path is longer than 1023.
    uv_fs_event_getpath(handle, path, &size);
    path[size] = '\0';

    if ((pid = fork()) == 0) {
        execl("/bin/bash", "bash", "-c", command, NULL);
        _exit(0);
    } else if (pid == -1)
        fprintf(stderr, "Something went terribly wrong.\n");
}

int main(int argc, char **argv) {
    if (argc <= 2) {
        fprintf(stderr, "Usage: %s <command> <file> [file2 ...]\n", argv[0]);
        return 1;
    }

    int i = 1;
    uv_loop_t *loop = uv_default_loop();

    while (i < argc) {
        if (strncmp(argv[i], "-c", 2) == 0) {
            // Concat the commands together into one string delimited by a space.
            while (++i < argc && argv[i][0] != '-') {
                strncat(command, argv[i], strlen(argv[i]));
                strncat(command, " ", 1);
            }
        } else {
            uv_fs_event_t *fs_event_req = malloc(sizeof(uv_fs_event_t));
            uv_fs_event_init(loop, fs_event_req);
            uv_fs_event_start(fs_event_req, run_command, argv[i], UV_FS_EVENT_RECURSIVE);
        }

        i++;
    }

    printf("Watching files...\n");

    return uv_run(loop, UV_RUN_DEFAULT);
}

