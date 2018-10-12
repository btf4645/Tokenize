#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "classes.h"

char *initial[75][12] = {0};
int count = 0;
int accept = 0;
int start = 0;
int statesv = 0;
int classcharacter;
int statenumber;
char dors = '\0';



void  matrix(){
  
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
	   (class >= 96 && class < 127)){
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
  char* ptr, buf[256];
  classcharacter = -1;
  statenumber = -1;
  dors = '\0';
  int zates;
  int* p = (int*)malloc(2 * sizeof(int));

  
  while((ptr = fgets(buf, 256, fp)) != NULL){
    if (count == 0){
      char word[256];
      sscanf(ptr, "%s %d", word, &statesv);
      //printf("%s %d\n", word, statesv);
    }
    else if (count == 1) {
      char word[256];
      sscanf(ptr, "%s %d", word, &start);
      //printf("%s %d\n", word, start);
    }
    else if (count == 2) {
      char word[256];
      sscanf(ptr, "%s %d", word, &accept);
      //printf("%s %d\n", word, accept);
    }
    else{
      char StringCurrent[266];
      strcpy(StringCurrent, ptr);
      char* atoken;
      atoken = strtok(StringCurrent, " \t"); 
      while(atoken != NULL){
	if(strlen(atoken) == 1) {
	  statenumber  = atoi(atoken); 
	}
	atoken = strtok(NULL, " \n\t");
	//printf("%s\n", atoken);
	if(atoken != NULL) {
	  //printf("%s\n", atoken);
	  sscanf(atoken, "%d/%d%c", &classcharacter, &zates, &dors);
	  char anotherarray[3] = "";
	  sprintf(anotherarray, "%d%c", zates, dors);
	  //printf("[%d][%d] = %d%c\n", statenumber,classcharacter,zates,dors); 
	  initial[statenumber][classcharacter] = anotherarray;
	}
 	
      }
    }
    count++;    
  }
  printf("%s", "      0     1     2     3     4     5     6     7     8     9     10     11\n");
  for(int i = 0; i < statenumber; i++){
    printf("%d ", i);
    for(int j = 0; j < 12; j++){
      if(initial[i][j] == NULL){
	initial[i][j] = "99d";
      }
      printf("  %4s" , initial[i][j]);
      }
    printf("\n");
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
