#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NEWNODE (struct info *)malloc(sizeof(struct info))
struct info
{
char fname[20];
int start,length;
struct info *next;
};
struct info *E=NULL,*last=NULL;
int *D=NULL;
int dsize;
int used;
int freeSpace;
void init_disk()
{
int i;
D=(int *)malloc(sizeof(int)*dsize);
for(i=0;i<dsize;i++)
{
D[i]=-2;
}
used=0;
freeSpace=dsize;
}
int search(int length)
{
int i,cnt,flag,blknum;
for(i=0;i<dsize;i++)
{
if(D[i]==-2)
{
flag=1;
blknum=i;
for(cnt=1; cnt<=length; cnt++)
{
if(D[i]==-2)
{
i++;
}
else
{
flag=0;
break;
}
}
if(flag==1)
return blknum;
}
}
return -1;
}
void makeDirEntry(char fname[],int blknum,int length)
{
struct info *t;
t=NEWNODE;
strcpy(t->fname,fname);
t->start=blknum;
t->length=length;
t->next=NULL;
if(E==NULL)
{
E=t;
last=t;
}
else
{
last->next=t;
last=last->next;
}
}
void deleteEntry(struct info *s)
{
struct info *f;
int length=s->length;
if(s==E)
{
E=E->next;
free(s);
used=used-length;
freeSpace=freeSpace+length;
return;
}
f=E;
while(f->next!=s)
{
f=f->next;
}
if(f->next == last) # you are going to delete last node
{
last = f;
}
f->next=s->next;
free(s);
used=used-length;
freeSpace=freeSpace+length;
}
void assignBlock(int blknum,int length)
{
int cnt;
for(cnt=1;cnt<=length;cnt++)
{
D[blknum]=1;
blknum++;
}
}
void freeBlock(int blknum,int length)
{
int cnt;
for(cnt=1;cnt<=length;cnt++)
{
D[blknum]=-2;
blknum++;
}
}
void allocate()
{
char fname[10];
int length,blknum,i;
printf("Enter Filename: ");
scanf("%s",fname);
printf("Enter Length of file: ");
scanf("%d",&length);
blknum=search(length);
if(length > freeSpace || blknum==-1)
{
printf("\nError: No Disk Space Available\n");
return;
}
printf("\nBlock Allocated\n");
assignBlock(blknum,length);
used=used+length;
freeSpace=freeSpace-length;
makeDirEntry(fname,blknum,length);
printf("Disk Status :");
for(i=0;i<dsize;i++)
{
printf(" %d",D[i]);
}
}
void deallocate()
{
struct info *s;
char fname[10];
int length,i,blknum;
printf("\nEnter Filename to delete= ");
scanf("%s",fname);
for(s=E;s!=NULL;s=s->next)
{
if(strcmp(s->fname,fname)==0)
{
blknum=s->start;
length=s->length;
freeBlock(blknum,length);
printf("Disk Status :");
for(i=0;i<dsize;i++)
{
printf(" %d",D[i]);
}
deleteEntry(s);
return;
}
}
printf("\nInvalid Filename given to delete\n");
}
void displayDirFile()
{
struct info *s;
printf("\nFname\tStart\tLength\n");
for(s=E;s!=NULL;s=s->next)
{
printf("%s\t%d\t%d\n",s->fname,s->start,s->length);
}
printf("\nUsed Block=%d",used);
printf("\nFree Block=%d\n",freeSpace);
}
int main()
{
int choice;
printf("\nWhat is Disk Size: ");
scanf("%d",&dsize);
init_disk();
while(1)
{
printf("\nMenu\n1.Allocate Space for newly created
file \n 2.Deallocate Space for now Deleted
file \n 3.Show used and free space on
disk \n 4.Exit\n");
printf("\nEnter Your choice:");
scanf("%d",&choice);
switch(choice)
{
case 1: allocate();
break;
case 2: deallocate();
break;
case 3: displayDirFile();
break;
case 4: exit(0);
}
}
}