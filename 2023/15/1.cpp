#include <ket/all.hpp>

using namespace Ket;

int main(void) {
	int ans =
		ParseString(Input("input.txt").readAll())
		.split(',')
		.map([](String s) {
			return s.foldLeft(0, LAM (h, c) EXPR (h + ((h + c) * 17) % 256));
		})
		.foldLeft(0, Pred::Add)
	;
	println("{}", ans);
	return 0;
}
