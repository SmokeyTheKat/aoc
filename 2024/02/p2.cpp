Int main(void) {
	Array<Array<Int>> reports = Input("input.txt").lines()
		.map($a.view().split(" ").map(Pred::ToNumber<Int>) $);
	Ket::println("{}", reports.count(
		[]FN (&report) {
			auto testWithout = [&](Int without) {
				auto diffs = report.range().filter($f2 $1 != without $).pairs().map(Pred::Tuple::Diff);
				return (
					diffs.all($f1 Math::sign($0) == Math::sign(*diffs.first()) $) &&
					diffs.all($f1 Math::inRange(Math::abs($0), 1, 3) $)
				);
			};
			return Iter::range(-1, report.length()).any(testWithout);
		}
	));
}
