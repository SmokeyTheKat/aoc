#include <ket/all.hpp>

using namespace Ket;

struct Pos { int x, y; };

enum class Dir { N, S, E, W, NE, NW, SE, SW };

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

	auto move = [&](Pos from, Pos at) -> Option<Pair<Pos, Dir>> {
		if (!map[0].validIndex(at.x) || !map.validIndex(at.y)) {
			return None();
		}
		switch (map[at.y][at.x]) {
		case '|': {
			if (from.y < at.y) return Pair<Pos, Dir>{Pos{at.x, at.y + 1}, Dir::S};
			else return Pair<Pos, Dir>{Pos{at.x, at.y - 1}, Dir::N};
		} break;
		case '-': {
			if (from.x < at.x) return Pair<Pos, Dir>{Pos{at.x + 1, at.y}, Dir::E};
			else return Pair<Pos, Dir>{Pos{at.x - 1, at.y}, Dir::W};
		} break;
		case 'L': {
			if (from.x > at.x) return Pair<Pos, Dir>{Pos{at.x, at.y - 1}, Dir::NW};
			else return Pair<Pos, Dir>{Pos{at.x + 1, at.y}, Dir::SE};
		} break;
		case 'J': {
			if (from.x < at.x) return Pair<Pos, Dir>{Pos{at.x, at.y - 1}, Dir::NE};
			else return Pair<Pos, Dir>{Pos{at.x - 1, at.y}, Dir::SW};
		} break;
		case '7': {
			if (from.x < at.x) return Pair<Pos, Dir>{Pos{at.x, at.y + 1}, Dir::SE};
			else return Pair<Pos, Dir>{Pos{at.x - 1, at.y}, Dir::NW};
		} break;
		case 'F': {
			if (from.x > at.x) return Pair<Pos, Dir>{Pos{at.x, at.y + 1}, Dir::SW};
			else return Pair<Pos, Dir>{Pos{at.x + 1, at.y}, Dir::NE};
		} break;
		default: return None();
		}
	};

	Pos loopStart =
		startingPositions
		.map([&](Pos tryStart) -> Pair<Pos,int> {
			Pos from = start;
			Pos at = tryStart;
			int length = 0;
			do {
				if (auto next = move(from, at)) {
					from = at;
					at = next->a;
					length += 1;
				} else {
					return {tryStart, -1};
				}
			} while (!(at.x == start.x && at.y == start.y));
			return {tryStart, length + 1};
		})
		.max(LAM (a, b) EXPR (a.b < b.b))
		.value(Pair<Pos,int>{{-1,-1},-1})
		.a
	;

	auto travle = [&](auto&& func) {
		Pos from = start;
		Pos at = loopStart;
		do {
			if (auto next = move(from, at)) {
				func(at, *next);
				from = at;
				at = next->a;
			}
		} while (!(at.x == start.x && at.y == start.y));
	};

	List<String> outMap(map);

	travle(LAM (at, next) BODY (outMap[at.y][at.x] = '*'));
	outMap[start.y][start.x] = '*';

	auto tryOutput = [&](int x, int y, char c) {
		if (outMap.validIndex(y) && outMap[0].validIndex(x) && outMap[y][x] != '*') outMap[y][x] = c;
	};

	travle([&](auto at, auto next){
		switch (next.b) {
		case Dir::N: {
			tryOutput(at.x+1, at.y+0, 'r');
			tryOutput(at.x-1, at.y+0, 'l');
		} break;
		case Dir::S: {
			tryOutput(at.x+1, at.y+0, 'l');
			tryOutput(at.x-1, at.y+0, 'r');
		} break;
		case Dir::E: {
			tryOutput(at.x+0, at.y+1, 'r');
			tryOutput(at.x+0, at.y-1, 'l');
		} break;
		case Dir::W: {
			tryOutput(at.x+0, at.y+1, 'l');
			tryOutput(at.x+0, at.y-1, 'r');
		} break;
		case Dir::NE: {
			tryOutput(at.x-1, at.y+0, 'l');
			tryOutput(at.x+0, at.y-1, 'l');
		} break;
		case Dir::NW: {
			tryOutput(at.x+1, at.y+0, 'r');
			tryOutput(at.x+0, at.y-1, 'r');
		} break;
		case Dir::SE: {
			tryOutput(at.x+1, at.y+0, 'l');
			tryOutput(at.x+0, at.y-1, 'l');
		} break;
		case Dir::SW: {
			tryOutput(at.x-1, at.y+0, 'r');
			tryOutput(at.x+0, at.y-1, 'r');
		} break;
		}
	});

	Iter::loop2D(outMap, [&](char& c) {
		if (c != '*' && c != 'r' && c != 'l') c = '.';
	});

	auto tryFill = [&](int x, int y, char c) {
		if (outMap[0].validIndex(x) && outMap.validIndex(y) && outMap[y][x] == '.') outMap[y][x] = c;
	};

	auto fillAround = [&](char c, int x, int y) {
		if (c == 'l' || c == 'r') {
			tryFill(x-1, y+0, c);
			tryFill(x+1, y+0, c);
			tryFill(x+0, y-1, c);
			tryFill(x+0, y+1, c);
		}
	};

	Iter::loop2DI(outMap, fillAround);
	Iter::loopRev2DI(outMap, fillAround);

	int rs = 0;
	int ls = 0;

	Iter::loop2D(outMap, [&](char c) {
		if (c == 'l') ls++;
		else if (c == 'r') rs++;
	});

	println("L: {}\nR: {}", ls, rs);
	return 0;
}
