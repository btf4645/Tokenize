#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "classes.h"

char states[25][25] = {0};
char initial[25][25] = {0};
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

int classification(char class){
  if(class == 32 || class == 9){
    return CC_WS;
  }
  else if (class == 13){
    return CC_NEWLINE;
  }
  else if ((class >= 65 && class <= 90) && class == 95){
    return CC_ALPHA;
  }
  else if (class == 48){
    return CC_DIG_0;
  }
  else if (class >= 49 && class <= 55){
    return CC_DIG_1_7;
  }
  else if (class == 56 || class == 57){
    return CC_DIG_8_9;
  }
  else if (class == 47){
    return CC_CHAR_SLASH;
  }
  else if (class == 42){
    return CC_CHAR_STAR;
  }
  else if (class == 37 || class == 43 || class == 45){
    return CC_ARITH_OP;
  }
  else if ((class >= 0 && class <= 12) || (class >= 14 && class <= 36) || (class >= 38 && class <= 41) ||
	   (class >= 50 && class <= 54) || (class >= 58 && class <= 64) || (class >= 91 && class <= 94) ||
	   (class >= 96 && class <= 127)){
    return CC_OTHER;
  }
  else if (class == EOF){
    return CC_EOF;
  }
  else{
    return CC_ERROR;
  }
}


void scanner(FILE *fp){
  count = 0;
  int lineLen = 0;
  //size_t n = 0;
  //ssize_t num = -1;
  //char* valuesPtr;
  char* ptr, buf[256];
  
  while((ptr = fgets(buf, 256, fp)) != NULL){
    if (count == 0){
      char word[256];
      sscanf(ptr, "%s %d", word, &statesv);
      printf("%s %d\n", word, statesv);
    }
    else if (count == 1) {
      char word[256];
      sscanf(ptr, "%s %d", word, &start);
      printf("%s %d\n", word, start);
    }
    else if (count == 2) {
      char word[256];
      sscanf(ptr, "%s %d", word, &accept);
      printf("%s %d\n", word, accept);
    }
    else{
      char StringCurrent[266];
      strcpy(StringCurrent, ptr);
      char* pch;
      pch = strtok(StringCurrent, ",.-");
      while(pch != NULL){
	printf("%s\n", pch);
	pch = strtok(NULL, ",.-");
      }
      lineLen = strlen(ptr);
      for(int i = 0; i < lineLen; i++){
	initial[count][i] = pch;
      }
    }
    count++;    
  }

  

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
