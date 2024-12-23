Int main(void) {
	Array<String> data = Input("input.txt").lines();
	Span<String> designs = data;
	Array<StringView> towels = designs.pop(1)[0].view().split(", ");
	
	HashMap<StringView, Bool> valid;
	Func<Bool(StringView)> checkPattern = [&](StringView design) -> Bool {
		if (valid.has(design)) return valid.get(design).value();
		if (design.length() == 0) return true;
		for (StringView towel : towels) {
			if (design.startsWith(towel)) {
				if (checkPattern(design.sub(towel.length()))) {
					valid.add(design, true);
					return true;
				}
			}
		}
		valid.add(design, false);
		return false;
	};
	Ket::println("{}", designs.count(checkPattern));
}
