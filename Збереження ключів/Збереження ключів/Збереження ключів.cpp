#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include <Windows.h>
#include <typeinfo>

#define MaxUsers 30

struct users{
    char name[20];
    char info[40];
    char num[5];
};

using namespace std;
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    fstream file;
    string path = "Users.txt";
    string username;
    int inUsername;
    bool check = false;
    file.open(path, fstream::out | fstream::in | fstream::app);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return 1;
    }
    else cout << "Файл найден!" << endl;    
    struct users users[MaxUsers];
    int i = 0;
    while (!file.eof()) {
        for (int j = 0; j < 3; j++) {
            char word[40];
            file >> word;
            switch (j) {
            case 0: {
                strcpy_s(users[i].name, word);
                break;
            }
            case 1: {
                strcpy_s(users[i].num, word);
                break;
            }
            case 2: {
                strcpy_s(users[i].info, word);
                break;
            }
            }
        }
        ++i;
    }
    while (true) {
        cout << "Войдите в программу или зарегестрируйтесь: ";       
        cin >> username;
        if (username == "Add") {
            file.close();
            file.open(path, fstream::out | fstream::in);
            char NewName[20], NewRoom[5], NewInfo[40], f[] = { "---" };
            bool CheckIf = true;
            cout << "Введите имя пользователя, номер комнаты и контактные данные: " << endl;
            cin >> NewName;
            cin >> NewRoom;
            cin >> NewInfo;
            for (int j = 0; j < i; j++) {
                if (!strcmp(users[j].name, "---")) {
                    strcpy_s(users[j].name, NewName);
                    strcpy_s(users[j].num, NewRoom);
                    strcpy_s(users[j].info, NewInfo);
                    CheckIf = false;
                    break;
                }
            }
            if (CheckIf) {
                strcpy_s(users[i].name, NewName);
                strcpy_s(users[i].num, NewRoom);
                strcpy_s(users[i].info, NewInfo);
                for (int newI = 0; newI < i + 1; newI++) {
                    for (int k = 0; k < 3; k++) {
                        switch (k) {
                        case 0: {
                            file << users[newI].name << " ";
                            break;
                        }
                        case 1: {
                            file << users[newI].num << " ";
                            break;
                        }
                        case 2: {
                            file << users[newI].info;
                            break;
                        }
                        }
                    }
                    if (newI < i)
                        file << endl;
                }
            }
            else {
                for (int newI = 0; newI < i; newI++) {
                    for (int k = 0; k < 3; k++) {
                        switch (k) {
                        case 0: {
                            file << users[newI].name << " ";
                            break;
                        }
                        case 1: {
                            file << users[newI].num << " ";
                            break;
                        }
                        case 2: {
                            file << users[newI].info;
                            break;
                        }
                        }
                    }
                    if (newI < i - 1)
                        file << endl;
                }
            }

            cout << "Данные успешно обновились, производится выход из программы, чтобы обновить информацию...";
            cin.get();
            cin.get();
            file.close();
            return 2;
        }
        else if (username == "Log-in") {
            cout << "Введите имя пользователя: ";
            cin >> username;
            for (int j = 0; j < i; j++) {
                if (username == users[j].name) {
                    check = true;
                    inUsername = j;
                }
            }
            if (check) {
                cout << "Вы вошли в программу успешно" << endl;
                break;
            }
            else cout << "Такого пользователя нет!" << endl;
        }
        else cout << "Команда не распознана!" << endl;
        
    }
    cin.get();
    cin.get();
    system("cls");
    while (true) {
        string foo;
        cout << "Выберите функцию которой хотите воспользоваться: ";
        getline(cin, foo);
        if (foo == "Delete user") {
            cout << "Вы уверены? ";
            cin >> foo;
            if (foo == "Да") {
                strcpy_s(users[inUsername].info, "---");
                strcpy_s(users[inUsername].name, "---");
                strcpy_s(users[inUsername].num, "---");
                cout << "Аккаунт успешно удален!"<<endl;
                cout << "Так как нет такого пользователя, производиться выход из приложения!"<<endl;
                cout << "Нажмите Enter чтобы выйти...";
                cin.get();
                cin.get();
                break;
            }
        }
        else if (foo == "Show-list") {
            for (int j = 0; j < i; j++) {
                for (int k = 0; k < 3; k++) {
                    switch (k) {
                    case 0: {
                        cout << users[j].name << " ";
                        break;
                    }
                    case 1: {
                        cout << users[j].num << " ";
                        break;
                    }
                    case 2: {
                        cout << users[j].info;
                        break;
                    }
                    }
                }
                if (j < i - 1)
                    cout << endl;
            }
        }
        else if (foo == "Sort-list") {
            bool NumFoo = true;
            int min, max, index, nk;
            int InMas[MaxUsers];
            for (int j = 0; j < i; j++) {
                InMas[j] = j;
            }
            while (true) {
                cout << "Сортировать номера комнат по возростанию(\"Ascending\") или по убыванию(\"Descending\"): ";
                getline(cin, foo);
                if (foo == "Ascending") {
                    NumFoo = true;
                    break;
                }
                else if (foo == "Descending") {
                    NumFoo = false;
                    break;
                }
                else cout << "Команда не распознана!" << endl;
            }
            cout << endl;
            if (NumFoo) {
                for (int j = 0; j < i; j++) {
                    min = stoi(users[InMas[j]].num);
                    index = InMas[j];
                    nk = j;
                    for (int k = j + 1; k < i;k++) {
                        if (min > stoi(users[InMas[k]].num)) {
                            min = stoi(users[InMas[k]].num);
                            index = InMas[k];
                            nk = k;
                        }
                    }
                    InMas[nk] = InMas[j];
                    InMas[j] = index;                   
                }
            }
            else {
                for (int j = 0; j < i; j++) {
                    max = stoi(users[InMas[j]].num);
                    index = InMas[j];
                    nk = j;
                    for (int k = j + 1; k < i;k++) {
                        if (max < stoi(users[InMas[k]].num)) {
                            max = stoi(users[InMas[k]].num);
                            index = InMas[k];
                            nk = k;
                        }
                    }
                    InMas[nk] = InMas[j];
                    InMas[j] = index;
                }
            }
            for (int j = 0; j < i; j++) {
                for (int k = 0; k < 3; k++) {
                    switch (k) {
                    case 0: {
                        cout << users[InMas[j]].name << " ";
                        break;
                    }
                    case 1: {
                        cout << users[InMas[j]].num << " ";
                        break;
                    }
                    case 2: {
                        cout << users[InMas[j]].info;
                        break;
                    }
                    }                    
                }
                cout << endl;
            }
        }
        else if (foo == "Find") {
            bool NumFoo = true;
            char user[10];          
            while (true) {
                cout << "Поиск за именем(\"By name\") владельца или за номером(\"By room\") комнаты: ";
                getline(cin, foo);
                if (foo == "By name") {
                    NumFoo = true;
                    break;
                }
                else if (foo == "By room") {
                    NumFoo = false;
                    break;
                }
                else cout << "Команда не распознана!" << endl;
            }

            if (NumFoo) {
                cout << "Введите имя пользователя: ";
                cin >> user;
                cout << endl;
                for (int j = 0; j < i; j++) {
                    if (!strcmp(users[j].name, user)) {
                        cout << users[j].name << " " << users[j].num << " " << users[j].info << endl;
                    }
                }
            }
            else {
                cout << "Введите номер комнаты пользователя: ";
                cin >> user;
                cout << endl;
                for (int j = 0; j < i; j++) {
                    if (!strcmp(users[j].num, user)) {
                        cout << users[j].name << " " << users[j].num << " " << users[j].info << endl;
                    }
                }
            }
            
        }
        else if (foo == "Edit") {
            char NextFoo[40];
            int NumFoo;
            
            while (true) {
                cout << "Введите что хотите редактировать: ";
                cin >> foo;
                if (foo == "Name") {
                    NumFoo = 0;
                    break;
                }
                else if (foo == "Room") {
                    NumFoo = 1;
                    break;
                }
                else if (foo == "Info") {
                    NumFoo = 2;
                    break;
                }
                else cout << "Команда не распознана!" << endl;
            }
            cout << "Введите изменение: ";
            cin >> NextFoo;
            if (NumFoo == 0) {
                strcpy_s(users[inUsername].name, NextFoo);
            }
            else if (NumFoo == 1) {
                strcpy_s(users[inUsername].num, NextFoo);
            }
            else {
                strcpy_s(users[inUsername].info, NextFoo);
            }
            cout << "Данные успешно обновились, производится выход из программы, чтобы обновить информацию...";
            cin.get();
            cin.get();
            break;
        }
        else cout << "Команда не распознана!";
        cout << "\nХотите продолжить? ";
        cin >> foo;
        if (foo == "Exit") {
            cout << "Хорошего дня!\nНажмите Enter чтобы выйти...";
            cin.get();
            cin.get();
            break;
        }
        else cout << "Работа программы продолжается!";
        cin.get();
        cin.get();
        system("cls");
    }
    file.close();
    file.open(path, fstream::out);
    for (int newI = 0; newI < i; newI++) {
        for (int k = 0; k < 3; k++) {
            switch (k) {
            case 0: {
                file << users[newI].name << " ";
                break;
            }
            case 1: {
                file << users[newI].num << " ";
                break;
            }
            case 2: {
                file << users[newI].info;
                break;
            }
            }
        }
        if (newI < i-1)
        file << endl;
    }
}