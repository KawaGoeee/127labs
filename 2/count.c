#include <stdio.h>

// #6 count.c
int main(void) {
  unsigned long int charcount=0, wordcount=0, linecount=0;
  int ch=0;
  do {
    ch = getchar();
    printf("ch(%d):%c\n", ch, ch);
    if( !(ch==39 || (ch>=65 && ch<=90) || (ch>=97 && ch<=122)) ) {
      if(ch=='\n') {
        linecount++;
      }
      wordcount++;
    }
    charcount++;
  }while(ch!=EOF);

  // reaching EOF
  printf("%lu %lu %lu\n", charcount, wordcount, linecount);
  return 0;
}
// getcharの戻り値がintである理由https://okwave.jp/qa/q5326377.html