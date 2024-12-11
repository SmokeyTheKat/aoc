Int main(void) {
	Map<I64, I64> stones = Input("input.txt").readAll().view()
		.split(' ').map($f1 Tuple{Number::from<I64>($0), 1_i64} $);
	
	auto blink = [&](void) {
		Map<I64, I64> next;
		for (auto [stone, count] : stones) {
			if (stone == 0) next.defaulted(1, 0) += count;
			else if (Int dc = Math::digitCount(stone); dc % 2 == 0) {
				String num = String::from(stone);
				next.defaulted(num.view().sub(dc / 2).getInt(), 0) += count;
				next.defaulted(num.view().slice(dc / 2).getInt(), 0) += count;
			} else next.defaulted(stone * 2024, 0) += count;
		}
		stones = O::move(next);
	};
	
	Iter::range(75).forEach($l1 blink() $);
	Ket::println("{}", stones.sum($a.b $));
}