#include <ket/all.hpp>

using namespace Ket;

int main(void) {
	List<String> sch =
		Input("input.txt").foldLeft(List<String>(), [](auto list, String& line){
			list.pushBack(line);
			return list;
		})
	;

	auto isSymb = [](char c) { return c != '.' && Ascii::isSpecial(c); };

	auto isPart = [&](int x, int y, int nlen) {
		bool xl = x > 0;
		bool xr = x + nlen < sch[0].length();
		bool yu = y > 0;
		bool yd = y + 1 < sch.length();
		if (xl && isSymb(sch[y][x-1])) return true;
		if (xl && yu && isSymb(sch[y-1][x-1])) return true;
		if (xl && yd && isSymb(sch[y+1][x-1])) return true;
		if (xr && isSymb(sch[y][x+nlen])) return true;
		if (xr && yu && isSymb(sch[y-1][x+nlen])) return true;
		if (xr && yd && isSymb(sch[y+1][x+nlen])) return true;
		for (int i = 0; i < nlen; i++) {
			if (yu && isSymb(sch[y-1][x+i])) return true;
			if (yd && isSymb(sch[y+1][x+i])) return true;
		}
		return false;
	};

	int ans = 0;
	for (int y = 0; y < sch.length(); y++) {
		ParseString ps(sch[y]);
		while (!ps.isEmpty()) {
			if (Ascii::isDigit(ps.front())) {
				int x = ps.parsedCount();
				ParseString num = ps.popInt();
				if (isPart(x, y, num.length())) ans += num.getInt();
			} else ps.pop();
		}
	}
	println("{}", ans);
	return 0;
}
