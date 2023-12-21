#include <stdio.h>
#include <time.h>

int binsearch(int x, int v[], int n);
int fast_binsearch(int x, int v[], int n);

int main()
{
    int arr[6] = {3, 4, 5, 6, 7, 8};
    int number = 42;
    int result = -1;

    clock_t start, finish;
    start = clock();
    result = binsearch(number, arr, 6);
    finish = clock();
    printf("number: %d position: %d", number, result);
    printf("binsearch duration: %f\n", ((double)(finish - start)) / CLOCKS_PER_SEC);
    
    start = clock();
    result = fast_binsearch(number, arr, 6);
    finish = clock();
    printf("number: %d position: %d", number, result);
    printf("fast binsearch duration: %f\n", ((double)(finish - start)) / CLOCKS_PER_SEC);


    return 0;
}

/* binsearch: search x in v[] <= v[1] <= ... <= x[n-1] */
int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* fast_binsearch: search x in v[] <= v[1] <= ... <= x[n-1] */
int fast_binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
            
    }
    if (x == v[mid])
		return mid;
	else if (x > v[mid])
		mid += 1;
	else
		mid -= 1;

	if (mid < 0 || mid > n - 1)
		return -1;
	else
		return mid;
}


