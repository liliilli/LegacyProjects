#include <stdio.h>
#include <stdlib.h>

/* ADD any function if necessary */

void print_map_line(int a1, int a2, int n_digits)
{
  /* FILL */
}

int main()
{
  int n, i;
  int *A1, *A2;

  scanf("%d",&n);
  if ( n <= 0 ) {
    fprintf(stderr,"Error: n = %d <= 0\n",n);
    exit(0);
  }
  A1 = (int*)malloc(sizeof(int)*n);
  A2 = (int*)malloc(sizeof(int)*n);

  for (i=0; i<n; i++) scanf("%d",A1+i);
  for (i=0; i<n; i++) scanf("%d",A2+i);

  for (i=0; i<n; i++) {
    printf("|");
    print_map_line(A1[i], A2[i], n);
    printf("|\n");
  }

  free(A2);
  free(A1);
}
