#pragma once
#include <graphics.h>
#include <conio.h>
#include "Point.h"
#include <cmath>
// ���ڵ㣺����
class Node
{
private:
	int date;
	int rank; // rank
public:
	Node* left = NULL;
	Node* right = NULL;

private:
	int centerX = 0;
	int centerY = 0;
	int halfW = 0;
	int halfH = 0;
	wchar_t* text = NULL;							// �ؼ�����
	void (*userfunc)() = NULL;						// �ؼ���Ϣ

public:
	Node(int d, int r) {
		date = d;
		rank = r;
		left = NULL;
		right = NULL;
	}

	~Node()
	{
		if (text != NULL)
			delete[] text;
	}

	void Create(int x, int y, int w, int h, wchar_t* title, void (*func)())
	{
		text = new wchar_t[wcslen(title) + 1];
		wcscpy_s(text, wcslen(title) + 1, title);
		centerX = x; centerY = y; halfH = h; halfW = w;
		userfunc = func;
		// �����û�����
		Show();
	}


	// ���ƽ���
	void Show()
	{
		int oldlinecolor = getlinecolor();
		int oldbkcolor = getbkcolor();
		int oldfillcolor = getfillcolor();

		setlinecolor(BLACK);			// ���û�����ɫ
		setbkcolor(LIGHTGRAY);				// ���ñ�����ɫ
		setfillcolor(LIGHTGRAY);			// ���������ɫ


		fillrectangle(centerX-halfW, centerY+halfH, centerX+halfW, centerY - halfH);
		line(centerX - halfW, centerY, centerX + halfW, centerY);
		line(centerX, centerY, centerX, centerY+halfH);

		wchar_t val_str[256];
		swprintf_s(val_str, L"%d", date);
		outtextxy(centerX-halfW + (2 * halfW - textwidth(val_str) + 1) / 2, centerY - halfH + (halfH - textheight(val_str) + 1) / 2, val_str);

		wchar_t rank_str[256];
		swprintf_s(rank_str, L"%d", rank);
		outtextxy(centerX-halfW + (halfW - textwidth(rank_str) + 1) / 2, centerY + (halfH - textheight(rank_str) + 1) / 2, rank_str);

		outtextxy(centerX + (halfW - textwidth(text) + 1) / 2, centerY + (halfH - textheight(text) + 1) / 2, text);


		setlinecolor(oldlinecolor);
		setbkcolor(oldbkcolor);
		setfillcolor(oldfillcolor);
	}

	Point getTopPoint() {
		return Point{ centerX, centerY - halfH };
	}
	Point getBottomPoint() {
		return Point{ centerX, centerY + halfH };
	}
	
	void OnMessage()
	{
		if (userfunc != NULL)
			userfunc();
	}
};

class Tree
{	
public:
	Node* node;
	int rootX;
	int rootY;

	int nodeH;
	int nodeW;

	int intervalH;
	int intervalW;

	wchar_t info[4]= L"ABC";

	int h; // height/depth start from 1

public:
	Tree(Node *n, int x, int y, int H, int W, int interH, int interW) {
		node = n;
		rootX = x;
		rootY = y;
		nodeH = H;
		nodeW = W;
		intervalH = interH;
		intervalW = interW;
		
	}

	int height(Node* node)
	{
		if (node == NULL)
			return 0;
		else {
			/* compute the height of each subtree */
			int lheight = height(node->left);
			int rheight = height(node->right);

			/* use the larger one */
			if (lheight > rheight) {
				return (lheight + 1);
			}
			else {
				return (rheight + 1);
			}
		}
	}
	void draw() {
		clearrectangle(
			0,
			0,
			960*0.8-1,
			540
		);
		BeginBatchDraw();
		drawInorder(node, 1, 1);
		EndBatchDraw();
	}
	void drawInorder(Node *cur, int height, int nth)
	{
		if (cur == NULL)
			return;

		/* first recur on left child */
		drawInorder(cur->left, height + 1, nth * 2 );

		/* then print the data of node */
		int Y = rootY + (height - 1) * intervalH;
		// balance
		int num_interval = pow(2, (height - 1)) - 1;
		int interval_width = intervalW * pow(2, h - height);
		int total_width = num_interval * interval_width;
		int nth_interval = nth - pow(2, height - 1);
		int X = rootX - total_width / 2 + nth_interval * interval_width;
		cur->Create(X,Y,nodeW, nodeH, info, NULL);
		cur->Show();

		if (cur->left) {
			Point from = cur->getBottomPoint();
			Point to = cur->left->getTopPoint();
			line(from.x, from.y, to.x, to.y);
		}
		/* now recur on right child */
		drawInorder(cur->right, height + 1, nth * 2 + 1);
		
		if (cur->right) {
			Point from = cur->getBottomPoint();
			Point to = cur->right->getTopPoint();
			line(from.x, from.y, to.x, to.y);
		}
	}

	void moveTo(int x, int y) {
		rootX = x;
		rootY = y;
	}
};