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

	List<List<I64>> seedRanges =
		ParseString(inp.getLine())
		.split(": ")[1]
		.split(' ')
		.map(Pred::PSToInt<I64>)
		.group(2)
	;

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
		seedRanges
		.reverse()
		.map([&](List<I64> r) {
			I64 min = INT64_MAX;
			for (I64 i = 0; i < r[1]; i++) {
				I64 value = maps.foldLeft(r[0] + i, [](auto acc, auto& map){ return map.map(acc); });
				if (value < min) min = value;
			}
			return min;
		})
		.min(Pred::Less)
		.value(-1l)
	;

	println("{}", min);
	return 0;
}
