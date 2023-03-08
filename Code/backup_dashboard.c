#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

void backup_dashboard(void) {

    time_t now;
    time(&now);  /* get current time; same as: now = time(NULL)  */
    struct tm tm = *localtime(&now);
    char date[20];
    sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    pid_t pid = fork();

    char path[100];

    if (pid == 0)
    {
        sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Backup/%s", date);
        mkdir(path, 0777);
        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Backup/%s/Department 1", date);
        mkdir(path, 0777);
        execlp("cp", "cp", "/workspaces/SysSoftwareAssignment1/-Reporting/Department 1/report.xml", path, NULL);
        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Backup/%s/Department 2", date);
        mkdir(path, 0777);
        execlp("cp", "cp", "/workspaces/SysSoftwareAssignment1/-Reporting/Department 2/report.xml", path, NULL);
        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Backup/%s/Department 3", date);
        mkdir(path, 0777);
        execlp("cp", "cp", "/workspaces/SysSoftwareAssignment1/-Reporting/Department 3/report.xml", path, NULL);
        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Backup/%s/Department 4", date);
        mkdir(path, 0777);
        execlp("cp", "cp", "/workspaces/SysSoftwareAssignment1/-Reporting/Department 4/report.xml", path, NULL);
        exit(0);
    }
    else if (pid > 0)
    {
        // Parent process
        wait(NULL);
        printf("XML file copied successfully!\n");
    }
    else
    {
        // Error creating child process
        printf("Error creating child process!\n");
        exit(1);
    }
    
}
