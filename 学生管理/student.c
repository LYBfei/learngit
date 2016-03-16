#include<stdio.h>
#define SWN 3				//课程数
#define NAMELEN 20			//姓名最大字符数
#define CODELEN 10			//学号最大字符数 
#define FNAMELEN 80			//文件名最大字符数
#define BUFFLEN 80			//缓冲区最大字符数
/*课程名称表*/
char schoolwork[SWN][NAMELEN+1]={"Chinese","Mathematic","English"};
struct record
{
	char name[NAMELEN+1];	//姓名
	char code[CODELEN+1];	//学号
	int marks[SWN];			//各科成绩
	int total;   			//总分
	struct node *next;    	//后续表元指针
}*head;						//表首指针
int total[SWN];				//各科总分
FILE *stfpt; 				//文件指针
char stuf[FNAMELEN];		//文件名
/*指定文件读入一个记录*/
int radrecord(FILE *fpt,struct record *rpt)
{
	char buf[BUFFLEN];
	int i;
	if(fscanf(fpt,"%s",buf)!=1)
	return 0;				//文件结束
	strncpy(rpt->name,buf,NAMELEN);
	fscanf(fpt,"%s",buf);
	strncpy(rpt->code,buf,CODELEN);
	for(i=0;i<SWN;i++)
		fscanf(ftp,"%d",&rpt->marks[i]);
	for(rpt->total=0,i=0;i<SWN;i++)
		rpt->total+=rpt->marks[i];
	return 1;
}
/*对指定文件写入一个记录*/
writerecord(FILE *fpt,struct record *rpt)
{
	int i;
	fprintf(fpt,"%s\n",rpt->name);
	fprintf(ftp,"%S\n",rpt->code);
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
struct node *makelist(char *fname)
{
	FILE *fp;
	struct record s;
	struct node *p,*u,*v,*h;
	int i;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s.\n",fname);
		return NULL;
	}
	h=NULL;
	p=(struct node*)malloc(sizeof(struct node));
	while(readrecord(fp,(struct record *)p)!=0)
	{
		v=h;
		while(v&&p->total<=v->total)
		{
			u=v;
			v=v->next;
		}
		if(v==h)
		h=p;
		else
		u->next=p;
		p->next=v;
		p=(struct node *)malloc(sizeof(struct node));
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
int retrievebyn(chae *fname,char *key)
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
main()













