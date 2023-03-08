#include <unistd.h>
#include <syslog.h>
#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>

// This is not the most efficient way of checking if subfolders contain files of a certain type, however it is the easiest way I could find using C.

void check_file_uploads(void) {

   FILE *file;
   file = fopen("/workspaces/SysSoftwareAssignment1/Logs/output.txt", "ab");

   bool dept1 = false;
   bool dept2 = false;
   bool dept3 = false;
   bool dept4 = false;

   char *msg;

   char folder_path[] = "/workspaces/SysSoftwareAssignment1/-Upload/Department 1";
   DIR *directory = opendir(folder_path);
   struct dirent *entry;

   char folder_path2[] = "/workspaces/SysSoftwareAssignment1/-Upload/Department 2";
   directory = opendir(folder_path2);
   struct dirent *entry2;

   char folder_path3[] = "/workspaces/SysSoftwareAssignment1/-Upload/Department 3";
   directory = opendir(folder_path3);
   struct dirent *entry3;

   char folder_path4[] = "/workspaces/SysSoftwareAssignment1/-Upload/Department 4";
   directory = opendir(folder_path4);
   struct dirent *entry4;


   //Department 1 upload check   

   while ((entry = readdir(directory)) != NULL) {
      if (strstr(entry->d_name, ".xml") != NULL) {
         dept1 = true;
         break;
      }
   }
   closedir(directory);

   if (dept1) {
      msg = "Check file uploads > DEPARTMENT 1 XML FILE UPLOADED";
      fprintf(file, "%s\n", msg);
    }
    else {
      msg = "***** ALERT *****\nCheck file uploads > DEPARTMENT 1 XML FILE NOT UPLOADED\n";
      fprintf(file, "\n%s", msg);
   }


   //Department 2 upload check

   while ((entry2 = readdir(directory)) != NULL) {
      if (strstr(entry2->d_name, ".xml") != NULL) {
         dept2 = true;
         break;
      }
   }
   closedir(directory);
   if (dept2) {
      msg = "Check file uploads > DEPARTMENT 2 XML FILE UPLOADED";
      fprintf(file, "%s\n", msg);
    }
    else {
      msg = "***** ALERT *****\nCheck file uploads > DEPARTMENT 2 XML FILE NOT UPLOADED\n";
      fprintf(file, "\n%s", msg);
   }


   //Department 3 upload check

   while ((entry3 = readdir(directory)) != NULL) {
      if (strstr(entry3->d_name, ".xml") != NULL) {
         dept3 = true;
         break;
      }
   }
   closedir(directory);
   if (dept3) {
      msg = "Check file uploads > DEPARTMENT 3 XML FILE UPLOADED";
      fprintf(file, "%s\n", msg);
    }
    else {
      msg = "***** NOTICE *****\nCheck file uploads > DEPARTMENT 3 XML FILE NOT UPLOADED\n";
      fprintf(file, "\n%s", msg);
   }


   //Department 4 upload check

   while ((entry4 = readdir(directory)) != NULL) {
      if (strstr(entry4->d_name, ".xml") != NULL) {
         dept4 = true;
         break;
      }
   }
   closedir(directory);
   if (dept4) {
      msg = "Check file uploads > DEPARTMENT 4 XML FILE UPLOADED";
      fprintf(file, "%s\n", msg);
    }
    else {
      msg = "***** ALERT *****\nCheck file uploads > DEPARTMENT 4 XML FILE NOT UPLOADED\n";
      fprintf(file, "\n%s", msg);
   }

   fclose(file);

}

      