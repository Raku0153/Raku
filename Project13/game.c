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

//게임 내에서 사용할 키 컨트롤
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

//메뉴 키 컨트롤(khbit 없음)
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

	//이동할 장소에 장애물이 있는지 확인
	if (mapObject == '0') {
		tempMap[*y][*x] = '0';
		tempMap[*y + _y][*x + _x] = 'p';
		*x += _x;
		*y += _y;
		return TRUE;
	}
	return FALSE;
}

//게임 시작시 플레이어 위치 가져오는 함수
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
	printscr("현재무기: ");
	switch (selectWeapon) {
	case HG:
		printscr("HG");
		gotoxy(30, 24);	printscr("            ■  ■                            ");
		gotoxy(30, 25);	printscr("        ■■■■■■■■■■■■■■■■■■■");
		gotoxy(30, 26);	printscr("      ■            ■■                  ■■");
		gotoxy(30, 27);	printscr("    ■                                    ■  ");
		gotoxy(30, 28);	printscr("      ■■■      ■■■■■■■■■■■■■  ");
		gotoxy(30, 29);	printscr("          ■    ■  ■  ■                    ");
		gotoxy(30, 30);	printscr("        ■    ■    ■  ■                    ");
		gotoxy(30, 31);	printscr("      ■    ■■■■■■                      ");
		gotoxy(30, 32);	printscr("    ■    ■                                  ");
		gotoxy(30, 33);	printscr("      ■■                                      ");
		gotoxy(30, 34);	printscr("                                                                                           ");
		//space 랑 ■ 랑 크기가 달라서 그림이 깨져보이는데 콘솔상으론 제대로 보임
		gotoxy(10, 24);
		break;
	case AR:
		printscr("AR");
		gotoxy(30, 24);	printscr("            ■■■■■■■■■■■■■■■■■■■■■■■            ■  ");
		gotoxy(30, 25);	printscr("■■■    ■                                              ■■■■■■■■");
		gotoxy(30, 26);	printscr("■    ■■    ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(30, 27);	printscr("■          ■  ■  ■■      ■  ■    ■■■");
		gotoxy(30, 28);	printscr("■        ■    ■  ■        ■  ■ ");
		gotoxy(30, 29);	printscr("■      ■      ■  ■        ■  ■");
		gotoxy(30, 30);	printscr("■■■■        ■■■        ■  ■");
		gotoxy(30, 31);	printscr("                              ■■  ■");
		gotoxy(30, 32);	printscr("                                ■  ■■");
		gotoxy(30, 33);	printscr("                                  ■■");
		gotoxy(10, 24);
		break;
	case SG:
		printscr("SG");

		gotoxy(30, 24);	printscr("                                                                                            ");
		gotoxy(30, 25);	printscr("                  ■■■■■■■■■■■■■■■■■■                                      ");
		gotoxy(30, 26);	printscr("              ■■■■■■■■■■■■■■■■■■■■■■■■                              ");
		gotoxy(30, 27);	printscr("          ■■■      ■■              ■■■■■■■                                      ");
		gotoxy(30, 28);	printscr("      ■■■■  ■    ■■■■■■■■■■  ■  ■  ■■■■                                ");
		gotoxy(30, 29);	printscr("    ■    ■■■■■■■■■■■■■■■■  ■  ■  ■■■■                                ");
		gotoxy(30, 30);	printscr("  ■    ■    ■  ■  ■                ■■■■■■■                                      ");
		gotoxy(30, 31);	printscr("■    ■      ■■■■                                                                      ");
		gotoxy(30, 32);	printscr("■  ■■                                                                                    ");
		gotoxy(30, 33);	printscr("■■■                                                                                      ");
		gotoxy(30, 34);	printscr("                                                                                            ");

		gotoxy(10, 24);

		break;
	case SR:
		printscr("SR");

		gotoxy(30, 24);	printscr("                  ■■■                                                                    ");
		gotoxy(30, 25);	printscr("                ■■■■■              ■                                                  ");
		gotoxy(30, 26);	printscr("                  ■  ■                ■                                                  ");
		gotoxy(30, 27);	printscr("  ■■■■■■■■■■■■■■■■■■■■■■■                                          ■");
		gotoxy(30, 28);	printscr("■■                              ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(30, 29);	printscr("■                                                ■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(30, 30);	printscr("■■■■■■■■■■■■■■■■■■■■■■■■■■■                                      ");
		gotoxy(30, 31);	printscr("■    ■      ■■■      ■  ■  ■        ■                                              ");
		gotoxy(30, 32);	printscr("■    ■      ■■        ■■■■          ■                                              ");
		gotoxy(30, 33);	printscr("  ■  ■                                    ■                                              ");
		gotoxy(30, 34);	printscr("    ■■                                    ■                                              ");

		gotoxy(10, 24);

		break;
	}

	gotoxy(10, 25);
	printscr("남은 총알: ");
	int weaponBullet = weapon[selectWeapon].bullet;

	char* weaponBullet_char = (char*)malloc(sizeof(char) * 4);
	_itoa(weaponBullet, weaponBullet_char, 10);
	printscr(weaponBullet_char);
}

//전체 맵 그리기
void drawMap(int* x, int* y)
{
	//뒷장 페이지 초기화
	scr_clear();
	//테두리 그리기
	border();
	drawInfo();
	gotoxy(MAPXSTART, 1);
	//플레이어 기준 x값 최소, 최대 | y값 최소 최대 결정
	int hLow, hHigh, wLow, wHigh;

	//위, 아래, 왼쪽, 오른쪽 끝으로 갔을때 작아진 부분만큼 반대쪽 맵 크기 늘리기
	int hUpDif = 0, hDownDif = 0, wLeftDif = 0, wRightDif = 0;
	int i = 1;

	//맵의 최소, 최대값 설정
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

	//맵 그리기
	for (int h = hLow; h <= hHigh; h++) {
		for (int w = wLow; w <= wHigh; w++) {
			char temp = tempMap[h][w];
			if (temp == '0') {
				printscr("  ");
			}
			else if (temp == '1') {
				printscr("■");
			}
			else if (temp == '2') {
				textcolor(GREEN1, GREEN1);
				printscr("♤");
				textcolor(WHITE, BLACK);
			}
			else if (temp == '3') {
				textcolor(GRAY1, GRAY1);
				printscr("♠");
				textcolor(WHITE, BLACK);
			}
			else if (temp == '4') {
				//textcolor(WHITE, WHITE);
				printscr("  ");
				//textcolor(WHITE, BLACK);
			}
			else if (temp == '5') {
				textcolor(RED1, RED1);
				printscr("♥");
				textcolor(WHITE, BLACK);
			}
			else if (temp == '6') {
				textcolor(CYAN1, CYAN1);
				printscr("♧");
				textcolor(WHITE, BLACK);
			}
			else if (temp == 'p') {
				*x = w;
				*y = h;
				textcolor(MAGENTA1, MAGENTA1);
				printscr("☆");
				textcolor(WHITE, BLACK);
			}
			//가로총알
			else if (temp == 'w') {
				printscr("─");
			}
			//세로총알
			else if (temp == 'h') {
				printscr("│");
			}
			//샷건
			else if (temp == 's') {
				printscr("⊙");
			}
			//몬스터
			else if (temp == 'q') {
				printscr("◆");       //100
			}
			else if (temp == 't') {
				printscr("◇");       //200
			}
			else if (temp == 'e') {
				printscr("▲");        //50
			}
			else if (temp == 'r') {
				printscr("△");       //80
			}
		}
		i++;
		gotoxy(MAPXSTART, i);
	}

	//뒷장, 앞장 전환
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

	//게임 시작시 플레이어 위치 가져오기
	userData(&x, &y);

	gameInit();

	while (1) {

		runTime = time(NULL) - startTime;

		//캐릭터 움직임에 변화가 있을시 맵 다시 그리기
		if (changeData == TRUE)
			drawMap(&x, &y);

		if (frameCount % monsterFrameSync == 0)
			spawnMonster();
		Sleep(delay);
		frameCount++;

		int keyData = keyControl();

		switch (keyData) {
			//위, 아래, 왼쪽, 오른쪽 이동
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
			//방향키로 공격
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
