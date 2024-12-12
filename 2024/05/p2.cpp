Int main(void) {
	String data = Input("input.txt").readAll();
	auto [rulesData, updatesData] = data.view().splitFirst("\n\n");
	MultiMap<Size, Size> rules =
		rulesData.split('\n').map($a.split('|').map($a.getInt()$)$)
		.map($f1 Tuple{$0[0], $0[1]} $);
		
	auto ordered = [&](Array<Size> update) {
		FlatSet<Size> visited;
		Array<Size> out;
		Func<void(Size)> visit = [&](Int node) {
			if (!update.has(node) || !visited.add(node)) return;
			rules[node].inspect($a.forEach(visit)$);
			out.pushFront(node);
		};
		update.forEach(visit);
		return out;
	};
		
	auto outOfOrder = $f(l, r) rules[r].map(false, $a.has(l)$)$;
	Ket::println("{}",
		updatesData
			.split('\n').map($a.split(',').map($a.getInt()$)$)
			.map($l(update)
				auto outOfOrder = $f(l, r) rules[r].map(false, $a.has(l)$)$;
				auto outOfOrderAt = $f(l,i) update.range().skip(i+1).any($f(r) outOfOrder(l, r)$)$;
				if (!update.any(outOfOrderAt)) return 0_size;
				return ordered(update)[update.length() / 2];
			$).sum()
	);
}
