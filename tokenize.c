#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "classes.h"

int initial[75][12][2] = {0};
int count = 0;
int accept = 0;
int start = 0;
int statesv = 0;
int classcharacter;
int statenumber;
char dors = '\0';



void  matrix(){
  /**  for(int i = 0; i < statesv; i ++){ //the first column
    for(int j = 0; j != 0; j++){ //each row (filled with zeroes, so you hit the end when you hit a zero)
      int curState = initial[i][0][]; //current state
      char curStatus[2] = {0}; //TODO: split on / take the last two numbers
      int firstNumber = 0; //split on the / take the first number (the num before the slash)
      states[curState][firstNumber] = curStatus; //copy curStatus into this value
    }
    for(int k = 0; k < 12; k++){ //iterating through the row in the new matrix again, to fill empty spaces
      if(states[curState][k] == 0){ //if it is an empty space (initialized to 0)
	states[curState][k] = "99d"; //fill with 99d
      }
    }   
    }**/
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
      int btoken;
      atoken = strtok(StringCurrent, " \t"); //do something with n_cc is useful maybe use 2 arrays in third 3d array
      btoken = (int)(__intptr_t)atoken;
      while(atoken != NULL){
	//printf("%s\n", atoken);
	atoken = strtok(NULL, " \n\t");
	//printf("%s\n", atoken);
	if(atoken != NULL) {
	  printf("%s\n", atoken);
	  if(strlen(atoken) == 1){
	    printf("equals 1");
	  }
	  sscanf(atoken, "%d/%d%c", &classcharacter, &statenumber, &dors);
	  initial[count + 3][classcharacter][0] = statenumber;//somehow needs to have btoken in counts place
	  if(dors == 'd'){
	    initial[classcharacter][statenumber][2] = 0; //0 means delete
	  }
	  if(dors == 's'){
	    initial[classcharacter][statenumber][2] = 1; //1 means save
	  }
	}
 	
      }
    }
    count++;    
  }
  for(int i = 0; i < classcharacter; i++){
    for(int j = 0; j < statenumber; j++){
      for(int k = 0; k < dors; k++){
	printf("%d\t" , initial[i][j][k]);
      }
    }
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
