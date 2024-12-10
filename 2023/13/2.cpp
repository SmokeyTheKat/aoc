#include <ket/all.hpp>

using namespace Ket;

int main(void) {
	auto getReflection = [&](const List<String>& map) {
		for (int r = 0; r + 1 < map.length(); r++) {
			int ones = 0;
			for (int i = 0; r - i >= 0 && r + 1 + i < map.length(); i++) {
				int notSame = map[r - i].foldLeft2(map[r + i + 1], 0, LAM (acc, a, b) EXPR (acc + (a != b)));
				if (notSame == 1) ones += 1;
				else if (notSame > 1) break;
				if (
					!(r - i - 1 >= 0 && r + 1 + i + 1 < map.length()) &&
					ones == 1
				) return r + 1;
			}
		}
		return -1;
	};
	int ans = 0;
	Input inp("input.txt");
	while (!inp.isDone()) {
		List<String> map;
		for (String line; inp.getLine(line) && line.length() > 0;) {
			map += line;
		}
		if (int refl = getReflection(map); refl >= 0) {
			ans += refl * 100;
		} else if (int refl = getReflection(Iter::rotateCW902D(map)); refl >= 0) {
			ans += refl;
		}
	}
	println("{}", ans);
	return 0;
}
