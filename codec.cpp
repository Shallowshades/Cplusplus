#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <sstream>
#include <memory>

using namespace std;

//二叉树的序列化和反序列化
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:

	// Encodes a tree to a single string.
	// 层序遍历
	// TODO: 能否改为深搜实现?
	string serialize(TreeNode* root) {
		queue<TreeNode*> nodes;
		nodes.push(root);
		string ret;
		while (!nodes.empty()) {
			TreeNode* cur = nodes.front(); nodes.pop();
			if (cur == nullptr) ret += "nullptr ";
			else {
				nodes.push(cur->left);
				nodes.push(cur->right);
				ret += to_string(cur->val) + " ";
			}
		}
		return ret;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		vector<string> nums;
		int start = 0;
		while (start < data.size()) {
			int pos = data.find(' ', start);
			string substr = data.substr(start, pos - start);
			//std::cout << substr << std::endl;
			nums.emplace_back(substr);
			if (pos == data.size() - 1) break;
			start = pos + 1;
		}
		if (nums.empty()) return nullptr;
		if (nums.front() == "nullptr") return nullptr;
		TreeNode* root = new TreeNode(atoi(nums.front().c_str()));
		queue<TreeNode*> nodes;
		nodes.push(root);
		for (int i = 1; i < nums.size(); i += 2) {
			TreeNode* cur = nodes.front(); nodes.pop();

			TreeNode* left = nullptr;
			TreeNode* right = nullptr;

			if (nums[i] != "nullptr") {
				TreeNode* left = new TreeNode(atoi(nums[i].c_str()));
				cur->left = left;
				nodes.push(left);
			}

			if (nums[i + 1] != "nullptr") {
				TreeNode* right = new TreeNode(atoi(nums[i + 1].c_str()));
				cur->right = right;
				nodes.push(right);
			}
		}
		return root;
	}
};

void clearTree(TreeNode* root) {
	if (root == nullptr) return;
	clearTree(root->left);
	clearTree(root->right);
	delete root;
}

int main() {

	// 序列化的时候最下层可以不序列化 选个简单的空标记 节省内存 
	// 反序列化必须按照序列化的方式 
	string data = "1 2 3 4 nullptr nullptr nullptr nullptr nullptr ";
	Codec codec;
	TreeNode* root = codec.deserialize(data);
	string ans = codec.serialize(root);
	std::cout << ans << std::endl;
	std::cout << (ans == data ? "Yes" : "No") << std::endl;

	// TODO: 清空树
	clearTree(root);

	return 0;
}