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

	int width = 0;
	int height = 0;
	int startX = 0;
	int startY = 0;
	{
		int left = 0;
		int right = 0;
		int top = 0;
		int bottom = 0;
		int cx = 0;
		int cy = 0;
		insts.forEach([&](auto inst) {
			switch (inst.dir) {
			case 'U': cy -= inst.count; break;
			case 'D': cy += inst.count; break;
			case 'L': cx -= inst.count; break;
			case 'R': cx += inst.count; break;
			}
			if (cx < left) {
				startX += left - cx;
				left = cx;
			}
			if (cx > right) right = cx;
			if (cy < top) {
				startY += top - cy;
				top = cy;
			}
			if (cy > bottom) bottom = cy;
		});
		width = right - left + 2;
		height = bottom - top + 2;
	}

	List<char> mapList('.', width * height);
	MatrixView<char> map(mapList.data(), width, height, width);

	{
		int x = startX;
		int y = startY;
		insts.forEach([&](auto inst) {
			int nx = x;
			int ny = y;
			switch (inst.dir) {
			case 'U': ny -= inst.count; break;
			case 'D': ny += inst.count; break;
			case 'L': nx -= inst.count; break;
			case 'R': nx += inst.count; break;
			}

			if (x != nx) {
				int xd = (nx - x) / Math::abs(nx - x);
				for (int ix = x; ix - xd != nx; ix += xd) {
					map[y][ix] = '#';
				}
			} else {
				int yd = (ny - y) / Math::abs(ny - y);
				for (int iy = y; iy - yd != ny; iy += yd) {
					map[iy][x] = '#';
				}
			}
			x = nx;
			y = ny;
		});
	}

	int x = 0;
	int y = 0;
	for (int xi = 0; xi < map.height(); xi++) {
		if (map[0][xi] == '#' && map[1][xi] == '.') {
			x = xi;
			y = 1;
			break;
		}
	}

	auto rec = [&](int x, int y, auto&& rec) -> void {
		map[y][x] = '@';
		if (x > 0 && map[y][x-1] == '.') rec(x-1, y, rec); 
		if (y > 0 && map[y-1][x] == '.') rec(x, y-1, rec);
		if (x + 1 < map.width() && map[y][x+1] == '.') rec(x+1, y, rec);
		if (y + 1 < map.height() && map[y+1][x] == '.') rec(x, y+1, rec);
	};
	rec(x, y, rec);

	int count = 0;
	for (int y = 0; y < map.height(); y++) {
		for (int x = 0; x < map.width(); x++) {
			if (map[y][x] != '.') count += 1;
		}
	}

	println("{}", count);

	return 0;
}
