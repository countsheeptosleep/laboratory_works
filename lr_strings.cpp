// Лабораторная работа №1. Вариант 4
// Dmitry Domrachev, Виталий Богомольский, МАИ 2022 группа М3О-111Б-21

#include <iostream>
#include <fstream>
using namespace std;



// Глобальные константы
const int NMAX = 80 + 1; // Максимальная длина двух вводимых в задаче строк (на 1 больше, учитывая символ конца строки)
const string FILEMANE = "4-4.txt"; // Имя файла исходных данных (в случае ввода из файла)
const bool USER_CHOOSE_READING_METHOD = true; // Выбирает ли пользователь метод чтения данных, или используется метод по умолчанию
const char DEFAULT_DATA_READING_METHOD_ID = '1'; // Номер метода чтения данных по умолчанию. '1' - консоль, '2' - файл


// Прототипы функций: для чтения данных
void ReadDataFromConsole(char(&FirstLine)[NMAX], int& FirstLine_Length, char(&SecondLine)[NMAX], int& SecondLine_Length, char& GivenSymbol);
void ReadDataFromFile(char(&FirstLine)[NMAX], int& FirstLine_Length, char(&SecondLine)[NMAX], int& SecondLine_Length, char& GivenSymbol);
// Прототипы функций: другие
void CleanLine(char(&Line)[NMAX], const int Length);
void FindWordsIndexesInLine(const char(&Line)[NMAX], const int Length, int(&WordsIndexes)[NMAX], int& WordsCount);
void DeleteRepeatingWordsInLine(char(&Line)[NMAX], int(&WordsIndexes)[NMAX], int WordsCount);
bool CompareTwoWordsFromTwoLines(const char(&Line1)[NMAX], const char(&Line2)[NMAX], int Line1_StartIndex, int Line1_EndIndex, int Line2_StartIndex, int Line2_EndIndex);
void PrintWord(const char(&Line)[NMAX], int start_index, int end_index);
void FindDuplicatesInTwoLines(const char(&FirstLine)[NMAX], const char(&SecondLine)[NMAX], int FirstLine_WordsCount, int SecondLine_WordsCount, const int(&FirstLine_WordsIndexes)[NMAX], const int(&SecondLine_WordsIndexes)[NMAX]);
void DeleteWord(char(&Line)[NMAX], int start_index, int end_index);
void CountSymbolInTwoLines(const char(&FirstLine)[NMAX], const char(&SecondLine)[NMAX], char Symbol, int FirstLine_Length, int SecondLine_Length);




// Основная программа
int main() {

    /// ---------------------------------------------------------------------------
    /// ---------------------------------- ПЕРВАЯ ЧАСТЬ ---------------------------
    /// ----------------------- Объявление переменных, ввод данных ----------------
    /// ---------------------------------------------------------------------------

    // Объявление переменных: основные переменные
    char FirstLine[NMAX]; // Первая строка
    int FirstLine_Length = 0; // Длина первой строки
    char SecondLine[NMAX]; // Вторая строка
    int SecondLine_Length = 0; // Длина второй строки
    char GivenSymbol = 0; // Заданный символ
    // Объявление переменных: дополнительные переменные
    char FirstLine_Copy[NMAX]; // Копия первой строки
    char SecondLine_Copy[NMAX]; // Копия второй строки
    int FirstLine_WordsIndexes[NMAX]; // Массив индексов слов первой строки
    int FirstLine_WordsCount; // Кол-во слов первой строки
    int SecondLine_WordsIndexes[NMAX]; // Массив индексов слов второй строки
    int SecondLine_WordsCount; // Кол-во слов второй строки
    // Объявление переменных: переменные для настройки программы
    char DataReadingMethodID = DEFAULT_DATA_READING_METHOD_ID; // Номер метода чтения данных, выбираемый пользователем, если такая возможность активирована. '1' - консоль, '2' - файл



    // Подключение русского языка
    setlocale(LC_ALL, "Russian");



    // Выбор способа ввода данных
    if (USER_CHOOSE_READING_METHOD) {

        // Приглашению к выбору способа ввода данных
        cout << "Выбирете способ ввода данных. Введите его номер:\n" <<
            "'1' - для ввода из консоли\n" <<
            "'2' - для ввода из файла\n";

        // Считывание ответа пользователя
        cin.get(DataReadingMethodID);

        // Первая проверка ответа пользователя на корректность
        if ((DataReadingMethodID != '1') && (DataReadingMethodID != '2')) { // Первый символ любого ID - это цифра 1 или 2. Проверим, что ввел пользователь

            cout << "Ошибка №1-1. Некорректно выбран метод ввода данных.\n";

            return 1;

        }

        // Вторая проверка ответа пользователя на корректность
        if (cin.peek() != '\n') {   // Любой ID имеет длину 1, поэтому после считывания одного символа ничего не должно было остаться

            cout << "Ошибка №1-2. Некорректно выбран метод ввода данных.\n";

            return 1;

        }

        // Очистим буфер ввода
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } // Конец блока "Выбор способа ввода данных"



    // Ввод данных по выбранному способу
    switch (DataReadingMethodID) {

    case '1':

        ReadDataFromConsole(FirstLine, FirstLine_Length, SecondLine, SecondLine_Length, GivenSymbol);
        break;

    case '2':

        ReadDataFromFile(FirstLine, FirstLine_Length, SecondLine, SecondLine_Length, GivenSymbol);
        break;

    } // Конец блока "Ввод данных по выбранному способу"



    /// ---------------------------------------------------------------------------
    /// ---------------------------------- ВТОРАЯ ЧАСТЬ ---------------------------
    /// ------------------ Нахождение слов, встречающихся в двух строках ----------
    /// ---------------------------------------------------------------------------



    // Создадим копии массивов первой и второй строки
    memcpy(FirstLine_Copy, FirstLine, NMAX);
    memcpy(SecondLine_Copy, SecondLine, NMAX);

    // Заменим в копиях все символы, не являющиеся буквами, на пробелы, а также заменим заглавные буквы на строчные
    CleanLine(FirstLine_Copy, FirstLine_Length);
    CleanLine(SecondLine_Copy, SecondLine_Length);

    // Перед тем как искать слова в этих копиях и записывать их индексы в вспомогательные массивы,
    // заполним эти самые вспомогательные массивы минус единицами
    for (int i = 0; i < NMAX; i++) {
        FirstLine_WordsIndexes[i] = -1;
        SecondLine_WordsIndexes[i] = -1;
    }

    // "Найдем" слова в копии первой строки и "запомним" индексы этих слов. Заодно сосчитаем количество слов.
    FindWordsIndexesInLine(FirstLine_Copy, FirstLine_Length, FirstLine_WordsIndexes, FirstLine_WordsCount);
    // То же самое сделаем для второй строки
    FindWordsIndexesInLine(SecondLine_Copy, SecondLine_Length, SecondLine_WordsIndexes, SecondLine_WordsCount);

    // Если в одной из строк совсем не оказалось слов:
    if ((FirstLine_WordsCount == 0) || (SecondLine_WordsCount == 0)) {

        cout << "Нет слов, которые встречаются в обоих строчках. \n";

    }
    else {

        // Удалим из копии первого массива те слова, которые повторяются в этом массиве
        DeleteRepeatingWordsInLine(FirstLine_Copy, FirstLine_WordsIndexes, FirstLine_WordsCount);

        // Очистим массив слов, сделанный ранее для первого массива
        for (int i = 0; i < NMAX; i++) {
            FirstLine_WordsIndexes[i] = -1;
        }

        // Заново найдем слова
        FindWordsIndexesInLine(FirstLine_Copy, FirstLine_Length, FirstLine_WordsIndexes, FirstLine_WordsCount);

        // Наконец, обнаружим слова, которые встречаются в обоих строках
        FindDuplicatesInTwoLines(FirstLine_Copy, SecondLine_Copy, FirstLine_WordsCount, SecondLine_WordsCount, FirstLine_WordsIndexes, SecondLine_WordsIndexes);

    }


    /// ---------------------------------------------------------------------------
    /// ---------------------------------- ТРЕТЬЯ ЧАСТЬ ---------------------------
    /// --------------------- В какой строке символ встречается чаще --------------
    /// ---------------------------------------------------------------------------


    cout << "В какой строке символ встречается чаще? ";

    // Считаем кол-во вхождений символа в каждую из двух строк
    CountSymbolInTwoLines(FirstLine, SecondLine, GivenSymbol, FirstLine_Length, SecondLine_Length);

    return 0;


}








void ReadDataFromConsole(char(&FirstLine)[NMAX], int& FirstLine_Length, char(&SecondLine)[NMAX], int& SecondLine_Length, char& GivenSymbol) {

    cout << "\nВвод данных из консоли\n\n";

    // По началу считаем длины строк нулевыми
    FirstLine_Length = 0;
    SecondLine_Length = 0;



    // Первая строка: Чтение
    cout << "Введите первую строку." << endl;
    cin.getline(FirstLine, NMAX);                            //!!!! не выдает ошибку если строка больше нмакс


    // Первая строка: Подсчет длины
    while (FirstLine[FirstLine_Length] != '\0') {
        FirstLine_Length++;
    }

    //  Первая строка: Проверка, не пуста ли
    if (FirstLine_Length == 0) {

        cout << "Ошибка №2-1. Первая строка пуста.\n";

        exit(2);
    }

    // Первая строка: Эхо-вывод
    cout << " - Первая строка: |" << FirstLine << "|" << endl << endl;



    // Вторая строка: Чтение
    cout << "Введите вторую строку." << endl;
    cin.getline(SecondLine, NMAX);                               //!!!! не выдает ошибку если строка больше нмакс


    // Вторая строка: Подсчет длины
    while (SecondLine[SecondLine_Length] != '\0') {
        SecondLine_Length++;
    }

    //  Вторая строка: Проверка, не пуста ли
    if (SecondLine_Length == 0) {

        cout << "Ошибка №2-2. Вторая строка пуста.\n";

        exit(2);
    }

    // Вторая строка: Эхо-вывод
    cout << "- Вторая строка: |" << SecondLine << "|" << endl << endl;



    // Символ для подсчета вхождений: Чтение
    cout << "Введите символ, повторения которого необходимо посчитать." << endl;
    cin.get(GivenSymbol);

    // Символ для подсчета вхождений: Проверка на корректность
    if ((GivenSymbol == '\n') || (cin.peek() != '\n')) {   // Если ввели Enter или больше одного символа

        cout << "Ошибка №2-3. Некорректно введен символ.\n";

        exit(2);

    }

    // Символ для подсчета вхождений: Эхо-вывод
    cout << " - Символ: |" << GivenSymbol << "|" << endl << endl;

    



    // Очистим буфер ввода
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}

//Функция чтения входных данных из файла
void ReadDataFromFile(char(&FirstLine)[NMAX], int& FirstLine_Length, char(&SecondLine)[NMAX], int& SecondLine_Length, char& GivenSymbol) {



    cout << "\nВвод данных из файла\n\n";

    // Объявление вспомогательных переменных:
    char CurrentSymbol; // Рассматриваемый символ
    int CurrentSymbol_Line = 1; // Номер строки, в которой стоит рассматриваемый символ
    int CurrentSymbol_Position = 0; // Позиция рассматриваемого символа в этой строке (индекс)
    int ThirdLine_Length = 0; // Число элементов в третьей строке (в которой ожидается всего 1 символ)


    // По началу обнулим переменные, которые будут хранить длины считываемых строк
    FirstLine_Length = 0;
    SecondLine_Length = 0;


    ifstream f(FILEMANE); // Открываем файл

    // Проверим, удалось ли открыть файл
    if (!f.good()) {

        cout << "Ошибка №3-1. Не удалось открыть файл.\n";
        exit(3);

    }


    CurrentSymbol = f.get();

    while (CurrentSymbol != -1) { // Пока удается считывать следующий символ

        if (CurrentSymbol == '\n') { // Если встречаем символ переноса строки

            CurrentSymbol_Line += 1; // Переходим к следующей строке
            CurrentSymbol_Position = 0; // Переводим индекс рассматриваемого элемента на первый элемент в строке

            CurrentSymbol = f.get(); // Считываем следующий символ

            continue;

        }

        switch (CurrentSymbol_Line) {  // В зависимости от номера рассматриваемой строки сохраняем символы в нужные переменные

        case 1:

            // Проверим, не успел ли уже заполниться первый массив
            if (FirstLine_Length == NMAX) {

                cout << "Ошибка №3-2. Длина введенной первой строки превышает максимально допустимую.\n";
                exit(3);

            }

            FirstLine[CurrentSymbol_Position] = CurrentSymbol; // Сохраняем символ в массив
            FirstLine_Length++; // Увеличиваем счетчик количества символов
            FirstLine[CurrentSymbol_Position + 1] = '\0'; // Пока что делаем следующий элемент концом строки

            break;

        case 2:

            // Проверим, не успел ли уже заполниться второй массив
            if (SecondLine_Length == NMAX) {

                cout << "Ошибка №3-3. Длина введенной второй строки превышает максимально допустимую.\n";
                exit(3);

            }

            SecondLine[CurrentSymbol_Position] = CurrentSymbol; // Сохраняем символ в массив
            SecondLine_Length++; // Увеличиваем счетчик количества символов
            SecondLine[CurrentSymbol_Position + 1] = '\0'; // Пока что делаем следующий элемент концом строки

            break;

        case 3:

            GivenSymbol = CurrentSymbol; // Сохраняем символ
            ThirdLine_Length++;
            break;

        case 4:

            cout << "Ошибка №3-4. Слишком много непустых строк в файле, должно быть 3.\n";
            exit(3);

        }

        CurrentSymbol_Position++; // Переводим индекс рассматриваемых элементов на следующий элемент в строке

        CurrentSymbol = f.get(); // Считываем следующий символ

    }

    // Проверим, не был ли считан current_char из пустой строки
    if (FirstLine_Length == 0) {

        cout << "Ошибка №3-5. Первая строка пуста.\n";
        exit(3);

    }

    // Проверим, не был ли считан current_char из пустой строки
    if (SecondLine_Length == 0) {

        cout << "Ошибка №3-6. Вторая строка пуста.\n";
        exit(3);

    }

    // Проверим, не был ли считан current_char из пустой строки
    if (ThirdLine_Length == 0) {

        cout << "Ошибка №3-7. Третья строка пуста.\n";
        exit(3);

    }


    // Проверка, не было ли в третьей строке лишних символов:
    if (ThirdLine_Length > 1) {

        cout << "Ошибка №3-8. Третья строка содержит больше 1 символа.\n";
        exit(3);

    }

    // Первая строка: Эхо-вывод
    cout << " - Первая строка: |" << FirstLine << "|" << endl << endl;

    // Вторая строка: Эхо-вывод
    cout << "- Вторая строка: |" << SecondLine << "|" << endl << endl;

    // Символ из третьей строки: Эхо-вывод
    cout << " - Символ: |" << GivenSymbol << "|" << endl << endl;

}



// Функиця CleanLine: В данной строке заменяет все символы, не являющиеся буквами английского алфавита, на пробелы, а также меняет заглавные буквы на строчные
void CleanLine(char(&Line)[NMAX], const int Length) {

    for (int i = 0; i < Length; i++) { // Рассмотрим все символы строки

        if (!isalpha(Line[i])) {  // Если символ - не буква, то заменяется на пробел
            Line[i] = ' ';
        }

        Line[i] = tolower(Line[i]);  // Если символ - заглавный, то становится строчным

    }

}



// Функция FindWordsIndexes: находит индексы начал и концов слов в строке
//
// Например: для строки Line="I love milk", получим WordsIndexes=[0, 0, 2, 5, 7, 10, -1, -1, -1 ...]
//
void FindWordsIndexesInLine(const char(&Line)[NMAX], const int Length, int(&WordsIndexes)[NMAX], int& WordsCount) {

    // Вспомогательные переменные:
    bool is_word = false; // Выражает, являются ли перебираемые символы частью слова
    int index_counter = 0; // Индекс для движения по массиву WordsIndexes, в котором будем сохранять индексы начал и концов слов

    // По началу считаем количество слов равным 0:
    WordsCount = 0;

    for (int i = 0; i <= Length; i++) {

        if (((Line[i] == ' ') or (Line[i] == '\0')) and is_word) { // Если сейчас пробел или конец строки и до этого шло слово

            WordsIndexes[index_counter] = i - 1; // "Запомним" конец слова
            index_counter++; // Передвинемся по массиву, в котором храним индексы начал и концов слов
            is_word = false; // Выразим, что больше мы "не находимся" в слове

        }

        else if ((Line[i] != ' ' and Line[i] != '\0') and !is_word) {  // Иначе, если сейчас не пробел, не конец строки, и слово еще не шло

            WordsIndexes[index_counter] = i;  // "Запомним" начало слова
            index_counter++; // Передвинемся по массиву, в котором храним индексы начал и концов слов
            is_word = true; // Выразим, что теперь мы "находимся" в слове
            WordsCount++; // Увеличим счетчик количества слов на единицу

        }

    }

}



//Функция DeleteRepeatingWordsInLine: удаляет из данной строки слова, которые в ней повторяются
void DeleteRepeatingWordsInLine(char(&Line)[NMAX], int(&WordsIndexes)[NMAX], int WordsCount) {

    // Сравним каждые 2 пары слов в данной строке
    for (int i = 0; i < 2 * WordsCount; i += 2) {
        for (int j = i + 2; j < 2 * WordsCount; j += 2) {

            // Хитро воспользуемся функцией CompareTwoWordsFromTwoLines, чтобы сравнить, являются ли выбранные два слова этой строки одинаковыми
            if (CompareTwoWordsFromTwoLines(Line, Line, WordsIndexes[i], WordsIndexes[i + 1], WordsIndexes[j], WordsIndexes[j + 1])) {

                DeleteWord(Line, WordsIndexes[j], WordsIndexes[j + 1]); // Если одинаковы, то удалим их

            }
        }
    }


}



// Функция CompareTwoWordsFromTwoLines: сравнивает 2 слова из 2 строк
bool CompareTwoWordsFromTwoLines(const char(&Line1)[NMAX], const char(&Line2)[NMAX], int Line1_StartIndex, int Line1_EndIndex, int Line2_StartIndex, int Line2_EndIndex) {

    if ((Line1_EndIndex - Line1_StartIndex) != (Line2_EndIndex - Line2_StartIndex)) { // Если слова разной длины, они точно не равны
        return false;
    }

    for (int i = 0; i < (Line1_EndIndex - Line1_StartIndex + 1); i++) {

        if (Line1[Line1_StartIndex + i] != Line2[Line2_StartIndex + i]) {   // Если хоть один символ в двух словах не равен, они не равны
            return false;
        }

    }

    return true;
}



// Функция DeleteWord: удаляет слово из данной строки
void DeleteWord(char(&Line)[NMAX], int start_index, int end_index) {

    for (int i = start_index; i <= end_index; i++) { // В исходной строке меняем символы слова на пробелы
        Line[i] = ' ';
    }

}



// Функция DeleteWord: находит слова, встречающиеся в двух строках
void FindDuplicatesInTwoLines(const char(&FirstLine)[NMAX], const char(&SecondLine)[NMAX], int FirstLine_WordsCount, int SecondLine_WordsCount, const int(&FirstLine_WordsIndexes)[NMAX], const int(&SecondLine_WordsIndexes)[NMAX]) {

    bool AreDuplicatesFounded = false; // Выражает, был ли найден хоть один дубликат. По началу считается ложным.

    for (int i = 0; i < 2 * FirstLine_WordsCount; i += 2) { // Cравниваем каждое слово из первого массива с каждым словом из второго
        for (int j = 0; j < 2 * SecondLine_WordsCount; j += 2) {

            if (CompareTwoWordsFromTwoLines(FirstLine, SecondLine, FirstLine_WordsIndexes[i], FirstLine_WordsIndexes[i + 1], SecondLine_WordsIndexes[j], SecondLine_WordsIndexes[j + 1])) {

                PrintWord(FirstLine, FirstLine_WordsIndexes[i], FirstLine_WordsIndexes[i + 1]); // Печатаем одинаковые слова
                AreDuplicatesFounded = true;

               break;

            }
        }
    }

    if (AreDuplicatesFounded) {
        cout << " - встречаются в обоих строках.\n\n";
    }
    else {
        cout << "Нет слов, встречающихся в обоих строках\n\n";
    }

}



// Функция PrintWord: печатает слово из строки
void PrintWord(const char(&Line)[NMAX], int start_index, int end_index) {

    for (int i = start_index; i <= end_index; i++) {
        cout << Line[i];
    }
    cout << " ";
    return;

}



// Функция CountSymbolInLine: считает количество повторов символа в двух строках
void CountSymbolInTwoLines(const char(&FirstLine)[NMAX], const char(&SecondLine)[NMAX], char Symbol, int FirstLine_Length, int SecondLine_Length) {

    // Вспомогательные переменные:
    int first_count = 0; // Число повторов данного символа в первой строке
    int second_count = 0; // Число повторов данного символа во второй строке
    int result; // Результат. Он равен: 0 - если одинаковое количество повторов в обоих строках, 1 - больше в первой строке, 2 - больше во второй строке, 3 - вообще не встречается


    // Считаем число повторов символа в первой строке
    for (int i = 0; i < FirstLine_Length; i++) {

        if (FirstLine[i] == Symbol) {
            first_count++;
        }

    }



    // Считаем число повторов символа во второй строке
    for (int i = 0; i < SecondLine_Length; i++) {

        if (SecondLine[i] == Symbol) {
            second_count++;
        }

    }



    // Сравниваем и получаем результат
    if (first_count > second_count) {
        result = 1;
    }

    else if (first_count < second_count) {
        result = 2;
    }

    else if (first_count == 0 && second_count == 0) {
        result = 3;
    }
    else {
        result = 0;
    }
    switch (result) {
    case 0:
        cout << "Кол-во одинаково в обеих строках" << endl;
        break;
    case 1:
        cout << "В первой строке символ встречается чаще" << endl;
        break;
    case 2:
        cout << "Во второй строке символ встречается чаще" << endl;
        break;
    case 3:
        cout << "Заданный символ не встречается ни в одной из строк" << endl;
        break;
    }
}
