#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initDifficulty(int diff);
void initAnimalArray();
void initAnimalName();
void shuffleAnimal();
int getEmptyPosition();
int conv_pos_x(int x);
int conv_pos_y(int y);
void printAnimals();
void printQuestion();
int foundAllAnimals();

int** animalArray;
int** checkAnimal;
const char** strAnimal;
const char* strDifficulty;
short height;
short width;

int main_a(void)
{
	srand(time(NULL));
	short difficulty;

	while (1)
	{
		printf("(1: 쉬움    2: 보통    3: 어려움)\n");
		printf("난이도를 선택하세요  >>   ");
		scanf_s("%d", &difficulty);
		if (!(0 > difficulty || difficulty > 3))
		{
			break;
		}
		printf("올바른 난이도가 아닙니다. 다시 선택하십시오\n\n");
	}

	initDifficulty(difficulty);
	initAnimalArray();
	initAnimalName();
	shuffleAnimal();

	system("cls");

	printf("%s 난이도\n\n\n\n", strDifficulty);

	int failCount = 0;

	while (1)
	{
		int select1 = 0;
		int select2 = 0;

		//printAnimals();  //정답표시모드
		printQuestion();
		printf("\n\n뒤집을 카드를 2개 고르세요  >>  ");
		scanf_s("%d %d", &select1, &select2);

		system("cls");

		if ((select1 < 1 || select1 > height * width) || (select2 < 1 || select2 > height * width))
		{
			printf("올바르지 않은 수 입니다: %d, %d\n", select1, select2);
			continue;
		}
		else if (select1 == select2)
		{
			printf("같은 수 2개는 고를 수 없습니다\n");
			continue;
		}

		int firstSelect_x = conv_pos_x(select1 - 1);
		int firstSelect_y = conv_pos_y(select1 - 1);

		int secondSelect_x = conv_pos_x(select2 - 1);
		int secondSelect_y = conv_pos_y(select2 - 1);

		if (checkAnimal[firstSelect_x][firstSelect_y] == 0 &&
			checkAnimal[secondSelect_x][secondSelect_y] == 0 &&
			animalArray[firstSelect_x][firstSelect_y] ==
			animalArray[secondSelect_x][secondSelect_y])
		{
			printf("정답!\n");
			printf("%s 발견\n\n\n", strAnimal[animalArray[firstSelect_x][firstSelect_y]]);
			checkAnimal[firstSelect_x][firstSelect_y] = 1;
			checkAnimal[secondSelect_x][secondSelect_y] = 1;
		}
		else
		{
			printf("틀렸습니다!\n");
			printf("%d : %s\n", select1, strAnimal[animalArray[firstSelect_x][firstSelect_y]]);
			printf("%d : %s\n\n", select2, strAnimal[animalArray[secondSelect_x][secondSelect_y]]);

			failCount++;
		}

		if (foundAllAnimals())
		{
			printf("Clear!!!\n");
			printf("실수 횟수: %d", failCount);
			break;
		}
	}

	for (int i = 0; i < width; i++)
	{
		free(animalArray[i]);
		free(checkAnimal[i]);
	}

//	free(animalArray);
//	free(checkAnimal);
	free(strAnimal);

	return 0;
}

void initDifficulty(int diff)
{
	if (diff == 0)
	{
		strDifficulty = "INSANE";
		exit(1);
		height = 10;
		width = 10;
	}
	else if (diff == 1)
	{
		strDifficulty = "쉬움";
		height = 3;
		width = 4;
	}
	else if (diff == 2)
	{
		strDifficulty = "보통";
		height = 4;
		width = 4;
	}
	else if (diff == 3)
	{
		strDifficulty = "어려움";
		height = 4;
		width = 5;
	}
}

void initAnimalArray()
{
	animalArray = (int**)malloc(sizeof(int*) * height);
	checkAnimal = (int**)malloc(sizeof(int*) * height);

	for (int i = 0; i < width; i++)
	{
		animalArray[i] = (int*)malloc(sizeof(int) * width);
		checkAnimal[i] = (int*)malloc(sizeof(int) * width);
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			animalArray[i][j] = -1;
			checkAnimal[i][j] = 0;
		}
	}
}

void initAnimalName()
{
	int animalSize = (int)(height * width / 2);
	strAnimal = (const char**)malloc(sizeof(const char*) * animalSize);

	const char* animalName[] = {
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
	printf("(문제)\n");
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
