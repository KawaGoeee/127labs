#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[]) {
  char word[128]={'\0'};
  char ch;

  while((ch=getchar())!=EOF) {
    int index=0;

    // get chunk of word and put in array:word
    while( (ch=='\'') || (ch>='A' && ch<='Z') || (ch>='a' && ch<='z') ) {
      word[index]=ch;
      ch = getchar();
      index++;
    }
    // compare array word and words from input
    for(int i=1; i<argc; i++) {
      if(strcmp(argv[i], word)==0) {
        strcpy(word, "CENSORED");
      }
    }

    printf("%s", word);
    if(ch!=EOF) {
      printf("%c", ch);
    }
    // clear array for next iteration
    memset(word, '\0', sizeof(char)*128);

  }
  // printf("\n");
  return 0;
}