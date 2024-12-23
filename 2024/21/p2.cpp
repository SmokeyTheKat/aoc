Int main(void) {
	Array<String> codes = Input("input.txt").lines();
	FlatMap<Char, Vec2I> kpPos = {
		{'7', {0,0}},{'8', {1,0}},{'9', {2,0}},
		{'4', {0,1}},{'5', {1,1}},{'6', {2,1}},
		{'1', {0,2}},{'2', {1,2}},{'3', {2,2}},
		{' ', {0,3}},{'0', {1,3}},{'A', {2,3}}
	};
	FlatMap<Char, Vec2I> dpPos = {
		{' ', {0,0}},{'^', {1,0}},{'A', {2,0}},
		{'<', {0,1}},{'v', {1,1}},{'>', {2,1}}
	};

	auto pads = $f(pad) pad == 0 ? Ref{kpPos} : Ref{dpPos} $;

	auto xChar = $f1 $0 < 0 ? '<' : '>' $;
	auto yChar = $f1 $0 < 0 ? '^' : 'v' $;

	HashMap<Tuple<Int, String>, I64> cache;
	auto move = [&](this auto&& rec, Int pad, String inp) -> I64 {
		if (pad == 26) return inp.length();
		if (auto opt = cache.get(Tuple{pad, inp})) return opt.value();
		I64 count = 0;
		Char from = 'A';
		for (Char to : inp) {
			Vec2I p1 = pads(pad)[from].value();
			Vec2I p2 = pads(pad)[to].value();
			Vec2I d = p2 - p1;
			String h = String(xChar(d.x), Math::abs(d.x));
			String v = String(yChar(d.y), Math::abs(d.y));
			Vec2I invalid = pads(pad)[' '].value();
			I64 min = NumberInfo<I64>::max;
			if (!(p2.x == invalid.x && p1.y == invalid.y)) {
				min = Math::min(min, rec(pad + 1, h + v + 'A'));
			}
			if (!(p2.y == invalid.y && p1.x == invalid.x)) {
				min = Math::min(min, rec(pad + 1, v + h + 'A'));
			}
			count += min;
			from = to;
		}
		cache.add(Tuple{pad, inp}, count);
		return count;
	};

	auto calc = $a.view().removeSuffix(1).getInt()$;
	Ket::println("{}", codes.sum($f1 move(0, $0) * calc($0) $));
}
