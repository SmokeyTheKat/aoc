#include <ket/all.hpp>

using namespace Ket;

struct Pos {
	int x=0, y=0;
	bool operator==(const Pos& o) const {
		return x == o.x && y == o.y;
	}
};

int main(void) {
	List<String> sch = Input("input.txt").foldLeft(List<String>(), Pred::Append);

	auto getNumber = [&](int x, int y, List<Pos>& found) -> Option<int> {
		int start = x;
		int end = x;
		String& s = sch[y];
		while (end < s.length() && Ascii::isDigit(s[end])) end++;
		while (start >= 0 && Ascii::isDigit(s[start])) start--;
		start++;
		if (found.contains(Pos{start, y})) return None();
		found.pushBack(Pos{start, y});
		return ParseString(s).subString(start, end).getInt();
	};

	auto getGearRatio = [&](int x, int y) {
		List<int> nums;
		List<Pos> found;
		bool xl = x > 0;
		bool xr = x + 1 < sch[0].length();
		bool yu = y > 0;
		bool yd = y + 1 < sch.length();
		if (xl && Ascii::isDigit(sch[y][x-1]))
			if (auto num = getNumber(x-1, y, found)) nums.pushBack(*num);
		if (xl && yu && Ascii::isDigit(sch[y-1][x-1]))
			if (auto num = getNumber(x-1, y-1, found)) nums.pushBack(*num);
		if (xl && yd && Ascii::isDigit(sch[y+1][x-1]))
			if (auto num = getNumber(x-1, y+1, found)) nums.pushBack(*num);
		if (xr && Ascii::isDigit(sch[y][x+1]))
			if (auto num = getNumber(x+1, y, found)) nums.pushBack(*num);
		if (xr && yu && Ascii::isDigit(sch[y-1][x+1]))
			if (auto num = getNumber(x+1, y-1, found)) nums.pushBack(*num);
		if (xr && yd && Ascii::isDigit(sch[y+1][x+1]))
			if (auto num = getNumber(x+1, y+1, found)) nums.pushBack(*num);
		if (yu && Ascii::isDigit(sch[y-1][x]))
			if (auto num = getNumber(x, y-1, found)) nums.pushBack(*num);
		if (yd && Ascii::isDigit(sch[y+1][x]))
			if (auto num = getNumber(x, y+1, found)) nums.pushBack(*num);
		if (nums.length() != 2) return 0;
		return nums[0] * nums[1];
	};

	int ans = Iter::foldLeft2DI(sch, 0, [&](int acc, char c, int x, int y) {
		return acc + (c == '*' ? getGearRatio(x, y) : 0);
	});
	println("{}", ans);
	return 0;
}
