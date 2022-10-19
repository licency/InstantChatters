#include<stdio.h>
#include<stdlib.h>
#include<string.h>



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
//			printf("Inside if condition \n ");
//			printf("%s \n",str);
			break;
		}
		else {


//			printf("Inside else condition str = %s   \n",str);

			//char *token = strtok(str,":");

			//printf("token =  %s\n",token);

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

