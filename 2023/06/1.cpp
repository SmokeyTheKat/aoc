#include <ket/all.hpp>
#include <cmath>

using namespace Ket;

int main(void) {
	Input inp("input.txt");
	List<I64> times =
		ParseString(inp.getLine())
		.split(':')[1]
		.split(' ')
		.map(Pred::PSToInt<I64>)
	;
	List<I64> dists =
		ParseString(inp.getLine())
		.split(':')[1]
		.split(' ')
		.map(Pred::PSToInt<I64>)
	;

	I64 ans = 1;
	times.forEach2(dists, [&](I64 t, I64 td) {
		double x2 = (t + Math::sqrt(t * t - 4.0 * td)) / 2.0;
		double x1 = t - x2;
		I64 possible = 1 + Math::floor(x2) - Math::ceil(x1);
		if (x2 == td || x1 == td) possible -= 2;
		ans *= possible;
	});
	
	println("{}", ans);
	return 0;
}
