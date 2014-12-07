#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct u_tab
{
	int no;
	char type[20];
	char name[20];
}u_tab[200];

struct lit
{
	int no;
	char name[20];
}lit_tab[100];

struct id
{
	int no;
	char name[20];
}id_tab[100];

FILE *fp1,*fp2;

char buff[80];

int lit_cnt=0,id_cnt=0,u_cnt=0;

int search_idtab(char temp[20])
{
	int i;

	for(i=0;i<id_cnt;i++)
	{
		if(strcmp(temp,id_tab[i].name)==0)
			return(i);
	}
	return(-1);
}

int search_littab(char temp[20])
{
	int i;
	for(i=0;i<lit_cnt;i++)
	{
		if(strcmp(temp,lit_tab[i].name)==0)
			return(i);
	}
	return(-1);
}

void lex(char source[80])
{
	int i,id,lit=0,term=0,l=0,terminal_no,res;

	char temp[20],terminal[20],str[80];

	fp1=fopen(source,"r");
	if(fp1==NULL)
	{
		printf("\n\n source file not found::");
		exit(0);
	}

	while(fgets(str,80,fp1)!=NULL)
	{

		for(i=0;str[i]!='\0';i++)
		{
			id=lit=term=l=0;

			strcpy(temp,"");

			if(str[i]=='{'||str[i]=='}'||str[i]=='['||str[i]==']')
			{
				temp[l]=str[i];
				l++;
				temp[l]='\0';
			}

			if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/')
			{
				temp[l]=str[i];
				l++;
				temp[l]='\0';
			}


			if(str[i]==','||str[i]=='.'||str[i]==':'||str[i]=='"')
			{
				temp[l]=str[i];
				l++;
				temp[l]='\0';
			}

			if(str[i]=='#'||str[i]=='%'||str[i]=='('||str[i]==')')
			{
				temp[l]=str[i];
				l++;
				temp[l]='\0';
			}

			if(str[i]=='<')
			{
				temp[l]=str[i];
				l++;
				if(str[i+1]=='=')
				{
					temp[l]=str[i+1];
					i++;
					l++;
				}
				temp[l]='\0';
			}
			else if(str[i]=='=')
			{
				temp[l]=str[i];
				l++;
				if(str[i+1]=='='||str[i+1]=='>')
				{
					temp[l]=str[i+1];
					l++;
					i++;
				}
				temp[l]='\0';
			}
			else if(str[i]=='>')
			{
				temp[l]='>';
				l++;
				temp[l]='\0';
			}
			else if(isalpha(str[i]))
			{
				temp[l]=str[i];
				l++;
				i++;
				while( isalpha(str[i]) || isdigit(str[i]) || str[i]=='_'||str[i]=='.')
				{
					temp[l]=str[i];
					i++;
					l++;
				}
				i--;
				temp[l]='\0';
				id=1;
			}
			else if(isdigit(str[i]))
			{
				temp[l]=str[i];
				l++;
				i++;
				while(isdigit(str[i]))
				{
					temp[l]=str[i];
					l++;
					i++;
				}
				i--;
				temp[l]='\0';
				lit=1;
			}
			fp2=fopen("term_file.txt","r");

			if(fp2==NULL)
			{
				printf("\n\n terminal file not found::");
				exit(0);
			}
			while(fscanf(fp2,"%s%d",terminal,&terminal_no)!=EOF)
			{
				if(strcmp(terminal,temp)==0)
				{
					strcpy(u_tab[u_cnt].name,temp);
					strcpy(u_tab[u_cnt].type,"term");
					u_tab[u_cnt].no=terminal_no;
					term=1;
					u_cnt++;
					break;
				}
			}
			fclose(fp2);
			if(term!=1&&id==1)
			{
				res=search_idtab(temp);

		 if(res==-1)//not found
		 {
		 	strcpy(u_tab[u_cnt].name,temp);
		 	strcpy(u_tab[u_cnt].type,"ID");
		 	u_tab[u_cnt].no=id_cnt;

		 	strcpy(id_tab[id_cnt].name,temp);
		 	id_tab[id_cnt].no=id_cnt;

		 	id_cnt++;
		 	u_cnt++;
		 }
		 else
		 {
		 	strcpy(u_tab[u_cnt].name,temp);
		 	strcpy(u_tab[u_cnt].type,"ID");
		 	u_tab[u_cnt].no=res;
		 	u_cnt++;
		 }
		}

		if(term!=1&&lit==1)
		{
			res=search_littab(temp);
		 if(res==-1)//not found
		 {
		 	strcpy(u_tab[u_cnt].name,temp);
		 	strcpy(u_tab[u_cnt].type,"lit");
		 	u_tab[u_cnt].no=lit_cnt;

		 	strcpy(lit_tab[lit_cnt].name,temp);
		 	lit_tab[lit_cnt].no=lit_cnt;

		 	lit_cnt++;
		 	u_cnt++;
		 }
		 else
		 {
		 	strcpy(u_tab[u_cnt].name,temp);
		 	strcpy(u_tab[u_cnt].type,"lit");
		 	u_tab[u_cnt].no=res;
		 	u_cnt++;
		 }
		}
  }//for
}
}

void printUniver()
{ int i;

	printf("\n\n UNIVERSAL SYMB TABLE");
	printf("\nTERMINAL\tTYPE\tNO");
	for(i=0;i<u_cnt;i++)
	{
		printf("\n%s\t\t%s\t%d",u_tab[i].name,u_tab[i].type,u_tab[i].no);
	}
}

void printLit()
{
	int i;

	printf("\n\n literal table\n");
	printf("\nliteral\tNO");
	for(i=0;i<lit_cnt;i++)
	{
		printf("\n%s\t%d",lit_tab[i].name,lit_tab[i].no);
	}
}

int main()
{
	char source[20];
	printf("\n\n enter source file name::");
	scanf("%s",source);
	lex(source);
	printUniver();
	printLit();
	return 0;
}