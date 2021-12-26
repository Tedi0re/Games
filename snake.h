#include "libraries.h"

bool game_over, up_down = 1, left_right = 1;//��� ������ �� ����
const int width = 50, height = 20;//������ ����
int x, y, fruit_x, fruit_y, score;// ���������� ������, ���������� ������, ���-�� �����
int n_tail, tail_x[100], tail_y[100];// ��� ��� ������
enum e_direction { STOP = 0, LEFT, RIGHT, UP, DOWN };//������������� ���
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
void setcur_s(int x, int y)//��������� ������� �� �������  x y                  //������� ��� ����������� ������
{
	CONSOLE_CURSOR_INFO cci;
	COORD coord;

	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);


}; 

void draw()//������� ����������
{
	setcur_s(0, 0);//�������� ������
	for (int i = 0; i < width + 1; i+=2)//����� ������� �����
	{
		cout << "#"<<" ";
	}
	printf("\n");

	for (int i = 0; i < height; i++)//����� ������� ������, ������ � ������
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)//������� �����
			{
				printf("#");
			}
			if (i == y && j == x)//������ ����
			{
				printf("O");
			}
			else if (i == fruit_y && j == fruit_x)//�����
			{
				printf("f");
			}
			else
			{
				bool print = false;
				for (int k = 0; k < n_tail; k++)//�����
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


	for (int i = 0; i < width + 1; i+=2)//������ �����
	{
		cout << "#"<<" ";
	}
	printf("\n");
	cout << "SCOPE " << score;//����� �����
}

void input()//������� �����
{
	if (_kbhit())
	{
		/*SetConsoleCP(1251);              //�������� �� �����
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
			/*case '�':                      //�� ��������
				dir = LEFT;
				break;
			case '�':
				dir = UP;
				break;
			case '�':
				dir = RIGHT;
				break;
			case '�':
				dir = DOWN;
				break;*/
		case 'f':
			game_over = true;
			break;
			/*	case '�':
					game_over = true;                //�� ��������
					break;*/
		}
	}
}

void setup()//������� ��������� �������
{
	game_over = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruit_x = rand() % width;
	fruit_y = rand() % height;
	score = 0;
}

void logic()//������� �������
{
	int prev_x = tail_x[0], prev_y = tail_y[0];//��� ��� ������
	int prev_2x, prev_2y;//��� ����
	tail_x[0] = x;
	tail_y[0] = y;
	for (int i = 1; i < n_tail; i++)//���������� ������
	{
		prev_2x = tail_x[i];
		prev_2y = tail_y[i];
		tail_x[i] = prev_x;
		tail_y[i] = prev_y;
		prev_x = prev_2x;
		prev_y = prev_2y;

	}
	switch (dir)//�������� ����
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

	//if (x > width || x < 0||y>height||y<0)    //���� ����,����� ���� ����������� � �����, �� ��� �������������
	//	game_over = true;
	if (x >= width - 1)        // ������� � ��������������� �����
		x = 0;
	else if (x < 0)
		x = width - 2;

	if (y >= height )
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 1; i < n_tail; i++)// ����� ������ �� ����� ���� �������������
	{
		if (tail_x[i] == x && tail_y[i] == y)
		{
			game_over = true;
		}
	}
	if (x == fruit_x && y == fruit_y)//����� �������� ������ ���������� ���
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
	cout << endl << "���� ��������, ������� f, ����� ����� ";
	do {
#pragma warning(disable : 4996)
		if (_kbhit())
		{
			getch();
		}

	} while (getch() != 'f');
	


}
