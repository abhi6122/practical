#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NEWNODE (struct info *)malloc(sizeof(struct info))
struct info
{
char fname[20];
int start, end, length;
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
freeSpace=dsize;
used=0;
}
int search()
{
int i;
for(i=0;i<dsize;i++)
{
if(D[i]==-2)
{
return i;
}
}
return(-1);
}
void makeDirEntry(char fname[],int start,int end,int length)
{
struct info *t;
t=NEWNODE;
strcpy(t->fname,fname);
t->start=start;
t->end=end;
t->length=length;
t->next=NULL;
if(E==NULL)
{
E=last=t;
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
f->next=s->next;
free(s);
used=used-length;
freeSpace=freeSpace+length;
}
void allocate()
{
char fname[10];
int length,blknum,i,cnt,start,end;
struct info *t;
printf("Enter Filename: ");
scanf("%s",fname);
printf("Enter Length of file: ");
scanf("%d",&length);
if( length > freeSpace)
{
printf("\nError: No Disk Space Available\n");
return;
}
printf("\nBlock Allocated\n");
blknum=search();
start=blknum;
D[blknum]=-1;
for(cnt=2; cnt<=length; cnt++)
{
D[blknum]=search();
blknum=D[blknum];
D[blknum]=-1;
}
end=blknum;
makeDirEntry(fname,start,end,length);
printf("\nDisk Status :");
for(i=0;i<dsize;i++)
{
printf(" %d",D[i]);
}
used=used+length;
freeSpace=freeSpace-length;
}
void deallocate()
{
struct info *f,*s;
char fname[10];
int length,i,cnt,blknum,tblknum;
printf("\nEnter Filename to delete= ");
scanf("%s",fname);
for(s=E;s!=NULL;s=s->next)
{
if(strcmp(s->fname,fname)==0)
{
blknum=s->start;
length=s->length;
for(cnt=1;cnt<=length;cnt++)
{
tblknum=D[blknum];
D[blknum]=-2;
blknum=tblknum;
}
deleteEntry(s);
printf("\nDisk Status :");
for(i=0;i<dsize;i++)
{
printf(" %d",D[i]);
}
return;
}
}
printf("\nInvalid Filename given to delete\n");
}
void displayDirFile()
{
struct info *t;
printf("\nFname\tStart\tEnd\tLength\n");
for(t=E;t!=NULL;t=t->next)
{
printf("%s\t%d\t%d\t%d\n",t->fname,t->start,t->end,t->length);
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
{ printf("\nMenu\n1.Allocate Space for newly created
file\n2.Deallocate Space for now Deleted
file\n3.Show used and free space on
disk\n4.Exit\n");
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