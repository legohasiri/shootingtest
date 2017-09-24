#include "enemy.h"
#include "define.h"
#include "DxLib.h"
#include "cmath"

int EnemyShotNum = 0;

void enemy_shot::Shot(Point_ x, Point_ y, _Color color, Type type, double angle, double speed) {
	ShotFlag(x, y, color, type, angle, speed);
	FireShot();
}

int	enemy_shot::ShotFlag(Point_ x, Point_ y, _Color color, Type type, double angle, double speed) {
	int i;
	for (i = 0; i < E_MAX_SHOT; i++)
		if (!flag)
			break;
	if (i == E_MAX_SHOT)
		return -1;


	{
		nx = x;
		ny = y;
		bullet = BulletData[type][color].graph;

		//���A�������ւ̈ړ���
		sx = cos(angle*(PI / 180))*speed;
		sy = sin(angle*(PI / 180))*speed;

		flag = true;
		EnemyShotNum++;
	}
	return 0;
}

void enemy_shot::FireShot() {
	int i, Con, Num;

	// �e�̐������ړ��������J��Ԃ�
	Con = 0;
	Num = EnemyShotNum;
	for (i = 0; i < E_MAX_SHOT; i++)
	{
		// �e�̃f�[�^���L���ȏꍇ�͏���
		if (flag)
		{
			// �ړ�����
			nx += sx;
			ny += sy;

			// ��ʊO�ɏo����e������������
			if ((nx < -20) ||
				(nx > 660) ||
				(ny < -20) ||
				(ny > 500))
			{
				// �f�[�^�̗L���t���O��|��
				flag = false;

				// �e�̐������炷
				EnemyShotNum--;
			}

			// �e�̕`��
			{
				int x, y;

				x = nx;
				y = ny;

				DrawRotaGraph(x, y, 1, 0, bullet, TRUE);
			}

			// ���������e�̐����C���N�������g
			Con++;

			// ���������e�̐����A���݂��Ă���e�̐��Ɠ����ɂȂ����ꍇ�̓��[�v�𔲂���
			if (Num == Con) break;
		}
	}
}


void enemy_shot::CreateShot01(Point_ x, Point_ y, double speed, double angle, _Color color, Type type, Count_ late = 0) {
	Count_ count = 0;
	Shot(x, y, color, type, angle, speed);
	if (count >= late) {

	}
	count++;
}

void enemy_shot::CreateShot02(Point_ x, Point_ y, double speed, double angle, double acceleration, double max_speed, _Color color, Type type, Count_ late = 0) {

}