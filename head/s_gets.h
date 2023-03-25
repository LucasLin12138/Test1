#ifndef __S_GETS_H__
#define __S_GETS_H__

#include <stdio.h>
#include <string.h>

char *s_gets(char *st, int n)
{
	char *ret_val;
	char *find;
	
	ret_val = fgets(st, n, stdin);
	if(ret_val)
	{
		find = strchr(st, '\n');
		if (find)
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;
			
	}
	
	return ret_val;
}


#endif
