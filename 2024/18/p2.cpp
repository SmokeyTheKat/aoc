Int main(void) {
	Int h = 71, w = 71;
	Array<Array<Int>> map(Array<Int>(0, w), h);
	auto at = $f(pos) pos.inRange(Vec2I{w,h}) ? SomeRef(map[pos.y][pos.x]) : None() $;
	Array<Vec2I> abytes = 
		Input("input.txt").lines().range()
			.map($a.view().split(',').map($a.template getInt<Int>()$)$).map($f1 Vec2I{$0[0], $0[1]} $)
	;
	Span<Vec2I> bytes = abytes;
	bytes.pop(1024).forEach($l1 at($0) = -1 $);
	
	Array<Vec2I> dirs = {{0,-1},{0,1},{-1,0},{1,0}};
	auto neighborsAt = [&](Vec2I pos) -> Array<Vec2I> {
		return dirs.range().map($a + pos $).filter($f1 at($0) && at($0) != -1 $);
	};
	auto fill = [&](this auto&& rec, Int layer, Vec2I pos) {
		if (at(pos) != layer) return;
		at(pos) += 1;
		neighborsAt(pos).forEach($l1 rec(layer, $0) $);
	};
	while (bytes.length() > 0) {
		Vec2I byt = bytes.popFront();
		at(byt) = -1;
		fill(at(Vec2I{0,0}).value(), Vec2I{0,0});
		if (at(Vec2I{0,0}) != at(Vec2I{w-1, h-1})) {
			Ket::println("{},{}", byt.x, byt.y);
			break;
		}
	}
}
