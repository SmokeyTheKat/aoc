#include <ket/all.hpp>

using namespace Ket;

using MoveMap = Map<String, Array<String, 2>>;

int main(void) {
	Input inp("input.txt");
	List<int> moves = inp.getLine().list().map([](char c){ return c == 'L' ? 0 : 1; });
	inp.skipLine();
	MoveMap map =
		inp.foldLeft(MoveMap(), [](MoveMap&& map, String& line) {
			ParseString ps(line);
			auto splits = ps.split(" = ");
			splits[1].pop();
			splits[1].popBack();
			auto lr = splits[1].split(", ");
			map[splits[0].string()] = {lr[0].string(), lr[1].string()};
			return move(map);
		})
	;

	Pair p{"AAA"_s, 0};
	while (true) {
		p = moves.foldLeft(p, [&](auto p, int dir) {
			return p.a == "ZZZ" ? p : Pair{map[p.a][dir], p.b + 1};
		});
		if (p.a == "ZZZ") break;
	}
	println("{}", p.b);
	return 0;
}
