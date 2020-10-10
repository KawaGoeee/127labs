#include <stdio.h>
#include <ctype.h>

int main(void) {
  int ch, total=0;
  int alpha[26]={0};
  double freq=0.0;

  while((ch=getchar())!=EOF) {
    if(isalpha(ch)){
      total++;
      ch = tolower(ch);
      alpha[ch-97]++;
    }
  }

  for(int i=0; i<26; i++) {
    int letter = i+97;

    if(alpha[i]!=0) {
      // printf("alpha[%d]:%d ",i,alpha[i]);
      // printf("total:%d ",total);

      freq = (double)alpha[i] / (double)total;
      printf( "%c %.4f\n", letter, freq);
    }
  }
  return 0;
}