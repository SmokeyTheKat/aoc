Int main(void) {
	Array<String> map = Input("input.txt").lines();
	Int h = map.length(), w = map[0].length();
	auto at = $f1 $0.inRange(Vec2I{w,h}) ? SomeRef(map[$0.y][$0.x]) : None() $;
	Array<Vec2I> heads = Iter::range2D(w, h).filter($f1 at($0) == '0' $);
	Array<Vec2I> dirs{{1,0},{-1,0},{0,1},{0,-1}};
	Set<Vec2I> visited;
	Func<Int(Vec2I)> score = [&](Vec2I pos) -> Int {
		Char cur = at(pos).value();
		if (cur == '0') visited.clear();
		if (!visited.tryAdd(pos)) return 0;
		if (cur == '9') return 1;
		return dirs.range()
			.filter($f1 at(pos + $0) == cur + 1 $)
			.sum($f1 score(pos + $0) $);
	};
	Ket::println("{}", heads.sum(score));
}
