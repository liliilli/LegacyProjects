#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MIN(__A__, __B__) (__A__ > __B__) ? __B__ : __A__
#define ARR_SIZE(__A__) sizeof(__A__) / sizeof(__A__[0])
#define SWAP(__TYPE__, __A__, __B__) { \
        __TYPE__ temp = *__A__; *__A__ = *__B__; *__B__ = temp; \
    }
#define PRINT(__STRING__, __VALUE__) \
    printf("%s : %d\n", __STRING__, __VALUE__)
#define TRAVELSE(__N__, __A__, __B__) \
    for (int i = __A__; i < __B__; ++i) printf("%d ", __N__[i]); \
    printf("\n");

/////////////////////////////////////////////
// Any subfunctions can be defined
/////////////////////////////////////////////


/////////////////////////////////////////////
// INSERTION SORT
void insertionsort(int A[], int N) {
  for (int i = 1; i < N; ++i) {
    for (int j = i - 1; j >= 0; --j) {
      if (A[j + 1] < A[j]) {
        SWAP(int, &A[j], &A[j + 1]);
      }
      else break;
    }
  }
}
/////////////////////////////////////////////

/////////////////////////////////////////////
// MERGE SORT
void merge_sort(int array[], int s, int e) {
  if (s == e) return;

  // Devide
  int sep = (s + e) >> 1;
  merge_sort(array, s, sep);
  merge_sort(array, sep + 1, e);
  int buf[e - s + 1]; 

  // Conquer
  int i = 0;
  int l = s, r = sep + 1, l_lim = sep + 1, r_lim = e + 1;
  while ((l ^ l_lim) && (r ^ r_lim)) {
    if (array[l] > array[r]) { buf[i++] = array[r++]; }
    else { buf[i++] = array[l++]; }
  }

  while (l ^ l_lim) { buf[i] = array[l++]; ++i; }
  while (r ^ r_lim) { buf[i] = array[r++]; ++i; }

  i = s;
  while (i <= e) { array[i] = buf[i - s]; ++i; }
}

void mergesort(int A[], int buf[], int N) {
  merge_sort(A, 0, N - 1); // look forward to Tailing recursion optimization 
}
/////////////////////////////////////////////


/////////////////////////////////////////////
// HEAP SORT
void heapify(int A[], int i, int size) {
  int l = (i << 1) + 1;
  int r = l + 1;

  int i_lst = i;
  if (l < size && A[l] > A[i]) i_lst = l;
  if (r < size && A[r] > A[i_lst]) i_lst = r;

  if (i_lst != i) {
    SWAP(int, &A[i], &A[i_lst]);
    heapify(A, i_lst, size);
  }
}

void build_heap(int A[], int s, int e) {
  int size = e - s + 1;
  for (int i = size >> 1; i >= 0; --i) {
    heapify(A, i, size);
  }
}

void heapsort(int A[], int N) {
  build_heap(A, 0, N - 1);

  for (int i = N - 1; i > 0; --i) {
      SWAP(int, &A[0], &A[i]);
      --N;
      heapify(A, 0, N - 1);
  }
}
/////////////////////////////////////////////

// auto parent = (present - 1) >> 1;
// auto left = (present << 1) + 1;
// auto right = left + 1;

/////////////////////////////////////////////
// QUICK SORT
int get_partition(int array[], int i_start, int i_end) {
  int i_pre = i_start - 1;
  for (int i = i_start; i < i_end; ++i) {
    if (array[i] < array[i_end]) {
      i_pre += 1;
      SWAP(int, &array[i_pre], &array[i]);
    }
  }

  i_pre += 1;
  SWAP(int, &array[i_pre], &array[i_end]);
  return i_pre;
}

void quick_sort(int array[], int i_start, int i_end) {
  if (i_start < i_end) { // Randomization for worst case input array.
    int r_index = (rand() % (i_end - i_start + 1)) + i_start;
    SWAP(int, &array[r_index], &array[i_end]);

    int sep = get_partition(array, i_start, i_end);
    quick_sort(array, i_start, sep - 1);
    quick_sort(array, sep + 1, i_end);
  }
}

void quicksort(int A[], int N) {
  srand(time(NULL));
  quick_sort(A, 0, N - 1); // 꼬리재귀가 되기를...
}
/////////////////////////////////////////////

int main(int argc, char *argv[])
{
  int i, N;
  int *X, *buf;
  FILE *fp;

  // check input file
  if ( argc != 4 ) {
    fprintf(stderr,"usage: %s [-i|-m|-h|-q] <input_file> <out_file>\n"
	"  *argument 1:\n"
	"    -i: insertion sort\n"
	"    -m: merge sort\n"
	"    -i: heap sort\n"
	"    -i: quick sort\n"
	"  *argument 2, <input_file>, is a text file\n"
	"   starting with #numbers, followed by integer numbers to sort\n"
	"    Example) \n"
	"       10\n"
	"       16 9 19 6 19 18 16 12 8 8 \n"
	"  *argument 3, <out_file>, is a sorting output with the same\n"
	"   structure as the input file, except the numbers are sorted\n"
	"    Example) \n"
	"       10\n"
	"       6 8 8 9 12 16 16 18 19 19 \n"
	, argv[0]);
    exit(0);
  }

  // load input
  if ( !(fp = fopen(argv[2],"rt")) ) {
    fprintf(stderr, "cannot open file %s for input\n",argv[2]);
    exit(0);
  }
  fscanf(fp,"%d",&N);
  X = (int*)malloc(sizeof(int)*N);	// input, unsorted, and to be sorted
  buf = (int*)malloc(sizeof(int)*N);	// for merge sort
  for (i=0; i<N; i++) {
    if ( fscanf(fp,"%d",X+i) != 1 ) {
      fprintf(stderr, "cannot read integer from %s\n",argv[2]);
      exit(0);
    }
  }
  fclose(fp);

  // sort function calls
  if ( strcmp(argv[1], "-i" ) == 0 ) {
    insertionsort(X,N);
  }
  else if ( strcmp(argv[1], "-m" ) == 0 ) {
    mergesort(X,buf,N);
  }
  else if ( strcmp(argv[1], "-h" ) == 0 ) {
    heapsort(X,N);
  }
  else if ( strcmp(argv[1], "-q" ) == 0 ) {
    //quicksort(X,0,N-1);
    quicksort(X,N);
  }
  else {
    fprintf(stderr, "unknown sorting method flag: %s\n",argv[1]);
    exit(0);
  }

  // file output
  if ( !(fp = fopen(argv[3],"wt")) ) {
    fprintf(stderr, "cannot open file %s for output\n",argv[3]);
    exit(0);
  }
  fprintf(fp,"%d\n",N);
  for (i=0; i<N; i++) {
    fprintf(fp,"%d ",X[i]);
    if ( (i+1)%10 == 0 ) fprintf(fp,"\n");	// line change every 10 lines
  }
  fprintf(fp,"\n");
  fclose(fp);

  // free memory
  free(X);
  free(buf);

  return 0;
}
