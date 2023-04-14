#include<iostream>
#include<string>
#include<vector>
#include<conio.h>
#include<windows.h>
#include"huffman.h"

using namespace std;

class TextEditor {

private:
	string text;
	vector<string> dictionary;


	void printSuggestion(vector<string> suggestedWords)
	{

		cout << endl << endl;
		cout << "Suggestions:" << endl;
		for (int i = 0; i < suggestedWords.size(); i++)
		{
		   cout << i << ". " << suggestedWords[i] << endl;
   		}     
		cout << "10.type more" << endl;
	}
	vector<string> getSuggestions(char c)
	{
		vector<string> suggestedWords;

		suggestedWords.push_back("s1");

		return suggestedWords;
	}

	void placeCursor(int x = 0, int y = 0)
	{
		//this function is taken from internet to set cursor back to(0,0) after clearing screen
		HANDLE handle;
		COORD coordinates;   
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
		coordinates.X = x;
		coordinates.Y = y;
		SetConsoleCursorPosition(handle, coordinates);
	}

	string getWord(vector<string> suggestedWords)
	{

		int i = 0;
		cout << "Select: ";
		while (1) {
			cin >> i;
			if (i >= 0 && i <= 9) break;
			else if (i == 10) {
				return "more";
			}
		}

		return suggestedWords[i];
	}
	string getText()
	{
		return text;
	}
public:
	vector<string> getDictionary() {
		return this->dictionary;
	}
	vector<string> readFile(string filename)
	{
		vector<string> data;
		fstream file;
		string word;
		int i = 0;
		file.open(filename.c_str());
		while (!file.eof()) {
			file >> word;
			data.push_back(word);
			i++;
		}
		file.close();
		return data;

	}

	TextEditor(string inputFile, string dic_filname)
	{
		this->dictionary = this->readFile(dic_filname);
		huffman ht(inputFile);
		this->text = ht.decode();

	}
	void printText()
	{
		cout << getText();
	}

	void suggestWord(char c, vector<string>& s)
	{
		string cf;
		cf += c;
		vector<string> suggestedWords;

		if (c >= 'a' && c <= 'z')
		{
			char i = 1;
			string word = "more";
			while (word.compare("more") == 0)
			{
				suggestedWords.clear();
				int k = 0;
				for (; k < s.size(); k++)
				{
					string temp;
					for (int j = 0; j < cf.size(); j++)
					{
						if (j < s[k].size()) {
							temp += s[k][j];
						}
					}
					if (cf.compare(temp) == 0)
						break;
				}

				int  count = 0;
				while (count < 10 && k < s.size())
				{
					suggestedWords.push_back(s[k]);
					k++;
					count++;
				}

				this->printSuggestion(suggestedWords);
				word = this->getWord(suggestedWords);
				if (word.compare("more") != 0) {
					this->text += word;
					system("cls");
					placeCursor(0, 0);
					this->printText();
					break;
				}
				system("cls");
				placeCursor(0, 0);
				this->printText();
				cout << cf;
				c = _getch();

				cout << c;
				cf += c;
				i++;
			}

		}
		else
			this->text += c;
	}

	void compressAndSave(string path) {
		huffman ht(path);
		ht.encodeAndSave(text);
	}

	void insertSpecialChar(char c)
	{
		this->text += c;
	}

};
