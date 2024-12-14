Int main(void) {
	struct Robot { Vec2I p, v; };
	Vec2I size{101, 103};
	Vec2I quadSize = (size + 1) / 2;
	TupleN<Int, 4> quads =
		"\\-?\\d+"_regex.exec(Input("input.txt").readAll()).range()
		.map($f1 Number::from<Int>($0[0].view()) $)
		.chunk(4).map($a.begin()$)
		.map($f1 Robot{Vec2I{*$0++, *$0++}, Vec2I{*$0++, *$0}} $)
		.map($f1 ($0.p = Math::cycle($0.p + $0.v * 100, size), $0) $)
		.filter($f1 $0.p.x != quadSize.x - 1 && $0.p.y != quadSize.y - 1 $)
		.foldLeft(TupleN<Int, 4>{0,0,0,0}, $f(quads, bot)
			$match (bot.p / quadSize) (
			$case| Vec2I{0, 0} = $e (quads.a += 1, quads) $,
			$case| Vec2I{1, 0} = $e (quads.b += 1, quads) $,
			$case| Vec2I{0, 1} = $e (quads.c += 1, quads) $,
			$case| Vec2I{1, 1} = $e (quads.d += 1, quads) $,
			)
		$)
	;
	Ket::println("{}", quads.a * quads.b * quads.c * quads.d);
}
