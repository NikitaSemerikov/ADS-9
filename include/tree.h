// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

struct TreeNode {
    char value;
    std::vector<TreeNode*> children;

    explicit TreeNode(char val) : value(val) {}
    ~TreeNode();
};

class PMTree {
 private:
    TreeNode* root;
    void buildTree(TreeNode* node, const std::vector<char>& elements);

 public:
    explicit PMTree(const std::vector<char>& elements);
    ~PMTree();
    TreeNode* getRoot() const { return root; }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif // INCLUDE_TREE_H_
