/*5.Design, develop and implement a C/Java program to generate the machine code using 
Triples for the statement A = -B * (C+D) whose intermediate code in three-address form:
	T1 = -B
	T2 = C + D
	T3 = T1 * T2
	A = T3       */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
char tset[4][3][3]= { {"-","B","?"},
                      {"+","C","D"},
                      {"*","0","1"},
                      {"=","A","2"}
                    };
int main()
{
int row,col;
printf("Input statement is:A = -B * (C+D)\n");
printf("Intermediate code in three address form is:\nT1 = -B\n T2 = C + D\nT3 = T1 * T2\nA =T3\n");
printf("Triples are:\n");    //Display the table
for(row=0;row<4;row++)
{
    printf("%d\t", row);
    for(col=0; col<3; col++)
        printf("%c\t",tset[row][col][0]);
    printf("\n");
   
}
 printf("Machine code generated is:\n");
 for(row=0;row<4;row++)
 {
   if (tset[row][2][0]=='?')
   {
     printf("\nLD R0,%s%s",tset[row][0],tset[row][1]);
   }
   else
   {
 	if(tset[row][0][0]=='+')
  	{
        printf("\nLD R1,%s",tset[row][1]);
    	printf("\nLD R2,%s",tset[row][2]);
    	printf("\nADD R1,R1,R2");
  	}
	else
	{
        if(tset[row][0][0]=='*')
            printf("\nMUL R0,R0,R1");
        else
            printf("\nST  %s,R0",tset[row][1]);
    }
   }
 }
 printf("\n");
 return 0;
}
