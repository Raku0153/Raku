#define _CRT_SECURE_NO_WARNINGS

#include "main.h"
#include "game.h"
#include "displayControl.h"
#include "map.h"
#include "attack.h"

typedef struct {
	int x, y;
	int exist;
} BULLET;

int frameCount = 0;
int delay = 10;
int monsterFrameSync = 100;
int monsterCount = 0;
int startTime;
int HGtime, SGtime, SRtime;

MONSTER mon[MAXMONSTER];

//���� ������ ����� Ű ��Ʈ��
int keyControl()
{
	if (_kbhit() == 1) {
		unsigned char temp = _getch();

		if (temp == SPECIAL1 || temp == SPECIAL2) {
			temp = _getch();
			switch (temp) {
			case UP:
				return UP;
				break;
			case DOWN:
				return DOWN;
				break;
			case LEFT:
				return LEFT;
				break;
			case RIGHT:
				return RIGHT;
				break;
			}
		}
		else if (temp == 'w' || temp == 'W')
			return UP2;
		else if (temp == 's' || temp == 'S')
			return DOWN2;
		else if (temp == 'a' || temp == 'A')
			return LEFT2;
		else if (temp == 'd' || temp == 'D')
			return RIGHT2;
		else if (temp == '1') {
			selectWeapon = HG;
		}
		else if (temp == '2') {
			selectWeapon = AR;
		}
		else if (temp == '3') {
			selectWeapon = SG;
		}
		else if (temp == '4') {
			selectWeapon = SR;
		}
		else if (temp == 'e' || temp == 'E') {
			if (selectWeapon == SR) {
				selectWeapon = HG;
			}
			else {
				selectWeapon++;
			}
		}
		else if (temp == ESC)
			exit(1);
		else if (temp == ' ')
			return ATTACK;
	}
}

//�޴� Ű ��Ʈ��(khbit ����)
int keyMenuControl()
{
	char temp = _getch();

	if (temp == 'w' || temp == 'W')
		return UP2;
	else if (temp == 's' || temp == 'S')
		return DOWN2;
	else if (temp == ESC)
		exit(1);
	else if (temp == ' ')
		return SUBMIT;
}

int move(int* x, int* y, int _x, int _y)
{
	char mapObject = tempMap[*y + _y][*x + _x];

	//�̵��� ��ҿ� ��ֹ��� �ִ��� Ȯ��
	if (mapObject == '0') {
		tempMap[*y][*x] = '0';
		tempMap[*y + _y][*x + _x] = 'p';
		*x += _x;
		*y += _y;
		return TRUE;
	}
	return FALSE;
}

//���� ���۽� �÷��̾� ��ġ �������� �Լ�
void userData(int* x, int* y) {
	for (int h = 0; h < 20; h++) {
		for (int w = 0; w < 99; w++) {
			if (tempMap[h][w] == 'p') {
				*x = w;
				*y = h;
				return;
			}
		}
	}
}

void drawInfo() {
	gotoxy(10, 24);
	printscr("���繫��: ");
	switch (selectWeapon) {
	case HG:
		printscr("HG");
		gotoxy(30, 24);	printscr("            ��  ��                            ");
		gotoxy(30, 25);	printscr("        ��������������������");
		gotoxy(30, 26);	printscr("      ��            ���                  ���");
		gotoxy(30, 27);	printscr("    ��                                    ��  ");
		gotoxy(30, 28);	printscr("      ����      ��������������  ");
		gotoxy(30, 29);	printscr("          ��    ��  ��  ��                    ");
		gotoxy(30, 30);	printscr("        ��    ��    ��  ��                    ");
		gotoxy(30, 31);	printscr("      ��    �������                      ");
		gotoxy(30, 32);	printscr("    ��    ��                                  ");
		gotoxy(30, 33);	printscr("      ���                                      ");
		gotoxy(30, 34);	printscr("                                                                                           ");
		//space �� �� �� ũ�Ⱑ �޶� �׸��� �������̴µ� �ֻܼ����� ����� ����
		gotoxy(10, 24);
		break;
	case AR:
		printscr("AR");
		gotoxy(30, 24);	printscr("            ������������������������            ��  ");
		gotoxy(30, 25);	printscr("����    ��                                              ���������");
		gotoxy(30, 26);	printscr("��    ���    �������������������������������");
		gotoxy(30, 27);	printscr("��          ��  ��  ���      ��  ��    ����");
		gotoxy(30, 28);	printscr("��        ��    ��  ��        ��  �� ");
		gotoxy(30, 29);	printscr("��      ��      ��  ��        ��  ��");
		gotoxy(30, 30);	printscr("�����        ����        ��  ��");
		gotoxy(30, 31);	printscr("                              ���  ��");
		gotoxy(30, 32);	printscr("                                ��  ���");
		gotoxy(30, 33);	printscr("                                  ���");
		gotoxy(10, 24);
		break;
	case SG:
		printscr("SG");

		gotoxy(30, 24);	printscr("                                                                                            ");
		gotoxy(30, 25);	printscr("                  �������������������                                      ");
		gotoxy(30, 26);	printscr("              �������������������������                              ");
		gotoxy(30, 27);	printscr("          ����      ���              ��������                                      ");
		gotoxy(30, 28);	printscr("      �����  ��    �����������  ��  ��  �����                                ");
		gotoxy(30, 29);	printscr("    ��    �����������������  ��  ��  �����                                ");
		gotoxy(30, 30);	printscr("  ��    ��    ��  ��  ��                ��������                                      ");
		gotoxy(30, 31);	printscr("��    ��      �����                                                                      ");
		gotoxy(30, 32);	printscr("��  ���                                                                                    ");
		gotoxy(30, 33);	printscr("����                                                                                      ");
		gotoxy(30, 34);	printscr("                                                                                            ");

		gotoxy(10, 24);

		break;
	case SR:
		printscr("SR");

		gotoxy(30, 24);	printscr("                  ����                                                                    ");
		gotoxy(30, 25);	printscr("                ������              ��                                                  ");
		gotoxy(30, 26);	printscr("                  ��  ��                ��                                                  ");
		gotoxy(30, 27);	printscr("  ������������������������                                          ��");
		gotoxy(30, 28);	printscr("���                              ������������������������������");
		gotoxy(30, 29);	printscr("��                                                ����������������������");
		gotoxy(30, 30);	printscr("����������������������������                                      ");
		gotoxy(30, 31);	printscr("��    ��      ����      ��  ��  ��        ��                                              ");
		gotoxy(30, 32);	printscr("��    ��      ���        �����          ��                                              ");
		gotoxy(30, 33);	printscr("  ��  ��                                    ��                                              ");
		gotoxy(30, 34);	printscr("    ���                                    ��                                              ");

		gotoxy(10, 24);

		break;
	}

	gotoxy(10, 25);
	printscr("���� �Ѿ�: ");
	int weaponBullet = weapon[selectWeapon].bullet;

	char* weaponBullet_char = (char*)malloc(sizeof(char) * 4);
	_itoa(weaponBullet, weaponBullet_char, 10);
	printscr(weaponBullet_char);
}

//��ü �� �׸���
void drawMap(int* x, int* y)
{
	//���� ������ �ʱ�ȭ
	scr_clear();
	//�׵θ� �׸���
	border();
	drawInfo();
	gotoxy(MAPXSTART, 1);
	//�÷��̾� ���� x�� �ּ�, �ִ� | y�� �ּ� �ִ� ����
	int hLow, hHigh, wLow, wHigh;

	//��, �Ʒ�, ����, ������ ������ ������ �۾��� �κи�ŭ �ݴ��� �� ũ�� �ø���
	int hUpDif = 0, hDownDif = 0, wLeftDif = 0, wRightDif = 0;
	int i = 1;

	//���� �ּ�, �ִ밪 ����
	if (*y - MAPYHALF < 0) {
		hLow = 0;
		hUpDif = 0 - (*y - MAPYHALF);
	}
	else
		hLow = *y - MAPYHALF;

	if (*y + MAPYHALF > MAPYMAX) {
		hHigh = MAPYMAX;
		hDownDif = (*y + MAPYHALF) - MAPYMAX;
		hLow = hLow - hDownDif;
	}
	else
		hHigh = *y + MAPYHALF + hUpDif;

	if (*x - MAPXHALF < 0) {
		wLow = 0;
		wLeftDif = 0 - (*x - MAPXHALF);
	}
	else
		wLow = *x - MAPXHALF;

	if (*x + MAPXHALF > MAPXMAX) {
		wHigh = MAPXMAX;
		wRightDif = (*x + MAPXHALF) - MAPXMAX;
		wLow = wLow - wRightDif;
	}
	else
		wHigh = *x + MAPXHALF + wLeftDif;

	//�� �׸���
	for (int h = hLow; h <= hHigh; h++) {
		for (int w = wLow; w <= wHigh; w++) {
			char temp = tempMap[h][w];
			if (temp == '0') {
				printscr("  ");
			}
			else if (temp == '1') {
				printscr("��");
			}
			else if (temp == '2') {
				textcolor(GREEN1, GREEN1);
				printscr("��");
				textcolor(WHITE, BLACK);
			}
			else if (temp == '3') {
				textcolor(GRAY1, GRAY1);
				printscr("��");
				textcolor(WHITE, BLACK);
			}
			else if (temp == '4') {
				//textcolor(WHITE, WHITE);
				printscr("  ");
				//textcolor(WHITE, BLACK);
			}
			else if (temp == '5') {
				textcolor(RED1, RED1);
				printscr("��");
				textcolor(WHITE, BLACK);
			}
			else if (temp == '6') {
				textcolor(CYAN1, CYAN1);
				printscr("��");
				textcolor(WHITE, BLACK);
			}
			else if (temp == 'p') {
				*x = w;
				*y = h;
				textcolor(MAGENTA1, MAGENTA1);
				printscr("��");
				textcolor(WHITE, BLACK);
			}
			//�����Ѿ�
			else if (temp == 'w') {
				printscr("��");
			}
			//�����Ѿ�
			else if (temp == 'h') {
				printscr("��");
			}
			//����
			else if (temp == 's') {
				printscr("��");
			}
			//����
			else if (temp == 'q') {
				printscr("��");       //100
			}
			else if (temp == 't') {
				printscr("��");       //200
			}
			else if (temp == 'e') {
				printscr("��");        //50
			}
			else if (temp == 'r') {
				printscr("��");       //80
			}
		}
		i++;
		gotoxy(MAPXSTART, i);
	}

	//����, ���� ��ȯ
	scr_switch();
}

void spawnMonster() {
	while (TRUE) {
		if (monsterCount == MAXMONSTER)
			break;

		mon[monsterCount].x = rand() % MAPXMAX;
		mon[monsterCount].y = rand() % MAPYMAX;
		if (tempMap[mon[monsterCount].y][mon[monsterCount].x] == '0') {
			if (monsterCount % 4 == 0) {
				tempMap[mon[monsterCount].y][mon[monsterCount].x] = 'q';
				mon[monsterCount].hp = 100;
			}
			else if (monsterCount % 4 == 1) {
				tempMap[mon[monsterCount].y][mon[monsterCount].x] = 't';
				mon[monsterCount].hp = 200;
			}
			else if (monsterCount % 4 == 2) {
				tempMap[mon[monsterCount].y][mon[monsterCount].x] = 'e';
				mon[monsterCount].hp = 50;
			}
			else if (monsterCount % 4 == 3) {
				tempMap[mon[monsterCount].y][mon[monsterCount].x] = 'r';
				mon[monsterCount].hp = 80;
			}
			monsterCount++;
			break;
		}
	}
}

void gameInit() {

	weapon[HG].bullet = 100;
	weapon[HG].damage = HGDAMAGE;

	weapon[AR].bullet = 100;
	weapon[AR].damage = ARDAMAGE;

	weapon[SG].bullet = 100;
	weapon[SG].damage = SGDAMAGE;

	weapon[SR].bullet = 100;
	weapon[SR].damage = SRDAMAGE;
}

void game() {

	int x;
	int y;
	int changeData = TRUE;
	int runTime, startTime;

	startTime = time(NULL);

	//���� ���۽� �÷��̾� ��ġ ��������
	userData(&x, &y);

	gameInit();

	while (1) {

		runTime = time(NULL) - startTime;

		//ĳ���� �����ӿ� ��ȭ�� ������ �� �ٽ� �׸���
		if (changeData == TRUE)
			drawMap(&x, &y);

		if (frameCount % monsterFrameSync == 0)
			spawnMonster();
		Sleep(delay);
		frameCount++;

		int keyData = keyControl();

		switch (keyData) {
			//��, �Ʒ�, ����, ������ �̵�
		case UP2:
			changeData = move(&x, &y, 0, -1);
			break;
		case DOWN2:
			changeData = move(&x, &y, 0, 1);
			break;
		case LEFT2:
			changeData = move(&x, &y, -1, 0);
			break;
		case RIGHT2:
			changeData = move(&x, &y, 1, 0);
			break;
			//����Ű�� ����
		case UP:
			attack(&x, &y, 0, -1, 'h');
			drawMap(&x, &y);
			Sleep(50);
			endAttack(&x, &y, 0, -1, 'h');
			drawMap(&x, &y);
			break;
		case DOWN:
			attack(&x, &y, 0, 1, 'h');
			drawMap(&x, &y);
			Sleep(50);
			endAttack(&x, &y, 0, 1, 'h');
			drawMap(&x, &y);
			break;
		case LEFT:
			attack(&x, &y, -1, 0, 'w');
			drawMap(&x, &y);
			Sleep(50);
			endAttack(&x, &y, -1, 0, 'w');
			drawMap(&x, &y);
			break;
		case RIGHT:
			attack(&x, &y, 1, 0, 'w');
			drawMap(&x, &y);
			Sleep(50);
			endAttack(&x, &y, 1, 0, 'w');
			drawMap(&x, &y);
			break;
		}


	}
}
