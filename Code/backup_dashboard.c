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

    FILE *file;
    file = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "ab");
    char *msg = "Backup dashboard > Dashboard backup starting";
    fprintf(file, "%s\n", msg);
    fclose(file);

    pid_t pid = fork();

    char path[100];

    FILE *src_file;
    FILE *dst_file;

    int ch;

    if (pid == 0)
    {
        sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Backup/%s/", date);
        mkdir(path, 0700);


        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Backup/%s/Distribution", date);
        mkdir(path, 0777);
        src_file = fopen("workspaces/SysSoftwareAssignment1/-Reporting/Distribution/report.xml", "rb");
        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Backup/%s/Distribution/report.xml", date);
        dst_file = fopen(path, "wb");
        while ((ch = fgetc(src_file)) != EOF) {
            fputc(ch, dst_file);
        }
        fclose(src_file);
        fclose(dst_file);

        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Backup/%s/Manufacturing", date);
        mkdir(path, 0777);
        src_file = fopen("workspaces/SysSoftwareAssignment1/-Reporting/Manufacturing/report.xml", "rb");
        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Backup/%s/Manufacturing/report.xml", date);
        dst_file = fopen(path, "wb");
        while ((ch = fgetc(src_file)) != EOF) {
            fputc(ch, dst_file);
        }
        fclose(src_file);
        fclose(dst_file);

        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Backup/%s/Sales", date);
        mkdir(path, 0777);
        src_file = fopen("workspaces/SysSoftwareAssignment1/-Reporting/Sales/report.xml", "rb");
        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Backup/%s/Sales/report.xml", date);
        dst_file = fopen(path, "wb");
        while ((ch = fgetc(src_file)) != EOF) {
            fputc(ch, dst_file);
        }
        fclose(src_file);
        fclose(dst_file);

        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Backup/%s/Warehouse", date);
        mkdir(path, 0777);
        src_file = fopen("workspaces/SysSoftwareAssignment1/-Reporting/Warehouse/report.xml", "rb");
        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Backup/%s/Warehouse/report.xml", date);
        dst_file = fopen(path, "wb");
        while ((ch = fgetc(src_file)) != EOF) {
            fputc(ch, dst_file);
        }
        fclose(src_file);
        fclose(dst_file);

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