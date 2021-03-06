#include"stdafx.h"
#include<iostream>
#include<stdio.h>
#include<fstream>
#include <string>
#include<cmath>
#include <sstream>
using namespace std;
const int n = 255;

int symbol_count;
char *symbol_array = new char[symbol_count];

void freq1_ent1()
{
	setlocale(LC_ALL, "rus");
	cout << "Укажите имя файла: " << endl;
	char name[40];
	cin.getline(name, 40);
	
	char current_char;
	int i = 0;
	ifstream myfile(name, ios::app);
	string text_string;
	if (myfile.is_open())
	{

		stringstream string_stream;

		string_stream << myfile.rdbuf();
		text_string = string_stream.str();
		myfile.close();
		int symbol_count; 
		symbol_count = text_string.length();
		symbol_array = new char[symbol_count]; 
		text_string.copy(symbol_array, symbol_count);


		char symbols[n];     // масив символів без повторень
		double chance[n];   // частота символів
		int symbolsLenth = 0;

		for (int i = 0; i < symbol_count; i++)
		{
			int flg = 0;
			for (int j = 0; j < symbolsLenth; j++) {
				if (symbol_array[i] == symbols[j]) {
					chance[j]++; //якщо символи однакові збільчуємо частоту
					flg = 1;
					break;
				}
			}
			if (!flg)
			{
				chance[symbolsLenth] = 1.0;
				symbols[symbolsLenth] = symbol_array[i];
				symbolsLenth++;
			}
		}

		// сортування
		int flg = 1;
		while (flg)
		{
			flg = 0;
			for (int i = 0; i < symbolsLenth - 1; i++)
			{
				if (chance[i] < chance[i + 1]) {
					double tmp = chance[i];
					chance[i] = chance[i + 1];
					chance[i + 1] = tmp;
					char ch = symbols[i];
					symbols[i] = symbols[i + 1];
					symbols[i + 1] = ch;
					flg = 1;
				}
			}
		}

		ofstream out;
		out.open("Freq1.txt");
		if (out.is_open())
		{
			out << "Частота символов:\n";
			for (int i = 0; i < symbolsLenth; i++)
			{
					out << symbols[i] << '\t' << chance[i] / symbol_count <<endl;
			}
		}
		out.close();



		out.open("Entropy1.txt");

		if (out.is_open())
		{
			out << "Ентpопия с пробелами: \n";
			float  H1, sum = 0;

			for (int i = 0; i < symbolsLenth; i++)
			{

				sum = sum + (chance[i] / symbol_count)*log((chance[i] / symbol_count)) / log(2);

			}
			H1 = 0 - sum;
			out << "Ентропия = "<< H1 << '\n' << '\n';
		}
		out.close();
		int z = 0;
		for (int i = 0; i < symbol_count; i++)
		{
			if (symbol_array[i] == ' ')
				z++;

		}
		int count = symbol_count - z;

		out.open("Freq2.txt");
		if (out.is_open())
		{
			out << "Частота символов без пробелов:\n";
			for (int i = 0; i < symbolsLenth; i++)
			{
				if (symbols[i] != ' ')
				{

					out << symbols[i] << '\t' << chance[i] / count<<endl;
				}
			}
		}
		out.close();

		out.open("Entropy2.txt");

		if (out.is_open())
		{
			out << "Ентpопия без пробелов: \n";
			float  H1, sum = 0;

			for (int i = 0; i < symbolsLenth; i++)
			{

				if (symbols[i] != ' ')
					sum = sum + (chance[i] / count)*log((chance[i] / count)) / log(2);

			}
			H1 = 0 - sum;
			out << "Ентропия = " << H1 << '\n' << '\n';
		}
		out.close();

	}
}


int main()

{
	freq1_ent1();
	system("Pause");
	return 0;

}