// Copyright 2022 NNTU-CS

#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

struct TreeNode {
    char data;
    std::vector<TreeNode*> descendants;

    explicit TreeNode(char val) : data(val) {}
    ~TreeNode();
};

class PMTree {
 private:
    TreeNode* origin;
    void constructTree(TreeNode* current, const std::vector<char>& available);

 public:
    explicit PMTree(const std::vector<char>& symbols);
    ~PMTree();
    TreeNode* getOrigin() const { return origin; }
};

std::vector<std::vector<char>> extractAllPermutations(const PMTree& permTree);
std::vector<char> fetchPermutationByNumber1(PMTree& permTree, int position);
std::vector<char> fetchPermutationByNumber2(PMTree& permTree, int position);

#endif // INCLUDE_TREE_H_
