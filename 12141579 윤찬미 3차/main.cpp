#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
int n, m;
typedef struct VertexList	//각 정점을 가리키고 있는 Vertex 시퀀스를 구조체로 정의한다.
{
	VertexList* next;	//다음 시퀀스를 가리킴
	struct Vertex* MyVer;	//정점을 가리킨다.

	VertexList() : next(NULL), MyVer(NULL) {};	//각 값을 초기화한다.
} VertexList;

typedef struct Vertex	//정점의 구조체
{
	int num;	//학번
	string Email;	//이메일
	int dev;	//차수
	struct ConEdge *Con;	//연결되어있는 간선의 시퀀스
	Vertex() : num(0), dev(0), Con(NULL) {};	//초기화해준다

}Vertex;

typedef struct ConEdge	//정점에 연결된 간선의 시퀀스
{
	ConEdge* next;	//다음 간선 시퀀스
	struct Edge *MyEd;	//간선의 위치
	ConEdge() : next(NULL), MyEd(NULL) {};	//초기화 시켜준다.
} ConEdge;

typedef struct EdgeList	//그래프에서 간선의 시퀀스
{
	EdgeList* next;	//다음 간선
	struct Edge *SelfEd;	//가지고 있는 간선의 위치
	EdgeList() : next(NULL), SelfEd(NULL) {};	//초기화

} EdgeList;

typedef struct Edge
{
	int StreetNum;	//도로 번호
	ConEdge* ConEd1;	//한쪽 정점에 연결된 간선 시퀀스
	ConEdge* ConEd2;	//반대쪽 정점에 연결된 간선 시퀀스
	EdgeList* MyOrder;	//엣지 리스트에서 나의 위치
	Vertex *Ver1;	//한쪽 정점의 위치
	Vertex *Ver2;	//반대쪽 정점의 위치
	Edge() : StreetNum(0), ConEd1(NULL), ConEd2(NULL), MyOrder(NULL), Ver1(NULL), Ver2(NULL) {}; //각 값을 초기화한다.
}Edge;

typedef struct Graph	//그래프 구조체
{
	EdgeList* EDList;	//엣지 리스트 시퀀스
	VertexList* VerList;	//버텍스 시퀀스
	Graph() : EDList(NULL), VerList(NULL) {};	//초기화해줌

}Graph;

Graph *Gra;

void AddFileVertex(int num, string Email)
{
	VertexList* newVList = new VertexList;	//버텍스 리스트에 삽입 할 새로운 노드를 만든다
	Vertex* newV = new Vertex;				//새로운 버텍스 노드를 만든다
	newV->num = num;						//각 값을 저장한다.
	newV->Email = Email;
	newVList->MyVer = newV;			//새로만든 버텍스 리스트가 가지는 정점은 newV(새로만든 Vertex)이다.

	VertexList* NOW = Gra->VerList;	//그래프에 있는 버텍스 리스트에서 삽입할 곳을 찾는다. 첫 정점 리스트로 간다.
	if (NOW == NULL)	//만약 처음이 비어져있다면
		Gra->VerList = newVList;		//바로 삽입

	else {			//비어져 있지 않다면,
		while (NOW->next != NULL)	//리스트의 다음이 빌 때 가지 반복문을 돌린다.
			NOW = NOW->next;

		NOW->next = newVList;	//반복문을 탈출하면 리스트의 다음에 새로운 버텍스 리스트 노드를 삽입한다.
	}

}
void AddVertex(int num, string Email)
{
	AddFileVertex(num, Email);	//위에서 구현한 함수를 실행하여 정점을 삽입한다.
	n++;						//총 정점의 갯수를 더한 후 출력한다.
	cout << n << endl;
}
Vertex* SearchVertex(int num)			//정점의 위치를 찾고 반환해주는 함수
{
	VertexList *SearchNow = Gra->VerList;	//그래프의 정점리스트시퀀스의 처음부터 살펴본다.

	while (1)
	{
		if (SearchNow == NULL)	//만약 모든 시퀀스를 다 보았는데 없다면 반복문을 탈출한다.
			break;
		if (SearchNow->MyVer->num == num)	//해당 학번과 같은 정점의 위치를 찾았다면 반복문을 탈출한다.
			break;

		else
			SearchNow = SearchNow->next;		//위 두 조건을 만족하지 못했다면 다음 정점리스트로 간다.
	}
	if (SearchNow != NULL)	//정점을 찾았다면 그 위치를 반환한다.
		return SearchNow->MyVer;
	else
		return NULL;	//찾지 못하였다면 그 NULL값을 반환한다.
}

void AddFileEdge(int StreetNum, int n1, int n2)
{													//간선 삽입
	EdgeList *newEdList = new EdgeList;				//새로운 간선 리스트를 만들어준다
	Edge *newEdge = new Edge;						//새로운 간선을 만들어준다.
	newEdge->StreetNum = StreetNum;					//해당 도로번호를 넣어준다.
	Vertex *ver1 = SearchVertex(n1);				//n1,n2를 가지고 있는 버텍스를 찾는다.
	Vertex *ver2 = SearchVertex(n2);
	if (ver1 == NULL || ver2 == NULL)
		return;										//둘 중 하나라도 찾을 수 없다면 함수를 끝냄

	newEdge->Ver1 = ver1;							//둘다 찾았다면 새로운 엣지가 가리키는 양 끝 정점을 지정한다.
	newEdge->Ver2 = ver2;

	ConEdge* newCon1 = ver1->Con;					//한 정점의 연결된 간선 시퀀스를 따라가며 빈 공간에 새로운 간선 시퀀스를 만들어주고 삽입한다.
	if (newCon1 == NULL)							//만약 간선 시퀀스가 비어있다면
	{
		ConEdge* newOne = new ConEdge;			//새로운 간선 시퀀스를 만듬
		ver1->Con = newOne;						//처음 간선 시퀀스에 대입
		newOne->MyEd = newEdge;					//새로운 엣지의 위치를 자기가 가지고 있는 엣지의 위치 정보로 저장
		newEdge->ConEd1 = newOne;				//엣지 또한 가지고 있는 간선시퀀스의 위치로 저장
	}
	else
	{										//간선 시퀀스가 비어있지 않다면
		while (newCon1->next != NULL)		//다음 간선 시퀀스가 빌때가지 반복문을 실행한다.
			newCon1 = newCon1->next;
		ConEdge* newOne = new ConEdge;		//비어있는 위치가 나오면 새로운 간선 시퀀스 노드를 만든 후,
		newCon1->next = newOne;				//삽입
		newOne->MyEd = newEdge;				//새로운 엣지의 위치를 자기가 가지고 있는 엣지의 위치 정보로 저장
		newEdge->ConEd1 = newOne;			//엣지 또한 가지고 있는 간선시퀀스의 위치로 저장
	}

	ConEdge* newCon2 = ver2->Con;			//위의 과정을 반복한다.
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
	//그래프의 엣지 리스트에 삽입하는 과정
	if (Gra->EDList == NULL)	{			//그래프의 엣지리스트가 비어져있다면
		Gra->EDList = newEdList;			//새로운 엣지 리스트 만든 것을 대입
		newEdList->SelfEd = newEdge;		//그것이 가리키고 있는 엣지는 새로 만든 엣지임
	}
	else
	{												//비어있지 않다면
		EdgeList* NowEdgeList = Gra->EDList;
		while (NowEdgeList->next != NULL)		//다음 엣지 리스트가 빌때까지 반복문을 실행한다.
			NowEdgeList = NowEdgeList->next;

		NowEdgeList->next = newEdList;	//반복문을 빠져 나오면 다음 위치에 엣지 리스트를 삽입 하고,
		newEdList->SelfEd = newEdge;		//엣지 리스트의 엣지위치에 새로운 엣지를 삽입한다.
	}
	ver1->dev++;		//전 과정을 긑낸 후 양 끝 정점의 차수를 1씩 증가시킨다.
	ver2->dev++;
}
void AddEdge(int StreetNum, int n1, int n2)		//위 AddFileEdge 함수와 과정이 같다.
{
	EdgeList *newEdList = new EdgeList;
	Edge *newEdge = new Edge;
	newEdge->StreetNum = StreetNum;
	Vertex *ver1 = SearchVertex(n1);
	Vertex *ver2 = SearchVertex(n2);
	if (ver1 == NULL || ver2 == NULL) {			//둘 중 하나라도 찾지 못하였다면
		cout << m << " Not found" << endl;		//총 간선의 갯수, Not found를 출력 한 후 함수를 종료한다.
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

	m++;					//총 간선의 갯수를 1개 증가시킨다.
	cout << m << endl;		//총 간선의 갯수를 출력한다.

}

Edge* SearchEdge(int StreetNum)	//해당 도로번호를 가지고 있는 간선의 위치를 반환하는 함수
{
	EdgeList *nowList = Gra->EDList;
	//그래프의 첫 간선리스트를 봄

	while (1) {
		if (nowList == NULL)	//만약 비어져있다면 반복문을 탈출
			break;

		if (nowList->SelfEd->StreetNum == StreetNum)	//그 리스트가 가지고 있는 간선의 도로번호와 입력받은 도로번호가 같다면 반복문 탈출
			break;

		else
			nowList = nowList->next;		//둘다 해당하지 않을 경우 다음 간선리스트를 본다.

	}
	if (nowList != NULL)	//간선의 위치를 찾았다면 그 간선의 위치를 반환해준다
		return nowList->SelfEd;
	else
		return NULL;		//찾지 못하였다면 NULL값을 반환한다.
}
void printVer(int num)		//해당 학번의 정보를 출력한다.
{
	Vertex* PrintNow = SearchVertex(num);	//SearchVertex를 통해 해당 정점의 위치를 찾는다.
	if (PrintNow == NULL)					//찾지 못하면 Not found 출력
		cout << "Not found" << endl;
	else
		cout << PrintNow->Email << " " << PrintNow->dev << endl;	//찾았다면 이메일과 차수를 출력한다.

}
void printEd1(int StreetNum)	//해당 도로번호의 정보 출력
{
	Edge *Search = SearchEdge(StreetNum);	//해당 도로번호를 가지고있는 간선의 위치를 찾음
	if (Search == NULL)						//찾지 못했다면 Not found 출력
		cout << "Not found" << endl;
	else
	{										//찾았다면 양 끝 정점이 가지고 있는 학번 중 더 작은 것 순서대로 출력한다.
		if (Search->Ver1->num < Search->Ver2->num)
			cout << Search->Ver1->num << " " << Search->Ver2->num << endl;
		else
			cout << Search->Ver2->num << " " << Search->Ver1->num << endl;
	}
}
void printEd2(int StreetNum, int num)	//해당 학번위치에서 도로번호 위치로 갈 수 있는지 확인
{
	Vertex* SerVE = SearchVertex(num);	//해당 학번의 위치를 찾음
	Edge* SerEd = SearchEdge(StreetNum);	//도로 번호의 위치를 찾음
	if (SerVE == NULL || SerEd == NULL)			//둘 중 하나라도 발견하지 못하면 Not available 출력
		cout << "Not available" << endl;
	else
	{												//둘다 찾았다면
		if (SerEd->Ver1->num == num)				//간선의 한쪽 끝 정점의 학번이 해당 학번과 같다면
			cout << SerEd->Ver2->num << endl;		//num과 반대쪽 위치의 정점의 학번 출력

		else if (SerEd->Ver2->num == num)			//간선의 한쪽 끝 정점의 학번이 해당 학번과 같다면
			cout << SerEd->Ver1->num << endl;		//num과 반대쪽 위치의 정점의 학번 출력
		else
			cout << "Not available" << endl;		//양 쪽 모두 다르다면 Not available 출력
	}

}

void printAllEd(int num)		//해당 학번을 가지고 있는 정점에 연결된 모든 간선 출력
{
	Vertex *PrintVer = SearchVertex(num);	//학번의 위치를 찾음
	if (PrintVer == NULL)					//학번이 존재하지 않는다면 Not found 출력
		cout << "Not found" << endl;

	else {
		cout << PrintVer->dev << " ";		//정점의 차수 출력
		ConEdge* PrintCon = PrintVer->Con;	//해당 정점의 연결 간선의 리스트로 간다.
		while (PrintCon != NULL)	//리스트의 끝까지 보며, 
		{
			cout << PrintCon->MyEd->StreetNum << " ";	//도로 번호를 출력한다.

			PrintCon = PrintCon->next;	//다음 리스트로 옮김
		}

		cout << endl;

	}
}
void IsAdjacency(int n1, int n2)	//두 정점이 서로 인접해 있는지 확인
{
	Vertex* V1 = SearchVertex(n1);
	Vertex* V2 = SearchVertex(n2);		//두 정점의 위치를 찾음
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
	if (V1->dev < V2->dev)				//두 정점중 차수가 작은 정점으로 함수 실행
	{

		ConEdge *nowCon = V1->Con;		//해당 정점의 첫 간선 리스트로 간다.
		while (1)
		{
			if (nowCon == NULL)
			{
				cout << "Not found" << endl;	//간선이 존재하지 않는다면 Not found 
				break;
			}
			if (nowCon->MyEd->Ver1 == V2 || nowCon->MyEd->Ver2 == V2)	//간선의 양 끝점중 하나가 다른 정점과 일치하면
			{
				cout << nowCon->MyEd->StreetNum << endl;			//해당 간선의 도로 번호 출력
				break;
			}
			else
				nowCon = nowCon->next;		//아니라면 연결 다음 간선 시퀀스를 본다
		}

	}
	else
	{									//두 정점중 차수가 작은 정점으로 함수 실행 같은 과정 반복
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
void DelEdge(int streetnum)		//간선 삭제
{
	Edge* delEdge = SearchEdge(streetnum);	//삭제할 간선의 위치를 찾는다.
	if (delEdge == NULL)	//간선이 존재하지 않는 경우 출력후 함수 종료
	{
		cout << m << " Not found" << endl;
		return;
	}

	EdgeList* nowList = Gra->EDList;		//그래프에 있는 엣지 시퀀스에서 삭제 간선 위치를 찾는다
	if (nowList->SelfEd == delEdge)
		delete nowList;
	else
	{
		while (nowList->next->SelfEd != delEdge)
			nowList = nowList->next;		//해당 간선의 위치를 찾을 때 가지 엣지 시퀀스를 끝까지 돌아본다
		EdgeList* delList = nowList->next;	//해당 간선의 위치로 지정
		nowList->next = nowList->next->next;

		delete delList;	//엣지 리스트 삭제
	}
	ConEdge* nowCon = delEdge->Ver1->Con;	//연결된 간선 리스트를 확인한다.
	if (nowCon->next == NULL)	//연결된 간선이 한개면
		delete delEdge->ConEd1;	//연결된 간선 리스트 삭제

	else
	{
		while (1)
		{
			if (nowCon->next->MyEd == delEdge)	//삭제할 간선과 연결된 간선의 다음이 같으면
			{
				ConEdge* delCon = nowCon->next;	//다음 간선을 복사 해놓고 그 다음 간선으로 next를 바꿔 준 후 삭제하고 반복문을 탈출한다.
				nowCon->next = nowCon->next->next;
				delete delCon;
				break;
			}
			else
				nowCon = nowCon->next;	//다음 간선을 확인한다.
		}
	}
	nowCon = delEdge->Ver2->Con;		//위의 과정을 반복한다
	if (nowCon->next == NULL)
		delete delEdge->ConEd2;		//연결된 간선 리스트 삭제

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

	delEdge->Ver1->dev--;	//찾았다면 해당 간선의 양쪽 끝 정점의 차수 감소
	delEdge->Ver2->dev--;	//
	m--;					//총 간선의 갯수 감소
	delete delEdge;		//간선 삭제
	cout << m << endl;


}
void DelVertex(int num)
{
	Vertex *delver = SearchVertex(num);		//삭제할 정점의 위치를 찾는다
	if (delver == NULL)	//찾지 못하면 n, m, Not found 출력 후 함수 종료
	{
		cout << n << " " << m << " Not found" << endl;
		return;
	}
	/*
	while (delver->Con->next != NULL)	//함수에 연결된 엣지들의 시퀀스를 따라간다.
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
	ifstream In(File);	//파일 입출력을 통한 파일 불러오기
	In >> n >> m;
	for (int i = 0; i < n; i++)
	{
		In >> Num >> E;
		AddFileVertex(Num, E);	//정점 입력
	}

	for (int i = 0; i < m; i++)
	{
		In >> streetnum >> n1 >> n2;
		AddFileEdge(streetnum, n1, n2);	//간선 입력
	}


	while (1) {
		cin >> Q; //질의를 받아옴
		switch (Q) {
		case 'A':       //학생 추가
			cin >> Num >> E;    //학번, 이메일을 받음
			AddVertex(Num, E);  //학생 추가함수 실행
			break;

		case 'P':   //학생 정보 출력
			cin >> Num; //출력할 학생의 학번을  입력 받음
			printVer(Num);  //출력 함수 실행
			break;


		case 'I':   //간선 추가
			cin >> streetnum >> n1 >> n2;   //도로번호와 양 끝 정점의 학번을 받음
			AddEdge(streetnum, n1, n2);       //간선 추가 함수 실행
			break;

		case 'X':   //학생 삭제
			cin >> Num; //삭제할 학번을 받음
			DelVertex(Num);  //삭제 함수 실행
			break;

		case 'Z':   //도로 삭제
			cin >> streetnum;   //삭제할 도로번호 받음
			DelEdge(streetnum); //간선 삭제 함수 실행
			break;

		case 'L':   //연결된 도로 출력
			cin >> n1;  //학번을 받음
			printAllEd(n1); //모든 도로를 출력하는 함수 실행
			break;

		case 'F':   //도로 정보 출력 1
			cin >> streetnum;   //도로 번호 입력 받음
			printEd1(streetnum);    //도로정보 출력 1 함수 실행
			break;

		case 'O':   //도로 정보 출력 2
			cin >> n1 >> streetnum; //도로 번호, 학번 입력받음
			printEd2(streetnum, n1);    //해당 학번과 도로가 연결 되어 있는지 확인후 출력하는 함수 실행
			break;

		case 'K':   //도로 존재 여부 확인
			cin >> n1 >> n2;    //확인 할 두 학번을 입력 받음
			IsAdjacency(n1, n2);    //인접한지 확인하는 함수 실행
			break;

		case 'Q': //프로그램 종료
			return 0;   //종료
		}
	}

	return 0;
}