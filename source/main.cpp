#include "DxLib.h"
#include "define.h"
#include "func.h"
#include "bullet.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);
	SetMainWindowText("ShootingTest");
	// �c�w���C�u�����̏�����
	if (DxLib_Init() == -1) return -1;

	// ����ʂ��g�p
	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){

		// ��ʂ̍X�V
		ScreenFlip();
	}
	// �c�w���C�u�����̎g�p�I��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}