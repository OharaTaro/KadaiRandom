#include "CardDeck.h"
#include "DxLib.h"
#include <random>

namespace
{
	const char* const kMarkKindName[] =
	{
		"スペード",
		"ハート　",
		"ダイア　",
		"クラブ　"
	};
	static_assert(CardDeck::kMarkKind == _countof(kMarkKindName));
}

CardDeck::CardDeck(int playerNo):
	m_playerNo(playerNo)
{
}

CardDeck::~CardDeck()
{
}

void CardDeck::createRandomDeck()
{
	m_deck.clear();
	for (int i = 0; i < kTotalCardNum; i++)
	{
		CardData data;
		data.mark = i / kNumMax;
		data.no = i % kNumMax;
		m_deck.push_back(data);
	}

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(m_deck.begin(), m_deck.end(), engine);
}

void CardDeck::createDeck(SendData sendData)
{
	printfDx("SendDataSize = %d\n", sizeof(sendData));

	// 受け取ったデータからデックを生成
	m_deck.clear();
	for (int i = 0; i < kTotalCardNum; i++)
	{
		CardData data;
		data.mark = sendData.data[i].mark;
		data.no = sendData.data[i].no;
		m_deck.push_back(data);
	}
}

CardDeck::SendData CardDeck::getSendData()
{
	SendData sendData;

	for (int i = 0; i < kTotalCardNum; i++)
	{
		sendData.data[i] = m_deck[i];
	}

	return sendData;
}

void CardDeck::draw()
{
	int x = 8 + m_playerNo * 200;
	int y = 8;

	for (auto& card : m_deck)
	{
		drawCard(x, y, card);
		y += 16;
	}
}

void CardDeck::drawCard(int x, int y, CardData card)
{
	DrawFormatString(x, y, 0xffffff, "%s : %d", kMarkKindName[card.mark], card.no);
}
