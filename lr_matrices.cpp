
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;

// ���������� ���������
const int k_max_matrix_size = 5; // ������������ ������ ������� ���������� �������
const char k_reading_method = '3'; // ����� ������ ������. '1' - �������, '2' - ����, '3' - ��������� �����
const string k_file_name = "File.txt"; // ��� ����� �������� ������ 


// ��������� �������
void read_data_from_console(int*** pointer_to_pointer_to_dynamic_matrix, int& dynamic_matrix_size);
void read_data_from_file(int*** pointer_to_pointer_to_dynamic_matrix, int& dynamic_matrix_size);
void fill_with_random_numbers(int*** pointer_to_pointer_to_dynamic_matrix, int& dynamic_matrix_size);
void calculation_of_sums(int** dynamic_matrix, const int& dynamic_matrix_size);


// �������� ���������
int main() {



    /// ---------------------------------------------------------------------------
    /// ---------------------------------- ������ ����� ---------------------------
    /// ----------------------- ���������� ����������, ���� ������ ----------------
    /// ---------------------------------------------------------------------------



    // ����������� �������� �����
    setlocale(LC_ALL, "Russian");



    // �������� ������� ��������� ��������� �����
    srand(time(NULL));



    // ���������� ����������: 
    int** dynamic_matrix = NULL; // �������
    int dynamic_matrix_size; // ������ �������




    // ���� ������ 
    switch (k_reading_method){
    case '1': // ������ �� �������

        // ���������� ������ �� �������:
        read_data_from_console(&dynamic_matrix, dynamic_matrix_size);

        break;

    case '2': // ������ �� �����

        // ���������� ������ �� �����:
        read_data_from_file(&dynamic_matrix, dynamic_matrix_size);

        break;

    case '3': // ���������� ���������� �������

        // �������� ������� ���������� �������:
        fill_with_random_numbers(&dynamic_matrix, dynamic_matrix_size);

        break;

    } // ����� ����� "���� ������"



    /// ---------------------------------------------------------------------------
    /// ---------------------------------- ������ ����� ---------------------------
    /// ------------------------ ������� ��������� � ������ ����� -----------------
    /// ---------------------------------------------------------------------------



    // ���������� ��������� �����:
    calculation_of_sums(dynamic_matrix, dynamic_matrix_size);


    return 0;


}



// ������� ������ ������ �� �������
void read_data_from_console(int*** pointer_to_pointer_to_dynamic_matrix, int& dynamic_matrix_size) {

    cout << "\n���� ������ �� �������\n\n";

    // ������ �������: ����
    cout << "������� ������ �������: ";
    cin >> dynamic_matrix_size;


    // ������ �������: 1-�� �������� �� ������������ (�������� �� ������)
    if (!cin.good()) {
        cout << "������ ��� ����� �� ������� (�1).\n"
            << "����������� ������ ������ ������� - �� ������ ���� ����� ������.\n";
        exit(1);
    }


    // ������ �������: 2-�� �������� �� ������������ (����������� �� ������� ���������� ��������)
    if ((dynamic_matrix_size < 1) || (dynamic_matrix_size > k_max_matrix_size)) {
        cout << "������ ��� ����� �� ������� (�2).\n"
            << "������ ������������ ������ ������� - �� ������ ������������ ������� ���������� ��������\n"
            << "(�� ���� ���� � �������� �� 1 �� ������������� ����������� �������).\n";
        exit(2);
    }


    // ������ �������: ���-�����
    cout << "������ ������� = " << dynamic_matrix_size << endl;


    // �������� ����� ������������ ������
    int** new_dynamic_matrix = new int* [dynamic_matrix_size];


    // ������ �������� �������, �������� ������ �������� ������� �� ������������
    for (int i = 0; i < dynamic_matrix_size; i++) {

        // � i-�� ������ ������� ����� �������� ������ ��������� ������
        new_dynamic_matrix[i] = new int[dynamic_matrix_size];

        for (int j = 0; j < dynamic_matrix_size; j++) {

            // ������ ��������� �������
            cin >> new_dynamic_matrix[i][j];

            // ���������, �������� �� �� ������
            if (!cin.good()) {
                cout << "������ ��� ����� �� ������� (�3).\n"
                    << "����������� ������ ������� ������� - �� ������ ���� ����� ������.\n";
                exit(3);
            }

        }

    } // ����� ����� "������ �������� �������, �������� ������ �������� ������� �� ������������"


    // �������� ��� ��������� � ������� main �� ������ ��� ����������� ������������ ������:
    *pointer_to_pointer_to_dynamic_matrix = new_dynamic_matrix;


    // ���-�����:
    for (int i = 0; i < dynamic_matrix_size; i++) {

        for (int j = 0; j < dynamic_matrix_size; j++) {

            cout << new_dynamic_matrix[i][j] << " ";

        }

        cout << endl;

    }

    // ������� ����� �����:
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}





// ������� ������ ������ �� �����
void read_data_from_file(int*** pointer_to_pointer_to_dynamic_matrix, int& dynamic_matrix_size){


    cout << "\n���� ������ �� �����\n\n";

    // ������� ������� ����
    ifstream file;
    file.open(k_file_name);

    // ��������, ���������� �� ������� ����
    if (!file.is_open()) {
        cout << "������ ��� ����� �� ����� (�4).\n"
            << "�� ������� ������� ����.\n";
        exit(4);
    }

    // ������ �������: ����
    file >> dynamic_matrix_size;


    // ������ �������: 1-�� �������� �� ������������ (�������� �� ������)
    if (!file.good()) {
        cout << "������ ��� ����� �� ����� (�5).\n"
            << "����������� ������ ������ ������� - �� ������ ���� ����� ������.\n";
        exit(5);
    }


    // ������ �������: 2-�� �������� �� ������������ (����������� �� ������� ���������� ��������)
    if ((dynamic_matrix_size < 1) || (dynamic_matrix_size > k_max_matrix_size)) {
        cout << "������ ��� ����� �� ����� (�6).\n"
            << "������ ������������ ������ ������� - �� ������ ������������ ������� ���������� ��������\n"
            << "(�� ���� ���� � �������� �� 1 �� ������������� ����������� �������).\n";
        exit(6);
    }


    // ������ �������: ���-�����
    cout << "������ ������� = " << dynamic_matrix_size << endl;


    // �������� ����� ������������ ������
    int** new_dynamic_matrix = new int* [dynamic_matrix_size];


    // ������ �������� �������, �������� ������ �������� ������� �� ������������
    for (int i = 0; i < dynamic_matrix_size; i++) {

        // � i-�� ������ ������� ����� �������� ������ ��������� ������
        new_dynamic_matrix[i] = new int[dynamic_matrix_size];

        for (int j = 0; j < dynamic_matrix_size; j++) {

            // ������ ��������� �������
            file >> new_dynamic_matrix[i][j];

            // ���� �������� �� ������� ��� ���� �� �� �����, ������� ������
            if (!file.good()) {
                cout << "������ ��� ����� �� ����� (�7).\n"
                    << "���� �� ��������� ������� ����������� ��� ��� �� �������.\n";
                exit(7);
            }
        }

    } // ����� ����� "������ �������� �������, �������� ������ �������� ������� �� ������������"


    // �������� ��� ��������� � ������� main �� ������ ��� ����������� ������������ ������:
    *pointer_to_pointer_to_dynamic_matrix = new_dynamic_matrix;


    // ��������, �� �������� �� � ����� ������ �����
    char a;
    file.get(a);
    file.get(a);
    if (!file.eof()) {
        cout << "������ ��� ����� �� ����� (�8).\n"
            << "� ����� ���� ������ ��������.\n";
        exit(8);
    }

    // ���-����� �������:
    cout << "\n������� �������:\n";
    for (int i = 0; i < dynamic_matrix_size; i++) {

        for (int j = 0; j < dynamic_matrix_size; j++) {

            cout << new_dynamic_matrix[i][j] << " ";

        }

        cout << endl;

    } // ����� ����� "���-����� �������"
    cout << endl;


    // ������� ����� �����:
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}





// ������� ������� ��������� ����
void calculation_of_sums(int** dynamic_matrix, const int& dynamic_matrix_size) {

    // ���������� ����������
    int sum_in_all_strings = 0; // ����� �� ���� �������
    int sum_in_current_string; // ����� � ������� ������
    int sum_minimal = -1; // ����������� ����� ���� 
    int sum_minimal_id; // ����� ������, � ������� ����������� �����
    bool string_has_negative_elements; // ���������� ��������, ���� �� � ������ ������������� �����

    // ������� �����:
    for (int i = 1; i < dynamic_matrix_size; i++) {

        sum_in_current_string = 0; // � ������� ������ ���������� ����� �� ���������
        string_has_negative_elements = false; //  � ������� ������ ���������� �� ������� ������������� ��������

        // ������� ��������� � ������ �� ������� ���������:
        for (int j = 0; j < i; j++) {

            // ���� � ������ ���� ������������� ��������, "��������" ���:
            if (dynamic_matrix[i][j] < 0) {

                string_has_negative_elements = true;
                break;

            }

            // �������� � ����� ����� ����� ��������� ���� ������
            sum_in_current_string += dynamic_matrix[i][j];

        }

        // ���� � ������ �� ������� ������������� ���������:
        if (!string_has_negative_elements) {

            sum_in_all_strings += sum_in_current_string; // �������� � ����� ����� �� ���� ����� ����� ���� ������

            // ���� � ������� �� ��� ��� �� ���� ������� �� ���� ������ ��� ������������� ���������:
            if (sum_minimal == -1) {

                // ����� ��������� � ���� ������ ����� �����������
                sum_minimal = sum_in_current_string;
                sum_minimal_id = i;

            }
            else {

                // ���� � ���� ������ ����� ������, ��� ����������� ����� ����� ������ �����:
                if (sum_in_current_string < sum_minimal) {

                    // ����� ��������� � ���� ������ ����� �����������
                    sum_minimal = sum_in_current_string;
                    sum_minimal_id = i;

                }

            }

        }

    }


    // ���� �� ����� �� ����� ���������� ������:
    if (sum_minimal == -1) {

        cout << "����� �1: " << 0
            << "\n(��� ����� ��������� �����, ����������� ��� ������� ���������� � �� ������� ��� ������������� ���������)" << endl;
        cout << "����� �2: " << 0
            << "\n(��� ����������� �� ���� ��������� �����, ����������� ��� ������� ���������� � �� ������� ��� ������������� ���������)" << endl;

    }
    else {

        cout << "����� �1: " << sum_in_all_strings
            << "\n(��� ����� ��������� �����, ����������� ��� ������� ���������� � �� ������� ��� ������������� ���������)" << endl;
        cout << "����� �2: " << sum_minimal << ", ������� �� ������: " << sum_minimal_id
            << "\n(��� ����������� �� ���� ��������� �����, ����������� ��� ������� ���������� � �� ������� ��� ������������� ���������)" << endl;

    }

}

// ������� ���������� ������� ���������� �������
void fill_with_random_numbers(int*** pointer_to_pointer_to_dynamic_matrix, int& dynamic_matrix_size) {

    cout << "\n���� ��������� ������\n\n";

    // ������� ��������� �������� ��� ������� ������� 
    dynamic_matrix_size = (rand() % k_max_matrix_size) + 1;

    cout << "��������� ������ �������: " << dynamic_matrix_size << endl << endl;


    // �������� ����� ������������ ������
    int** new_dynamic_matrix = new int* [dynamic_matrix_size];


    // �������� ������� ���������� �������
    for (int i = 0; i < dynamic_matrix_size; i++) {

        // � i-�� ������ ������� ����� �������� ������ ��������� ������
        new_dynamic_matrix[i] = new int[dynamic_matrix_size];

        for (int j = 0; j < dynamic_matrix_size; j++) {

            new_dynamic_matrix[i][j] = (rand() % 20) - 10;

        }

    }


    // �������� ��� ��������� � ������� main �� ������ ��� ����������� ������������ ������:
    *pointer_to_pointer_to_dynamic_matrix = new_dynamic_matrix;


    // ������� ���������� �������:
    cout << "����������� ���������� ������� �������: " << endl;
    for (int i = 0; i < dynamic_matrix_size; i++) {

        for (int j = 0; j < dynamic_matrix_size; j++) {

            cout << new_dynamic_matrix[i][j] << " ";

        }

        cout << endl;

    }

    cout << endl;
}