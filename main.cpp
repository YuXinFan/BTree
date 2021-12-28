#include <graphics.h>
#include <conio.h>
#include "EasyButton.h"
#include "Node.h"
#include "Point.h"

void On_btnOk_Click()
{
	MessageBox(GetHWnd(),L"Halo", L"Hello", MB_OK);
}

void On_btnInsert_Click() {
	MessageBox(GetHWnd(), L"Halo", L"Hello", MB_OK);
}

void On_btnDelete_Click() {
	MessageBox(GetHWnd(), L"Halo", L"Hello", MB_OK);
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
	int tans = 0;
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
	// ��ʼ���� ����ɫ, ������ɫ
	setbkcolor(0xeeeeee);
	cleardevice();
	settextcolor(BLACK);

	// draw show window contains tan value, insert button, delete button with text style Consolas
	settextstyle(16, 0, _T("Consolas"));
	EasyButton insertButton;
	EasyButton deleteButton;
	int showWindowW = 160;
	int showWindowH = 90;
	// draw the windon with color 0xB0C4DE
	setfillcolor(0xB0C4DE);
	fillrectangle(width - showWindowW, 0, width, showWindowH);
	// draw insert button 
	wchar_t insert_text[7] = L"INSERT";
	insertButton.Create(width - showWindowW * 0.9, showWindowH / 2 * 1.1, width - showWindowW / 2 * 1.1, showWindowH * 0.9, insert_text, On_btnInsert_Click);
	// draw delete button
	wchar_t delete_text[7] = L"DELETE";
	insertButton.Create(width - showWindowW / 2 * 0.9, showWindowH / 2 * 1.1, width - showWindowW * 0.1, showWindowH * 0.9, delete_text, On_btnDelete_Click);
	// draw tan value
	wchar_t tans_text[256];
	swprintf_s(tans_text, L"tans: %d", tans);
	RECT r = { width - showWindowW , 0, width - 1, showWindowH/2 -1 };
	drawtext(tans_text, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// �����߶ο�Ⱥ���ɫ
	wchar_t tmp[] = L"abc";
	setlinestyle(PS_SOLID, 1);
	setlinecolor(BLACK);
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

	ExMessage msg;
	while (true)
	{
		msg = getmessage(EM_MOUSE);			// ��ȡ��Ϣ����

		if (msg.message == WM_LBUTTONDOWN)
		{
			// �жϿؼ�
			if (txtName.Check(msg.x, msg.y))	txtName.OnMessage();

			// �жϿؼ�
			if (txtPwd.Check(msg.x, msg.y))		txtPwd.OnMessage();

			// �жϿؼ�
			if (btnOK.Check(msg.x, msg.y))		btnOK.OnMessage();
		}
	}
	// ��������˳�
	_getch();

	closegraph();

	return 0;
}