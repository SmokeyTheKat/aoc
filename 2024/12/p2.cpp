Int main(void) {
	Array<String> map = Input("input.txt").lines();
	Int h = map.length(), w = map[0].length();
	auto at = $f1 $0.inRange(Vec2I{w,h}) ? SomeRef(map[$0.y][$0.x]) : None() $;
	Array<Vec2I> udlr{{0,-1},{0,1},{-1,0},{1,0}};
	Array<Tuple<Vec2I, Vec2I>> corners = {
		{{{ 0,-1}, { 1, 0}}}, // tr
		{{{ 1, 0}, { 0, 1}}}, // br
		{{{ 0, 1}, {-1, 0}}}, // bl
		{{{-1, 0}, { 0,-1}}}, // tl
	};
	Set<Vec2I> visited;
	Func<Vec2I(Char, Vec2I)> compute = [&](Char type, Vec2I pos) -> Vec2I {
		if (at(pos) != type) return Vec2I{0,0};
		if (!visited.tryAdd(pos)) return Vec2I{0,0};
		Int cornerCount = corners.count($f1
			$0.all($f(dir) at(pos + dir) != type $)
		$);
		cornerCount += corners.count($f1
			at(pos + $0.a + $0.b) != type &&
			$0.all($f(dir) at(pos + dir) == type $)
		$);
		return Vec2I{1, cornerCount} + udlr.sum($f(dir) compute(type, pos + dir) $);
	};
	Ket::println("{}",
		Iter::range2D(w, h)
		.map($f(pos) compute(at(pos).value(), pos) $)
		.sum($f1 $0.x * $0.y $)
	);
}
