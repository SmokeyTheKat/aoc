Int main(void) {
	Array<I64> data =
		$match (Input("input.txt").readAll()) (
			$case| $a.length() % 2 == 0 $ = $id,
			$case| _ = $a + "0" $
		).range()
		.chunk(2).map($a.begin()$)
		.foldLeft(Array<I64>(), $f3
			$0.pushBack(Iter::repeat(*$1++ - '0', $2))
			.pushBack(Iter::repeat(*$1 - '0', -1))
			.take()
		$);
	
	for (Int j = data.length() - 1; j >= 0; j--) {
		if (data[j] == -1) continue;
		Int count = 1;
		while (j > 0 && data[j] == data[j - 1]) j--, count++;
		for (Int i = 0; i < j; i++) {
			if (Iter::range(count).all($f1 data[i + $0] == -1 $)) {
				for (Int k = 0; k < count; k++) O::swap(data[i + k], data[j + k]);
				break;
			}
		}
	}
	
	Ket::println("{}", data.range().sum($f2 $0 == -1 ? 0 : $0 * $1 $));
}
