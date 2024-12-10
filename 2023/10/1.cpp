#include <ket/all.hpp>

using namespace Ket;

struct Pos {
	int x, y;
};

int main(void) {
	List<String> map =
		Input("input.txt")
		.foldLeft(List<String>(), [](auto acc, String& line) {
			acc.pushBack(line);
			return acc;
		})
	;

	Pos start = map.findMapI([](String& l, int i) -> Option<Pos> {
		int p = l.find('S');
		if (p == -1) return None();
		return Some(Pos{p, i});
	}).value(Pos{-1,-1});

	List<Pos> startingPositions = {
		Pos{start.x + 1, start.y + 0},
		Pos{start.x + 0, start.y + 1},
		Pos{start.x + -1, start.y + 0},
		Pos{start.x + 0, start.y + -1},
	};

	auto move = [&](Pos from, Pos at) -> Option<Pos> {
		if (at.x < 0 || at.y < 0 || at.x >= map[0].length() || at.y >= map.length()) {
			return None();
		}
		switch (map[at.y][at.x]) {
		case '|': {
			if (from.y < at.y) return Some(Pos{at.x, at.y + 1});
			else return Some(Pos{at.x, at.y - 1});
		} break;
		case '-': {
			if (from.x < at.x) return Some(Pos{at.x + 1, at.y});
			else return Some(Pos{at.x - 1, at.y});
		} break;
		case 'L': {
			if (from.x > at.x) return Some(Pos{at.x, at.y - 1});
			else return Some(Pos{at.x + 1, at.y});
		} break;
		case 'J': {
			if (from.x < at.x) return Some(Pos{at.x, at.y - 1});
			else return Some(Pos{at.x - 1, at.y});
		} break;
		case '7': {
			if (from.x < at.x) return Some(Pos{at.x, at.y + 1});
			else return Some(Pos{at.x - 1, at.y});
		} break;
		case 'F': {
			if (from.x > at.x) return Some(Pos{at.x, at.y + 1});
			else return Some(Pos{at.x + 1, at.y});
		} break;
		default: return None();
		}
	};

	int length = startingPositions.map([&](Pos tryStart) {
		Pos from = start;
		Pos at = tryStart;
		int length = 0;
		do {
			if (auto next = move(from, at)) {
				from = at;
				at = *next;
				length += 1;
			} else {
				return -1;
			}
		} while (!(at.x == start.x && at.y == start.y));
		return length+1;
	}).max(Pred::Less).value(-1);

	println("{}", length / 2);
	return 0;
}
