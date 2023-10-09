#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int charToAsciiVal(char c){//Konvertiert Char in Int
    return (int)(c);
}

void strrev(char *arr, int start, int end) //Standart-C Funktion für itoa
{
    char temp;

    if (start >= end)
        return;

    temp = *(arr + start);
    *(arr + start) = *(arr + end);
    *(arr + end) = temp;

    start++;
    end--;
    strrev(arr, start, end);
}

char *itoa(int number, char *arr, int base)//Konvertiert Int in String (Standard-C Funktion)
{
    int i = 0, r, negative = 0;

    if (number == 0)
    {
        arr[i] = '0';
        arr[i + 1] = '\0';
        return arr;
    }

    if (number < 0 && base == 10)
    {
        number *= -1;
        negative = 1;
    }

    while (number != 0)
    {
        r = number % base;
        arr[i] = (r > 9) ? (r - 10) + 'a' : r + '0';
        i++;
        number /= base;
    }

    if (negative)
    {
        arr[i] = '-';
        i++;
    }

    strrev(arr, 0, i - 1);

    arr[i] = '\0';

    return arr;
}

void xor(char *input, char *key,char *output){
    int i;
    for(i = 0; i < strlen(input); i++) {
        output[i] = input[i] ^ key[i % (sizeof(key)/sizeof(char))];
    }
}

void encrypt(char *input, char *output){ //Caesar-Ascii Verschlüselung
    //konvertiere String zu int-Array
    int intArr[strlen(input)];
    int i;
    for(i = 0; i < strlen(input); i++) {
        intArr[i]=charToAsciiVal(input[i])+7;
    }
    //konvertiere int zu char zurück
    int j;
    for(j = 0; j < strlen(input); j++) { 
        char caesarString[7];
        itoa(intArr[j],caesarString,10);
    //string number to ascii char
        output[j]=(atoi(caesarString));
     }
}

void printFlag(){
        char flag[]="t~suI_WAA[O";//FLAG{messi}
        char keyy[]="+++++++++";  //Key, mit dem gexort wird. Ist ebenso in Caesar verschlüsselt. Entschlüsselt: 222222222       
        char keyy2[57];
        char output[100];
        encrypt(keyy,keyy2);
        xor(flag, keyy2,output);
        printf("%s \n", output);
}

int main(int argc, char *argv[]){

    printf("Geben Sie das Passwort ein. Achtung es ist salty: ");

    char passwort[]="salty";
    
    char input[30];
    scanf("%s", &input);

    char salt[]="lZem[Z^";
    char decryptedSalt[strlen(salt)];
    
    encrypt(salt, decryptedSalt);
    strcat(passwort, decryptedSalt);//konkateniere salt mit passwort

    if(strcmp(passwort, input) == 0){//Prüfung der Eingabe
        printFlag();
        return 0;
    }
    else{
        printf("Not Salty enough tho");
        return 0;
    }
}