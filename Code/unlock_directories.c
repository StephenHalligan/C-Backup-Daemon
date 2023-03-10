
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <syslog.h>
#include <stdio.h>

void unlock_directories() {

    FILE *file;
    file = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "ab");
    char *msg = "Backup dashboard > Dashboard backup complete";
    fprintf(file, "%s\n", msg);

    int result = chmod("/workspaces/SysSoftwareAssignment1/-Upload", S_IRWXU | S_IRWXG | S_IRWXO);
    if (result != 0) {
        perror("chmod");
    }

    int result2 = chmod("/workspaces/SysSoftwareAssignment1/-Reporting", S_IRWXU | S_IRWXG | S_IRWXO);
    if (result2 != 0) {
        perror("chmod");
    }

    msg =  "Unlock directories >  Directories successfully unlocked";
    fprintf(file, "%s\n", msg);
    fclose(file);


}
        