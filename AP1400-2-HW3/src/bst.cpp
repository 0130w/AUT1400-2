#include "bst.h"

BST::Node::Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
BST::Node::Node() {}
BST::Node::Node(const Node& node) : value(node.value), left(node.left), right(node.right) {}

BST::BST(std::initializer_list<int> list) : root(nullptr) {
    for(auto value : list) {
        add_node(value);
    }
}
BST::BST(const BST &bst) : root(bst.root) {}
BST::BST(BST &&bst) : root(std::exchange(bst.root, nullptr)) {}
BST::~BST() {
    std::vector<Node*> nodes;
    bfs([&nodes](Node*& node) {nodes.push_back(node); });
    for(auto &node: nodes) { delete node; }
}
BST& BST::operator=(const BST& other) {
    root = other.root;
    return *this;
}
BST& BST::operator=(BST&& other) {
    root = std::exchange(other.root, nullptr);
    return *this;
}
BST& BST::operator++() {
    bfs([](Node*& node) { node->value += 1; });
    return *this;
}
BST BST::operator++(int) {
    BST copy = *this;
    bfs([](Node*& node) { node->value += 1; });
    return copy;
}

BST::Node*& BST::get_root() {
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func) {
    // using bfs to find all nodes then apply func to them
    if(root == nullptr) return;
    std::queue<Node*> queue;
    queue.push(root);
    while(!queue.empty()) {
        auto current = queue.front();
        queue.pop();
        func(current);
        if(current->left) queue.push(current->left);
        if(current->right) queue.push(current->right);
    }
}

size_t BST::length() {
    size_t result = 0;
    bfs([&result](Node*& node) { result++; });
    return result;
}

bool BST::add_node(int value) {
    if(!root) {
        root = new Node(value, nullptr, nullptr);
        return true;
    }
    auto current = &root;
    while(*current) {
        if((*current)->value > value) { current = &((*current)->left); }
        else if ((*current)->value < value) { current = &((*current)->right); }
        else { return false; }
    }
    *current = new Node(value, nullptr, nullptr);
    return true;
}

BST::Node** BST::find_node(int value) {
    if(!root) return nullptr;
    auto current = &root;
    while(*current) {
        if((*current)->value == value) {
            return current;
        } else if ((*current)->value > value) {
            current = &((*current)->left);
        } else {
            current = &((*current)->right);
        }
    }
    return nullptr;
}

BST::Node** BST::find_parent(int value) {
    if(!root) return nullptr;
    auto current = &root;
    if((*current)->value == value) return nullptr;
    auto check = [&value](Node*& node) -> bool {
        return ( (node->left && node->left->value == value) || (node->right && node->right->value == value) );
    };
    while(*current) {
        if(check(*current)) { return current; }
        if((*current)->value > value) { 
            current = &((*current)->left); 
        } else {
            current = &((*current)->right);
        }
    }
    return nullptr;
}

BST::Node** BST::find_successor(int value) {
    auto node = find_node(value);
    if(node == nullptr) return nullptr;
    Node** result = nullptr;
    if((*node)->right == nullptr) {
        return find_parent(value);
    } else {
        result = &((*node)->right);
        while((*result)->left) {
            result = &((*result)->left);
        }
    }
    return result;
}

bool BST::delete_node(int value) {
    Node** node = find_node(value);
    Node** parent = find_parent(value);

    if(!node) { return false; }

    Node* delete_node = *node;

    if(!delete_node->left && !delete_node->right) {
        // 两个节点不存在
        if(parent) {
            if((*parent)->left && (*parent)->left->value == value) {
                (*parent)->left = nullptr;
            } else { (*parent)->right = nullptr; }
        } else {
            root = nullptr;
        }
        delete delete_node;
    } else if(!delete_node->left || !delete_node->right) {
        //有一个节点不存在
        Node* child = delete_node->left ? delete_node->left : delete_node->right;
        if(parent) {
            if((*parent)->left && (*parent)->left->value == value) {
                (*parent)->left = child;
            } else { (*parent)->right = child; }
        } else {
            root = child;
        }
        delete delete_node;
    } else {
        // 两个节点都存在
        Node** successor = find_successor(value);
        // 肯定能找得到successor，而且肯定是在右子树上面
        std::swap((*successor)->value, delete_node->value);
        // 接下来只需要考虑怎么删除successor
        Node** successor_parent = find_parent((*successor)->value);
        if((*successor_parent)->left && (*successor_parent)->left->value == value) {
            (*successor_parent)->left = nullptr;
        } else {
            (*successor_parent)->right = nullptr;
        }
        delete *successor;
    }
    return true;
}