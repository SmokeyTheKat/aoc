#include <ket/all.hpp>

using namespace Ket;

struct Group {
	int pos;
	int size;
	int end(void) { return pos + size; }
};

int main(void) {
	auto subValidate = [](const List<Group>& groups, String& with, int start) {
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

	auto validate = [](const List<Group>& groups, String& with, int start) {
		String s('.', with.length());
		for (Group g : groups) {
			s.fill('#', g.pos, g.pos + g.size);
		}

		for (Size i = start; i < with.length(); i++) {
			if (with[i] != '?' && s[i] != with[i]) return false;
		}

		return true;
	};

	auto calculateArrangements = [&](String& orig, List<int> groupsSizes) {
		List<Group> groups;
		groupsSizes.foldLeft(0, [&](int pos, int size) {
			groups += {pos, size};
			return pos + size + 1;
		});

		int fullLength = orig.length();
		int count = 0;
		if (validate(groups, orig, 0)) count += 1;

		auto rec = [&](List<Group> groups, auto&& rec) -> void {
			int start = groups.first().pos;
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
		.foldLeft(0, [&](auto acc, ParseString line) {
			auto splits = line.split(' ');
			String orig = splits[0].string();
			List<int> groups = splits[1].split(",").map(Pred::PSToInt<int>);
			return acc + calculateArrangements(orig, groups);
		})
	;

	println("{}", sum);
	return 0;
}
