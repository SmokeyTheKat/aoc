Int main(void) {
	Array<Array<Int>> reports = Input("input.txt").lines()
		.map($a.view().split(" ").map(Pred::ToNumber<Int>)$);
	Ket::println("{}", reports.count(
		[]FN (&report) {
			Int dir = Math::sign(report[1] - report[0]);
			return report.range().pairs().map(Pred::Tuple::Diff).all($f1
				Math::sign($0) == dir && Math::inRange(Math::abs($0), 1, 3)
			$);
		}
	));
}
