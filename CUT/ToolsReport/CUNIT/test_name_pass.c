#include <stdio.h>
#define MAX 30
#include<string.h>
#define SUCCESS 1
#define FAIL 0

int printMsg(char name[MAX], char pass[MAX])
{
	int n1 = validName(name);
	if(n1 == 0)
	{
		printf("\nInvalid name, should be greater than 2 and less than 30");
		return FAIL;
	}
	
	int n2 = validPass(pass);
	if(validPass(pass) == 0)
	{
		printf("\nInvalid password, should be greater than 2 and less than 30");
		return FAIL;
	}
	else
	{
		printf("\nName : %s", name);
		printf("\nPass : %s", pass);
	
		return SUCCESS;
	}
}

int main()
{
	char name[MAX], pass[MAX];
	printf("Please enter your name: ");
	fgets(name, MAX, stdin);
	
	printf("Please enter your password: ");
	fgets(pass, MAX, stdin);
	
	int c = printMsg(name, pass);

	
	return 0;
}
