#include<stdio.h>
#define SIZE 100
int no_of_cylinder;
int request[SIZE],copy[SIZE];
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
printf("\n");
}
void copy_request()
{
int i;
for(i=0;i<n;i++)
{
copy[i] = request[i];
}
}
int get_shortest(int cr)
{
int i;
int min=9999;
int k;
int diff;
for(i=0; i<n; i++)
{
if(copy[i] !=-1)
{
diff = cr -copy[i];
if(diff<0)
{
diff=-diff;
}
if(diff<min)
{
k=i;
min = diff;
}
}
}
copy[k]=-1;
return k;
}
void sstf()
{
int cr,i,sub,cnt;
cr = current_request;
for(cnt=1;cnt<=n; cnt++)
{
i = get_shortest(cr);
printf("Processing Request : %d \n", request[i]);
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
bubble_sort();
copy_request();
sstf();
return 0;
}