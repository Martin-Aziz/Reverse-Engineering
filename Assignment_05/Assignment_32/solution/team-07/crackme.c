#include <stdio.h>
#include <string.h>

int main(int argc, const char **argv, const char **envp)
{
  // Declare variables for loop indices
  int i;
  int j; 
  // Declare array to store predetermined values
  int v6[30]; 
  // Check if exactly one command line argument was passed
  if ( argc == 1 )
  {
    puts("Usage: ./crackme FLAG");
    return 1;
  }
  // Check if the length of the command line argument is 21 characters, if not print "Wrong Flag"
  else if ( strlen(argv[1]) == 21 )
  {
    for ( i = 0; i < 21; i++ ) // Loop through initialization key
     {  v6[24+i]= "sup3r_s3cr3t_k3y_1337"[i] - 34; // Do some distraction
     }
    v6[0] = 55;
    v6[1] = 63;
    v6[2] = 47;
    v6[3] = 118;
    v6[4] = 43;
    v6[5] = 98;
    v6[6] = 40;
    v6[7] = 33;
    v6[8] = 52;
    v6[9] = 15;
    v6[10] = 119;
    v6[11] = 98;
    v6[12] = 72;
    v6[13] = 39;
    v6[14] = 117;
    v6[15] = 8;
    v6[16] = 86;
    v6[17] = 106;
    v6[18] = 104;
    v6[19] = 78;
    v6[20] = 104;
    for ( j = 0; j < 21; ++j )
    {
      // validates the user input from argv[1] which denotes a XOR operation with the buffer array. Every single character of the input is compared with v6[j]
      if ( (char)(argv[1][j] ^ (v6[24+j])) != v6[j] )
      {
        puts("Wrong flag");
        return 1;
      }
    }
    // If all comparisons are true, print success message and return success code
    printf("You found a flag! %s\n", argv[1]);
    return 0;
  }
  else
  {
    puts("Wrong flag");
    return 1;
  }
}