#include <ket/all.hpp>

using namespace Ket;

struct Range {
	I64 dstStart;
	I64 srcStart;
	I64 len;
};

struct DestMap {
	List<Range> ranges;
	I64 map(I64 x) {
		if (auto r = ranges.find([&](auto& r){ return x >= r.srcStart && x < r.srcStart + r.len; })) {
			return r->dstStart + (x - r->srcStart);
		} else return x;
	}
};

int main(void) {
	Input inp("input.txt");

	List<I64> seeds = ParseString(inp.getLine()).split(": ")[1].split(' ').map(Pred::PSToInt<I64>);

	List<DestMap> maps;
	inp.skipLine();
	for (int i = 0; i < 7; i++) {
		inp.skipLine();
		DestMap map;
		for (String line; inp.getLine(line);) {
			if (line.length() == 0) break;
			List<I64> nums = ParseString(line).split(' ').map(Pred::PSToInt<I64>);
			map.ranges.pushBack(Range{nums[0], nums[1], nums[2]});
		}
		maps.pushBack(map);
	}

	I64 min =
		seeds
		.map([&](auto seed){
			return maps.foldLeft(seed, [](auto acc, auto& map){ return map.map(acc); });
		})
		.min(Pred::Less)
		.value(-1l)
	;

	println("{}", min);
	return 0;
}
