Int main(void) {
	struct Machine { Vec2I a, b, p; };
	Ket::println("{}",
		"\\d+"_regex.exec(Input("input.txt").readAll()).range()
		.map($f1 Number::from<Int>($0[0].view()) $)
		.chunk(2).map($a.begin()$)
		.map($f1 Vec2I{*$0++, *$0} $)
		.chunk(3).map($a.begin()$)
		.map($f1 Machine{*$0++, *$0++, *$0} $)
		.sum($l(m)
			Int a = m.p.cross(m.b) / m.a.cross(m.b);
			Int b = m.a.cross(m.p) / m.a.cross(m.b);
			if (a * m.a.x + b * m.b.x == m.p.x && a * m.a.y + b * m.b.y == m.p.y) {
				return 3 * a + b;
			} else return 0;
		$)
	);
}