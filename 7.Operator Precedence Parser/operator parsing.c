#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

char str[20],stk[20],pstk[20];
int tos=-1,flag=0,ptr=0,rm=-1,i,j;
char q[9][9]={
	{'>','>','<','<','<','<','>','<','>'},
	{'>','>','<','<','<','<','>','<','>'},
	{'>','>','>','>','<','<','>','<','>'},
	{'>','>','>','>','<','<','>','<','>'},
	{'>','>','<','<','<','<','>','<','>'},
	{'<','<','<','<','<','<','=','<','E'},
	{'>','>','>','>','>','E','>','E','>'},
	{'>','>','>','>','>','E','>','E','>'},
	{'<','<','<','<','<','<','E','<','A'},
};
char c[9]={'+','-','*','/','^','a','(',')','$'};

void pushin(char a)
{
	tos++;
	stk[tos]=a;
}

char popout()
{
	char a;
	a=stk[tos];
	tos--;
	return(a);
}

int find(char a)
{
	switch(a)
	{
		case'+':return 0;
		case'-':return 1;
		case'*':return 2;
		case'/':return 3;
		case'^':return 4;
		case'(':return 5;
		case')':return 6;
		case'a':return 7;
		case'$':return 8;
	}
	return-1;
}

void display(char a)
{
	printf("\n SHIFT %c",a);
}

void display1(char a)
{
	if(a!='(')
	{
		if(isalpha(a))
			printf("\n REDUCE E--> %c",a);
		else if(a==')')
			printf("\n REDUCE E-->(E)");
		else
			printf("\n REDUCE E-->E %c E",a);
	}
}

int rel(char a,char b,char d)
{
	if(isalpha (a))
		a='a';
	if(isalpha(b))
		b='a';
	if(q[find(a)][find(b)]==d)
		return 1;
	else
		return 0;
}

int main()
{
	printf("\n\n\t The productions used are:\n\t");
	printf("E-->E*E/E+E/E^E/E*E/E-E\n\tE-->E/E \n\tE-->a/b/c/d/e.../z");
	printf("\n\t Enter an expression that terminals with $:");
	fflush(stdin);
	i=-1;
	while(str[i]!='$')
	{
		i++;
		scanf("%c",&str[i]);
	}

	for(j=0;j<i;j++)
	{
		if((str[j]=='(')||(str[j]==')')||(str[j+1]=='(')||(str[j+1]==')'))
		{}
		else if (((isalpha(str[j])==0)&&(isalpha(str[j+1])==0))||((isalpha(str[j])!=0)&&(isalpha(str[j+1])!=0)))
		{
			printf("ERROR");
			exit(0);
		}
	}
	if((((isalpha(str[0]))!=0)||(str[0]=='('))&&(((isalpha(str[i-1]))!=0)||(str[i-1]==')')))
	{
		pushin('$');
		printf("\n\n\n\t+\t-\t*\t/\t^\ta\t(\t)\t$\n\n");
		for(i=0;i<9;i++)
		{
			printf("%c",c[i]);
			for(j=0;j<9;j++)
				printf("\t%c",q[i][j]);
			printf("\n");
		}

		while(1)
		{
			if(str[ptr]=='$' && stk[tos]=='$')
			{
				printf("\n\n\t ACCEPT!");
				break;
			}
			else if(rel(stk[tos],str[ptr],'<')||rel(stk[tos],str[ptr],'=='))
			{
				display(str[ptr]);
				pushin(str[ptr]);
				ptr++;
			}
			else if(rel(stk[tos],str[ptr],'>'))
			{
				do
				{
					rm++;
					pstk[rm]=popout();
					display1(pstk[rm]);
				}

				while(!rel(stk[tos],pstk[rm],'<'));
			}

			else
			{
				printf("\n\n\t NOT ACCEPTED!!!!!!!");
				exit(1);
			}
		}
	}
	else
	{
		printf("ERROR");
	}
	return 0;
}