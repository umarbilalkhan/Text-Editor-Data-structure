#include <iostream>
#include "huffman.h"
#include "texteditor.cpp"
#include "tree.h"
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<vector>
using namespace std;

int main()
{

    TextEditor te("text.txt", "dictionary.txt");
    char wordArray[1000], c;
    te.printText();

    vector<string> dictionary = te.getDictionary();
    Node* tree = new Node;
    for (int i = 0; i < dictionary.size(); i++)
        insert(tree, dictionary[i]);


    while (1)
    {
        c = _getch();
        cout << c;

        if (c == '=')
        {
            te.compressAndSave("text.txt");
            break;
        }

        if (c >= ' ' && c <= '@' || c >= 'a' && c <= 'z')
        {
            if (c >= 'a' && c <= 'z')
            {
                vector<string> suggestion;
                Make_Suggestion(tree, wordArray, 0, c, suggestion);
                te.suggestWord(c, suggestion);
            }
            else {
                te.insertSpecialChar(c);
            }
        }

    }
    return 0;
}