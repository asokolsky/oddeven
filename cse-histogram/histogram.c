#include <stdio.h>

/**
 * From requirements
 */
#define BINS 16
#define INITIAL_BIN_SIZE 1


typedef struct {
   int min;     // bottom of the bin range, including
   int max;     // top of the bin range, not-including
   int counter; // # of samples in the bin
} bin_t;

/**
 *  Error codes returned by different functions
 */
#define EC_SUCCESS 0
// end of file
#define EC_EOF     1
//
#define EC_TOO_BIG 2

/**
 * reset counters, init all the fields
 */
void bins_initialize(bin_t bins[]) {
   for(int i=0; i < BINS; i++) {
      bins[i].min = i * INITIAL_BIN_SIZE;
      bins[i].max = bins[i].min + INITIAL_BIN_SIZE;
      bins[i].counter = 0;
   }
}

/**
 * Account for new input by incrementing appropriate counter
 * Returns EC_SUCCESS or EC_TOO_BIG is the input does not fit in.
 */
int bins_add_input(bin_t bins[], int inp) {
   for(int i=0; i < BINS; i++) {
      if(inp >= bins[i].max)
         continue;
      // found my bin!
      bins[i].counter++;
      return EC_SUCCESS;
   }
   return EC_TOO_BIG;
}

/**
 * Double the range handled by bins
 */
void bins_shrink(bin_t bins[]) {
   for(int i=0; i < BINS/2; i++) {
      int iSource = i*2;
      bins[i].min = bins[iSource].min;
      bins[i].max = bins[iSource+1].max;
      bins[i].counter = bins[iSource].counter + bins[iSource+1].counter;
   }
   int iBinSize = bins[0].max - bins[0].min;
   // need to clear the top half of the bins
   for(int j = BINS/2; j < BINS; j++) {
      bins[j].min = j * iBinSize;
      bins[j].max = bins[j].min + iBinSize;
      bins[j].counter = 0;
   }
}

/**
 * print a short bins summary
 */
void bins_summary(bin_t bins[])
{
   int iBinSize = bins[0].max - bins[0].min;
   printf("%d bins of size %d for range [%d, %d)\n",
      BINS, iBinSize, bins[0].min, bins[BINS-1].max);
}

/**
 * print a histogram
 */
void bins_histogram(bin_t bins[]) {
   for(int i=0; i < BINS; i++) {
      printf("[%3d:%3d] ", bins[i].min, bins[i].max-1);
      for(int j = 0; j< bins[i].counter; j++)
         printf("*");
      printf("\n");
   }
}

/**
 * Read an integer from stdin.
 * Returns error code EC_xxx
 * Stores input into *res
 */
int read_int(int *res)
{
   // initialize the result
   int iRes = 0;
   *res = 0;
   iRes = scanf("%d", res);
   //printf("iRes=%d\n", iRes);
   if(iRes == 1)
      return EC_SUCCESS;

   return EC_EOF;
}

int main()
{
   bin_t bins[BINS];
   bins_initialize(bins);
   bins_summary(bins);

   for(;;) {
      int i = 0;
      if(read_int(&i) != EC_SUCCESS)
         break;
      if(i < 0)
         continue;
      if(bins_add_input(bins, i) == EC_SUCCESS)
         continue;
      for(;;) {
         bins_shrink(bins);
         bins_summary(bins);
         if(bins_add_input(bins, i) == EC_SUCCESS)
            break;
      }
   }
   bins_histogram(bins);
   return 0;
}
