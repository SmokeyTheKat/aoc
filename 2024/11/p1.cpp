Int main(void) {
	Array<I64> stones = Input("input.txt").readAll().view()
		.split(' ').map($f1 Number::from<I64>($0) $);
	
	auto blink = [&](void) {
		Array<I64> next;
		for (I64 stone : stones) {
			if (stone == 0) next += 1;
			else if (Int dc = Math::digitCount(stone); dc % 2 == 0) {
				String num = String::from(stone);
				next += num.view().sub(dc / 2).getInt();
				next += num.view().slice(dc / 2).getInt();
			} else next += stone * 2024;
		}
		stones = O::move(next);
	};
	
	Iter::range(25).forEach($l1 blink() $);
	Ket::println("{}", stones.length());
}