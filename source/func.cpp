#include "func.h"
#include "define.h"
#include "bullet.h"
#include "define.h"
#include <cmath>
#include "DxLib.h"

typedef struct _enemyshot {
	int x, y;//���W
	int sx, sy;//���̍��W
	double speed;//�X�s�[�h
	_Bullet_ bullet;//�e�̎��

	double hit_r;
	bool flag;//�t���O
}ENEMY_SHOT;

typedef struct _enemy {
	int x, y;
	int counter, counter2;
	int life;
	double angle;
	int number;
}ENEMY;

typedef struct _player {
	int x, y;
	double speed;
	double hit_r;
	bool life;
}PLAYER;


PLAYER Player;
ENEMY Enemy[ENEMY_MAX];
ENEMY_SHOT Enemy_shot[E_MAX_SHOT];

double Rand(double min, double max) {
	(double)SRand(GetNowCount()*PI);//���������l�̐ݒ�
	return (double)GetRand(max - min) + min;
}

int GetPlayerX() {
	return Player.x;
}

int GetPlayerY(){
	return Player.y;
}

int GetEnemyX(int i) {
	return Enemy[i].x;
}

int GetEnemyY(int i) {
	return Enemy[i].y;
}

int GetEnemyLife(int i) {
	return Enemy[i].life;
}

void SetPlayerX(Point_ x) {
	Player.x = x;
}

void SetPlayerY(Point_ y) {
	Player.x = y;
}

void SetSpeed(double speed) {

}
void SetAngle(double angle) {

}

double GetAngleEnemyToPlayer(int i) {
	return atan2((double)(Player.y - Enemy[i].y), (double)(Player.x - Enemy[i].x));
}

double GetAngle(Point_ ax, Point_ ay, Point_ bx, Point_ by) {
	return atan2((double)(ay - by), (double)(ax - bx));
}

void DrawPlayer(Point_ x, Point_ y, Graph_ graph){
	DrawRotaGraph(x, y, 1, 0, graph, TRUE);
}

void Wait(Count_ count) {
	for (int i = 0; i < count; i++);
}


int EnemyShotNum = 0;


void Shot(Point_ x, Point_ y, _Color color, Type type, double angle, double speed) {
	ShotFlag(x, y, color, type, angle, speed);
	FireShot();
}

int	ShotFlag(Point_ x, Point_ y, _Color color, Type type, double angle, double speed) {
		int i;
		for (i = 0; i < E_MAX_SHOT; i++)
			if (!Enemy_shot[i].flag)
				break;
		if (i == E_MAX_SHOT)
			return -1;


		{
			Enemy_shot[i].x = x;
			Enemy_shot[i].y = y;
			Enemy_shot[i].bullet = BulletData[type][color].graph;

			//���A�������ւ̈ړ���
			Enemy_shot[i].sx = cos(angle*(PI / 180))*speed;
			Enemy_shot[i].sy = sin(angle*(PI / 180))*speed;

			Enemy_shot[i].flag = true;
			EnemyShotNum++;
		}
		return 0;
	}

void FireShot() {
		int i, Con, Num;

		// �e�̐������ړ��������J��Ԃ�
		Con = 0;
		Num = EnemyShotNum;
		for (i = 0; i < E_MAX_SHOT; i++)
		{
			// �e�̃f�[�^���L���ȏꍇ�͏���
			if (Enemy_shot[i].flag)
			{
				// �ړ�����
				Enemy_shot[i].x += Enemy_shot[i].sx;
				Enemy_shot[i].y += Enemy_shot[i].sy;

				// ��ʊO�ɏo����e������������
				if ((Enemy_shot[i].x < -20) ||
					(Enemy_shot[i].x > 660) ||
					(Enemy_shot[i].y < -20) ||
					(Enemy_shot[i].y > 500))
				{
					// �f�[�^�̗L���t���O��|��
					Enemy_shot[i].flag = false;

					// �e�̐������炷
					EnemyShotNum--;
				}

				// �e�̕`��
				{
					int x, y;

					x = Enemy_shot[i].x;
					y = Enemy_shot[i].y;

					DrawRotaGraph(x, y, 1, 0, Enemy_shot[i].bullet, TRUE);
				}

				// ���������e�̐����C���N�������g
				Con++;

				// ���������e�̐����A���݂��Ă���e�̐��Ɠ����ɂȂ����ꍇ�̓��[�v�𔲂���
				if (Num == Con) break;
			}
		}
	}


void CreateShot01(Point_ x, Point_ y, double speed, double angle, _Color color, Type type, Count_ late = 0) {
	Count_ count = 0;
	Shot(x, y, color, type, angle, speed);
	if (count >= late) {

	}
	count++;
}

void CreateShot02(Point_ x, Point_ y, double speed, double angle, double acceleration, double max_speed, _Color color, Type type, Count_ late = 0) {

}

