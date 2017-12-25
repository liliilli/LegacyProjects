#include <stdio.h>
#include <stdlib.h>

/* ADD any function if necessary */

int convert_dartResult(const char dartResult[])
{
  /* FILL */
  return 0;
}

int main()
{
  char dartResult[1024];
  int answer;

  scanf("%s",dartResult);
  answer = convert_dartResult(dartResult);
  printf("%d", answer);
}
