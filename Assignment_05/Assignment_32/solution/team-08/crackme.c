#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void win(){
    printf("FLAG{it's_less_than_9000!}\n");
}

void lose(){
    printf("You won't get my flag this way\n");
}

//checks each char of string, if it's a number
int checkInput(char* input){
    for(int i=0; i<strlen(input); i++)
    	if(input[i] < 48 || input[i] > 57)
            return 0;
    return 1;
}

//reverts input
char* someFunc(char* input){
    char* end= &input[strlen(input)-1];
    char* b = malloc((strlen(input)) * sizeof(char));
    for (int i = 0; i<strlen(input);i++){
        b[i]=*end;
        end--;
    }
    return b;

}

int main(){

    char* first = malloc(64 * sizeof(char));
    char* second = malloc(64 * sizeof(char));
    char* third = malloc(64 * sizeof(char));
    
    printf("Please enter your input: \n");
    
    scanf("%s",first);
    scanf("%s",second);
    scanf("%s",third);
    
    int result1 = checkInput(first);
    int result2 = checkInput(second);
    int result3 = checkInput(third);
    
    //checks if second and third input are numbers
    if((result2 != 0) && (result3 != 0)){
        char* something = someFunc(second);
        char* a = malloc((strlen(something)+5) * sizeof(char));
        
        // append reverted input to "-"
        strcpy(a,"-");
        strcat(a,something);
        
        int b=atoi(a);
        int c=atoi(third);
        
        if (b==1337 && !(c%1637) && !(c%3557)){
            win();
            return 0;
        }
    }
    lose();
    return 0;
}