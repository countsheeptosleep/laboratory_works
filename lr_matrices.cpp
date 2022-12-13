
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;

// Глобальные константы
const int k_max_matrix_size = 5; // Максимальный размер стороны квадратной матрицы
const char k_reading_method = '3'; // Метод чтения данных. '1' - консоль, '2' - файл, '3' - случайные числа
const string k_file_name = "File.txt"; // Имя файла исходных данных 


// Прототипы функций
void read_data_from_console(int*** pointer_to_pointer_to_dynamic_matrix, int& dynamic_matrix_size);
void read_data_from_file(int*** pointer_to_pointer_to_dynamic_matrix, int& dynamic_matrix_size);
void fill_with_random_numbers(int*** pointer_to_pointer_to_dynamic_matrix, int& dynamic_matrix_size);
void calculation_of_sums(int** dynamic_matrix, const int& dynamic_matrix_size);


// Основная программа
int main() {



    /// ---------------------------------------------------------------------------
    /// ---------------------------------- ПЕРВАЯ ЧАСТЬ ---------------------------
    /// ----------------------- Объявление переменных, ввод данных ----------------
    /// ---------------------------------------------------------------------------



    // Подключение русского языка
    setlocale(LC_ALL, "Russian");



    // Настроим функцию генерации случайных чисел
    srand(time(NULL));



    // Объявление переменных: 
    int** dynamic_matrix = NULL; // Матрица
    int dynamic_matrix_size; // Размер матрицы




    // Ввод данных 
    switch (k_reading_method){
    case '1': // ЧТЕНИЕ ИЗ КОНСОЛИ

        // Считывание данных из консоли:
        read_data_from_console(&dynamic_matrix, dynamic_matrix_size);

        break;

    case '2': // ЧТЕНИЕ ИЗ ФАЙЛА

        // Считывание данных из файла:
        read_data_from_file(&dynamic_matrix, dynamic_matrix_size);

        break;

    case '3': // ЗАПОЛНЕНИЕ СЛУЧАЙНЫМИ ЧИСЛАМИ

        // Заполним матрицу случайными числами:
        fill_with_random_numbers(&dynamic_matrix, dynamic_matrix_size);

        break;

    } // Конец блока "Ввод данных"



    /// ---------------------------------------------------------------------------
    /// ---------------------------------- ВТОРАЯ ЧАСТЬ ---------------------------
    /// ------------------------ Считаем требуемые в задачи суммы -----------------
    /// ---------------------------------------------------------------------------



    // Подсчитаем требуемые суммы:
    calculation_of_sums(dynamic_matrix, dynamic_matrix_size);


    return 0;


}



// Функция чтения данных из консоли
void read_data_from_console(int*** pointer_to_pointer_to_dynamic_matrix, int& dynamic_matrix_size) {

    cout << "\nВвод данных из консоли\n\n";

    // Размер матрицы: Ввод
    cout << "Введите размер матрицы: ";
    cin >> dynamic_matrix_size;


    // Размер матрицы: 1-ая Проверка на корректность (является ли числом)
    if (!cin.good()) {
        cout << "Ошибка при вводе из консоли (№1).\n"
            << "Некорректно введен размер матрицы - он должен быть целым числом.\n";
        exit(1);
    }


    // Размер матрицы: 2-ая Проверка на корректность (принадлежит ли области допустимых значений)
    if ((dynamic_matrix_size < 1) || (dynamic_matrix_size > k_max_matrix_size)) {
        cout << "Ошибка при вводе из консоли (№2).\n"
            << "Введен некорректный размер матрицы - он должен принадлежать области допустимых значений\n"
            << "(то есть быть в пределах от 1 до максимального допустимого размера).\n";
        exit(2);
    }


    // Размер матрицы: Эхо-вывод
    cout << "Размер матрицы = " << dynamic_matrix_size << endl;


    // Создадим новый динамический массив
    int** new_dynamic_matrix = new int* [dynamic_matrix_size];


    // Вводим элементы матрицы, проверяя каждый вводимый элемент на корректность
    for (int i = 0; i < dynamic_matrix_size; i++) {

        // В i-ую ячейку массива строк поместим массив элементов строки
        new_dynamic_matrix[i] = new int[dynamic_matrix_size];

        for (int j = 0; j < dynamic_matrix_size; j++) {

            // Вводим очередной элемент
            cin >> new_dynamic_matrix[i][j];

            // Проверяем, является ли он числом
            if (!cin.good()) {
                cout << "Ошибка при вводе из консоли (№3).\n"
                    << "Некорректно введен элемент матрицы - он должен быть целым числом.\n";
                exit(3);
            }

        }

    } // Конец блока "Вводим элементы матрицы, проверяя каждый вводимый элемент на корректность"


    // Направим наш указатель в функции main на только что заполненный динамический массив:
    *pointer_to_pointer_to_dynamic_matrix = new_dynamic_matrix;


    // Эхо-вывод:
    for (int i = 0; i < dynamic_matrix_size; i++) {

        for (int j = 0; j < dynamic_matrix_size; j++) {

            cout << new_dynamic_matrix[i][j] << " ";

        }

        cout << endl;

    }

    // Очистим буфер ввода:
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}





// Функция чтения данных из файла
void read_data_from_file(int*** pointer_to_pointer_to_dynamic_matrix, int& dynamic_matrix_size){


    cout << "\nВвод данных из файла\n\n";

    // Пробуем открыть файл
    ifstream file;
    file.open(k_file_name);

    // Проверим, получилось ли открыть файл
    if (!file.is_open()) {
        cout << "Ошибка при вводе из файла (№4).\n"
            << "Не удалось открыть файл.\n";
        exit(4);
    }

    // Размер матрицы: Ввод
    file >> dynamic_matrix_size;


    // Размер матрицы: 1-ая Проверка на корректность (является ли числом)
    if (!file.good()) {
        cout << "Ошибка при вводе из файла (№5).\n"
            << "Некорректно введен размер матрицы - он должен быть целым числом.\n";
        exit(5);
    }


    // Размер матрицы: 2-ая Проверка на корректность (принадлежит ли области допустимых значений)
    if ((dynamic_matrix_size < 1) || (dynamic_matrix_size > k_max_matrix_size)) {
        cout << "Ошибка при вводе из файла (№6).\n"
            << "Введен некорректный размер матрицы - он должен принадлежать области допустимых значений\n"
            << "(то есть быть в пределах от 1 до максимального допустимого размера).\n";
        exit(6);
    }


    // Размер матрицы: Эхо-вывод
    cout << "Размер матрицы = " << dynamic_matrix_size << endl;


    // Создадим новый динамический массив
    int** new_dynamic_matrix = new int* [dynamic_matrix_size];


    // Вводим элементы матрицы, проверяя каждый вводимый элемент на корректность
    for (int i = 0; i < dynamic_matrix_size; i++) {

        // В i-ую ячейку массива строк поместим массив элементов строки
        new_dynamic_matrix[i] = new int[dynamic_matrix_size];

        for (int j = 0; j < dynamic_matrix_size; j++) {

            // Вводим очередной элемент
            file >> new_dynamic_matrix[i][j];

            // Если элемента НЕ ХВАТАЕТ или если он НЕ ЧИСЛО, получим ошибку
            if (!file.good()) {
                cout << "Ошибка при вводе из файла (№7).\n"
                    << "Один из элементов матрицы некорректен или его не хватает.\n";
                exit(7);
            }
        }

    } // Конец блока "Вводим элементы матрицы, проверяя каждый вводимый элемент на корректность"


    // Направим наш указатель в функции main на только что заполненный динамический массив:
    *pointer_to_pointer_to_dynamic_matrix = new_dynamic_matrix;


    // Проверим, не осталось ли в файле лишних чисел
    char a;
    file.get(a);
    file.get(a);
    if (!file.eof()) {
        cout << "Ошибка при вводе из файла (№8).\n"
            << "В файле есть лишние элементы.\n";
        exit(8);
    }

    // Эхо-вывод матрицы:
    cout << "\nВведена матрица:\n";
    for (int i = 0; i < dynamic_matrix_size; i++) {

        for (int j = 0; j < dynamic_matrix_size; j++) {

            cout << new_dynamic_matrix[i][j] << " ";

        }

        cout << endl;

    } // Конец блока "Эхо-вывод матрицы"
    cout << endl;


    // Очистим буфер ввода:
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}





// Функция расчета требуемых сумм
void calculation_of_sums(int** dynamic_matrix, const int& dynamic_matrix_size) {

    // Объявление переменных
    int sum_in_all_strings = 0; // Сумма по всем строкам
    int sum_in_current_string; // Сумма в текущей строке
    int sum_minimal = -1; // Минимальная среди сумм 
    int sum_minimal_id; // Номер строки, в которой минимальная сумма
    bool string_has_negative_elements; // Переменная выражает, есть ли в строке отрицательные числа

    // Перебор строк:
    for (int i = 1; i < dynamic_matrix_size; i++) {

        sum_in_current_string = 0; // В текущей строке изначально сумма не расчитана
        string_has_negative_elements = false; //  В текущей строке изначально не найдены отрицательные элементы

        // Перебор элементов в строке до главной диагонали:
        for (int j = 0; j < i; j++) {

            // Если в строке есть отрицательные элементы, "запомним" это:
            if (dynamic_matrix[i][j] < 0) {

                string_has_negative_elements = true;
                break;

            }

            // Прибавим к общей сумме сумму элементов этой строки
            sum_in_current_string += dynamic_matrix[i][j];

        }

        // Если в строке не нашлось отрицательных элементов:
        if (!string_has_negative_elements) {

            sum_in_all_strings += sum_in_current_string; // Прибавим к общей сумме со всех строк сумму этой строки

            // Если в матрице до сих пор не была найдена ни одна строка без отрицательных элементов:
            if (sum_minimal == -1) {

                // Сумма элементов в этой строке будет минимальной
                sum_minimal = sum_in_current_string;
                sum_minimal_id = i;

            }
            else {

                // Если в этой строке сумма меньше, чем минимальная сумма среди других строк:
                if (sum_in_current_string < sum_minimal) {

                    // Сумма элементов в этой строке будет минимальной
                    sum_minimal = sum_in_current_string;
                    sum_minimal_id = i;

                }

            }

        }

    }


    // Если ни нашли ни одной подходящей строки:
    if (sum_minimal == -1) {

        cout << "Сумма №1: " << 0
            << "\n(это сумма элементов строк, находящихся под главной диагональю и не имеющих там отрицательных элементов)" << endl;
        cout << "Сумма №2: " << 0
            << "\n(это минимальная из сумм элементов строк, находящихся под главной диагональю и не имеющих там отрицательных элементов)" << endl;

    }
    else {

        cout << "Сумма №1: " << sum_in_all_strings
            << "\n(это сумма элементов строк, находящихся под главной диагональю и не имеющих там отрицательных элементов)" << endl;
        cout << "Сумма №2: " << sum_minimal << ", найдена по строке: " << sum_minimal_id
            << "\n(это минимальная из сумм элементов строк, находящихся под главной диагональю и не имеющих там отрицательных элементов)" << endl;

    }

}

// Функция заполнения матрицы случайными числами
void fill_with_random_numbers(int*** pointer_to_pointer_to_dynamic_matrix, int& dynamic_matrix_size) {

    cout << "\nВвод случайных данных\n\n";

    // Получим случайное значение для размера матрицы 
    dynamic_matrix_size = (rand() % k_max_matrix_size) + 1;

    cout << "Случайный размер матрицы: " << dynamic_matrix_size << endl << endl;


    // Создадим новый динамический массив
    int** new_dynamic_matrix = new int* [dynamic_matrix_size];


    // Заполним матрицу случайными числами
    for (int i = 0; i < dynamic_matrix_size; i++) {

        // В i-ую ячейку массива строк поместим массив элементов строки
        new_dynamic_matrix[i] = new int[dynamic_matrix_size];

        for (int j = 0; j < dynamic_matrix_size; j++) {

            new_dynamic_matrix[i][j] = (rand() % 20) - 10;

        }

    }


    // Направим наш указатель в функции main на только что заполненный динамический массив:
    *pointer_to_pointer_to_dynamic_matrix = new_dynamic_matrix;


    // Выведем полученную матрицу:
    cout << "Заполненная случайными числами матрица: " << endl;
    for (int i = 0; i < dynamic_matrix_size; i++) {

        for (int j = 0; j < dynamic_matrix_size; j++) {

            cout << new_dynamic_matrix[i][j] << " ";

        }

        cout << endl;

    }

    cout << endl;
}