#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int n, m; //파일 입출력시 들어가는 정점의 갯수 간선의 갯수.

typedef struct Vertex  //정점의 구조체
{
	int stunum;  //학번
	string email; //이메일
	int index;  //차수
	struct Vertex *next;   //다음 정점을 가리킴
	struct Edge *Incident;//연결된 간선을 가리킴
	Vertex() : stunum(0), index(0), next(NULL), Incident(NULL) {};  //각 값을 초기화해줌

}Vertex;

typedef struct Edge  //간선의 구조체
{
	int street;  //도로번호
	Edge *next;   //다음 도로
	Vertex* From; //연결된 정점1
	Vertex* to; //정점2

	Edge() : street(0), next(NULL), From(NULL), to(NULL) {};  //각 값을 초기화한다.

}Edge;

typedef struct Graph  //그래프의 구조체
{
	Vertex* Vertices; //정점을 가리킴
	Edge* Ed; //간선을 가리킴
	Graph() : Vertices(NULL), Ed(NULL){}; //각 값을 초기화한다

}Graph;

Graph* G;

Vertex* SearchVer(int num) //num이라는 학번을 가지고있는 정점을 찾는다.
{
	Vertex* ver = G->Vertices; //ver은 그래프의 첫 정점을 가리킴
	while (1) // ver의 학번이 해당 num과 같을 때, 반복문을 끝냄
	{
		if (ver == NULL) //만약 그래프각 가지고 있는 모든 정점을 보았는데 없다면 반복문을 종료
			break;
		if (ver->stunum == num)
			break;

		ver = ver->next; //다음 정점을 찾아본다.
	}
	return ver; //정점의 위치를 반환한다. 정점이 없다면 NULL이 반환됨
	//O(n)
}

Edge* SearchEd(int num) //num이라는 도로번호를 가지고 있는 간선을 찾아본다.
{
	Edge* serEd = G->Ed; //Ed는 그래프의 첫 간선을 가리킴
	while (serEd->street != num) // 간선이 가지고 있는 도로번호가 해당 num과 같을 때, 반복문을 종료함
	{
		if (serEd == NULL) //모든 간선을 모두 보았는데 없다면 반복문을 종료함.
			break;
		serEd = serEd->next; //다음 간선을 찾아본다.
	}

	return serEd;             //간선의 위치를 반환함. 간선이 없다면 NULL이 반환됨
}

void AddVertex(int num, string EM) //정점 추가
{
	Vertex *ver = new Vertex; // 새로운 정점을 만들어준다.
	ver->stunum = num; //그 정점에 해당 학번과 이메일을 넣어준다.
	ver->email = EM;
	Vertex* _Ver = G->Vertices; //_Ver은 그래프의 첫 정점을 가리킨다.

	if (_Ver == NULL) //만약에 그래프에 정점이 없다면
		G->Vertices = ver; //첫 정점에 삽입해줌.
	else
	{       //정점이 존재한다면
		while (_Ver->next != NULL) //그래프의 정점의 다음을 보면서 다음이 비어질 때 까지 반복문을 실행한다.
			_Ver = _Ver->next;

		_Ver->next = ver;   //다음이 비어졋으면 그 다음에 새 정점을 삽입한다.
	}

	n++;    //총 정점의 갯수를 증가시킴.
}

void AddEdge(int streetnum, int Snum, int Vnum) //간선을 추가한다.
{
	Edge *Ed = new Edge; //새로운 간선을 만들어준다.
	Vertex* SV = SearchVer(Snum); //Snum을 가지고 있는 정점의 위치를 찾아줌
	Vertex* VV = SearchVer(Vnum);   //Vnum을 가지고 있는 정점의 위치를 찾아줌

	if (SV == NULL || VV == NULL) //둘 중 하나라도 찾지 못하면 총 간선의 갯수를 출력 한 후 Not found를 출력함.
	{
		cout << m << " Not found" << endl;
		return;
	}

	else        //둘다 찾앗다면
	{
		Ed->street = streetnum; //간선의 도로번호를 삽입함.
		Edge* _Edg = G->Ed; //_Edg는 그래프의 첫 간선을 가리킨다
		Edge *SE = SV->Incident;
		Edge *VE = VV->Incident;

		if (_Edg == NULL) //만약에 그래프에 정점이 없다면
			G->Ed = Ed; //첫 정점에 삽입해줌.
		else
		{       //정점이 존재한다면
			while (_Edg->next != NULL) //그래프의 정점의 다음을 보면서 다음이 비어질 때 까지 반복문을 실행한다.
				_Edg = _Edg->next;

			_Edg->next = Ed;   //다음이 비어졋으면 그 다음에 새 정점을 삽입한다.
		}
		while (SE != NULL) //찾은 정점에 연결된 간선의 다음이 빌 때 까지 반복문을 실행한다.
			SE = SE->next;
		while (VE != NULL)
			VE = VE->next;

		SE = Ed; //비어져 있는 위치가 나온다면 해당 간선을 삽입
		VE = Ed;
		Ed->From = SV;          //해당 간선의 양 끝 정점을 대입해줌.
		Ed->to = VV;
		SV->index++; //정점의 차수를 증가시켜준다.
		VV->index++;

	}

	m++; //간선의 갯수를 증가시킨다.
	cout << m << endl;   //삽입 할 수 있다면 간선의 갯수를 출력함.
}

void DelVertex(int num)
{
	Vertex* ver = SearchVer(num); //지울 정점의 위치를 찾는다.

	if (ver == NULL) //만약 그 정점이 존재하지 않는다면
	{
		cout << n << " " << m << " Not found" << endl;
		return;
	}
	//총 정점의 갯수, 간선의 갯수, Not found를 출려한 후 함수를 종료한다.

	n--; //정점을 찾았다면 우선 삭제하는 것이기에 정점의 갯수를 1개 감소함.
	m = m - ver->index; //정점을 삭제하면 해당 정점에 연결된 모든 간선도 삭제되기 때문에 정점의 차수 만큼 총 간선의 갯수도 감소한다.

	while (1)
	{
		Edge* Ed = ver->Incident;  //Ed는 삭제할 정점에 연결된 첫 간선임
		if (Ed == NULL) //만약 간선이 비어져 있다면 반복문을 종료
			break;


		while (1)   //간선이 비어져 있지 않다면
		{
			if (Ed == NULL) //간선의 끝까지 반복문을 실행함.
				break;

			while (1)
			{
				if (Ed->From->Incident == Ed)      //Ed간선의 한쪽 끝 정점에 연결된 간선이 Ed와 일치하면
				{
					delete Ed->From->Incident; // 해당 간선을 지우고 차수를 감소 시킨 후 반복문을 탈출한다.
					Ed->From->index--;
					break;
				}
				Ed->From->Incident = Ed->From->Incident->next;
				//연결된 간선이 일치하지 않는다면 다음 간선 까지 본다. Ed의 한쪽 끝 정점에 연결된 간선중엔 Ed가 반드시 존재하므로	반복문은 탈출 할 수 있다.
			}
			Ed = Ed->next;  //삭제할 정점에 연결된 다음 간선을 확인한다.
		}

		Ed = ver->Incident;  //Ed는 삭제할 정점에 연결된 첫 간선임

		while (1)
		{
			if (Ed == NULL) //간선의 끝까지 반복문을 실행한다.
				break;

			while (1)
			{
				if (Ed->to->Incident == Ed)    //Ed간선의 반대 쪽 끝 정점에 연결된 간선이 Ed와 일치하면
				{
					delete Ed->to->Incident;   //해당 간선을 지운다.
					Ed->to->index--;            //해당 간선을 가지고 있는 정점의 차수를 감소시킨다.
					break;                      //반복문을 탈출한다.
				}
				Ed->to->Incident = Ed->to->Incident->next;    //일치 하지 않는다면 해당 정점이 가지고 있는 다음 간선을 확인한다.
			}
			Ed = Ed->next;  //삭제할 정점에 연결된 다음 간선을 확인한다.
		}

		delete Ed;  //양 끝에 있는 정점에 연결된 간선을 모두 지우면 Ed를 삭제 한다.
		ver->Incident = ver->Incident->next;  //삭제할 정점에 연결되있는 다음 간선을 확인한다.
	}
	delete ver;         //해당 정점을 지움
	cout << n << " " << m << endl;  //총 정점의 갯수, 간선의 갯수를 출력한다.
}


void DelEdge(int num)   //간선 삭제
{
	Edge* Ed = SearchEd(num);       //간선의 위치를 찾는다.
	if (Ed == NULL)                     //해당 간선이 존재하지 않는다면
	{
		cout << m << " Not found" << endl;
		return;   //총간선의 갯수를 출력하고 Not found를 출력 한 후 함수를 종료한다.
	}

	else
	{
		//해당 간선을 찾은 경우
		Ed->From->index--;      //간선의 양쪽 끝의 차수를 각각 1 감소시킨다.
		Ed->to->index--;
		m--;         //총 간선의 갯수를 감소시킨다.

		Edge *delFEg = Ed->From->Incident;
		while (1)
		{
			if (delFEg == Ed)  //해당 간선의 한쪽 끝에 연결된 간선이 삭제할 간선 Ed와 같다면
			{
				delete delFEg;
				break;  //해당 간선을 삭제하고 반복문을 종료한다.
			}

			delFEg = delFEg->next;
			//삭제할 간선의 한쪽 끝에 연결된 간선의 다음 간선을 확인함.
		}

		Edge *delTEg = Ed->to->Incident;

		while (1)
		{
			if (delTEg == Ed)    //해당 간선의 한쪽 끝에 연결된 간선이 삭제할 간선 Ed와 같다면
			{
				delete delTEg;
				break;  //해당 간선을 삭제하고 반복문을 종료한다.
			}

			delTEg = delTEg->next;    //삭제할 간선의 한쪽 끝에 연결된 간선의 다음 간선을 확인함.
		}

		delete Ed;  //해당 간선을 삭제한다.

		cout << m << endl;   //총 간선의 갯수를 출력한다.
	}
}

void printVer(int num)  //학생 정보 출력
{
	Vertex *v = SearchVer(num); //num이라는 학번을 가지고 있는 정점의 위치를 찾는다.

	if (v != NULL)  //만약 해당 정점이 존재하지 않으면
		cout << v->email << " " << v->index << endl;
	//해당 정점이 존재하면 이메일과 연결된 도로의 수(차수)를 출력한다.
	else
		cout << "Not found" << endl; // //Not found를 출력함
}
void printAllEd(int num)    //모든 도로를 출력
{
	Vertex* v = SearchVer(num); //해당 정점의 위치를 찾음
	if (v->Incident != NULL)  //정점의 위치를 찾았으면
	{
		cout << v->index << " ";    //정점의 차수를 출력
		while (v->Incident != NULL)    //정점에 연결된 간선이 없을때 까지 출력을 반복함
		{
			cout << v->Incident->street << " ";    //연결된 간선의 도로 번호를 출력

			v->Incident = v->Incident->next;  //다음 간선의 위치로 간다.
		}
		cout << endl;
	}
	else
		cout << "Not found" << endl;    //정점을 찾지 못하면 Not found를 출력함.

}

void printEd1(int stnum)    //도로 정보 출력1
{
	Edge *Ed = SearchEd(stnum); //도로의 위치를 찾음
	if (Ed != NULL) //도로의 위치를 찾았다면
		cout << Ed->to->stunum << " " << Ed->From->stunum << endl;  //양 끝점의 학번을 출력

	else
		cout << "Not found" << endl;   //해당 간선이 존재하지 않을 경우 Not found 출력

}

void printEd2(int stnum, int num)   //해당 정점과 간선이 연결되어 있는지 확인
{
	Edge *Ed = SearchEd(stnum); //해당 간선의 위치를 찾아주고
	if (Ed->From->stunum == num)    //해당 간선의 양끝 정점이  num과 일치하면 반대쪽 정점의 학번을 출력시킴
		cout << Ed->to->stunum << endl;

	else if (Ed->to->stunum == num)
		cout << Ed->From->stunum << endl;
	else
		cout << "Not available" << endl;    //양 끝 정점이 둘다 num과 일치하지 않는다면 Not avaulable 출력

}

void IsAdjacency(int n1, int n2)   //두 정점이 인접한지 확인 하는거
{
	Vertex* V1 = SearchVer(n1); //n1의 값을 가지고 있는 정점의 위치를 차음
	Vertex* V2 = SearchVer(n2); //n2의 값을 가지고 있는 정점의 위치를 찾음
	if (V1 == NULL || V2 == NULL)
		cout << "Not found" << endl;        //둘중 하나라도 찾지 못할 경우 Not found 출력

	else
	{
		if (V1->index<V2->index)    //V1이 차수가 더 작을 때,
		{
			Edge *ed = V1->Incident;  //ed는 V1이 연결된 간선의 첫번째
			while (1)
			{
				if (ed->From == V2)   //간선의 한쪽 끝이 V2와 같다면 연결된 도로의 번호를 출력 한 후 반복문 탈출
				{
					cout << ed->street << endl;
					break;
				}

				else if (ed->to == V2)  //간선의 한쪽 끝이 V2와 같다면 연결된 도로의 번호를 출력 한 후 반복문 탈출
				{
					cout << ed->street << endl;
					break;
				}

				if (ed == NULL)    //만약 모든 간선을 다 보았는데 V2와 같지 않다면
					cout << "Not found" << endl;    //Not found 출력

				ed = ed->next;    //연결된 다음 간선을 확인함
			}
		}

		else
		{
			Edge *ed = V2->Incident;  //ed는 V2에 연결된 간선의 첫번째
			while (1)
			{
				if (ed->From == V1)   //간선의 한쪽 끝이 V1과 같담젼 연결된 도로의 번호를 출력하고 반복문 탈출
				{
					cout << ed->street << endl;
					break;
				}

				else if (ed->to == V1)  //간선의 한쪽 끝이 V1과 같담젼 연결된 도로의 번호를 출력하고 반복문 탈출
				{
					cout << ed->street << endl;
					break;
				}

				if (ed == NULL)    //만약 모든 간선을 다 보았는데 V1와 같지 않다면
					cout << "Not found" << endl;    //Not found 출력

				ed = ed->next;    //연결된 다음 간선을 확인함

			}
		}
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	//	freopen("output2.txt", "w", stdout);

	G = new Graph;
	string file, E; //파일이름, 이메일
	char Q; //질의 변수
	int Num, streetnum, n1, n2; //학번, 도로번호, 학번1, 학번2
	cin >> file;    //파일을 입력받음
	ifstream In(file);  //파일을 읽어옴

	In >> n >> m;   //첫 줄에서 n과 m을 읽어온다.

	for (int i = 0; i<n; i++) //n번 반복문을 반복하며
	{
		In >> Num >> E; //학번과 이메일을 받아 온 후
		Vertex *ver = new Vertex; // 새로운 정점을 만들어준다.
		ver->stunum = Num; //그 정점에 해당 학번과 이메일을 넣어준다.
		ver->email = E;
		Vertex* _Ver = G->Vertices; //_Ver은 그래프의 첫 정점을 가리킨다.

		if (_Ver == NULL) //만약에 그래프에 정점이 없다면
			G->Vertices = ver; //첫 정점에 삽입해줌.
		else
		{       //정점이 존재한다면
			while (_Ver->next != NULL) //그래프의 정점의 다음을 보면서 다음이 비어질 때 까지 반복문을 실행한다.
				_Ver = _Ver->next;

			_Ver->next = ver;   //다음이 비어졋으면 그 다음에 새 정점을 삽입한다.
		}
	}

	for (int i = 0; i<m; i++) //m번 반복문을 반복하며
	{
		In >> streetnum >> n1 >> n2;    //도로번호와 양 끝 정점의 학번을 받고
		Edge *Ed = new Edge; //새로운 간선을 만들어준다.
		Ed->street = streetnum; //간선의 도로번호를 삽입함.
		Vertex* SV = SearchVer(n1); //Snum을 가지고 있는 정점의 위치를 찾아줌
		Vertex* VV = SearchVer(n2);   //Vnum을 가지고 있는 정점의 위치를 찾아줌

		if (SV == NULL || VV == NULL) //둘 중 하나라도 찾지 못하면 NULL값을 반환해준다.
			return NULL;

		else        //둘다 찾앗다면
		{
			Edge* _Edg = G->Ed; //_Edg는 그래프의 첫 간선을 가리킨다

			if (_Edg == NULL) //만약에 그래프에 정점이 없다면
				G->Ed = Ed; //첫 정점에 삽입해줌.
			else
			{       //정점이 존재한다면
				while (_Edg->next != NULL) //그래프의 정점의 다음을 보면서 다음이 비어질 때 까지 반복문을 실행한다.
					_Edg = _Edg->next;

				_Edg->next = Ed;   //다음이 비어졋으면 그 다음에 새 정점을 삽입한다.
			}

			Edge *SE = SV->Incident;
			Edge *VE = VV->Incident;


			while (SE != NULL) //찾은 정점에 연결된 간선의 다음이 빌 때 까지 반복문을 실행한다.
				SE = SE->next;
			while (VE != NULL)
				VE = VE->next;

			SE = Ed; //비어져 있는 위치가 나온다면 해당 간선을 삽입
			VE = Ed;
			Ed->From = SV;          //해당 간선의 양 끝 정점을 대입해줌.
			Ed->to = VV;
			SV->index++; //정점의 차수를 증가시켜준다.
			VV->index++;
		}
	}

	while (1) {
		cin >> Q; //질의를 받아옴
		switch (Q) {
		case 'A':       //학생 추가
			cin >> Num >> E;    //학번, 이메일을 받음
			AddVertex(Num, E);  //학생 추가함수 실행
			cout << n << endl; //총 학생수 출력
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
			cin >> streetnum >> n1; //도로 번호, 학번 입력받음
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
}