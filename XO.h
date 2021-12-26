#include "libraries.h"

using namespace std;
namespace XO_variable
{
	bool player, game_over;
	char name_first[15], name_second[15];
	int x, y, x_cursor, y_cursor;
	enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };//перечисляемый тип
	enum chunks { NOTHING, X, O };
	direction dir;
	chunks chunk[3][3] =
	{
		{NOTHING, NOTHING, NOTHING},
		{NOTHING, NOTHING, NOTHING},
		{NOTHING, NOTHING, NOTHING}
	};

	void setcur(int x, int y)//установка курсора на позицию  x y                  //функция для немигающего экрана
	{
		CONSOLE_CURSOR_INFO cci;
		COORD coord;

		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);


	};

	char f = 'x', OX_c = 'o';
	char XO[19][37] =
	{
		{ f, ' ', f, ' ', f, ' ', f, ' ', f, ' ', f, ' ',f, ' ', f, ' ', f, ' ', f, ' ', f, ' ', f, ' ',f, ' ', f, ' ', f, ' ', f, ' ', f,  ' ',f, ' ',f},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f, ' ', f, ' ', f, ' ', f, ' ', f, ' ', f, ' ',f, ' ', f, ' ', f, ' ', f, ' ', f, ' ', f, ' ',f, ' ', f, ' ', f, ' ', f, ' ', f,  ' ',f, ' ',f},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f, ' ', f, ' ', f, ' ', f, ' ', f, ' ', f, ' ',f, ' ', f, ' ', f, ' ', f, ' ', f, ' ', f, ' ',f, ' ', f, ' ', f, ' ', f, ' ', f,  ' ',f, ' ',f},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', f,},
		{ f, ' ', f, ' ', f, ' ', f, ' ', f, ' ', f, ' ',f, ' ', f, ' ', f, ' ', f, ' ', f, ' ', f, ' ',f, ' ', f, ' ', f, ' ', f, ' ', f,  ' ',f, ' ',f}
	};
	char X_picture[5][11] =
	{
		{' ',OX_c,OX_c,' ',' ',' ',' ',' ',OX_c,OX_c,' '},
		{' ',' ',' ',OX_c,' ',' ',' ',OX_c,' ',' ',' '},
		{' ',' ',' ',' ',' ',OX_c,' ',' ',' ',' ',' '},
		{' ',' ',' ',OX_c,' ',' ',' ',OX_c,' ',' ',' '},
		{' ',OX_c,OX_c,' ',' ',' ',' ',' ',OX_c,OX_c,' '}
	};
	char O_picture[5][11] =
	{
		{' ',' ',' ',' ',OX_c,OX_c,OX_c,' ',' ',' ',' '},
		{' ',' ',OX_c,' ',' ',' ',' ',' ',OX_c,' ',' '},
		{' ',OX_c,' ',' ',' ',' ',' ',' ',' ',OX_c,' '},
		{' ',' ',OX_c,' ',' ',' ',' ',' ',OX_c,' ',' '},
		{' ',' ',' ',' ',OX_c,OX_c,OX_c,' ',' ',' ',' '},
	};

	char NULL_picture[5][11] =
	{
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	};
}

void setcur(int x, int y)//установка курсора на позицию  x y                  //функция для немигающего экрана
{
	CONSOLE_CURSOR_INFO cci;
	COORD coord;

	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);


};

void exit_game_XO()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			XO_variable::chunk[i][j] = XO_variable::NOTHING;
		}
		
	}
	
	XO_variable::y_cursor = 1;
	XO_variable::x_cursor = 1;
	for (int t = 0; t < 3; t++)
	{
		for (int k = 0; k < 3; k++)
		{
			for (int i = 0; i < 5; i++)
			{
				
				for (int j = 0; j < 11; j++)
				{
					XO_variable::XO[i + XO_variable::y_cursor][j + XO_variable::x_cursor] = XO_variable::NULL_picture[i][j];

				}
			}
			XO_variable::x_cursor += 12;
		}
		XO_variable::x_cursor = 1;
		XO_variable::y_cursor += 6;
	}
	
	

	XO_variable::game_over = false;
}

void setup_XO()
{
	XO_variable::player = 1;
	XO_variable::game_over = false;
	XO_variable::x = 18;
	XO_variable::y = 9;
	XO_variable::dir = XO_variable::STOP;
	XO_variable::x_cursor = XO_variable::x;
	XO_variable::y_cursor = XO_variable::y;
}

void draw_XO()
{

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 37; j++)
		{

			if (i == XO_variable::y && j == XO_variable::x)
			{
				char buf_field;
				buf_field = XO_variable::XO[i][j];
				XO_variable::XO[i][j] = 0x9f;
				cout << XO_variable::XO[i][j];
				XO_variable::XO[i][j] = buf_field;
			}
			else
			{
				cout << XO_variable::XO[i][j];
			}

		}
		cout << endl;
	};

}

void input_XO()//функция ввода
{
	bool true_input_XO = 0;
	do {
		if (_kbhit())
		{
			/*SetConsoleCP(1251);              //наверное не нужно
			SetConsoleOutputCP(1251);*/
			switch (_getch())
			{

			case 'a':
				XO_variable::dir = XO_variable::LEFT;
				true_input_XO = 1;
				break;
			case 'w':
				XO_variable::dir = XO_variable::UP;
				true_input_XO = 1;
				break;
			case 'd':
				XO_variable::dir = XO_variable::RIGHT;
				true_input_XO = 1;
				break;
			case 's':
				XO_variable::dir = XO_variable::DOWN;
				true_input_XO = 1;
				break;
			case 'f':
				XO_variable::x_cursor -= 5;
				XO_variable::y_cursor -= 2;
				int i_chunk = XO_variable::y_cursor / 6, j_chunk = XO_variable::x_cursor / 12;
				if (XO_variable::chunk[i_chunk][j_chunk] == XO_variable::X || XO_variable::chunk[i_chunk][j_chunk] == XO_variable::O)
				{
					true_input_XO = 1;
					XO_variable::x_cursor += 5;
					XO_variable::y_cursor += 2;
					break;
				}
				if (XO_variable::player == 1)
				{
					for (int i = 0; i < 5; i++)
					{
						for (int j = 0; j < 11; j++)
						{
							XO_variable::XO[i + XO_variable::y_cursor][j + XO_variable::x_cursor] = XO_variable::X_picture[i][j];
						}
						//cout << endl;
					}
					XO_variable::chunk[i_chunk][j_chunk] = XO_variable::X;
					XO_variable::player = 0;
				}
				else
				{
					for (int i = 0; i < 5; i++)
					{
						for (int j = 0; j < 11; j++)
						{
							XO_variable::XO[i + XO_variable::y_cursor][j + XO_variable::x_cursor] = XO_variable::O_picture[i][j];
						}
						/*cout << endl;*/
					}
					XO_variable::chunk[i_chunk][j_chunk] = XO_variable::O;
					XO_variable::player = 1;
				}
				true_input_XO = 1;
				XO_variable::x_cursor += 5;
				XO_variable::y_cursor += 2;
				XO_variable::x = 18;
				XO_variable::y = 9;
				XO_variable::x_cursor = XO_variable::x;
				XO_variable::y_cursor = XO_variable::y;
				break;
			}
		}

	} while (true_input_XO == 0);

}

void logic_XO()
{


	switch (XO_variable::dir)
	{
	case XO_variable::LEFT:
		if (XO_variable::x == 6)
		{
			break;
		}
		else
		{
			XO_variable::x -= 12;
			XO_variable::dir = XO_variable::STOP;
			break;
		}
	case XO_variable::RIGHT:
		if (XO_variable::x == 30)
		{
			break;
		}
		else
		{
			XO_variable::x += 12;
			XO_variable::dir = XO_variable::STOP;
			break;
		}
	case XO_variable::UP:
		if (XO_variable::y == 3)
		{
			break;
		}
		else
		{
			XO_variable::y -= 6;
			XO_variable::dir = XO_variable::STOP;
			break;
		}
	case XO_variable::DOWN:
		if (XO_variable::y == 15)
		{
			break;
		}
		else
		{
			XO_variable::y += 6;
			XO_variable::dir = XO_variable::STOP;
			break;
		}
	}

	XO_variable::x_cursor = XO_variable::x;
	XO_variable::y_cursor = XO_variable::y;

	if ((XO_variable::chunk[0][0] == XO_variable::X && XO_variable::chunk[0][1] == XO_variable::X && XO_variable::chunk[0][2] == XO_variable::X) 
		|| (XO_variable::chunk[1][0] == XO_variable::X && XO_variable::chunk[1][1] == XO_variable::X && XO_variable::chunk[1][2] == XO_variable::X) 
		|| (XO_variable::chunk[2][0] == XO_variable::X && XO_variable::chunk[2][1] == XO_variable::X && XO_variable::chunk[2][2] == XO_variable::X) 
		|| (XO_variable::chunk[0][0] == XO_variable::X && XO_variable::chunk[1][0] == XO_variable::X && XO_variable::chunk[2][0] == XO_variable::X)
		|| (XO_variable::chunk[0][1] == XO_variable::X && XO_variable::chunk[1][1] == XO_variable::X && XO_variable::chunk[2][1] == XO_variable::X) 
		|| (XO_variable::chunk[0][2] == XO_variable::X && XO_variable::chunk[1][2] == XO_variable::X && XO_variable::chunk[2][2] == XO_variable::X)
		|| (XO_variable::chunk[0][0] == XO_variable::X && XO_variable::chunk[1][1] == XO_variable::X && XO_variable::chunk[2][2] == XO_variable::X)
		|| (XO_variable::chunk[0][2] == XO_variable::X && XO_variable::chunk[1][1] == XO_variable::X && XO_variable::chunk[2][0] == XO_variable::X)
		and XO_variable::game_over != true )
	{
		setcur(0,0);
		cout << endl;
		draw_XO();
		cout << endl << "игрок " << XO_variable::name_first << " победил!";
		XO_variable::game_over = true;
	}
	if ((XO_variable::chunk[0][0] == XO_variable::O && XO_variable::chunk[0][1] == XO_variable::O && XO_variable::chunk[0][2] == XO_variable::O) 
		|| (XO_variable::chunk[1][0] == XO_variable::O && XO_variable::chunk[1][1] == XO_variable::O && XO_variable::chunk[1][2] == XO_variable::O)
		|| (XO_variable::chunk[2][0] == XO_variable::O && XO_variable::chunk[2][1] == XO_variable::O && XO_variable::chunk[2][2] == XO_variable::O)
		|| (XO_variable::chunk[0][0] == XO_variable::O && XO_variable::chunk[1][0] == XO_variable::O && XO_variable::chunk[2][0] == XO_variable::O)
		|| (XO_variable::chunk[0][1] == XO_variable::O && XO_variable::chunk[1][1] == XO_variable::O && XO_variable::chunk[2][1] == XO_variable::O) 
		|| (XO_variable::chunk[0][2] == XO_variable::O && XO_variable::chunk[1][2] == XO_variable::O && XO_variable::chunk[2][2] == XO_variable::O)
		|| (XO_variable::chunk[0][0] == XO_variable::O && XO_variable::chunk[1][1] == XO_variable::O && XO_variable::chunk[2][2] == XO_variable::O) 
		|| (XO_variable::chunk[0][2] == XO_variable::O && XO_variable::chunk[1][1] == XO_variable::O && XO_variable::chunk[2][0] == XO_variable::O)
		and XO_variable::game_over != true)
	{
		setcur(0, 0);
		cout << endl;
		draw_XO();
		cout << endl << "Игрок "<< XO_variable::name_second<< " победил!";
		XO_variable::game_over = true;
	}
	if ((XO_variable::chunk[0][0] == XO_variable::O || XO_variable::chunk[0][0] == XO_variable::X) &&
		(XO_variable::chunk[1][0] == XO_variable::O || XO_variable::chunk[1][0] == XO_variable::X) &&
		(XO_variable::chunk[2][0] == XO_variable::O || XO_variable::chunk[2][0] == XO_variable::X) &&
		(XO_variable::chunk[0][1] == XO_variable::O || XO_variable::chunk[0][1] == XO_variable::X) &&
		(XO_variable::chunk[1][1] == XO_variable::O || XO_variable::chunk[1][1] == XO_variable::X) &&
		(XO_variable::chunk[1][2] == XO_variable::O || XO_variable::chunk[1][2] == XO_variable::X) &&
		(XO_variable::chunk[2][0] == XO_variable::O || XO_variable::chunk[2][0] == XO_variable::X) &&
		(XO_variable::chunk[2][1] == XO_variable::O || XO_variable::chunk[2][1] == XO_variable::X) &&
		(XO_variable::chunk[2][2] == XO_variable::O || XO_variable::chunk[2][2] == XO_variable::X)
		and XO_variable::game_over != true)
	{
		
		cout << endl;
		draw_XO();
		cout << endl << "Ничья!";
		XO_variable::game_over = true;
	}
}

void XO_game()
{
	
	cout << "Введите имя первого игрока" << endl;
	cin >> XO_variable::name_first;
	cout << "Введите имя второго игрока" << endl;
	cin >> XO_variable::name_second;
	setup_XO();
	do
	{
		setcur(0, 0);
		if (XO_variable::player == 1)
		{
			cout << "ходит игрок "<< XO_variable::name_first<<" (X)" << endl;
		}
		else
		{
			cout << "ходит игрок " << XO_variable::name_second << " (O)" << endl;
		}
		draw_XO();
		input_XO();
		logic_XO();
	} while (XO_variable::game_over == false);
	exit_game_XO();
	cout << endl << "Игра окончена, нажмите f, чтобы выйти ";
	do {
#pragma warning(disable : 4996)
		if (_kbhit())
		{
			getch();
		}

	} while (getch() != 'f');

}