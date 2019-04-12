#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_ROW 9
#define MAX_COL 9
#define MINE_COUNT 10
//1.ʹ��������ά�����ʾ��ͼ
//show_map(char)��ʾ���������֣���δ������'*'��''��ʾ�ַ�""��ʾ�ַ���
//mine_map(char)��ʾ����('1')�Ͳ�����('0')
//2.����ĳ�ʼ��
//show_map��ʼ��Ϊȫ����δ������״̬��'*'��
//mine_map�ȳ�ʼ��Ϊȫ����('0')��״̬��Ȼ�����������ʮ��('1')
//3.��ӡ��ͼ��show_map��
//4.��ʾ�������һ�������ʾҪ������λ��,У���������Ч��
//5.�ж��ǲ��ǲ�����
//6.���û���ף��ж��ǲ�����Ϸʤ�������������в��ǵ��׵ĸ��ӣ�
//7.û���ף��͸�����ҵ�ǰλ���м�����
int Menu()
{
	printf("**********************\n");
	printf("***** 1.��ʼ��Ϸ *****\n");
	printf("***** 0.��Ϸ���� *****\n");
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
	//��ʾ������룬������У��
	
	printf("������Ҫ�����ĵ�ַ��row col��\n");
	int row = 0;
	int col = 0;
	int blank_count = 0;
	scanf("%d %d", &row, &col);
	
		if (row<0 || row>MAX_ROW || col<0 || col>MAX_COL)
		{
			printf("���������Ƿ�������������\n");
			continue;
		}
		if (show_map[row][col] != '*')
		{
			printf("���λ���ѱ�����������������\n");
			continue;
		}
		//�ж��Ƿ����
		if (mine_map[row][col] == '1')
		{
			printf("���ź�������\n");
			UpdateShowMap(row, col, mine_map, show_map);
			PrintMap(show_map);
			return;
		}
		++blank_count;
		//�ж��Ƿ�����Ϸʤ��
		if (blank_count == MAX_ROW * MAX_COL - MINE_COUNT)
		{
			printf("��ϲ�㣬ɨ�׳ɹ�\n");
			return;
		}
		//������ҵ�ǰλ���м�����
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
			printf("��������Ƿ�����������\n");
			continue;
		}
	}
	system("pause");
	return 0;
}
