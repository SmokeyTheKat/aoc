Int main(void) {
	Array<String> omap = Input("input.txt").lines();
	Int h = omap.length(), w = omap[0].length();
	auto at = $f(pos) Ref{omap[pos.y][pos.x]} $;
	Vec2I startPos = Iter::range2D(w, h).find($f1 at($0) == '^' $).value();
	
	Vec2I pos = startPos;
	Vec2I dir{0,-1};
	while (true) {
		at(pos) = '@';
		Vec2I ahead = pos + dir;
		if (!ahead.inRange(Vec2I{w,h})) break;
		if (at(ahead) == '#') dir.rotate90CW();
		else pos = ahead;
	}
	
	auto tryWithBlockAt = [&](Vec2I blockPos) {
		if (blockPos == startPos || at(blockPos) != '@') return false;
		Array<String> map = omap;
		auto at = $f(pos) Ref{map[pos.y][pos.x]} $;
		at(blockPos) = '#';
		FlatSet<Tuple<Vec2I, Vec2I>> states;
		Vec2I pos = startPos;
		Vec2I dir{0,-1};
		while (true) {
			Vec2I ahead = pos + dir;
			if (!ahead.inRange(Vec2I{w,h})) break;
			if (at(ahead) == '#') {
				dir.rotate90CW();
				if (!states.tryAdd(Tuple{pos, dir})) return true;
			} else pos = ahead;
		}
		return false;
	};
	
	Ket::println("{}", Iter::range2D(w, h).count(tryWithBlockAt));
}
