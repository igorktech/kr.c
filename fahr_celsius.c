#include "stdio.h"

#define LOWER 0
#define HIGHER 300
#define STEP 20

void main()
{
  float fahr, celsius;
  int lower, upper, step;

//  lower = 0;
//  upper = 300;
//  step = 20;
//
//  fahr = lower;
//
//  printf("%18s\n","Table Fahr to Cel");
//  printf("%9s\t%9s\n","fahr","cel");
//
//  while (fahr <= upper) {
//    celsius = (5.0/9.0) * (fahr-32);
//    printf("%9.0f\t%9.1f\n", fahr, celsius);
//    fahr = fahr + step;
//  }
//
//  celsius = 0;
//
//  printf("%18s\n","Table Cel to Fahr ");
//  printf("%9s\t%9s\n","cel","fahr");
//
//  while (celsius <= upper) {
//    fahr = (9.0/5.0) * (celsius-32);
//    printf("%9.0f\t%9.1f\n", celsius, fahr);
//    celsius = celsius + step;
//  }
// char c = getchar();
// putchar(c);
//
  for (int fahr = HIGHER; fahr>=LOWER; fahr = fahr - STEP)
    printf("%6d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}
