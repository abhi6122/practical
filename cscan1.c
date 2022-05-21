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
void bubble_sort()
{
int i,j,t;
for(i=n-1; i>0; i--)
{
for(j=0; j<i; j++)
{
	if(request[j]>request[j+1])
{
t = request[j];
request[j] = request[j+1];
request[j+1] = t;
}
}
}
printf("\nSorted :");
for(i=0;i<n;i++)
{
printf("%d ", request[i]);
}
printf("\n\n");
}
void cscan()
{
int cr,i,k,sub,cnt;
for(k=0;k<n;k++)
{
if(request[k]>current_request)
break;
}
thm = (no_of_cylinder-1-current_request)+(0+request[k-1]);
printf("\n\nTotal Head Movement : %d \n", thm);
}
int main()
{
accept();
bubble_sort();
cscan();
return 0;
}