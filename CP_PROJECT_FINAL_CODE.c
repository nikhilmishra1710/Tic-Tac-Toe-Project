#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <string.h>

int c, p1, p2;
int arr[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
char comp, play1, play2;
COORD coord = {0, 0};
SYSTEMTIME str_t;

struct info
{
	char name[100];
	char result[10];
	char date[20];
	char time[20];
	char name2[100];
	char gametype[100];
} rinfo[100];

struct score
{
	char name[100];
	int points;
	char streak[7];
	int match;
} lb[100], temp;

void menu();
void gotoxy(int x, int y);
void drawboard();
void putXO(char type, int value);
int startgame(int n, int gtype);
int check();
void gamebrain();
void attack();
void putXOcomp(int i, int j);
void history(int gtype, char player1, char player2);
void leaderboard(char name[100], char result);
void displayleaderboard();
void displayhistory();
void resetarr();
void end();

int main()
{

	menu();

	return 0;
}

void menu()
{

	int choice, n;
	do
	{
		system("cls");
		printf("Welcome to TIC TAC TOE Game\n");
		printf("1. Computer VS Player\n2. Player 1 VS Player 2\n");
		printf("3. History\n4. Leaderboard\n5. Exit\n");
		printf("Enter your choice (1/2/3/4/5): ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("1. Player plays as X\n2. Player plays as O\n");
			printf("Enter your choice (1/2): ");
			scanf("%d", &n);
			printf("USE ARROW KEYS TO MOVE CURSOR AND PRESS ENTER TO SELECT THE POSITION");
			if (n == 1)
				play1 = 'X', comp = 'O', c = -1, p1 = 1;
			if (n == 2)
				play1 = 'O', comp = 'X', c = 1, p1 = -1;

			startgame(n, choice);
			break;

		case 2:
			printf("1. Player 1 plays as X\n2. Player 1 plays as O\n");
			printf("Enter your choice (1/2): ");
			scanf("%d", &n);
			printf("USE ARROW KEYS TO MOVE CURSOR AND PRESS ENTER TO SELECT THE POSITION");
			if (n == 1)
				play1 = 'X', play2 = 'O', p2 = -1, p1 = 1;
			if (n == 2)
				play1 = 'O', play2 = 'X', p2 = 1, p1 = -1;

			startgame(n, choice);
			break;

		case 3:
			system("cls");
			displayhistory();
			printf("Press Enter to continue: ");
			getch();
			menu();
			break;

		case 4:
			system("cls");
			displayleaderboard();
			printf("Press Enter to continue: ");
			getch();
			menu();
			break;

		case 5:
			printf("Thank You for playing the game :)\n");
			exit(1);
			break;

		default:
			printf("Invalid input!! Try again....\n\n");
			Sleep(1500);
		}
	} while (choice != 5);
}

void end()
{

	int i;

	gotoxy(11, 21);
	printf("PLEASE WAIT....UPDATING DATA......0 %");
	Sleep(500);

	gotoxy(78, 21);
	printf("|");

	for (i = 0; i < 10; i++)
	{
		gotoxy(45, 21);
		printf("%d %", (i + 1) * 10);
		gotoxy(48 + i * 3, 21);
		printf("|||");
		Sleep(500);
	}

	resetarr();
	// menu();
}

int startgame(int n, int gtype)
{
	int i, j, k, flag1, flag2;
	drawboard();

	if (gtype == 1 && n == 1)
	{

		for (i = 0; i < 5; i++)
		{

			gotoxy(25, 12);
			printf("PLAYER'S TURN         ");

			putXO(play1, p1);

			flag1 = check();

			if (i == 4)
			{
				gotoxy(11, 17);
				printf("The Game is Draw\n");
				history(gtype, 'D', 'D');
				break;
			}
			else if (flag1 == 1)
			{
				gotoxy(11, 17);
				printf("Player Wins\n");
				history(gtype, 'W', 'L');
				break;
			}

			gotoxy(25, 12);

			printf("SYSTEM's TURN...");

			for (j = 0; j < 12; j++)
			{
				gotoxy(41, 12);
				switch (j % 8)
				{
				case 0:
				case 4:
					printf("||");
					break;
				case 1:
				case 5:
					printf("\\\\");
					break;
				case 2:
				case 6:
					printf("==");
					break;
				case 3:
				case 7:
					printf("//");
					break;
				}
				Sleep(200);
			}

			gamebrain();

			flag2 = check();
			if (flag2 == 2)
			{
				gotoxy(11, 17);
				printf("Computer Wins\n");
				history(gtype, 'L', 'W');
				break;
			}
		}
	}
	else if (gtype == 1 && n == 2)
	{

		for (i = 0; i < 5; i++)
		{
			gotoxy(25, 12);

			printf("SYSTEM's TURN...");

			for (j = 0; j < 12; j++)
			{
				gotoxy(41, 12);
				switch (j % 8)
				{
				case 0:
				case 4:
					printf("||");
					break;
				case 1:
				case 5:
					printf("\\\\");
					break;
				case 2:
				case 6:
					printf("==");
					break;
				case 3:
				case 7:
					printf("//");
					break;
				}
				Sleep(200);
			}

			gamebrain();

			flag1 = check();

			if (i == 4)
			{
				gotoxy(11, 17);
				printf("The Game is Draw\n");
				history(gtype, 'D', 'D');
				break;
			}
			else if (flag1 == 1)
			{
				gotoxy(11, 17);
				printf("Computer wins\n");
				history(gtype, 'L', 'W');
				break;
			}

			gotoxy(25, 12);
			printf("PLAYER'S TURN         ");

			putXO(play1, p1);

			flag2 = check();

			if (flag2 == 2)
			{
				gotoxy(11, 17);
				printf("Player Wins\n");
				history(gtype, 'W', 'L');
				break;
			}
		}
	}
	else if (gtype == 2 && n == 1)
	{

		for (i = 0; i < 5; i++)
		{

			gotoxy(25, 12);
			printf("PLAYER 1 TURN");

			putXO(play1, p1);

			flag1 = check();
			if (i == 4)
			{
				gotoxy(11, 17);
				printf("The Game is Draw\n");
				history(gtype, 'D', 'D');
				break;
			}
			else if (flag1 == 1)
			{
				gotoxy(11, 17);
				printf("Player 1 Wins\n");
				history(gtype, 'W', 'L');
				break;
			}

			gotoxy(25, 12);
			printf("PLAYER 2 TURN");

			putXO(play2, p2);

			flag2 = check();

			if (flag2 == 2)
			{
				gotoxy(11, 17);
				printf("Player 2 Wins\n");
				history(gtype, 'L', 'W');
				break;
			}
		}
	}
	else
	{
		for (i = 0; i < 5; i++)
		{
			gotoxy(25, 12);
			printf("PLAYER 2 TURN");

			putXO(play2, p2);

			flag1 = check();

			if (i == 4)
			{
				gotoxy(11, 17);
				printf("The Game is Draw\n");
				history(gtype, 'D', 'D');
				break;
			}
			else if (flag1 == 1)
			{
				gotoxy(11, 17);
				printf("Player 2 Wins\n");
				history(gtype, 'L', 'W');
				break;
			}
			gotoxy(25, 12);
			printf("PLAYER 1 TURN");

			putXO(play1, p1);

			flag2 = check();

			if (flag2 == 2)
			{
				gotoxy(11, 17);
				printf("Player 1 Wins\n");
				history(gtype, 'W', 'L');
				break;
			}
		}
	}
	end();
}

void gotoxy(int x, int y)
{
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawboard()
{
	int i, j, k = 0, l = 0;

	for (i = 0; i < 3; i++)
	{
		gotoxy(10, 12 + i * 2);
		for (j = 0; j < 3; j++)
		{
			if (j == 0)
				printf("   ");
			else
				printf("|   ");
		}
		printf("\n");
		if (i < 2)
		{
			gotoxy(10, 12 + i * 2 + 1);
			for (j = 0; j < 2; j++)
			{
				if (j == 0)
					printf("---");
				printf("+---");
			}
		}
		printf("\n");
	}
}

void putXO(char type, int value)
{
	char chr2;
	int k = 11, l = 12, i = 0, j = 0, flag = 0;
	gotoxy(k, l);
	while (1)
	{

		chr2 = getch();
		switch (chr2)
		{
		case 72:
			l -= 2;
			i -= 1;
			if (l >= 12 && l <= 16)
				gotoxy(k, l);
			else
				l += 2, i += 1;
			break;
		case 80:
			l += 2;
			i += 1;
			if (l >= 12 && l <= 16)
				gotoxy(k, l);
			else
				l -= 2, i -= 1;
			break;
		case 75:
			k -= 4;
			j -= 1;
			if (k >= 11 && k <= 19)
				gotoxy(k, l);
			else
				k += 4, j += 1;
			break;
		case 77:
			k += 4;
			j += 1;
			if (k >= 11 && k <= 19)
				gotoxy(k, l);
			else
				k -= 4, j -= 1;
			break;
		case 13:
			if (!arr[i][j])
			{
				printf("%c", type);
				flag = 1;
				arr[i][j] = value;
				break;
			}
			else
			{
				gotoxy(11, 17);
				printf("Already Occupied");
				gotoxy(k, l);
			}
		};
		if (flag)
		{
			break;
		}
	}
	gotoxy(11, 10);
}

void resetarr()
{
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			arr[i][j] = 0;
		}
	}
}

int check()
{

	int i, j, k, row, col;

	for (i = 0; i < 3; i++)
	{
		row = 0, col = 0;
		for (j = 0; j < 3; j++)
		{
			row += arr[i][j];
			col += arr[j][i];
		}

		if (row == 3 || col == 3)
			return 1;

		if (row == -3 || col == -3)
			return 2;
	}

	int dia = 0, opp = 0;
	for (i = 0, j = 0, k = 2; j < 3; i++, j++, k--)
	{
		dia += arr[i][j];
		opp += arr[k][i];
	}

	if (dia == 3 || opp == 3)
		return 1;

	if (dia == -3 || opp == -3)
		return 2;

	return 0;
}

void gamebrain()
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		if (arr[i][0] + arr[i][1] == 2 * c && arr[i][2] == 0)
		{
			arr[i][2] = c;
			putXOcomp(i, 2);
			return;
		}
		if (arr[0][i] + arr[1][i] == 2 * c && arr[2][i] == 0)
		{
			arr[2][i] = c;
			putXOcomp(2, i);
			return;
		}
		if (arr[i][0] + arr[i][2] == 2 * c && arr[i][1] == 0)
		{
			arr[i][0 + 1] = c;
			putXOcomp(i, 1);
			return;
		}
		if (arr[0][i] + arr[2][i] == 2 * c && arr[1][i] == 0)
		{
			arr[1][i] = c;
			putXOcomp(1, i);
			return;
		}
		if (arr[i][1] + arr[i][2] == 2 * c && arr[i][0] == 0)
		{
			arr[i][0] = c;
			putXOcomp(i, 0);
			return;
		}
		if (arr[1][i] + arr[2][i] == 2 * c && arr[0][i] == 0)
		{
			arr[0][i] = c;
			putXOcomp(0, i);
			return;
		}
	}
	if (arr[0][0] + arr[1][1] == 2 * c && arr[2][2] == 0)
	{
		arr[2][2] = c;
		putXOcomp(2, 2);
		return;
	}
	else if (arr[0][0] + arr[2][2] == 2 * c && arr[1][1] == 0)
	{
		arr[1][1] = c;
		putXOcomp(1, 1);
		return;
	}
	else if (arr[1][1] + arr[2][2] == 2 * c && arr[0][0] == 0)
	{
		arr[0][0] = c;
		putXOcomp(0, 0);
		return;
	}
	else if (arr[0][2] + arr[1][1] == 2 * c && arr[2][0] == 0)
	{
		arr[2][0] = c;
		putXOcomp(2, 0);
		return;
	}
	else if (arr[0][2] + arr[2][0] == 2 * c && arr[1][1] == 0)
	{
		arr[1][1] = c;
		putXOcomp(1, 1);
		return;
	}
	else if (arr[1][1] + arr[2][0] == 2 * c && arr[0][2] == 0)
	{
		arr[0][2] = c;
		putXOcomp(0, 2);
		return;
	}

	for (i = 0; i < 3; i++)
	{
		if (arr[i][0] + arr[i][1] == 2 * p1 && arr[i][2] == 0)
		{
			arr[i][2] = c;
			putXOcomp(i, 2);
			return;
		}
		if (arr[0][i] + arr[1][i] == 2 * p1 && arr[2][i] == 0)
		{
			arr[2][i] = c;
			putXOcomp(2, i);
			return;
		}
		if (arr[i][0] + arr[i][2] == 2 * p1 && arr[i][1] == 0)
		{
			arr[i][0 + 1] = c;
			putXOcomp(i, 1);
			return;
		}
		if (arr[0][i] + arr[2][i] == 2 * p1 && arr[1][i] == 0)
		{
			arr[1][i] = c;
			putXOcomp(1, i);
			return;
		}
		if (arr[i][1] + arr[i][2] == 2 * p1 && arr[i][0] == 0)
		{
			arr[i][0] = c;
			putXOcomp(i, 0);
			return;
		}
		if (arr[1][i] + arr[2][i] == 2 * p1 && arr[0][i] == 0)
		{
			arr[0][i] = c;
			putXOcomp(0, i);
			return;
		}
	}
	if (arr[0][0] + arr[1][1] == 2 * p1 && arr[2][2] == 0)
	{
		arr[2][2] = c;
		putXOcomp(2, 2);
		return;
	}
	else if (arr[0][0] + arr[2][2] == 2 * p1 && arr[1][1] == 0)
	{
		arr[1][1] = c;
		putXOcomp(1, 1);
		return;
	}
	else if (arr[1][1] + arr[2][2] == 2 * p1 && arr[0][0] == 0)
	{
		arr[0][0] = c;
		putXOcomp(0, 0);
		return;
	}
	else if (arr[0][2] + arr[1][1] == 2 * p1 && arr[2][0] == 0)
	{
		arr[2][0] = c;
		putXOcomp(2, 0);
		return;
	}
	else if (arr[0][2] + arr[2][0] == 2 * p1 && arr[1][1] == 0)
	{
		arr[1][1] = c;
		putXOcomp(1, 1);
		return;
	}
	else if (arr[1][1] + arr[2][0] == 2 * p1 && arr[0][2] == 0)
	{
		arr[0][2] = c;
		putXOcomp(0, 2);
		return;
	}
	else
	{
		attack();
	}
}

void attack()
{
	GetSystemTime(&str_t);
	int i, j, rand = (int)str_t.wMilliseconds;
	switch (rand % 10)
	{
	case 0:
	case 5:
		if (arr[0][0] == 0)
		{
			arr[0][0] = c;
			putXOcomp(0, 0);
			break;
		}

	case 1:
	case 6:
		if (arr[0][2] == 0)
		{
			arr[0][2] = c;
			putXOcomp(0, 2);
			break;
		}
	case 2:
	case 7:
		if (arr[2][0] == 0)
		{
			arr[2][0] = c;
			putXOcomp(2, 0);
			break;
		}
	case 3:
	case 8:
		if (arr[2][2] == 0)
		{
			arr[2][2] = c;
			putXOcomp(2, 2);
			break;
		}
	case 4:
	case 9:
		if (arr[1][1] == 0)
		{
			arr[1][1] = c;
			putXOcomp(1, 1);
			break;
		}
	default:
		for (i = 0; i < 3; i++)
		{
			int f = 0;
			for (j = 0; j < 3; j++)
			{
				if (arr[i][j] == 0)
				{
					arr[i][j] = c;
					putXOcomp(i, j);
					f = 1;
					break;
				}
				if (f)
					break;
			}
		}
		break;
	}
}

void putXOcomp(int i, int j)
{
	gotoxy(11 + j * 4, 12 + i * 2);
	printf("%c", comp);
}

void history(int gtype, char player1, char player2)
{

	gotoxy(0, 19);
	Sleep(250);
	GetSystemTime(&str_t);
	FILE *fptr;
	fptr = fopen("history.txt", "r");
	int i = 1, j;
	char c;

	while (1)
	{
		fscanf(fptr, "%[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c", rinfo[i].name, rinfo[i].name2, rinfo[i].gametype, rinfo[i].result, rinfo[i].date);
		c = fgetc(fptr);
		if (c == -1)
		{
			break;
		}
		i++;
	}

	if (gtype == 1)
	{

		strcpy(rinfo[0].gametype, "PLAY VS COMP");
		printf("Enter the name of player: ");
		scanf(" %[^\n]s", rinfo[0].name);
		if (player1 == 'W')
			strcpy(rinfo[0].result, "WIN");
		else
			strcpy(rinfo[0].result, "LOSE");
		strcpy(rinfo[0].name2, "COMPUTER");
		leaderboard(rinfo[0].name, player1);
	}
	else
	{

		printf("Enter Player 1 name: ");
		scanf(" %[^\n]s", rinfo[0].name);
		printf("Enter Player 2 name: ");
		scanf(" %[^\n]s", rinfo[0].name2);
		strcpy(rinfo[0].gametype, "PLAY vs PLAY");

		if (player1 == 'W')
		{
			strcpy(rinfo[0].result, "P1 WIN");
		}
		else
		{
			strcpy(rinfo[0].result, "P2 WIN");
		}

		leaderboard(rinfo[0].name, player1);
		leaderboard(rinfo[0].name2, player2);
	}

	if (player1 == 'D')
		strcpy(rinfo[0].result, "DRAW");
	sprintf(rinfo[0].date, "%d-%d-%d", str_t.wDay, str_t.wMonth, str_t.wYear);

	fclose(fptr);

	fptr = fopen("history.txt", "w");
	for (j = 0; j < i; j++)
	{
		fprintf(fptr, "%s,%s,%s,%s,%s,\n", rinfo[j].name, rinfo[j].name2, rinfo[j].gametype, rinfo[j].result, rinfo[j].date);
	}

	fclose(fptr);
}

void leaderboard(char name[100], char result)
{
	FILE *fp;
	int i, j = 0, k;
	char c = 'a';
	fp = fopen("leaderboard.csv", "r");
	i = 0;

	while (1)
	{
		fscanf(fp, "%[^,]%*c %d%*c %d%*c %[^,]%*c", lb[i].name, &lb[i].points, &lb[i].match, lb[i].streak);
		c = fgetc(fp);
		if (c == -1)
		{
			break;
		}
		i++;
	}

	fclose(fp);

	int flag = -1;
	for (j = 0; j < i + 1; j++)
	{
		if (strcmp(lb[j].name, name) == 0)
		{
			flag = j;
			break;
		}
	}

	if (flag == -1)
	{
		flag = i;
		i++;
		strcpy(lb[flag].name, name);
		strcpy(lb[flag].streak, "000000");
		lb[flag].match = 0;
		lb[flag].points = 0;
	}

	if (result == 'W')
		lb[flag].points += 3;
	else if (result == 'D')
		lb[flag].points += 1;
	else if (result == 'L')
	{
		if (lb[flag].points - 2 < 0)
			lb[flag].points = 0;
		else
			lb[flag].points -= 2;
	}

	char str[6];
	strcpy(str, lb[flag].streak);

	for (k = strlen(str) - 1; k > 0; k--)
	{
		str[k] = str[k - 1];
	}

	str[0] = result;
	strcpy(lb[flag].streak, str);
	lb[flag].match += 1;

	fp = fopen("leaderboard.csv", "w");

	for (j = 0; j < i; j++)
	{
		fprintf(fp, "%s,%d,%d,%s,\n", lb[j].name, lb[j].points, lb[j].match, lb[j].streak);
	}

	fclose(fp);
}

void displayleaderboard()
{

	FILE *fptr;
	fptr = fopen("leaderboard.csv", "r");
	int i = 0, j, k;
	char c;

	if (fptr == NULL)
	{
		printf("NOOOOOOOOOO");
		return;
	}

	printf("LEADERBOARD IS BEING LOADED PLEASE WAIT... \n");

	while (1)
	{
		fscanf(fptr, "%[^,]%*c %d%*c %d%*c %[^,]%*c", lb[i].name, &lb[i].points, &lb[i].match, lb[i].streak);
		c = fgetc(fptr);
		if (c == -1)
		{
			break;
		}
		i++;
	}
	fclose(fptr);

	for (j = 0; j < i + 4; j++)
	{
		if (j == 0 || j == 2 || j == i + 3)
		{
			for (k = 0; k < 53; k++)
			{
				if (k == 0 || k == 21 || k == 30 || k == 39 || k == 52)
				{
					printf("+");
					Sleep(1.0);
				}
				else
				{
					printf("-");
					Sleep(1.0);
				}
			}
		}
		else
		{
			for (k = 0; k < 53; k++)
			{
				if (k == 0 || k == 21 || k == 30 || k == 39 || k == 52)
				{
					printf("|");
					Sleep(1.0);
				}
				else
				{
					printf(" ");
					Sleep(1.0);
				}
			}
		}
		printf("\n");
		Sleep(1.0);
	}

	for (j = 0; j < i; j++)
	{
		for (k = 0; k < i - j - 1; k++)
		{
			if (lb[k].points < lb[k + 1].points)
			{
				temp = lb[k];
				lb[k] = lb[k + 1];
				lb[k + 1] = temp;
			}
		}
	}

	gotoxy(9, 2);
	printf("NAME");
	Sleep(2.5);
	gotoxy(23, 2);
	printf("POINTS");
	Sleep(2.5);
	gotoxy(32, 2);
	printf("STREAK");
	Sleep(2.5);
	gotoxy(41, 2);
	printf("GAME PLAYED");
	Sleep(2.5);

	for (j = 0; j < i; j++)
	{
		gotoxy(3, 4 + j);

		for (k = 0; lb[j].name[k] != '\0', k < 16; k++)
		{
			printf("%c", lb[j].name[k]);
			Sleep(1.0);
		}

		gotoxy(25, 4 + j);
		printf("%d", lb[j].points);
		Sleep(2.5);
		gotoxy(32, 4 + j);
		printf("%s", lb[j].streak);
		Sleep(2.50);
		gotoxy(45, 4 + j);
		printf("%d", lb[j].match);
		Sleep(2.5);
	}

	gotoxy(0, 0);
	printf("WIN=3 Points,DRAW=1 Points,LOSS=-2 Points........\n");
	gotoxy(0, 4 + 1 + j);
}

void displayhistory()
{

	FILE *fptr;
	fptr = fopen("history.txt", "r");
	int i = 0, j, k;
	char c;
	printf("PLEASE WAIT HISTORY IS LOADING.....\n");
	while (1)
	{
		fscanf(fptr, "%[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c", rinfo[i].name, rinfo[i].name2, rinfo[i].gametype, rinfo[i].result, rinfo[i].date);
		c = fgetc(fptr);
		if (c == -1)
		{
			break;
		}
		i++;
	}

	for (j = 0; j < 14; j++)
	{
		if (j == 0 || j == 2 || j == 13)
		{
			for (k = 0; k < 86; k++)
			{
				if (k == 0 || k == 21 || k == 42 || k == 59 || k == 69 || k == 85)
				{
					printf("+");
					Sleep(1);
				}
				else
				{
					printf("-");
					Sleep(1);
				}
			}
		}
		else
		{
			for (k = 0; k < 86; k++)
			{
				if (k == 0 || k == 21 || k == 42 || k == 59 || k == 69 || k == 85)
				{
					printf("|");
					Sleep(1);
				}
				else
				{
					printf(" ");
					Sleep(1);
				}
			}
		}
		printf("\n");
	}

	gotoxy(7, 2);
	printf("PLAYER 1");
	Sleep(5);
	gotoxy(28, 2);
	printf("PLAYER 2");
	Sleep(5);
	gotoxy(49, 2);
	printf("TYPE");
	Sleep(5);
	gotoxy(62, 2);
	printf("RESULT");
	Sleep(5);
	gotoxy(75, 2);
	printf("DATE");
	Sleep(5);

	for (j = 0; j < 10; j++)
	{
		gotoxy(3, 4 + j);
		for (k = 0; rinfo[j].name[k] != '\0', k < 16; k++)
		{
			printf("%c", rinfo[j].name[k]);
			Sleep(1);
		}
		gotoxy(23, 4 + j);
		for (k = 0; rinfo[j].name2[k] != '\0', k < 16; k++)
		{
			printf("%c", rinfo[j].name2[k]);
			Sleep(1);
		}
		gotoxy(45, 4 + j);
		for (k = 0; rinfo[j].gametype[k] != '\0', k < 12; k++)
		{
			printf("%c", rinfo[j].gametype[k]);
			Sleep(1);
		}
		gotoxy(62, 4 + j);
		for (k = 0; rinfo[j].result[k] != '\0', k < 6; k++)
		{
			printf("%c", rinfo[j].result[k]);
			Sleep(1);
		}
		gotoxy(71, 4 + j);
		for (k = 0; rinfo[j].date[k] != '\0', k < 10; k++)
		{
			printf("%c", rinfo[j].date[k]);
			Sleep(1);
		}
	}

	gotoxy(0, 0);
	printf("HISTORY                                   ");
	gotoxy(0, 4 + 1 + j);
}
