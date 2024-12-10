Int main(void) {
	Array<String> map = Input("input.txt").lines();
	Int h = map.length(), w = map[0].length();
	auto at = $f(pos) pos.inRange(Vec2I{w,h}) ? map[pos.y][pos.x] : 0 $;
	auto checkDir = $f(pos, dir) "XMAS"_sv.all($f2 at(pos + dir * $1) == $0 $) $;
	Array<Vec2I> dirs = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
	auto countAt = $f(pos) dirs.count($f(dir) checkDir(pos, dir) $) $;
	Ket::println("{}", Iter::range2D(w, h).sum(countAt));
}
