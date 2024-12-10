#include <ket/all.hpp>

using namespace Ket;

struct Pos {
	int x, y;
	Pos n(int c = 1) { return Pos{x+0,y-c}; };
	Pos s(int c = 1) { return Pos{x+0,y+c}; };
	Pos e(int c = 1) { return Pos{x+c,y+0}; };
	Pos w(int c = 1) { return Pos{x-c,y+0}; };
	bool operator==(const Pos& o) const {
		return x == o.x && y == o.y;
	};
};
namespace Dir {
	enum { N=0, S, E, W };
	int oppisite(int dir) {
		switch (dir) {
			case N: return S;
			case S: return N;
			case E: return W;
			case W: return E;
		}
		return N;
	}
};

constexpr int maxStepCount = 3;

int main(void) {
	List<String> map = Input("input.txt").foldLeft(List<String>(), Pred::Append);
	int width = map[0].length();
	int height = map.length();
	int count = width * height;

	auto getValueWalkN = [&](Pos p, int c) {
		int v = 0;
		for (int i = 0; i < c; i++) {
			p.y -= 1;
			v += map[p.y][p.x] - '0';
		}
		return v;
	};

	auto getValueWalkS = [&](Pos p, int c) {
		int v = 0;
		for (int i = 0; i < c; i++) {
			p.y += 1;
			v += map[p.y][p.x] - '0';
		}
		return v;
	};

	auto getValueWalkE = [&](Pos p, int c) {
		int v = 0;
		for (int i = 0; i < c; i++) {
			p.x += 1;
			v += map[p.y][p.x] - '0';
		}
		return v;
	};

	auto getValueWalkW = [&](Pos p, int c) {
		int v = 0;
		for (int i = 0; i < c; i++) {
			p.x -= 1;
			v += map[p.y][p.x] - '0';
		}
		return v;
	};

	auto getValueWalk = [&](Pos p, int c, int dir) {
		switch (dir) {
		case Dir::N: return getValueWalkN(p, c);
		case Dir::S: return getValueWalkS(p, c);
		case Dir::E: return getValueWalkE(p, c);
		case Dir::W: return getValueWalkW(p, c);
		}
		return 0;
	};

	auto posToId = [&](Pos p) -> int { return map.length() * p.y + p.x; };

	auto idToPos = [&](int id) -> Pos {
		return {
			id % (int)map[0].length(),
			(id / (int)map[0].length()) % count
		};
	};

	auto stateToId = [&](int id, int dir, int steps) {
		return (
			dir * (maxStepCount + 1) * count +
			steps * count +
			id
		);
	};

	struct Node {
		int id;
		int dir;
		int steps;
		int cost;
	};

	auto stateFromId = [&](int id) {
		return Node{
			id % count,
			(id / count) % (maxStepCount + 1),
			id / ((maxStepCount + 1) * count)
		};
	};

	Map<int, List<Node>> graph;

	for (int steps = 0; steps <= maxStepCount; steps++) {
		for (int dir = Dir::N; dir <= Dir::W; dir++) {
			Iter::loop2DI(map, [&](char c, int x, int y) {
				Pos p{x, y};
				List<Node> nbs;
				for (int d = Dir::N; d <= Dir::W; d++) {
					int i = 1;
					if (d == dir) i = steps + 1;

					if (d == Dir::oppisite(dir) && steps > 0) continue;

					if (d == Dir::N) {
						for (int j = 1; i <= maxStepCount; i++, j++) {
							if (y - j >= 0) nbs += Node{posToId(p.n(j)), d, i, getValueWalkN(p, j)};
						}
					} else if (d == Dir::S) {
						for (int j = 1; i <= maxStepCount; i++, j++) {
							if (y + j < height) nbs += Node{posToId(p.s(j)), d, i, getValueWalkS(p, j)};
						}
					} else if (d == Dir::W) {
						for (int j = 1; i <= maxStepCount; i++, j++) {
							if (x - j >= 0) nbs += Node{posToId(p.w(j)), d, i, getValueWalkW(p, j)};
						}
					} else if (d == Dir::E) {
						for (int j = 1; i <= maxStepCount; i++, j++) {
							if (x + j < width) nbs += Node{posToId(p.e(j)), d, i, getValueWalkE(p, j)};
						}
					}
				}
				graph.add(stateToId(posToId(p), dir, steps), nbs);
			});
		}
	}

	List<int> dist(graph.length(), LAM (i) EXPR (NumberInfo<int>::max));
	List<int> prevs(graph.length(), LAM (i) EXPR (-1));
	dist[0] = 0;
	List<bool> visited(graph.length(), LAM (i) EXPR (false));

	for (int j = 0; j < graph.length(); j++) {
		int u = -1;
		for (int i = 0; i < graph.length(); i++) {
			if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
				u = i;
			}
		}
		if (dist[u] == NumberInfo<int>::max) break;

		visited[u] = true;

		for (Node n : *graph[u]) {
			int v = stateToId(n.id, n.dir, n.steps);
			if (dist[u] + n.cost < dist[v]) {
				dist[v] = dist[u] + n.cost;
				prevs[v] = u;
			}
		}
	}

	int end =
		dist
		.mapI(LAM (cost, id) EXPR (Pair<int, int>{(int)id, (int)cost}))
		.filter(LAM (p) EXPR (idToPos(stateFromId(p.a).id) == Pos{width-1, height-1}))
		.min(LAM (a, b) EXPR (a.b < b.b))
		.map(-1, LAM (p) EXPR (p.a))
	;

	println("{}", dist[end]);

	return 0;
}
