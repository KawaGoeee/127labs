#include <stdio.h>


int main(void) {
  unsigned long int charcount=0, wordcount=0, linecount=0;

  char ch=0;
  int contiguous=0;

  while((ch = getchar())!=EOF) {

    charcount++;

    if(contiguous==0) {
      if( (ch=='\'') || (ch>='A' && ch<='Z') || (ch>='a' && ch<='z') ) {
        wordcount++;
        contiguous=1;
      }
    }else {
      if( !((ch=='\'') || (ch>='A' && ch<='Z') || (ch>='a' && ch<='z')) ) {
        contiguous=0;
      }
    }

    if(ch=='\n') {
      linecount++;
    }

  }

  // reaching EOF
  printf("%lu %lu %lu\n", charcount, wordcount, linecount);
  return 0;
}

// getcharの戻り値がintである理由https://okwave.jp/qa/q5326377.html

