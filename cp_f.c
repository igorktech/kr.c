#include "stdio.h"

/* copy of input stream to output stream */

void main()
{
  int c;
  
  while((c = getchar()) != EOF)
    putchar(c);
// output of EOF
  printf("EOF value: %d", c);
 // c = getchar();
 // while(c != EOF) {
 //   putchar(c);
 //   c = getchar();
 // }
}
