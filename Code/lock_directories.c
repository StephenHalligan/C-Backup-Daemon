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
    char *msg = "Lock directories > Directories successfully locked";
    fprintf(file, "%s\n", msg);
    fclose(file);

    int result = chmod("/workspaces/SysSoftwareAssignment1/-Upload", S_IRUSR | S_IRGRP | S_IROTH);
    if (result != 0) {
        perror("chmod");
    }

    int result2 = chmod("/workspaces/SysSoftwareAssignment1/-Reporting", S_IRUSR | S_IRGRP | S_IROTH);
    if (result2 != 0) {
        perror("chmod");
    }
}
