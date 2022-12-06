// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <cstring>

using namespace std;

void setTextColor(int textColorIndex) { // Смена цвета текста
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, (0 << 4) + textColorIndex);
}


bool isRestartNeeded() { // Функция перезапуска программы
    cout << '\n';
    cin.clear(); // Очистка ввода от ошибок
    cin.sync();
    cout << "Перезагрузить программу? [";
    setTextColor(2);
    cout << "Y";
    setTextColor(15);
    cout << "/";
    setTextColor(4);
    cout << "любой другой символ";
    setTextColor(15);
    cout << "] ";
    string answer;
    cin >> answer;
    if (answer == "y" || answer == "Y")
        return true;
    else
        return false;
}
string reading(string FileName)
{
    ifstream File;   // Создали поток ввода для чтения данных из файла
    File.open(FileName);  // Открыли файл
    if (!File.is_open())  //  Проверили удалось ли открыть файл
    {
        cout << "Открыть файл не удалось!\n";
        return 0;   // Файл не открыт
    }
    char S[1000];
    File.getline(S, 1000);
    cout << S << endl;
    File.close();  // Закрываем файл
    return S;

}


bool isAllowedSymbol(char c) {
    string allowed = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789";
    for (int i = 0; i < allowed.length(); i++) {
        if (c == allowed[i])
            return TRUE;
    }
    return FALSE;
}

bool isUpper(char c) {
    string allowed = "QWERTYUIOPASDFGHJKLZXCVBNM";
    for (int i = 0; i < allowed.length(); i++) {
        if (c == allowed[i])
            return TRUE;
    }
    return FALSE;
}

bool isNumber(char c) {
    string allowed = "0123456789";
    for (int i = 0; i < allowed.length(); i++) {
        if (c == allowed[i])
            return TRUE;
    }
    return FALSE;
}
bool isInIndexes(int n, int indexes[], int length) {
    for (int i = 0; i < length; i++) {
        if (n == indexes[i])
            return TRUE;
    }
    return FALSE;
}

int main()
{
    setlocale(0, "");
    setTextColor(15);
    string str;
    int choice;
    cout << "Как ввести символы?\n";
    setTextColor(6);
    cout << "[1] ";
    setTextColor(15);
    cout << "С клавиатуры\n";
    setTextColor(6);
    cout << "[2] ";
    setTextColor(15);
    cout << "С файла\n";
    cin >> choice;
    switch (choice) {
    case 1:
        cin.clear();
        cin.sync();
        cin.ignore();
        cout << "Введите текст: ";
        getline(cin, str);
        break;
    case 2:
        cout << "Чтение данных...\n";
        Sleep(1000);
        str = reading("C:\\LR4.txt");
        break;
    default:
        setTextColor(4);
        cout << "Введено неверное число!\n";
        setTextColor(15);
        if (isRestartNeeded())
            main();
        else
            return 0;
    }
    for (int i = str.length() - 1; i > 1; i--) {
        if (str[i] == '.' and str[i - 1] == '.' and str[i - 2] == '.')
            str.replace(i - 2, 3, "$");
    }
    for (int i = str.length() - 2; i > -1; i--) {
        if (not(isAllowedSymbol(str[i])) and str[i] == str[i + 1])
            str.erase(i + 1, 1);
    }
    for (int i = str.length() - 1; i > -1; i--) {
        if (str[i] == '$')
            str.replace(i, 1, "...");
    }
    for (int i = 1; i < str.length(); i++) {
        if (isUpper(str[i]) and str[i - 1] != ' ')
            str[i] = (char) (((int) str[i]) + 32);
    }
    cout << "\nОбработанный текст:\n";
    cout << str << '\n';
    
    cout << "\nВывод изменённой строки #1:\n";

    char firstLatter = str[0];
    int firstLatterIndex = 0;
    bool flag = FALSE;
    string tempWord = "";
    tempWord += str[0];
    for (int i = 1; i < str.length(); i++) {
        if (isAllowedSymbol(str[i]) and not(isAllowedSymbol(str[i - 1]))) {
            tempWord += str[i];
            firstLatter = str[i];
            firstLatterIndex = i;
        }
        else if (isAllowedSymbol(str[i]) and isAllowedSymbol(str[i - 1])) {
            tempWord += str[i];
            if (str[i] == firstLatter)
                flag = TRUE;
        }
        else if (not(isAllowedSymbol(str[i])) and isAllowedSymbol(str[i - 1])) {
            if (flag) { 
                cout << tempWord;
                flag = FALSE;
            }
            tempWord = "";
        }
        if (not(isAllowedSymbol(str[i]))) {
            cout << str[i];
        }

    }
    cout << "\nВывод изменённой строки #2:\n";

    tempWord = "";
    if (isNumber(str[0]))
        tempWord += str[0];
    else
        cout << str[0];
    for (int i = 1; i < str.length(); i++) {
        if (isAllowedSymbol(str[i]) and not(isAllowedSymbol(str[i - 1]))) {
            if (isNumber(str[i]))
                tempWord += str[i];
            else
                cout << str[i];
        }
        else if (isAllowedSymbol(str[i]) and isAllowedSymbol(str[i - 1])) {
            if (isNumber(str[i]))
                tempWord += str[i];
            else
                cout << str[i];
        }
        else if (not(isAllowedSymbol(str[i])) and isAllowedSymbol(str[i - 1])) {
            cout << tempWord;
            tempWord = "";
        }
        if (not(isAllowedSymbol(str[i]))) {
            cout << str[i];
        }

    }

    string substring;
    int substringIndexes[1000];
    int substringCounter = 0;
    cout << "\n\nВведите подстроку для поиска: ";
    cin >> substring;


    for (int i = 0; i < str.length() - substring.length() + 1; i++) {
        int counter = 0;
        for (int j = 0; j < substring.length(); j++) {
            if (str[i + j] == substring[j])
                counter++;
        }
        if (counter == substring.length()) {
            substringIndexes[substringCounter] = i;
            substringCounter++;
        }
    }



    int latters[128];
    for (int i = 32; i < 128; i++)
        latters[i] = substring.length();


    for (int i = substring.length() - 2; i > -1; i--) {
        if (latters[(int)substring[i]] == substring.length())
            latters[(int)substring[i]] = substring.length() - 1 - i;
    }

    int i = substring.length() - 1;
    while (i < str.length()) {
        int counter = 0;
        for (int j = 0; j < substring.length(); j++) {
            if (str[i - j] != substring[substring.length() - 1 - j]) {
                i += latters[(int)str[i]];
                break;
            }
            counter++;
        }
        if (counter == substring.length()) {
            cout << i - substring.length() + 1 << ' ';
            i += latters[(int)str[i]];
        }
    }
    cout << '\n';

    int counter = 0;
    int lastKnownIndex = -1000;
    for (int i = 0; i < str.length(); i++) {
        if (isInIndexes(i, substringIndexes, substringCounter)) {
            setTextColor(6);
            lastKnownIndex = i;
        }
        if (i - lastKnownIndex == substring.length())
            setTextColor(15);
        cout << str[i];
    }
    setTextColor(15);


    if (isRestartNeeded()) {
        system("cls");
        main();
    }
    else
        return 0;
}

