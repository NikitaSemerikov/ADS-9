// Copyright 2022 NNTU-CS
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <locale>
#include <vector>
#include "tree.h"

TreeNode::~TreeNode() {
    for (auto child : children) {
        delete child;
    }
}

void traverseAndCollect(TreeNode* node, std::vector<char>& currentPath,
                        std::vector<std::vector<char>>& result) {
    if (!node) return;

    currentPath.push_back(node->value);

    if (node->children.empty()) {
        result.push_back(currentPath);
    } else {
        for (auto child : node->children) {
            traverseAndCollect(child, currentPath, result);
        }
    }

    currentPath.pop_back();
}

void PMTree::buildTree(TreeNode* node,
                       const std::vector<char>& elements) {
    if (elements.empty()) return;

    for (const char& elem : elements) {
        TreeNode* child = new TreeNode(elem);
        node->children.push_back(child);

        std::vector<char> remaining;
        for (const char& e : elements) {
            if (e != elem) {
                remaining.push_back(e);
            }
        }

        buildTree(child, remaining);
    }
}

PMTree::PMTree(const std::vector<char>& elements) : root(nullptr) {
    std::vector<char> sorted = elements;
    std::sort(sorted.begin(), sorted.end());
    root = new TreeNode('\0');
    buildTree(root, sorted);
}

PMTree::~PMTree() {
    delete root;
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> currentPath;

    for (auto child : tree.getRoot()->children) {
        traverseAndCollect(child, currentPath, result);
    }

    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    if (num <= 0) return {};

    auto allPerms = getAllPerms(tree);
    if (num > static_cast<int>(allPerms.size())) {
        return {};
    }

    return allPerms[num - 1];
}

int countLeaves(TreeNode* node) {
    if (!node) return 0;
    if (node->children.empty()) return 1;

    int count = 0;
    for (auto child : node->children) {
        count += countLeaves(child);
    }
    return count;
}

bool navigateToPerm(TreeNode* node, int& targetNum,
                    std::vector<char>& result) {
    if (!node) return false;

    result.push_back(node->value);

    if (node->children.empty()) {
        if (targetNum == 1) {
            return true;
        } else {
            targetNum--;
            result.pop_back();
            return false;
        }
    }

    for (auto child : node->children) {
        int leavesInSubtree = countLeaves(child);
        if (targetNum <= leavesInSubtree) {
            if (navigateToPerm(child, targetNum, result)) {
                return true;
            }
        } else {
            targetNum -= leavesInSubtree;
        }
    }

    result.pop_back();
    return false;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    if (num <= 0) return {};

    std::vector<char> result;

    for (auto child : tree.getRoot()->children) {
        int leavesInSubtree = countLeaves(child);
        if (num <= leavesInSubtree) {
            int target = num;
            if (navigateToPerm(child, target, result)) {
                return result;
            }
        } else {
            num -= leavesInSubtree;
        }
    }

    return {};
}
