Int main(void) {
	Func<Bool(Size, Span<Size>)> isValid = [&](Size value, Span<Size> ops) {
		if (ops.length() == 1) return ops[0] == value;
		Size next = ops.popBack();
		String valueStr = String::from(value);
		String nextStr = String::from(next);
		return (
			isValid(value - next, ops) ||
			(value % next == 0 && isValid(value / next, ops)) || (
				valueStr.endsWith(nextStr) &&
				isValid(valueStr.view().removeSuffix(nextStr.length()).getInt(), ops)
			)
		);
	};
	Ket::println("{}",
		Input("input.txt").lines().range()
		.map($a.view().splitFirst(':')$)
		.map($f1 Tuple{$0.a.getInt(), $0.b.trim().split(" ").map($a.getInt()$)}$)
		.filter($f1 isValid($0.a, $0.b)$)
		.sum<Size>($a.a $)
	);
}