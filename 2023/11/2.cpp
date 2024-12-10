#include <ket/all.hpp>

using namespace Ket;

struct Pos { I64 x, y; };

int main(void) {
	List<int> yGaps;
	List<String> map =
		Input("input.txt")
		.foldLeftI(List<String>(), [&](auto acc, String& line, int y) {
			acc.pushBack(line);
			if (line.all('.')) yGaps += y;
			return acc;
		})
	;

	List<int> xGaps;

	map = Iter::rotateCW902D(map);
	map.forEachI(LAM (&col, x) BODY (if (col.all('.')) xGaps += x));
	map = Iter::rotateCCW902D(map);

	List<Pos> gals;
	Iter::loop2DI(map, [&](char c, I64 x, I64 y) {
		if (c == '#') gals += {x, y};
	});

	auto gapsBetween = [](auto& gaps, I64 a, I64 b) {
		if (a > b) O::swap(a, b);
		return gaps.count([&](int pos){ return pos > a && pos < b; });
	};

	auto distanceBetween = [&](Pos a, Pos b) {
		return (
			Math::abs(b.x - a.x) + 999999 * gapsBetween(xGaps, a.x, b.x) +
			Math::abs(b.y - a.y) + 999999 * gapsBetween(yGaps, a.y, b.y)
		);
	};

	I64 sum = 0;
	int count = 0;
	for (int i = 0; i + 1 < gals.length(); i++) {
		for (int j = i + 1; j < gals.length(); j++) {
			sum += distanceBetween(gals[i], gals[j]);
			count += 1;
		}
	}

	println("{}", sum);

	return 0;
}
