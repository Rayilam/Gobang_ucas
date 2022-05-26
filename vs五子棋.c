//UCAS 2018K8009929030  热伊莱·图尔贡（Rayilam）  Gobang
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define N	15
#define samep	same( row + dx[u] * i, col + dy[u] * i, p[row][col] )
#define off	if ( !inboard( row + dx[u] * i, col + dy[u] * i ) || p[row + dx[u] * i][col + dy[u] * i] != 0 ) continue;

int	p[N + 2][N + 2];                                /* 0空1黑2白  1●2○ -1▲-2△ */
int	s = 0, ais = 1, s0;                       	/* s是轮到谁下,s=1,2，3，4，s=1是ai下，s=2是玩家, s=3是玩家1, s=4是玩家2，s=s0是黑方下，否则是白方下 */
int	is_end = 0;
int	dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };        /* flat技术 */
int	dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };          /* （dx,dy）是8个方向向量 */
int	manu[2][300], manukey = 0;

int isFull()
{
	int i;
	int j;
	int ok = 0; //0代表满了
	for (i = 0; i < N + 2; i++)
	{
		for (j = 0; j < N + 2; j++)
		{
			if (p[i][j] == 0)
			{
				ok = 1;//代表没有满
				return ok;
			}
		}
	}
	return ok;
}

int out(int i, int j)
{
	if (p[i][j] == 1)
		return(printf(" ●"));
	if (p[i][j] == 2)
		return(printf(" ○"));
	if (p[i][j] == -1)
		return(printf(" ▲"));
	if (p[i][j] == -2)
		return(printf(" △"));
	if (i == N)
	{
		if (j == 1)
			return(printf("┌ "));
		if (j == N)
			return(printf(" ┐"));
		return(printf(" ┬ "));
	}
	if (i == 1)
	{
		if (j == 1)
			return(printf("└ "));
		if (j == N)
			return(printf(" ┘"));
		return(printf(" ┴ "));
	}
	if (j == 1)
		return(printf("├ "));
	if (j == N)
		return(printf(" ┤"));
	return(printf(" ┼ "));
}


void DrawBoard() /* 画棋盘 */
{
	system("cls");
	int	row = 0, col = 0, keyr = 0, keyc = 0;
	char	alpha = 'A';
	printf("\n\n\n     ");
	for (col = 1; col <= N; col++)
		printf(" %c ", alpha++);
	for (row = N; row >= 1; row--)
	{
		printf("\n   %2d", row);
		for (col = 1; col <= N; col++)
		{
			out(row, col);
			if (p[row][col] < 0)
				keyr = row, keyc = col;
		}
		printf(" %d", row);
	}
	alpha = 'A';
	printf("\n     ");
	for (col = 1; col <= N; col++)
		printf(" %c ", alpha++);
	printf("\n\n");
	if (s0 == ais)
		printf("  AI执黑，玩家执白\n");
	else if (s0 == 2) printf("  AI执白，玩家执黑\n");
	else if (s0 == 3) printf("  p1执黑，p2执白\n");
	else printf("  p1执白，p2执黑\n");
	alpha = 'A';
	if (keyr)
		printf("  最后落子位置：%c%d\n", alpha + keyc - 1, keyr);
}


void init()
{
	system("color f0");
	printf("输入1或者2或者3进行选择\n1，人机对战AI执黑先行\n2，人机对战玩家执黑先行\n3，人人对战,p1执黑先行\n4，人人对战,p2执黑先行\n");
	rewind(stdin);
	scanf_s("%d", &s);
	if (s != 1 && s != 2 && s != 3 && s != 4)
	{
		init();
		return;
	}
	s0 = s;
	int i, j;
	for (i = 0; i <= N + 1; i++)
		for (j = 0; j <= N + 1; j++)
			p[i][j] = 0;
	/* 以空格包围棋盘 */
	DrawBoard();
	for (j = 0; j < 300; j++)
		manu[0][j] = manu[1][j] = 0;
}


int inboard(int row, int col)        /* 是否在棋盘内 */
{
	if (row < 1 || row > N)
		return 0;
	return(col >= 1 && col <= N);
}


int same(int row, int col, int key) /* 判断2个棋子是否同色 */
{
	if (!inboard(row, col))
		return 0;
	return(p[row][col] == key || p[row][col] + key == 0);
}


int num(int row, int col, int u) /* 坐标（row,col），方向向量u */
{
	int i = row + dx[u], j = col + dy[u], sum = 0, ref = p[row][col];
	if (ref == 0)
		return(0);
	while (same(i, j, ref))
		sum++, i += dx[u], j += dy[u];
	return(sum);
}


int live4(int row, int col)           /* 活4的数量 */
{
	static int ok = 0;
	int sum = 0, i, u;
	for (u = 0; u < 4; u++)       /* 4个方向，每个方向最多1个 */
	{
		int sumk = 1;
		for (i = 1; samep; i++)
			sumk++;
		off;
		for (i = -1; samep; i--)
			sumk++;
		off;
		if (sumk == 4)
			sum++;
	}
	if (sum >= 2 && s == s0)
	{
		if (ok == 0)
		{
			ok = 1;
			if (s == 3)
				printf("黑方玩家1形成了活四\n");
			else if (s == 4) {
				printf("黑方玩家2形成了活四\n");
			}
		}
	}
	return sum;
}


int chong4(int row, int col)                          /* 冲4的数量 */
{
	static int ok = 0;
	int sum = 0, i, u;
	for (u = 0; u < 8; u++)                       /* 8个方向，每个方向最多1个 */
	{
		int	sumk = 0;
		int flag = 1;
		for (i = 1; samep || flag; i++)       /* 成五点的方向 */
		{
			if (!samep)
			{
				if (flag && p[row + dx[u] * i][col + dy[u] * i])
					sumk -= 10;
				flag = 0;
			}
			sumk++;
		}
		if (!inboard(row + dx[u] * --i, col + dy[u] * i))
			continue;
		for (i = -1; samep; i--)
			sumk++;
		if (sumk == 4)
			sum++;
	}
	sum = sum - live4(row, col) * 2;
	if (sum >= 2 && s == s0)
	{
		if (ok == 0)
		{
			ok = 1;
			if (s == 3)
				printf("黑方玩家1形成了冲四\n");
			else if (s == 4) {
				printf("黑方玩家2形成了冲四\n");
			}
		}
	}
	return sum;
}


int live3(int row, int col)           /* 活3的数量 */
{
	static int ok = 0;
	int key = p[row][col], sum = 0, i, u;
	for (u = 0; u < 4; u++)       /*三连的活三 */
	{
		int sumk = 1;
		for (i = 1; samep; i++)
			sumk++;
		off;
		i++;
		off;
		for (i = -1; samep; i--)
			sumk++;
		off;
		i--;
		off;
		if (sumk == 3)
			sum++;
	}
	for (u = 0; u < 8; u++)                       /* 8个方向，每个方向最多1个非三连的活三 */
	{
		int	sumk = 0;
		int flag = 1;
		for (i = 1; samep || flag; i++)       /* 成活四点的方向 */
		{
			if (!samep)
			{
				if (flag && p[row + dx[u] * i][col + dy[u] * i])
					sumk -= 10;
				flag = 0;
			}
			sumk++;
		}
		off;
		if (p[row + dx[u] * --i][col + dy[u] * i] == 0)
			continue;
		for (i = 1; samep; i++)
			sumk++;
		off;
		if (sumk == 3)
			sum++;
	}
	if (sum >= 2 && s == s0) {
		if (ok == 0)
		{
			ok = 1;
			if (s == 3)
				printf("  黑方玩家1形成了活三\n");
			else if (s == 4) {
				printf("  黑方玩家2形成了活三\n");
			}
		}

	}
	return sum;
}


int overline(int row, int col) /* 长连禁手 */
{
	static int ok = 0;
	for (int u = 0; u < 4; u++)
		if (num(row, col, u) + num(row, col, u + 4) > 4)
		{
			if (ok == 0)
			{
				ok = 1;
				if (s == 3)
					printf("  黑方玩家1形成了长连\n");
				else if (s == 4) {
					printf("  黑方玩家2形成了长连\n");
				}
			}
			return 1;
		}
	return 0;
}


int ban(int row, int col)    /* 判断落子后是否成禁手 */
{
	if (same(row, col, 2))
		return 0;  /* 白方无禁手 */
	return(live3(row, col) > 1 || overline(row, col) || live4(row, col) + chong4(row, col) > 1);
}


int end_(int row, int col)   /* (row,col)处落子之后是否游戏结束 */
{
	for (int u = 0; u < 4; u++)
		if (num(row, col, u) + num(row, col, u + 4) >= 4)
			is_end = 1;
	if (is_end)
		return 1;
	is_end = ban(row, col);
	return(is_end);
}

void go(int row, int col)                     /* 落下一子 */
{
	int banvalue;
	if (s == s0)
		p[row][col] = -1;               /* 标出最新下的棋 */
	else p[row][col] = -2;
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)  /* 取消上一个最新棋的标识 */
		{
			if (i == row && j == col)
				continue;
			if (p[i][j] < 0)
				p[i][j] *= -1;
		}
	DrawBoard();
	banvalue = ban(row, col);
	if (banvalue)
	{
		if (s0 == 1)
			printf("玩家胜利，恭喜呀！");
		else if (s0 == 3)
			printf("恭喜玩家2胜利！");
		else if (s0 == 4)
			printf("恭喜玩家1胜利！");
		else printf("AI胜利！");
		Sleep(3000);
	}
	if (end_(row, col) && !banvalue)
	{
		if (s == ais)
			printf("AI胜利了呢！");
		else if (s == 2)
			printf("玩家胜利，恭喜呀！");
		else if (s == 3)
			printf("恭喜玩家1胜利呀！");
		else printf("恭喜玩家2胜利呀！");
		Sleep(3000);
	}
	manu[0][manukey] = row, manu[1][manukey++] = col;
}


int ok(int row, int col)     /* 能否落子 */
{
	return(inboard(row, col) && (p[row][col] == 0));
}


int point(int row, int col)   /* 非负分值 */
{
	if (ban(row, col))
		return(0);      /* 禁手0分 */
	if (end_(row, col))
	{
		is_end = 0;
		return(10000);
	}
	int ret = live4(row, col) * 1000 + (chong4(row, col) + live3(row, col)) * 100, u;
	for (u = 0; u < 8; u++)
		if (p[row + dx[u]][col + dy[u]])
			ret++;
	/* 无效点0分 */
	return(ret);
}


int AI3(int p2)
{
	int keyp = -100000, tempp;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
		{
			if (!ok(i, j))
				continue;
			p[i][j] = s0;
			tempp = point(i, j);
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}
			if (tempp == 10000)
			{
				p[i][j] = 0;
				return(10000);
			}
			p[i][j] = 0;
			if (tempp - p2 * 2 > keyp)
				keyp = tempp - p2 * 2;  /* 第三层取极大 */
		}
	return(keyp);
}


int AI2()
{
	int keyp = 100000, tempp;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
		{
			if (!ok(i, j))
				continue;
			p[i][j] = 3 - s0;
			tempp = point(i, j);
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}
			if (tempp == 10000)
			{
				p[i][j] = 0;
				return(-10000);
			}
			tempp = AI3(tempp);
			p[i][j] = 0;
			if (tempp < keyp)
				keyp = tempp;  /* 第二层取极小 */
		}
	return(keyp);
}


void AI()
{
	DrawBoard();
	printf("  轮到AI下，请稍等一下下： ");
	if (p[8][8] == 0)
	{
		go(8, 8);
		return;
	}

	int	i, j;
	int	keyp = -100000, keyi, keyj, tempp;
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			if (!ok(i, j))
				continue;
			p[i][j] = s0;
			tempp = point(i, j);
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			} /* 高效剪枝，避开了禁手点和无效点 */
			if (tempp == 10000)
			{
				go(i, j);
				return;
			}

			tempp = AI2();
			p[i][j] = 0;
			if (tempp > keyp)
				keyp = tempp, keyi = i, keyj = j;  /* 第一层取极大 */
		}
	}
	go(keyi, keyj);
	return;
}


void out_manual()
{
	char	alpha = 'A';
	int	i;
	printf("\n  黑方落子位置: ");
	for (i = 0; i < manukey; i += 2)
		printf("  %c%d", alpha + manu[1][i] - 1, manu[0][i]);
	printf("\n  白方落子位置: ");
	for (i = 1; i < manukey; i += 2)
		printf("  %c%d", alpha + manu[1][i] - 1, manu[0][i]);
	Sleep(5000);
}


void player()
{
	int play = 0;
	DrawBoard();
	if (s < 2) play = 1;
	else play = s - 2;
	printf("  轮到玩家%d下，请输入坐标(输入=0查看棋谱)： ", play);
	char	c = '\n';
	int	row = 0, col = 0;
	while (c < '0')
	{
		rewind(stdin);
		scanf_s("%c", &c);
		scanf_s("%d", &row);
	}

	if (c == '=')
	{
		out_manual();
		player();
		return;
	}
	if (c < 'a')
		col = c - 'A' + 1;
	else col = c - 'a' + 1;
	if (!ok(row, col))
	{
		printf("此处不能下");
		Sleep(1000);
		player();
		return;
	}
	go(row, col);
}


int main()
{
	init();
	while (!is_end)
	{
		if (isFull() == 0)
		{
			printf("棋盘下满，平局");
			break;
		}
		else {
			if (s == ais)
				AI();
			else if (s == 2)player();
			else if (s == 3) player(); //p1执黑
			else if (s == 4) player(); //p1执白
			if (s < 3) s = 3 - s; /* 换下棋方 */
			else s = 7 - s;
		}
	}
	return(0);
}

