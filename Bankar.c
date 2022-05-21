#include<stdio.h>
#include<stdlib.h>

int allocation[10][10];
int max[10][10];
int available[10],work[10];
int need[10][10];
int finish[10];
int seq[10],scnt=0;
int no_of_processes,no_of_resources;
int check_process, request[10];

void accept()
{
	int i,j;

	printf("How many number of processes:");
	scanf("%d",&no_of_processes);

	printf("How many number of resources:");
	scanf("%d",&no_of_resources);

	printf("\nACCEPTING ALLOCATION MATRIX:\n");
	
	for(i=0;i<no_of_processes;i++)
	{
		for(j=0;j<no_of_resources;j++)
		{
			
			printf("For P%d enter resources for %c=",i,65+j);
			scanf("%d",&allocation[i][j]);

		}
	}
	
	printf("\nACCEPTING MAXIMUM MATRIX:\n");

	for(i=0;i<no_of_processes;i++)
	{
		for(j=0;j<no_of_resources;j++)
		{

			printf("For P%d enter resources for %c=",i,65+j);
			scanf("%d",&max[i][j]);

		}

	}
	
	printf("\nACCEPTING AVAILABILITY:\n");

	for(j=0;j<no_of_resources;j++)
	{
		
		printf("Available resource for %c=",65+j);
		scanf("%d",&available[j]);
		work[j]=available[j];
	
	}

}

void display()
{

	int i,j;

	printf("\nALLOCATION MATRIX\n");

	for(j=0;j<no_of_resources;j++)
	{
		
		printf("\t%c",65+j);

	}

	for(i=0;i<no_of_processes;i++)
	{
		
		printf("\nP%d\t",i);
		
		for(j=0;j<no_of_resources;j++)
		{
			
			printf("%d\t",allocation[i][j]);
		
		}
		printf("\n");

	}
	
	printf("MAXIMUM MATRIX\n");

	for(j=0;j<no_of_resources;j++)
	{
		
		printf("\t%c",65+j);
	
	}
	
	for(i=0;i<no_of_processes;i++)
	{
		
		printf("\nP%d\t",i);
		
		for(j=0;j<no_of_resources;j++)
		{

			printf("%d\t",max[i][j]);
		}
		printf("\n");

	}

	printf("NEED MATRIX\n");

	for(j=0;j<no_of_resources;j++)
	{

		printf("\t%c",65+j);
	
	}
	
	for(i=0;i<no_of_processes;i++)
	{

		printf("\nP%d\t",i);

		for(j=0;j<no_of_resources;j++)
		{

			printf("%d\t",need[i][j]);
		}
		printf("\n");

	}

	printf("AVAILABLE MATRIX\n");
	
	for(j=0;j<no_of_resources;j++)
	{

		printf("%c\t",65+j);
	
	}
	printf("\n");

	for(j=0;j<no_of_resources;j++)
	{

		printf("%d\t",available[j]);

	}
	printf("\n");

}

int check_request(int i)
{
	
	int j;
	
	for(j=0;j<no_of_resources;j++)
	{
			
			if(request[j]>need[i][j] || request[j] > available[j])
			return 0;

	}
	return 1;

}

void banker()
{
	
	int cnt=1,i=0,j;

	while(cnt<=2)
	{
		
		if(finish[i]==0)
		{
			
			if(check_need_with_available(i))
			{

				finish[i]=1;
				seq[scnt]=i;
				scnt++;

				for(j=0;j<no_of_resources;j++)
				{

					available[j]= available[j]+ allocation[i][j];
				
				}
			
			}

		}
		
		i=(i+1)%no_of_processes;
		if(i==0)
		cnt++;
	
	}

}

void calc_need()
{
	
	int i,j;

	for(i=0;i<no_of_processes;i++)
	{
		
		for(j=0;j<no_of_resources;j++)
		{
			
			need[i][j]=max[i][j]-allocation[i][j];
		
		}
	
	}

}

int check_need_with_available(int i)
{
	
	int j;

	for(j=0 ; j<no_of_resources; j++)
	{
		
		if( need[i][j] > available[j] )
		return 0;

	}
	return 1;

}




int main()
{

	int i,j;
	accept();
	calc_need();
	display();
	banker();

	if(scnt==no_of_processes)
	{

		printf("\nSystem is in Safe State....");
		printf("\nSafe Sequence=");
		printf("<");

		for(i=0;i<scnt;i++)
		{

			printf("P%d\t",seq[i]);
		
		}

		printf(">");

	}
	else
	{

		printf("\nGiven System is not in Safe State....");

	}

	printf("\nWhich process you want to check that it will be granted or not : ");
	scanf("%d",&check_process);

	if(check_process>no_of_processes)
	{
		
		printf("\nInvalid Process..Please Enter valid process\n");
		return 0;

	}

	for(j=0;j<no_of_resources;j++)
	{
		
		printf("Enter For P%d request resource %c=",check_process,65+j);
		scanf("%d",&request[j]);

	}

	if((check_request(check_process)))
	{

		printf("\nRequest for P%d will be granted\n",check_process);
	
	}
	else
	{
		
		printf("\n Request for P%d will not be granted\n",check_process);

	}
	return 0;

}