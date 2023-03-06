#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <syslog.h>
#include <stdio.h>

void lock_directories() {

    FILE *file;
    file = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "ab");
    char *msg = "Locking directories";
    fprintf(file, "%s\n", msg);
    fclose(file);

    int result = chmod("/workspaces/SysSoftwareAssignment1/-Upload", S_IRUSR | S_IRGRP | S_IROTH);
    if (result != 0) {
        perror("chmod");
    }
}
