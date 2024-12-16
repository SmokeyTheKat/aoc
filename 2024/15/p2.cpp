Int main(void) {
	String data = Input("input.txt").readAll();
	auto [mapData, moveData] = data.view().splitFirst("\n\n");
	String moves = moveData.split("\n").collect<String>();
	Array<String> map = mapData.split("\n").map($f(line)
		line.range().foldLeft(String(), $f(acc, c)
			$match (c) (
			$case| '#' = $e acc + "##" $,
			$case| 'O' = $e acc + "[]" $,
			$case| _ = $e acc + c + '.' $
			)
		$)
	$);

	Int h = map.length(), w = map[0].length();
	auto at = [&](Vec2I pos) -> Char& { return map[pos.y][pos.x]; };
	Vec2I bot = Iter::range2D(w, h).find($f1 at($0) == '@' $).value();
	at(bot) = '.';

	auto isBox = $f(pos) at(pos) == '[' || at(pos) == ']' $;

	auto boxLeft = $f(pos) (at(pos) == '[') ? (pos) : (pos - Vec2I{1,0}) $;

	auto fixBoxPos = $l(pos, dir)
		if (at(pos) == '[' && dir.x > 0) return pos + Vec2I{1,0};
		else if (at(pos) == ']' && dir.x < 0) return pos - Vec2I{1,0};
		else if (dir.x == 0) return boxLeft(pos);
		else return pos;
	$;

	auto hasWallInPath = $l(pos, dir)
		Vec2I fwd = fixBoxPos(pos, dir) + dir;
		return at(fwd) == '#' || (dir.y != 0 && at(fwd + Vec2I{1,0}) == '#');
	$;

	auto getPushingBoxes = [&](Vec2I pos, Vec2I dir) -> Array<Vec2I> {
		Vec2I fwd = fixBoxPos(pos, dir) + dir;
		if (dir.y == 0) return isBox(fwd) ? Array{boxLeft(fwd)} : Array<Vec2I>{};
		Array<Vec2I> out;
		if (isBox(fwd)) out += boxLeft(fwd);
		if (isBox(fwd + Vec2I{1,0}) && at(fwd) != '[') out += boxLeft(fwd + Vec2I{1,0});
		return out;
	};

	auto getAllPushingBoxes = [&](this auto&& rec, Vec2I pos, Vec2I dir, Array<Vec2I>& acc) -> Bool {
		if (hasWallInPath(pos, dir)) return false;
		Array<Vec2I> hitting = getPushingBoxes(pos, dir).range().filter($f1 !acc.has($0) $);
		if (hitting.length() == 0) return true;
		if (!hitting.all($f(next) rec(next, dir, acc) $)) return false;
		acc.pushBack(hitting);
		return true;
	};

	FlatMap<Char, Vec2I> dirs = {{'>',{1,0}},{'<',{-1,0}},{'^',{0,-1}},{'v',{0,1}}};
	for (Vec2I dir : moves.map($f1 dirs[$0].value() $)) {
		if (isBox(bot + dir)) {
			Array<Vec2I> boxes;
			if (getAllPushingBoxes(bot + dir, dir, Ref{boxes})) {
				boxes.range().append(boxLeft(bot + dir)).forEach($l(pos, i)
					at(pos) = '.';
					at(pos + Vec2I{1,0}) = '.';
					at(pos + dir) = '[';
					at(pos + Vec2I{1,0} + dir) = ']';
				$);
				bot += dir;
			}
		} else if (at(bot + dir) == '.') {
			bot += dir;
		}
	}
	Ket::println("{}",
		Iter::range2D(w, h).filter($f1 at($0) == '[' $).sum($f1 $0.y * 100 + $0.x $)
	);
}
