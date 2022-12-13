#include <iostream>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <stdio.h> 
#include <time.h> 
using namespace std;

// Объявление глобальных переменных:
const int min_array_length = 10000; // Минимальный размер массива среди опытов
const int max_array_length = 200000; // Максимальный размер массива среди опытов
const int number_of_measurements = 10;  // Число опытов 
const int number_of_search_functions = 4; // Число функций поиска
const int number_of_search_element_positions = 3; // Число различных положений искомого элемента в массиве
const string search_element_positions[number_of_search_element_positions] = { "beginning","center","ending" }; // Положения искомого элемента в массиве
int measurements_comparisons[number_of_measurements * number_of_search_functions * number_of_search_element_positions]; // Дополнительный массив в котором будут числа сравнений из каждого опыта.
int measurements_comparisons_index = 0; // Его индекс
const string file_name = "measurements.txt"; // Файл с результатами опытов (время)
const string file2_name = "measurements2.txt"; // Файл с результатами опытов (перестановки)


// Объявление функций поиска:
void BLS(int* array, int length, string search_element_position); // Better Linear Search
void SLS(int* array, int length, string search_element_position); // Sentinel Linear
void T(int* array, int length, string search_element_position); // Последовательный поиск в упорядоченном массиве
void B(int* array, int length, string search_element_position); // Binary Search

// Объявление дополнительных функций:
int get_function_time(void (*func)(int* array, int length, string search_element_position), int* array, int length, string key_position); // Получение времени работы функции
void generate_random_unsorted_array(int* array, int length); // Заполняет массив случайными числами
void generate_random_sorted_array(int* array, int length); // Заполняет массив случайными числами так, чтобы он оказался отсортирован по неубыванию
int choose_search_element(int* array, int length, string search_element_position); // Выбирает искомый элемент в массиве

// Основная программа:
int main()
{
	// Зададим сид, зависящий от текущего времени, для функции генерации случайных чисел:
	srand((unsigned)time(NULL));

	// Установим русский язык:
	setlocale(LC_ALL, "Russian");

	// Объявление переменных:
	int* unsorted_array; // Неотсортированный массив случайных чисел
	int* sorted_array; // Отсортированный по неубыванию массив случайных чисел
	void (*search_functions[number_of_search_functions])(int* array, int length, string key_position) = {BLS , SLS, T, B}; // Массив функций поиска
	int*** measurements = new int**[number_of_measurements]; // Массив записей результатов опытов
	fstream file; // Поток ввода в файл времени работы при разных размерах массива
	fstream file2; //  Поток ввода в файл числа перестановок при разных размерах массива

	// Подготовим файл для заполения результатами опыта:
	file.open(file_name);
	file2.open(file2_name);

	// Проведем измерения 
	for (int i=0; i < number_of_measurements; i++) {

		// Создадим запись об i-ом опыте:
		measurements[i] = new int*[number_of_search_functions];

		// Размер массива в i-ом опыте:
		int array_length = min_array_length + i * (max_array_length - min_array_length) / number_of_measurements;

		// Выделим память для массивов:
		unsorted_array = new int[array_length];
		sorted_array = new int[array_length]; 

		// Заполним массивы в соответствии с их назначением:
		generate_random_unsorted_array(unsorted_array, array_length); // Случайные числа
		generate_random_sorted_array(sorted_array, array_length); // Случайные числа с сортировкой по неубыванию

		// Переберем все функции и для каждой из них проведем опыт при i-ом размере массива:
		for (int j = 0; j < number_of_search_functions; j++) {

			// Выделим память для записей о j-ой функции в i-ом опыте при разных положениях искомого элемента:
			measurements[i][j] = new int[number_of_search_element_positions];

			// Проведем опыт при i-ом размере массива для j-ой функции при разных k-ых значениях искомого элемента:
			for (int k = 0; k < number_of_search_element_positions; k++) {
				
				// Для функий поиска BLS и SLS будем передавать неотсортированный массив:
				if (search_functions[j] == BLS || search_functions[j] == SLS) {
					measurements[i][j][k] = get_function_time(search_functions[j], unsorted_array, array_length, search_element_positions[k]);
					file << measurements[i][j][k] << " ";
					file2 << measurements_comparisons[measurements_comparisons_index] << " "; 
					measurements_comparisons_index++;
				}

				// Для функий поиска T и B будем передавать отсортированный по неубыванию массив:
				else if (search_functions[j] == T || search_functions[j] == B) {
					measurements[i][j][k] = get_function_time(search_functions[j], sorted_array, array_length, search_element_positions[k]);
					file << measurements[i][j][k] << " ";
					file2 << measurements_comparisons[measurements_comparisons_index] << " ";
					measurements_comparisons_index++;
				}

				// Если в программу была добавлена какая-то функция и для нее не определили, какого вида массив ей следует подавать, то выдается ошибка:
				else {
					cout << "Ошибка. Используется функция, для которой не определено, какого вида массив ей следует подавать: отсортированный или неотсортированный. Номер этой функции в массиве функций: " << j << ".\n";
					return 1;
				}



			} // Конец блока перебора k значений ключа

		} // Конец блока перебора всех функций

	} // Конец блока перебора всех размеров массива

	return 0;
}

// Выбор ключа в массиве:
int choose_search_element(int* array, int array_length, string search_element_position) {

	// Объявление переменных:
	int zone_start_index; // Индекс начала некоторой зоны массива
	int zone_end_index; // Индекс конца некоторой зоны массива
	int zone_length; // Длина зоны
	int search_element_index; // Индекс искомого элемента
	int search_element; // Искомый элемента

	// Выбор ключа:
	if (search_element_position == "beginning") { // Зона "Начало массива"

		// Для текущей зоны найдем ее границы:
		zone_start_index = 0 * (array_length / 10);
		zone_end_index = 1 * (array_length / 10);

	} 
	else if (search_element_position == "center") { // Зона "Центер массива

		// Для текущей зоны найдем ее границы:
		zone_start_index = 4 * (array_length / 10);
		zone_end_index = 6*(array_length / 10);

	}
	else if (search_element_position == "ending") { // Зона "Конец массива"

		// Для текущей зоны найдем ее границы:
		zone_start_index = 9 * (array_length / 10);
		zone_end_index = 10 * (array_length / 10);

	}
	else {
		
		cout << "Ошибка. Используется зона, для которой в коде не определены ее границы. Это зона: " << search_element_position << ".\n";
		exit(0);

	}

	// Длина текущей зоны:
	zone_length = zone_end_index - zone_start_index;

	// Выберем случайный индекс из заданной зоны:
	search_element_index = (rand() % (zone_length + 1)) + zone_start_index - 1;

	// По индексу найдем ключ:
	search_element = array[search_element_index];

	cout << "Ищем элемент с индексом " << search_element_index << " и значением " << search_element << " алгоритмом ";

	for (int i = 0; i < array_length; i++) {
		if ((i < search_element_index) && (array[i] == search_element)) {
			array[i] = search_element - 1;
		}
	}

	return search_element;

}

// Better Linear Search:
void BLS(int* array, int length, string search_element_position) {

	
	// Объявление переменных:
	int position = 0; // Позиция поиска
	bool found = false; // Отображает найден ли искомый элемент
	int search_element = choose_search_element(array, length, search_element_position); // Искомый элемента
	int number_of_comparisons = 0; // Число сравнений

	// Перебираем эл-ты массива, пока он не кончится или пока не найден искомый элемент:
	while ((position < length) && !found) {

		// Если текущий элемент равен искомому элементу:
		if (array[position] == search_element) {

			// Отображаем, что мы нашли искомый элемент:
			found = true;

		}
		// Если текущий	эл-т не равен искомому элементу:
		else {

			// Сдвигаемся на одну позицию вперед
			position++;

		}

		// Сделали одно сравнение:
		number_of_comparisons+=2;

	} // Конец цикла перебора эл-тов массива

	// Печать информации об исходных данных опыта:
	cout << "BLS длина_массива=" << length << " расположение_искомого_элемента=" << search_element_position << " ";

	// Печать информации о результах опыта:
	if (!found) { // Если искомый элемент не найден

		cout << "искомый элемент не найден.";
		exit(0);
	}
	else { // Если искомый элемент найден

		//cout << "искомый элемент найден";
		
		cout << "число_сравнений " << number_of_comparisons << " ";

		cout << "TOFIND=" << search_element << "~FOUND=" << array[position] << "~POS=" << position << " ";
		measurements_comparisons[measurements_comparisons_index] = number_of_comparisons;

	}

}

// Sentinel Linear Search:
void SLS(int* array, int length, string search_element_position) {

	// Объявление переменных:
	int last = array[length - 1]; // Значение последнего элемента
	int search_element = choose_search_element(array, length, search_element_position); // Искомый элемент
	int number_of_comparisons = 0; // Число сравнений
	int i = 0; // Итератор

	// Присвоим последнему элементу массива значение искомого элемента:
	array[length - 1] = search_element;

	// Перебираем элементы массива, пока не найдем равный искомому элементу:
	while (array[i] != search_element) {
		i++;
		number_of_comparisons++;
	}

	// Вернем на место значение последнего элемента:
	array[length - 1] = last;

	// Печать информации об исходных данных опыта:
	cout << "SLS длина_массива=" << length << " расположение_искомого_элемента=" << search_element_position << " ";

	// Печать информации о результах опыта:
	if ((i < length - 1) || (array[length - 1] == search_element)) { // Если искомый элемент найден

		//cout << "искомый элемент найден";

		cout << "число_сравнений " << number_of_comparisons << " ";
		cout << "TOFIND=" << search_element << "~FOUND=" << array[i] << "~POS=" << i << " ";
		measurements_comparisons[measurements_comparisons_index] = number_of_comparisons;
	}
	else { // Если искомый элемент не найден 

		cout << "искомый элемент не найден.";
		exit(0);
	}
		

}

// T - Последовательный поиск в упорядоченном массиве:
void T(int* array, int length, string search_element_position) {

	/*
	for (int i = 0; i < length; i++) {
		cout << array[i] << " ";
	}
	cout << endl;*/

	// Объявление переменных:
	int search_element = choose_search_element(array, length, search_element_position); // Искомый элемент
	int i = 0; // Итератор

	if (array[length - 1] < search_element) {

		cout << "Ошибка. Элемент, поиск которого введется, больше последнего элемента в неубывающем массиве.";
		cout << array[length - 1] << " " << search_element;
		exit(0);
	}

	while (search_element > array[i]) {
		i++;
	}

	// Печать информации об исходных данных опыта:
	cout << "T длина_массива=" << length << " расположение_искомого_элемента=" << search_element_position << " ";

	// Печать информации о результах опыта:
	if ((i < length - 1) || (array[length - 1] == search_element)) { // Если искомый элемент найден

		//cout << "искомый элемент найден";
		cout << "TOFIND=" << search_element << "~FOUND=" << array[i] << "~POS=" << i << " ";
		measurements_comparisons[measurements_comparisons_index] = 0;
	}
	else { // Если искомый элемент не найден 

		cout << "искомый элемент не найден.";
		exit(0);
	}
}

// Binary Search:
void B(int* array, int length, string search_element_position) {

	// Объявление переменных:
	int p = 0;
	int n = length;
	int q;
	int search_element = choose_search_element(array, length, search_element_position); // Искомый элемент
	bool found = false;

	while (p <= n) {

		q = (p + n) / 2;

		if (array[q] == search_element) {

			found = true;
			break;

		}
		else {

			if (array[q] > search_element) {

				n = q - 1;

			}
			else {

				p = q + 1;

			}

		}

	}

	if (array[q + 1] == search_element || array[q - 1] == search_element) {
		found = true;
	}

	// Печать информации об исходных данных опыта:
	cout << "B длина_массива=" << length << " расположение_искомого_элемента=" << search_element_position << " ";

	// Печать информации о результах опыта:
	if (!found) { // Если искомый элемент не найден

		cout << "искомый элемент не найден.";
		exit(0);
	}
	else { // Если искомый элемент найден

		//cout << "искомый элемент найден.";
		cout << "TOFIND=" << search_element << "~FOUND=" << array[q] << "~POS=" << q << " ";
		measurements_comparisons[measurements_comparisons_index] = 0;
	}

}

// Получение времени работы функции:
int get_function_time(void (*func)(int* array, int length, string search_element_position), int* array, int length, string key_position) {

	
	// Запустим отсчет времени
	auto begin = std::chrono::steady_clock::now();

	// Вызовем функцию
	func(array, length, key_position);

	// Завершим отсчет времени
	auto end = std::chrono::steady_clock::now();

	// Высчитаем, сколько прошло времени
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end-begin); 

	// Напечатаем результат
	std::cout << " время_работы=" << elapsed_ms.count() << " (мкС)" << std::endl << endl;

	// Вернем результат
	return elapsed_ms.count();
	

	/*
	clock_t start = clock();
	func(array, length, key_position);
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << " время_работы=" << seconds * 1000 << " (мкС)" << std::endl << endl;
	return seconds * 1000;
	

	
	time_t start, end;
  
	time(&start);
	func(array, length, key_position);
	time(&end);
  
	double seconds = difftime(end, start);
	std::cout << " время_работы=";
	printf("time taken for function() %.2lf seconds.\n", seconds);
	cout << " (мкС)" << std::endl << endl;
	return seconds ;
	*/
	

}

// Заполняет массив случайными числами:
void generate_random_unsorted_array(int* array, int length) {

	const int MAX = 10000;
	const int MIN = 100;
	srand((unsigned)time(NULL));
	for (int* i = array; i != array + length; i++) {
		*i = rand() % MAX + MIN;
	}

}

// Заполняет массив случайными числами так, чтобы он оказался отсортирован по неубыванию:
void generate_random_sorted_array(int* array, int length) {

	const int MAX = 10;
	srand((unsigned)time(NULL));
	for (int i = 0; i < length; i++) {
		if (i == 0) {
			array[i] = rand() % MAX;
			continue;
		}
		array[i] = rand() % MAX + array[i - 1];
	}

}