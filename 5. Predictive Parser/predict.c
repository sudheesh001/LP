#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char ip_sym[15],ip_ptr=0;
void e_prime();
void t();
void e();
void f();
void t_prime();
void advance();
void e()
{
	printf("\n\t\tE->TE");
	t();
	e_prime();
}
void e_prime()
{
	if(ip_sym[ip_ptr]=='+')
	{
		printf("\n\t\tE'->TE'");
		advance();
		t();
		e_prime();
	}
	else
		printf("\n\t\tE'->E");
}
void t()
{
	printf("\n\t\tE'->FT'");
	f();
	t_prime();
}
void t_prime()
{
	if(ip_sym[ip_ptr]=='*')
	{
		printf("\n\t\tT'->*FT");
		advance();
		f();
		t_prime();
	}
	else
		printf("\n\t\tT->E");
}
void f()
{
	if((ip_sym[ip_ptr]=='i')||(ip_sym[ip_ptr]=='I'))
	{
		printf("\n\t\tF->i");
		advance();
	}
	else
	{
		if(ip_sym[ip_ptr]==')')
		{
			advance();
			printf("\n\t\tF->(E)");
		}
		else
		{
			printf("\n\t\tSyntax Error");			
			exit(1);
		}
	}
}
void advance()
{
	ip_ptr++;
}
int main()
{
	int i;
	printf("\n\n\n\n");
	printf("\n\tGrammar without left recursion");
	printf("\n\t\tE->TE'\n\t\tE'->+TE'/e\n\t\tT->FT'");
	printf("\n\t\tT'->*FT'/e\n\t\tF->(e)/i");
	printf("\n\t\tEnter thye input symbol:");
	gets(ip_sym);
	printf("\n\tSequence of production rules");
	e();
	for(i=0;i<strlen(ip_sym);i++)
	{
		if(ip_sym[i]!='+'&&ip_sym[i]!='*'&&ip_sym[i]!='('&&ip_sym[i]!=')'&&ip_sym[i]!='i'&&ip_sym[i]!='I')
		{
			printf("\n\tSyntax Error");
			break;
		}
	}
	return 0;
}
