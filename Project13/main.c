#define _CRT_SECURE_NO_WARNINGS

#include "displayControl.h"
#include "main.h"
#include "map.h"
#include "menu.h"

void init()
{
	//â ������ ����
	system("mode con cols=125 lines=40 | title Game Title");
	scr_init();
}



int main(void) {
	init();

	while (TRUE) {
		int userChoice = menuChoice();

		switch (userChoice) {
		case 0:
			//���ӽ���
			switch (mapChoice()) {
			case 0:
				//MAP1
				memcpy(tempMap, map1, sizeof(tempMap));
				game();
				break;

			case 2:
				//MAP2
				memcpy(tempMap, map2, sizeof(tempMap));
				game();
				break;

			case 4:
				//MAP3
				memcpy(tempMap, map3, sizeof(tempMap));
				game();
				break;

			default:
				break;
			}
			break;

		case 2:
			
			//�ɼ�

			how();


			



			break;

		case 4:
			exit(1);
			break;
		}
	}
}