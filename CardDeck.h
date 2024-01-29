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
	// 通信相手に渡すデータ
	struct SendData
	{
		CardData data[kTotalCardNum];
	};


public:
	CardDeck(int playerNo);
	virtual ~CardDeck();

	// カードの順番をランダムに生成
	void createRandomDeck();
	// カードの順番を受け取って生成
	void createDeck(SendData sendData);

	// 同じデータを生成するために渡すデータの取得
	SendData getSendData();

	// 描画
	void draw();

private:
	// カード1枚分表示
	void drawCard(int x, int y, CardData card);


private:
	int m_playerNo;

	std::vector<CardData>	m_deck;
};

