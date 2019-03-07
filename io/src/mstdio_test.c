#include "mstdio.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void)
{
	MFILE *fp1 = mfopen("/etc/passwd", "r");
	assert(fp1 != NULL);

	MFILE *fp2 = mfopen("mypasswd", "w");
	assert(fp2 != NULL);

	char c;
	while((c = mfgetc(fp1)) != MEOF)
	{
		mfputc(c, fp2);
	}

	mfclose(fp1);
	mfclose(fp2);
	return 0;
}
