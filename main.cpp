#include "DxLib.h"

#include "game.h"
#include "CardDeck.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	///////////////////////////////////////////////////
	// ���
	///////////////////////////////////////////////////

	// �ʐM���g�����ΐ��z�肵���������s��
	// �v���C���[�̎g���J�[�h�ł���deck0	��
	// �ΐ푊��̎g���J�[�h�ł���deck1		������

	// ���݂��̃v���C���[�ŃJ�[�h�𓯂����ɂ�����
	// ���̂��߂Ƀv���C���[��(deck0)�ŕ��я������肵��
	// �����ΐ푊��(deck1)�ɓn���ē������я��𐶐�����

	// �ʐM�̓G���[�����������莞�Ԃ������邽��
	// �ł������n���f�[�^��������������
	// �n���f�[�^�̃T�C�Y���ł�����菬��������
	
	// CardDeck::createDeck()���œn���f�[�^�̃T�C�Y��printfDx�ŕ\�����Ă���̂ł��������������
	// (��蕶�̎��_��416�o�C�g)
	// �ʐM�ő��̋@��Ƀf�[�^��n���z��Ȃ̂Ń������͋��L���Ă��Ȃ��z���(�|�C���^�Œl��n���Ȃ�)

	CardDeck deck0{ 0 };
	CardDeck deck1{ 1 };

	// �����_���ȕ��я��𐶐�
	deck0.createRandomDeck();
	// deck0����f�[�^���󂯎���ē������я��𐶐�
	deck1.createDeck(deck0.getSendData());



	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		deck0.draw();
		deck1.draw();

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}