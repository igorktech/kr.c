#include <stdio.h>
#include <stddef.h>

int main()
{
	char *alloc(int n);
	void afree(char* p);

	char *p = alloc(15);
	if (NULL == p) {
    	printf("not enough memory\n");
		return -1;
    }

	p[0] = 'H';
	p[1] = 'e';
	p[2] = 'l';
	p[3] = 'l';
	p[4] = 'o';
    p[5] = ',';
    p[6] = ' ';
    p[7] = 'w';
    p[8] = 'o';
    p[9] = 'r';
    p[10] = 'l';
    p[11] = 'd';
    p[12] = '!';
	p[13] = '\0';

	printf("%s\n", p);

	afree(p);

	printf("%s\n", p);

	p = alloc(10001);

	if (NULL == p)
		printf("not enough memory\n");

	printf("%d\n", NULL);

	return 0;
}
