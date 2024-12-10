#include <ket/all.hpp>

using namespace Ket;

struct Instruction {
	char dir;
	int count;
};

int main(void) {
	List<Instruction> insts =
		Input("input.txt")
		.foldLeft(List<Instruction>(), [&](auto list, ParseString line) {
			list += {line[0], line.split(' ')[1].getInt<int>()};
			return list;
		})
	;

	return 0;
}
