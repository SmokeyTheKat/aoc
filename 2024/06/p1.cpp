Int main(void) {
	Array<String> map = Input("input.txt").lines();
	Int h = map.length(), w = map[0].length();
	auto at = $f(pos) Ref{map[pos.y][pos.x]} $;
	Vec2I pos = Iter::range2D(w, h).find($f1 at($0) == '^' $).value();
	Vec2I dir{0,-1};
	while (true) {
		at(pos) = '@';
		Vec2I ahead = pos + dir;
		if (!ahead.inRange(Vec2I{w,h})) break;
		if (at(ahead) == '#') dir.rotate90CW();
		else pos = ahead;
	}
	Ket::println("{}", map.sum($a.count($a == '@' $)$));
}
