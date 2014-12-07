#include<stdio.h>

void bubblesort(int a[], int n)
{
	int i=0;
	for(i; i<n; i++)
	{
		for(j=i; j<n; j++)
		{
			if(a[i]<a[j])
			{
				int temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
}

void main()
{
	int i,j=1,k=2,flag;
	for(i=0;i<=4;i++)
	{
		k=i+j;
	}
	flag=5;
	if(flag==10)
	{
		printf("Hello Students\n");
	}
	return 0;
}