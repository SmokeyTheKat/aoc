Int main(void) {
	String data = Input("input.txt").readAll();
	Array<I64> prog = data.view().split("Program: ")[1].split(',').map(Pred::ToNumber<I64>);
	I64 r[3] = {
		data.view().split("Register A: ")[1].getInt<I64>(),
		data.view().split("Register B: ")[1].getInt<I64>(),
		data.view().split("Register C: ")[1].getInt<I64>()
	};
	
	auto combo = $f1 ($0 >= 4 && $0 <= 6) ? r[$0 - 4] : $0 $;
	
	Array<I64> out;
	for (I64 ip = 0; ip + 1 < prog.length();) {
		switch (prog[ip++]) {
		case 0: r[0] = r[0] >> combo(prog[ip++]); break;
		case 1: r[1] = r[1] ^ prog[ip++]; break;
		case 2: r[1] = combo(prog[ip++]) & 0b111; break;
		case 3: if (r[0] != 0) ip = prog[ip]; break;
		case 4: r[1] = r[1] ^ r[2]; ip++; break;
		case 5: out += combo(prog[ip++]) & 0b111; break;
		case 6: r[1] = r[0] >> combo(prog[ip++]); break;
		case 7: r[2] = r[0] >> combo(prog[ip++]); break;
		}
	}
	Ket::println("{}", out);
}
