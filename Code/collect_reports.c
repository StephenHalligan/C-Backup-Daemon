#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

void collect_reports(void) {

    pid_t pid = fork();

    if (pid == 0) {

        // Child process
        mkdir("/workspaces/SysSoftwareAssignment1/-Reporting/Department 1", 0777);
        mkdir("/workspaces/SysSoftwareAssignment1/-Reporting/Department 2", 0777);
        mkdir("/workspaces/SysSoftwareAssignment1/-Reporting/Department 3", 0777);
        mkdir("/workspaces/SysSoftwareAssignment1/-Reporting/Department 4", 0777);

        execlp("cp", "cp", "/workspaces/SysSoftwareAssignment1/-Upload/Department 1/report.xml", "/workspaces/SysSoftwareAssignment1/-Reporting/Department 1", NULL);
        execlp("cp", "cp", "/workspaces/SysSoftwareAssignment1/-Upload/Department 2/report.xml", "/workspaces/SysSoftwareAssignment1/-Reporting/Department 2", NULL);
        execlp("cp", "cp", "/workspaces/SysSoftwareAssignment1/-Upload/Department 3/report.xml", "/workspaces/SysSoftwareAssignment1/-Reporting/Department 3", NULL);
        execlp("cp", "cp", "/workspaces/SysSoftwareAssignment1/-Upload/Department 4/report.xml", "/workspaces/SysSoftwareAssignment1/-Reporting/Department 4", NULL);

        FILE *file;
        file = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "ab");
        char *msg = "Collect reports > Reports collected and moved to Reporting directory";
        fprintf(file, "\n%s\n", msg);
        fclose(file);

        exit(0);
    }

    else if (pid > 0) {
        // Parent process
        wait(NULL);
        printf("XML files copied successfully!\n");
    }

    else {
        // Error creating child process
        printf("Error creating child process!\n");
        exit(1);
    }

}