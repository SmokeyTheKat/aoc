#include <ket/all.hpp>

using namespace Ket;

int main(void) {
	auto getReflection = [&](const List<String>& map) {
		for (int r = 0; r + 1 < map.length(); r++) {
			for (int i = 0; r - i >= 0 && r + 1 + i < map.length(); i++) {
				if (map[r - i] != map[r + 1 + i]) break;
				if (!(r - i - 1 >= 0 && r + 1 + i + 1 < map.length())) return r + 1;
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
