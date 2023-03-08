#include <syslog.h>
#include <stdio.h>
#include <time.h>
#include <stdio.h>

void update_timer(struct tm *due_date) {
	printf("CURRENT DAY IS %d; CHANGING TIMER TO TOMMOROW'S DAY", due_date -> tm_mday);
	due_date -> tm_mday += 1;
  	mktime(due_date);	
	printf("TIMER UPDATED, DUE NEXT DAY, %d", due_date -> tm_mday);
}