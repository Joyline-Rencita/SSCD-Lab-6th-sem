/*Pgm4: Shift-Reduce Parsing*/
#include<stdio.h>
#include<string.h>
int k=0,z=0,i=0,j=0,c=0;//c for length of string, i for stack, j for input and z for check function
char a[16],ac[20],stk[15],act[10];      //act[ ] for shift and ac[ ] for reduce
int count=0,level=0;
void check();       // to check top of stack
int main()
{
      	printf("GRAMMAR is:\n	E->E+T|T \n	T->T*F|F\n	F->(E)|id\n");
      	printf("Enter input string\n");
      	scanf("%s",&a);
      	c=strlen(a);
      	printf("stack \t input \t action\n");
      	printf("------\t ------\t ------\n");
	printf("\n$%s\t%s$\t",stk,a);
        for(k=0,i=0; j<c; k++,i++,j++)
      	{
         	if(a[j]=='i' && a[j+1]=='d')    //checks the input for "id"
           	{
			strcpy(act,"SHIFT ");       //initial configuration
			stk[i]=a[j];
              		stk[i+1]=a[j+1];    //shift id to stack
              		stk[i+2]='\0';
              		a[j]=' ';
              		a[j+1]=' ';     //delete "id" from input array
              		printf("\n$%s\t%s$\t%sid",stk,a,act);   //displays the first line SHIFT->id
			count+=1;
			check();
           	}
         	else if(a[j]=='+'||a[j]=='*')
           	{
			strcpy(act,"SHIFT ");
			stk[i]=a[j];
              		stk[i+1]='\0';
              		a[j]=' ';
              		printf("\n$%s\t%s$\t%s%c",stk,a,act,stk[i]);   //print SHIFT->symbols for inputs like +,*
			count+=1;
			check();
	   	}
		else if(a[j]=='(')
           	{
			strcpy(act,"SHIFT ");
			stk[i]=a[j];
              		stk[i+1]='\0';
              		a[j]=' ';
              		printf("\n$%s\t%s$\t%s%c",stk,a,act,stk[i]);
			count+=1;
			level+=1;
			check();
	   	}
		else if(a[j]==')')
           	{
			strcpy(act,"SHIFT ");
			stk[i]=a[j];
              		stk[i+1]='\0';
              		a[j]=' ';
              		printf("\n$%s\t%s$\t%s%c",stk,a,act,stk[i]);
			count+=1;
			level-=1;
			check();
	   	}
		else
	   	{
			printf("\nERROR IN INPUT\n");
			break;
	   	}
       }
	if(stk[0]=='E' && count==1 && level==0 && j==c) //at the end of input if stack holds "E"
		printf("\n****SUCCESSFULL PARSING****\n");
	else
		printf("\n****FAILURE IN PARSING****\n");
}
void check()
{
     	strcpy(ac,"REDUCE F->id");  //display REDUCE
     	for(z=0; z<c; z++)
       		if(stk[z]=='i' && stk[z+1]=='d')      // if stack holds id
         	{
           		stk[z]='F';     //reduce to F
           		stk[z+1]='\0';
           		printf("\n$%s\t%s$\t%s",stk,a,ac);
           		j++;    //move input pointer
                }
	strcpy(ac,"REDUCE T->T*F");
	for(z=0; z<c; z++)
       		if(stk[z]=='T' && stk[z+1]=='*' && stk[z+2]=='F')   // if stack holds T*F
         	{
           		stk[z]='T';
           		stk[z+1]='\0';
           		stk[z+2]='\0';
           		printf("\n$%s\t%s$\t%s",stk,a,ac);
           		i=i-2;      //top of stack holds T
			count=count-2;
         	}
	strcpy(ac,"REDUCE T->F");
	for(z=0; z<c; z++)
       		if(stk[z]=='F' )
         	{
           		stk[z]='T';
           		stk[z+1]='\0';
           		printf("\n$%s\t%s$\t%s",stk,a,ac);
           	}
	strcpy(ac,"REDUCE E->E+T");
     	for(z=0; z<c; z++)
	{
       		if(stk[z]=='E' && stk[z+1]=='+' && stk[z+2]=='T' && stk[z+3]!='*' && a[j+1]!='*')     
 //checks for stack E+T
        	{
			if(stk[z+3]==')')
			{
				stk[z]='E';
           			stk[z+1]=')';
           			stk[z+2]='\0';
				stk[z+3]='\0';
	   			printf("\n$%s\t%s$\t%s",stk,a,ac);
           			i=i-2;
				count=count-2;
			}
			else
			{
				stk[z]='E';
           			stk[z+1]='\0';
           			stk[z+2]='\0';
	   			printf("\n$%s\t%s$\t%s",stk,a,ac);
           			i=i-2;
				count=count-2;
			}
         	}
		else if(stk[z]=='E' && stk[z+1]=='+' && stk[z+2]=='T' && j==c)
		{
           		stk[z]='E';
           		stk[z+1]='\0';
           		stk[z+2]='\0';
	   		printf("\n$%s\t%s$\t%s",stk,a,ac);
           		i=i-2;
			count=count-2;
		}
		else if(stk[z]=='E' && stk[z+1]=='+' && stk[z+2]=='T' && stk[z+3]==')')
		{
           		stk[z]='E';
           		stk[z+1]=')';
           		stk[z+2]='\0';
	   		printf("\n$%s\t%s$\t%s",stk,a,ac);
           		i=i-2;
			count=count-2;

		}
		else
			break;
 	}
	strcpy(ac,"REDUCE E->T");
	for(z=0; z<c; z++)
        	if(stk[z]=='T' )
         	{
           		if(a[j+1]=='+')
          		{
           			stk[z]='E';
           			stk[z+1]='\0';
           			printf("\n$%s\t%s$\t%s",stk,a,ac);
           		}
			else
				break;

        	}
   	strcpy(ac,"REDUCE F->(E)");
     	for(z=0; z<c; z++)
       		if(stk[z]=='(' && stk[z+1]=='E' && stk[z+2]==')')
         	{
           		stk[z]='F';
           		stk[z+1]='\0';
           		stk[z+2]='\0';
           		printf("\n$%s\t%s$\t%s",stk,a,ac);
           		count=count-2;
         	}
   }
