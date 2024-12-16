Int main(void) {
	Array<String> map = Input("input.txt").lines();
	Int h = map.length(), w = map[0].length();
	auto at = $f(pos) Ref{map[pos.y][pos.x]} $;
	Vec2I start = Iter::range2D(w, h).find($f1 at($0) == 'S' $).value();
	Vec2I end = Iter::range2D(w, h).find($f1 at($0) == 'E' $).value();
	at(start) = '.';
	at(end) = '.';
	Array<Vec2I> dirs = {{0,-1},{0,1},{-1,0},{1,0}};

	Func<Bool(Vec2I)> isCorner = [&](Vec2I pos) -> Bool {
		if (at(pos) != '.') return false;
		Array<Vec2I> p = dirs.range().filter($f(dir) at(pos + dir) == '.' $);
		if (p.length() > 2) return true;
		if (p.length() == 1) return true;
		return p[0] != -p[1];
	};

	Map<Vec2I, Array<Vec2I>> corners =
		Iter::range2D(w-2, h-2)
		.map($a + Vec2I{1,1}$).filter(isCorner)
		.map($f(pos)
			Tuple{
				pos,
				dirs.range().filter($f(dir) at(pos + dir) == '.' $).collect()
			}
		$);

	struct Node {
		Array<Tuple<Vec2I, Int>> nodes;
		Vec2I pos, dir;
		Node& addTurnCost(Vec2I dirFrom) {
			for (auto& [dir, cost] : nodes) {
				cost += $match (dirFrom) (
					$case| dir = 0,
					$case| -dir = 2000,
					$case| _ = 1000
				);
			}
			return *this;
		}
		Bool operator==(const Tuple<Vec2I, Vec2I>& state) const {
			return state.a == pos && state.b == dir;
		}
	};

	auto pathsCosts = [&](Vec2I from, Vec2I dir) -> Array<Tuple<Vec2I, Int>> {
		Array<Tuple<Vec2I, Int>> nodes;
		Int cost = 0;
		from += dir;
		while (at(from) == '.') {
			cost += 1;
			if (isCorner(from)) {
				nodes += Tuple{from, cost};
			}
			from += dir;
		}
		return nodes;
	};

	Array<Node> nodes(SizeHint{corners.length()*2});
	for (auto& [pos, paths] : corners) {
		if (pos == Vec2I{1,13}) {
			pos.x += 0;
		}
		Array<Tuple<Vec2I, Int>> neighbors;
		for (Vec2I dir : paths) {
			neighbors += pathsCosts(pos, dir);
		}
		for (Vec2I dirFrom : dirs) {
			nodes += Node{neighbors, pos, dirFrom}.addTurnCost(dirFrom);
		}
	}

	Array<Int> dist(NumberInfo<Int>::max, nodes.length());
	Array<Int> q = Iter::range(nodes.length());
	Int startId = nodes.findIndex($a == Tuple{start, Vec2I{1,0}} $);
	Int endId = nodes.findIndex($a == Tuple{end, Vec2I{1,0}} $);
	dist[startId] = 0;

	while (q.length() > 0) {
		Int u = q.range().min($f2 dist[$0] < dist[$1] $).value();
		q.remove(u);
		Node& un = nodes[u];
		if (un.pos == end) {
			end.x += 0;
		}
		for (auto [pos, cost] : un.nodes) {
			Int v = nodes.findIndex($a == Tuple{pos, un.dir} $);
			if (!q.has(v)) continue;
			Int alt = dist[u] + cost;
			if (alt < dist[v]) {
				dist[v] = alt;
			}
		}
	}

	Ket::println("{}", dist[endId]);
}
