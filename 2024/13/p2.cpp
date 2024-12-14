Int main(void) {
	struct Machine { Vec2I64 a, b, p; };
	Ket::println("{}",
		"\\d+"_regex.exec(Input("input.txt").readAll()).range()
		.map($f1 Number::from<I64>($0[0].view()) $)
		.chunk(2).map($a.begin()$)
		.map($f1 Vec2I64{*$0++, *$0} $)
		.chunk(3).map($a.begin()$)
		.map($f1 Machine{*$0++, *$0++, *$0 + 10000000000000} $)
		.sum($l(m)
			I64 a = m.p.cross(m.b) / m.a.cross(m.b);
			I64 b = m.a.cross(m.p) / m.a.cross(m.b);
			if (a * m.a.x + b * m.b.x == m.p.x && a * m.a.y + b * m.b.y == m.p.y) {
				return 3_i64 * a + b;
			} else return 0_i64;
		$)
	);
}