#include "libraries.h"

bool game_over, up_down = 1, left_right = 1;//дл€ выхода из игры
const int width = 50, height = 20;//размер окна
int x, y, fruit_x, fruit_y, score;// координаты головы, координаты фрукта, кол-во очков
int n_tail, tail_x[100], tail_y[100];// это дл€ хвоста
enum e_direction { STOP = 0, LEFT, RIGHT, UP, DOWN };//перечисл€емый тип
e_direction dir;





//BOOL SetConsoleCursorInfo(BOOL bShow)
//{
//	CONSOLE_CURSOR_INFO cci;
//	HANDLE hStdOut;
//	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	if (hStdOut == INVALID_HANDLE_VALUE)
//		return FALSE;
//	if (!GetConsoleCursorInfo(hStdOut, &cci))
//		return FALSE;
//	cci.bVisible = bShow;
//	if (!SetConsoleCursorInfo(hStdOut, &cci))
//		return FALSE;
//	return TRUE;
//}
//int main(int argc, char* argv[])
//{
//	Sleep(5000);
//	ShowConsoleCursor(FALSE);
//	Sleep(5000);
//	ShowConsoleCursor(TRUE);
//	Sleep(5000);
//	return 0;
//}
void setcur_s(int x, int y)//установка курсора на позицию  x y                  //функци€ дл€ немигающего экрана
{
	CONSOLE_CURSOR_INFO cci;
	COORD coord;

	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);


}; 

void draw()//функци€ прорисовки
{
	setcur_s(0, 0);//очищение экрана
	for (int i = 0; i < width + 1; i+=2)//вывод верхней грани
	{
		cout << "#"<<" ";
	}
	printf("\n");

	for (int i = 0; i < height; i++)//вывод боковых граней, фрукта и хвоста
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)//боковые грани
			{
				printf("#");
			}
			if (i == y && j == x)//голова змеи
			{
				printf("O");
			}
			else if (i == fruit_y && j == fruit_x)//фрукт
			{
				printf("f");
			}
			else
			{
				bool print = false;
				for (int k = 0; k < n_tail; k++)//хвост
				{
					if (tail_x[k] == j && tail_y[k] == i)
					{
						print = true;
						cout << "o";
					}
				}
				if (print == false)
					cout << " ";
			}

		}
		printf("\n");
	}


	for (int i = 0; i < width + 1; i+=2)//нижн€€ грань
	{
		cout << "#"<<" ";
	}
	printf("\n");
	cout << "SCOPE " << score;//вывод очков
}

void input()//функци€ ввода
{
	if (_kbhit())
	{
		/*SetConsoleCP(1251);              //наверное не нужно
		SetConsoleOutputCP(1251);*/
		switch (_getch())
		{

		case 'a':
			if(left_right == true)
			{
				dir = LEFT;
				up_down = 1;
				left_right = 0;
			}
			
			break;
		case 'w':
			if (up_down == 1)
			{
				dir = UP;
				up_down = 0;
				left_right = 1;
			}
			
			break;
		case 'd':
			if (left_right == true)
			{
				dir = RIGHT;
				up_down = 1;
				left_right = 0;
			}
			
			break;
		case 's':
			if (up_down == 1)
			{
				dir = DOWN;
				up_down = 0;
				left_right = 1;
			}
		
			break;
			/*case 'ф':                      //не работает
				dir = LEFT;
				break;
			case 'ц':
				dir = UP;
				break;
			case 'в':
				dir = RIGHT;
				break;
			case 'ы':
				dir = DOWN;
				break;*/
		case 'f':
			game_over = true;
			break;
			/*	case 'а':
					game_over = true;                //не работает
					break;*/
		}
	}
}

void setup()//функци€ начальных условий
{
	game_over = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruit_x = rand() % width;
	fruit_y = rand() % height;
	score = 0;
}

void logic()//игровые правила
{
	int prev_x = tail_x[0], prev_y = tail_y[0];//это дл€ хвоста
	int prev_2x, prev_2y;//это тоже
	tail_x[0] = x;
	tail_y[0] = y;
	for (int i = 1; i < n_tail; i++)//координаты хвоста
	{
		prev_2x = tail_x[i];
		prev_2y = tail_y[i];
		tail_x[i] = prev_x;
		tail_y[i] = prev_y;
		prev_x = prev_2x;
		prev_y = prev_2y;

	}
	switch (dir)//движени€ змеи
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	//if (x > width || x < 0||y>height||y<0)    //если надо,чтобы зме€ разбивалась о стены, то это раскомментить
	//	game_over = true;
	if (x >= width - 1)        // переход к противоположной стене
		x = 0;
	else if (x < 0)
		x = width - 2;

	if (y >= height )
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 1; i < n_tail; i++)// после захода на хвост игра заканчиваетс€
	{
		if (tail_x[i] == x && tail_y[i] == y)
		{
			game_over = true;
		}
	}
	if (x == fruit_x && y == fruit_y)//после поедани€ фрукта произойдет это
	{
		score += 10;
		fruit_x = rand() % width;
		fruit_y = rand() % height;
		n_tail++;
	}
}

void snake()
{


	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setup();
	while (game_over == false)
	{
		draw();
		input();
		logic();
	}
	game_over = false;
	up_down = 1; left_right = 1;
	n_tail = 0;
	cout << endl << "»гра окончена, нажмите f, чтобы выйти ";
	do {
#pragma warning(disable : 4996)
		if (_kbhit())
		{
			getch();
		}

	} while (getch() != 'f');
	


}
