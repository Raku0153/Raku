#include "main.h"
#include "displayControl.h"

//ó�� ���� �޴�
void mainMenu(int x, int y) {
	gotoxy(x, y);
	printscr("Start");
	gotoxy(x, y + 2);
	printscr("How");
	gotoxy(x, y + 4);
	printscr("Exit");
}

//�� ���� �޴�
void mapMenu(int x, int y) {
	gotoxy(x, y);
	printscr("Map1");
	gotoxy(x, y + 2);
	printscr("Map2");
	gotoxy(x, y + 4);
	printscr("Map3");
}

//Ÿ��Ʋ
void title(int x, int y, int choice) {
	gotoxy(0, 5);
	printscr("                      ########      ########       #######   \n");
	printscr("                      ##     ##     ##     ##     ##         \n");
	printscr("                      ##     ##     ##     ##    ##          \n");
	printscr("                      ########      ########     ##          \n");
	printscr("                      ## ###        ##           ##   ###### \n");
	printscr("                      ##   ###      ##           ##     ##   \n");
	printscr("                      ##     ##     ##            ##    ##   \n");
	printscr("                      ##     ##     ##             #######   \n");

	if (choice == 0)
		mainMenu(x, y);
	else if (choice == 1)
		mapMenu(x, y);
}

//w,s�� ��, �Ʒ� ������ �����̽��ٷ� ����
int menuControl(int keyData, int* x, int* y) {
	switch (keyData) {
	case UP2:
		if (*y > 14) {
			gotoxy(*x - 2, *y);
			printscr(" ");
			*y -= 2;
			gotoxy(*x - 2, *y);
			printscr(">");
		}
		else if (*y == 14) {
			gotoxy(*x - 2, *y);
			printscr(">");
		}
		break;

	case DOWN2:
		if (*y < 18) {
			gotoxy(*x - 2, *y);
			printscr(" ");
			*y += 2;
			gotoxy(*x - 2, *y);
			printscr(">");
		}
		else if (*y == 18) {
			gotoxy(*x - 2, *y);
			printscr(">");
		}
		break;

	case ESC:
		exit(1);

	case SUBMIT:
		return *y - 14;
	}
}
//�޴����� �Լ�
int menuChoice() {

	int x = 36;
	int y = 14;
	int select;

	scr_clear();
	title(x, y, 0);
	gotoxy(34, 14);
	printscr(">");
	scr_switch();

	while (TRUE) {
		int keyData = keyMenuControl();

		scr_clear();
		title(36, 14, 0);

		select = menuControl(keyData, &x, &y);
		if (select == 0 || select == 2 || select == 4)
			return select;
		scr_switch();
	}
}

int mapChoice() {
	int x = 36;
	int y = 14;
	int select;

	scr_clear();
	title(x, y, 1);
	gotoxy(34, 14);
	printscr(">");
	scr_switch();

	while (TRUE) {
		int keyData = keyMenuControl();

		scr_clear();
		title(36, 14, 1);

		select = menuControl(keyData, &x, &y);
		if (select == 0 || select == 2 || select == 4)
			return select;
		scr_switch();
	}
}


void how() {
	scr_clear();
	gotoxy(0,3);
	printscr("      W             \n");
	printscr("    A   D  WASD�� ���� ĳ���͸� �����Դϴ�.        \n");
	printscr("      S                                                       \n");

	gotoxy(0, 7); printscr("       ��");
	gotoxy(0, 8); printscr("     ���ࢹ      ����⸦ ���� ���� �� �߻��մϴ�");
	gotoxy(0, 9); printscr("       ��");
	
	gotoxy(65, 2); printscr("�� �� �� �� �븦 ���� ���⸦ �ٲߴϴ�.");
	gotoxy(65, 3); printscr("E ��ư�� ���� ���� ����� �Ѿ�ϴ�.");

	gotoxy(65, 6); printscr("���� HG");
	gotoxy(65, 7); printscr("���� AR");
	gotoxy(65, 8); printscr("���� SG");
	gotoxy(65, 9); printscr("���� RF");
	gotoxy(65, 10); printscr("���� ��� ��ġ �� ������ ���߽�ų �� �ֽ��ϴ�.");


	gotoxy(5, 18); printscr("��(50)   ");
	gotoxy(5, 20); printscr("��(80)   ");
	gotoxy(5, 22); printscr("��(100)");
	gotoxy(5, 24); printscr("��(200)");
	
	gotoxy(10, 28); printscr("EP 1 The Escape");
	gotoxy(10, 30); printscr("EP 2 No Parking");


	gotoxy(60, 19); printscr("                            ��");
	gotoxy(60, 20); printscr("        ��           ��        ��");
	gotoxy(60, 21); printscr("      ����                           ��");
	gotoxy(60, 22); printscr("��  ������    ��               ��");
	gotoxy(60, 23); printscr("�٢�������         ��               ��      ��");
	gotoxy(60, 24); printscr("    ������                ��");
	gotoxy(60, 25); printscr("      ����            ��        ��");
	gotoxy(60, 26); printscr("        ��          ��                   ��");
	gotoxy(60, 27); printscr("                         ��                   ��");




	scr_switch();
	_getch();
}