#include <ket/all.hpp>

using namespace Ket;

struct Bag {
	int red=0, green=0, blue=0;
};

int main(void) {
	int ans =
		Input("2.txt")
		.foldLeft(0, [](int acc, ParseString line) {
			line.popUntilAndSkip(':');
			Bag max;
			while (!line.isEmpty()) {
				int val = line.popInt().getInt();
				ParseString color = line.trimFront().popUntilAndSkip({';', ','});
				if (color == "red") {
					if (val > max.red) max.red = val;
				} else if (color == "green") {
					if (val > max.green) max.green = val;
				} else if (color == "blue") {
					if (val > max.blue) max.blue = val;
				}
			}
			return acc + max.red * max.blue * max.green;
		})
	;
	println("{}", ans);
	return 0;
}
