#include <ket/all.hpp>
#include <cmath>

using namespace Ket;

int main(void) {
	Input inp("input.txt");
	double t =
		ParseString(
			ParseString(inp.getLine())
			.split(':')[1]
			.split(' ')
			.foldLeft(""_s, LAM (acc, s) EXPR (acc + s.trim().string()))
		).trim().getInt()
	;

	double td =
		ParseString(
			ParseString(inp.getLine())
			.split(':')[1]
			.split(' ')
			.foldLeft(""_s, LAM (acc, s) EXPR (acc + s.trim().string()))
		).trim().getInt()
	;

	double x2 = (t + Math::sqrt(t * t - 4.0 * td)) / 2.0;
	double x1 = t - x2;
	I64 possible = 1 + Math::floor(x2) - Math::ceil(x1);
	if (x2 == td || x1 == td) possible -= 2;
	println("{}", possible);

	return 0;
}
