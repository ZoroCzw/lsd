#include <stdio.h>

void ch(int *a)
{
	printf("in ch a addr 0x%lx\n", (long unsigned int)a);
	*a = 10;
}
void ch1(int a)
{
	printf("in ch1 a addr 0x%lx\n", (long unsigned int)&a);
	a = 5;
}
int main()
{
	int a = 5;
	printf("in main a addr 0x%lx\n", (long unsigned int)&a);
	printf("first a = %d\n", a);
	ch(&a);
	printf("second a = %d\n", a);
	ch1(a);
	printf("third a = %d\n", a);
	return 0;
}

