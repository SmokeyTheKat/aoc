Int main(void) {
	String data = Input("input.txt").readAll();
	auto [mapData, moveData] = data.view().splitFirst("\n\n");
	String moves = moveData.split("\n").collect<String>();
	Array<String> map = mapData.split("\n").map($a.string()$);
	Int h = map.length(), w = map[0].length();
	auto at = [&](Vec2I pos) -> Char& { return map[pos.y][pos.x]; };
	Vec2I bot = Iter::range2D(w, h).find($f1 at($0) == '@' $).value();
	at(bot) = '.';
	FlatMap<Char, Vec2I> dirs = {{'>',{1,0}},{'<',{-1,0}},{'^',{0,-1}},{'v',{0,1}}};
	for (Vec2I dir : moves.map($f1 dirs[$0].value() $)) {
		if (at(bot + dir) == 'O') {
			Size count = 1 + Iter::naturals.findIndex($f1 at(bot + dir * ($0 + 1)) != 'O' $);
			if (at(bot + dir * count) == '.') {
				O::swap(at(bot + dir), at(bot + dir * count));
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
