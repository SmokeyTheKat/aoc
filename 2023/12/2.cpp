#include <ket/all.hpp>
#include <cmath>

using namespace Ket;

struct Group {
	I64 pos;
	I64 size;
	I64 end(void) { return pos + size; }
};

int main(void) {
	println("-1");
	return 0;
	auto subValidate = [](const List<Group>& groups, String& with, I64 start) {
		if (
			(groups.last().end() < with.length() && with[groups.last().end()] == '#') ||
			(groups.first().pos > 0 && with[groups.first().pos - 1] == '#')
		) return false;

		String s('.', with.length());
		for (Group g : groups) {
			s.fill('#', g.pos, g.pos + g.size);
		}

		for (Size i = start; i < groups.last().end(); i++) {
			if (with[i] != '?' && s[i] != with[i]) return false;
		}

		return true;
	};

	auto validate = [](const List<Group>& groups, String& with, I64 start) {
		String s('.', with.length());
		for (Group g : groups) {
			s.fill('#', g.pos, g.pos + g.size);
		}

		for (Size i = start; i < with.length(); i++) {
			if (with[i] != '?' && s[i] != with[i]) return false;
		}

		return true;
	};

	auto calculateArrangements = [&](String& orig, List<I64> groupsSizes) {
		List<Group> groups;
		groupsSizes.foldLeft(0, [&](I64 pos, I64 size) {
			groups += {pos, size};
			return pos + size + 1;
		});

		I64 fullLength = orig.length();
		I64 count = 0;
		if (validate(groups, orig, 0)) count += 1;

		auto rec = [&](List<Group> groups, auto&& rec) -> void {
			I64 start = groups.first().pos;
			while (groups.last().end() < fullLength) {
				if (
					groups.length() > 1 &&
					groups.last().end() < fullLength &&
					subValidate(List<Group>{groups.first()}, orig, start)
				) {
					rec(groups.clone().removeFront(), rec);
				}
				groups.forEach([&](Group& g){ g.pos += 1; });
				if (validate(groups, orig, start)) count += 1;
			}
		};
		rec(groups, rec);

		return count;
	};

	I64 sum =
		Input("input.txt")
		.foldLeftI(0, [&](auto acc, ParseString line, int i) {
			auto splits = line.split(' ');
			String templ = splits[0].string();
			String orig;
			List<I64> groups;
			List<I64> outputs;
			for (I64 i = 0; i < 3; i++) {
				orig += templ;
				orig += '.';
				groups += splits[1].split(",").map(Pred::PSToInt<I64>);
				outputs += calculateArrangements(orig, groups);
				std::fflush(stdout);
				orig.popBack();
			}
//            if (Math::fmod((float)outputs[1], (float)outputs[0]) != 0) {
				print("{: <3}: {: <30}:", i, line.string());
				outputs.forEach([](I64 v){ print("{}, ", v); });
				println("");
//            }
			return acc + 0;
		})
	;

	println("{}", sum);
	return 0;
}
