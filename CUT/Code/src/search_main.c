/*
program name : search
description  : This helps in searching particular string through chat history.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*searches for string, taken from user, in chat history file. */
int main()
{
	FILE *fp;
	int flag=0;
	char strToBeSearched[100],  str[100];
	fp = fopen("../data/logfile.txt","r");
	if(fp ==NULL) printf("Error in opening file \n");

	printf("Enter string to be searched : ");
	fgets(strToBeSearched,100,stdin);
	strToBeSearched[strlen(strToBeSearched)-1]='\0';

	while(1)
	{
		strcpy(str,"");

		if(fgets(str,100, fp)==NULL)
		{
			break;
		}
		else {
			if(strstr(str,strToBeSearched))
				{
					printf("Found in this line %s \n ",str);
					printf("Written by   %s ",strtok(str,":"));
					flag=1;
				}
		}

	}
	if(flag==0)
	printf("Not found in chat history \n");
	
return 0;
}
