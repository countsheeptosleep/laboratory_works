# Лабораторные работы / Laboratory works
Лабораторные работы на C++ для института
____
*Laboratory works in C++ for the institute*


## 1️⃣ Графы / Graphs (lr_graphs):

Для взвешенного ориентированного графа реализовать:
- алгоритм поиска кратчайшего пути - алгоритм Дейкстры
- сделав тот же самый граф неориентированным, построить его остовное дерево минимальной стоимости - алгоритм Прима

Должны быть представлены промежуточные результаты.
По каждому кратчайшему пути указать предшествующие вершины.
____
*For a weighted directed graph, implement:*
- *algorithm for finding the shortest path - Dijkstra's algorithm*
- *making the same graph undirected, build its minimum cost spanning tree - Prim's algorithm*

*Intermediate results must be presented.*
*For each shortest path, indicate the previous vertices.*

**[код](https://github.com/countsheeptosleep/laboratory_works/blob/main/lr_graphs.cpp)**

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

## 3️⃣ Списки / Lists (lr_lists):
Реализовать линейный список, состоящий из 20 элементов заданного типа. Интерфейс должен включать следующие операции:
- создание списка;
- вывод на экран и/или в файл значений элементов списка с их индексами (номерами);
- удаление списка,
- Поиск в списке элемента с максимальным значением с получением его номера в списке (повторное вхождение одного и того же значения разрешено)
- Включение нового элемента в начало списка.
- Удаление элемента из начала списка.
После выполнения операций включения или удаления вывести содержимое списка. Выполнение операций организовать с помощью меню.
____
*Implement a linear list consisting of 20 elements of a given type. The interface must include the following operations:*
- *creating a list;*
- *output to the screen and/or to a file the values of the list elements with their indices (numbers);*
- *deleting the list,*
- *Search in the list for the element with the maximum value and get its number in the list (repeated occurrence of the same value is allowed)*
- *Inclusion of a new element in the beginning of the list.*
- *Removing an element from the beginning of the list.*
*After performing the include or remove operations, display the contents of the list. Organize operations using the menu.*

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
