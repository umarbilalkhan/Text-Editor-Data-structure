#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <string>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;

struct huffman_node
{
	char id;																				
	int freq;																				
	string code;																			
	huffman_node* left;
	huffman_node* right;
	huffman_node()
	{
		left = right = NULL;
	}
};
typedef huffman_node* node_ptr;

class huffman
{
protected:
	node_ptr node_array[128];																
	fstream in_file, out_file;
	node_ptr child, parent, root;
	char id;
	string in_file_name, out_file_name;
	class compare
	{
	public:
		bool operator()(const node_ptr& c1, const node_ptr& c2) const
		{
			return c1->freq > c2->freq;
		}
	};
	priority_queue<node_ptr, vector<node_ptr>, compare> preQueue;									
	void create_node_array();																
	void traverse(node_ptr, string);														
	int binary_to_decimal(string&);															 
	string decimal_to_binary(int);															
	inline void build_tree(string&, char);													
public:
	huffman(string);
	void create_preQueue(string text);
	void create_huffman_tree();
	void calculate_huffman_codes();
	void coding_save(string in_text);
	string decoding_save();
	void recreate_huffman_tree();
	void encodeAndSave(string text);
	string decode();
};

#endif
