#include <stdio.h>

int main(int argc, char* argv[]) {
  // // for debug output
  // printf("argc = %d\n", argc);
  // for(int i=0; i<argc; i++) {
  //   printf("argv[%d]: %s\n", i, argv[i]);
  // }

  // count length of string1
  int len1=0;
  char* ptr1 = argv[1];
  for(; *ptr1 != '\0'; len1++, ptr1++) {};
  // count length of string2
  int len2=0;
  char* ptr2 = argv[2];
  for(; *ptr2 != '\0'; len2++, ptr2++) {};


  // printf("len1: %d\n", len1);
  // printf("len2: %d\n", len2);

  // printf("=======================\n");
  //compare elements
  int k, j;
  for(int i=0; i<len1; i++) {
    k=i;
    j=0;
    // printf("--------new iteration-------\n");
    // printf("argv[1][%d]: %c\n", i, *(argv[1]+i));
    while(*(argv[1]+k) == *(argv[2]+j)) {
      j++;
      k++;
      if(j==len2) {
        printf("true\n");
        i=len1;
        break;
      }else if(k==len1) {
        printf("false\n");
        break;
      }
    }
    if((*(argv[1]+k) != *(argv[2]+j)) && i==len1-1) {
      printf("false\n");
    }
  }
  return 0;
}