#include "FileParse.h"

FileParse::FileParse(std::string path)
	: m_Root(nullptr)
	, m_curIdx(0) {

	std::fstream in(path, std::ios::in);
	if (in.is_open()) {
		std::string line;
		while (getline(in, line)){
			m_strText += line;
		}
		//std::cout << m_strText << std::endl;
		//std::cout << "-------------------------------" << std::endl;
	}
	else {
		std::cout << "Open Fail, Path Error" << std::endl;
	}
	in.close();
}

FileParse::~FileParse() {
	free_memory(m_Root);
}
void FileParse::free_memory(Node* root) {
	for (auto elem : root->m_listChild) {
		free_memory(elem);
	}
	delete root;
	root = nullptr;
}

void FileParse::print() {
	print_node(m_Root, 0);
}

void FileParse::print_node(Node* root, int level) {
	if (root == nullptr) return;
	for (int i = 0; i < level; ++i) std::cout << '\t';
	std::cout << root->m_strKey;
	for (auto& elem : root->m_listKV) {
		std::cout << "-" << elem.first << ":" << elem.second;
	}
	if (root->m_strValue.size() > 0) std::cout << "-value:" << root->m_strValue;
	std::cout << std::endl;

	for (auto& node : root->m_listChild) {
		print_node(node, level + 1);
	}
}

void FileParse::parse() {
	m_Root = parse_node();
}

FileParse::Node* FileParse::parse_node() {
	int size = m_strText.size();
	Node* node = new Node();
	while (m_curIdx < size) {
		if (m_strText[m_curIdx] != '(') {
			std::cout << "( not exist" << std::endl;
			return nullptr;
		}
		++m_curIdx; //跳过(

		int startPos = m_curIdx;
		if (!(m_curIdx < size && (isalpha(m_strText[m_curIdx]) || m_strText[m_curIdx] == '_'))) { // name 效验
			std::cout << "Parse Error, Node Name Error" << std::endl;
			return nullptr;
		}

		// 提取name
		while (m_curIdx < size && m_strText[m_curIdx] != ')' && m_strText[m_curIdx] != '/' && m_strText[m_curIdx] != ' ') ++m_curIdx;
		node->m_strKey = m_strText.substr(startPos, m_curIdx - startPos);
		//std::cout << "name = " << node->m_strKey << " Success" << std::endl;

		while (m_curIdx < size) {
			while (m_curIdx < size && isblank(m_strText[m_curIdx])) m_curIdx++;
			char tag = m_strText[m_curIdx];
			if (tag == '/') { // 1. 单标识
				if (m_strText[m_curIdx + 1] == ')') {
					m_curIdx += 2;
				}
				else {
					std::cout << "Parse Error, /)" << std::endl;
				}
				return node;
			}
			else if (tag == '(' && m_strText[m_curIdx + 1] == '/') { // 2. 双标识
				if (m_strText.substr(m_curIdx + 2, node->m_strKey.size()) != node->m_strKey) {
					std::cout << "(/ key error" << std::endl;
					return nullptr;
				}
				m_curIdx += 2 + node->m_strKey.size();
				if (m_strText[m_curIdx] != ')') {
					std::cout << "(/) format error" << std::endl;
					return nullptr;
				}
				return node;
			}
			else if (tag == '(') { // 子节点
				node->m_listChild.push_back(parse_node());
			}
			else if (tag == ')') { // 3. text
				++m_curIdx;
				while (m_curIdx < size && isblank(m_strText[m_curIdx])) m_curIdx++;
				if (m_strText[m_curIdx] != '(') { // 存在文本
					int pos = m_curIdx;
					while (m_curIdx < size && m_strText[m_curIdx] != '(' && !isblank(m_strText[m_curIdx])) m_curIdx++;
					std::string value = m_strText.substr(pos, m_curIdx - pos);
					node->m_strValue = value;
					if (value[0] != '\"') node->m_strValue = '\"' + node->m_strValue;
					if (value.back() != '\"') node->m_strValue += '\"';
					while (m_curIdx < size && isblank(m_strText[m_curIdx])) m_curIdx++;
				}
			}
			else { // 4. 属性键值对
				do {
					while (m_curIdx < size && isblank(m_strText[m_curIdx])) m_curIdx++;
					int pos = m_strText.find('=', m_curIdx);
					if (pos == std::string::npos) {
						std::cout << "KV error" << std::endl;
						return nullptr;
					}
					std::string key = m_strText.substr(m_curIdx, pos - m_curIdx);
					m_curIdx = pos + 1;
					while (m_curIdx < size && !isblank(m_strText[m_curIdx]) && m_strText[m_curIdx] != ')' && m_strText[m_curIdx] != '/') m_curIdx++;
					std::string value = m_strText.substr(pos + 1, m_curIdx - pos - 1);
					node->m_listKV.push_back({ key, value });
					while (m_curIdx < size && isblank(m_strText[m_curIdx])) m_curIdx++;
				} while (m_curIdx < size && m_strText[m_curIdx] != ')' && m_strText[m_curIdx] != '/');
			}

		}
	}
}
