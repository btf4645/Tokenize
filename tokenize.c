#define _DEFAULT_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "classes.h"


char *initial[75][12];
int count = 0;
int accept = 0;
int start = 0;
int statesv = 0;
int classcharacter;
int statenumber;
char dors = '\0';
int classification(char a);


void  matrix(){
  statenumber = start;
  printf("%d " , statenumber);
  int a;
  int num;
  char* agoodpointer;
  int counter = 0;
  a = getchar();
  while(a != EOF){
    num = classification(a);
    char* aspot;
    aspot = initial[statenumber][num];
    sscanf(aspot, "%d%c", &statenumber, &dors);
    if(dors == 's'){
      printf("%d ", statenumber);
    }
    if(statenumber == 99){
      printf("%d ", statenumber);
      printf("rejected");
      printf("\n");
      a = getchar();
      num = classification(a);
      while(num != 0){
	a = getchar();
	num = classification(a);
      }
      statenumber = start;
      printf("%d ", statenumber);
    }
    else if(statenumber == accept){
      printf("%d ", statenumber);
      printf("recognized ");
      printf("\n");
      statenumber = start;
      printf("%d ", statenumber);
    }
    a = getchar();
  }
  num = classification(a);

  char* donez =  initial[statenumber][num];
  sscanf(donez, "%d%c", &statenumber, &dors);
  if(dors == 's'){
    printf("%d ", statenumber);
  }
  else if (statenumber == 99){
    printf("%d rejected\n", statenumber);
  }
  else if(statenumber == accept){
    printf("%d EOF\n", statenumber);
  }
}
    


int classification(char class){
  if(class == 32 || class == 9){
    return CC_WS;
  }
  else if (class == 10 || class == 13){
    return CC_NEWLINE;
  }
  else if ((class >= 65 && class <= 90) || class == 95 || (class >= 97 && class <= 122)){
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
  else if ((class >= 0 && class <= 8) || (class == 11) || (class == 12) || (class >= 14 && class <= 31) || (class >= 33 && class <= 36)
	   || (class >= 38 && class <= 41) || (class == 44) || (class == 46) || (class >= 58 && class <= 64) || (class >= 91 && class <= 94) || (class == 96) || (class >= 123 && class < 127)){
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
	  char *anotherarray = (char*) malloc(3);
	  sprintf(anotherarray, "%d%c", zates, dors);
	  //printf("[%d][%d] = %d%c\n", statenumber,classcharacter,zates,dors); 
	  initial[statenumber][classcharacter] = anotherarray;
	}
 	
      }
    }
    count++;    
  }
  printf("Scanning using the following matrix\n");
  printf("%s", "      0     1     2     3     4     5     6     7     8     9     10     11\n");
  for(int i = 0; i < statenumber; i++){
    printf("%d ", i);
    for(int j = 0; j < 12; j++){
      if(initial[i][j] == NULL){
	char* agoodone = (char*) malloc(3);
	agoodone = strdup("99d");
	initial[i][j] = agoodone;
      }
      printf("  %4s" , initial[i][j]);
      }
    printf("\n");
  }
}

int main(int argc, char* argv[]){
  FILE *fp;

  if (argc == 1){
    printf("usage: /tokenize tmfile \n");
  }
  fp = fopen(argv[1], "r");
  if (fp == NULL){
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }
  
  scanner(fp);
  fclose(fp);
  
  matrix();
  
  for(int i = 0; i < statenumber; i++){
    for(int j = 0; j < 12; j++){
      free(initial[i][j]);
    }
  }
  return 0;
}
