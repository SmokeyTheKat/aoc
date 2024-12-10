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
				f.pushFront(f.first() - d.first());
			});
			return acc + ds.first().first();
		})
	;
	println("{}", ans);
	return 0;
}
