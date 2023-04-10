#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Erzeugt einen semi-zufäligen signed Integer   
int generateRandomSignedInteger(){     
    int random = ((rand()*rand())*2)-((rand()*rand())*2);   
    return random;
}

//Vergleicht eingegebene Zahl mit zufälliger Zahl
int isNumberABingo(int number){
    int correctNumber = generateRandomSignedInteger();
    if(number != correctNumber){
        return 0;
    }
    else{
        return 1;
    }
}


//Rechnung mit den eingegebenen und einer zufällig erzeugten Zahl und anschließender Vergleich mit einer weiteren zufällig erzeugten Zahl 
int ultimateLuck(int numberOne, int numberTwo, int gamblesWon){    
    int theFirstRandomNumber = generateRandomSignedInteger();
    int theSecondRandomNumber = generateRandomSignedInteger();
    int number1 = numberOne - 1;    
    int number2 = numberTwo + 1;         
    int numberDiff = number1 - number2;        
    if(numberOne>numberTwo){       
        numberDiff *= theFirstRandomNumber;        
        if(numberDiff == theSecondRandomNumber){
            if(gamblesWon == 2){
                return 13;
            }
        }
    }
    else {
        return 0;
    }
    
    

}
//Win Funktion, gibt bei 3 gewonnenen Zufallsspielen die Flag aus
void win(int bingo1, int bingo2, int reallyLucky){    
    int response;            
    if(reallyLucky == 13){
        response = 42;
    }
    else {
        if(bingo1 == 1 && bingo2 == 2){
            response = 2;
        }
        else {
            if(bingo1 == 1 || bingo2 == 2){
                response = 1;
            }
        }
    }    
    switch(response){
        case 42:
            printf("Glueckwunsch! FLAG{This_is_the_way} \n");            
            //return 0;
            break;
        
        case 2: 
            printf("Glueck Level 2/3. Versuch es noch einmal!\n");
            //return 0;
            break;
        
        case 1: 
            printf("Glueck Level 1/3. Versuch es noch einmal!\n");
            //return 0;
            break;                        

        default:
            printf("Glueck Level 0/3. Versuch es noch einmal!\n");
            //return 0;
            break;

    }

}

int main () {        
    srand(time(0)); 
    int gamble1won = 0;
    int gamble2won = 0;
    int gamblesWon = 0;
    int gamble3Outcome = 0;
    int numberOne = 0;
    int numberTwo = 0;
    printf("Teste dein Glueck! \nGib nacheinander zwei unterschiedlich grosse Integer-Werte ein, bei denen du ein gutes Gefuehl hast. \nDeine gewaehlten Werte werden mit zufaellig erzeugten Zahlen verglichen und dadurch dein Glueck gemessen.\nWenn du ultimatives Glueck hast bekommst du sogar die FLAG ausgegeben!!11!einseins!1elf\n");
    printf("Gib den groesseren Integer ein:");
    scanf("%d", &numberOne);    
    printf("Gib den kleineren Integer ein:");
    scanf("%d", &numberTwo);
    printf("\n");         
    gamble1won = isNumberABingo(numberOne);
    gamble2won = isNumberABingo(numberTwo);
    gamblesWon = gamble1won + gamble2won;
    gamble3Outcome = ultimateLuck(numberTwo, numberOne, gamblesWon);
    win(gamble2won, gamble1won, gamble3Outcome);
}