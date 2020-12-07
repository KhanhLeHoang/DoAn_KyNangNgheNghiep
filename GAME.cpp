#include<iostream>
#include"console.h"
#include<conio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

#define consoleWidth 120;
#define consoleHeigh 30;

enum TrangThai {UP,DOWN,RIGHT,LEFT};

struct ToaDo
	{
		int x;
		int y;
	};

struct Snake
	{
		ToaDo dot[30];
		int n;
		TrangThai tt;
	};

struct ThucAn
{
	ToaDo td;
};

void KhoiTao(Snake &snake, ThucAn &food)
{
	
	snake.n = 1;
	do
	{
		snake.dot[0].x = rand() % consoleWidth;
	} while (snake.dot[0].x %2 != 0);
	snake.dot[0].y = rand() % consoleHeigh;
	snake.tt = RIGHT;
	do
	{
		food.td.x = rand() % consoleWidth;
	} while (food.td.x %2 != 0);
	food.td.y = rand() % consoleHeigh;
}

void HienThi(Snake &snake, ThucAn food, int &score)
{
	clrscr();
	TextColor(10);
	gotoXY(50, 14);
	cout << "YOUR SCORE: " << score;
	gotoXY(food.td.x, food.td.y);
	putchar('o');

	TextColor(12);
	gotoXY(snake.dot[0].x, snake.dot[0].y);
	putchar('@');
	for (int i = 1;i < snake.n;i++)
	{
		gotoXY(snake.dot[i].x,snake.dot[i].y);
		putchar('#');
	}
}

void DieuKhien(Snake &snake)
{
	for (int i = snake.n - 1; i > 0; i--)
		snake.dot[i] = snake.dot[i - 1];
	if (_kbhit())
	{
		char key = _getch();
		if (key == 'a' || key == 75)
		{
			if (snake.tt != RIGHT)
				snake.tt = LEFT;
		}
		else if (key == 's' || key == 80)
		{
			if (snake.tt != UP)
				snake.tt = DOWN;
		}
		else if (key == 'd' || key == 77)
		{
			if (snake.tt != LEFT)
				snake.tt = RIGHT;
		}
		else if (key == 'w' || key == 72)
		{
			if (snake.tt != DOWN)
				snake.tt = UP;
		}
	}
	
	if (snake.tt == UP)
		snake.dot[0].y--;
	else if (snake.tt == DOWN)
		snake.dot[0].y++;
	else if (snake.tt == RIGHT)
		snake.dot[0].x+=2;
	else if (snake.tt == LEFT)
		snake.dot[0].x-=2;
}

int XuLy(Snake &snake, ThucAn &food, int &timesleep, int &score)	//Hàm trả về -1 nếu gameover
{
	// Xử lý ăn thức ăn
	if (snake.dot[0].x == food.td.x && snake.dot[0].y == food.td.y)
	{
		for (int i = snake.n; i > 0; i--)
		{
			snake.dot[i] = snake.dot[i - 1];	//dời về 1 đốt
		}
		snake.n++;
		//Mọc thêm đầu
		if (snake.tt == UP)
			snake.dot[0].y--;
		else if (snake.tt == DOWN)
			snake.dot[0].y++;
		else if (snake.tt == RIGHT)
			snake.dot[0].x += 2;
		else if (snake.tt == LEFT)
			snake.dot[0].x -= 2;

		// Tạo thức ăn mới
		food.td.y = rand() % consoleHeigh;
		do {
			food.td.x = rand() % consoleWidth;
			} while (food.td.x % 2 != 0);

		// Tăng tốc độ
			if(timesleep >20)
			timesleep -= 4;

		// Tính điểm
			score += 10;
	}

	// Xử lý chạm biên
	if (snake.dot[0].x < 0 || snake.dot[0].y < 0 || snake.dot[0].y >= 30 || snake.dot[0].x >= 120)
	{
		return -1;
	}

	//Xử lý chạm thân
	for (int i = snake.n; i > 0;i--)
	{
		if (snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y)
			return -1;
	}
	return 0;
}

int main()
{
	while(1)
	{
		int timesleep = 50;
		int ma, score = 0;
		srand((int)time(0));
		Snake	snake;
		ThucAn food;
		KhoiTao(snake, food);
		gotoXY(45, 12);
		TextColor(5);
		cout << "PRESS ENTER TO START A NEW GAME" << "\n\n\n\n\t\t\t\t\t   ";
		while (_getch() != 13);	//Mã ENTER là 13
		{
			while (1)
			{
				//Hiển thị
				HienThi(snake, food, score);

				//Điều khiển
				DieuKhien(snake);

				//Xử lý
				ma = XuLy(snake, food, timesleep, score);
				if (ma == -1)
				{
					gotoXY(52, 10);
					cout << "GAME OVER" << "\n\n\n\n\t\t\t\t\t   ";
					break;
				}
				Sleep(timesleep);
			}
		}
	}
}