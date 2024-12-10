#include <ket/all.hpp>

using namespace Ket;

enum class Dir { N, S, E, W };

struct Light {
	union {
		struct { I8 n, s, e, w; };
		I32 used;
	};

	Light(void)
	: used(0) {};

	~Light(void) {};

	void set(Dir d) {
		switch (d) {
		case Dir::N: n = 1; break;
		case Dir::S: s = 1; break;
		case Dir::E: e = 1; break;
		case Dir::W: w = 1; break;
		}
	};

	bool has(Dir d) {
		switch (d) {
		case Dir::N: return n == 1;
		case Dir::S: return s == 1;
		case Dir::E: return e == 1;
		case Dir::W: return w == 1;
		}
	};
};

int main(void) {
	List<String> map = Input("input.txt").foldLeft(List<String>(), Pred::Append);

	List<List<Light>> outMap(map.length(), [&](int i){ return List<Light>(Light(), map[0].length()); });

	auto tryFrom = [&](int ix, int iy, Dir id) {
		outMap.forEach(LAM (&a) BODY (a.forEach(LAM (&b) BODY (b.used = 0))));
	
		auto move = [&](int& x, int& y, Dir d) {
			switch (d) {
			case Dir::N: {
				if (y > 0) y -= 1;
				else return false;
			} break;
			case Dir::S: {
				if (y + 1 < map.length()) y += 1;
				else return false;
			} break;
			case Dir::W: {
				if (x > 0) x -= 1;
				else return false;
			} break;
			case Dir::E: {
				if (x + 1 < map[0].length()) x += 1;
				else return false;
			} break;
			}
			return true;
		};
	
		auto walk = [&](int x, int y, Dir d, auto&& walk) {
			if (move(x, y, d) == false) return;
			if (outMap[y][x].has(d)) return;
			outMap[y][x].set(d);
			switch (map[y][x]) {
			case '.': {
				walk(x, y, d, walk);
			} break;
			case '|': {
				if (d == Dir::N || d == Dir::S) {
					walk(x, y, d, walk);
				} else {
					walk(x, y, Dir::N, walk);
					walk(x, y, Dir::S, walk);
				}
			} break;
			case '-': {
				if (d == Dir::W || d == Dir::E) {
					walk(x, y, d, walk);
				} else {
					walk(x, y, Dir::W, walk);
					walk(x, y, Dir::E, walk);
				}
			} break;
			case '/': {
				switch (d) {
				case Dir::N: walk(x, y, Dir::E, walk); break;
				case Dir::S: walk(x, y, Dir::W, walk); break;
				case Dir::E: walk(x, y, Dir::N, walk); break;
				case Dir::W: walk(x, y, Dir::S, walk); break;
				}
			} break;
			case '\\': {
				switch (d) {
				case Dir::N: walk(x, y, Dir::W, walk); break;
				case Dir::S: walk(x, y, Dir::E, walk); break;
				case Dir::E: walk(x, y, Dir::S, walk); break;
				case Dir::W: walk(x, y, Dir::N, walk); break;
				}
			} break;
			}
		};
	
		walk(ix, iy, id, walk);
	
		return outMap.foldLeft(0, LAM (acc, &row) EXPR (acc + row.count(LAM (&l) EXPR (l.used != 0))));
	};

	List<int> values;
	for (int x = 0; x < map[0].length(); x++) {
		values += tryFrom(x, -1, Dir::S);
		values += tryFrom(x, map.length(), Dir::N);
	}

	for (int y = 0; y < map.length(); y++) {
		values += tryFrom(-1, y, Dir::E);
		values += tryFrom(map[0].length(), y, Dir::W);
	}

	println("{}", values.max(Pred::Less).value(-1));

	return 0;
}
