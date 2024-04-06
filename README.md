# Алгоритмы и структуры данных на C++
В рамках курса "Алгоритмы и структуры данных" (2022)_

## 1️⃣ Графы / Graphs (lr_graphs):

Для взвешенного ориентированного графа реализовать:
- алгоритм поиска кратчайшего пути - алгоритм Дейкстры
- сделав тот же самый граф неориентированным, построить его остовное дерево минимальной стоимости - алгоритм Прима

Должны быть представлены промежуточные результаты.
По каждому кратчайшему пути указать предшествующие вершины.

**💻 [Открыть код](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_graphs.cpp)**
____
*For a weighted directed graph, implement:*
- *algorithm for finding the shortest path - Dijkstra's algorithm*
- *making the same graph undirected, build its minimum cost spanning tree - Prim's algorithm*

*Intermediate results must be presented.*
*For each shortest path, indicate the previous vertices.*

**💻 [Open code](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_graphs.cpp)**

## 2️⃣ Очереди / Queues (lr_queues):
Программно реализовать очередь с приоритетами в виде линейного списка с символьными элементами.
Выполнение операций организовать с помощью меню:
- создание очереди;
- вывод на экран или в файл значений элементов очереди с их индексами (номерами) и приоритетами;
- включение в очередь нового элемента;
- очистка очереди, 
- вывод элементов очереди с заданным значением приоритета.
После выполнения операций включения или выборки вывести новое содержимое очереди. 

Приоритеты задать произвольно в виде целых чисел. Наивысший приоритет у меньшего значения. Совпадение приоритетов - разрешено

**💻 [Открыть код](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_queues.cpp)**
____
*Implement a priority queue as a linear list with character elements.*
*Organize operations using the menu:*
- *creating a queue;*
- *output to the screen or to a file the values of the elements of the queue with their indices (numbers) and priorities;*
- *inclusion in the queue of a new element;*
- *clearing the queue*
- *output queue elements with a given priority value.*
*After the include or fetch operations are performed, output the new contents of the queue.*

*Priorities can be set arbitrarily as integers. The lowest value has the highest priority. Priority match - allowed*

**💻 [Open code](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_queues.cpp)**

## 3️⃣ Списки / Lists (lr_lists):
Реализовать линейный список, состоящий из 20 элементов заданного типа. Интерфейс должен включать следующие операции:
- создание списка;
- вывод на экран и/или в файл значений элементов списка с их индексами (номерами);
- удаление списка,
- Поиск в списке элемента с максимальным значением с получением его номера в списке (повторное вхождение одного и того же значения разрешено)
- Включение нового элемента в начало списка.
- Удаление элемента из начала списка.
После выполнения операций включения или удаления вывести содержимое списка. Выполнение операций организовать с помощью меню.

**💻 [Открыть код](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_lists.cpp)**
____
*Implement a linear list consisting of 20 elements of a given type. The interface must include the following operations:*
- *creating a list;*
- *output to the screen and/or to a file the values of the list elements with their indices (numbers);*
- *deleting the list,*
- *Search in the list for the element with the maximum value and get its number in the list (repeated occurrence of the same value is allowed)*
- *Inclusion of a new element in the beginning of the list.*
- *Removing an element from the beginning of the list.*
*After performing the include or remove operations, display the contents of the list. Organize operations using the menu.*

**💻 [Open code](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_lists.cpp)**

## 4️⃣ Поиск / Search (lr_search):
Цель работы - изучить основные принципы работы алгоритмов поиска, исследовать их свойства: 
- алгоритм BLS - последовательный поиск (Better_Linear_Search);
- алгоритм SLS - быстрый последовательный поиск (Sentinel_Linear);
- алгоритм Т - последовательный поиск в упорядоченном массиве, в конце массива помещается фиктивная запись, значение которой намного больше значения ключа поиска;
- алгоритм В - бинарный поиск.

Задание
- Для алгоритмов BLS и SLS в качестве входного массива использовать одну и ту же последовательность значений (функция rand( )).
- Для алгоритмов Т и В – значения массива должны быть отсортированы по неубыванию, одна и та же последовательность чисел (можно использовать соответствующую функцию из первой лабораторной работы). 
- Оценить длительность поиска для различных значений размеров последовательностей (начиная с 10000 до 200000 элементов массива, провести измерения не менее, чем для 10 разных размерностей).
- Для каждой размерности рассматриваются случаи нахождения ключа поиска в начале, в середине и в конце массива.
- Для алгоритмов BLS и SLS кроме подсчета времени, необходимого для поиска, требуется определить сколько раз выполняются операции сравнения (сравнение ключа с элементом массива, а также в одном из этих двух алгоритмов добавляется подсчет сравнений при анализе индекса элемента массива в цикле… ).

**💻 [Открыть код](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_search.cpp)**
____

*The purpose of the work is to study the basic principles of the search algorithms, to explore their properties:*
- *BLS algorithm - sequential search (Better_Linear_Search);*
- *SLS algorithm - fast sequential search (Sentinel_Linear);*
- *algorithm T - sequential search in an ordered array, a dummy entry is placed at the end of the array, the value of which is much greater than the value of the search key;*
- *Algorithm B - binary search.*

*Exercise*
- *For the BLS and SLS algorithms, use the same sequence of values as the input array (the rand( ) function).*
- *For algorithms T and B - the array values must be sorted in non-decreasing order, the same sequence of numbers (you can use the corresponding function from the first laboratory work).*
- *Estimate the duration of the search for different sizes of sequences (starting from 10,000 to 200,000 array elements, take measurements for at least 10 different dimensions).*
- *For each dimension, the cases of finding the search key at the beginning, in the middle and at the end of the array are considered.*
- *For the BLS and SLS algorithms, in addition to counting the time required for the search, it is required to determine how many times comparison operations are performed (comparison of the key with an array element, and also in one of these two algorithms, a count of comparisons is added when analyzing the index of an array element in a loop ...).*

**💻 [Open code](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_search.cpp)**

## 5️⃣ Массивы / Arrays (lr_arrays):

Цель: Дан одномерный целочисленный массив AVec. Найти
минимальный элемент среди положительных. После него сдублировать все
отрицательные элементы.

Предупреждение: В случае, когда есть несколько равных минимальных
положительных элементов, дублировать все отрицательные элементы только
после первого из них.

**💻 [Открыть код](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_arrays.cpp)**
____
*Purpose: Given a one-dimensional integer array AVec. Find*
*the smallest element among the positive ones. After it, duplicate everything
negative elements.*

*Warning: In the case where there are several equal minimum
positive elements, duplicate all negative elements only
after the first one.*

**💻 [Open code](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_arrays.cpp)**

## 6️⃣ Графы 2 / Graphs 2 (lr_graphs_2):
Реализовать:
- Поиск всех кратчайших путей между двумя вершинами
- Поиск радиуса, диаметра и центров графа
- Построить все остовные деревья минимального веса (считая граф неориентированным)

Использовать алгоритмы:
- Дейкстры
- Флойда — Уоршелла
- Прима

**💻 [Открыть код](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_graphs_2.cpp)**
____
Implement:
- Finding all shortest paths between two vertices
- Finding the radius, diameter and centers of the graph
- Construct all spanning trees of minimum weight (assuming the graph is undirected)

Use algorithms:
- Dijkstra
- Floyd-Warshall
- Prima

**💻 [Open code](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_graphs_2.cpp)**

## 7️⃣ Индексная сортировка / Index sort (lr_index_sort):
Реализовать структуру данных "Самолет":
- Марка
- Бортовой номер
- Номер рейса
- Время посадки

Осуществить считывание данных с **входным контролем**.

Произвести индексную сортировку:
- по номеру рейса
- по времени посадки

**💻 [Открыть код](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_index_sort.cpp)**
____

Implement the "Airplane" data structure:
- Brand
- Board number
- Flight number
- Landing time

Perform data reading with **input control**.

Perform an index sort:
- by flight number
- by landing time

**💻 [Open code](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_index_sort.cpp)**

## 8️⃣ Матрицы / Matrices (lr_matrices):
Реализовать:

- ввод квадратной матрицы из консоли с **входным контролем**
- ввод квадратной матрицы из файла с **входным контролем**
- заполнение квадратной матрицы случайными числами
- нахождение суммы отрезков строк до главной диагонали в которых нет отрицательных элементов, а также строки с минимальной такой суммой

**💻 [Открыть код](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_matrices.cpp)**
____
Implement:

- square matrix input from console with **input control**
- input of a square matrix from a file with **input control**
- filling a square matrix with random numbers
- finding the sum of line segments up to the main diagonal in which there are no negative elements, as well as lines with the minimum such sum

**💻 [Open code](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_matrices.cpp)**

## 9️⃣ Строки / Strings (lr_strings):

Работа со строками в виде массива char.

Реализовать:
- Ввод из консоли с **входным контролем**
- Ввод из файла с **входным контролем**
- Функция очистки строки
- Поиск слова в строке
- Удаление повторяющихся слов
- Сравнение двух слов из двух строк
- Печать слова из строки
- Удаление слова
- Нахождение слов, встречающихся в двух строках
- Подсчет количества появлений элемента в двух строках

**💻 [Открыть код](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_strings.cpp)**
____

Working with strings as an array of char.

Implement:
- Input from console with **input control**
- Input from file with **input control**
- Line cleaning function
- Search for a word in a string
- Remove duplicate words
- Comparing two words from two strings
- Printing a word from a string
- Deleting a word
- Finding words occurring in two strings
- Counting the number of occurrences of an element in two lines

**💻 [Open code](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_strings.cpp)**
