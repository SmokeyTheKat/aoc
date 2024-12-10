Int main(void) {
	Func<Bool(Size, Span<Size>)> isValid = [&](Size value, Span<Size> ops) {
		if (ops.length() == 1) return ops[0] == value;
		Size next = ops.popBack();
		return (
			isValid(value - next, ops) ||
			(value % next == 0 && isValid(value / next, ops))
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
