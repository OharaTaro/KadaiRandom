#pragma once
#include <vector>

class CardDeck
{
public:
	static constexpr int kMarkKind = 4;
	static constexpr int kNumMax = 13;

	static constexpr int kTotalCardNum = kNumMax * kMarkKind;

public:
	struct CardData
	{
		int mark = 0;
		int no = 0;
	};
	// �ʐM����ɓn���f�[�^
	struct SendData
	{
		CardData data[kTotalCardNum];
	};


public:
	CardDeck(int playerNo);
	virtual ~CardDeck();

	// �J�[�h�̏��Ԃ������_���ɐ���
	void createRandomDeck();
	// �J�[�h�̏��Ԃ��󂯎���Đ���
	void createDeck(SendData sendData);

	// �����f�[�^�𐶐����邽�߂ɓn���f�[�^�̎擾
	SendData getSendData();

	// �`��
	void draw();

private:
	// �J�[�h1�����\��
	void drawCard(int x, int y, CardData card);


private:
	int m_playerNo;

	std::vector<CardData>	m_deck;
};

