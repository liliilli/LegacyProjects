#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convTimeHourMin( const char time[] )
  // converts HH:MM into numbers, saves them into hours and minutes
  // and returns hours*60+minutes
{
  int hours, minutes;
  hours = (time[0]-'0')*10+(time[1]-'0');
  minutes = (time[3]-'0')*10+(time[4]-'0');

  if ( hours > 23 || minutes > 59 ) {
    fprintf(stderr,"wrong time format: %s\n",time);
    return 0;
  }
  else return hours*60+minutes;
}

/* ADD any function if necessary */

int main()
{
  int i;
  int n, t, m, numTimeTables;
  char time_s[1024];	// just assign enough text storage: 1024 bytes
  int timeTableMin[2000];
  // maximum number of time tables: 2000

  scanf("%d",&n);
  scanf("%d",&t);
  scanf("%d",&m);
  scanf("%d",&numTimeTables);
  for (i=0; i<numTimeTables; i++) {
    scanf("%s",time_s);
    timeTableMin[i] = convTimeHourMin(time_s);
  }

  printf("%d ",n);
  printf("%d ",t);
  printf("%d ",m);
  printf("%d\n",numTimeTables);
  for (i=0; i<numTimeTables; i++) {
    printf("%d:%d ",timeTableMin[i]/60,timeTableMin[i]%60);
  }
  printf("\n");

  /* FILL - do necessary actions */

}
