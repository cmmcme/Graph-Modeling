#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int n, m; //���� ����½� ���� ������ ���� ������ ����.

typedef struct Vertex  //������ ����ü
{
	int stunum;  //�й�
	string email; //�̸���
	int index;  //����
	struct Vertex *next;   //���� ������ ����Ŵ
	struct Edge *Incident;//����� ������ ����Ŵ
	Vertex() : stunum(0), index(0), next(NULL), Incident(NULL) {};  //�� ���� �ʱ�ȭ����

}Vertex;

typedef struct Edge  //������ ����ü
{
	int street;  //���ι�ȣ
	Edge *next;   //���� ����
	Vertex* From; //����� ����1
	Vertex* to; //����2

	Edge() : street(0), next(NULL), From(NULL), to(NULL) {};  //�� ���� �ʱ�ȭ�Ѵ�.

}Edge;

typedef struct Graph  //�׷����� ����ü
{
	Vertex* Vertices; //������ ����Ŵ
	Edge* Ed; //������ ����Ŵ
	Graph() : Vertices(NULL), Ed(NULL){}; //�� ���� �ʱ�ȭ�Ѵ�

}Graph;

Graph* G;

Vertex* SearchVer(int num) //num�̶�� �й��� �������ִ� ������ ã�´�.
{
	Vertex* ver = G->Vertices; //ver�� �׷����� ù ������ ����Ŵ
	while (1) // ver�� �й��� �ش� num�� ���� ��, �ݺ����� ����
	{
		if (ver == NULL) //���� �׷����� ������ �ִ� ��� ������ ���Ҵµ� ���ٸ� �ݺ����� ����
			break;
		if (ver->stunum == num)
			break;

		ver = ver->next; //���� ������ ã�ƺ���.
	}
	return ver; //������ ��ġ�� ��ȯ�Ѵ�. ������ ���ٸ� NULL�� ��ȯ��
	//O(n)
}

Edge* SearchEd(int num) //num�̶�� ���ι�ȣ�� ������ �ִ� ������ ã�ƺ���.
{
	Edge* serEd = G->Ed; //Ed�� �׷����� ù ������ ����Ŵ
	while (serEd->street != num) // ������ ������ �ִ� ���ι�ȣ�� �ش� num�� ���� ��, �ݺ����� ������
	{
		if (serEd == NULL) //��� ������ ��� ���Ҵµ� ���ٸ� �ݺ����� ������.
			break;
		serEd = serEd->next; //���� ������ ã�ƺ���.
	}

	return serEd;             //������ ��ġ�� ��ȯ��. ������ ���ٸ� NULL�� ��ȯ��
}

void AddVertex(int num, string EM) //���� �߰�
{
	Vertex *ver = new Vertex; // ���ο� ������ ������ش�.
	ver->stunum = num; //�� ������ �ش� �й��� �̸����� �־��ش�.
	ver->email = EM;
	Vertex* _Ver = G->Vertices; //_Ver�� �׷����� ù ������ ����Ų��.

	if (_Ver == NULL) //���࿡ �׷����� ������ ���ٸ�
		G->Vertices = ver; //ù ������ ��������.
	else
	{       //������ �����Ѵٸ�
		while (_Ver->next != NULL) //�׷����� ������ ������ ���鼭 ������ ����� �� ���� �ݺ����� �����Ѵ�.
			_Ver = _Ver->next;

		_Ver->next = ver;   //������ ������ �� ������ �� ������ �����Ѵ�.
	}

	n++;    //�� ������ ������ ������Ŵ.
}

void AddEdge(int streetnum, int Snum, int Vnum) //������ �߰��Ѵ�.
{
	Edge *Ed = new Edge; //���ο� ������ ������ش�.
	Vertex* SV = SearchVer(Snum); //Snum�� ������ �ִ� ������ ��ġ�� ã����
	Vertex* VV = SearchVer(Vnum);   //Vnum�� ������ �ִ� ������ ��ġ�� ã����

	if (SV == NULL || VV == NULL) //�� �� �ϳ��� ã�� ���ϸ� �� ������ ������ ��� �� �� Not found�� �����.
	{
		cout << m << " Not found" << endl;
		return;
	}

	else        //�Ѵ� ã�Ѵٸ�
	{
		Ed->street = streetnum; //������ ���ι�ȣ�� ������.
		Edge* _Edg = G->Ed; //_Edg�� �׷����� ù ������ ����Ų��
		Edge *SE = SV->Incident;
		Edge *VE = VV->Incident;

		if (_Edg == NULL) //���࿡ �׷����� ������ ���ٸ�
			G->Ed = Ed; //ù ������ ��������.
		else
		{       //������ �����Ѵٸ�
			while (_Edg->next != NULL) //�׷����� ������ ������ ���鼭 ������ ����� �� ���� �ݺ����� �����Ѵ�.
				_Edg = _Edg->next;

			_Edg->next = Ed;   //������ ������ �� ������ �� ������ �����Ѵ�.
		}
		while (SE != NULL) //ã�� ������ ����� ������ ������ �� �� ���� �ݺ����� �����Ѵ�.
			SE = SE->next;
		while (VE != NULL)
			VE = VE->next;

		SE = Ed; //����� �ִ� ��ġ�� ���´ٸ� �ش� ������ ����
		VE = Ed;
		Ed->From = SV;          //�ش� ������ �� �� ������ ��������.
		Ed->to = VV;
		SV->index++; //������ ������ ���������ش�.
		VV->index++;

	}

	m++; //������ ������ ������Ų��.
	cout << m << endl;   //���� �� �� �ִٸ� ������ ������ �����.
}

void DelVertex(int num)
{
	Vertex* ver = SearchVer(num); //���� ������ ��ġ�� ã�´�.

	if (ver == NULL) //���� �� ������ �������� �ʴ´ٸ�
	{
		cout << n << " " << m << " Not found" << endl;
		return;
	}
	//�� ������ ����, ������ ����, Not found�� ����� �� �Լ��� �����Ѵ�.

	n--; //������ ã�Ҵٸ� �켱 �����ϴ� ���̱⿡ ������ ������ 1�� ������.
	m = m - ver->index; //������ �����ϸ� �ش� ������ ����� ��� ������ �����Ǳ� ������ ������ ���� ��ŭ �� ������ ������ �����Ѵ�.

	while (1)
	{
		Edge* Ed = ver->Incident;  //Ed�� ������ ������ ����� ù ������
		if (Ed == NULL) //���� ������ ����� �ִٸ� �ݺ����� ����
			break;


		while (1)   //������ ����� ���� �ʴٸ�
		{
			if (Ed == NULL) //������ ������ �ݺ����� ������.
				break;

			while (1)
			{
				if (Ed->From->Incident == Ed)      //Ed������ ���� �� ������ ����� ������ Ed�� ��ġ�ϸ�
				{
					delete Ed->From->Incident; // �ش� ������ ����� ������ ���� ��Ų �� �ݺ����� Ż���Ѵ�.
					Ed->From->index--;
					break;
				}
				Ed->From->Incident = Ed->From->Incident->next;
				//����� ������ ��ġ���� �ʴ´ٸ� ���� ���� ���� ����. Ed�� ���� �� ������ ����� �����߿� Ed�� �ݵ�� �����ϹǷ�	�ݺ����� Ż�� �� �� �ִ�.
			}
			Ed = Ed->next;  //������ ������ ����� ���� ������ Ȯ���Ѵ�.
		}

		Ed = ver->Incident;  //Ed�� ������ ������ ����� ù ������

		while (1)
		{
			if (Ed == NULL) //������ ������ �ݺ����� �����Ѵ�.
				break;

			while (1)
			{
				if (Ed->to->Incident == Ed)    //Ed������ �ݴ� �� �� ������ ����� ������ Ed�� ��ġ�ϸ�
				{
					delete Ed->to->Incident;   //�ش� ������ �����.
					Ed->to->index--;            //�ش� ������ ������ �ִ� ������ ������ ���ҽ�Ų��.
					break;                      //�ݺ����� Ż���Ѵ�.
				}
				Ed->to->Incident = Ed->to->Incident->next;    //��ġ ���� �ʴ´ٸ� �ش� ������ ������ �ִ� ���� ������ Ȯ���Ѵ�.
			}
			Ed = Ed->next;  //������ ������ ����� ���� ������ Ȯ���Ѵ�.
		}

		delete Ed;  //�� ���� �ִ� ������ ����� ������ ��� ����� Ed�� ���� �Ѵ�.
		ver->Incident = ver->Incident->next;  //������ ������ ������ִ� ���� ������ Ȯ���Ѵ�.
	}
	delete ver;         //�ش� ������ ����
	cout << n << " " << m << endl;  //�� ������ ����, ������ ������ ����Ѵ�.
}


void DelEdge(int num)   //���� ����
{
	Edge* Ed = SearchEd(num);       //������ ��ġ�� ã�´�.
	if (Ed == NULL)                     //�ش� ������ �������� �ʴ´ٸ�
	{
		cout << m << " Not found" << endl;
		return;   //�Ѱ����� ������ ����ϰ� Not found�� ��� �� �� �Լ��� �����Ѵ�.
	}

	else
	{
		//�ش� ������ ã�� ���
		Ed->From->index--;      //������ ���� ���� ������ ���� 1 ���ҽ�Ų��.
		Ed->to->index--;
		m--;         //�� ������ ������ ���ҽ�Ų��.

		Edge *delFEg = Ed->From->Incident;
		while (1)
		{
			if (delFEg == Ed)  //�ش� ������ ���� ���� ����� ������ ������ ���� Ed�� ���ٸ�
			{
				delete delFEg;
				break;  //�ش� ������ �����ϰ� �ݺ����� �����Ѵ�.
			}

			delFEg = delFEg->next;
			//������ ������ ���� ���� ����� ������ ���� ������ Ȯ����.
		}

		Edge *delTEg = Ed->to->Incident;

		while (1)
		{
			if (delTEg == Ed)    //�ش� ������ ���� ���� ����� ������ ������ ���� Ed�� ���ٸ�
			{
				delete delTEg;
				break;  //�ش� ������ �����ϰ� �ݺ����� �����Ѵ�.
			}

			delTEg = delTEg->next;    //������ ������ ���� ���� ����� ������ ���� ������ Ȯ����.
		}

		delete Ed;  //�ش� ������ �����Ѵ�.

		cout << m << endl;   //�� ������ ������ ����Ѵ�.
	}
}

void printVer(int num)  //�л� ���� ���
{
	Vertex *v = SearchVer(num); //num�̶�� �й��� ������ �ִ� ������ ��ġ�� ã�´�.

	if (v != NULL)  //���� �ش� ������ �������� ������
		cout << v->email << " " << v->index << endl;
	//�ش� ������ �����ϸ� �̸��ϰ� ����� ������ ��(����)�� ����Ѵ�.
	else
		cout << "Not found" << endl; // //Not found�� �����
}
void printAllEd(int num)    //��� ���θ� ���
{
	Vertex* v = SearchVer(num); //�ش� ������ ��ġ�� ã��
	if (v->Incident != NULL)  //������ ��ġ�� ã������
	{
		cout << v->index << " ";    //������ ������ ���
		while (v->Incident != NULL)    //������ ����� ������ ������ ���� ����� �ݺ���
		{
			cout << v->Incident->street << " ";    //����� ������ ���� ��ȣ�� ���

			v->Incident = v->Incident->next;  //���� ������ ��ġ�� ����.
		}
		cout << endl;
	}
	else
		cout << "Not found" << endl;    //������ ã�� ���ϸ� Not found�� �����.

}

void printEd1(int stnum)    //���� ���� ���1
{
	Edge *Ed = SearchEd(stnum); //������ ��ġ�� ã��
	if (Ed != NULL) //������ ��ġ�� ã�Ҵٸ�
		cout << Ed->to->stunum << " " << Ed->From->stunum << endl;  //�� ������ �й��� ���

	else
		cout << "Not found" << endl;   //�ش� ������ �������� ���� ��� Not found ���

}

void printEd2(int stnum, int num)   //�ش� ������ ������ ����Ǿ� �ִ��� Ȯ��
{
	Edge *Ed = SearchEd(stnum); //�ش� ������ ��ġ�� ã���ְ�
	if (Ed->From->stunum == num)    //�ش� ������ �糡 ������  num�� ��ġ�ϸ� �ݴ��� ������ �й��� ��½�Ŵ
		cout << Ed->to->stunum << endl;

	else if (Ed->to->stunum == num)
		cout << Ed->From->stunum << endl;
	else
		cout << "Not available" << endl;    //�� �� ������ �Ѵ� num�� ��ġ���� �ʴ´ٸ� Not avaulable ���

}

void IsAdjacency(int n1, int n2)   //�� ������ �������� Ȯ�� �ϴ°�
{
	Vertex* V1 = SearchVer(n1); //n1�� ���� ������ �ִ� ������ ��ġ�� ����
	Vertex* V2 = SearchVer(n2); //n2�� ���� ������ �ִ� ������ ��ġ�� ã��
	if (V1 == NULL || V2 == NULL)
		cout << "Not found" << endl;        //���� �ϳ��� ã�� ���� ��� Not found ���

	else
	{
		if (V1->index<V2->index)    //V1�� ������ �� ���� ��,
		{
			Edge *ed = V1->Incident;  //ed�� V1�� ����� ������ ù��°
			while (1)
			{
				if (ed->From == V2)   //������ ���� ���� V2�� ���ٸ� ����� ������ ��ȣ�� ��� �� �� �ݺ��� Ż��
				{
					cout << ed->street << endl;
					break;
				}

				else if (ed->to == V2)  //������ ���� ���� V2�� ���ٸ� ����� ������ ��ȣ�� ��� �� �� �ݺ��� Ż��
				{
					cout << ed->street << endl;
					break;
				}

				if (ed == NULL)    //���� ��� ������ �� ���Ҵµ� V2�� ���� �ʴٸ�
					cout << "Not found" << endl;    //Not found ���

				ed = ed->next;    //����� ���� ������ Ȯ����
			}
		}

		else
		{
			Edge *ed = V2->Incident;  //ed�� V2�� ����� ������ ù��°
			while (1)
			{
				if (ed->From == V1)   //������ ���� ���� V1�� ������ ����� ������ ��ȣ�� ����ϰ� �ݺ��� Ż��
				{
					cout << ed->street << endl;
					break;
				}

				else if (ed->to == V1)  //������ ���� ���� V1�� ������ ����� ������ ��ȣ�� ����ϰ� �ݺ��� Ż��
				{
					cout << ed->street << endl;
					break;
				}

				if (ed == NULL)    //���� ��� ������ �� ���Ҵµ� V1�� ���� �ʴٸ�
					cout << "Not found" << endl;    //Not found ���

				ed = ed->next;    //����� ���� ������ Ȯ����

			}
		}
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	//	freopen("output2.txt", "w", stdout);

	G = new Graph;
	string file, E; //�����̸�, �̸���
	char Q; //���� ����
	int Num, streetnum, n1, n2; //�й�, ���ι�ȣ, �й�1, �й�2
	cin >> file;    //������ �Է¹���
	ifstream In(file);  //������ �о��

	In >> n >> m;   //ù �ٿ��� n�� m�� �о�´�.

	for (int i = 0; i<n; i++) //n�� �ݺ����� �ݺ��ϸ�
	{
		In >> Num >> E; //�й��� �̸����� �޾� �� ��
		Vertex *ver = new Vertex; // ���ο� ������ ������ش�.
		ver->stunum = Num; //�� ������ �ش� �й��� �̸����� �־��ش�.
		ver->email = E;
		Vertex* _Ver = G->Vertices; //_Ver�� �׷����� ù ������ ����Ų��.

		if (_Ver == NULL) //���࿡ �׷����� ������ ���ٸ�
			G->Vertices = ver; //ù ������ ��������.
		else
		{       //������ �����Ѵٸ�
			while (_Ver->next != NULL) //�׷����� ������ ������ ���鼭 ������ ����� �� ���� �ݺ����� �����Ѵ�.
				_Ver = _Ver->next;

			_Ver->next = ver;   //������ ������ �� ������ �� ������ �����Ѵ�.
		}
	}

	for (int i = 0; i<m; i++) //m�� �ݺ����� �ݺ��ϸ�
	{
		In >> streetnum >> n1 >> n2;    //���ι�ȣ�� �� �� ������ �й��� �ް�
		Edge *Ed = new Edge; //���ο� ������ ������ش�.
		Ed->street = streetnum; //������ ���ι�ȣ�� ������.
		Vertex* SV = SearchVer(n1); //Snum�� ������ �ִ� ������ ��ġ�� ã����
		Vertex* VV = SearchVer(n2);   //Vnum�� ������ �ִ� ������ ��ġ�� ã����

		if (SV == NULL || VV == NULL) //�� �� �ϳ��� ã�� ���ϸ� NULL���� ��ȯ���ش�.
			return NULL;

		else        //�Ѵ� ã�Ѵٸ�
		{
			Edge* _Edg = G->Ed; //_Edg�� �׷����� ù ������ ����Ų��

			if (_Edg == NULL) //���࿡ �׷����� ������ ���ٸ�
				G->Ed = Ed; //ù ������ ��������.
			else
			{       //������ �����Ѵٸ�
				while (_Edg->next != NULL) //�׷����� ������ ������ ���鼭 ������ ����� �� ���� �ݺ����� �����Ѵ�.
					_Edg = _Edg->next;

				_Edg->next = Ed;   //������ ������ �� ������ �� ������ �����Ѵ�.
			}

			Edge *SE = SV->Incident;
			Edge *VE = VV->Incident;


			while (SE != NULL) //ã�� ������ ����� ������ ������ �� �� ���� �ݺ����� �����Ѵ�.
				SE = SE->next;
			while (VE != NULL)
				VE = VE->next;

			SE = Ed; //����� �ִ� ��ġ�� ���´ٸ� �ش� ������ ����
			VE = Ed;
			Ed->From = SV;          //�ش� ������ �� �� ������ ��������.
			Ed->to = VV;
			SV->index++; //������ ������ ���������ش�.
			VV->index++;
		}
	}

	while (1) {
		cin >> Q; //���Ǹ� �޾ƿ�
		switch (Q) {
		case 'A':       //�л� �߰�
			cin >> Num >> E;    //�й�, �̸����� ����
			AddVertex(Num, E);  //�л� �߰��Լ� ����
			cout << n << endl; //�� �л��� ���
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
			cin >> streetnum >> n1; //���� ��ȣ, �й� �Է¹���
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
}