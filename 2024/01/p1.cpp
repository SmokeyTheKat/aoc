Int main(void) {
	Array<Int> a, b;
	Input("input.txt").lines()
		.map($a.view().split(' ').map(Pred::ToNumber<Int>)$)
		.forEach($l1 a += $0[0]; b += $0[1] $);
	Ket::println("{}", a.sort().range().map2(b.sort(), Pred::Dist).sum());
}
