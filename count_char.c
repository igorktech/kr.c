#include "stdio.h"

/* copy of input stream to output stream */

void main()
{
  long nc;
  
  nc = 0;
  while(getchar() != EOF)
    ++nc;
// output of EOF
  printf("Total inserted characters: %ld\n", nc);

  int c = 0, nl = 0;
  for(nl = 0; (c = getchar()) != EOF; )
    if(c == '\n')
      ++nl;
  printf("Total inserted lines: %d\n", nl);
 // c = getchar();
 // while(c != EOF) {
 //   putchar(c);
 //   c = getchar();
 // }
}
