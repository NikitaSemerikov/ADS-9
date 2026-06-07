// Copyright 2022 NNTU-CS

#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
public:
    struct Node {
        char value;
        std::vector<std::shared_ptr<Node>> children;
        explicit Node(char val) : value(val) {}
    };

    explicit PMTree(const std::vector<char>& symbols);
    ~PMTree() = default;

    std::shared_ptr<Node> getRoot() const { return root_; }

private:
    std::shared_ptr<Node> root_;

    void buildTree(std::shared_ptr<Node> parent,
        const std::vector<char>& remaining);
};

// Задание №2: Получение всех перестановок
std::vector<std::vector<char>> getAllPerms(const PMTree& tree);

// Задание №3: Получение перестановки по номеру (медленный способ)
std::vector<char> getPerm1(const PMTree& tree, int num);

// Задание №3: Получение перестановки по номеру (быстрый способ)
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
