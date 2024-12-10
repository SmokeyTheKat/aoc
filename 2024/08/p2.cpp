Int main(void) {
	Array<String> map = Input("input.txt").lines();
	Int h = map.length(), w = map[0].length();
	MultiMap<Char, Vec2I> towers =
		Iter::range2D(w, h)
			.map($f1 Tuple{map[$0.y][$0.x], $0} $)
			.filter($a.a != '.' $);
	towers
		.range().map($a.b $)
		.forEach($l(type)
			type.forEach($l(towerA) type.forEach($l(towerB)
				if (towerA == towerB) return;
				Vec2I dir = towerB - towerA;
				Vec2I node = towerB;
				while (node.inRange(Vec2I{w,h})) {
					map[node.y][node.x] = '@';
					node += dir;
				}
			$)$)
		$);
	Ket::println("{}", Iter::range2D(w, h).count($f1 map[$0.y][$0.x] == '@' $));
}
