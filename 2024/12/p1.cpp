Int main(void) {
	Array<String> map = Input("input.txt").lines();
	Int h = map.length(), w = map[0].length();
	auto at = $f1 $0.inRange(Vec2I{w,h}) ? SomeRef(map[$0.y][$0.x]) : None() $;
	Array<Vec2I> udlr{{0,-1},{0,1},{-1,0},{1,0}};
	Set<Vec2I> visited;
	Func<Vec2I(Char, Vec2I)> compute = [&](Char type, Vec2I pos) -> Vec2I {
		if (at(pos) != type) return Vec2I{0,0};
		if (!visited.add(pos)) return Vec2I{0,0};
		Int perim = udlr.count($f1 at(pos + $0) != type $);
		return Vec2I{1, perim} + udlr.sum($f1 compute(type, pos + $0) $);
	};
	Ket::println("{}",
		Iter::range2D(w, h)
		.map($f(pos) compute(at(pos).value(), pos) $)
		.sum($f1 $0.x * $0.y $)
	);
}
