#pragma once
#include <iostream>
#include <string>
using namespace std;
#define alphabets 26
 
struct Node
{
    Node* child[alphabets];
    bool end;
    Node() :end(false)   
    {
        for (int i = 0; i < alphabets; i++)
            child[i] = NULL;
    }
};

void insert(Node* root, string word)
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (root->child[word[i] - 'a'] == NULL)
        {
            root->child[word[i] - 'a'] = new Node;
        }
        root = root->child[word[i] - 'a'];
    }
    root->end = true;
}


void printWord(string str, int n,char c,vector<string>& s)
{
    string temp;
    if (str[0] == c)
    {
        for (int i = 0; i < n; i++)
        {
            temp += str[i];
        }
        s.push_back(temp);
    }
}


void Make_Suggestion(Node* root, char* wordArray, int pos,char c, vector<string>& s){
    if (root == NULL)
        return;
    if (root->end)
    {
        printWord(wordArray, pos,c,s);
    }
    for (int i = 0; i < alphabets; i++)
    {
        if (root->child[i] != NULL)
        {
            wordArray[pos] = i + 'a';
            Make_Suggestion(root->child[i], wordArray, pos + 1,c,s);
        }
    }
}