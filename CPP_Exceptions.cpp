#include <iostream>
#include "CPP_Exceptions.h"

using namespace std;

void exception1()
{
	cout << "Start\n";
	try {									// начало блока try
		cout << "Inside try block\n";
		throw "100.0";							// генерация ошибки
		cout << "This will not execute";
	}
	catch (int i) {							// перехват ошибки для целочисленного исключения
		cerr << "Caught an integer exception -- value is: ";
		cout << i << " \n";
	}
	catch (double i) {						// не будет работать для целочисленного исключения
		cout << "Caught a double exception -- value is: ";
		cout << i << "\n";
	}
	catch (...) {						// будет работать для всех остальных
		cout << "Caught other exceptions" << endl;
	}
	cout << "End";
}

void MyFunc(int c)
{
	if (c > numeric_limits<char>::max())
		throw invalid_argument("MyFunc argument too large.");
	cout << "Correct value" << endl;
}

int exception2()
{
	cout << endl;
	try
	{
		MyFunc(106); //cause an exception to throw
	}
	catch (invalid_argument& e)
	{
		cerr << e.what() << endl;
		return -1;
	}
}

float quotient(int numl, int num2)
{
	if (num2 == 0)
		throw 1;
	return (float)numl / num2;
}

int exception3()
{
	bool isCorrect = false;
	do {
		cout << "\nВведите два целых числа для расчета их частного: ";
		int numberl, number2;
		cin >> numberl >> number2;
		try { // включает код, который может сгенерировать исключение 
			float result = quotient(numberl, number2);
			cout << "Частное равно " << result << endl;
			isCorrect = true;
		}
		catch (int error)
		{ // обработчик ошибки 
			cout << "ОШИБКА: деление на ноль" << endl;
			//return 1; // завершение при ошибке 
		}
	} while (!isCorrect);
	return 0; // нормальное завершение 
}

void files_secured()
{
	cout << endl;
	FILE* f = NULL;
	string s2 = "123456789012345678901234567890";
	char s1[31];
	errno_t errCode = 0;

	try {
		errCode = fopen_s(&f, "test.txt", "w+");
		if (errCode) throw 1;

		cout << fwrite(s2.c_str(), 1, s2.length(), f) << endl;
		fclose(f);

		errCode = fopen_s(&f, "test.txt", "r");
		if (errCode) throw 2;

		size_t n = fread(s1, 1, sizeof(s1) - 1, f);
		cout << n << endl;
		s1[n] = '\0';
		cout << s1 << endl;
		fclose(f);
		throw "1.1";
	}
	catch (int err)
	{
		switch (err)
		{
		case 1:
			cerr << "Error writing file: no access" << endl;
			break;
		case 2:
			cerr << "Error reading file: no such file" << endl;
			break;
		}
	}
	catch (double value)
	{
		cerr << "Заготовка на будущее..." << endl;
	}
	catch (...)
	{
		cerr << "Что-то пошло не так" << endl;
	}

	return;
}

void exception4()
{
	files_secured();
}

void exception5()
{
	cout << endl;
	try
	{
		int a = 5, b = 0, c;
		if (b == 0)
			throw 1;
		c = a / b;
		cout << c << endl;
	}
	catch (int e)
	{
		cerr << "Error: division by zero!" << endl;
	}
}

int main()
{
	setlocale(0, "ru");
	std::cout << "Exceptions"<< endl << endl;

	exception1();
	exception2();
	exception3();
	exception4();
	exception5();

	cout << endl;
}