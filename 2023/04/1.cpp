#include <ket/all.hpp>
#include <cmath>

using namespace Ket;

int main(void) {
	int ans = 
		Input("input.txt")
		.foldLeft(0, [](int acc, ParseString ps) {
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

			return acc + (matches == 0 ? 0 : Math::pow(2, matches - 1));
		})
	;
	
	println("{}", ans);
	return 0;
}
