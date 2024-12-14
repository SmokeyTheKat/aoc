Int main(void) {
	struct Robot { Vec2I p, v; };
	Vec2I size{101, 103};
	Vec2I quadSize = (size + 1) / 2;
	Array<Robot> bots =
		"\\-?\\d+"_regex.exec(Input("input.txt").readAll()).range()
		.map($f1 Number::from<Int>($0[0].view()) $)
		.chunk(4).map($a.begin()$)
		.map($f1 Robot{Vec2I{*$0++, *$0++}, Vec2I{*$0++, *$0}} $)
	;
	Array<String> map(String('.', size.x), size.y);
	auto at = $f1 $0.inRange(size) ? SomeRef(map[$0.y][$0.x]) : None() $;
	Int iteration = 0;
	while (true) {
		iteration += 1;
		bots.forEach($l1
			at($0.p) = '.';
			$0.p = Math::cycle($0.p + $0.v, size);
			at($0.p) = '*'
		$);
		for (Robot& bot : bots) {
			if (Iter::range(5).cast<Int>().all($f(i)
				at(bot.p + Vec2I{i, i}) == '*' &&
				at(bot.p + Vec2I{-i, i}) == '*'
			$)) {
				Ket::println("{}", iteration);
				return 0;
			}
		}
	}
}
