#include "main.h"
#include "displayControl.h"

//처음 시작 메뉴
void mainMenu(int x, int y) {
	gotoxy(x, y);
	printscr("Start");
	gotoxy(x, y + 2);
	printscr("How");
	gotoxy(x, y + 4);
	printscr("Exit");
}

//맵 선택 메뉴
void mapMenu(int x, int y) {
	gotoxy(x, y);
	printscr("Map1");
	gotoxy(x, y + 2);
	printscr("Map2");
	gotoxy(x, y + 4);
	printscr("Map3");
}

//타이틀
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

//w,s로 위, 아래 조종후 스페이스바로 선택
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
//메뉴선택 함수
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
	printscr("    A   D  WASD를 통해 캐릭터를 움직입니다.        \n");
	printscr("      S                                                       \n");

	gotoxy(0, 7); printscr("       △");
	gotoxy(0, 8); printscr("     ◁□▷      방향기를 통해 조준 및 발사합니다");
	gotoxy(0, 9); printscr("       ▽");
	
	gotoxy(65, 2); printscr("① ② ③ ④ ⑤를 통해 무기를 바꿉니다.");
	gotoxy(65, 3); printscr("E 버튼을 통해 다음 무기로 넘어갑니다.");

	gotoxy(65, 6); printscr("①은 HG");
	gotoxy(65, 7); printscr("②은 AR");
	gotoxy(65, 8); printscr("③은 SG");
	gotoxy(65, 9); printscr("③은 RF");
	gotoxy(65, 10); printscr("⑤은 길목에 설치 후 공격해 폭발시킬 수 있습니다.");


	gotoxy(5, 18); printscr("▲(50)   ");
	gotoxy(5, 20); printscr("△(80)   ");
	gotoxy(5, 22); printscr("◆(100)");
	gotoxy(5, 24); printscr("◇(200)");
	
	gotoxy(10, 28); printscr("EP 1 The Escape");
	gotoxy(10, 30); printscr("EP 2 No Parking");


	gotoxy(60, 19); printscr("                            ▲");
	gotoxy(60, 20); printscr("        ⊙           ▲        △");
	gotoxy(60, 21); printscr("      ⊙⊙                           ◆");
	gotoxy(60, 22); printscr("○  ⊙⊙⊙    ▲               △");
	gotoxy(60, 23); printscr("☆⊙⊙⊙⊙         △               ◆      ◇");
	gotoxy(60, 24); printscr("    ⊙⊙⊙                ▲");
	gotoxy(60, 25); printscr("      ⊙⊙            △        △");
	gotoxy(60, 26); printscr("        ⊙          ▲                   ◆");
	gotoxy(60, 27); printscr("                         ▲                   ▲");




	scr_switch();
	_getch();
}