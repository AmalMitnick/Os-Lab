#include<stdio.h>
struct process
{
 int pno;
 int at;
 int bt;
 int wt;
 int ct;
 int tt;
}p[10],temp;
void main()
{
 int i,j,n,b=0;
 float sumtt=0,sumwt=0;
 printf("Enter the number of process\n");
 scanf("%d",&n);
 for(i=0;i<n;i++)
 {
  p[i].pno=i+1;
  printf("Enter the arrival time of %d process\n",i+1); 
  scanf("%d",&p[i].at);
  printf("Enter the burst time of %d process\n",i+1); 
  scanf("%d",&p[i].bt);
 }
 for(i=0;i<n-1;i++)
 {
  for(j=0;j<n-i-1;j++)
  {
   if(p[j].at>p[j+1].at)
   {
     temp=p[j];
     p[j]=p[j+1];
     p[j+1]=temp;    
   }
  }
 }
 for(i=0;i<n;i++)
 {
  b=b+p[i].bt;
  p[i].ct=b;
  p[i].tt=p[i].ct-p[i].at;
  p[i].wt=p[i].tt-p[i].bt;
  sumtt+=p[i].tt;
  sumwt+=p[i].wt;
 }
 printf("Pno\tAT\tBT\tCT\tTT\tWT\n");
 for(i=0;i<n;i++)
 {
  printf("%d\t",p[i].pno);
  printf("%d\t",p[i].at);
  printf("%d\t",p[i].bt);
  printf("%d\t",p[i].ct);
  printf("%d\t",p[i].tt);
  printf("%d\n",p[i].wt);
 }
 printf("Average waiting time is %f\n",sumwt/n);
 printf("Average turnaround time is %f\n",sumtt/n);
}
