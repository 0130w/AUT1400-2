#ifndef BST_H
#define BST_H
#include <iostream>
#include <queue>

class BST {

    public:
        BST(std::initializer_list<int> list);
        BST(const BST &other);
        BST(BST &&other);
        ~BST();
        class Node
        {
            public:
                Node(int value, Node* left, Node* right);
                Node();
                Node(const Node& node);
                bool operator==(int a) { return value == a; }
                bool operator<(int a) { return value < a; }
                bool operator<=(int a) { return value <= a; }
                bool operator>(int a) { return value > a; }
                bool operator>=(int a) { return value >= a; }

                int value = 0;
                Node* left = nullptr;
                Node* right = nullptr;
        };

        Node*& get_root();
        void bfs(std::function<void(Node*& node)> func);
        size_t length();
        bool add_node(int value);
        Node** find_node(int value);
        Node** find_parent(int value);
        Node** find_successor(int value);
        bool delete_node(int value);
        BST& operator=(const BST& other);
        BST& operator=(BST&& other);
        BST& operator++();
        BST operator++(int);

    private:
        Node* root = nullptr;
};

inline std::ostream& operator<<(std::ostream& out, BST::Node node) {
    out << "node's address : " << &node << "\nnode's value : " << node.value;
    if(node.left) {
        out << "\nnode's left address : " << node.left;
    } else {
        out << "\nnode's left address : nullptr";
    }
    if(node.right) {
        out << "\nnode's right address : " << node.right;
    } else {
        out << "\nnode's right address : nullptr";
    }
    return out;
}

inline bool operator==(int a, BST::Node b) {
    return a == b.value;
}

inline bool operator<(int a, BST::Node b) {
    return a < b.value;
}

inline bool operator<=(int a, BST::Node b) {
    return a <= b.value;
}

inline bool operator>(int a, BST::Node b) {
    return a >= b.value;
}

inline bool operator>=(int a, BST::Node b) {
    return a >= b.value;
}

inline std::ostream& operator<<(std::ostream& out, BST &bst) {
    out << std::string(20, '*') << std::endl;
    bst.bfs([&out](BST::Node*& node) {
        out << "node address : " << node << " value " << node->value << std::endl;
        if(node->left) { out << "node left child address : " << node->left << std::endl; }
        if(node->right) { out << "node right child address : " << node->right << std::endl; }
    });
    out << "binary search tree size : " << bst.length() << std::endl;
    out << std::string(20, '*') << std::endl;
    return out;
}


#endif //BST_H