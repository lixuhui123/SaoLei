#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_ROW 9
#define MAX_COL 9
#define MINE_COUNT 10
//1.使用两个二维数组表示地图
//show_map(char)表示翻开（数字）和未翻开（'*'）''表示字符""表示字符串
//mine_map(char)表示是雷('1')和不是雷('0')
//2.数组的初始化
//show_map初始化为全都是未翻开的状态（'*'）
//mine_map先初始化为全都是('0')的状态，然后随机的生成十个('1')
//3.打印地图（show_map）
//4.提示玩家输入一个坐标表示要翻开的位置,校验坐标的有效性
//5.判定是不是踩雷了
//6.如果没踩雷，判断是不是游戏胜利（翻开了所有不是地雷的格子）
//7.没踩雷，就告诉玩家当前位置有几个雷
int Menu()
{
	printf("**********************\n");
	printf("***** 1.开始游戏 *****\n");
	printf("***** 0.游戏结束 *****\n");
	printf("**********************\n");
	int chioce = 0;
	scanf("%d", &chioce);
	return chioce;
}
void Init(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL])
{
	for (int row = 0; row < MAX_ROW; ++row)
	{
		for (int col = 0; col < MAX_COL; ++col)
		{
			show_map[row][col] = '*';
		}
	}
	for (int row = 0; row < MAX_ROW; ++row)
	{
		for (int col = 0; col < MAX_COL; ++col)
		{
			mine_map[row][col] = '0';
		}
	}
	int mine_count = MINE_COUNT;
	while (mine_count > 0)
	{
		int row = rand()%MAX_ROW;
		int col = rand()%MAX_COL;
		if (mine_map[row][col] == '1')
		{
			continue;
		}
		else
		{
			mine_map[row][col] = '1';
			--mine_count;
		}
	}
}
void PrintMap(char show_map[MAX_ROW][MAX_COL])
{
	printf("  |");
	
	for (int col = 0; col < MAX_COL; ++col)
	{
		printf("%d ", col);
	}
	printf("\n");
	for (int col = 0; col < MAX_COL-2; ++col)
	{
		printf("___");
	}
	printf("\n");
	for (int row = 0; row < MAX_ROW; ++row)
	{
		printf(" %d|", row);
		for (int col = 0; col < MAX_COL; ++col)
		{
			printf("%c ", show_map[row][col]);
			
		}
		printf("\n");
	}
}
void UpdateShowMap(int row,int col,char mine_map[MAX_ROW][MAX_COL],char show_map[MAX_ROW][MAX_COL])
{
	int count = 0;
	if (row-1 >= 0 && col-1 >=0 && mine_map[row - 1][col - 1] == '1')
	{
		++count;
	}
	if (row - 1 >= 0 && mine_map[row - 1][col] == '1')
	{
		++count;
	}
	if (row - 1 >= 0 && col + 1 < MAX_COL && mine_map[row - 1][col + 1] == '1')
	{
		++count;
	}
	if (col - 1 >= 0 && mine_map[row][col - 1] == '1')
	{
		++count;
	}
	if (col + 1 < MAX_COL && mine_map[row][col + 1] == '1')
	{
		++count;
	}
	if (row + 1 < MAX_ROW && col - 1 >= 0 && mine_map[row + 1][col - 1] == '1')
	{
		++count;
	}
	if (row + 1 < MAX_ROW && mine_map[row + 1][col] == '1')
	{
		++count;
	}
	if (row + 1 < MAX_ROW && col + 1 < MAX_COL && mine_map[row + 1][col + 1] == '1')
	{
		++count;
	}
	show_map[row][col] = count + '0';
}
void Game()
{
	char show_map[MAX_ROW][MAX_COL];
	char mine_map[MAX_ROW][MAX_COL];
	Init(show_map, mine_map);
	while (1)
	{
	PrintMap(show_map);
	//提示玩家输入，并进行校验
	
	printf("请输入要翻开的地址（row col）\n");
	int row = 0;
	int col = 0;
	int blank_count = 0;
	scanf("%d %d", &row, &col);
	
		if (row<0 || row>MAX_ROW || col<0 || col>MAX_COL)
		{
			printf("输入的坐标非法，请重新输入\n");
			continue;
		}
		if (show_map[row][col] != '*')
		{
			printf("这个位置已被翻开，请重新输入\n");
			continue;
		}
		//判断是否踩雷
		if (mine_map[row][col] == '1')
		{
			printf("很遗憾踩雷了\n");
			UpdateShowMap(row, col, mine_map, show_map);
			PrintMap(show_map);
			return;
		}
		++blank_count;
		//判断是否是游戏胜利
		if (blank_count == MAX_ROW * MAX_COL - MINE_COUNT)
		{
			printf("恭喜你，扫雷成功\n");
			return;
		}
		//告诉玩家当前位置有几颗雷
		system("cls");
		UpdateShowMap(row,col,mine_map,show_map);

	}
}
int main()
{
	srand((unsigned int)time(0));
	//int chioce = Menu();
	while (1)
	{
		int chioce = Menu();
		if (1 == chioce)
			Game();
		else if (0 == chioce)
		{
			printf("BYE BYE\n");
			break; 
		}
		else
		{
			printf("您的输入非法请重新输入\n");
			continue;
		}
	}
	system("pause");
	return 0;
}
