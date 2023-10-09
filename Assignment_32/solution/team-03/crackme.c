#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

 //Verschlüsselte Flag sonst ist es ja zu einfach :)
#define KEY "\xBF\xA8\xF2\xBA"
#define ENCRYPTED "\xf9\xe4\xb3\xfd\xc4\xfa\xb7\xff\xe0\xeb\xb3\xf4\xe0\xea\xb7\xe5\xf9\xfd\xbc\xc7"

//simple Binary to Int interpreter
int binary_to_int(char *binary)
{
  int len = strlen(binary);
  int result = 0;
  for (int i = 0; i < len; i++)
  {
    if (binary[i] == '1')
    {
      result += pow(2, len - i - 1);
    }
  }
  return result;
}

void win()
{
  int j = 0;

  // das Flag wird durch verXORen mit dem Key entschlüsselt
  while (j < 20)
  {
    printf("%c", ENCRYPTED[j] ^ KEY[j % 4]);
    j = j + 1;
  }
  printf("%s", "\n");
}

int main()
{

  printf("Geben Sie meine Lieblingszahl ein: ");
  // Eingabe führt zur erstellung eines mallocs

  int eingabe;
  scanf("%d", &eingabe);
  //Malloc never fails, hier wird ein Malloc Fail nicht abgefangen sondern mit einem hint zum Flag geführt
  int *ptr = malloc(eingabe * sizeof(int));
  if (ptr == NULL)
  {
    printf("FALSEFALG{SHIT_1337_BIN_UR_CLOSE_SECRETCODE_69}\n");
    exit(0);
  } if (eingabe == 69)  {
    // Wenn die Eingabe 1337 ist, wird das Flag ausgegeben bzw. wenn sich die Binäreingabe in 1337 konvertieren lässt
    printf("SECRET CODE?\n");
    char eingabe[100];
    scanf("%s", eingabe);
    if (binary_to_int(eingabe) == 1337)
    {
      win();
      exit(0);
    } else
    {
      printf("LOL FAILED");
      exit(0);
    }
  }
    //eye candy
    printf("Was ist denn ihre ID?: ");
    int eingabe2;
    scanf("%d", &eingabe2);
    printf("Cool :) ");

    return 1;
  }
