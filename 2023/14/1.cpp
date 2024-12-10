#include <ket/all.hpp>

using namespace Ket;

int main(void) {
	List<String> map = Input("input.txt").foldLeft(List<String>(), Pred::Append);

	auto rollRock = [&](int x, int y) {
		for (; y > 0 && map[y-1][x] == '.'; y--) O::swap(map[y][x], map[y-1][x]);
	};

	Iter::loop2DI(map, LAM (c, x, y) BODY (if (c == 'O') rollRock(x, y)));
	int ans = Iter::foldLeft2DI(
		map, 0,
		LAM (acc, c, x, y) EXPR (acc + (c == 'O' ? map.length() - y : 0))
	);
	println("{}", ans);
	return 0;
}
