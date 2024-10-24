#pragma once

#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <stack>

class FileParse {
public:
	struct Node {
		std::string m_strKey;									// �ڵ�����
		std::string m_strValue;									// �ڵ�ֵ

		using pss = std::pair<std::string, std::string>;
		std::list<pss> m_listKV;								// ��ֵ��
		std::list<Node*> m_listChild;							// �ӽڵ�

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