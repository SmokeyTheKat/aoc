#include <ket/all.hpp>

using namespace Ket;

struct Hand {
	String cards;
	I64 value;
	int score;
};

static constexpr StringView cards = "J23456789TQKA";

auto cardPred = [](char a, char b) {
	return cards.find(a) < cards.find(b);
};

auto scoreHand = [](String& cards) {
	int jokers = cards.count('J');
	String sorted = cards.clone().sort(cardPred);
	String unique = sorted.unique();
	List<String> grouped = sorted.group(Pred::Equal);
	auto nonJokerGroupsOfSize = [&](int size) {
		return grouped.count([&](String& s){ return s.length() == size && s[0] != 'J'; });
	};
	if (
		unique.length() == 1 || (
			unique.length() == 2 &&
			jokers > 0
		)
	) return 7;
	if (
		grouped.some([](String& s){ return s.length() == 4; }) || (
			nonJokerGroupsOfSize(3) > 0 &&
			jokers == 1
		) || (
			nonJokerGroupsOfSize(2) > 0 &&
			jokers == 2
		) || (
			jokers == 3
		)
	) return 6;
	if (
		unique.length() == 2 || (
			nonJokerGroupsOfSize(2) == 2 &&
			jokers == 1
		) || (
			nonJokerGroupsOfSize(2) > 0 &&
			nonJokerGroupsOfSize(1) > 0 &&
			jokers == 2
		) || (
			nonJokerGroupsOfSize(3) > 0 &&
			nonJokerGroupsOfSize(1) > 0 &&
			jokers == 1
		)
	) return 5;
	if (
		grouped.some([](String& s){ return s.length() == 3; }) || (
			nonJokerGroupsOfSize(2) > 0 &&
			jokers == 1
		) || (
			nonJokerGroupsOfSize(1) > 0 &&
			jokers == 2
		)
	) return 4;
	int pairCount = grouped.count([](String& s){ return s.length() == 2; });
	if (
		pairCount == 2 || (
			nonJokerGroupsOfSize(2) > 0 &&
			jokers == 1
		)
	) return 3;
	if (pairCount == 1 || jokers == 1) return 2;
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
			return hands;
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
