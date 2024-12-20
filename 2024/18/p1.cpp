Int main(void) {
	struct Node {
		Bool wall;
		Int cost;
		Vec2I pos;
	};
	Int h = 71, w = 71;
	Array<Array<Node>> map(Array<Node>(Node{false,NumberInfo<Int>::max}, w), h);
	auto at = $f(pos) pos.inRange(Vec2I{w,h}) ? SomeRef(map[pos.y][pos.x]) : None() $;
	Iter::range2D(w, h).forEach($l1 at($0)->pos = $0 $);
	Input("input.txt").lines().range()
		.map($a.view().split(',').map($a.template getInt<Int>()$)$).map($f1 Vec2I{$0[0], $0[1]} $)
		.take(1024).forEach($l1 at($0)->wall = true $)
	;
	
	Array<Vec2I> dirs = {{0,-1},{0,1},{-1,0},{1,0}};
	auto neighborsAt = [&](Node* n) -> Array<Node*> {
		return dirs.range().map($a + n->pos $).filter($f1 at($0) && !at($0)->wall $).map($f1 at($0).ptr()$);
	};
	
	Array<Node*> q = map.flatMap($a.range().filter($a.wall == false $).map(Pred::Ref)$);
	map[0][0].cost = 0;
	while (q.length() > 0) {
		Node* u = q.range().min($f2 $0->cost < $1->cost $).value();
		q.remove(u);
		for (Node* v : neighborsAt(u)) {
			if (!q.has(v)) continue;
			Int alt = u->cost + 1;
			if (alt < v->cost) v->cost = alt;
		}
	}
	Ket::println("{}", at(Vec2I{w-1,h-1})->cost);
}
