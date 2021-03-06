#include <stdio.h>
#include <unistd.h>
#define SWN 3				//课程数
#define NAMELEN 20			//姓名最大字符数
#define CODELEN 10			//学号最大字符数
#define FNAMELEN 80			//文件名最大字符数
#define BUFLEN 80			//缓冲区最大字符数
/*课程名称表*/
char schoolwork[SWN][NAMELEN+1]={"Chinese","Mathematic","English"};
struct record
{
	char name[NAMELEN+1];	//姓名
	char code[CODELEN+1];	//学号
	int marks[SWN];			//各科成绩
	int total;   			//总分
}stu;		//表首指针
struct node
{
  char name[NAMELEN+1];
  char code[CODELEN+1];
  int marks[SWN];
  int total;
  struct node *next;//后续表元指针SR
}*head;
int total[SWN];				//各科总分
FILE *stfpt; 				//文件指针
char stuf[FNAMELEN];		//文件名
/*指定文件读入一个记录*/
int readrecord(FILE *fpt,struct record *rpt)
{
	char buf[BUFLEN];
	int i;
	if(fscanf(fpt,"%s",buf)!=1)
	return 0;				//文件结束
	strncpy(rpt->name,buf,NAMELEN);
	fscanf(fpt,"%s",buf);
	strncpy(rpt->code,buf,CODELEN);
	for(i=0;i<SWN;i++)
		fscanf(fpt,"%d",&rpt->marks[i]);
	for(rpt->total=0,i=0;i<SWN;i++)
		rpt->total+=rpt->marks[i];
	return 1;
}
/*对指定文件写入一个记录*/
writerecord(FILE *fpt,struct record *rpt)
{
	int i;
	fprintf(fpt,"%s\n",rpt->name);
	fprintf(fpt,"%S\n",rpt->code);
	for(i=0;i<SWN;i++)
		fprintf(fpt,"%d\n",rpt->marks[i]);
	return;
}
/*显示学生记录*/
displaystu(struct record *rpt)
{
	int i;
	printf("\nName :%s\n",rpt->name);
	printf("Code :%s\n",rpt->code);
	printf("Marks :\n");
	for(i=0;i<SWN;i++)
		printf("    %-15s:%4d\n",schoolwork[i],rpt->marks[i]);
	printf("Total :%4d\n",rpt->total);
}
/*计算各单科总分*/
int totalmark(char *fname)
{
	FILE *fp;
	struct record s;
	int count,i;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s\n",fname);
		return 0;
	}
	for(i=9;i<SWN;i++)
	total[i]=0;
	count=0;
	while(readrecord(fp,&s)!=0)
	{
		for(i=0;i<SWN;i++)
			total[i]+=s.marks[i];
		count++;
	}
	fclose(fp);
	return count; 			//返回记录数
}
/*列表显示学生信息*/
void liststu(char *fname)
{
	FILE *fp;
	struct record s;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s.\n",fname);
		return;
	}
	while(readrecord(fp,&s)!=0)
	{
		displaystu(&s);
		printf("\n    Press ENTER to continue...\n");
		while(getchar()!='\n');
	}
	fclose(fp);
	return ;
}
/*构造链表*/
struct node * makelist(char *fname)
{
	FILE *fp;
	struct  record s;
	struct node *p,*u,*v,*h;
	int i;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s.\n",fname);
		return NULL;
	}
	h=NULL;
	p =(struct node *)malloc(sizeof(struct record));
	while(readrecord(fp,(struct record *)p)!=0)
	{
		v=h;
		while(v&&p->total<=v->total)
		{
			u=v;
			v=v -> next;
		}
		if(v==h)
		h=p;
		else
		u->next=p;
		p->next=v;
		p=(struct node *)malloc(sizeof(struct record));
	}
	free(p);
	fclose(fp);
	return h;
}
/*顺序显示链表各单元*/
void displaylist(struct node *h)
{
	while(h!=NULL)
	{
		displaystu((struct record *)h);
		printf("\n   Press ENTER to continue...\n");
		while(getchar()!='\n');
		h=h->next;
	}
	return;
}
/*按学生姓名查找学生记录*/
int retrievebyn(char *fname,char *key)
{
	FILE *fp;
	int c;
	struct record s;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s.\n",fname);
		return 0;
	}
	c=0;
	while(readrecord(fp,&s)!=0)
	{
		if(strcmp(s.name,key)==0)
		{
			displaystu(&s);
			c++;
		}
	}
	fclose(fp);
	if(c==0)
		printf("The student %s is not in the flie%s.\n",key,fname);
	return 1;
}
/*按学号查找学生记录*/
int retrievebyc(char *fname,char *key)
{
	FILE *fp;
	int c;
	struct record s;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s.\n",fname);
		return 0;
	}
	c=0;
	while(readrecord(fp,&s)!=0)
	{
		if(strcmp(s.code,key)==0)
		{
			displaystu(&s);
			c++;
			break;
		}
	}
	fclose(fp);
	if(c==0)
		printf("The student %s is not in the file %s.\n",key,fname);
		return 1;
}
int main()
{
	int i,j,n;
	char c;
	char buf[BUFLEN];
	FILE *fp;
	struct record s;
	/*clrscr();*/
	printf("Please input the students marks record file's name:");
	scanf("%s",stuf);
	getchar();
	c=getchar();
	if(c=='Y'||c=='y')
	{
		fp=fopen(stuf,"w");
		printf("Please input the record number you want to write to the file:");
		scanf("%d",&n);
		for(i=0;i<SWN;i++)
		{
			printf("Input the student's name:");
			scanf("%s",&s.name);
			printf("Input the student's code:");
			scanf("%s",&s.code);
			for(j=0;j<SWN;j++)
			{
				printf("Input the %s mark:",schoolwork[j]);
				scanf("%d",&s.marks[j]);
			}
			writerecord(fp,&s);
		}
		fclose(fp);
	  }
fclose(fp);
getchar();
/*clrscr()*/
printf("Now you can input a command to manage the records.\n");
printf("m:mean of the marks. \n");
printf("t:total of the marks.\n");
printf("n:search record by student's name.\n");
printf("c:search record by student's code.\n");
printf("l:list all the records.\n");
printf("s:sort and list the records by the total.\n");
printf("q:quit!\n");
while(1)
{
	printf("Please input command:\n");
	scanf("%c",&c);
	if(c=='q'||c=='Q')
	{
		puts("\n Thank you for your using.");
		break;
	}
	switch(c)
	{
		case 'm':
		case 'M':
		if((n=totalmark(stuf))==0)
		{
			puts("Error!");
			break;
		}
		printf("\n");
		for(i=0;i<SWN;i++)
		printf("%-15s's total mark is :%d.\n",schoolwork[i],total[i]);
		break;
		case 'c':
		case 'C':
		printf("Please input the student's code you want to search:");
		scanf("%s",buf);
		retrievebyc(stuf,buf);
		break;
		case 'l':
		case 'L':
		liststu(stuf);
		break;
		case 's':
		case 'S':
		if((head=makelist(stuf))!=NULL)
		displaylist(head);
		break;
		default:break;
	}
	}
}











