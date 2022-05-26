//UCAS 2018K8009929030  ��������ͼ������Rayilam��  Gobang
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define N	15
#define samep	same( row + dx[u] * i, col + dy[u] * i, p[row][col] )
#define off	if ( !inboard( row + dx[u] * i, col + dy[u] * i ) || p[row + dx[u] * i][col + dy[u] * i] != 0 ) continue;

int	p[N + 2][N + 2];                                /* 0��1��2��  1��2�� -1��-2�� */
int	s = 0, ais = 1, s0;                       	/* s���ֵ�˭��,s=1,2��3��4��s=1��ai�£�s=2�����, s=3�����1, s=4�����2��s=s0�Ǻڷ��£������ǰ׷��� */
int	is_end = 0;
int	dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };        /* flat���� */
int	dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };          /* ��dx,dy����8���������� */
int	manu[2][300], manukey = 0;

int isFull()
{
	int i;
	int j;
	int ok = 0; //0��������
	for (i = 0; i < N + 2; i++)
	{
		for (j = 0; j < N + 2; j++)
		{
			if (p[i][j] == 0)
			{
				ok = 1;//����û����
				return ok;
			}
		}
	}
	return ok;
}

int out(int i, int j)
{
	if (p[i][j] == 1)
		return(printf(" ��"));
	if (p[i][j] == 2)
		return(printf(" ��"));
	if (p[i][j] == -1)
		return(printf(" ��"));
	if (p[i][j] == -2)
		return(printf(" ��"));
	if (i == N)
	{
		if (j == 1)
			return(printf("�� "));
		if (j == N)
			return(printf(" ��"));
		return(printf(" �� "));
	}
	if (i == 1)
	{
		if (j == 1)
			return(printf("�� "));
		if (j == N)
			return(printf(" ��"));
		return(printf(" �� "));
	}
	if (j == 1)
		return(printf("�� "));
	if (j == N)
		return(printf(" ��"));
	return(printf(" �� "));
}


void DrawBoard() /* ������ */
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
		printf("  AIִ�ڣ����ִ��\n");
	else if (s0 == 2) printf("  AIִ�ף����ִ��\n");
	else if (s0 == 3) printf("  p1ִ�ڣ�p2ִ��\n");
	else printf("  p1ִ�ף�p2ִ��\n");
	alpha = 'A';
	if (keyr)
		printf("  �������λ�ã�%c%d\n", alpha + keyc - 1, keyr);
}


void init()
{
	system("color f0");
	printf("����1����2����3����ѡ��\n1���˻���սAIִ������\n2���˻���ս���ִ������\n3�����˶�ս,p1ִ������\n4�����˶�ս,p2ִ������\n");
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
	/* �Կո��Χ���� */
	DrawBoard();
	for (j = 0; j < 300; j++)
		manu[0][j] = manu[1][j] = 0;
}


int inboard(int row, int col)        /* �Ƿ��������� */
{
	if (row < 1 || row > N)
		return 0;
	return(col >= 1 && col <= N);
}


int same(int row, int col, int key) /* �ж�2�������Ƿ�ͬɫ */
{
	if (!inboard(row, col))
		return 0;
	return(p[row][col] == key || p[row][col] + key == 0);
}


int num(int row, int col, int u) /* ���꣨row,col������������u */
{
	int i = row + dx[u], j = col + dy[u], sum = 0, ref = p[row][col];
	if (ref == 0)
		return(0);
	while (same(i, j, ref))
		sum++, i += dx[u], j += dy[u];
	return(sum);
}


int live4(int row, int col)           /* ��4������ */
{
	static int ok = 0;
	int sum = 0, i, u;
	for (u = 0; u < 4; u++)       /* 4������ÿ���������1�� */
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
				printf("�ڷ����1�γ��˻���\n");
			else if (s == 4) {
				printf("�ڷ����2�γ��˻���\n");
			}
		}
	}
	return sum;
}


int chong4(int row, int col)                          /* ��4������ */
{
	static int ok = 0;
	int sum = 0, i, u;
	for (u = 0; u < 8; u++)                       /* 8������ÿ���������1�� */
	{
		int	sumk = 0;
		int flag = 1;
		for (i = 1; samep || flag; i++)       /* �����ķ��� */
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
				printf("�ڷ����1�γ��˳���\n");
			else if (s == 4) {
				printf("�ڷ����2�γ��˳���\n");
			}
		}
	}
	return sum;
}


int live3(int row, int col)           /* ��3������ */
{
	static int ok = 0;
	int key = p[row][col], sum = 0, i, u;
	for (u = 0; u < 4; u++)       /*�����Ļ��� */
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
	for (u = 0; u < 8; u++)                       /* 8������ÿ���������1���������Ļ��� */
	{
		int	sumk = 0;
		int flag = 1;
		for (i = 1; samep || flag; i++)       /* �ɻ��ĵ�ķ��� */
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
				printf("  �ڷ����1�γ��˻���\n");
			else if (s == 4) {
				printf("  �ڷ����2�γ��˻���\n");
			}
		}

	}
	return sum;
}


int overline(int row, int col) /* �������� */
{
	static int ok = 0;
	for (int u = 0; u < 4; u++)
		if (num(row, col, u) + num(row, col, u + 4) > 4)
		{
			if (ok == 0)
			{
				ok = 1;
				if (s == 3)
					printf("  �ڷ����1�γ��˳���\n");
				else if (s == 4) {
					printf("  �ڷ����2�γ��˳���\n");
				}
			}
			return 1;
		}
	return 0;
}


int ban(int row, int col)    /* �ж����Ӻ��Ƿ�ɽ��� */
{
	if (same(row, col, 2))
		return 0;  /* �׷��޽��� */
	return(live3(row, col) > 1 || overline(row, col) || live4(row, col) + chong4(row, col) > 1);
}


int end_(int row, int col)   /* (row,col)������֮���Ƿ���Ϸ���� */
{
	for (int u = 0; u < 4; u++)
		if (num(row, col, u) + num(row, col, u + 4) >= 4)
			is_end = 1;
	if (is_end)
		return 1;
	is_end = ban(row, col);
	return(is_end);
}

void go(int row, int col)                     /* ����һ�� */
{
	int banvalue;
	if (s == s0)
		p[row][col] = -1;               /* ��������µ��� */
	else p[row][col] = -2;
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)  /* ȡ����һ��������ı�ʶ */
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
			printf("���ʤ������ϲѽ��");
		else if (s0 == 3)
			printf("��ϲ���2ʤ����");
		else if (s0 == 4)
			printf("��ϲ���1ʤ����");
		else printf("AIʤ����");
		Sleep(3000);
	}
	if (end_(row, col) && !banvalue)
	{
		if (s == ais)
			printf("AIʤ�����أ�");
		else if (s == 2)
			printf("���ʤ������ϲѽ��");
		else if (s == 3)
			printf("��ϲ���1ʤ��ѽ��");
		else printf("��ϲ���2ʤ��ѽ��");
		Sleep(3000);
	}
	manu[0][manukey] = row, manu[1][manukey++] = col;
}


int ok(int row, int col)     /* �ܷ����� */
{
	return(inboard(row, col) && (p[row][col] == 0));
}


int point(int row, int col)   /* �Ǹ���ֵ */
{
	if (ban(row, col))
		return(0);      /* ����0�� */
	if (end_(row, col))
	{
		is_end = 0;
		return(10000);
	}
	int ret = live4(row, col) * 1000 + (chong4(row, col) + live3(row, col)) * 100, u;
	for (u = 0; u < 8; u++)
		if (p[row + dx[u]][col + dy[u]])
			ret++;
	/* ��Ч��0�� */
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
				keyp = tempp - p2 * 2;  /* ������ȡ���� */
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
				keyp = tempp;  /* �ڶ���ȡ��С */
		}
	return(keyp);
}


void AI()
{
	DrawBoard();
	printf("  �ֵ�AI�£����Ե�һ���£� ");
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
			} /* ��Ч��֦���ܿ��˽��ֵ����Ч�� */
			if (tempp == 10000)
			{
				go(i, j);
				return;
			}

			tempp = AI2();
			p[i][j] = 0;
			if (tempp > keyp)
				keyp = tempp, keyi = i, keyj = j;  /* ��һ��ȡ���� */
		}
	}
	go(keyi, keyj);
	return;
}


void out_manual()
{
	char	alpha = 'A';
	int	i;
	printf("\n  �ڷ�����λ��: ");
	for (i = 0; i < manukey; i += 2)
		printf("  %c%d", alpha + manu[1][i] - 1, manu[0][i]);
	printf("\n  �׷�����λ��: ");
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
	printf("  �ֵ����%d�£�����������(����=0�鿴����)�� ", play);
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
		printf("�˴�������");
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
			printf("����������ƽ��");
			break;
		}
		else {
			if (s == ais)
				AI();
			else if (s == 2)player();
			else if (s == 3) player(); //p1ִ��
			else if (s == 4) player(); //p1ִ��
			if (s < 3) s = 3 - s; /* �����巽 */
			else s = 7 - s;
		}
	}
	return(0);
}

