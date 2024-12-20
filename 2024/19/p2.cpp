Int main(void) {
	Array<String> data = Input("input.txt").lines();
	Span<String> designs = data;
	Array<StringView> towels = designs.pop(1)[0].view().split(", ");
	
	HashMap<StringView, I64> valid;
	Func<I64(StringView)> countPattern = [&](StringView design) -> I64 {
		if (valid.has(design)) return valid.get(design).value();
		if (design.length() == 0) return 1;
		I64 count = 0;
		for (StringView towel : towels) {
			if (design.startsWith(towel)) {
				count += countPattern(design.sub(towel.length()));
			}
		}
		valid.add(design, count);
		return count;
	};
	Ket::println("{}", designs.sum(countPattern));
}
