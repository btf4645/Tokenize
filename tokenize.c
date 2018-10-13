/*
 *Author: Rebecca Fried
 *File: Tokenize
 *This file scans in a matrix and then decides where certain elements should go depending on that
 *
 */
//Define statement for the future use of strdup
#define _DEFAULT_SOURCE

//All of the include statements that helpfully 
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "classes.h"

//These are the global variables used
char *initial[75][12];
int count = 0;
int accept = 0;
int start = 0;
//this is an arbitrary value
char something[64];
int statesv = 0;
int classcharacter;
int statenumber;
//this is the d or s char variable
char dors = '\0';
//this defines the classification function for use in the matrix function
int classification(char a);

/*
 *This function is for using character classifications in order to determine what states the subject is going *to. 
 */
void  matrix(){
  //sets the state number to the start value
  statenumber = start;
  //outputs the statenumber
  printf("%d " , statenumber);
  //these are the local variables which will be of use in this function
  int a;
  int num;
  int counter = 0;
  //allows a to getchar
  a = getchar();
  //while loop if int a doesn't equal to end of file
  while(a != EOF){
    //the number gets set equal to classification function
    num = classification(a);
    //char variable is set to aspot
    char* aspot;
    //set aspot to equal initial matrix sub of statenumber and num
    aspot = initial[statenumber][num];
    //sscanf is used to seperate the int statenumber and the int of d or s
    sscanf(aspot, "%d%c", &statenumber, &dors);
    //if statement that if d is equal to s
    if(dors == 's'){
      //prints out statenumber
      printf("%d ", statenumber);
      //sets the something char to counter equaling to int a
      something[counter] = a;
      //counter gets increased
      counter++;
    }
    //if statement that checks if statenumber is equal to 99
    if(statenumber == 99){
      //prints the statenumber
      printf("%d ", statenumber);
      //prints rejected
      printf("rejected");
      printf("\n");
      //sets a to getchar
      a = getchar();
      //sets num to equal the result of calling the classification function
      num = classification(a);
      //while the num does not equal to 0
      while(num != 0){
	//sets a to getchar
	a = getchar();
	//sets num to equal the result of calling the classification function
	num = classification(a);
      }
      //uses memset to set something to fill in with 64 bits
      memset(something, '\0', 64);
      //counter is equal to 0
      counter = 0;
      //statenumber is equal to start
      statenumber = start;
      //prints out the statenumber
      printf("%d ", statenumber);
    }
    //if statenumber equals accept
    else if(statenumber == accept){
      //prints out the statenumber
      printf("%d ", statenumber);
      //prints recognized
      printf("recognized '");
      //for loop that prints all contents of the something variables
      for(size_t i = 0; i < strlen(something); i++){
	printf("%c", something[i]);
      }
      printf("'\n");
      //uses memset to set something to nothing and 64 bits
      memset(something, '\0', 64);
      //sets counter to 0
      counter = 0;
      //sets statenumber to start
      statenumber = start;
      //prints out statenumber
      printf("%d ", statenumber);
    }
    //sets a int to get character
    a = getchar();
  }
  //sets num to eqaul classification function
  num = classification(a);
  //sets donez variable to initial matrix
  char* donez =  initial[statenumber][num];
  //sscanf will split up between the statenumber and the d or s
  sscanf(donez, "%d%c", &statenumber, &dors);
  //if d or s is equal to s
  if(dors == 's'){
    //prints out the statenumber
    printf("%d ", statenumber);
  }
  //statenumber equal to 99, then print out rejected
  else if (statenumber == 99){
    printf("%d rejected\n", statenumber);
  }
  //if statenumber is equal to accept
  else if(statenumber == accept){
    //prints out the statenumber
    printf("%d EOF\n", statenumber);
  }
}
    

/*
 *Classification function which determines the classification of a character determined ny ASCII charcters
 */
int classification(char class){
  //if the class character equals either 32 or 9
  if(class == 32 || class == 9){
    //it will return CC_WS
    return CC_WS;
  }
  //if the class chracter equals 10 or equals 13
  else if (class == 10 || class == 13){
    //it will return CC_NEWLINE
    return CC_NEWLINE;
  }
  //if the class character either equals 95 or is an upper or lower case character
  else if ((class >= 65 && class <= 90) || class == 95 || (class >= 97 && class <= 122)){
    //return CC_ALPHA
    return CC_ALPHA;
  }
  //if the class chracter either equals 48
  else if (class == 48){
    //return CC_DIG_0
    return CC_DIG_0;
  }
  //if the class is greater than 49 and less than 55
  else if (class >= 49 && class <= 55){
    //return CC_DIG_1_7
    return CC_DIG_1_7;
  }
  //if the class equals 56 or 57
  else if (class == 56 || class == 57){
    //return CC_DIG_8_9
    return CC_DIG_8_9;
  }
  //if the class chracter equals 47
  else if (class == 47){
    //return CC_CHAR_SLASH
    return CC_CHAR_SLASH;
  }
  //if the class character equals 42
  else if (class == 42){
    //return CC_CHAR_STAR
    return CC_CHAR_STAR;
  }
  //if the class character equals either 37,43,or 45
  else if (class == 37 || class == 43 || class == 45){
    //return CC_ARITH_OP
    return CC_ARITH_OP;
  }
  //else if it is anything else
  else if ((class >= 0 && class <= 8) || (class == 11) || (class == 12) || (class >= 14 && class <= 31) || (class >= 33 && class <= 36)
	   || (class >= 38 && class <= 41) || (class == 44) || (class == 46) || (class >= 58 && class <= 64) || (class >= 91 && class <= 94) || (class == 96) || (class >= 123 && class < 127)){
    //return CC_OTHER
    return CC_OTHER;
  }
  //else if class character equals end of life
  else if (class == EOF){
    //return CC_EOF
    return CC_EOF;
  }
  //else
  else{
    //return CC_ERROR
    return CC_ERROR;
  }
}


/*
 *The scanner function takes in a file, then determines where it should go in the initial matrix
 */
void scanner(FILE *fp){
  //these are the initial variable names that are locally stored
  count = 0;
  char* ptr, buf[256];
  classcharacter = -1;
  statenumber = -1;
  dors = '\0';
  int zates;

  //while fgets/the file does not equal NULL
  while((ptr = fgets(buf, 256, fp)) != NULL){
    //if the count equals to 0
    if (count == 0){
      //make word char
      char word[256];
      //scans in the word and the states
      sscanf(ptr, "%s %d", word, &statesv);
    }
    //else if the count is equal to 1
    else if (count == 1) {
      //make word char
      char word[256];
      //scans in the word and the start
      sscanf(ptr, "%s %d", word, &start);
    }
    //else if the count is equal to 2
    else if (count == 2) {
      //make word char
      char word[256];
      //scans in the word and the accept
      sscanf(ptr, "%s %d", word, &accept);
    }
    //else if it doesn't
    else{
      //make stringcurrent char
      char StringCurrent[266];
      //stringcopy the string current and the pointer variable
      strcpy(StringCurrent, ptr);
      //makes atoken char
      char* atoken;
      //atoken is set to equal the strtok of string current and then will slice it on the tab character
      atoken = strtok(StringCurrent, " \t");
      //while token does not eqaul to null
      while(atoken != NULL){
	//if the length of the token is equal to 1
	if(strlen(atoken) == 1) {
	  //statenumber is equal to the token using atoi
	  statenumber  = atoi(atoken); 
	}
	//atoken is equal to strtok to equal to NULL and splits it at new line and new tab
	atoken = strtok(NULL, " \n\t");
	//if token is not null
	if(atoken != NULL) {
	  //then it will use sscanf to put in a classcharacter, states, and d or s
	  sscanf(atoken, "%d/%d%c", &classcharacter, &zates, &dors);
	  //makes an array and uses malloc
	  char *anotherarray = (char*) malloc(3);
	  //uses springf to do put in zates and dors
	  sprintf(anotherarray, "%d%c", zates, dors);
	  //initial sub statenumber and sub classcharacter is set equal to another array variable
	  initial[statenumber][classcharacter] = anotherarray;
	}
 	
      }
    }
    //count increases
    count++;    
  }
  //prints out the following matrix
  printf("Scanning using the following matrix\n");
  printf("%s", "      0     1     2     3     4     5     6     7     8     9     10     11\n");
  //use for loop to iterate through statenumber and the classcharacter
  for(int i = 0; i < statesv; i++){
    printf("%d ", i);
    for(int j = 0; j < 12; j++){
      //if the initial[i][j] is equal to null
      if(initial[i][j] == NULL){
	//then sets the char to allocate for memory
	char* agoodone = (char*) malloc(3);
	//sets agoodone variable to strdup to be able to properyl free matrix
	agoodone = strdup("99d");
	//sets initial matrix to agoodone
	initial[i][j] = agoodone;
      }
      //prints out matrix
      printf("  %4s" , initial[i][j]);
      }
    printf("\n");
  }
}

/*
 *Main function that reads in a file and is able to open and close it
 */
int main(int argc, char* argv[]){
  //opens file
  FILE *fp;
  //if argc equals to 1
  if (argc == 1){
    //prints out this message
    printf("usage: /tokenize tmfile \n");
  }
  //opens the file fp
  fp = fopen(argv[1], "r");
  //if the file is equal to null
  if (fp == NULL){
    //give an error
    perror(argv[1]);
    //exits the function
    exit(EXIT_FAILURE);
  }
  //scanner function call using fp
  scanner(fp);
  //closes fp
  fclose(fp);
  //calls matrix function
  matrix();
  //iterates over statenumber and classification
  for(int i = 0; i < statesv; i++){
    for(int j = 0; j < 12; j++){
      //frees the initial matrix and prints it out
      free(initial[i][j]);
    }
  }
  //returns 0
  return 0;
}
