#include <ket/all.hpp>

using namespace Ket;

struct Hand {
	String cards;
	I64 value;
	int score;
};

static constexpr StringView cards = "23456789TJQKA";

auto cardPred = [](char a, char b) {
	return cards.find(a) < cards.find(b);
};

auto scoreHand = [](String& cards) {
	List<String> grouped = cards.clone().sort(cardPred).group(Pred::Equal);
	if (cards.unique().length() == 1)
		return 7;
	if (grouped.some([](String& s){ return s.length() == 4; }))
		return 6;
	if (cards.clone().sort(cardPred).unique().length() == 2)
		return 5;
	if (grouped.some([](String& s){ return s.length() == 3; }))
		return 4;
	int pairCount = grouped.count([](String& s){ return s.length() == 2; });
	if (pairCount == 2) return 3;
	if (pairCount == 1) return 2;
	return 1;
};

auto handValueHigh = [](String& s) {
	return s.foldLeftI(0, [](I64 acc, char c, I64 i){
		return acc + (cards.find(c) << (5 - i) * 4);
	});
};

int main(void) {
	I64 ans =
		Input("input.txt")
		.foldLeft(List<Hand>(), [](auto hands, String line) {
			auto splits = ParseString(line).split(' ');
			String cards = splits[0].string();
			hands.pushBack(Hand{cards, splits[1].getInt(), scoreHand(cards)});
			return O::move(hands);
		})
		.sort([](Hand& a, Hand& b) {
			return (
				a.score < b.score || (
					a.score == b.score &&
					handValueHigh(a.cards) < handValueHigh(b.cards)
				)
			);
		})
		.foldLeftI(0, [](I64 acc, Hand& h, int i) {
			return acc + h.value * (i + 1);
		})
	;
	println("{}", ans);
	return 0;
}
