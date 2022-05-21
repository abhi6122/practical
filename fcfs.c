#include<stdio.h>
#define SIZE 100
int no_of_cylinder;
int request[SIZE];
int n;
int current_request;
int thm=0;
void accept()
{
int i;
printf("How many Cylinder :");
scanf("%d", &no_of_cylinder);
printf("How many Request :");
scanf("%d", &n);
for(i=0; i<n; i++)
{
printf("Enter Request : ");
scanf("%d", &request[i]);
}
printf("Enter Current Request:");
scanf("%d", &current_request);
}
void fcfs()
{
int cr,i,sub;
cr = current_request;
for(i=0; i<n; i++)
{
sub = cr - request[i];
if(sub<0)
{
sub = -sub;
}
thm = thm + sub;
cr = request[i];
}
printf("\n\nTotal Head Movement : %d \n", thm);
}
int main()
{
accept();
fcfs();
return 0;
}
