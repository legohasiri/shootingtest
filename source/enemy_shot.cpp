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

		//ｘ、ｙ方向への移動量
		sx = cos(angle*(PI / 180))*speed;
		sy = sin(angle*(PI / 180))*speed;

		flag = true;
		EnemyShotNum++;
	}
	return 0;
}

void enemy_shot::FireShot() {
	int i, Con, Num;

	// 弾の数だけ移動処理を繰り返す
	Con = 0;
	Num = EnemyShotNum;
	for (i = 0; i < E_MAX_SHOT; i++)
	{
		// 弾のデータが有効な場合は処理
		if (flag)
		{
			// 移動処理
			nx += sx;
			ny += sy;

			// 画面外に出たら弾情報を消去する
			if ((nx < -20) ||
				(nx > 660) ||
				(ny < -20) ||
				(ny > 500))
			{
				// データの有効フラグを倒す
				flag = false;

				// 弾の数を減らす
				EnemyShotNum--;
			}

			// 弾の描画
			{
				int x, y;

				x = nx;
				y = ny;

				DrawRotaGraph(x, y, 1, 0, bullet, TRUE);
			}

			// 処理した弾の数をインクリメント
			Con++;

			// 処理した弾の数が、存在している弾の数と同じになった場合はループを抜ける
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