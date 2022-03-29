#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

void Help(bool full); //Виклик допомоги
double GetValue(); //Перевірка на правильність вводу даних

//Віртуальній класс
class Expenses 
{	
protected:
	ifstream fread; //Об'єкт для зчитування даних з БД
	ofstream fwrite; //Об'єкт для запису даних до БД
	string filepath; //Шлях до БД
	double limit; //Ліміт на витрати в певній галузі
	double spends;	//Кількість грошей витрачених в певній галузі
public:
	//Геттер для spends
	double GetSpended();
	//Геттер для limit
	double GetLimit();
	//Метод для додавання витрачених грошей
	virtual void AddSpends(double spends) = 0;
	//Метод, що показує скільки витратили в певній галузі
	virtual void ShowSpended() const = 0;
	//Метод для встановлення ліміту на витрати
	virtual void SetLimit(double limit) = 0;
	//Встановлення даних з БД
	virtual void SetFromDB() = 0;
	//Оновлення даних БД
	virtual void UpdateDB() = 0;
};

//Класс для витат на їжу
class FoodExpenses : public Expenses {
	//Загальна кількість грошей
	double money;
public:
	//Конструктори
	FoodExpenses(string filepath);
	FoodExpenses(string filepath, double spends);
	FoodExpenses(string filepath, double spends, double limit);
	void AddSpends(double spends) override;
	void ShowSpended() const override;
	//Метод для встановлення кількості грошей
	void SetMoney(double money);
	//Метод, що показує залишок
	void ShowRests(Expenses& e1, Expenses& e2, Expenses& e3, Expenses& e4) const;
	void SetLimit(double limit) override;
	void SetFromDB() override;
	void UpdateDB() override;
};


//Класс для витат на комунальні послуги
class Utilities : public Expenses {
public:
	Utilities(string filepath);
	Utilities(string filepath, double spends);
	Utilities(string filepath, double spends, double limit);
	void AddSpends(double spends) override;
	void ShowSpended() const override;
	void SetLimit(double limit) override;
	void SetFromDB() override;
	void UpdateDB() override;
};


//Класс для витат на одяг
class ClothesExpenses : public Expenses {
public:
	ClothesExpenses(string filepath);
	ClothesExpenses(string filepath, double spends);
	ClothesExpenses(string filepath, double spends, double limit);
	void AddSpends(double spends) override;
	void ShowSpended() const override;
	void SetLimit(double limit) override;
	void SetFromDB() override;
	void UpdateDB() override;
};


//Класс для інших витат та розваг
class EntertainmentExpenses : public Expenses {
public:
	EntertainmentExpenses(string filepath);
	EntertainmentExpenses(string filepath, double spends);
	EntertainmentExpenses(string filepath, double spends, double limit);
	void AddSpends(double spends) override;
	void ShowSpended() const override;
	void SetLimit(double limit) override;
	void SetFromDB() override;
	void UpdateDB() override;
};


