#include <stdio.h>

struct s_i_c{
	short a;
	int	b;
	char c;
};

struct s_c_i{
	short a;
	char b;
	int c;
};

int main(void)
{
	struct s_i_c A;
	struct s_c_i B;
	printf("short int char: %d\nshort char int: %d\n", (int)sizeof(A), (int)sizeof(B));
	
	return 0;
}
