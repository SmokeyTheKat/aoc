#include <ket/all.hpp>

using namespace Ket;

struct Box {
	String id;
	int lens;
};

int main(void) {
	Vector<List<Box>, 256> boxs;
	ParseString(Input("input.txt").readAll())
		.split(',')
		.forEach([&](ParseString s) {
			int id = 0;
			ParseString lable = s.popWord();
			for (char c : lable) id = ((id + c) * 17) % 256;
			if (s[0] == '=') {
				int lens = s[1] - '0';
				if (auto box = boxs[id].find(LAM (&b) EXPR (b.id == lable.string()))) {
					box->lens = lens;
				} else {
					boxs[id].pushBack({lable.string(), lens});
				}
			} else if (s[0] == '-') {
				int find = boxs[id].findIndex(LAM (&b) EXPR (b.id == lable.string()));
				if (find >= 0) boxs[id].removeAt(find);
			}
		})
	;
	int ans =
		boxs.foldLeftI(0, LAM (acc, &b, i) {
			return b.foldLeftI(acc, LAM (acc, &l, j) EXPR (acc + (i + 1) * (j + 1) * l.lens));
		})
	;
	println("{}", ans);
	return 0;
}
