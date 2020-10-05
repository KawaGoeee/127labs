#include <stdio.h>

// #6 count.c
int main(void) {
  unsigned long int charcount=0, wordcount=0, linecount=0;
  char ch=0;
  // set 1 if ch is alphabet(a-z, A-Z), else 0
  int contiguous=1;

  do {
    ch = getchar();
    // printf("ch(%d):%c\n", ch, ch);

    if(ch=='\n') {
      linecount++;
      contiguous=1;

    }else if( (ch=='\'') || (ch>='A' && ch<='Z') || (ch>='a' && ch<='z') ) {

      // increment when beginning of word appears: contiguous==1
      if(contiguous==1)	{
        wordcount++;
        contiguous=0;
      }

    }else {
      contiguous=0;
    }

    charcount++;
  }while(ch!=EOF);

  // reaching EOF
  printf("%lu %lu %lu\n", charcount, wordcount, linecount);
  return 0;
}
// getcharの戻り値がintである理由https://okwave.jp/qa/q5326377.html
