#pragma once

#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <stack>

class FileParse {
public:
	struct Node {
		std::string m_strKey;									// 节点名称
		std::string m_strValue;									// 节点值

		using pss = std::pair<std::string, std::string>;
		std::list<pss> m_listKV;								// 键值对
		std::list<Node*> m_listChild;							// 子节点

	};

	FileParse(std::string path);								
	~FileParse();

	void parse();	// 
	void print();	// 

private:
	std::string m_strText;
	int m_curIdx;
	Node* m_Root;

	Node* parse_node();
	void print_node(Node* root, int level);
	void free_memory(Node* root);
};