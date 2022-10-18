#include <stdio.h>
#define MAX 30
#define SUCCESS 1
#define FAIL 0
#include<string.h>

int validName(char name[MAX])
{
	int c = 0;
	for(int i = 0; name[i] != '\0'; i++)
	{
		c++;
	}
	 
	if(c > 2 && c < 30)
	{
		return SUCCESS;
	}
	else
		return FAIL; 
}

int validPass(char pass[MAX])
{
	int a = 0;
	for(int j = 0; pass[j] != '\0'; j++)
	{
		a++;
	}
	 
	if(a > 2 && a < 30)
	{
		return SUCCESS;
	}
	else
		return FAIL;
}