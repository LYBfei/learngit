#include<stdio.h>
//#include<string.h>
void main()
{
	int Password=0,Number=0,Price=58,i=0;
	while(Password!=1234)
	{
		if(i>3)
		return;
		i++;
		printf("please input Password:");
		scanf("%d",&Password);
		
	}
	i=0;
	while(Number!=Price)
	{
		do
		{
			printf("Please input a number between 1 and 100: ");
			scanf("%d",&Number);
			printf("your input number is%d\n",Number);
		}
		while(!(Number>=1&&Number<=100))
		;
	    if(Number>=90)
		{
			printf("too bigger!Press any key to try again!\n");
		}
		else if(Number>=70&&Number<=90)
		{
			printf("Bigger!\n");
		}
		else if(Number>=1&&Number<=30)
		{
			printf("Too Small！Press any key to try again!\n");
		}
		else if(Number>30&&Number<=50)
		{
			printf("Small!Press any key to try again!\n");
		}
		else
		{
			if(Number==Price)
			{
				printf("OK!you are ringt!bye bye!\n");
			}
			else if(Number<Price||Number>Price)
				printf("sorry, Press any key to try again!\n");
			//getch();
		}
	}
}
