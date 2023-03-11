/*
 *
 * At 11:30 pm , there will be a check for the xml files that have been uploaded or 
 * files that have not been upladed
 *
 * At 1:00 am, the xml reports will be backed up from xml_upload_directory to 
 * dashboard_directory
 *
 * Directories are locked during transfer / backup
 * 
 * Kill -2 signal will enable the daemon to transfer / backup at any given time
 *
 */


// Orphan Example
// The child process is adopted by init process, when parent process dies.
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
#include "daemon_task.h"
#include <signal.h>
#include <string.h>
#include <fcntl.h>

void backup(int sig) {

    printf("Manual backup request received.\n");
    FILE *file;
    file = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "ab");
    char *msg = "\n***** PERFORMING MANUAL BACKUP *****\n";
    fprintf(file, "%s\n", msg);
    fclose(file);

    lock_directories();
    collect_reports();  
    backup_dashboard();
    sleep(30);
    unlock_directories();
    generate_reports();
}

int main() {

    FILE *file;
    file = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "w");
    char *msg = "";
    fprintf(file, "%s", msg);
    fclose(file);

    time_t now;
    struct tm backup_time;
    time(&now);  /* get current time; same as: now = time(NULL)  */
    backup_time = *localtime(&now);
    backup_time.tm_hour = 17; 
    backup_time.tm_min = 56; 
    backup_time.tm_sec = 15;

    // Implementation for Singleton Pattern if desired (Only one instance running)

    // Create a child process      
    int pid = fork();
 
    if (pid > 0) {
        // if PID > 0 :: this is the parent
        // this process performs printf and finishes
        //sleep(10);  // uncomment to wait 10 seconds before process ends
        exit(EXIT_SUCCESS);
    }
    
    else if (pid == 0) {
        // Step 1: Create the orphan process
       
        // Step 2: Elevate the orphan process to session leader, to loose controlling TTY
        // This command runs the process in a new session
        if (setsid() < 0) { exit(EXIT_FAILURE); }

        // We could fork here again , just to guarantee that the process is not a session leader
        int pid = fork();
        if (pid > 0) {
            exit(EXIT_SUCCESS);
        } 
        
        else {

            // Call umask() to set the file mode creation mask to 0
            umask(0);

            // Change the current working dir to root.
            if (chdir("/") < 0 ) { exit(EXIT_FAILURE); }

            // Close all open file descriptors
            int x;
            for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
            {
                close (x);
            } 

            // Signal Handler goes here

            // Orphan Logic goes here!! 
            // Keep process running with infinite loop
            // When the parent finishes after 10 seconds, 
            // the getppid() will return 1 as the parent (init process)
          
            struct tm check_uploads_time;
            time(&now);  /* get current time; same as: now = time(NULL)  */
            check_uploads_time = *localtime(&now);
            check_uploads_time.tm_hour = 20; 
            check_uploads_time.tm_min = 44;
            check_uploads_time.tm_sec = 0;

            close(STDIN_FILENO);
            close(STDOUT_FILENO);
            close(STDERR_FILENO);

            const char *filename1;
            const char *filename2;
            const char *filename3;
            const char *filename4;

            filename1 = "workspaces/SysSoftwareAssignment1/-Upload/Distribution/report.xml";
            filename2 = "workspaces/SysSoftwareAssignment1/-Upload/Manufacturing/report.xml";
            filename3 = "workspaces/SysSoftwareAssignment1/-Upload/Sales/report.xml";
            filename4 = "workspaces/SysSoftwareAssignment1/-Upload/Warehouse/report.xml";

            struct stat st1;
            struct stat st2;
            struct stat st3;
            struct stat st4;

            FILE *file1;
            FILE *file2;
            FILE *file3;
            FILE *file4;

            time_t last_modification_time1 = st1.st_mtime;
            time_t last_modification_time2 = st2.st_mtime;
            time_t last_modification_time3 = st3.st_mtime;
            time_t last_modification_time4 = st4.st_mtime;

        while(1) {

            char date[128];


            //Dept 1
            file1 = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "ab");
            if (stat(filename1, &st1) == -1) {
                perror("stat");
                exit(1);
            }
            if (st1.st_mtime != last_modification_time1) {
                strftime(date, sizeof(date), "%a %b %d %T %Y", localtime(&now));
                fprintf(file1, "File integrity > The 'Distribution' report file was modified at %s\n", date);
                fclose(file1);
                last_modification_time1 = st1.st_mtime;
            }

            //Dept 2
            file2 = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "ab");
            if (stat(filename2, &st2) == -1) {
                perror("stat");
                exit(1);
            }
            if (st2.st_mtime != last_modification_time2) {
                strftime(date, sizeof(date), "%a %b %d %T %Y", localtime(&now));
                fprintf(file2, "File integrity > The 'Manufacturing' report file was modified at %s\n", date);
                fclose(file2);
                last_modification_time2 = st2.st_mtime;
            }

            //Dept 3
            file3 = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "ab");
            if (stat(filename3, &st3) == -1) {
                perror("stat");
                exit(1);
            }
            if (st3.st_mtime != last_modification_time3) {
                strftime(date, sizeof(date), "%a %b %d %T %Y", localtime(&now));
                fprintf(file3, "File integrity > The 'Sales' report file was modified at %s\n", date);
                fclose(file3);
                last_modification_time3 = st3.st_mtime;
            }

            //Dept 4
            file4 = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "ab");
            if (stat(filename4, &st4) == -1) {
                perror("stat");
                exit(1);
            }
            if (st4.st_mtime != last_modification_time4) {
                strftime(date, sizeof(date), "%a %b %d %T %Y", localtime(&now));
                fprintf(file4, "File integrity > The 'Warehouse' report file was modified at %s\n", date);
                fclose(file4);
                last_modification_time4 = st4.st_mtime;
            }	

            sleep(1);

            if(signal(SIGINT, sig_handler) == SIG_ERR) {
                syslog(LOG_ERR, "ERROR: daemon.c : SIG_ERR RECEIVED");
            } 

            signal(SIGINT, backup);
		
            //countdown to 23:30
            time(&now);
            double seconds_to_files_check = difftime(now,mktime(&check_uploads_time));
            if(seconds_to_files_check == 0) {

                FILE *file;
                file = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "ab");
                strftime(date, sizeof(date), "%a %b %d %T %Y", localtime(&now));
                char *msg = "***** CHECKING REPORTS *****\n";
                fprintf(file, "\n%s: %s\n", date, msg);
                fclose(file);

                check_file_uploads();

                //change to tommorow's day
                update_timer(&check_uploads_time);
            }

            //countdown to 1:00
            time(&now);
            double seconds_to_transfer = difftime(now, mktime(&backup_time));

            if(seconds_to_transfer == 0) {

                char date[128];
                FILE *file;
                file = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "ab");
                strftime(date, sizeof(date), "%a %b %d %T %Y", localtime(&now));
                char *msg = "***** PERFORMING BACKUP *****\n";
                fprintf(file, "\n%s: %s\n", date, msg);
                fclose(file);

                lock_directories();
                collect_reports();  
                backup_dashboard();
                sleep(30);
                unlock_directories();
                generate_reports();
                
                //after actions are finished, start counting to next day
                update_timer(&backup_time);
		    }	
	    }
	}	

       return 0;

    }
}