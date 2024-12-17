Int main(void) {
	Array<String> map = Input("input.txt").lines();
	Int h = map.length(), w = map[0].length();
	auto at = $f(pos) Ref{map[pos.y][pos.x]} $;
	Vec2I startPos = Iter::range2D(w, h).find($f1 at($0) == 'S' $).value();
	Vec2I endPos = Iter::range2D(w, h).find($f1 at($0) == 'E' $).value();
	at(startPos) = '.';
	at(endPos) = '.';
	Array<Vec2I> dirs = {{0,-1},{0,1},{-1,0},{1,0}};

	Func<Bool(Vec2I)> isCorner = [&](Vec2I pos) -> Bool {
		if (at(pos) != '.') return false;
		Array<Vec2I> p = dirs.range().filter($f(dir) at(pos + dir) == '.' $);
		if (p.length() > 2) return true;
		if (p.length() == 1) return true;
		return p[0] != -p[1];
	};

	auto getNeighbors = $f(pos) dirs.range().filter($f(dir) at(pos + dir) == '.' $).collect() $;
	Map<Vec2I, Array<Vec2I>> corners =
		Iter::range2D(w-2, h-2)
		.map($a + Vec2I{1,1}$).filter(isCorner)
		.map($f(pos) Tuple{pos, getNeighbors(pos)} $);

	struct Node {
		Array<Tuple<Vec2I, Int>> nodes;
		Vec2I pos, dir;
		Int cost;
		Array<Node*> prev;
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

	auto neighborsAndCost = [&](Vec2I from, Vec2I dir) {
		Array<Tuple<Vec2I, Int>> nodes;
		Int cost = 1;
		for (from += dir; at(from) == '.'; from += dir, cost += 1) {
			if (isCorner(from)) nodes += Tuple{from, cost};
		}
		return nodes;
	};

	Array<Node> nodes;
	for (auto& [pos, paths] : corners) {
		Array<Tuple<Vec2I, Int>> neighbors = paths.flatMap($f(dir) neighborsAndCost(pos, dir) $);
		for (Vec2I dirFrom : dirs) {
			nodes += Node{neighbors, pos, dirFrom, NumberInfo<Int>::max}.addTurnCost(dirFrom);
		}
	}

	Array<Node*> q = nodes.map(Pred::Ref);
	Node* start = nodes.find($a == Tuple{startPos, Vec2I{1,0}} $).ptr();
	Node* end = nodes.find($a == Tuple{endPos, Vec2I{1,0}} $).ptr();
	start->cost = 0;

	while (q.length() > 0) {
		Node* u = q.range().min($f2 $0->cost < $1->cost $).value();
		q.remove(u);
		for (auto [pos, cost] : u->nodes) {
			Node* v = nodes.find($a == Tuple{pos, u->dir} $).ptr();
			if (!q.has(v)) continue;
			Int alt = u->cost + cost;
			if (alt == v->cost) {
				v->prev.pushBack(u);
			} else if (alt < v->cost) {
				v->cost = alt;
				v->prev.clear().pushBack(u);
			}
		}
	}

	FlatSet<Node*> visited;
	Func<void(Node*)> countBest = [&](Node* node) {
		if (!visited.tryAdd(node)) return;
		if (node->prev.length() == 0) return;
		Int count = 0;
		for (Node* u : node->prev) {
			Vec2I from = u->pos;
			Vec2I to = node->pos;
			Vec2I dir = (to - from).normalize();
			while (from != to) {
				at(from) = 'O';
				from += dir;
			}
			countBest(u);
		}
	};
	countBest(end);
	Ket::println("{}", Iter::range2D(w, h).count($f1 at($0) == 'O' $) + 1);
}
