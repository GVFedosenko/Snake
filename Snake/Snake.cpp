#include <iostream>
#include <conio.h>

using namespace std;
	
bool gameOver;
const int width = 20;// высота
const int height = 20;// ширина
int x, y, fruitX, fruitY;// координаты головы змейки и фруктов
int score;// подсчет очков
int tailX[100], tailY[100]; // хвост
int nTail;// количество элементов в хвосте, по дехолту 0
enum eMotion {STOP = 0, LEFT, RIGHT, UP, DOWN };// движение змейки
eMotion dir;

void Setup() {
    gameOver = false;
	dir = STOP;
    x = width / 2 -1;
    y = height / 2 -1;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Map() {
		system("cls");
		for (int i = 0; i < width - 1; i++) {
			cout << "##";
		} cout << endl;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (j == 0 || j == width - 1) {
					cout << "@";
				} 
				else if (i == y && j == x) {
					cout << "0";
				}
				else if (i == fruitY && j == fruitX) {
					cout << "F";
				}
				else {
					bool print = false;
					for (int k = 0; k < nTail; k++) {
						if (tailX[k] == j && tailY[k] == i) {
							print = true;
							cout << "o";
						}
					}
					if (!print) {
						cout << " ";
					}
					cout << " ";
				}
			} cout << endl;
		}

		for (int i = 0; i < width - 1; i++) {
			cout << "##";
		} cout << endl;
		cout << "score: " << score << endl;
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'w':
			dir = UP;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) {
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
	} /*if (x > WIDTH || x < 0 || y > HEIGHT || y < 0) {
		gameOver = true;
		setlocale(LC_ALL, "RUS");
		cout << "***************" << endl;
		cout << "Вы проиграли!!!" << endl;
		cout << "***************" << endl;
		system("pause");
	}*/ 
	
	if (x >= width) {
		x = 0;
	}
	else if (x < 0) {
		x = width - 1;
	} 
	else if (y >= height) {
		y = 0;
	}
	else if (y < 0) {
		y = height - 1;
	}
	
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	} for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			setlocale(LC_ALL, "RUS");
			gameOver = true;
			cout << "***************" << endl;
			cout << "Вы проиграли!!!" << endl;
			cout << "***************" << endl;
			system("pause");
		}
	}
}

int main() {
	Setup();
	while (!gameOver) {
		Map();
		Input();
		Logic();
	}
}