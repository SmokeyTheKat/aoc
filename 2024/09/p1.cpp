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
	
	for (Int i = 0, j = data.length() - 1; i < j;) {
		if (data[i] == -1 && data[j] != -1) O::swap(data[i++], data[j--]);
		else data[i] != -1 ? i++ : j--;
	}
	
	Ket::println("{}", data.range().sum($f2 $0 == -1 ? 0 : $0 * $1 $));
}
