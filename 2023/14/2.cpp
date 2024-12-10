#include <ket/all.hpp>

using namespace Ket;

int main(void) {
	List<String> map = Input("input.txt").foldLeft(List<String>(), Pred::Append);

	auto rollRockN = [&](int x, int y) {
		for (; y - 1 >= 0 && map[y-1][x] == '.'; y--) O::swap(map[y][x], map[y-1][x]);
	};

	auto rollRockS = [&](int x, int y) {
		for (; y + 1 < map.length() && map[y+1][x] == '.'; y++) O::swap(map[y][x], map[y+1][x]);
	};

	auto rollRockE = [&](int x, int y) {
		for (; x + 1 < map[0].length() && map[y][x+1] == '.'; x++) O::swap(map[y][x], map[y][x+1]);
	};

	auto rollRockW = [&](int x, int y) {
		for (; x - 1 >= 0 && map[y][x-1] == '.'; x--) O::swap(map[y][x], map[y][x-1]);
	};

	auto doCycle = [&](void) {
		Iter::loop2DI(map, LAM (c, x, y) BODY (if (c == 'O') rollRockN(x, y)));
		Iter::loopCol2DI(map, LAM (c, x, y) BODY (if (c == 'O') rollRockW(x, y)));
		Iter::loopRev2DI(map, LAM (c, x, y) BODY (if (c == 'O') rollRockS(x, y)));
		Iter::loopColRev2DI(map, LAM (c, x, y) BODY (if (c == 'O') rollRockE(x, y)));
	};

	auto findCycle = [&](void) -> int {
		List<Pair<U64, int>> founds;
		for (int i = 0; i < 1000000000; i++) {
			doCycle();
			U64 hash = Hash::hash(map);
			auto repeat = founds.find(LAM (&p) EXPR (hash == p.a));
			if (repeat) return (1000000000 - repeat->b) % (i - repeat->b);
			founds += {hash, i};
		}
		return -1;
	};

	int endPos = findCycle();
	for (int i = 0; i < endPos - 1; i++) doCycle();

	int ans = Iter::foldLeft2DI(
		map, 0,
		LAM (acc, c, x, y) EXPR (acc + (c == 'O' ? map.length() - y : 0))
	);
	println("{}", ans);
	return 0;
}
