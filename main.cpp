#include <iostream>
#include <time.h>
#include <fstream>
#include <chrono>
using namespace std;

struct list
{
	list *next;
	int v;
};

int iter, *stos;
list **graph;
char *visited;

const char WHITE = 0;
const char GRAY = 1;
const char GREEN = 2;

void generate(int vertex)
{
	srand(time(NULL));
	ofstream wynik;
	wynik.open("dane.txt");
	int edges = 0.3*((vertex*vertex) - vertex);
	char **matrix;
	matrix = new char *[vertex];
	for (int i = 0; i < vertex; i++)
		matrix[i] = new char[vertex];
	
	for (int i = 0; i < vertex; i++)
		for (int j = 0; j < vertex; j++) matrix[i][j] = 0;

	int iterator=0;
	struct graph
	{
		int begin;
		int end;
	};
	graph *tab = new graph[edges];
	while (iterator < edges)
	{
		int i = rand()%vertex;
		int j = rand() % vertex;
		if (i < j && matrix[i][j]==0)
		{
			tab[iterator].begin = i;
			tab[iterator].end = j;
			matrix[i][j] = 1;
			iterator++;
		}
	}
	for (int i = 0; i < edges; i++)
	{
		wynik  << tab[i].begin << " " << tab[i].end << endl;
	}
}


bool TP_SORT(int v)
{
	list *p;
	if (visited[v] == GRAY)
	{
		return false;
	}
	if (visited[v] == WHITE)
	{
		visited[v] = GRAY;
		for (p = graph[v]; p; p = p->next)
			if (!TP_SORT(p->v)) return false;
		visited[v] = GREEN;
		stos[iter++] = v;
	}
	return true;
}


int main()
{
	int vertex = 100;
	for (int k = 0; k < 15; k++)
	{
		ifstream wejscie;
		wejscie.open("dane.txt");
		ofstream wynik;
		wynik.open("sortowanie_top.txt", ios::app);
		
		int begin;
		int end;
		list *p, *r;

		int edges = 0.3*((vertex*vertex) - vertex);
		generate(vertex);

		graph = new list *[vertex];
		stos = new int[vertex];
		iter = 0;

		visited = new char[vertex];
		for (int i = 0; i < vertex; i++)
		{
			graph[i] = NULL;
			visited[i] = WHITE;
		}

		for (int i = 0; i < edges; i++)
		{
			wejscie >> begin;
			wejscie >> end;
			p = new list;
			p->v = end;
			p->next = graph[begin];
			graph[begin] = p;
		}
		long long time = 0;
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < vertex; i++)
		{
			if (visited[i] == WHITE)
			{
				if (!TP_SORT(i)) break;
			}
		}
		auto stop = std::chrono::high_resolution_clock::now();
		time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
		/*
		if (iter == vertex)
			for (int i = vertex - 1; i >= 0; i--) cout << stos[i] << " ";

		cout << endl;

		*/
		wynik << vertex << " " << time << endl;
		for (int i = 0; i < vertex; i++)
		{
			p = graph[i];
			while (p)
			{
				r = p;
				p = p->next;
				delete r;
			}
		}
		delete[] graph;
		delete[] visited;
		delete[] stos;
		vertex = vertex + 200;
		cout << k << endl;
	}
	
	
	system("pause");
}