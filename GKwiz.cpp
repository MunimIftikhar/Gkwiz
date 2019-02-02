#include <iostream>

#include <stdio.h>

#include "windows.h"

#include <math.h>

#include <fstream>

using namespace std;

void Display_Menu();

struct information
{
	char *name = new char[20];
	char *cellNumber = new char[11];
};

void get_info_from_user(information user);
bool read_Questions_and_ask(int *correct, int *wrong, int *Qnum);
bool check_num_of_Qs(int no);
void write_Qs_num(ofstream &fout, int no);
void Allocate_memory(char *options[], int s);
void Display_and_get_ans(char *Qs, char *options[], char *ans, int s);
void write_user_info(ofstream &tout, information user, int percentage);
bool read_user_info(information user, int *percentage);
void Displlay_result(int percent, int correct, int wrong, int Qnum);
void Read_Hard_Qs(int *correct, int *wrong, int *Qnum);
void Read_medium_Qs(int *correct, int *wrong, int *Qnum);
void Read_easy_Qs(int *correct, int *wrong, int *Qnum);

int main()
{
	Display_Menu();
	information user;

	get_info_from_user(user);
	int Read_percentage = 0;
	ofstream tout;
	tout.open("user_info.txt", ios::app);
	int correctCount = 0, wrongCount = 0, Qnum = 0;

	if (read_user_info(user, &Read_percentage))
	{
		if (!read_Questions_and_ask(&correctCount, &wrongCount, &Qnum))
		{
			int percentage = (correctCount * 100) / Qnum;
			write_user_info(tout,user, percentage);
			Displlay_result(percentage, correctCount, wrongCount, Qnum);
			tout.close();
		}
	}
	else
	{
		if (Read_percentage > 70)
		{
			cout << endl << "According to previous record you have to give answerz of HARD Questions." << endl;
			system("cls");
			Read_Hard_Qs(&correctCount, &wrongCount, &Qnum);
			int percentage = (correctCount * 100) / Qnum;
			Displlay_result(percentage, correctCount, wrongCount, Qnum);
		}
		else if (Read_percentage > 50 && Read_percentage < 70)
		{
			cout << endl << "According to previous record you have to give answerz of MEDIUM Questions." << endl;
			system("cls");
			Read_medium_Qs(&correctCount, &wrongCount, &Qnum);
			int percentage = (correctCount * 100) / Qnum;
			Displlay_result(percentage, correctCount, wrongCount, Qnum);
		}
		else if (Read_percentage < 50)
		{
			cout << endl << "According to previous record you have to give answerz of EASY Questions." << endl;
			system("cls");
			Read_easy_Qs(&correctCount, &wrongCount, &Qnum);
			int percentage = (correctCount * 100) / Qnum;
			Displlay_result(percentage, correctCount, wrongCount, Qnum);
		}
	}
}

bool read_Questions_and_ask(int *correct, int *wrong, int *Qnum)
{
	int no = 0;
	char *Qs = new char[100]{'\0'};
	char *options[4];
	char *correctOpt = new char, *ans = new char;
	Allocate_memory(options, 4);
	ifstream fin;
	fin.open("Question.txt", ios::in);
	ofstream fout;
	int i = 0;
	bool a = true;
	while (fin >> no)
	{
		fout.open("QsNum.txt", ios::app);
		//fout << 0 << endl;
		fin.getline(Qs, 100);
		//cout << Qs << endl;
		for (int i = 0; i < 4; i++)
		{
			fin.getline(options[i], 80);
		}
		fin >> *correctOpt;
		if (check_num_of_Qs(no))
		{
			Display_and_get_ans(Qs, options, ans, 4);

			if ((*ans) == 'Q' || (*ans) == 'q')
			{
				a = false;
				break;
				//return false;
			}
			if ((*ans) == (*correctOpt))
			{
				(*correct)++;
				cout << "You answer is Correct." << endl << endl;
			}
			else
			{
				(*wrong)++;
				cout << "Your answer is incorrect." << endl;
				cout << "Correct answer is  " << *correctOpt << endl << endl;
			}
			(*Qnum)++;
			Sleep(3000);
			system("cls");
			write_Qs_num(fout, no);
		}
		fout.close();
		//i = no;
	}
	fin.close();
	return a;
}
void Display_and_get_ans(char *Qs, char *options[], char *ans, int s)
{

	cout << Qs << endl << endl;
	for (int i = 0; i < s; i++)
	{
		cout << options[i] << endl;
	}

	cout << endl << "Give your answer: ";
	//Sleep(10000);
	cin >> (*ans);
	//Sleep(5000);
	cout << endl;
}
void Allocate_memory(char *options[], int s)
{
	for (int i = 0; i < s; i++)
	{
		options[i] = new char[80]{'\0'};
	}
}

void get_info_from_user(information user)
{

	cout << "Give Your full name: ";
	cin.getline(user.name, 50);
	cout << endl << "Give your cell phone number without (-)";
	cin.getline(user.cellNumber, 50);
	system("cls");
}

bool check_num_of_Qs(int no)
{
	ifstream tin;
	int n = 0;
	tin.open("QsNum.txt", ios::in);
	if (!tin.is_open())
	{
		cout << "not found";
	}
	else
	{
		while (tin >> n)
		{
			if (n == no)
			{
				return false;
			}
		}
	}
	tin.close();
	return true;
}
void write_Qs_num(ofstream &fout, int no)
{
	fout << no << endl;
}

void Display_Menu()
{
	cout << endl << endl;
	cout << "***********************************************************************" << endl;
	cout << "                            WELCOME TO                                 " << endl;
	cout << "                               GKwiz                                   " << endl;
	cout << "                                BY                                     " << endl;
	cout << "                          MUNIM IFTIKHAR                               " << endl;
	cout << "***********************************************************************" << endl << endl;

	cout << "This testing application has following RULES: " << endl << endl;
	cout << "--You have to give answers in a,b,c,d " << endl;
	cout << "--You can give answers of as many Quitions as you want." << endl;
	cout << "--To Quit you have to give 'q' to stop the quiz and to see your result." << endl;

	Sleep(7000);
	system("cls");
}

void write_user_info(ofstream &tout,information user, int percentage)
{
	
	tout << endl << 0;
	tout << user.name << endl;
	tout << user.cellNumber << endl;
	tout << percentage << endl;
}

bool Compare(char *num1, char *num2)
{
	if (num2[0] == num1[0] && num2[1] == num1[1] && num2[2] == num1[2] && num2[3] == num1[3] && num2[4] == num1[4] && num2[5] == num1[5] && num2[6] == num1[6] && num2[7] == num1[7] && num2[8] == num1[8] && num2[9] == num1[9] && num2[10] == num1[10])
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool read_user_info(information user, int *percentage)
{
	ifstream gin;
	int n = 0;
	gin.open("user_info.txt", ios::in);
	information Read_info;
	if (!gin.is_open())
	{
		cout << "not ";
		Sleep(100000);
	}
	else
	{
		while (gin >> n)
		{
			gin.getline(Read_info.name, 20);
			gin.getline(Read_info.cellNumber,12);
			gin >> *percentage;
			for (int i = 0; i < 11; i++)
			{
				cout << Read_info.cellNumber[i];
			}
			if (!Compare(Read_info.cellNumber, user.cellNumber))
			{
				cout << endl << "Your Previous Result is " << *percentage << "%"<<endl;
				gin.close();
				return false;
			}
		}
		gin.close();
	}
	return true;
}

void Displlay_result(int percent, int correct, int wrong, int Qnum)
{
	system("cls");
	cout << "You Gave The answers of " << Qnum << " Questions. " << endl << endl;
	cout << "You Gave " << correct << " Correct answers " << endl << endl;
	cout << "You Gave " << wrong << " Wrong answers " << endl << endl;
	cout << "Your IQ level is " << percent << "% " << endl << endl;

}

void Read_Hard_Qs(int *correct, int *wrong, int *Qnum)
{
	int no = 0;
	char *Qs = new char[100]{'\0'};
	char *options[3];
	char *correctOpt = new char, *ans = new char;
	Allocate_memory(options, 3);
	ifstream fin;
	fin.open("hard.txt", ios::in);
	while (fin >> no)
	{
		fin.getline(Qs, 100);
		//cout << Qs << endl;
		for (int i = 0; i < 3; i++)
		{
			fin.getline(options[i], 80);
		}
		fin >> *correctOpt;
		Display_and_get_ans(Qs, options, ans, 3);
		if ((*ans) == (*correctOpt))
		{
			(*correct)++;
			cout << "You answer is Correct." << endl << endl;
		}
		else
		{
			(*wrong)++;
			cout << "Your answer is incorrect." << endl;
			cout << "Correct answer is  " << *correctOpt << endl << endl;
		}
		(*Qnum)++;
	}
	fin.close();
}

void Read_medium_Qs(int *correct, int *wrong, int *Qnum)
{
	int no = 0;
	char *Qs = new char[100]{'\0'};
	char *options[3];
	char *correctOpt = new char, *ans = new char;
	Allocate_memory(options, 3);
	ifstream fin;
	fin.open("medium.txt", ios::in);
	while (fin >> no)
	{
		fin.getline(Qs, 100);
		//cout << Qs << endl;
		for (int i = 0; i < 3; i++)
		{
			fin.getline(options[i], 80);
		}
		fin >> *correctOpt;
		Display_and_get_ans(Qs, options, ans, 3);
		if ((*ans) == (*correctOpt))
		{
			(*correct)++;
			cout << "You answer is Correct." << endl << endl;
		}
		else
		{
			(*wrong)++;
			cout << "Your answer is incorrect." << endl;
			cout << "Correct answer is  " << *correctOpt << endl << endl;
		}
		(*Qnum)++;
	}
	fin.close();
}

void Read_easy_Qs(int *correct, int *wrong, int *Qnum)
{
	int no = 0;
	char *Qs = new char[100]{'\0'};
	char *options[3];
	char *correctOpt = new char, *ans = new char;
	Allocate_memory(options, 3);
	ifstream fin;
	fin.open("easy.txt", ios::in);
	while (fin >> no)
	{
		fin.getline(Qs, 100);
		//cout << Qs << endl;
		for (int i = 0; i < 3; i++)
		{
			fin.getline(options[i], 80);
		}
		fin >> *correctOpt;
		Display_and_get_ans(Qs, options, ans, 3);
		if ((*ans) == (*correctOpt))
		{
			(*correct)++;
			cout << "You answer is Correct." << endl << endl;
		}
		else
		{
			(*wrong)++;
			cout << "Your answer is incorrect." << endl;
			cout << "Correct answer is  " << *correctOpt << endl << endl;
		}
		(*Qnum)++;
	}
	fin.close();
}