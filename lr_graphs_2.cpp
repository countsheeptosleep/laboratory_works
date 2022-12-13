#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// Объявление и инициализация глобальных констант:
const int N = 8; // Число вершин графа
const int inf = 999999; // Бесконечность

// Объявление основных функций:
void FloydWarshall(const int Graph[N][N], int start, int end); // Алгоритм Флойда — Уоршелла

void Dijkstra(const int Graph[N][N], int start, int end); // Алгоритм Дейкстры
void FindAllShortestPaths(int startPosition, int endPosition, int* visitedVertices, int k, int** DGraph, int* ShortestPath);

void Prima(const int Graph[N][N]);
void PrimaSecond(int** Derevo, bool* Visited, int** Graph, std::vector<int> i_j_d);

// Объявление вспомогательных функций:
void printmatrix(const int arr[N]); // Печать матрицы размера 1xN
void printmatrix(const int arr[N][N]); // Печать матрицы размера NxN
void printmatrix(const bool arr[N]); // Печать матрицы размера 1xN (bool)
void printmatrix(std::vector<int> i_j_d); // Печать вектора
void printmatrix(int** Derevo);



int main() {

	setlocale(LC_ALL, "Russian");

	int start = 0; // Индекс вершины X1, считая от 0
	int end = 7; // Индекс вершины X8, считая от 0

	const int Graph[N][N] = { // Опишем граф
			{0,3,inf,5,inf,inf,inf,inf},
			{inf,0,inf,2,inf,inf,7,inf},
			{inf,3,0,inf,inf,9,inf,inf},
			{inf,inf,inf,0,1,5,inf,inf},
			{inf,inf,inf,inf,0,8,6,inf},
			{inf,inf,inf,inf,inf,0,10,inf},
			{inf,inf,4,inf,inf,inf,0,4},
			{inf,inf,inf,inf,inf,12,inf,0},
	};

	// Постановка задачи
	cout << "Дан граф:\n";
	printmatrix(Graph);
	cout << "\n\n\n";

	// Алгоритм Дейкстры
	cout << "Задание 1. Поиск всех кратчайших путей из X1 в X8.\n\n";
	Dijkstra(Graph, start, end);
	cout << "\n\n\n\n\n";

	// Алгоритм Флойда — Уоршелла
	cout << "Задание 2. Поиск радиуса, диаметра и центров графа.\n\n";
	FloydWarshall(Graph, start, end);
	cout << "\n\n\n\n\n";

	// Алгоритм нахождения остовного дерево минимального веса
	cout << "Задание 3. Построить все остовные деревья минимального веса (считая граф неориентированным).\n\n";
	Prima(Graph);
	cout << "\n\n\n\n\n";


	system("pause");
	return 0;
}

// Описание функции Prima:
void Prima(const int Graph[N][N]) {

	// Скопируем элементы Graph в новый массив PGraph
	int** PGraph = new int* [N];
	for (int i = 0; i < N; i++) {
		PGraph[i] = new int[N];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			PGraph[i][j] = Graph[i][j];
		}
	}

	// Сделаем граф неориентированным
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (PGraph[i][j] != inf) {
				PGraph[j][i] = PGraph[i][j];
			}
		}
	}

	// Распечатаем новый граф
	cout << "Исходный граф с той поправкой, что теперь он неориентированный:\n";
	printmatrix(PGraph);

	// Создадим пустое остовное дерево
	int** Derevo = new int*[N]; 
	for (int i = 0; i < N; i++) {
		Derevo[i] = new int[N];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Derevo[i][j] = inf;
			if (i == j)Derevo[i][j] = 0;
		}
	}

	// Создадим пустой массив посещенных вершин PGraph
	bool* Visited = new bool [N]; 
	for (int i = 0; i < N; i++) {
		Visited[i] = false;
	}

	// Создадим вектор рассстояний d от i-ой до j-ой вершин, где i и j - рассмотренные
	std::vector<int> i_j_d;

	cout << "\nМинимальные остовные деревья:\n\n";

	PrimaSecond(Derevo, Visited, PGraph, i_j_d);
	
}

void PrimaSecond(int** DerevoPreviousPart, bool* VisitedPrevious, int** Graph, std::vector<int > i_j_d2) {

	// Создадим копию уже созданной части остовного дерева (так как их может быть несколько с этой общей частью)
	int** Derevo = new int*[N];
	for (int i = 0; i < N; i++) {
		Derevo[i] = new int[N];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Derevo[i][j] = DerevoPreviousPart[i][j];
		}
	}

	// Аналогично создадим копию массива посещенных вершин
	bool* Visited = new bool[N];
	for (int i = 0; i < N; i++) {
		Visited[i] = VisitedPrevious[i];
	}

	// И копию вектора
	std::vector<int > i_j_d;
	for (int i = 0; i < i_j_d.size(); i++) {
		i_j_d[i] = i_j_d2[i];
	}

	// Если нулевая вершина не посещена, посетить её
	if (Visited[0] == false) {

		// Отметим её, как посещенную
		Visited[0] = true;

		// Сохраним все пути из нее
		for (int i = 1; i < N; i++) {
			if (Graph[0][i] != inf) {
				i_j_d.push_back(0);
				i_j_d.push_back(i);
				i_j_d.push_back(Graph[0][i]);
			}
		}
	}

	while (true) {

		// Выберем ближайшую вершину (ближайшую к одной из рассмотренных)
		int closestVertexIndex = -1;
		int closestVertexAmount = inf;
		int fromToclosestVertexIndex = -1;
		int indexinijd = -1;
		for (int i = 0; i < N; i++) {
			if (Visited[i]) {
				for (int j = 0; j < i_j_d.size(); j += 3) {
					if (i == i_j_d[j] && i_j_d[j + 2] < closestVertexAmount && !Visited[i_j_d[j + 1]]) {
						closestVertexAmount = i_j_d[j+2];
						closestVertexIndex = i_j_d[j+1];
						fromToclosestVertexIndex = i;
						indexinijd = j;
					}	
				}
			}
		}

		// Если не нашли не одной такой вершины
		if (closestVertexIndex == -1) {

			// Если не нашли не одной такой вершины и граф не обойден, то выдадим ошибку
			for (int i = 0; i < N; i++) {
				if (!Visited[i]) {
					cout << "Граф несвязный.\n";
					return;
				}
			}

			break;
		}

		// Если такая вершина найдина, но она не одна, создадим еще один вариант дерева, до этой вершины одинаковый с этим деревом
		for (int i = 2; i < i_j_d.size(); i += 3) {
			if (i_j_d[i] == closestVertexAmount && (i-1 != closestVertexIndex || i - 2 != fromToclosestVertexIndex) && Visited[i-2] && !Visited[i - 1]) {
				
				// Создаем такое дерево, до рассматриваемой вершины равное с ранее рассматриваемым деревом

				int** anotherDerevo = new int*[N];
				for (int i = 0; i < N; i++) {
					anotherDerevo[i] = new int[N];
				}
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						anotherDerevo[i][j] = Derevo[i][j];
					}
				}

				bool anotherVisited[N];
				for (int i = 0; i < N; i++) {
					anotherVisited[i] = Visited[i];
				}


				std::vector<int> anothervector;
				for (int j = 0; j < i_j_d.size(); j++) {
					anothervector[j] = i_j_d[j];
				}

				// В новом дереве идем к вершине i

				// Помечаем i, как пройденную
				anotherVisited[i] = true;

				// Удаляем путь до i
				anothervector.erase(anothervector.begin()+i-2, anothervector.begin()+i+1);

				// Сохраняем пути от i
				for (int j = 0; j < N; j++) {
					if (Graph[i][j] != inf && Graph[i][j] != 0) {
						anothervector.push_back(i);
						anothervector.push_back(j);
						anothervector.push_back(Graph[i][j]);
					}
				}

				// Обновляем вид дерева
				anotherDerevo[fromToclosestVertexIndex][i] = 1;
				anotherDerevo[i][fromToclosestVertexIndex] = 1;

				// Продолжаем сборку нового дерева параллельно сборке первого дерева
				PrimaSecond(anotherDerevo, anotherVisited, Graph, anothervector);

			}
		} // Конец блока "Если она не одна, создадим новый вариант дерева"

	
		// Далее случай, если нашли такую вершину и ровно одну

		// Помечаем вершину, как пройденную
		Visited[closestVertexIndex] = true;

		// Удаляем путь до нее
		i_j_d.erase(i_j_d.begin() + indexinijd, i_j_d.begin() + indexinijd+3);
		
		// Сохраняем пути от нее
		for (int j = 0; j < N; j++) {
			if (Graph[closestVertexIndex][j] != inf && Graph[closestVertexIndex][j] != 0 && !Visited[j]) {
				i_j_d.push_back(closestVertexIndex);
				i_j_d.push_back(j);
				i_j_d.push_back(Graph[closestVertexIndex][j]);
			}
		}
		
		// Обновляем вид дерева
		Derevo[fromToclosestVertexIndex][closestVertexIndex] = 1;
		Derevo[closestVertexIndex][fromToclosestVertexIndex] = 1;
	

		/*
		// Для тестирования
		cout << "i_j_d: ";
		for (int i = 0; i < i_j_d.size(); i += 1) {
			cout << i_j_d[i] << " ";
		}
		cout << endl;
		printmatrix(i_j_d);
		cout << "closestVertexIndex = " << closestVertexIndex << endl;
		cout << "closestVertexAmount = " << closestVertexAmount << endl;
		cout << "fromToclosestVertexIndex = " << fromToclosestVertexIndex << endl;
		cout << "Visited: ";
		for (int i = 0; i < N; i++) {
			cout << Visited[i] << " ";
		}
		cout << endl;
		*/

	}


	printmatrix(Derevo);
	cout << endl;

}

// Описание функции Dijkstra:
void Dijkstra(const int Graph[N][N], int start, int end) {

	// ------------------------------------------------------------------------------------
	// ----- ПОСТРОЕНИЕ МАССИВА ДЛИН КРАТЧАЙШИХ ПУТЕЙ ИЗ X1 В ОСТАЛЬНЫЕ ВЕРШИНЫ ГРАФА -----
	// ------------------------------------------------------------------------------------

	// Скопируем элементы Graph в новый динамический массив DGraph:
	int** DGraph = new int* [N];
	for (int i = 0; i < N; i++) {
		DGraph[i] = new int[N];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			DGraph[i][j] = Graph[i][j];
		}
	}

	// Объявление переменных:
	int ClosestUnvisitedVertexDistance; // Расстояние до ближайшей непосещенной вершины
	int ClosestUnvisitedVertexIndex; // Индекс ближайшей непосещенной вершины
	bool Visited[N]; // Посещенные вершины
	int* ShortestPath = new int[N]; // Длины кратчайших путей от X1 до вершин графа


	//Инициализация ShortestPath и Visited:
	for (int i = 0; i < N; i++) {
		ShortestPath[i] = inf;
		Visited[i] = false;
	}
	ShortestPath[start] = 0;

	// Основной цикл:
	do {

		// Изначально полагаем, что непосещенных вершин не осталось
		ClosestUnvisitedVertexDistance = inf;
		ClosestUnvisitedVertexIndex = -1;

		// Пробуем найти непосещенные вершины и выбираем ближайшую из них
		for (int i = 0; i < N; i++) {
			if ((!Visited[i]) && (ShortestPath[i] < ClosestUnvisitedVertexDistance))
			{
				ClosestUnvisitedVertexDistance = ShortestPath[i];
				ClosestUnvisitedVertexIndex = i;
			}
		}

		if (ClosestUnvisitedVertexIndex != -1) // Если непосещенная вершина нашлась
		{
			for (int i = 0; i < N; i++) {
				// Если есть путь между рассматриваемой вершиной и вершиной i, а также рассматриваемой вершина сама не является вершиной i:
				if (DGraph[ClosestUnvisitedVertexIndex][i] != 0 && DGraph[ClosestUnvisitedVertexIndex][i] != inf)
				{
					// Если путь от X1 до i, проходящий через рассматриваемую вершину, короче, чем ранее найденный кратчайший путь
					if (ShortestPath[i] > ClosestUnvisitedVertexDistance + DGraph[ClosestUnvisitedVertexIndex][i])
					{
						ShortestPath[i] = ClosestUnvisitedVertexDistance + DGraph[ClosestUnvisitedVertexIndex][i];
					}
				}
			}
			Visited[ClosestUnvisitedVertexIndex] = true; // Помечаем рассмотренную вершину как пройденную
		}
	} while (ClosestUnvisitedVertexDistance < inf); // Пока находятся непосещенные вершины

	// Вывод кратчайших расстояний до вершин
	cout << "Кратчайший путь из X1 до каждой из других вершин:\n";
	printmatrix(ShortestPath);

	// ---------------------------------------------------------------------
	// ----------- ВОССТАНОВЛЕНИЕ КРАТЧАЙШИХ ПУТЕЙ ИЗ X1 В X8 --------------
	// ---------------------------------------------------------------------


	int* visitedVertices = new int[N]; // Массив индексов вершин кратчайшего пути
	visitedVertices[start] = end;
	int k = 1; // Количество ребер в visitedVertices

	// Вызовем рекурсивную функцию, ищущую все кратчайшие пути от вершины startPosition до вершины endPosition, 
	// причем соединив любой из этих путей с подграфом visitedVertices, получим кратчайший путь от X1 до X8
	cout << "Все пути наименьшей стоимости из X1 в X8:\n";
	FindAllShortestPaths(start, end, visitedVertices, k, DGraph, ShortestPath);


	// Удалим использованные указатели:
	delete[] visitedVertices;
	delete[] ShortestPath;
	for (int i = 0; i < N; i++) {
		delete[] DGraph[i];
	}
	delete[] DGraph;

	/*  --------ОТКЛЮЧЕННЫЙ КОД--------
	* // Решение задачи в случае, если из X1 в X8 существует всего один кратчайший путь
	int ver[N];
	ver[start] = end;
	int k = 1;
	int weight = ShortestPath[end];

	while (end != start){
		for (int i = 0; i < N; i++)
			if (DGraph[i][end] != 0) // Если конечная вершина смежна с i-той
			{
				int PathToI = weight - DGraph[i][end];
				if (PathToI == ShortestPath[i])
				{
					weight = PathToI; //
					end = i;
					ver[k] = i;
					k++;
					break;
				}
			}
	}

	cout << "Кратчайший путь от X1 до X8:" << endl;
	for (int i = k - 1; i >= 0; i--) {
		cout << "X" << ver[i]+1;
		if (i != 0)cout << " -> ";
	}
	*  -------- ОТКЛЮЧЕННЫЙ КОД --------*/
}

void FindAllShortestPaths(int startPosition, int endPosition, int* visitedVertices, int k, int** DGraph, int* ShortestPath) {
	int ShortestPathToEndPosition = ShortestPath[endPosition]; // Длина кратчайшего пути от X1 до endPosition

	if (startPosition != endPosition) { // Если путь еще не составлен, и мы еще не дошли от X8 до X1
		for (int i = 0; i < N; i++)
			if (DGraph[i][endPosition] != 0) // Если вершина endPosition смежна с i-той
			{
				int PathToI = ShortestPathToEndPosition - DGraph[i][endPosition]; // Расстояние от X1 до i
				if (PathToI == ShortestPath[i]) // Если расстояние от X1 до i минимально возможное
				{
					// Создадим массив newVisitedVertices, являющийся копией массива visitedVertices с тем изменением,
					// что k-ое место в кратчайшем пути от X1 до X8 теперь занимает вершина i
					int* newVisitedVertices = new int[N];
					for (int i = 0; i < N; i++) {
						newVisitedVertices[i] = visitedVertices[i];
					}
					newVisitedVertices[k] = i;

					// Вызовем рекурсивную функцию для нового массива
					FindAllShortestPaths(startPosition, i, newVisitedVertices, k + 1, DGraph, ShortestPath);
				}
			}
	}
	else { // Если путь уже составлен, и мы уже дошли от X8 до X1
		for (int i = k - 1; i >= 0; i--) {
			cout << "X" << visitedVertices[i] + 1;
			if (i != 0)cout << " -> ";
		}
		cout << endl;
	}
}


// Описание функции FloydWarshall:
void FloydWarshall(const int Graph[N][N], int start, int end) {

	// ---------------------------------------------------------------------
	// ---------- ПОСТРОЕНИЕ МАТРИЦЫ СТОИМОСТИ КРАТЧАЙШИХ ПУТЕЙ ------------
	// ---------------------------------------------------------------------


	// Скопируем элементы Graph в новый массив FWGraph
	int FWGraph[N][N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			FWGraph[i][j] = Graph[i][j];
		}
	}

	// Основной цикл
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {

				if (FWGraph[i][k] + FWGraph[k][j] < FWGraph[i][j]) {

					FWGraph[i][j] = FWGraph[i][k] + FWGraph[k][j];

				}
			}
		}
	}

	// Массив эксцентриситетов
	int ekszentrisitet[N];

	int radius = inf;
	int diametr = -1;

	// Изначально инициализируем массив эксцентрисетов минус единицами
	for (int i = 0; i < N; i++) {
		ekszentrisitet[i] = -1;
	}

	// Заполняем массив эксцентриситетов
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (ekszentrisitet[i] < FWGraph[i][j] && FWGraph[i][j] != inf) {
				ekszentrisitet[i] = FWGraph[i][j];
			}
		}
	}



	// Выведем FWGraph
	cout << "Матрица стоимости кратчайших путей:\n";
	printmatrix(FWGraph);

	cout << "Маcсив эксцентриситетов:\n";
	printmatrix(ekszentrisitet);

	for (int i = 0; i < N; i++) {
		if (ekszentrisitet[i] < radius) {
			radius = ekszentrisitet[i];
		}
		if (ekszentrisitet[i] > diametr) {
			diametr = ekszentrisitet[i];
		}
	}

	cout << "Радиус = " << radius << ", диаметр = " << diametr << ", центры: ";



	for (int i = 0; i < N; i++) {
		if (ekszentrisitet[i] == radius) {
			cout << "X" << i + 1 << " ";
		}
	}

	cout << endl << endl;
	/* -------- ОТКЛЮЧЕННЫЙ КОД --------
	* // Составление массива предков

	// Массив предков
	int p[N][N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			p[i][j] = inf;
		}
	}

	p[i][j] = k;

	printgraph(p);

	* -------- ОТКЛЮЧЕННЫЙ КОД --------*/
}


// Описание функции printmatrix для матриц размера NxN:
void printmatrix(const int arr[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (arr[i][j] != inf) cout << arr[i][j] << "\t";
			else cout << "inf\t";
		}
		cout << endl;
	}
	cout << endl;
}

void printmatrix(int** arr) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (arr[i][j] != inf) cout << arr[i][j] << "\t";
			else cout << "inf\t";
		}
		cout << endl;
	}
	cout << endl;
}

// Описание функции printmatrix для матриц размера 1xN:
void printmatrix(const int arr[N]) {
	for (int i = 0; i < N; i++) {
		if (arr[i] != inf) cout << arr[i] << "\t";
		else cout << "inf\t";
	}
	cout << endl << endl;
}
// Описание функции printmatrix для матриц размера 1xN:
void printmatrix(const bool arr[N]) {
	for (int i = 0; i < N; i++) {
		if (arr[i] != inf) cout << arr[i] << "\t";
		else cout << "inf\t";
	}
	cout << endl << endl;
}

void printmatrix(std::vector<int> i_j_d) {
	for (int i = 0; i < i_j_d.size(); i++) {
		if (i % 3 == 0 && i!=0) {
			cout << endl;
		}
		cout << i_j_d[i] << " ";
	}
	cout << endl ;
}

/*-------- ОТКЛЮЧЕННЫЙ КОД --------
старый примасеконд
	// Создадим копию уже созданной части остовного дерева (так как их может быть несколько с этой общей частью)
	int Derevo[N][N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Derevo[i][j] = DerevoPreviousPart[i][j];
		}
	}

	// Аналогично создадим копию массива посещенных вершин
	bool Visited[N];
	for (int i = 0; i < N; i++) {
		Visited[i] = VisitedPrevious[i];
	}

	// Алгоритм Прима
	while(true) {

		// Найдем вершину i, уже расмотренную, у которой наименьший эксцентриситет к одной из нерассмотренных вершин
		// Если такой вершины нет, завершаем алгоритм
		int i = inf;
		int minIndex = -1;
		int minAmount = inf;
		for (int j = 0; j < N; j++) {
			if (Visited[j]) {
				for (int k = 0; k < N; k++) {
					if (Graph[j][k] != inf && Graph[j][k] != 0 && !Visited[k]) {
						if (Graph[j][k] < minAmount) {
							minAmount = Graph[j][k];
							minIndex = k;
							i = j;
						}
					}
				}
			}
		}
		if (i == inf) {
			for (int j = 0; j < N; j++) {
				if (!Visited[j]) {
					i = j;
					break;
				}
			}
		}
		if (i == inf) {
			break;
		}


		cout << "---------------------------------------------------------------" << endl;
		cout << " Рассчитанный i = " << i << endl;
		cout << " Расчитанный путь minAmount = " << minAmount << endl;
		cout << " Расчитанный путь minIndex = " << minIndex << endl;

		// i-ая вершина нашлась, продолжаем алгоритм
		if (!Visited[minIndex]) {
			cout << "Зашли в цикл от вершины i=" << i << endl;

			// Индекс блишайшей к i вершины:
			int ClosestVertexIndex = -1;
			// Значение блишайшей к i вершины:
			int ClosestVertexAmount = -1;

			// Находим индекс и значение ближайшей вершины:
			for (int j = 0; j < N; j++) {
				if (Graph[i][j] != inf && Graph[i][j] != 0 && !Visited[j]) {
					if (ClosestVertexIndex == -1) {
						ClosestVertexIndex = j;
						ClosestVertexAmount = Graph[i][j];
					}
					else if (Graph[i][j] < ClosestVertexAmount) {
						ClosestVertexIndex = j;
						ClosestVertexAmount = Graph[i][j];
					}
				}
			}

			cout << "Посчитанный индекс ближайшей вершины: " << ClosestVertexIndex << endl;
			cout << "Посчитанный значение ближайшей вершины: " << ClosestVertexAmount << endl;

			// Если не нашлось ближайшей вершины (все смежные уже пройдены)
			if (ClosestVertexIndex == -1) {
				continue;
			}

			// Значение кратчайшего пути к ближайшей вершине, идя из других уже пройденных вершин:
			int AnotherPathAmout = inf;
			int AnotherPathIndex = -1;

			// Вычислим AnotherPathAmount
			for (int j = 0; j < N; j++) {
				if (j == ClosestVertexIndex)continue;
				if (j == i)continue;
				if (Visited[j]) {
					if (Graph[j][ClosestVertexIndex] < AnotherPathAmout) {
						AnotherPathAmout = Graph[j][ClosestVertexIndex];
						AnotherPathIndex = j;
					}
				}
			}

			cout << "Посчитанный индекс из других вершин: " << AnotherPathIndex << endl;
			cout << "Посчитанное значение из других вершин: " << AnotherPathAmout << endl;

			if (i == 0) {
				Visited[i] = true;
			}

			if (AnotherPathIndex == -1) { // Если через другие рассмотренные вершины нет путей
				Visited[ClosestVertexIndex] = true;
				Derevo[i][ClosestVertexIndex] = 1;
				Derevo[ClosestVertexIndex][i] = 1;
			}
			else {
				if (ClosestVertexAmount < AnotherPathAmout) { // Если путь из i-ой вершины короче, чем из других
					Visited[ClosestVertexIndex] = true;
					Derevo[i][ClosestVertexIndex] = 1;
					Derevo[ClosestVertexIndex][i] = 1;
				}
				else if (ClosestVertexAmount > AnotherPathAmout){ // Если путь из другой вершины короче, чем из i-ой

					// Подсчитаем количество таких путей
					int count = 0;
					for (int j = 0; j < N; j++) {
						if (j == ClosestVertexIndex || j == AnotherPathIndex)continue;

						if (Visited[j]) {
							if (Graph[j][AnotherPathIndex] == AnotherPathAmout) {
								count += 1;
							}
						}
					}

					if (count == 1) {
						Visited[ClosestVertexIndex] = true;
						Derevo[i][ClosestVertexIndex] = 1;
						Derevo[ClosestVertexIndex][i] = 1;
					}
					else if (count > 1) {
						cout << "ERROR_1" << endl;
						printmatrix(Derevo);
						return;
					}
				}
				else {
					cout << "ERROR_2" << endl;
					printmatrix(Derevo);
					return;
				}
			}
		}

		else {
			cout << "Не зашли в цикл от вершины i=" << i << endl;
			cout << "---------------------------------------------------------------" << endl;
		}


		cout << "Derevo:\n";
		printmatrix(Derevo);
		cout << "Visited:\n";
		printmatrix(Visited);
		cout << "---------------------------------------------------------------" << endl;


	}

	printmatrix(Derevo);
	*/