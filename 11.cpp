// 11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h> 
#include <cstdlib>
#include <windows.h>
using namespace std;
void _ignore(char*& s, char*& p, char c);
long _remcomm(char* s);
bool remove_comments(const char* output, const char* input);

int main(void) 
{
    int vib;
    HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    setlocale(0, "");
    cout << "Здравствуйте, эта программа удаляет комментарии из текста программы в файле и результат запиывает в другой файл. "<<endl;
    SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << ">---------------------------------------<" << endl;
    do 
    {
        SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "Введите ";
        SetConsoleTextAttribute(hOUTPUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "1 ";
        SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "или ";
        SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "	0." << endl;
        SetConsoleTextAttribute(hOUTPUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "1 ";
        SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << " - выполнение программы" << endl;
        SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "0 ";
        SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << " - выход из программы" << endl;
        SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << ">---------------------------------------<" << endl;
        SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "Ваш выбор: ";
        SetConsoleTextAttribute(hOUTPUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cin >> vib;
        SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << ">---------------------------------------<" << endl;
        switch (vib)
        {
        case 1:
        {
            char input[] = "D:\\240.cpp";//входной файл
            char output[] = "D:\\241.cpp";//выходной файл

            if (!remove_comments(output, input))
            {
                SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "Ошибка!" << endl;
            }
            else
            {
                SetConsoleTextAttribute(hOUTPUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << "программа выполнена успешно.результат записан в выходной файл." << endl;
            }
        }
        case 0:
        {

            SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "программа успешно завершена. " << endl;
            system("pause");
            break;
        }
        }
    } while (vib == 1);
}

bool remove_comments(const char* output, const char* input) 
{
    long n, m;
    ifstream fin(input, ifstream::binary);
    if (!fin.is_open())
        return false;

    fin.seekg(0, fin.end);
    if ((n = fin.tellg()) <= 0)
        return false;

    char* s = new (nothrow) char[n + 1];
    if (s == NULL)
        return false;

    fin.seekg(0, fin.beg);
    fin.read(s, n);
    m = fin.gcount();
    fin.close();

    if (m != n) {
        delete[] s;
        return false;
    }
    s[n] = '\0';
    m = _remcomm(s);

    ofstream fout(output, ofstream::binary);
    if (fout.is_open())
    {
        fout.write(s, m);
        fout.flush();
        fout.close();
    }
    delete[] s;
    return true;
}

long _remcomm(char* s) {
    char* i, * t = s;
    for (char* p = s; *s; *s = *p) {
        if ((*p == '"') || (*p == '\''))
            _ignore(s, p, *p);
        else if ((*p == '/') && (*(p + 1) == '/')) 
        { 
            // однострочные комментарии
            i = p + 2;
            while (*i && (*i != '\r') && (*i != '\n'))
                ++i;
            p = i;
        }
        else if ((*p == '/') && (*(p + 1) == '*')) { // многострочные комментарии
            i = p + 2;
            while (*i) {
                if ((*i == '*') && (*(i + 1) == '/')) {
                    i += 2;
                    break;
                }
                ++i;
            }
            p = i;
        }
        else
            ++s, ++p;
    }
    return (long)(s - t);
}

//пропуск
void _ignore(char*& s, char*& p, char c) {
    char* i = p + 1;
    while (*i && (*i != c)) {
        if (*i == '\\')
            ++i;
        ++i;
    }
    if (*i == c)
        ++i;

    while (p != i)
        *s++ = *p++;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
