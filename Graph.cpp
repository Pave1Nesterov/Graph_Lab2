#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int fordfalkerson(int n, int m, int** matrix, bool* used, queue <int> BFS, int from, int to)
{
	vector <vector <int>> positions; 
	int* parents = new int[n];
	parents[from] = -1;
	int* lengths = new int[n];
	fill_n(lengths, n, 0);
	while (!BFS.empty())
	{
		int firstElem = BFS.front();
		BFS.pop();
		used[firstElem] = true; 
		for (int i = 0; i < m; i++)
		{
			if (matrix[firstElem][i] <= 0)
			{
				continue;
			}
			int j;
			for (j = 0; j < n; j++)
			{
				if (j != firstElem && matrix[j][i] != 0)
				{
					break;
				}
			}
			if (used[j])
			{
				continue;
			}
			lengths[j] = matrix[firstElem][i];
			parents[j] = firstElem;
			positions.push_back({ firstElem,j,i });
			BFS.push(j);
			used[j] = true;
		}
	}
	//Поиск пути
	vector<int> path, pathlen;
	int minimum;
	if (!used[to])
	{
		return -1;
	}
	else //нашёлся путь
	{
		for (int i = to; i != -1; i = parents[i])
		{
			path.push_back(i); //Определение пути, пробегаясь по массиву
			if (lengths[i] != 0) pathlen.push_back(lengths[i]);
		}
		reverse(path.begin(), path.end());
		reverse(pathlen.begin(), pathlen.end());
		minimum = *min_element(pathlen.begin(), pathlen.end());
	}
	//Изменение матрицы инцидентности
	for (int i = 0; i < path.size() - 1; i++)
	{
		for (int j = 0; j < positions.size(); j++)
		{
			if (positions[j][0] == path[i] && positions[j][1] == path[i + 1])
			{
				matrix[positions[j][0]][positions[j][2]] -= minimum;
				matrix[positions[j][1]][positions[j][2]] += minimum;
			}
		}
	}
	return minimum;
}

void print(int** matrix, int n, int m)
{
	cout << endl << "Используемая матрица инцидентности: " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) cout << matrix[i][j] << ' ';
		cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int n = 5, m = 8;
	cout << "Количество вершин : " << n << endl;
	cout << "Количество дуг : " << m;

	int** matrix;
	matrix = new int* [n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new int[m];
	}

	int mass[5][8] =
	{
		{10,  0, 30, 20,  0,  0,  0,  0},
		{ 0,  0,  0, 20, 40,  0,  0, 30},
		{ 0,  0, 30,  0, 40, 10, 20,  0},
		{10, 20,  0,  0,  0, 10,  0,  0},
		{ 0, 20,  0,  0,  0,  0, 20, 30}
	};

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			matrix[i][j] = mass[i][j];
		}
	}

	print(matrix, n, m);
	bool* used = new bool[n];
	int* parents = new int[n];
	int* lengths = new int[n];
	int from, to;
	from = 0; //исток
	to = 4; //сток

	queue <int> BFS;
	BFS.push(from);
	fill_n(used, n, false);

	int stream, answer = 0;
	while (true)
	{
		stream = fordfalkerson(n, m, matrix, used, BFS, from, to);
		if (stream == -1)
		{
			break;
		}
		answer += stream;
		fill_n(used, n, false);
	}

	if (answer == 0)
	{
		cout << endl << "Минимальный разрез сети не найден...";
	}
	else
	{
		cout << endl << "Минимальный разрез сети: " << answer;
	}
}