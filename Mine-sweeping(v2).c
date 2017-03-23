#include<stdio.h>
#include<stdlib.h>//为使用srand函数
#include<time.h>//为使用time函数
#include<conio.h>//为使用getch函数
#include<string.h>//为使用memset函数
#include<conio.h>//for func getch()
#define M 8
#define N 6
#define NUM 10
int square[M][N]={0};
int check(int,int);
int checkpoint(int,int);
void output(void);
int main(void)
{
	int i,m,n,x,y;
	char ch;
	srand((unsigned)time(NULL));
		entrance:for(i=0;i<NUM;)//使用随机数（坐标）布置雷田
	{
		m=(rand()%M);
		n=(rand()%N);
		if(square[m][n]==0)
		{
			square[m][n]=50;
			i++;
		}
	}
	x=4;
	y=4;
	square[x][y]+=200;
	for(m=0;m<M;m++)
	{
		for(n=0;n<N;n++)
		{
			if(square[m][n]>=200)
				printf(" X");
			else
			printf("■");
		}
		printf("\n");
	}
	printf("use a,s,w,d to move,enter j to check the point,enter q to quit\n");
	for(;;)
	{
		ch=getch();
		if(ch=='a')
		{
			if(y>0)
			{
				square[x][y]-=200;
				y--;
				square[x][y]+=200;
				output();
			}
			else
				continue;
		}
		else if(ch=='w')
		{
			if(x>0)
			{
				square[x][y]-=200;
				x--;
				square[x][y]+=200;
				output();
			}
			else
				continue;
		}
		else if(ch=='d')
		{
			if(y<N-1)
			{
				square[x][y]-=200;
				y++;
				square[x][y]+=200;
				output();
			}
			else
				continue;
		}
		else if(ch=='s')
		{
			if(x<M-1)
			{
				square[x][y]-=200;
				x++;
				square[x][y]+=200;
				output();
			}
			else
				continue;
		}
		else if(ch=='j')
		{
			square[x][y]-=200;
			m=x;
			n=y;
			if(square[m][n]==50)//输入的坐标上有雷
		    {
				printf("GAME OVER\n");
				for(m=0;m<M;m++)//失败后显示雷田情况
				{
				   for(n=0;n<N;n++)
				   {
					   if(square[m][n]==50)
						  printf("△");
					   else if(square[m][n]<9&&square[m][n]>0)
						  printf("%-2d",square[m][n]);
					   else if(square[m][n]==0)
						  printf("■");
					   else 
						  printf("●");
				   }
				   printf("\n");
				}
				printf("是否继续(y/n)?\n");
				if(getch()=='y')//非回显函数
				{
					system("cls");//清屏
					memset(square,0,sizeof(square));//清空数组数据
					goto entrance;//返回程序开头
				}
				else
					break;
			}
			else
			{
				check(m,n);//检测该点周围情况
				square[x][y]+=200;
				output();
			}
		}
		else if(ch=='q')
			return 0;
	}
}
int checkpoint(int m,int n)//检测该点是否有雷
{
	if(m<0||m>M-1||n<0||n>N-1)
		return 0;//越界情况
	if(square[m][n]==50)
	    return 1;//有雷则数量为1
	else
		return 0;//无雷
}
int check(int m,int n)//检测该点
	//其中有雷的值为50，检测过的点值为48
{
	int sum=0;
	if(m<0||m>M-1||n<0||n>N-1)
		return 0;//越界情况
	if(square[m][n]!=48)//普通情况
		{
			sum=sum+checkpoint(m-1,n-1);
			sum=sum+checkpoint(m-1,n);
			sum=sum+checkpoint(m-1,n+1);
			sum=sum+checkpoint(m,n-1);
			sum=sum+checkpoint(m,n+1);
			sum=sum+checkpoint(m+1,n-1);
			sum=sum+checkpoint(m+1,n);
			sum=sum+checkpoint(m+1,n+1);
			if(sum==0)
			{
				square[m][n]=48;//将周围无雷的格子标为48 
				check(m-1,n-1);
				check(m-1,n);
				check(m-1,n+1);
				check(m,n-1);
				check(m,n+1);
				check(m+1,n-1);
				check(m+1,n);
				check(m+1,n+1);
			}
			else
			square[m][n]=sum;//该点数值为周围雷数
	    }
	return 1;
}
void output(void)
{
	int checksum,m,n;
	system("cls");//清屏
	for(checksum=0,m=0;m<M;m++)//输出更新后的雷田
	{
		for(n=0;n<N;n++)
		{
			if(square[m][n]<200)
			{
				if(square[m][n]==48)
					printf("●");
				else if(square[m][n]<9&&square[m][n]!=0)
					printf("%-2d",square[m][n]);
				else
				{
					printf("■");
					checksum++;//统计未点开的方块数
				}
			}
			else
			{
				if(square[m][n]==200||square[m][n]==250)
					checksum++;
				printf(" X");
			}
		}
		printf("\n");
	}
	printf("use a,s,w,d to move,enter j to check the point,enter q to quit\n");
	if(checksum==NUM)//未点开的方块数等于雷数，胜利
	printf("YOU WIN\n");
}
