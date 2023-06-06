/**
 *@file KDTree.cpp
 * @author your name (you@domain.com)
 * @brief KDTree
 * @version 0.1
 * @date 2023-02-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
struct Node {
    std::vector<T> data;
    Node<T>* left, * right;
    Node():left(nullptr), right(nullptr) {}
    ~Node() { delete left; delete right; }
};

template <typename T>
Node<T>* buildKDTree(std::vector<std::vector<T>>& points, size_t depth = 0) {
    if (points.empty()) {
        return nullptr;
    }

    //构造时，每层采用不同的轴作为中点
    size_t dim = points[0].size();
    size_t axis = depth % dim;
    std::cout << "dim = " << dim << std::endl;
    std::cout << "axis = " << axis << std::endl;
    auto cmp = [axis](std::vector<T>& a, std::vector<T>& b) {
        return a[axis] < b[axis];
    };
    std::sort(points.begin(), points.end(), cmp);
    auto mid = points.begin() + points.size() / 2;
    Node<T>* node = new Node<T>();
    node->data = *mid;
    std::vector<std::vector<T>> left_points(points.begin(), mid);
    std::vector<std::vector<T>> right_points(mid + 1, points.end());
    node->left = buildKDTree<T>(left_points, depth + 1);
    node->right = buildKDTree<T>(right_points, depth + 1);
    return node;
}

template<typename T>
Node<T>* searchKDTree(Node<T>* node, const std::vector<T>& target, size_t depth = 0) {
    if (!node) {
        return nullptr;
    }

    if (node->data == target) {
        return node;
    }

    size_t dim = node->data.size();
    size_t axis = depth % dim;

    if (target[axis] < node->data[axis]) {
        return searchKDTree(node->left, target, depth + 1);
    }
    return searchKDTree(node->right, target, depth + 1);
}

template<typename T>
void traverseKDTree(Node<T>* node, size_t depth = 0) {
    if (!node) {
        return;
    }
    std::cout << std::string(depth, '-') << "(";
    for (const auto& val : node->data) {
        std::cout << val << ",";
    }
    std::cout << ")" << std::endl;
    traverseKDTree(node->left, depth + 1);
    traverseKDTree(node->right, depth + 1);
}

int main() {

    std::vector<std::vector<int>> points = { {3, 6}, {17, 15}, {13, 15}, {6, 12},{9, 1}, {2, 7}, {10, 19} };
    Node<int>* root = buildKDTree(points);
    std::vector<int> target = { 10, 19 };
    Node<int>* node = searchKDTree(root, target);
    if (node) {
        std::cout << "Found: ";
        for (const auto& val : node->data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    traverseKDTree(root);
    delete(root);
    return 0;
}
