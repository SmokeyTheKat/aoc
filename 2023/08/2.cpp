#include <ket/all.hpp>
#include <numeric>

using namespace Ket;

U64 lcm(List<U64> nums) {
	U64 x = nums.popFront();
	return nums.foldLeft(x, [](U64 acc, U64 v){
		return std::lcm(acc, v);
	});
}

using MoveMap = Map<String, Array<String, 2>>;

int main(void) {
	Input inp("input.txt");
	List<int> moves = inp.getLine().list().map([](char c){ return c == 'L' ? 0 : 1; });
	inp.skipLine();
	List<String> starts;
	MoveMap map =
		inp.foldLeft(MoveMap(), [&](MoveMap&& map, String& line) {
			ParseString ps(line);
			auto splits = ps.split(" = ");
			splits[1].pop();
			splits[1].popBack();
			auto lr = splits[1].split(", ");
			String pos = splits[0].string();
			if (pos.last() == 'A') starts.pushBack(pos);
			map[pos] = {lr[0].string(), lr[1].string()};
			return move(map);
		})
	;

	List<U64> loops = starts.map([&](String& startPos) {
		Pair<String, U64> p{startPos, 0};
		auto isDone = [](String& pos) { return pos.last() == 'Z'; };
		do {
			moves.loop([&](int dir) {
				if (isDone(p.a)) return false;
				p.a = map[p.a][dir];
				p.b += 1;
				return true;
			});
		} while (!isDone(p.a));
		return p.b;
	});

	println("{}", lcm(loops));
	return 0;
}
