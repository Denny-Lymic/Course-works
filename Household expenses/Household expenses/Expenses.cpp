#include "Expenses.h"

double Expenses::GetSpended()
{
	return this->spends;
}

double Expenses::GetLimit()
{
	return this->limit;
}

FoodExpenses::FoodExpenses(string filepath)
{
	this->limit = 0.0;
	this->spends = 0.0;
	this->filepath = filepath;
	this->money = 0.0;
}

FoodExpenses::FoodExpenses(string filepath, double spends) :FoodExpenses(filepath)
{
	this->spends = spends;
}

FoodExpenses::FoodExpenses(string filepath, double spends, double limit) : FoodExpenses(filepath, spends)
{
	this->limit = limit;
}

void FoodExpenses::AddSpends(double spends)
{
	if (this->spends + spends < this->limit) {
		this->spends += spends;
		cout << "Ви успішно підвищили витрати на їжу." << endl;
	}
	else {
		cout << "Ви перевищили ліміт на витрати на їжу!" << endl;
	}
}

void FoodExpenses::ShowSpended() const
{
	cout << "Витрачено на їжу " << round(this->spends * 100) / 100 << " гривень." << endl;
}

void FoodExpenses::SetMoney(double money)
{
	this->money = money;
	cout << "Кількість грошей змінена." << endl;
}

void FoodExpenses::ShowRests(Expenses& e1, Expenses& e2, Expenses& e3, Expenses& e4) const
{
	double rests = this->money - (e1.GetSpended() + e2.GetSpended() + e3.GetSpended() + e4.GetSpended());
	cout << "Залишок в грошах дорівнює " << round(rests * 100) / 100 << " гривень." << endl;
}

void FoodExpenses::SetLimit(double limit)
{
	this->limit = limit;
	cout << "Ліміт на витрати на їжу встановлений." << endl;
}

void FoodExpenses::SetFromDB()
{
	this->fread.open(this->filepath);
	//Перевірка чи правильний шлях до БД, або перевірка на доступ на відкриття файла
	if (!fread.is_open()) {
		throw exception("Помилка відкриття файла!");
	}
	string info;
	char uinfo[10] = {};
	bool checked = false;

	do {
		getline(fread, info);
		//Зчитування кількості грошей з БД
		if (!checked)
			for (int i = 0, j = 0; i < static_cast<int>(info.size()); i++) {
				if (checked) {
					uinfo[j] = info[i];
					j++;
				}
				else {
					if (info[i] == ' ') checked = true;
				}
			}
		checked = true;
	} while (info != "FoodExpenses"); //Поки не знайдена потрібна частина записів в БД
	//Запис кількості грошей до властивості класа
	this->money = stoi(uinfo);
	for (int i = 0; i < 10; i++) uinfo[i] = '\0'; //Знищення даних в масиві uinfo

	checked = false;
	getline(fread, info);

	//Зчитування витрат з БД
	for (int i = 0, j = 0; i < static_cast<int>(info.size()); i++) {
		if (checked) {
			uinfo[j] = info[i];
			j++;
		}
		else {
			if (info[i] == ' ') checked = true;
		}
	}
	//Запис кількості витрачених грошей до властивості класа
	this->spends = stoi(uinfo);
	getline(fread, info);
	checked = false;
	for (int i = 0; i < 10; i++) uinfo[i] = '\0'; //Знищення даних в масиві uinfo
	//Зчитування ліміту з БД
	for (int i = 0, j = 0; i < static_cast<int>(info.size()); i++) {
		if (checked) {
			uinfo[j] = info[i];
			j++;
		}
		else {
			if (info[i] == ' ') checked = true;
		}
	}
	//Запис ліміту до властивості класу
	this->limit = stoi(uinfo);
	fread.close();
	cout << "Дані з бази даних для витрат на їжу встановлені." << endl;
}

void FoodExpenses::UpdateDB()
{
	fwrite.open(filepath);
	//Перевірка чи правильний шлях до БД, або перевірка на доступ на відкриття файла
	if (!fwrite.is_open()) {
		throw exception("Помилка відкриття файла!");
	}
	//Ввід даних до БД
	fwrite << "гроші " << this->money << endl;
	fwrite << "FoodExpenses" << endl;
	fwrite << "витрати " << this->spends << endl;
	fwrite << "ліміт " << this->limit << endl;
	fwrite.close();
}



Utilities::Utilities(string filepath)
{
	this->limit = 0.0;
	this->spends = 0.0;
	this->filepath = filepath;
}

Utilities::Utilities(string filepath, double spends) :Utilities(filepath)
{
	this->spends = spends;
}

Utilities::Utilities(string filepath, double spends, double limit) : Utilities(filepath, spends)
{
	this->limit = limit;
}

void Utilities::AddSpends(double spends)
{
	if (this->spends + spends < this->limit) {
		this->spends += spends;
		cout << "Ви успішно підвищили витрати на комунальні послуги." << endl;
	}
	else {
		cout << "Ви перевищили ліміт на витрати на комунальні послуги!" << endl;
	}
}

void Utilities::ShowSpended() const
{
	cout << "Витрачено на комунальні послуги " << round(this->spends * 100) / 100 << " гривень." << endl;
}

void Utilities::SetLimit(double limit)
{
	this->limit = limit;
	cout << "Ліміт на витрати на комунальні послуги встановлений." << endl;
}

void Utilities::SetFromDB()
{
	this->fread.open(this->filepath);
	//Перевірка чи правильний шлях до БД, або перевірка на доступ на відкриття файла
	if (!fread.is_open()) {
		throw exception("Помилка відкриття файла!");
	}
	string info;
	char uinfo[10] = {};
	bool checked = false;

	do {
		getline(fread, info);
	} while (info != "Utilities"); //Поки не знайдена потрібна частина записів в БД

	//Зчитування витрат з БД
	getline(fread, info);
	for (int i = 0, j = 0; i < static_cast<int>(info.size()); i++) {
		if (checked) {
			uinfo[j] = info[i];
			j++;
		}
		else {
			if (info[i] == ' ') checked = true;
		}
	}
	//Запис кількості витрачених грошей до властивості класа
	this->spends = stoi(uinfo);
	for (int i = 0; i < 10; i++) uinfo[i] = '\0'; //Знищення даних в масиві uinfo
	checked = false;

	//Зчитування ліміту з БД
	getline(fread, info);
	for (int i = 0, j = 0; i < static_cast<int>(info.size()); i++) {
		if (checked) {
			uinfo[j] = info[i];
			j++;
		}
		else {
			if (info[i] == ' ') checked = true;
		}
	}
	//Запис ліміту до властивості класа
	this->limit = stoi(uinfo);
	fread.close();
	cout << "Дані з бази даних для витрат на комунальні послуги встановлені." << endl;
}

void Utilities::UpdateDB()
{
	fwrite.open(filepath, ofstream::app); //Відкриття БД без знищення даних
	//Перевірка чи правильний шлях до БД, або перевірка на доступ на відкриття файла
	if (!fwrite.is_open()) {
		throw exception("Помилка відкриття файла!");
	}
	//Ввід даних
	fwrite << "Utilities" << endl;
	fwrite << "витрати " << this->spends << endl;
	fwrite << "ліміт " << this->limit << endl;
	fwrite.close();
}



ClothesExpenses::ClothesExpenses(string filepath)
{
	this->limit = 0.0;
	this->spends = 0.0;
	this->filepath = filepath;
}

ClothesExpenses::ClothesExpenses(string filepath, double spends) :ClothesExpenses(filepath)
{
	this->spends = spends;
}

ClothesExpenses::ClothesExpenses(string filepath, double spends, double limit) : ClothesExpenses(filepath, spends)
{
	this->limit = limit;
}

void ClothesExpenses::AddSpends(double spends)
{
	if (this->spends + spends < this->limit) {
		this->spends += spends;
		cout << "Ви успішно підвищили витрати на одяг." << endl;
	}
	else {
		cout << "Ви перевищили ліміт на витрати на одяг!" << endl;
	}
}

void ClothesExpenses::ShowSpended() const
{
	cout << "Витрачено на одяг " << round(this->spends * 100) / 100 << " гривень." << endl;
}

void ClothesExpenses::SetLimit(double limit)
{
	this->limit = limit;
	cout << "Ліміт на витрати на комунальні послуги встановлений." << endl;
}

void ClothesExpenses::SetFromDB()
{
	this->fread.open(this->filepath);
	//Перевірка чи правильний шлях до БД, або перевірка на доступ на відкриття файла
	if (!fread.is_open()) {
		throw exception("Помилка відкриття файла!");
	}
	string info;
	char uinfo[10] = {};
	bool checked = false;

	do {
		getline(fread, info);
	} while (info != "ClothesExpenses"); //Поки не знайдена потрібна частина записів в БД

	//Зчитування витрат з БД
	getline(fread, info);
	for (int i = 0, j = 0; i < static_cast<int>(info.size()); i++) {
		if (checked) {
			uinfo[j] = info[i];
			j++;
		}
		else {
			if (info[i] == ' ') checked = true;
		}
	}
	//Запис кількості витрачених грошей до властивості класа
	this->spends = stoi(uinfo);
	for (int i = 0; i < 10; i++) uinfo[i] = '\0'; //Знищення даних в масиві uinfo
	checked = false;

	//Зчитування ліміту з БД
	getline(fread, info);
	for (int i = 0, j = 0; i < static_cast<int>(info.size()); i++) {
		if (checked) {
			uinfo[j] = info[i];
			j++;
		}
		else {
			if (info[i] == ' ') checked = true;
		}
	}
	//Запис ліміту до властивості класа
	this->limit = stoi(uinfo);
	fread.close();
	cout << "Дані з бази даних для витрат на одяг встановлені." << endl;
}

void ClothesExpenses::UpdateDB()
{
	fwrite.open(filepath, ofstream::app); //Відкриття БД без знищення даних
	//Перевірка чи правильний шлях до БД, або перевірка на доступ на відкриття файла
	if (!fwrite.is_open()) {
		throw exception("Помилка відкриття файла!");
	}
	//Ввід даних
	fwrite << "ClothesExpenses" << endl;
	fwrite << "витрати " << this->spends << endl;
	fwrite << "ліміт " << this->limit << endl;
	fwrite.close();
}



EntertainmentExpenses::EntertainmentExpenses(string filepath)
{
	this->limit = 0.0;
	this->spends = 0.0;
	this->filepath = filepath;
}

EntertainmentExpenses::EntertainmentExpenses(string filepath, double spends) :EntertainmentExpenses(filepath)
{
	this->spends = spends;
}

EntertainmentExpenses::EntertainmentExpenses(string filepath, double spends, double limit)
{
	this->limit = limit;
}

void EntertainmentExpenses::AddSpends(double spends)
{
	if (this->spends + spends < this->limit) {
		this->spends += spends;
		cout << "Ви успішно підвищили витрати на інші потреби." << endl;
	}
	else {
		cout << "Ви перевищили ліміт на витрати на інші потреби!" << endl;
	}
}

void EntertainmentExpenses::ShowSpended() const
{
	cout << "Витрачено на інші потреби " << round(this->spends * 100) / 100 << " гривень." << endl;
}

void EntertainmentExpenses::SetLimit(double limit)
{
	this->limit = limit;
	cout << "Ліміт на витрати на комунальні послуги встановлений." << endl;
}

void EntertainmentExpenses::SetFromDB()
{
	this->fread.open(this->filepath);
	//Перевірка чи правильний шлях до БД, або перевірка на доступ на відкриття файла
	if (!fread.is_open()) {
		throw exception("Помилка відкриття файла!");
	}
	string info;
	char uinfo[10] = {};
	bool checked = false;

	do {
		getline(fread, info);
	} while (info != "EntertainmentExpenses"); //Поки не знайдена потрібна частина записів в БД

	//Зчитування витрат з БД
	getline(fread, info);
	for (int i = 0, j = 0; i < static_cast<int>(info.size()); i++) {
		if (checked) {
			uinfo[j] = info[i];
			j++;
		}
		else {
			if (info[i] == ' ') checked = true;
		}
	}
	//Запис кількості витрачених грошей до властивості класа
	this->spends = stoi(uinfo);
	for (int i = 0; i < 10; i++) uinfo[i] = '\0'; //Знищення даних в масиві uinfo
	checked = false;

	//Зчитування ліміту з БД
	getline(fread, info);
	for (int i = 0, j = 0; i < static_cast<int>(info.size()); i++) {
		if (checked) {
			uinfo[j] = info[i];
			j++;
		}
		else {
			if (info[i] == ' ') checked = true;
		}
	}
	//Запис ліміту до властивості класа
	this->limit = stoi(uinfo);
	fread.close();
	cout << "Дані з бази даних для інших витрат встановлені." << endl;
}

void EntertainmentExpenses::UpdateDB()
{
	fwrite.open(filepath, ofstream::app); //Відкриття БД без знищення даних
	//Перевірка чи правильний шлях до БД, або перевірка на доступ на відкриття файла
	if (!fwrite.is_open()) {
		throw exception("Помилка відкриття файла!");
	}
	//Ввід даних
	fwrite << "EntertainmentExpenses" << endl;
	fwrite << "витрати " << this->spends << endl;
	fwrite << "ліміт " << this->limit << endl;
	fwrite.close();
}


void Help(bool full)
{
	cout << "Перед вибором команди натисніть enter." << endl;
	cout << "<-------------- Команди --------------->" << endl;
	cout << "1. Показати витрати, команда {Show expenses}" << endl;
	cout << "2. Додати витрати, команда {Add expenses}" << endl;
	cout << "3. Показати ліміт, команда {Show limit}" << endl;
	if (full) cout << "4. Встановити ліміт, команда {Set limit}" << endl;
	cout << "5. Показати залишок, команда {Show rest of money}" << endl;
	if (full) cout << "6. Встановити суму грошей, команда {Set amount of money}" << endl;
	cout << "<----- Підкоманди для пунктів 1-4 ------>" << endl;
	cout << "1. Для витрат на їжу, команда {For foodexpenses}" << endl;
	if (full) cout << "2. Для витрат на комунальні послуги, команда {For utilities}" << endl;
	cout << "3. Для витрат на одяг, команда {For clothes}" << endl;
	cout << "4. Для витрат на розваги/інше, команда {For entertainment}" << endl;
	cout << "<----- Додаткова підкоманда для пунктів 1, 3 ------>" << endl;
	cout << "1. Показати всі пункти, команда {All}" << endl;
	
}

double GetValue()
{
	while (true) 
	{
		cout << "Введіть значення: ";
		double value;
		cin >> value;		
		if (cin.fail()) 
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Ви ввели неприпустиме значення, спробуйте ще раз.\n";
		}
		else
		{
			cin.ignore(32767, '\n');
			return value;
		}
	}
}

