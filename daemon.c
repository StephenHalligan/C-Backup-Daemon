#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>

#define EVENT_SIZE  (sizeof (struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))

int main(int argc, char *argv[]) {
    int fd, wd, length, i = 0;
    char buffer[BUF_LEN];

    // Create an inotify instance
    fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    // Add watch for directory
    wd = inotify_add_watch(fd, argv[1], IN_CREATE | IN_MODIFY);
    if (wd < 0) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }

    // Daemonize
    if (daemon(0, 0) == -1) {
        perror("daemon");
        exit(EXIT_FAILURE);
    }

    // Event loop
    while (1) {
        length = read(fd, buffer, BUF_LEN);
        if (length < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        i = 0;
        while (i < length) {
            struct inotify_event *event = (struct inotify_event *) &buffer[i];
            if (event->mask & (IN_CREATE | IN_MODIFY)) {
                printf("New file or changes detected in %s\n", argv[1]);
            }
            i += EVENT_SIZE + event->len;
        }
    }

    // Cleanup
    inotify_rm_watch(fd, wd);
    close(fd);

    return 0;
}
