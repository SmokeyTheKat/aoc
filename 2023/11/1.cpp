#include <ket/all.hpp>

using namespace Ket;

struct Pos { int x, y; };

int main(void) {
	List<String> map =
		Input("input.txt")
		.foldLeft(List<String>(), [](auto acc, String& line) {
			acc.pushBack(line);
			if (line.all('.')) acc.pushBack(line);
			return acc;
		})
	;

	map = Iter::rotateCW902D(map);
	map.insertWhere([](String& col) -> Option<String> {
		if (col.all('.')) return Some(col);
		return None();
	});
	map = Iter::rotateCCW902D(map);

	List<Pos> gals;
	Iter::loop2DI(map, [&](char c, int x, int y) {
		if (c == '#') gals += {x, y};
	});

	auto distanceBetween = [](Pos a, Pos b) {
		return Math::abs(b.x - a.x) + Math::abs(b.y - a.y);
	};

	int sum = 0;
	for (int i = 0; i + 1 < gals.length(); i++) {
		for (int j = i + 1; j < gals.length(); j++) {
			sum += distanceBetween(gals[i], gals[j]);
		}
	}

	println("{}", sum);

	return 0;
}
