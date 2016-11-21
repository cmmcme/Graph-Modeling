#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
int n, m;
typedef struct VertexList	//�� ������ ����Ű�� �ִ� Vertex �������� ����ü�� �����Ѵ�.
{
	VertexList* next;	//���� �������� ����Ŵ
	struct Vertex* MyVer;	//������ ����Ų��.

	VertexList() : next(NULL), MyVer(NULL) {};	//�� ���� �ʱ�ȭ�Ѵ�.
} VertexList;

typedef struct Vertex	//������ ����ü
{
	int num;	//�й�
	string Email;	//�̸���
	int dev;	//����
	struct ConEdge *Con;	//����Ǿ��ִ� ������ ������
	Vertex() : num(0), dev(0), Con(NULL) {};	//�ʱ�ȭ���ش�

}Vertex;

typedef struct ConEdge	//������ ����� ������ ������
{
	ConEdge* next;	//���� ���� ������
	struct Edge *MyEd;	//������ ��ġ
	ConEdge() : next(NULL), MyEd(NULL) {};	//�ʱ�ȭ �����ش�.
} ConEdge;

typedef struct EdgeList	//�׷������� ������ ������
{
	EdgeList* next;	//���� ����
	struct Edge *SelfEd;	//������ �ִ� ������ ��ġ
	EdgeList() : next(NULL), SelfEd(NULL) {};	//�ʱ�ȭ

} EdgeList;

typedef struct Edge
{
	int StreetNum;	//���� ��ȣ
	ConEdge* ConEd1;	//���� ������ ����� ���� ������
	ConEdge* ConEd2;	//�ݴ��� ������ ����� ���� ������
	EdgeList* MyOrder;	//���� ����Ʈ���� ���� ��ġ
	Vertex *Ver1;	//���� ������ ��ġ
	Vertex *Ver2;	//�ݴ��� ������ ��ġ
	Edge() : StreetNum(0), ConEd1(NULL), ConEd2(NULL), MyOrder(NULL), Ver1(NULL), Ver2(NULL) {}; //�� ���� �ʱ�ȭ�Ѵ�.
}Edge;

typedef struct Graph	//�׷��� ����ü
{
	EdgeList* EDList;	//���� ����Ʈ ������
	VertexList* VerList;	//���ؽ� ������
	Graph() : EDList(NULL), VerList(NULL) {};	//�ʱ�ȭ����

}Graph;

Graph *Gra;

void AddFileVertex(int num, string Email)
{
	VertexList* newVList = new VertexList;	//���ؽ� ����Ʈ�� ���� �� ���ο� ��带 �����
	Vertex* newV = new Vertex;				//���ο� ���ؽ� ��带 �����
	newV->num = num;						//�� ���� �����Ѵ�.
	newV->Email = Email;
	newVList->MyVer = newV;			//���θ��� ���ؽ� ����Ʈ�� ������ ������ newV(���θ��� Vertex)�̴�.

	VertexList* NOW = Gra->VerList;	//�׷����� �ִ� ���ؽ� ����Ʈ���� ������ ���� ã�´�. ù ���� ����Ʈ�� ����.
	if (NOW == NULL)	//���� ó���� ������ִٸ�
		Gra->VerList = newVList;		//�ٷ� ����

	else {			//����� ���� �ʴٸ�,
		while (NOW->next != NULL)	//����Ʈ�� ������ �� �� ���� �ݺ����� ������.
			NOW = NOW->next;

		NOW->next = newVList;	//�ݺ����� Ż���ϸ� ����Ʈ�� ������ ���ο� ���ؽ� ����Ʈ ��带 �����Ѵ�.
	}

}
void AddVertex(int num, string Email)
{
	AddFileVertex(num, Email);	//������ ������ �Լ��� �����Ͽ� ������ �����Ѵ�.
	n++;						//�� ������ ������ ���� �� ����Ѵ�.
	cout << n << endl;
}
Vertex* SearchVertex(int num)			//������ ��ġ�� ã�� ��ȯ���ִ� �Լ�
{
	VertexList *SearchNow = Gra->VerList;	//�׷����� ��������Ʈ�������� ó������ ���캻��.

	while (1)
	{
		if (SearchNow == NULL)	//���� ��� �������� �� ���Ҵµ� ���ٸ� �ݺ����� Ż���Ѵ�.
			break;
		if (SearchNow->MyVer->num == num)	//�ش� �й��� ���� ������ ��ġ�� ã�Ҵٸ� �ݺ����� Ż���Ѵ�.
			break;

		else
			SearchNow = SearchNow->next;		//�� �� ������ �������� ���ߴٸ� ���� ��������Ʈ�� ����.
	}
	if (SearchNow != NULL)	//������ ã�Ҵٸ� �� ��ġ�� ��ȯ�Ѵ�.
		return SearchNow->MyVer;
	else
		return NULL;	//ã�� ���Ͽ��ٸ� �� NULL���� ��ȯ�Ѵ�.
}

void AddFileEdge(int StreetNum, int n1, int n2)
{													//���� ����
	EdgeList *newEdList = new EdgeList;				//���ο� ���� ����Ʈ�� ������ش�
	Edge *newEdge = new Edge;						//���ο� ������ ������ش�.
	newEdge->StreetNum = StreetNum;					//�ش� ���ι�ȣ�� �־��ش�.
	Vertex *ver1 = SearchVertex(n1);				//n1,n2�� ������ �ִ� ���ؽ��� ã�´�.
	Vertex *ver2 = SearchVertex(n2);
	if (ver1 == NULL || ver2 == NULL)
		return;										//�� �� �ϳ��� ã�� �� ���ٸ� �Լ��� ����

	newEdge->Ver1 = ver1;							//�Ѵ� ã�Ҵٸ� ���ο� ������ ����Ű�� �� �� ������ �����Ѵ�.
	newEdge->Ver2 = ver2;

	ConEdge* newCon1 = ver1->Con;					//�� ������ ����� ���� �������� ���󰡸� �� ������ ���ο� ���� �������� ������ְ� �����Ѵ�.
	if (newCon1 == NULL)							//���� ���� �������� ����ִٸ�
	{
		ConEdge* newOne = new ConEdge;			//���ο� ���� �������� ����
		ver1->Con = newOne;						//ó�� ���� �������� ����
		newOne->MyEd = newEdge;					//���ο� ������ ��ġ�� �ڱⰡ ������ �ִ� ������ ��ġ ������ ����
		newEdge->ConEd1 = newOne;				//���� ���� ������ �ִ� ������������ ��ġ�� ����
	}
	else
	{										//���� �������� ������� �ʴٸ�
		while (newCon1->next != NULL)		//���� ���� �������� �������� �ݺ����� �����Ѵ�.
			newCon1 = newCon1->next;
		ConEdge* newOne = new ConEdge;		//����ִ� ��ġ�� ������ ���ο� ���� ������ ��带 ���� ��,
		newCon1->next = newOne;				//����
		newOne->MyEd = newEdge;				//���ο� ������ ��ġ�� �ڱⰡ ������ �ִ� ������ ��ġ ������ ����
		newEdge->ConEd1 = newOne;			//���� ���� ������ �ִ� ������������ ��ġ�� ����
	}

	ConEdge* newCon2 = ver2->Con;			//���� ������ �ݺ��Ѵ�.
	if (ver2->Con == NULL)
	{
		ConEdge* newTwo = new ConEdge;
		ver2->Con = newTwo;
		newTwo->MyEd = newEdge;
		newEdge->ConEd2 = newTwo;
	}
	else
	{
		while (newCon2->next != NULL)
			newCon2 = newCon2->next;

		ConEdge* newTwo = new ConEdge;
		newCon2->next = newTwo;
		newTwo->MyEd = newEdge;
		newEdge->ConEd2 = newTwo;
	}
	//�׷����� ���� ����Ʈ�� �����ϴ� ����
	if (Gra->EDList == NULL)	{			//�׷����� ��������Ʈ�� ������ִٸ�
		Gra->EDList = newEdList;			//���ο� ���� ����Ʈ ���� ���� ����
		newEdList->SelfEd = newEdge;		//�װ��� ����Ű�� �ִ� ������ ���� ���� ������
	}
	else
	{												//������� �ʴٸ�
		EdgeList* NowEdgeList = Gra->EDList;
		while (NowEdgeList->next != NULL)		//���� ���� ����Ʈ�� �������� �ݺ����� �����Ѵ�.
			NowEdgeList = NowEdgeList->next;

		NowEdgeList->next = newEdList;	//�ݺ����� ���� ������ ���� ��ġ�� ���� ����Ʈ�� ���� �ϰ�,
		newEdList->SelfEd = newEdge;		//���� ����Ʈ�� ������ġ�� ���ο� ������ �����Ѵ�.
	}
	ver1->dev++;		//�� ������ �P�� �� �� �� ������ ������ 1�� ������Ų��.
	ver2->dev++;
}
void AddEdge(int StreetNum, int n1, int n2)		//�� AddFileEdge �Լ��� ������ ����.
{
	EdgeList *newEdList = new EdgeList;
	Edge *newEdge = new Edge;
	newEdge->StreetNum = StreetNum;
	Vertex *ver1 = SearchVertex(n1);
	Vertex *ver2 = SearchVertex(n2);
	if (ver1 == NULL || ver2 == NULL) {			//�� �� �ϳ��� ã�� ���Ͽ��ٸ�
		cout << m << " Not found" << endl;		//�� ������ ����, Not found�� ��� �� �� �Լ��� �����Ѵ�.
		return;
	}
	newEdge->Ver1 = ver1;
	newEdge->Ver2 = ver2;

	ConEdge* newCon1 = ver1->Con;
	if (newCon1 == NULL)
	{
		ConEdge* newOne = new ConEdge;
		ver1->Con = newOne;
		newOne->MyEd = newEdge;
		newEdge->ConEd1 = newOne;
	}
	else
	{
		while (newCon1->next != NULL)
			newCon1 = newCon1->next;
		ConEdge* newOne = new ConEdge;
		newCon1->next = newOne;
		newOne->MyEd = newEdge;
		newEdge->ConEd1 = newOne;
	}

	ConEdge* newCon2 = ver2->Con;
	if (ver2->Con == NULL)
	{
		ConEdge* newTwo = new ConEdge;
		ver2->Con = newTwo;
		newTwo->MyEd = newEdge;
		newEdge->ConEd2 = newTwo;
	}
	else
	{
		while (newCon2->next != NULL)
			newCon2 = newCon2->next;

		ConEdge* newTwo = new ConEdge;
		newCon2->next = newTwo;
		newTwo->MyEd = newEdge;
		newEdge->ConEd2 = newTwo;
	}

	if (Gra->EDList == NULL)	{
		Gra->EDList = newEdList;
		newEdList->SelfEd = newEdge;
	}
	else
	{
		EdgeList* NowEdgeList = Gra->EDList;
		while (NowEdgeList->next != NULL)
			NowEdgeList = NowEdgeList->next;

		NowEdgeList->next = newEdList;
		newEdList->SelfEd = newEdge;
	}
	ver1->dev++;
	ver2->dev++;

	m++;					//�� ������ ������ 1�� ������Ų��.
	cout << m << endl;		//�� ������ ������ ����Ѵ�.

}

Edge* SearchEdge(int StreetNum)	//�ش� ���ι�ȣ�� ������ �ִ� ������ ��ġ�� ��ȯ�ϴ� �Լ�
{
	EdgeList *nowList = Gra->EDList;
	//�׷����� ù ��������Ʈ�� ��

	while (1) {
		if (nowList == NULL)	//���� ������ִٸ� �ݺ����� Ż��
			break;

		if (nowList->SelfEd->StreetNum == StreetNum)	//�� ����Ʈ�� ������ �ִ� ������ ���ι�ȣ�� �Է¹��� ���ι�ȣ�� ���ٸ� �ݺ��� Ż��
			break;

		else
			nowList = nowList->next;		//�Ѵ� �ش����� ���� ��� ���� ��������Ʈ�� ����.

	}
	if (nowList != NULL)	//������ ��ġ�� ã�Ҵٸ� �� ������ ��ġ�� ��ȯ���ش�
		return nowList->SelfEd;
	else
		return NULL;		//ã�� ���Ͽ��ٸ� NULL���� ��ȯ�Ѵ�.
}
void printVer(int num)		//�ش� �й��� ������ ����Ѵ�.
{
	Vertex* PrintNow = SearchVertex(num);	//SearchVertex�� ���� �ش� ������ ��ġ�� ã�´�.
	if (PrintNow == NULL)					//ã�� ���ϸ� Not found ���
		cout << "Not found" << endl;
	else
		cout << PrintNow->Email << " " << PrintNow->dev << endl;	//ã�Ҵٸ� �̸��ϰ� ������ ����Ѵ�.

}
void printEd1(int StreetNum)	//�ش� ���ι�ȣ�� ���� ���
{
	Edge *Search = SearchEdge(StreetNum);	//�ش� ���ι�ȣ�� �������ִ� ������ ��ġ�� ã��
	if (Search == NULL)						//ã�� ���ߴٸ� Not found ���
		cout << "Not found" << endl;
	else
	{										//ã�Ҵٸ� �� �� ������ ������ �ִ� �й� �� �� ���� �� ������� ����Ѵ�.
		if (Search->Ver1->num < Search->Ver2->num)
			cout << Search->Ver1->num << " " << Search->Ver2->num << endl;
		else
			cout << Search->Ver2->num << " " << Search->Ver1->num << endl;
	}
}
void printEd2(int StreetNum, int num)	//�ش� �й���ġ���� ���ι�ȣ ��ġ�� �� �� �ִ��� Ȯ��
{
	Vertex* SerVE = SearchVertex(num);	//�ش� �й��� ��ġ�� ã��
	Edge* SerEd = SearchEdge(StreetNum);	//���� ��ȣ�� ��ġ�� ã��
	if (SerVE == NULL || SerEd == NULL)			//�� �� �ϳ��� �߰����� ���ϸ� Not available ���
		cout << "Not available" << endl;
	else
	{												//�Ѵ� ã�Ҵٸ�
		if (SerEd->Ver1->num == num)				//������ ���� �� ������ �й��� �ش� �й��� ���ٸ�
			cout << SerEd->Ver2->num << endl;		//num�� �ݴ��� ��ġ�� ������ �й� ���

		else if (SerEd->Ver2->num == num)			//������ ���� �� ������ �й��� �ش� �й��� ���ٸ�
			cout << SerEd->Ver1->num << endl;		//num�� �ݴ��� ��ġ�� ������ �й� ���
		else
			cout << "Not available" << endl;		//�� �� ��� �ٸ��ٸ� Not available ���
	}

}

void printAllEd(int num)		//�ش� �й��� ������ �ִ� ������ ����� ��� ���� ���
{
	Vertex *PrintVer = SearchVertex(num);	//�й��� ��ġ�� ã��
	if (PrintVer == NULL)					//�й��� �������� �ʴ´ٸ� Not found ���
		cout << "Not found" << endl;

	else {
		cout << PrintVer->dev << " ";		//������ ���� ���
		ConEdge* PrintCon = PrintVer->Con;	//�ش� ������ ���� ������ ����Ʈ�� ����.
		while (PrintCon != NULL)	//����Ʈ�� ������ ����, 
		{
			cout << PrintCon->MyEd->StreetNum << " ";	//���� ��ȣ�� ����Ѵ�.

			PrintCon = PrintCon->next;	//���� ����Ʈ�� �ű�
		}

		cout << endl;

	}
}
void IsAdjacency(int n1, int n2)	//�� ������ ���� ������ �ִ��� Ȯ��
{
	Vertex* V1 = SearchVertex(n1);
	Vertex* V2 = SearchVertex(n2);		//�� ������ ��ġ�� ã��
	if (V1 == NULL || V2 == NULL)
	{
		cout << "Not found" << endl;
		return;
	}
	if (V1->dev == 0 || V2->dev == 0)
	{
		cout << "Not found" << endl;
		return;
	}
	if (V1->dev < V2->dev)				//�� ������ ������ ���� �������� �Լ� ����
	{

		ConEdge *nowCon = V1->Con;		//�ش� ������ ù ���� ����Ʈ�� ����.
		while (1)
		{
			if (nowCon == NULL)
			{
				cout << "Not found" << endl;	//������ �������� �ʴ´ٸ� Not found 
				break;
			}
			if (nowCon->MyEd->Ver1 == V2 || nowCon->MyEd->Ver2 == V2)	//������ �� ������ �ϳ��� �ٸ� ������ ��ġ�ϸ�
			{
				cout << nowCon->MyEd->StreetNum << endl;			//�ش� ������ ���� ��ȣ ���
				break;
			}
			else
				nowCon = nowCon->next;		//�ƴ϶�� ���� ���� ���� �������� ����
		}

	}
	else
	{									//�� ������ ������ ���� �������� �Լ� ���� ���� ���� �ݺ�
		ConEdge *nowCon = V2->Con;
		while (1)
		{
			if (nowCon == NULL)
			{
				cout << "Not found" << endl;
				break;
			}
			if (nowCon->MyEd->Ver1 == V1 || nowCon->MyEd->Ver2 == V1)
			{
				cout << nowCon->MyEd->StreetNum << endl;
				break;
			}
			else
				nowCon = nowCon->next;
		}

	}
}
void DelEdge(int streetnum)		//���� ����
{
	Edge* delEdge = SearchEdge(streetnum);	//������ ������ ��ġ�� ã�´�.
	if (delEdge == NULL)	//������ �������� �ʴ� ��� ����� �Լ� ����
	{
		cout << m << " Not found" << endl;
		return;
	}

	EdgeList* nowList = Gra->EDList;		//�׷����� �ִ� ���� ���������� ���� ���� ��ġ�� ã�´�
	if (nowList->SelfEd == delEdge)
		delete nowList;
	else
	{
		while (nowList->next->SelfEd != delEdge)
			nowList = nowList->next;		//�ش� ������ ��ġ�� ã�� �� ���� ���� �������� ������ ���ƺ���
		EdgeList* delList = nowList->next;	//�ش� ������ ��ġ�� ����
		nowList->next = nowList->next->next;

		delete delList;	//���� ����Ʈ ����
	}
	ConEdge* nowCon = delEdge->Ver1->Con;	//����� ���� ����Ʈ�� Ȯ���Ѵ�.
	if (nowCon->next == NULL)	//����� ������ �Ѱ���
		delete delEdge->ConEd1;	//����� ���� ����Ʈ ����

	else
	{
		while (1)
		{
			if (nowCon->next->MyEd == delEdge)	//������ ������ ����� ������ ������ ������
			{
				ConEdge* delCon = nowCon->next;	//���� ������ ���� �س��� �� ���� �������� next�� �ٲ� �� �� �����ϰ� �ݺ����� Ż���Ѵ�.
				nowCon->next = nowCon->next->next;
				delete delCon;
				break;
			}
			else
				nowCon = nowCon->next;	//���� ������ Ȯ���Ѵ�.
		}
	}
	nowCon = delEdge->Ver2->Con;		//���� ������ �ݺ��Ѵ�
	if (nowCon->next == NULL)
		delete delEdge->ConEd2;		//����� ���� ����Ʈ ����

	else
	{
		while (1)
		{
			if (nowCon->next->MyEd == delEdge)
			{
				ConEdge* delCon = nowCon->next;
				nowCon->next = nowCon->next->next;
				delete delCon;
				break;
			}
			else
				nowCon = nowCon->next;
		}
	}

	delEdge->Ver1->dev--;	//ã�Ҵٸ� �ش� ������ ���� �� ������ ���� ����
	delEdge->Ver2->dev--;	//
	m--;					//�� ������ ���� ����
	delete delEdge;		//���� ����
	cout << m << endl;


}
void DelVertex(int num)
{
	Vertex *delver = SearchVertex(num);		//������ ������ ��ġ�� ã�´�
	if (delver == NULL)	//ã�� ���ϸ� n, m, Not found ��� �� �Լ� ����
	{
		cout << n << " " << m << " Not found" << endl;
		return;
	}
	/*
	while (delver->Con->next != NULL)	//�Լ��� ����� �������� �������� ���󰣴�.
	{
		Edge *delEd = delver->Con->MyEd;

		if (delEd->Ver1->num != num)
		{
			ConEdge* DelCon = delEd->Ver1->Con;
			while (DelCon->MyEd != delEd)
			{
				DelCon = DelCon->next;
			}
			ConEdge* A = DelCon->next;
			DelCon->next = DelCon->next->next;
			delete A;
		}
		else if (delEd->Ver2->num != num)
		{
			ConEdge* DelCon = delEd->Ver2->Con;
			while (DelCon->MyEd != delEd)
			{
				DelCon = DelCon->next;
			}
			ConEdge* A = DelCon->next;
			DelCon->next = DelCon->next->next;
			delete A;

		}
		EdgeList* Dellist = Gra->EDList;
		EdgeList* NowDel;
		while (1)
		{
			if (Dellist->SelfEd == delEd)
			{
				NowDel = Dellist;
				delete NowDel;
				break;
			}
			if (Dellist->next->SelfEd == delEd)
			{
				NowDel = Dellist->next;
				Dellist->next = Dellist->next->next;
				delete NowDel;
				break;
			}
			else
				Dellist = Dellist->next;
		}

		delver->Con = delver->Con->next;
		delete delEd;
	}

	delete delver;
	*/
	n--;
	m = m - delver->dev;
}


int main()
{
	Gra = new Graph;
	char Q;
	int Num, n1, n2, streetnum;
	string File, E;
	cin >> File;
	ifstream In(File);	//���� ������� ���� ���� �ҷ�����
	In >> n >> m;
	for (int i = 0; i < n; i++)
	{
		In >> Num >> E;
		AddFileVertex(Num, E);	//���� �Է�
	}

	for (int i = 0; i < m; i++)
	{
		In >> streetnum >> n1 >> n2;
		AddFileEdge(streetnum, n1, n2);	//���� �Է�
	}


	while (1) {
		cin >> Q; //���Ǹ� �޾ƿ�
		switch (Q) {
		case 'A':       //�л� �߰�
			cin >> Num >> E;    //�й�, �̸����� ����
			AddVertex(Num, E);  //�л� �߰��Լ� ����
			break;

		case 'P':   //�л� ���� ���
			cin >> Num; //����� �л��� �й���  �Է� ����
			printVer(Num);  //��� �Լ� ����
			break;


		case 'I':   //���� �߰�
			cin >> streetnum >> n1 >> n2;   //���ι�ȣ�� �� �� ������ �й��� ����
			AddEdge(streetnum, n1, n2);       //���� �߰� �Լ� ����
			break;

		case 'X':   //�л� ����
			cin >> Num; //������ �й��� ����
			DelVertex(Num);  //���� �Լ� ����
			break;

		case 'Z':   //���� ����
			cin >> streetnum;   //������ ���ι�ȣ ����
			DelEdge(streetnum); //���� ���� �Լ� ����
			break;

		case 'L':   //����� ���� ���
			cin >> n1;  //�й��� ����
			printAllEd(n1); //��� ���θ� ����ϴ� �Լ� ����
			break;

		case 'F':   //���� ���� ��� 1
			cin >> streetnum;   //���� ��ȣ �Է� ����
			printEd1(streetnum);    //�������� ��� 1 �Լ� ����
			break;

		case 'O':   //���� ���� ��� 2
			cin >> n1 >> streetnum; //���� ��ȣ, �й� �Է¹���
			printEd2(streetnum, n1);    //�ش� �й��� ���ΰ� ���� �Ǿ� �ִ��� Ȯ���� ����ϴ� �Լ� ����
			break;

		case 'K':   //���� ���� ���� Ȯ��
			cin >> n1 >> n2;    //Ȯ�� �� �� �й��� �Է� ����
			IsAdjacency(n1, n2);    //�������� Ȯ���ϴ� �Լ� ����
			break;

		case 'Q': //���α׷� ����
			return 0;   //����
		}
	}

	return 0;
}