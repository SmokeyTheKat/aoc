Int main(void) {
	String data = Input("input.txt").readAll();
	Array<I64> prog = data.view().split("Program: ")[1].split(',').map(Pred::ToNumber<I64>);
	I64 r[3] = {
		data.view().split("Register A: ")[1].getInt<I64>(),
		data.view().split("Register B: ")[1].getInt<I64>(),
		data.view().split("Register C: ")[1].getInt<I64>()
	};
	
	auto combo = $f1 ($0 >= 4 && $0 <= 6) ? r[$0 - 4] : $0 $;
	
	auto expectWith = [&](Span<I64> out, I64 with) {
		r[0] = with;
		r[1] = 0;
		r[2] = 0;
		for (I64 ip = 0; ip + 1 < prog.length();) {
			switch (prog[ip++]) {
			case 0: r[0] = r[0] >> combo(prog[ip++]); break;
			case 1: r[1] = r[1] ^ prog[ip++]; break;
			case 2: r[1] = combo(prog[ip++]) & 0b111; break;
			case 3: if (r[0] != 0) ip = prog[ip]; break;
			case 4: r[1] = r[1] ^ r[2]; ip++; break;
			case 5: if (out.popFront() != (combo(prog[ip++]) & 0b111)) return false; break;
			case 6: r[1] = r[0] >> combo(prog[ip++]); break;
			case 7: r[2] = r[0] >> combo(prog[ip++]); break;
			}
		}
		return out.length() == 0;
	};
	
	auto solve = [&](this auto&& rec, Span<I64> data, I64 from, I64 cur) -> I64 {
		for (I64 i = 0; i <= 0b111; i++) {    
			I64 v = (cur << 3) | i;
			if (expectWith(data.sub(from), v)) {
				I64 out = (from == 0) ? v : rec(data, from - 1, v);
				if (out != 0) return out;
			}
		}
		return 0;
	};
	Ket::println("{}", solve(prog, prog.length() - 1, 0));
}
