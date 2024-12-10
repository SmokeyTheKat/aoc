#include <ket/all.hpp>

using namespace Ket;

int main(void) {
	int ans =
		Input("2.txt")
		.foldLeft(0, [](int acc, ParseString line) {
			line.popUntilAndSkip(' ');
			int id = line.popUntilAndSkip(':').getInt();
			bool possible = true;
			while (!line.isEmpty()) {
				int val = line.popInt().getInt();
				ParseString color = line.trimFront().popUntilAndSkip({';', ','});;
				if (color == "red") {
					if (val > 12) { possible = false; break; }
				} else if (color == "green") {
					if (val > 13) { possible = false; break; }
				} else if (color == "blue") {
					if (val > 14) { possible = false; break; }
				}
			}
			if (possible) return acc + id;
			else return acc;
		})
	;
	println("{}", ans);
	return 0;
}
