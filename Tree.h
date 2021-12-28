#pragma once
//#include "TreeBase.h"
#include "Node.h"
extern int son[1010100][2];
extern int dep[1010100];
extern int Rt;
//extern AVL avl;
void Create(Node* t, int x) {
	int l = son[x][0];
	int r = son[x][1];
	if (l != 0) {
		t->left = new Node(l, dep[l]);
		Create(t->left, l);
	}
	if (r != 0) {
		t->right = new Node(r, dep[r]);
		Create(t->right, r);
	}
}

Tree *Base2GUI() {
	// crete root
	//avl.rank()
	Node* root = new Node(Rt, dep[Rt]);
	
	Create(root, Rt);
	Tree* t = new Tree(root, WIDTH / 2, 50, 20, 30, 55, 75);
	return t;
}

void DeleteNode(Node* n) {
	if (n != NULL) {
		DeleteNode(n->left);
		DeleteNode(n->right);
		delete n;
	}
}

void DeleteTree(Tree *t){
	if (t->node != NULL) {
		DeleteNode(t->node);
	}
	delete t;
}

//void Create(int x, Node_AVL* now) {
//	if (x == Rt) {
//		Node_AVL* node = new Node_AVL(x, dep[x]);
//		root = node;
//		now = root;
//	}
//	// int ls = son[x][0];
//	// int rs = son[x][1];
//	if (ls != 0) {
//		Node_AVL* tmp = new Node_AVL(ls, dep[ls]);
//		now->left = tmp;
//		Create(ls, now->left);
//	}
//	if (rs != 0) {
//		Node_AVL* tmp = new Node_AVL(rs, dep[rs]);
//		now->right = tmp;
//		Create(rs, now->right);
//	}
//}