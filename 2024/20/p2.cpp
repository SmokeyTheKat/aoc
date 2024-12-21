Int main(void) {
	struct Node {
		Bool wall;
		Bool start;
		Int cost;
		Vec2I pos;
	};
	Array<Array<Node>> map =
		Input("input.txt").lines()
		.map($f(const& line, y)
			line.range().map($f(c, x) $match (c) (
				$case| '#' = Node{true, false, 0, Vec2I{Int(x),Int(y)}},
				$case| 'S' = Node{false, true, NumberInfo<Int>::max, Vec2I{Int(x),Int(y)}},
				$case| 'E' = Node{false, true, NumberInfo<Int>::max, Vec2I{Int(x),Int(y)}},
				$case| '.' = Node{false, false, NumberInfo<Int>::max, Vec2I{Int(x),Int(y)}}
			)$).collect()
		$);
	Int h = map.length(), w = map[0].length();
	auto at = $f(pos) pos.inRange(Vec2I{w,h}) ? SomeRef(map[pos.y][pos.x]) : None() $;
	
	Array<Vec2I> dirs = {{0,-1},{0,1},{-1,0},{1,0}};
	auto neighborsAt = [&](Node* n) -> Array<Node*> {
		return dirs.range().map($a + n->pos $).filter($f1 at($0) && !at($0)->wall $).map($f1 at($0).ptr()$);
	};

	Array<Node*> points = map.flatMap($f1 $0.range().filter($a.start $).map(Pred::Ref) $);
	
	Array<Node*> q = map.flatMap($a.range().filter($a.wall == false $).map(Pred::Ref)$);
	points[0]->cost = 0;
	while (q.length() > 0) {
		Node* u = q.range().min($f2 $0->cost < $1->cost $).value();
		q.remove(u);
		for (Node* v : neighborsAt(u)) {
			if (!q.has(v)) continue;
			Int alt = u->cost + 1;
			if (alt < v->cost) v->cost = alt;
		}
	}

	Set<Node*> visited;
	Func<Int(Node*)> walk = [&](Node* node) -> Int {
		if (!visited.tryAdd(node)) return 0;
		Int count = 0;
		for (Int x = -20; x <= 20; x++) {
			for (Int y = -20 + Math::abs(x); y <= 20 - Math::abs(x); y++) {
				Vec2I pos = node->pos + Vec2I{x,y};
				if (pos.inRange(Vec2I{w,h}) && at(pos)->wall == false) {
					Int cost = node->cost - (Math::abs(x) + Math::abs(y)) - at(pos)->cost;
					if (cost >= 100) count += 1;
				}
			}
		}
		return count + neighborsAt(node).sum(walk);
	};
	Ket::println("{}", walk(points[0]));
}
