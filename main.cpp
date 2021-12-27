#include <graphics.h>
#include <conio.h>
#include "EasyButton.h"
#include "Node.h"
#include "Point.h"

void On_btnOk_Click()
{
	MessageBox(GetHWnd(),L"Halo", L"Hello", MB_OK);
}

void connectNode(Node& a, Node& b) {
	Point from = a.getBottomPoint();
	Point to = b.getTopPoint();
	line(from.x, from.y, to.x, to.y);
}

EasyButton btnRank;

int main()
{	// set graph size
	int width = 960;
	int height = 540;

	// ��code�ļ������г�ʼ��һ�Ŷ�����
	int date = 0;
	int rank = 0;
	Node* root = new Node(date++, rank++);
	// y axis of root node
	// x axis of root node
	// half of one node height
	// half of one node width
	// interval height of two near level (centra to centra)
	// interval width of two near node in same level (centra to centra) of the leaf level with max depth
	Tree tree = Tree(root, width/2, 50, 20, 30, 55, 75);

	root->left = new Node(date++, rank++);
	root->right = new Node(date++, rank++);
	root->left->left = new Node(date++, rank++);
	root->left->right = new Node(date++, rank++);
	root->right->left = new Node(date++, rank++);
	root->right->right = new Node(date++, rank++);
	//
	

	// ��ʼ����ͼ����
	
	initgraph(width, height);
	// ��ô��ھ��
	HWND hWnd = GetHWnd();
	// ʹ�� Windows API �޸Ĵ�������
	SetWindowText(hWnd, L"Dynamic Tree");

	setbkcolor(0xeeeeee);
	cleardevice();
	settextcolor(BLACK);

	setlinecolor(BLACK);
	line(width * 0.8, 0, width * 0.8, height);
	
	//outtextxy(50, 55, L"�û�����");
	//outtextxy(50, 105, L"�ܡ��룺");*/

	wchar_t tmp[] = L"abc";
	setlinestyle(PS_SOLID, 1);
	//btnRank.Create(100, 100, 200, 200, tmp, On_btnOk_Click);
	/*node.Create(300, 300, 100, 50, 1, 2, tmp ,On_btnOk_Click);
	node2.Create(500, 100, 30, 40, 3, 4, tmp, On_btnOk_Click);
	connectNode(node2, node);*/
	//_getch();
	tree.h = tree.height(tree.node);
	tree.draw();
	// �����ַ������������������û�����
	wchar_t s[10];
	//InputBox(s, 10, L"������뾶");

	// ���û�����ת��Ϊ����
	//int r = _wtoi(s);

	// ��Բ
	//circle(320, 240, r);
	bool binput = true;
	ExMessage msg;
	int fromX = 0, fromY = 0;
	int toX, toY;

	while (binput) {
		while (binput && peekmessage(&msg, EM_MOUSE | EM_CHAR, false)) {
			if (msg.message == WM_LBUTTONDOWN){
				fromX = msg.x; fromY = msg.y;
			}else if (msg.message == WM_LBUTTONUP) {
				toX = msg.x; toY = msg.y;
				outtextxy(fromX, fromY, L"from");
				outtextxy(toX, toY, L"to");
				tree.moveTo(msg.x, msg.y);
				tree.draw();
			}
			peekmessage(NULL, EM_MOUSE | EM_CHAR);
		}
	}
	// ��������˳�
	_getch();

	closegraph();

	return 0;
}