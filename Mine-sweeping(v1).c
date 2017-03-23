#include<stdio.h>
#include<stdlib.h>//为使用srand函数
#include<time.h>//为使用time函数
#include<conio.h>//为使用getch函数
#include<string.h>//为使用memset函数
int square[8][6]={0};
void check(int,int);
int checkpoint(int,int);

int main(void)
{
	int i,m,n;
	srand((unsigned)time(NULL));
		entrance:for(i=0;i<10;)//使用随机数（坐标）布置雷田
	{
		m=(rand()%7+1);
		n=(rand()%5+1);
		if(square[m][n]==0)
		{
			square[m][n]=50;
			i++;
		}
	}
	for(m=0;m<8;m++)
	{
		for(n=0;n<6;n++)
			printf("■");
		printf("\n");
	}
	printf("请输入坐标(输入q退出)\n");
	while(scanf("%d %d",&m,&n)==2)//检测输入坐标情况
	{
		if(m>7||n>5||m<0||n<0)//超出边界
		{
			printf("输入无效，请重新输入\n");
			continue;
		}
		if(square[m][n]==50)//输入的坐标上有雷
		{
		    printf("GAME OVER\n");
			for(m=0;m<8;m++)//失败后显示雷田情况
	       {
		       for(n=0;n<6;n++)
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
			getchar();
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
		    check(m,n);//检测该点周围情况
	}
	return 0;
}

int checkpoint(int m,int n)//检测该点是否有雷
{
	int sum=0;
	if(square[m][n]==50)
		sum=1;//有雷则数量为1
	return sum;
}

void check(int m,int n)//检测该点
	//其中有雷的值为50，检测过的点值为48
{
	int sum=0,checksum;
	if(m==0)
	{
		if(n==0&&square[m][n]!=48)//左上角的情况
		{
			sum=sum+checkpoint(1,0);
			sum=sum+checkpoint(1,1);
			sum=sum+checkpoint(0,1);//统计周围雷的数目
			square[m][n]=48;//标记为检测过
			if(sum==0)//该点周围无雷
			{
				check(1,0);
				check(1,1);
				check(0,1);//扩展检测周围点的情况
			}
		}
		else if(n==5&&square[m][n]!=48)//右上角的情况
		{
			sum=sum+checkpoint(0,n-1);
			sum=sum+checkpoint(1,n-1);
			sum=sum+checkpoint(1,n);
			square[m][n]=48;
			if(sum==0)
			{
				check(0,n-1);
				check(1,n-1);
				check(1,n);
			}
		}
		else if(square[m][n]!=48)//顶行（除去两头）的情况
		{
			sum=sum+checkpoint(m,n-1);
			sum=sum+checkpoint(m+1,n-1);
			sum=sum+checkpoint(m+1,n);
			sum=sum+checkpoint(m+1,n+1);
			sum=sum+checkpoint(m,n+1);
			square[m][n]=48;
			if(sum==0)
			{
				check(m,n-1);
				check(m+1,n-1);
				check(m+1,n);
				check(m+1,n+1);
				check(m,n+1);
			}
		}
	}
	else if(m==7)
	{
		if(n==0&&square[m][n]!=48)//左下角
		{
			sum=sum+checkpoint(m-1,0);
			sum=sum+checkpoint(m-1,1);
			sum=sum+checkpoint(m,1);
			square[m][n]=48;
			if(sum==0)
			{
				check(m-1,0);
				check(m-1,1);
				check(m,1);
			}
		}
		else if(n==5&&square[m][n]!=48)//右下角
		{
			sum=sum+checkpoint(m-1,n);
			sum=sum+checkpoint(m-1,n-1);
			sum=sum+checkpoint(m,n-1);
			square[m][n]=48;
			if(sum==0)
			{
				check(m-1,n);
				check(m-1,n-1);
				check(m,n-1);
			}
		}
		else if(square[m][n]!=48)//最低行（除去两头）
		{
			sum=sum+checkpoint(m,n-1);
			sum=sum+checkpoint(m-1,n-1);
			sum=sum+checkpoint(m-1,n);
			sum=sum+checkpoint(m-1,n+1);
			sum=sum+checkpoint(m,n+1);
			square[m][n]=48;
			if(sum==0)
			{
				check(m,n-1);
				check(m-1,n-1);
				check(m-1,n);
				check(m-1,n+1);
				check(m,n+1);
			}
		}
	}
	else
	{
		if(n==0&&square[m][n]!=48)//最左列（除去两头）
		{
			sum=sum+checkpoint(m-1,0);
			sum=sum+checkpoint(m-1,1);
			sum=sum+checkpoint(m,1);
			sum=sum+checkpoint(m+1,1);
			sum=sum+checkpoint(m+1,0);
			square[m][n]=48;
			if(sum==0)
			{
				check(m-1,0);
				check(m-1,1);
				check(m,1);
				check(m+1,1);
				check(m+1,0);
			}
		}
		else if(n==5&&square[m][n]!=48)//最右列（除去两头）
		{
			sum=sum+checkpoint(m-1,n);
			sum=sum+checkpoint(m-1,n-1);
			sum=sum+checkpoint(m,n-1);
			sum=sum+checkpoint(m+1,n-1);
			sum=sum+checkpoint(m+1,n);
			square[m][n]=48;
			if(sum==0)
			{
				check(m-1,n);
				check(m-1,n-1);
				check(m,n-1);
				check(m+1,n-1);
				check(m+1,n);
			}
		}
		else if(square[m][n]!=48)//普通情况
		{
			sum=sum+checkpoint(m-1,n-1);
			sum=sum+checkpoint(m-1,n);
			sum=sum+checkpoint(m-1,n+1);
			sum=sum+checkpoint(m,n-1);
			sum=sum+checkpoint(m,n+1);
			sum=sum+checkpoint(m+1,n-1);
			sum=sum+checkpoint(m+1,n);
			sum=sum+checkpoint(m+1,n+1);
			square[m][n]=48;
			if(sum==0)
			{
				check(m-1,n-1);
				check(m-1,n);
				check(m-1,n+1);
				check(m,n-1);
				check(m,n+1);
				check(m+1,n-1);
				check(m+1,n);
				check(m+1,n+1);
			}
		}
	}
	if(sum!=0)
	    square[m][n]=sum;//该点数值为周围雷数
	system("cls");//清屏
	for(checksum=0,m=0;m<8;m++)//输出更新后的雷田
	{
		for(n=0;n<6;n++)
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
		printf("\n");
	}
	printf("\n");
	if(checksum==10)//未点开的方块数等于雷数，胜利
	printf("YOU WIN\n");
}
