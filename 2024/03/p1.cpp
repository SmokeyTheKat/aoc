Int main(void) {
	String data = Input("input.txt").readAll();
	Ket::println("{}", 
		"mul\\((\\d+),(\\d+)\\)"_regex.exec(data)
		.sum($f1 $0[1].getInt() * $0[2].getInt() $)
	);
}
