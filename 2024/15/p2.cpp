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
	auto at = $f(pos) Ref{map[pos.y][pos.x]} $;
	Vec2I bot = Iter::range2D(w, h).find($f1 at($0) == '@' $).value();
	at(bot) = '.';
	
	FlatMap<Char, Vec2I> dirs = {{'>',{1,0}},{'<',{-1,0}},{'^',{0,-1}},{'v',{0,1}}};
	moves.map($f1 dirs[$0].value() $).forEach($l(dir)
		FlatSet<Vec2I> targets = {bot};
		for (auto pos : targets.suspendRange()) {
			Vec2I next = pos + dir;
			if (targets.has(next)) continue;
			if (at(next) == '#') return;
			else if (at(next) == '[') targets.add(next).add(next + Vec2I{1,0});
			else if (at(next) == ']') targets.add(next - Vec2I{1,0}).add(next);
		}
		for (auto pos : targets) at(pos) = '.';
		for (auto [pos, i] : targets.range().skip(1).enumerate()) {
			at(pos + dir) = i % 2 == 0 ? '[' : ']';
		}
		bot += dir;
	$);
	Ket::println("{}",
		Iter::range2D(w, h).filter($f1 at($0) == '[' $).sum($f1 $0.y * 100 + $0.x $)
	);
}
