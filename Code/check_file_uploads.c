#include <unistd.h>
#include <syslog.h>
#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>


void check_file_uploads(void) {

   FILE *file;
   file = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "ab");

   bool dept1 = false;

   char folder_path[] = "/workspaces/SysSoftwareAssignment1/-Upload/Department 1";
   DIR *directory = opendir(folder_path);
   struct dirent *entry;

   while ((entry = readdir(directory)) != NULL) {
      if (strstr(entry->d_name, ".xml") != NULL) {
         dept1 = true;
         break;
      }
   }
   closedir(directory);


   if (dept1) {
      char *msg = "DEPARTMENT 1 XML FILE UPLOADED";
      fprintf(file, "%s\n", msg);
    }
    else {
      char *msg = "***** NOTICE *****\nDEPARTMENT 1 XML FILE NOT UPLOADED\n";
      fprintf(file, "\n%s", msg);
   }

   fclose(file);

}

      