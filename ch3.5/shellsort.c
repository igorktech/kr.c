#include <stdio.h>

void shellsort(int v[], int n);
print_arr(int v[], int n);

int main()
{
    int test[] = {4,3,6,1,10,4,33,2};

    print_arr(test, 8);

    shellsort(test, 8);
    
    print_arr(test, 8);

    return 0;
}


void shellsort(int v[], int n)
{
    int gap, i, j, temp;

    for (gap = n/2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j=i-gap; j >=0 && v[j]>v[j+gap]; j-=gap) {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
}


print_arr(int v[], int n)
{
    for(int i = 0; i < n; i++)
        printf(" %d ", v[i]);
    printf("\n");
}
