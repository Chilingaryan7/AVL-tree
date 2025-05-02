#ifndef HEADER
#define HEADER
 
#include <iostream>
#include <utility>
#include <exception>
#include <type_traits>
#include <algorithm>

template <typename T>
class AVL {
public: 
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_pointer = const T*;
    using const_reference = const T&;

    struct Node {
        Node(value_type value = T{}, Node * left = nullptr, Node * right = nullptr);
        Node(const Node& other);
        Node(Node&& other) noexcept;
        Node& operator=(const Node& other);
        Node& operator=(Node&& other) noexcept;
        ~Node();

        T m_value;
        Node * m_left;
        Node * m_right;
    };

    AVL(Node * root = nullptr);
    AVL(const AVL& other);
    AVL(AVL&& other) noexcept;
    AVL& operator=(const AVL& other);
    AVL& operator=(AVL&& other) noexcept;
    ~AVL();

    void insert(value_type value);
    void remove(value_type value);
    bool find(value_type value);
    size_t get_height();
    void pre_traverce();
    void in_traverce();
    void post_traverce();

    //private:
    Node * insert_helper(Node * root, value_type value);
    bool find_helper(Node * root, value_type value);
    Node * successor(Node * root);
    Node * predecessor(Node * root);
    Node * remove_helper(Node * root, value_type value);
    Node * get_min(Node * root);
    Node * get_max(Node * root);
    size_t get_height_helper(Node * root);
    void pre_traverce_helper(Node * node);
    void in_traverce_helper(Node * node);
    void post_traverce_helper(Node * node);
    Node * left_rotated(Node * node);
    Node * right_rotated(Node * node);
    int Balanced_factor(Node * node);

    Node * m_root = nullptr;
};
#include "implementation.tpp"

#endif //HEADER