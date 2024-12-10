#include <ket/all.hpp>

using namespace Ket;

int main(void) {
	Input inp("input.txt");
	List<String> cards = Input("input.txt").foldLeft(List<String>(), Pred::Append);

	auto scoreCard = [&](int card) {
		ParseString ps(cards[card]);
		ps.popUntilAndSkip(':');
		
		List<int> winners;
		while (ps.front() != '|') {
			winners += ps.popInt().getInt();
		}
		ps.pop();

		List<int> mine;
		while (!ps.isEmpty()) {
			mine += ps.popInt().getInt();
		}

		int matches = 0;
		for (int w : winners) {
			for (int m : mine) {
				if (w == m) matches += 1;
			}
		}

		return matches;
	};

	auto valueCard = [&](int y) {
		auto impl = [&](int y, auto& impl) {
			int matches = scoreCard(y);
			if (matches == 0) return 1;
			int count = 1;
			for (int i = 0; i < matches; i++) {
				count += impl(y+1+i, impl);
			}
			return count;
		};
		return impl(y, impl);
	};
	
	int ans = 0;
	for (int y = 0; y < cards.length(); y++) {
		ans += valueCard(y);
	}
	println("{}", ans);
	return 0;
}
