#include "stdc++.h"
using namespace std;
struct DynTree {
#define N 1010100
#define ls son[x][0]
#define rs son[x][1]
	// size of each node indexed by index, 
	// val of each node, using index from 1 to n 
	// son of each node, using index same to val[]
	// rotation factor
	// cc 
	// depth of each node
	// father of each node
	int sz[N], val[N], son[N][2], Rt, cc, dep[N], fa[N];
	DynTree() { dep[0] = -1; }
	void update(int x)
	{
		sz[x] = sz[ls] + sz[rs] + 1;
		dep[x] = max(dep[ls], dep[rs]) + 1;
	}
	int isson(int x) { return son[fa[x]][1] == x; }
	void rotate(int x)
	{
		int y = fa[x], z = isson(x);
		fa[x] = fa[y];
		if (fa[y]) son[fa[y]][isson(y)] = x;
		else Rt = x;
		fa[y] = x;
		if (son[x][z ^ 1]) fa[son[x][z ^ 1]] = y;
		son[y][z] = son[x][z ^ 1];
		son[x][z ^ 1] = y;
		update(y); update(x);
	}
	void balance(int x)
	{
		if (dep[ls] - dep[rs] >= 2 || dep[ls] - dep[rs] <= -2)
		{
			int z = !(dep[ls] - dep[rs] >= 2);
			if (dep[son[son[x][z]][z]] > dep[son[son[x][z]][z ^ 1]])
			{
				rotate(son[x][z]);
			}
			else
			{
				rotate(son[son[x][z]][z ^ 1]);
				rotate(son[x][z]);
			}
		}
	}
	void add(int x, int v)
	{
		if (v <= val[x]) // add to left children tree of node x
		{
			if (!ls) ls = cc, fa[cc] = x;
			else add(ls, v);
		}
		else  // add to left children tree of node x
		{
			if (!rs) rs = cc, fa[cc] = x;
			else add(rs, v);
		}
		update(x);
		balance(x);
	}
	void insert(int v)
	{//printf("insert %d\n",v);
		val[++cc] = v; // node count + 1
		update(cc); // update size and depth of cc-th node
		if (!Rt) Rt = cc; // 
		else add(Rt, v);
	}
	int find(int x, int v)
	{
		if (val[x] == v) return x;
		if (val[x] > v) return find(ls, v);
		else return find(rs, v);
	}
	void remove(int v)
	{//printf("remove %d\n",v);
		int x = find(Rt, v), y, tmp;
		if (!ls || !rs)
		{
			y = ls + rs;
			if (y) fa[y] = fa[x];
			if (fa[x]) son[fa[x]][isson(x)] = y;
			else Rt = y;
			x = fa[x];
		}
		else
		{
			y = ls;
			while (son[y][1]) y = son[y][1];
			son[fa[y]][isson(y)] = son[y][0];
			if (son[y][0]) fa[son[y][0]] = fa[y];
			val[x] = val[y];
			tmp = fa[y];
			fa[y] = 0;
			x = tmp;
		}
		while (x)
		{//printf("x=%d\n",x);
			update(x);
			balance(x);
			x = fa[x];
		}
	}
	int findkth(int x, int k)
	{
		if (k <= sz[ls]) return findkth(ls, k);
		if (k == sz[ls] + 1) return val[x];
		return findkth(rs, k - sz[ls] - 1);
	}
	int findrank(int x, int v)
	{
		if (!x) return 0;
		if (val[x] < v) return findrank(rs, v) + sz[ls] + 1;
		else return findrank(ls, v);
	}
	int kth(int k) { return findkth(Rt, k + 1); }
	int rank(int v) { return findrank(Rt, v); }
	int size() { return sz[Rt]; }

	void test() {}
#undef N
};
DynTree tree;



/* PLEASE DO NOT CHANGE BELOW*/
int A, B, C, lfsr;
double P[4][4];
int lfsr_generator() {
	auto ret = lfsr;
	return (lfsr ^= lfsr << 13, lfsr ^= lfsr >> 17, lfsr ^= lfsr << 5, ret);
}
std::tuple<int, int> command() {
	auto imm = lfsr_generator();
	static int state = 0;
	auto p = double(lfsr_generator() & 0x7fffffff) / INT32_MAX;
	for (int i = 0; i < 4; i++)
		if ((p -= P[state % 4][i]) < 0) {
			state += 4 - state % 4 + i;
			break;
		}
	return tuple<int, int>(state % 4, (imm * A + state * B + C) & 0x7fffffff);
}
/* PLEASE DO NOT CHANGE ABOVE*/
//int main() {
//	// tree.test();return 0;
//	int m;
//
//	cin >> m >> lfsr >> A >> B >> C;
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 4; j++) cin >> P[i][j];
//	int tans = 0;
//	for (int i = 1; i <= m; i++) {
//		int op, imm;
//		tie(op, imm) = command();
//		if (op == 0) tree.insert(imm);
//		if (op == 1) tree.remove(tree.kth(imm % tree.size()));
//		if (op == 2) tans ^= tree.rank(imm);
//		if (op == 3) tans ^= tree.kth(imm % tree.size());
//	}
//	cout << tans << "\n";
//}

