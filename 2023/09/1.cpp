#include <ket/all.hpp>

using namespace Ket;

int main(void) {
	int ans =
		Input("input.txt")
		.foldLeft(0, [](int acc, ParseString line) {
			List<List<int>> ds;
			ds.pushBack(line.split(' ').map(Pred::PSToInt<int>));
			while (!ds.last().all(0)) ds.pushBack(ds.last().mapPairs(Pred::Diff));
			ds.last().pushBack(0);
			ds.forEachPairRev([](List<int>& f, List<int>& d) {
				f.pushBack(f.last() + d.last());
			});
			return acc + ds.first().last();
		})
	;
	println("{}", ans);
	return 0;
}
