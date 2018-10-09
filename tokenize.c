#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "classes.h"

char states[25][25] = {0};
int initial[25][25] = {0};
int count = 0;
int width = 0;
int accept = 0;
int start = 0;
int statesv = 0;

void  matrix(int count, int width){
  // Matrix to be rewritten in solve
  for(int i = 0; i < count; i++)
    for(int j = 0; j < width; j++){
      if(states[i][j] == '1')
	states[i][j] = 1;
      else
	states[i][j] = 0;
    }
}

char classification(int count, int width){
  char class;
  for(int i = 0; i < count; i++)
    for(int j = 0; j < width; j++){
      if(initial[i][j] == '0'){
	class = CC_WS;
      }
      else if (initial[i][j] == '1'){
	class = CC_NEWLINE;
      }
      else if (initial[i][j] == '2'){
	class = CC_ALPHA;
      }
      else if (initial[i][j] == '3'){
	class = CC_DIG_0;
      }
      else if (initial[i][j] == '4'){
	class = CC_DIG_1_7;
      }
      else if (initial[i][j] == '5'){
	class = CC_DIG_8_9;
      }
      else if (initial[i][j] == '6'){
	class = CC_CHAR_SLASH;
      }
      else if (initial[i][j] == '7'){
	class = CC_CHAR_STAR;
      }
      else if (initial[i][j] == '8'){
	class = CC_ARITH_OP;
      }
      else if (initial[i][j] == '9'){
	class = CC_OTHER;
      }
      else if (initial[i][j] == '10'){
	class = CC_EOF;
      }
      else if (initial[i][j] == '11'){
	class = CC_ERROR;
      }
      else if (initial[i][j] == '12'){
	class = N_CC;
      }
    }
  return class;
}

void scanner(FILE *fp){
  count = 4;
  int lineLen = 0;
  size_t n = 0;
  ssize_t num = -1;
  char* valuesPtr;
  char* ptr, buf[256];
  
  while((ptr = getline(&buf, &n, fp)) > 0){
    if (count == 0){
      char word[256];
      sscanf(ptr, "%s %d", word, &statesv);
      printf("%s %d\n", word, statesv);
    }
    if (count == 1) {
      char word[256];
      sscanf(ptr, "%s %d", word, &start);
      printf("%s %d\n", word, start);
    }
    if (count == 2) {
      char word[256];
      sscanf(ptr, "%s %d", word, &accept);
      printf("%s %d\n", word, accept);
    }
    


    lineLen = strlen(buf);
    char values[lineLen / 2];
    for(int i = 0; i < lineLen; i++){
      values[i/2] = buf[i];
    }
    //    valuesPtr = strdup(values);
    // initial[valuesPtr][lineLen] = valuesPtr;
    
    //initial[count][i] = buf[i];
  }

    
    count++;

    //  width = lineLen;

    // for(int i = 0; i < 100; i++){
    // for (int j = 0; j < 100; j++){
    // printf("%d", initial[i][j]);
    // }
    //}
}

int main(int argc, char* argv[]){
  FILE *fp;

  fp = fopen(argv[1], "r");
  if (fp == NULL){
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }
  
  scanner(fp);

}
