// Copyright 2022 NNTU-CS

#include "include/tree.h"
#include <vector>
#include <memory>
#include <algorithm>

PMTree::PMTree(const std::vector<char>& symbols) {
    root_ = std::make_shared<Node>('\0');
    buildTree(root_, symbols);
}

void PMTree::buildTree(std::shared_ptr<Node> parent,
                       const std::vector<char>& remaining) {
    if (remaining.empty()) {
        return;
    }

    for (size_t i = 0; i < remaining.size(); ++i) {
        auto child = std::make_shared<Node>(remaining[i]);
        parent->children.push_back(child);

        std::vector<char> newRemaining;
        for (size_t j = 0; j < remaining.size(); ++j) {
            if (j != i) {
                newRemaining.push_back(remaining[j]);
            }
        }
        buildTree(child, newRemaining);
    }
}

void collectPerms(const std::shared_ptr<PMTree::Node>& node,
                  std::vector<char>& current,
                  std::vector<std::vector<char>>& result) {
    if (node->children.empty()) {
        if (!current.empty()) {
            result.push_back(current);
        }
        return;
    }

    for (const auto& child : node->children) {
        current.push_back(child->value);
        collectPerms(child, current, result);
        current.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    collectPerms(tree.getRoot(), current, result);
    return result;
}

long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    if (num < 1) {
        return std::vector<char>();
    }
    
    std::vector<std::vector<char>> allPerms = getAllPerms(tree);
    if (static_cast<size_t>(num) > allPerms.size()) {
        return std::vector<char>();
    }
    return allPerms[num - 1];
}

bool getPermFast(const std::shared_ptr<PMTree::Node>& node,
                 std::vector<char>& result,
                 int& remainingNum,
                 int currentLevel,
                 int totalLevels) {
    if (node->children.empty()) {
        return remainingNum == 1;
    }

    int remainingLevels = totalLevels - currentLevel - 1;
    long long subtreeSize = factorial(remainingLevels);

    for (const auto& child : node->children) {
        if (remainingNum > subtreeSize) {
            remainingNum -= subtreeSize;
        } else {
            result.push_back(child->value);
            return getPermFast(child, result, remainingNum, 
                             currentLevel + 1, totalLevels);
        }
    }
    return false;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    if (num < 1) {
        return std::vector<char>();
    }

    int depth = 0;
    auto temp = tree.getRoot();
    while (!temp->children.empty()) {
        depth++;
        temp = temp->children[0];
    }

    long long totalPerms = factorial(depth);
    if (static_cast<long long>(num) > totalPerms) {
        return std::vector<char>();
    }

    std::vector<char> result;
    result.reserve(depth);
    int remainingNum = num;

    if (getPermFast(tree.getRoot(), result, remainingNum, 0, depth)) {
        return result;
    }
    
    return std::vector<char>();
}
