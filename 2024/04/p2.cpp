Int main(void) {
	Array<String> map = Input("input.txt").lines();
	Int h = map.length(), w = map[0].length();
	auto at = $f(pos) pos.inRange(Vec2I{w,h}) ? map[pos.y][pos.x] : 0 $;
	auto isMas = [&](Vec2I pos, Vec2I dir) {
		return Math::minMax(at(pos + dir), at(pos - dir)) == Tuple{'M', 'S'};
	};
	auto countXMas = [&](Vec2I pos) {
		if (at(pos) != 'A') return false;
		return isMas(pos, Vec2I{1,1}) && isMas(pos, Vec2I{1,-1});
	};
	Ket::println("{}", Iter::range2D(w, h).count(countXMas));
}
