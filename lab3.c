/*3.Design, develop and implement YACC/C program to construct
Predictive / LL(1) Parsing Table for the grammar rules:
A->aBa , B->bB|e. Use this table to parse the sentence: abba$ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char ip[20],stack[20];
int main()
{
	char m[2][3][3]={ {"aBa","E","E"}, {"n","bB","E"} };
	int size[2][3]= {3,1,1,1,2,1};
	int i,j,k,n,row,col,flag=0;
	int p,q,r;
	printf("\nEnter the input string: ");
	scanf("%s",ip);
	strcat(ip,"$");
	n=strlen(ip);
	stack[0]='$';
	stack[1]='A';
	i=1;
	j=0;

	printf("PARSING TABLE:\n");
	for(p=0;p<2;p++)
	{
		for(q=0;q<3;q++)
		{
			for(r=0;r<3;r++)
				printf("%c",m[p][q][r]);
			printf("\t");
		}
		printf("\n");
	}

	printf("\nStack\t\tInput\n");
	printf("________\t_________\n");

	for(k=0;k<=i;k++)
		printf("%c",stack[k]); 		/* Initial stack*/
	printf("\t\t");
	for(k=j;k<=n;k++)
		printf("%c",ip[k]); 		/* input*/
	printf("\n");

	while((stack[i]!='$')&&(ip[j]!='$'))/*check stack and input both contains $ */
	{
		if(stack[i]==ip[j])   	/* input and stack matches, discard stack and  move to next input symbol */
		{
 			i--;        //pop stack
 			j++;        //advance the input pointer
			for(k=0;k<=i;k++)
			  printf("%c",stack[k]); /*stack content */
			printf("\t\t");
			for(k=j;k<=n;k++)
			  printf("%c",ip[k]); 		/* input*/
			printf("\n");
 		}
		switch(stack[i])
		{
 			case 'A': row=0;
 				break;
 			case 'B': row=1;
 				break;
			default:if ((stack[i]=='$')&&(ip[j]=='$'))
					printf("\nSUCCESSFULL PARSING\n");
				else
				{
				printf("\nUNSUCCESSFULL PARSING\n");
				printf("ERROR-NO VALID MATCH\n");
				}
				exit(0);
		}
		switch(ip[j])
		{
 			case 'a': col=0;
 				break;
 			case 'b': col=1;
 				break;
 			case '$': col=2;
 				break;
		}

		if(m[row][col][0]==ip[j]) /*to check top of stack and input are equal*/
		{
 			for(k=size[row][col]-1;k>=0;k--) /* to replace non terminal by its production*/
 			{
 				stack[i]=m[row][col][k];
 				i++;
 			}
			i--;       /* points to top of stack*/
		}
		if(m[row][col][0]=='E')   /* to check error entry*/
		{
			if(i>0)
				printf("\nERROR....\n");
			else
				flag=1;
			exit(0);
		}
		if(m[row][col][0]=='n') /*to check for epsilon*/
            i--;

		for(k=0;k<=i;k++)
			printf("%c",stack[k]); /* Display stack contents*/
		printf("\t\t");
		for(k=j;k<=n;k++)
			printf("%c",ip[k]);   /* Display input contents*/
		printf("\n");
	}
	return 0;
}
