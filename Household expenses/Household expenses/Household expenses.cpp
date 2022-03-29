#include "Expenses.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <locale>

using namespace std;

int main()
{
	bool full = true; //Повний доступ - true, неповний - false
	string access;
	//Перевірка на повний доступ до програми
	while (true)
	{
		cout << "Ви хочете увійти як дитина(child) чи батько(parent)?" << endl;
		cin >> access;
		if (access == "child") {
			full = false;
			break;
		}
		else if (access == "parent") {
			full = true;
			break;
		}
		else {
			cout << "Незрозуміла команда." << endl;
			_getch();
		}
		system("cls");
	}
	cout << "Вхід виконан." << endl;
	cin.get();
	system("cls");
	string filepath = "DB.txt";
	//Створення обьектів
	FoodExpenses foodexpenses(filepath);
	Utilities utilities(filepath);
	ClothesExpenses clothes(filepath);
	EntertainmentExpenses entertainment(filepath);

	//Перенесення даних з БД до обьектів
	try
	{
		foodexpenses.SetFromDB();
		utilities.SetFromDB();
		clothes.SetFromDB();
		entertainment.SetFromDB();
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
		return 1;
	}
	cin.get();

	bool exit = true;
	double value;
	while (exit)
	{
		system("cls");
		cout << "Дія (1)" << endl;
		cout << "f1 - допомога         esc - вихід         enter - далі та вибір дії" << endl;
		int firstbut = _getch(); //Перевірка на початкову дію

		//Натиснута кнопка f1
		if (firstbut == 0) {
			firstbut = _getch();
			if (firstbut == 59) {
				Help(full);
				cin.get();
			}

		}

		//Натиснута кнопка esc
		else if (firstbut == 27) {
			exit = false;
		}

		//Вибір дії
		else {
			system("cls");
			cout << "Дія (2)" << endl;
			cout << "f1 - допомога          esc - назад         enter - далі та вибір дії" << endl;
			firstbut = _getch(); //Перевірка на початкову дію

			//Натиснута кнопка f1
			if (firstbut == 0) {
				firstbut = _getch();
				if (firstbut == 59) {
					Help(full);
					cin.get();
					continue;
				}

			}

			//Натиснута кнопка esc
			else if (firstbut == 27) {
				continue;
			}

			string command;
			getline(cin, command);
			//Користувач ввів Show expenses
			if (command == "Show expenses") {
				cout << "\nДія (3)";
				while (true)
				{
					cout << endl;
					firstbut = _getch(); //Перевірка на початкову дію

					//Натиснута кнопка f1
					if (firstbut == 0) {
						firstbut = _getch();
						if (firstbut == 59) {
							Help(full);
							cin.get();
						}

					}

					//Натиснута кнопка esc
					else if (firstbut == 27) {
						break;
					}

					else {
						//Вибір витрат через консоль
						getline(cin, command);
						if (command == "For foodexpenses") {
							foodexpenses.ShowSpended();
							cin.get();
							break;
						}
						else if (command == "For utilities" && full) {
							utilities.ShowSpended();
							cin.get();
							break;
						}
						else if (command == "For clothes") {
							clothes.ShowSpended();
							cin.get();
							break;
						}
						else if (command == "For entertainment") {
							entertainment.ShowSpended();
							cin.get();
							break;
						}
						else if (command == "All") {
							foodexpenses.ShowSpended();
							if (full) utilities.ShowSpended();
							clothes.ShowSpended();
							entertainment.ShowSpended();
							cin.get();
							break;
						}
						//Якщо користувач ввів команду не правильно
						else {
							cout << "Незрозуміла команда." << endl;
						}
					}
				}
			}
			//Користувач ввів Add expenses
			else if (command == "Add expenses") {
				cout << "\nДія (3)";
				while (true)
				{
					cout << endl;
					firstbut = _getch(); //Перевірка на початкову дію

					//Натиснута кнопка f1
					if (firstbut == 0) {
						firstbut = _getch();
						if (firstbut == 59) {
							Help(full);
							cin.get();
						}

					}

					//Натиснута кнопка esc
					else if (firstbut == 27) {
						break;
					}

					else {
						//Вибір витрат через консоль
						getline(cin, command);
						if (command == "For foodexpenses") {
							value = GetValue();
							foodexpenses.AddSpends(value);
							cin.get();
							break;
						}
						else if (command == "For utilities" && full) {
							value = GetValue();
							utilities.AddSpends(value);
							cin.get();
							break;
						}
						else if (command == "For clothes") {
							value = GetValue();
							clothes.AddSpends(value);
							cin.get();
							break;
						}
						else if (command == "For entertainment") {
							value = GetValue();
							entertainment.AddSpends(value);
							cin.get();
							break;
						}

						else {
							cout << "Незрозуміла команда." << endl;
						}
					}
				}
			}
			//Користувач ввів Show limit
			else if (command == "Show limit") {
				cout << "\nДія (3)";
				while (true)
				{
					cout << endl;
					firstbut = _getch(); //Перевірка на початкову дію

					//Натиснута кнопка f1
					if (firstbut == 0) {
						firstbut = _getch();
						if (firstbut == 59) {
							Help(full);
							cin.get();
						}

					}

					//Натиснута кнопка esc
					else if (firstbut == 27) {
						break;
					}

					else {
						//Вибір витрат
						getline(cin, command);
						if (command == "For foodexpenses") {
							cout << "Ліміт на витрати на їжу дорівнює " << foodexpenses.GetLimit() << " гривень." << endl;
							cin.get();
							break;
						}
						else if (command == "For utilities" && full) {
							cout << "Ліміт на витрати на комунальні послуги дорівнює " << utilities.GetLimit() << " гривень." << endl;
							cin.get();
							break;
						}
						else if (command == "For clothes") {
							cout << "Ліміт на витрати на одяг дорівнює " << clothes.GetLimit() << " гривень." << endl;
							cin.get();
							break;
						}
						else if (command == "For entertainment") {
							cout << "Ліміт на витрати на розваги дорівнює " << entertainment.GetLimit() << " гривень." << endl;
							cin.get();
							break;
						}
						else if (command == "All") {
							cout << "Ліміт на витрати на їжу дорівнює " << foodexpenses.GetLimit() << " гривень." << endl;
							if (full) cout << "Ліміт на витрати на комунальні послуги дорівнює " << utilities.GetLimit() << " гривень." << endl;
							cout << "Ліміт на витрати на одяг дорівнює " << clothes.GetLimit() << " гривень." << endl;
							cout << "Ліміт на витрати на розваги дорівнює " << entertainment.GetLimit() << " гривень." << endl;
							cin.get();
							break;
						}
						else {
							cout << "Незрозуміла команда." << endl;
						}
					}
				}
			}
			//Користувач ввів Set limit та має повний доступ до програми
			else if (command == "Set limit" && full) {
				cout << "\nДія (3)";
				while (true)
				{
					cout << endl;
					firstbut = _getch(); //Перевірка на початкову дію

					//Натиснута кнопка f1
					if (firstbut == 0) {
						firstbut = _getch();
						if (firstbut == 59) {
							Help(full);
							cin.get();
						}

					}

					//Натиснута кнопка esc
					else if (firstbut == 27) {
						break;
					}

					else {

						getline(cin, command);
						if (command == "For foodexpenses") {
							value = GetValue();
							foodexpenses.SetLimit(value);
							cin.get();
							break;
						}
						else if (command == "For utilities" && full) {
							value = GetValue();
							utilities.SetLimit(value);
							cin.get();
							break;
						}
						else if (command == "For clothes") {
							value = GetValue();
							clothes.SetLimit(value);
							cin.get();
							break;
						}
						else if (command == "For entertainment") {
							value = GetValue();
							entertainment.SetLimit(value);
							cin.get();
							break;
						}
						else {
							cout << "Незрозуміла команда." << endl;
						}
					}
				}
			}
			//Користувач ввів Show rest of money
			else if (command == "Show rest of money") {
				cout << "\nДія (3)";
				while (true)
				{
					cout << endl;
					firstbut = _getch(); //Перевірка на початкову дію

					//Натиснута кнопка f1
					if (firstbut == 0) {
						firstbut = _getch();
						if (firstbut == 59) {
							Help(full);
							cin.get();
						}

					}

					//Натиснута кнопка esc
					else if (firstbut == 27) {
						break;
					}

					else {
						foodexpenses.ShowRests(foodexpenses, utilities, clothes, entertainment);
						_getch();
						break;
					}
				}
			}
			//Користувач ввів Set amount of money та має повний доступ до програми
			else if (command == "Set amount of money" && full) {
				cout << "\nДія (3)";
				while (true)
				{
					cout << endl;
					firstbut = _getch(); //Перевірка на початкову дію

					//Натиснута кнопка f1
					if (firstbut == 0) {
						firstbut = _getch();
						if (firstbut == 59) {
							Help(full);
							cin.get();
						}

					}

					//Натиснута кнопка esc
					else if (firstbut == 27) {
						break;
					}

					else {
						value = GetValue();
						foodexpenses.SetMoney(value);
						_getch();
						break;
					}
				}
			}
			else {
				cout << "Незрозуміла команда." << endl;
				_getch();
			}
		}
	}
	system("cls");
	try
	{
		foodexpenses.UpdateDB();
		utilities.UpdateDB();
		clothes.UpdateDB();
		entertainment.UpdateDB();
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
		return 2;
	}

}