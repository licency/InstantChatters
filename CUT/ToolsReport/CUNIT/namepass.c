#include <stdio.h>
#define MAX 30
#define SUCCESS 1
#define FAIL 0
#include<string.h>

int validName(char name[MAX])
{
	if(strlen(name) > 2 && strlen(name) < 30)
	{
		return SUCCESS;
	}
	else
		return FAIL; 
}

int validPass(char pass[MAX])
{
	if(strlen(pass) > 2 && strlen(pass) < 30)
	{
		return SUCCESS;
	}
	else
		return FAIL;
}