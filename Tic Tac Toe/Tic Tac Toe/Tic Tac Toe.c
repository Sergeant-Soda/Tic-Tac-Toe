#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

char draw[4][4]; /* the tic tac toe matrix */
bool isDraw = false;

void CreateGrid(void)
{
	int i, j;

	for (i = 0; i < 3; i++)

		for (j = 0; j < 3; j++) draw[i][j] = ' ';

}

bool CheckDraw()
{

	for (int i = 1; i < 3; i++)
	{
		for (int j = 1; j < 3; i++)
		{
			if (draw[i][j] == ' ')
				return false;
		}
	}
	return true;
}

/* Get a player's move. */
void get_player_move(void)
{

	int x, y;

	printf("Enter coordinates in the form of \"X Y\": ");

	scanf("%d%*c%d", &x, &y);

	x--;
	y--;

	if (draw[x][y] != ' ')
	{
		printf("Invalid move, try again.\n");
		get_player_move();
	}
	else
		draw[x][y] = 'X';

	//if (CheckDraw == true)
		//printf("Match is a draw!");
}

/* Get a move from the computer. */
void get_computer_move(void)
{
	int i, j;
	int test = 0;

	do
	{
		i = rand() % 1 + rand() / (RAND_MAX / (3 - 1 + 1) + 1);
		j = rand() % 1 + rand() / (RAND_MAX / (3 - 1 + 1) + 1);
		test++;
		if (test > 100)
		{
			printf("\nDRAW!\n");
			isDraw = true;
			return;
		}
	} while (draw[i][j] != ' ');

	draw[i][j] = 'O';


}

/* Display the matrix on the screen. */

void PrintGrid(void)
{

	for (int i = 0; i < 3; i++)
	{
		printf(" %c | %c | %c ", draw[i][0], draw[i][1], draw[i][2]);

		if (i != 2)
			printf("\n---|---|---\n");

	}

	printf("\n");

}

/* See if there is a winner. */

char check()
{

	for (int i = 0; i < 3; i++) /* check rows */
	{
		if (draw[i][0] == draw[i][1] && draw[i][0] == draw[i][2])
			return draw[i][0];
	}



	for (int i = 0; i < 3; i++) /* check columns */
	{
		if (draw[0][i] == draw[1][i] && draw[0][i] == draw[2][i])
			return draw[0][i];
	}

	/* test diagonals */

	if (draw[0][0] == draw[1][1] && draw[1][1] == draw[2][2])
		return draw[0][0];

	if (draw[0][2] == draw[1][1] && draw[1][1] == draw[2][0])
		return draw[0][2];

	return ' ';
}

void ClearScreen()
{

	FILE* osCheck = fopen("c:\\Windows\\System32\\cmd.exe", "r");

	if ((osCheck = fopen(osCheck, "r")))
	{
		fclose(osCheck);
		system("clear");
	}
	else
	{
		system("cls");
	}
}

int main()
{
	time_t time_start = (time_t*)malloc(sizeof(time_t));
	time_t time_end = (time_t*)malloc(sizeof(time_t));
	char done;

	int end = 0;
	int selection = 0;
	char goback = ' ';
	
	FILE* fWin;
	FILE* fLos;
	fWin = fopen("wins.txt", "r+");
	fLos = fopen("lose.txt", "r+");
	int Totalwins = 97;
	int loses = 65;

	if (fWin == NULL)
	{
		fWin = fopen("wins.txt", "w+");
		fprintf(fWin, "%d", Totalwins);
	}
	if (fLos == NULL)
	{
		fLos = fopen("lose.txt", "w+");
		fprintf(fLos, "%d", loses);
	}

	fscanf(fWin, "%d", &Totalwins);
	fscanf(fLos, "%d", &loses);
	fclose(fWin);
	fclose(fLos);

	do
	{
		printf("\nWelcome to Tic-Tac-Toe!\n");
		printf("-------------------------------\n");
		printf("\nPlease select an option below");
		printf("\n0. Exit");
		printf("\n1. Play!");
		printf("\n2. About the team");
		printf("\nChoice:");
		scanf("%i", &selection);

		switch (selection)
		{
		case 0:
			return 0;
		case 1:
			time_start = clock();
			done = ' ';

			CreateGrid();

			do {
				ClearScreen();
				PrintGrid();

				get_player_move();

				done = check(); /* see if winner */

				if (done != ' ')
					break; /* winner!*/

				get_computer_move();

				if (isDraw == true)
				{
					time_end = clock() - time_start;
					double time_taken = ((double)time_end) / CLOCKS_PER_SEC;

					printf("\nMatch is a draw!\n");
					printf("Time taken: %.2f seconds\n", time_taken);
					break;
				}

				done = check(); /* see if winner */
			} while (done == ' ');

			if (done == 'X')
			{
				time_end = clock() - time_start;
				double time_taken = ((double)time_end) / CLOCKS_PER_SEC;

				printf("You won!\n");
				printf("Time taken: %.2f seconds\n", time_taken);

				fWin = fopen("wins.txt", "w");
				Totalwins = Totalwins + 1;
				printf("\nTotal Wins: %d", Totalwins);
				printf("\nTotal Loses: %d\n", loses);
				fprintf(fWin, "%d", Totalwins);
				fclose(fWin);
			}
			else if (done == 'O')
			{
				time_end = clock() - time_start;
				double time_taken = ((double)time_end) / CLOCKS_PER_SEC;

				printf("I won!\n");
				printf("Time taken: %.2f seconds\n", time_taken);

				fLos = fopen("lose.txt", "w");
				loses = loses + 1;
				printf("\nTotal Wins: %d", Totalwins);
				printf("\nTotal Loses: %d\n", loses);
				fprintf(fLos, "%d", loses);
				fclose(fLos);
			}
			else
			{
				break;
			}

			PrintGrid(); /* show final positions */
			break;
		case 2:
			ClearScreen();
			printf("\nInteractive menu made by Brendan");
			printf("\nBoard designed by Michael");
			printf("\nPlayer movement made by Michael");
			printf("\nCPU AI made by Jacob and Michael");
			printf("\nCheckforwin function made by Jacob and Michael");
			printf("\nExternal API added by Mirai and Brandon\n");
			break;
		}
	} while (end == 0);

	return 0;

}