#include <stdio.h>

int biggerInt(int a, int b) { return a > b ? a : b; }

int main(void) {
  int nums[80];
  int num=0, width=0, max=0;
  
  // store integers in nums
  while(scanf("%d", &num) != EOF) {
    nums[width] = num;
    width++;
  }

  // find max value in nums[]
  for(int i=0; i<width; i++) {
    max = biggerInt(max, nums[i]);
  }

  // print
  for(int i=max; i>0; i--) {
    for(int j=0; j<width; j++) {

      if(i>nums[j]) {
        printf(" ");
      }else {
        printf("#");
      }
    }
    printf("\n");
  }
  return 0;
}
