/* Experiment 7: Design, develop and implement a C/C++/Java program to simulate the working of Shortest remaining time and
Round Robin (RR) scheduling algorithms. Experiment with different quantum sizes for RR algorithm.*/
#include<stdio.h>
#include<stdlib.h>
struct proc {          //structure to hold the process information
  int id;
  int arrival;
  int burst;
  int rem;
  int wait;
  int finish;
  int turnaround;
  float ratio;
} process[10];

struct proc temp;
int no;
int chkprocess(int);
int nextprocess();
void roundrobin(int, int, int[], int[]);
void srtf(int);

main()
{
  int n,tq,choice;
  int bt[10],st[10],i,j,k;
  for(; ;)
  {
  printf("Enter the choice\n");
  printf(" 1. Round Robin\n 2. SRT\n 3. Exit\n");
  scanf("%d",&choice);
  switch(choice)
  {
    case 1: printf("Round Robin scheduling algorithm\n");
    printf("Enter number of processes:\n");
    scanf("%d",&n);
    printf("Enter burst time for sequences:\n");
    for(i=0;i<n;i++)
    {
    scanf("%d",&bt[i]);
    st[i]=bt[i]; //service time
    }
    printf("Enter time quantum:");
    scanf("%d",&tq);
    roundrobin(n,tq,st,bt);
    break;
    
  case 2: printf("\n\n---SHORTEST REMAINING TIME NEXT---\n\n ");
  printf("\n\n Enter the number of processes: ");
  scanf("%d", &n);
  srtf(n);
  break;
  case 3: exit(0);
  } // end of switch
 } // end of for
} //end of main()
void roundrobin(int n,int tq,int st[],int bt[])
{
  int time=0;
  int tat[10],wt[10],i,count=0,swt=0,stat=0,temp1,sq=0,j,k;
  float awt=0.0,atat=0.0;
  while(1)
  {
  for(i=0,count=0;i<n;i++)
  {
  temp1=tq;
  if(st[i]==0) // when service time of a process equals zero then {
    count++; //count value is incremented
  continue;
  }
  if(st[i]>tq) // when service time of a process greater than time quantumst[i]=st[i]-tq; // then time quantum value subtracted from service timeelse
  if(st[i]>=0)
  {
  temp1=st[i]; // temp1 stores the service time of a process st[i]=0; // making service time equals 0
  }
  sq=sq+temp1; // utilizing temp1 value to calculate turnaround timetat[i]=sq; // turn around time
  } //end of for
  if(n==count) // if all processes have completed their task
  break;
  } //end of while
  for(i=0;i<n;i++) // to calculate the wait time and turnaround time of each process {
    wt[i]=tat[i]-bt[i]; // waiting time = turnaround time - bursttime swt=swt+wt[i]; // summation of wait time
    stat=stat+tat[i]; // summation of turnaround time
  }
  awt=(float)swt/n; // average wait time
  atat=(float)stat/n; // average turnaround time
  printf("Process_no Burst time Wait time Turn around time\n");
  for(i=0;i<n;i++)
    printf("%d\t\t%d\t\t%d\t%d\n",i+1,bt[i],wt[i],tat[i]);
    printf("Avg wait time is %f\nAvg turn around time is %f\n",awt,atat);
}// end of Round Robin


int chkprocess(int s) // function to check process remaining time is zero or not{
  int i;
  for(i = 1; i<=s; i++)
  {
    if(process[i].rem != 0)
      return 1;
  }
  return 0;
} // end of chkprocess

int nextprocess() // function to identify the next process to be executed
{
  int min, l, i;
  min = 32000; //any limit assumed
  for(i = 1; i<=no; i++)
  {
    if( process[i].rem!=0 && process[i].rem < min)
    {
      min = process[i].rem;
      l = i;
    }
  }
  return l;
} // end of nextprocess


void srtf(int n)
{
  int i,j,k,time=0;
  float tavg,wavg;
  for(i = 1; i<=n; i++)
  {
    process[i].id = i;
    printf("\n\nEnter the arrival time for process %d: ", i);
    scanf("%d", &(process[i].arrival));
    printf("Enter the burst time for process %d: ", i);
    scanf("%d", &(process[i].burst));
    process[i].rem = process[i].burst;
  }
  for(i = 1; i<=n; i++)
  {
    for(j = i + 1; j<=n; j++)
    {
      if(process[i].arrival > process[j].arrival) {  //sort arrival time of a process
        temp = process[i];
        process[i] = process[j];
        process[j] = temp;
      }
    }
  }
  no = 0;
  j = 1;
  while(chkprocess(n)==1)
  {
    if(process[no + 1].arrival==time)
    {
      while(process[no+1].arrival==time)
      no++;
      if(process[j].rem==0)
        process[j].finish=time;
        j = nextprocess();
    }
    if(process[j].rem!= 0) {       // to calculate the waiting time of a process
      process[j].rem--;
      for(i = 1; i<=no; i++)
      {
        if(i!=j && process[i].rem!=0)
          process[i].wait++;
        }
    }
    else
    {
      process[j].finish=time;
      j=nextprocess();
      time--;
      k=j;
    }
    time++;
    }
  process[k].finish = time;
  printf("\n\n\t\t\t---SHORTEST REMAINING TIME FIRST---");
  printf("\n\n Process Arrival Burst Waiting Finishing turnaround Tr/Tb \n");printf("%5s %9s %7s %10s %8s %9s\n\n", "id", "time", "time", "time", "time", "time");for(i = 1; i<=n; i++)
  {
    process[i].turnaround =process[i].wait + process[i].burst; // calc of turnaround process[i].ratio = (float)process[i].turnaround / (float)process[i].burst; printf("%5d %8d %7d %8d %10d %9d %10.1f ", process[i].id, process[i].arrival, process[i].burst, process[i].wait, process[i].finish,
    process[i].turnaround,process[i].ratio);
    tavg=tavg+process[i].turnaround; //summation of turnaround time
    wavg=wavg+process[i].wait; //summation of waiting time
    printf("\n\n");
  }
  tavg=tavg/n; // average turnaround time
  wavg=wavg/n; // average wait time
  printf("tavg=%f\n wavg=%f\n",tavg,wavg);
}// end of srtf


Output
Enter the choice
 1. Round Robin
 2. SRT
 3. Exit
1
Round Robin scheduling algorithm
Enter number of processes:
3
Enter burst time for sequences:
24
3
3
Enter time quantum:4
Process_no Burst time Wait time Turn around time
1 24 6 30
2 3 4 7
3 3 7 10
Avg wait time is 5.666667
Avg turn around time is 15.666667
Enter the choice
 1. Round Robin
 2. SRT
 3. Exit
2
---SHORTEST REMAINING TIME NEXT---
Enter the number of processes: 4
Enter the arrival time for process 1: 0
Enter the burst time for process 1: 8
Enter the arrival time for process 2: 1
Enter the burst time for process 2: 4
Enter the arrival time for process 3: 2
Enter the burst time for process 3: 9
Enter the arrival time for process 4: 3
Enter the burst time for process 4: 5
---SHORTEST REMAINING TIME FIRST---
 Process Arrival Burst Waiting Finishing turnaround Tr/Tb
 id time time time time time
 1 0 8 9 17 17 2.1
 2 1 4 0 5 4 1.0
 3 2 9 15 26 24 2.7
 4 3 5 2 10 7 1.4
tavg=13.000000
wavg=6.500000
Enter the choice
 1. Round Robin
 2. SRT
 3. Exit
3
