#include<stdio.h> 
#include<string.h> 
int main()
￼{
	char t[5],nt[10],p[5][5],first[5][5],temp;
	int i,j,not,nont,k=0,f=0;
	clrscr();
	printf("\nEnter the no. of Non-terminals in the grammer:"); scanf("%d",&nont);
	printf("\nEnter the Non-terminals in the grammer:\n");
	for(i=0;i<nont;i++)
	{
		scanf("\n%c",&nt[i]); }
		printf("\nEnter the no. of Terminals in the grammer: ( Enter e for absiline ) ");
		scanf("%d",&not);
		printf("\nEnter the Terminals in the grammer:\n"); 
		for(i=0;i<not||t[i]=='$';i++)
		{
			scanf("\n%c",&t[i]);
		} 
		for(i=0;i<nont;i++)
		{
			p[i][0]=nt[i];
			first[i][0]=nt[i]; 
		}
		printf("\nEnter the productions :\n");
		for(i=0;i<nont;i++)
		{
			scanf("%c",&temp);
			printf("\nEnter the production for %c ( End the production with '$' sign ) :",p[i][0]);
				for(j=0;p[i][j]!='$';)
				{
					j+=1;
					scanf("%c",&p[i][j]); 
				}
		} 
		for(i=0;i<nont;i++) 
		{
			printf("\nThe production for %c -> ",p[i][0]); 
			for(j=1;p[i][j]!='$';j++) 
			{
				
			} 
			getch();
		}
	}