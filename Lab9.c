/*Experiment 9: Design, develop and implement a C/C++/Java program to implement page replacement algorithms LRU and FIFO. Assume suitable input required to demonstrate the results.*/#include<stdio.h>
int n,nf,in[100],p[50],hit=0,i,j,k,pgfaultcnt=0;
void getData()
{
  printf("\nEnter length of page reference sequence:");
  scanf("%d",&n);
  printf("\nEnter the page reference sequence:");
  for(i=0; i<n; i++)
  scanf("%d",&in[i]);
  printf("\nEnter no of frames:");
  scanf("%d",&nf);
}
void initialize()
{
  pgfaultcnt=0;
  for(i=0; i<nf; i++)
  p[i]=9999;
}

int isHit(int data)
{
  hit=0;
  for(j=0; j<nf; j++)
  {
    if(p[j]==data)
    {
      hit=1;
      break;
    }
  }
  return hit;
}


void dispPages()
{
  for(k=0; k<nf; k++)
  {
  if(p[k]!=9999)
  printf(" %d",p[k]);
  }
}


void fifo()
{
  initialize();
  int m=0;
  for(i=0; i<n; i++)
  {
    printf("\nFor %d :",in[i]);
    if(isHit(in[i])==0)
     {
      p[m]=in[i];
      m=(m+1)%nf;
      pgfaultcnt++;
      dispPages();
     }
     else
       printf("No page fault");
  }
  printf("\nTotal no of page faults:%d",pgfaultcnt);
}


void lru()
{
  initialize();
  int least[50];
  for(i=0; i<n; i++)
  {
  printf("\nFor %d :",in[i]);
  if(isHit(in[i])==0)
  {
    for(j=0; j<nf; j++) //to check for element whether //least recently used
    {
      int pg=p[j];
      int found=0;
      for(k=i-1; k>=0; k--)
      {
        if(pg==in[k])
        {
          least[j]=k;
          found=1;
          break;
        }
        else
          found=0;
      }
      if(!found)
      least[j]=-9999;
    }
  int min=9999;
  int repindex;
  for(j=0; j<nf; j++) // insert element
  {
  if(least[j]<min)
  {
  min=least[j];
  repindex=j;
  }
  }
  p[repindex]=in[i];
  pgfaultcnt++;
  dispPages();
  }
  else
    printf("No page fault!");
    }
  printf("\nTotal no of page faults:%d",pgfaultcnt);
}


int main()
{
  int choice;
  while(1)
  {
    printf("\nPage Replacement Algorithms\n1.Enter data\n 2.FIFO\n 3.LRU\n 4.Exit\n Enter your choice:");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1:getData();
      break;
      case 2:fifo();
      break;
      case 3:lru();
      break;
      default:return 0;
      break;
    }
  }
}


Sample Output:
Page Replacement Algorithms
1. Enter data
2. FIFO
3. LRU
4. Exit
Enter your choice:1
Enter length of page reference sequence:8
Enter the page reference sequence: 2 1 3 2 3 0 1 3
Enter no of frames:3
Page Replacement Algorithms
1.Enter data
2.FIFO
3.LRU
4.Exit
Enter your choice:2
For 2 : 2
For 1 : 2 1
For 3 : 2 1 3
For 2 : No page fault
For 3 : No page fault
For 0 : 0 1 3
For 1 : No page fault
For 3 : No page fault
Total no of page faults:4
Page Replacement Algorithms
1. Enter data
2. FIFO
3. LRU
4. Exit
Enter your choice:3
For 2 : 2
For 1 : 2 1
For 3 : 2 1 3
For 2 : No page fault!
For 3 : No page fault!
For 0 : 2 0 3
For 1 : 1 0 3
For 3 :No page fault!
Total no of page faults:5
Page Replacement Algorithms
1. Enter data
2. FIFO
3. LRU
4. Exit
Enter your choice:4
