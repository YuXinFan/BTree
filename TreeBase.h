#ifndef TREE_BASE_
#define TREE_BASE_

#include "stdc++.h"
using namespace std;
#define ls son[x][0]
#define rs son[x][1]
#define N 1010100
int sz[N], val[N], son[N][2], Rt, cc, dep[N], fa[N];

typedef struct AVL {
	AVL() { dep[0] = -1; }

	void update(int x) {
		sz[x] = sz[ls] + sz[rs] + 1;
		dep[x] = max(dep[ls], dep[rs]) + 1;
	}

	int isson(int x) { return son[fa[x]][1] == x; }

	void rotate(int x) {
		int y = fa[x], z = isson(x);
		fa[x] = fa[y];
		if (fa[y]) son[fa[y]][isson(y)] = x;
		else Rt = x;
		fa[y] = x;
		if (son[x][z ^ 1]) fa[son[x][z ^ 1]] = y;
		son[y][z] = son[x][z ^ 1];
		son[x][z ^ 1] = y;
		update(y);
		update(x);
	}

	void balance(int x) {
		if (dep[ls] - dep[rs] >= 2 || dep[ls] - dep[rs] <= -2) {
			int z = !(dep[ls] - dep[rs] >= 2);
			if (dep[son[son[x][z]][z]] > dep[son[son[x][z]][z ^ 1]]) {
				rotate(son[x][z]);
			}
			else {
				rotate(son[son[x][z]][z ^ 1]);
				rotate(son[x][z]);
			}
		}
	}

	void add(int x, int v) {
		if (v <= val[x]) {
			if (!ls) ls = cc, fa[cc] = x;
			else add(ls, v);
		}
		else {
			if (!rs) rs = cc, fa[cc] = x;
			else add(rs, v);
		}
		update(x);
		balance(x);
	}

	void insert(int v) {//printf("insert %d\n",v);
		val[++cc] = v;
		update(cc);
		if (!Rt) Rt = cc;
		else add(Rt, v);
	}

	int find(int x, int v) {
		if (val[x] == v) return x;
		if (val[x] > v) return find(ls, v);
		else return find(rs, v);
	}

	void remove(int v) {//printf("remove %d\n",v);
		int x = find(Rt, v), y, tmp;
		if (!ls || !rs) {
			y = ls + rs;
			if (y) fa[y] = fa[x];
			if (fa[x]) son[fa[x]][isson(x)] = y;
			else Rt = y;
			x = fa[x];
		}
		else {
			y = ls;
			while (son[y][1]) y = son[y][1];
			son[fa[y]][isson(y)] = son[y][0];
			if (son[y][0]) fa[son[y][0]] = fa[y];
			val[x] = val[y];
			tmp = fa[y];
			fa[y] = 0;
			x = tmp;
		}
		while (x) {//printf("x=%d\n",x);
			update(x);
			balance(x);
			x = fa[x];
		}
	}

	int findkth(int x, int k) {
		if (k <= sz[ls]) return findkth(ls, k);
		if (k == sz[ls] + 1) return val[x];
		return findkth(rs, k - sz[ls] - 1);
	}

	int findrank(int x, int v) {
		if (!x) return 0;
		if (val[x] < v) return findrank(rs, v) + sz[ls] + 1;
		else return findrank(ls, v);
	}

	int kth(int k) { return findkth(Rt, k + 1); }
	int rank(int v) { return findrank(Rt, v); }
	int size() { return sz[Rt]; }

	void test() {}
#undef N
} AVL;
AVL avl;

//struct Node_AVL {
//	int element, rank;
//	Node_AVL* left = NULL;
//	Node_AVL* right = NULL;
//	Node_AVL(int d, int r) {
//		element = d;
//		rank = r;
//	}
//	~Node_AVL();
//};
//
//struct Tree_AVL {
//	Node_AVL* root;
//	Tree_AVL() {
//		root = NULL;
//	}
//
//	void Create(int x, Node_AVL* now) {
//		if (x == Rt) {
//			Node_AVL* node = new Node_AVL(x, dep[x]);
//			root = node;
//			now = root;
//		}
//		// int ls = son[x][0];
//		// int rs = son[x][1];
//		if (ls != 0) {
//			Node_AVL* tmp = new Node_AVL(ls, dep[ls]);
//			now->left = tmp;
//			Create(ls, now->left);
//		}
//		if (rs != 0) {
//			Node_AVL* tmp = new Node_AVL(rs, dep[rs]);
//			now->right = tmp;
//			Create(rs, now->right);
//		}
//	}
//
//	void print_tree(Node_AVL* now) {
//		cout << now->element << " ";
//		if (now->left != NULL) {
//			print_tree(now->left);
//		}
//		if (now->right != NULL) {
//			print_tree(now->right);
//		}
//	}
//};
//
//void tree_print(int x) {
//	cout << x << " ";
//	if (ls != 0) {
//		tree_print(ls);
//	}
//	if (rs != 0) {
//		tree_print(rs);
//	}
//}

/* PLEASE DO NOT CHANGE BELOW*/
int A, B, C, lfsr;
double P[4][4];
int lfsr_generator() {
	auto ret = lfsr;
	return (lfsr ^= lfsr << 13, lfsr ^= lfsr >> 17, lfsr ^= lfsr << 5, ret);
}
tuple<int, int> command() {
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
void DynTreeMain() {
	// 
	extern int P1[5];
	extern float P2[4 * 4];
	extern int tans;

	// clean for multi time use
	for (int i = 0; i < 1010100; i++) {
		sz[i] = 0;
		val[i] = 0;
		son[i][0] = 0;  son[i][1] = 0;
		Rt = 0;
		cc = 0;
		dep[i] = 0;
		fa[i] = 0;
	}
	dep[0] = -1;
	tans = 0;
	

	int m = P1[0]; lfsr = P1[1]; A = P1[2]; B = P1[3]; C = P1[4];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) P[i][j] = P2[i*4+j];
	for (int i = 1; i <= m; i++) {
		int op, imm;
		tie(op, imm) = command();
		if (op == 0) avl.insert(imm);
		if (op == 1) avl.remove(avl.kth(imm % avl.size()));
		if (op == 2) tans ^= avl.rank(imm);
		if (op == 3) tans ^= avl.kth(imm % avl.size());
		/*Tree_AVL node_tree;
		Node_AVL* now;
		node_tree.Create(Rt, now);
		cout << "node tree" << endl;
		node_tree.print_tree(node_tree.root);
		cout << endl << "array tree" << endl;
		tree_print(Rt);
		cout << endl;*/
	}
	//cout << tans << "\n";
}

#endif // !TREE_BASE_
