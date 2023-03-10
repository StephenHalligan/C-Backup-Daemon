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
    char path[200];

    FILE *src_file;
    FILE *dst_file;

    int ch;

    if (pid == 0) {

        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Upload/Distribution/report.xml");
        src_file = fopen(path, "rb");
        dst_file = fopen("/workspaces/SysSoftwareAssignment1/-Reporting/Distribution/report.xml", "wb");
        mkdir(path, 0777);
        while ((ch = fgetc(src_file)) != EOF) {
            fputc(ch, dst_file);
        }
        fclose(src_file);
        fclose(dst_file);


        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Upload/Manufacturing/report.xml");
        src_file = fopen(path, "rb");
        dst_file = fopen("/workspaces/SysSoftwareAssignment1/-Reporting/Manufacturing/report.xml", "wb");
        mkdir(path, 0777);
        while ((ch = fgetc(src_file)) != EOF) {
            fputc(ch, dst_file);
        }
        fclose(src_file);
        fclose(dst_file);


        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Upload/Sales/report.xml");
        src_file = fopen(path, "rb");
        dst_file = fopen("/workspaces/SysSoftwareAssignment1/-Reporting/Sales/report.xml", "wb");
        mkdir(path, 0777);
        while ((ch = fgetc(src_file)) != EOF) {
            fputc(ch, dst_file);
        }
        fclose(src_file);
        fclose(dst_file);


        sprintf(path, "/workspaces/SysSoftwareAssignment1/-Upload/Warehouse/report.xml");
        src_file = fopen(path, "rb");
        dst_file = fopen("/workspaces/SysSoftwareAssignment1/-Reporting/Warehouse/report.xml", "wb");
        mkdir(path, 0777);
        while ((ch = fgetc(src_file)) != EOF) {
            fputc(ch, dst_file);
        }
        fclose(src_file);
        fclose(dst_file);

        exit(0);
    }

    else if (pid > 0) {
        // Parent process
        wait(NULL);
        printf("XML files copied successfully!\n");
        FILE *file;
        file = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "ab");
        char *msg = "Collect reports > Reports collected and moved to Reporting directory";
        fprintf(file, "%s\n", msg);
        fclose(file);
    }

    else {
        // Error creating child process
        printf("Error creating child process!\n");
        exit(1);
    }

}