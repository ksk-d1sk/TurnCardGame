#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** animalArray;
int** checkAnimal;
char** strAnimal;
char* strDifficulty;
int difficulty;
short height = 3;
short width = 4;

void initDifficulty();
void initAnimalArray();
void initAnimalName();
void shuffleAnimal();
int getEmptyPosition();
int conv_pos_x(int x);
int conv_pos_y(int y);
void printAnimals();
void printQuestion();
int foundAllAnimals();

int main(void)
{
	srand(time(NULL));

	initDifficulty();
	initAnimalArray();
	initAnimalName();

	shuffleAnimal();
//	system("cls");
	
	int failCount = 0;

	while (1)
	{
		int select1 = 0;
		int select2 = 0;

		printf("%s 난이도\n", strDifficulty);
		printAnimals();  //정답표시모드
		printQuestion();
		printf("뒤집을 카드를 2개 고르세요  >>  ");
		scanf_s("%d %d", &select1, &select2);
//		system("cls");

		if (select1 == select2)
		{
			continue;
		}

		select1--;
		select2--;

		int firstSelect_x = conv_pos_x(select1);
		int firstSelect_y = conv_pos_y(select1);

		int secondSelect_x = conv_pos_x(select2);
		int secondSelect_y = conv_pos_y(select2);

		if (checkAnimal[firstSelect_x][firstSelect_y] == 0 &&
			checkAnimal[secondSelect_x][secondSelect_y] == 0
			&&
			animalArray[firstSelect_x][firstSelect_y] ==
			animalArray[secondSelect_x][secondSelect_y])
		{
			printf("\n\n정답! : %s발견\n\n", strAnimal[animalArray[firstSelect_x][firstSelect_y]]);
			checkAnimal[firstSelect_x][firstSelect_y] = 1;
			checkAnimal[secondSelect_x][secondSelect_y] = 1;
		}
		else
		{
			printf("\n\n 틀렸습니다!\n");
			printf("%d : %s\n", select1 + 1, strAnimal[animalArray[firstSelect_x][firstSelect_y]]);
			printf("%d : %s\n", select2 + 1, strAnimal[animalArray[secondSelect_x][secondSelect_y]]);
			printf("\n\n");

			failCount++;
		}

		if (foundAllAnimals())
		{
			printf("Clear!!!\n");
			printf("실수 횟수: %d", failCount);
			break;
		}
	}
	
	return 0;
}

void initDifficulty()
{
	printf("(1: 쉬움    2: 보통    3: 어려움)\n");
	printf("난이도를 선택하세요  >>   ");

	short i = 1;
	while (i--)
	{
		scanf_s("%d", &difficulty);
		if (0 > difficulty || difficulty > 3)
		{
			printf("올바른 난이도가 아닙니다. 다시 선택하십시오  >>  ");
			i++;
		}
	}

	if (difficulty == 0)
	{
		strDifficulty = "인세인";
		exit(0);
		height = 10;
		width = 10;
	}
	else if (difficulty == 1)
	{
		strDifficulty = "쉬움";
	}
	else if (difficulty == 2)
	{
		strDifficulty = "보통";
		height = 4;
	}
	else if (difficulty == 3)
	{
		strDifficulty = "어려움";
		height = 4;
		width = 5;
	}
}

void initAnimalArray()
{
	animalArray = (int**)malloc(height);
	checkAnimal = (int**)malloc(height);

	for (int i = 0; i < width; i++)
	{
		animalArray[i] = (int*)malloc(width);
		checkAnimal[i] = (int*)malloc(width);
	}

	for(int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			animalArray[i][j] = -1;
			checkAnimal[i][j] = 0;
		}
	}
}

void initAnimalName()
{
	int animalSize = (int)(height * width / 2);
	strAnimal = (int*)malloc(sizeof(int) * animalSize);

	char* animalName[] = {
		"펭귄", "고양이", "미어켓", "캥거루", "거미",
		"나무늘보", "개구리", "tentacle", "요루", "체임버"
	};

	for (int i = 0; i < animalSize; i++)
	{
		strAnimal[i] = animalName[i];
	}
}

void shuffleAnimal()
{
	int animalSize = height * width / 2;
	for (int i = 0; i < animalSize; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int pos = getEmptyPosition();
			int x = conv_pos_x(pos);
			int y = conv_pos_y(pos);

			animalArray[x][y] = i;
		}
	}
}

int getEmptyPosition()
{
	while (1)
	{
		int randPos = rand() % (height * width);

		int x = conv_pos_x(randPos);
		int y = conv_pos_y(randPos);

		if (animalArray[x][y] == -1)
			return randPos;
	}
	return 0;
}

int conv_pos_x(int x)
{
	return x / width;
}

int conv_pos_y(int y)
{
	return y % width;
}

void printAnimals()
{
	printf("\n============================================\n\n");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%10s", strAnimal[animalArray[i][j]]);
		}
		printf("\n");
	}
	printf("\n============================================\n\n");
}

void printQuestion()
{
	printf("\n\n(문제)\n");
	int seq = 1;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (checkAnimal[i][j] != 0)
				printf("%10s", strAnimal[animalArray[i][j]]);
			else
				printf("%10d", seq);
			seq++;
		}
		printf("\n");
	}
}

int foundAllAnimals()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (checkAnimal[i][j] == 0)
				return 0;
		}
	}

	return 1;
}
