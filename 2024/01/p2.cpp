Int main(void) {
	Array<Int> a, b;
	Input("input.txt").lines()
		.map($a.view().split(' ').map(Pred::ToNumber<Int>)$)
		.forEach($l1 a += $0[0]; b += $0[1] $);
	Map<Int, Int> map;
	b.forEach($l1 map.has($0) ? map[$0] += 1 : map.add($0, 1) $);
	Ket::println("{}",
		a.map($f1 $0 * map.get($0).value(0) $).sum()
	);
}
