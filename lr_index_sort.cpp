#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
#include <cstdlib>

using namespace std;


const string g_file_name = "inkorrekt7.txt"; // Имя файла исходных данных
const int g_max_planes_count = 50; // Максимально допустимое число самолетов в файле


// Структура "Самолет"
struct plane {

    string brand; // Марка самолета. Формат: любая строка
    string plane_number;  // Бортовой номер. Формат: "БУКВА", "-" , "ПОЛОЖИТЕЛЬНОЕ НАТУРАЛЬНОЕ ЧИСЛО"
    string flight_number; // Номер рейса. Формат: "РЕЙС", "ЦЕЛОЕ ЧИСЛО НЕ РАВНОЕ НУЛЮ"  
    string landing_time; // Время посадки. Формат: стандартный формат времени ЧЧ:ММ

    int flight_number_numeric; // Число из номера рейса
    int landing_time_numeric; // Время посадки в минутах

};


// Прототипы функций
void sorting(plane planes[], int planes_count); // Индексная сортировка считанного массива
//void get_random_planes(plane** planes, int& planes_count); // Получить случайные исходные данные


// Основная программа
int main()
{
    
    // Подключение русского языка:
    setlocale(LC_ALL, "Russian");


    // Объявление переменных:
    ifstream file; // Поток ввода данных из файла
    plane* planes = new plane[g_max_planes_count]; // Массив самолетов
    int planes_count = 0; // Количество самолетов


    // Открытие файла:
    file.open(g_file_name); // Полагается, что файл имеет кодировку ANSI


    // Проверка успешности открытия файла:
    if (!file.is_open()) {

        cout << "Ошибка! Не удалось открыть файл"
            << "\n\n";

        return 1;

    }

    
    // Считывание данных из файла
    while (!file.eof()) {


        // Если уже считали максимально допустимое количество информации:
        if (planes_count == g_max_planes_count) {

            cout << "Ошибка! Превышен лимит числа вводимых данных."
                << "\n\n";

            return 2;

        }


        plane plane; // Очередной самолет
        int plane_parameters_readed = 0; // Число считанных параметров очередного самолета


        // Считывание параметов самолета
        while ((!file.eof()) && (plane_parameters_readed < 4)) { // Пока не ввели все 4 параметра и пока они еще есть в файле

            plane_parameters_readed++;

            // Считывание и обработка каждого отдельного параметра самолета
            switch (plane_parameters_readed) { 


                // Ввод марки самолета:
                case 1: 

                    file >> plane.brand;

                    // Без входного контроля. 

                    break;

                // Конец ввода марки самолета



                // Ввод бортового номера:
                case 2:

                    file >> plane.plane_number;


                    // Входной контроль: Бортовой номер состоит минимум из 3 символов
                    if (plane.plane_number.length() < 3) {

                        cout << "Ошибка! В бортовом номере не хватает символов."
                            << "\n\n";

                        return 3;

                    }


                    // Входной контроль: Первый символ бортового номера должен быть заглавной буквой русского алфавита
                    if ((plane.plane_number[0] < 'А') || (plane.plane_number[0] > 'Я')) {

                        cout << "Ошибка! Буква бортового номера самолета некорректна."
                            << "\n\n";

                        return 4;

                    }


                    // Входной контроль: Второй символ бортового номера должен быть тире
                    if (plane.plane_number[1] != '-') {

                        cout << "Ошибка! В бортовом номере отсутствует тире между буквенной и числовой частями."
                            << "\n\n";

                        return 5;

                    }


                    // Входной контроль: После тире в бортовом номере должны быть цифры
                    for(int i = 2; i < plane.plane_number.length(); i++){

                        if ((plane.plane_number[i] < '0') || (plane.plane_number[i] > '9')) {

                            cout << "Ошибка! В бортовом номере после тире стоят не только цифры."
                                << "\n\n";

                            return 6;

                        }

                    }

                    break;

                // Конец ввода бортового номера



                // Ввод номера рейса:
                case 3:

                    file >> plane.flight_number;

                    // Входной контроль: Номер рейса должен состоять минимум из 5 символов
                    if (plane.flight_number.length() < 5) {

                        cout << "Ошибка! В номере рейса не хватает символов."
                            << "\n\n";

                        return 7;

                    }


                    // Входной контроль: Первые 4 символа в номере рейса должно занимать слово "РЕЙС"
                    if (plane.flight_number.substr(0,4) != "РЕЙС") {

                        cout << "Ошибка! В начале номера рейса не стоит слово \"РЕЙС\"."
                            << "\n\n";

                        return 8;

                    }

                    if (plane.flight_number[4] != '-') { // Если номер рейса неотрицательный

                        // Входной контроль: Номер рейса не равен 0
                        if (plane.flight_number[4] == '0') {

                            cout << "Ошибка! Номер рейса не должен быть равен 0."
                                << "\n\n";

                            return 9;

                        }

                        // Входной контроль: В случае положительного числа после "РЕЙС" в номере рейса должны быть только цифры 
                        for (int i = 4; i < plane.flight_number.length(); i++) {

                            if ((plane.flight_number[i] < '0') || (plane.flight_number[i] > '9')) {

                                cout << "Ошибка! В номера рейса после \"РЕЙС\" стоят не только цифры."
                                    << "\n\n";

                                return 10;

                            }

                        }

                    }
                    else { // Если номер рейса отрицательный

                        // Входной контроль: В случае отрицательного числа номер рейса должен иметь минимум 6 символов
                        if (plane.flight_number.length() < 6) {

                            cout << "Ошибка! В номере рейса не хватает символов."
                                << "\n\n";

                            return 11;

                        }

                        // Входной контроль: В случае отрицательного числа после "РЕЙС-" в номере рейса должны быть только цифры
                        for (int i = 5; i < plane.flight_number.length(); i++) {

                            if ((plane.flight_number[i] < '0') || (plane.flight_number[i] > '9')) {

                                cout << "Ошибка! В номера рейса после \"РЕЙС-\" стоят не только цифры."
                                    << "\n\n";

                                return 12;

                            }

                        }

                    }



                    // "Вытащим" из номера рейса число в отдельную переменную:
                    plane.flight_number_numeric = atoi(plane.flight_number.substr(4, plane.flight_number.length() - 4).c_str());
      


                    break;

                // Конец ввода номера рейса



                // Ввод времени посадки:
                case 4:

                    file >> plane.landing_time;


                    // Входной контроль: Время посадки должно состоять из 5 символов
                    if (plane.landing_time.length() != 5) {

                        cout << "Ошибка! Время посадки состоит из 5 символов."
                            << "\n\n";

                        return 13;

                    }


                    // Входной контроль: Должен быть формат "XX:YY". Причем XX от 0 до 23, а YY от 0 до 59
                    for(int i = 0; i < 5; i++){

                        bool flag = false; // Отображает наличие ошибки при проходе цикла. По началу false.

                        switch (i) { // Проверяем каждый символ

                        case 0:

                            if ((plane.landing_time[i] < '0') || (plane.landing_time[i] > '2')) {
                                flag = true;
                            }

                            break;


                        case 1:

                            if (plane.landing_time[0] < '2') {

                                if ((plane.landing_time[i] < '0') || (plane.landing_time[i] > '9')) {
                                    flag = true;
                                }

                            }
                            else {

                                if ((plane.landing_time[i] < '0') || (plane.landing_time[i] > '3')) {
                                    flag = true;
                                }

                            }

                            break;


                        case 2:

                            if (plane.landing_time[2] != ':') {
                                flag = true;
                            }

                            break;


                        case 3:

                            if ((plane.landing_time[i] < '0') || (plane.landing_time[i] > '5')) {
                                flag = true;
                            }

                            break;


                        case 4:

                            if ((plane.landing_time[i] < '0') || (plane.landing_time[i] > '9')) {
                                flag = true;
                            }

                            break;

                        }


                        if (flag) { // Если хотя бы один из символ не соотвествует формату

                            cout << "Ошибка! Неверный формат времени."
                                << "\n\n";

                            return 14;

                        }

                      

                    } // Конец проверки каждого символа    


                    // "Вытащим" из времени посадки число в отдельную переменную (представляя время посадки в минутах):
                    plane.landing_time_numeric = 0; // Инициализируем нулем
                    plane.landing_time_numeric += 10 * 60 * (plane.landing_time[0] - '0'); // Прибавим десятки часов
                    plane.landing_time_numeric += 60 * (plane.landing_time[1] - '0'); // Прибавим часы
                    plane.landing_time_numeric += 10 * (plane.landing_time[3] - '0'); // Прибавим десятки минут
                    plane.landing_time_numeric += (plane.landing_time[4] - '0'); // Прибавим минуты


            } // Конец считывания и обработки каждого отдельного параметра самолета

        } // Конец считывания параметров самолета


        // Если в файле не хватило параметров для очередного самолета
        if (plane_parameters_readed != 4) {

            cout << "Ошибка! Недостаточно данных о последнем самолете."
                << "\n\n";

            return 15;

        }


        // Итак, программа полностью считала информацию об очередном самолете и проверила её на корректность


        // Увеличим число считанных самолетов на 1:
        planes_count++;


        // Добавим очередной самолет в наш массив самолетов:
        planes[planes_count - 1] = plane;



    } // Конец считывания данных из файла
    

    //delete[] planes;
    //get_random_planes(&planes, planes_count);


    // Вывод таблицы исходных данных:
    cout << "1) Исходная таблица:\n";
    for (int i = 0; i < planes_count; i++) {

        cout << setiosflags(ios::left); // Устанавлием выравнивание таблицы по левому краю
    
        // Табулированно выводим параметры самолета
        cout << setw(15) << planes[i].brand
            << setw(15) << planes[i].plane_number
            << setw(15) << planes[i].flight_number
            << setw(15) << planes[i].landing_time
            << endl;

    }
    cout << endl;




    // Сделаем индексную сортировку и распечатаем результат
    sorting(planes, planes_count);



}




// Индексная сортировка считанного массива
void sorting(plane planes[], int planes_count) {


    // ---------------------------------------------------------
    // ---------------- Сортировка по номеру рейса -------------
    // ---------------------------------------------------------

    
    // Объявление переменных:
    int* sorted_by_flight_number = new int [planes_count]; // Массив индексов для сортировки по убыванию по номеру рейса
    int planes_in_flight_count = 0; // Число самолетов в полете 


    // Приведение массивов индексов к виду:  1,  2,  3, ... ,  planes_count - 2,  planes_count - 1,  planes_count.
    for (int i = 0; i < planes_count; i++) {

        sorted_by_flight_number[i] = i;

    }
    

    // Перебираем  все элементы массива индексов
    for (int i = 0; i < planes_count; i++) {

        int tmp; // Дополнительная переменная для хранения данных при обмене значениями двух других переменных
        int maximum_number_value; // Значение максимального номера рейса на рассматриваемом отрезке (от j = i до j < planes_count)
        int maximum_number_id; // Индекс максимального номера рейса на рассматриваемом отрезке      (от j = i до j < planes_count)

        // Перебираем элементы массива индексов от i и направо
        for (int j = i; j < planes_count; j++) { 


            int original_index = sorted_by_flight_number[j]; // Для j-ого элемента в массиве индексов получим его индекс в исходном массиве planes
            

            // Первый элемент на отрезке примем за максимальный:
            if (j == i) { 

                maximum_number_value = planes[original_index].flight_number_numeric; // "Запомним" его значение
                maximum_number_id = j; // "Запомним" его индекс
                continue;

            }

            // Сравниваем раннее найденный максимум с рассматриваемым элементом:
            if (planes[original_index].flight_number_numeric > maximum_number_value) {

                maximum_number_value = planes[original_index].flight_number_numeric;
                maximum_number_id = j;

            }

        } // Конец блока "Перебираем элементы массива индексов от i и направо"


        // В массиве индексов поменяем местами i-ый элемент с наибольшим элементом на полуинтервале [i;planes_count)
        tmp = sorted_by_flight_number[i];
        sorted_by_flight_number[i] = sorted_by_flight_number[maximum_number_id];
        sorted_by_flight_number[maximum_number_id] = tmp;


        // Если теперь на i-ом месте стоит элемент с отрицательным номером рейса, то увеличим счетчик самолетов в полете (не совершающих посадку):
        if (planes[sorted_by_flight_number[i]].flight_number_numeric < 0) {

            planes_in_flight_count++;

        }

    } // Конец блока "Перебираем  все элементы массива индексов"



    // Выведем получившуюся таблицу
    cout << "2) Таблица отсортированная в порядке убывания номера рейсов для самолетов в полете:\n";
    for (int i = planes_count- planes_in_flight_count; i < planes_count; i++) {

        cout << setiosflags(ios::left); // Устанавлием выравнивание таблицы по левому краю

        // Табулированно выводим параметры самолета
        cout << setw(15) << planes[sorted_by_flight_number[i]].brand
            << setw(15) << planes[sorted_by_flight_number[i]].plane_number
            << setw(15) << planes[sorted_by_flight_number[i]].flight_number
            << setw(15) << planes[sorted_by_flight_number[i]].landing_time
            << endl;

    }
    cout << endl;

    if (planes_in_flight_count == 0) {

        cout << "Пусто.\n\n";

    }


  
    // ---------------------------------------------------------
    // ------------- Сортировка по времени посадки -------------
    // ---------------------------------------------------------


    // Объявление переменных:
    int planes_landing_count = planes_count - planes_in_flight_count; // Число садящихся самолетов
    int* sorted_by_landing_time = new int[planes_landing_count]; // Массив индексов для сортировки по возрастанию по времени полета 


    // Из массива индексов отсортированного по номеру рейса скопируем первые planes_landing_count элементов - это и будут садящиеся самолеты
    for (int i = 0; i < planes_landing_count; i++) {

        sorted_by_landing_time[i] = sorted_by_flight_number[i];

    }


    // Сортировка по времени посадки
    for (int i = 0; i < planes_landing_count; i++) {

        int tmp; // Дополнительная переменная для хранения данных при обмене значениями двух других переменных
        int minimum_number_value; // Значение минимального времени посадки на рассматриваемом отрезке (от j = i до j < planes_landing_count)
        int minimum_number_id; // Индекс минимального времени посадки на рассматриваемом отрезке      (от j = i до j < planes_landing_count)

        // Перебираем элементы массива индексов 
        for (int j = i; j < planes_landing_count; j++) {


            int original_index = sorted_by_landing_time[j]; // Для j-ого элемента в массиве индексов получим его индекс в исходном массиве planes


            // Первый элемент на отрезке примем за максимальный:
            if (j == i) {

                minimum_number_value = planes[original_index].landing_time_numeric; // "Запомним" его значение
                minimum_number_id = j; // "Запомним" его индекс
                continue;

            }

            // Сравниваем раннее найденный максимум с рассматриваемым элементом:
            if (planes[original_index].landing_time_numeric < minimum_number_value) {

                minimum_number_value = planes[original_index].landing_time_numeric;
                minimum_number_id = j;

            }

        }


        // В массиве индексов поменяем местами i-ый элемент с наибольшим элементом на полуинтервале [i;planes_count)
        tmp = sorted_by_landing_time[i];
        sorted_by_landing_time[i] = sorted_by_landing_time[minimum_number_id];
        sorted_by_landing_time[minimum_number_id] = tmp;

    } // Конец сортировки по времени посадки



    // Выведем получившуюся таблицу
    cout << "3) Таблица отсортированная в порядке возрастания времени посадки для садящихся самолетов:\n";
    for (int i = 0; i < planes_landing_count; i++) {

        cout << setiosflags(ios::left); // Устанавлием выравнивание таблицы по левому краю

        // Табулированно выводим параметры самолета
        cout << setw(15) << planes[sorted_by_landing_time[i]].brand
            << setw(15) << planes[sorted_by_landing_time[i]].plane_number
            << setw(15) << planes[sorted_by_landing_time[i]].flight_number
            << setw(15) << planes[sorted_by_landing_time[i]].landing_time
            << endl;

    }
    cout << endl;

    if (planes_landing_count == 0) {

        cout << "Пусто.\n\n";

    }

}


/*
// Получить случайные исходные данные
void get_random_planes(plane** planes, int& planes_count) {

    srand(time(NULL)); // Настроим генерацию случайных чисел на зависимость от времени

    // Объявление переменных
    const int brands_count = 10; // Число марок ЛА
    const string brands[brands_count] = { "Ту-134", "Ту-154", "Ту-204", "ИЛ-62", "ИЛ-86", "ИЛ-96", "ИЛ-96-300", "Airbus A310", "Airbus A320", "Boeing-737" }; // Набор марок ЛА
    const int max_number_of_planes = 10; // Максимальное число самолетов, которое может быть сгенерировано

    // Проверим корректность max_number_of_planes 
    if (max_number_of_planes > g_max_planes_count) {

        cout << "Ошибка в функции get_random_planes().\n\n";
        exit(1);

    }

    // Получим случайное число самолетов
    planes_count = rand() % max_number_of_planes;
    cout << "planes_count=" << planes_count << "\n";

    // Создадим динамический массив для хранения самолетов, которые будем генерировать
    plane* random_planes = new plane[planes_count];
    *planes = random_planes;

    // Генерируем самолетыы
    for (int i = 0; i < planes_count;i++) {

        // Случайно выберем марку из готового списка  
        planes[i]->brand =
            brands[rand() % brands_count];

        // Случайно сгенерируем бортовой номер
        planes[i]->plane_number =
            string(1, 'А' + rand() % 33) +
            string(1, '-') +
            to_string(rand() % 9999);

        // Случайно сгенерируем номер рейса
        planes[i]->flight_number_numeric = (rand() % 19998) - 9999;
        planes[i]->flight_number =
            string(4, 'РЕЙС') +
            to_string(planes[i]->flight_number_numeric);

        // Случайно сгенерируем время посадки
        planes[i]->landing_time_numeric = rand() % 1439;
        planes[i]->landing_time =
            to_string(planes[i]->landing_time_numeric / 60) +
            string(1, ':') +
            to_string(planes[i]->landing_time_numeric % 60);

    }

    for (int i = 0; i < planes_count; i++) {

        cout << setiosflags(ios::left); // Устанавлием выравнивание таблицы по левому краю

        // Табулированно выводим параметры самолета
        cout << setw(15) << planes[i]->brand
            << setw(15) << planes[i]->plane_number
            << setw(15) << planes[i]->flight_number
            << setw(15) << planes[i]->landing_time
            << endl;

    }
    cout << endl;

}
*/