#ifndef _ATTACK_H

#define _ATTACK_H

#define HG 0
#define AR 1
#define SG 2
#define SR 3
#define HGDAMAGE 10
#define ARDAMAGE 5
#define SGDAMAGE 30
#define SRDAMAGE 100
#define WEAPONCOUNT 4

typedef struct {
	int bullet;
	int damage;
} WEAPON;

WEAPON weapon[WEAPONCOUNT];
int selectWeapon;

void attack(int* x, int* y, int _x, int _y, char wh);
void endAttack(int* x, int* y, int _x, int _y, char wh);

#endif