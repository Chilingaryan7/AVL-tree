#ifndef IMPLEMENTATION
#define IMPLEMENTATION

template <typename T>
AVL<T>::Node::Node(value_type value, Node * left, Node * right) :
    m_value{value}, m_left{left}, m_right{right} {}
 
template <typename T>
AVL<T>::Node::Node(const Node& other) : m_value{other.m_value} {
    if (other.m_left) {
        m_left = new Node(*other.m_left);
    }
    if (other.m_right) {
        m_right = new Node(*other.m_right);
    }
}

template <typename T>
AVL<T>::Node::Node(Node&& other) noexcept : m_value{std::move(other.m_value)}  {
    m_left = std::exchange(other.m_left, nullptr);
    m_right = std::exchange(other.m_right, nullptr);
}

template <typename T>
AVL<T>::Node& AVL<T>::Node::operator=(const Node& other) {
    if (this != other) {
        delete m_left;
        delete m_right;
    
        m_value = other.m_value;
        if (other.m_left) {
            m_left = new Node(*other.m_left);
        } else {
            m_left = nullptr;
        }
        if (other.m_right) {
            m_right = new Node(*other.m_right);
        } else {
            m_right = nullptr;
        }
    }
    return *this;
}

template <typename T>
AVL<T>::Node& AVL<T>::Node::operator=(Node&& other) noexcept {
    if (this != other) {
        delete m_left;
        delete m_right;
        m_value = std::move(other.m_value);
        m_left = std::exchange(other.m_left, nullptr);
        m_right = std::exchange(other.m_right, nullptr);
    }
    return *this;
}

template <typename T>
AVL<T>::Node::~Node() {
    delete m_left;
    delete m_right;
}

template <typename T>
AVL<T>::AVL(Node * root) : m_root{root} {}

template <typename T>
AVL<T>::AVL(const AVL& other) : m_root{ new Node(*other.m_root)} {}

template <typename T>
AVL<T>::AVL(AVL&& other) noexcept  {
    m_root = std::exchange(other.m_root);
}

template <typename T>
AVL<T>& AVL<T>::operator=(const AVL& other) {
    if (this != &other) {
        m_root = new Node(*other.m_root);
    }
    return *this;
}

template <typename T>
AVL<T>& AVL<T>::operator=(AVL&& other) noexcept {
    if (this != &other) {
        m_root = std::exchange(other.m_root, nullptr);
    }
    return *this;
}

template <typename T>
AVL<T>::~AVL() {
    delete m_root;
}

template <typename T>
void AVL<T>::insert(AVL<T>::value_type value) {
    m_root = insert_helper(m_root, value);
    return;
}

template <typename T>
AVL<T>::Node* AVL<T>::insert_helper(Node * root, value_type value){
    if (!root) {
        return new Node(value);
    }
    if (root -> m_value > value) {
        root -> m_left = insert_helper(root -> m_left, value);
    }
    else if (root -> m_value < value) {
        root -> m_right = insert_helper(root -> m_right, value);
    }
    if (Balanced_factor(root) > 1) {
        if (root -> m_left -> m_value < value) {
            root -> m_left = left_rotated(root -> m_left);
        }
        return right_rotated(root);
    }
    if (Balanced_factor(root) < -1) {
        if (root -> m_right > value) {
            root -> m_right = right_rotated(root -> m_right);
        }
        return left_rotated(root);
    }
    return root;
}

template <typename T>
void AVL<T>::remove(value_type value) {
    if (find(value)) {
        m_root = remove_helper(m_root, value);
    } else {
        std::cout << "no such value" << std::endl;
    }
    return;
}

template <typename T>
AVL<T>::Node* AVL<T>::remove_helper(Node * root, value_type value) {
    if (!root) {
        return nullptr;
    }
    else if (root -> m_value > value) {
       root -> m_left  = remove_helper(root -> m_left, value);
    }
    else if (root -> m_value < value) {
        root -> m_right  = remove_helper(root -> m_right, value);
    }
    else {
        if (!root -> m_left && !root -> m_right) {
            delete root;
            return nullptr;
        }
        else if (!root -> m_left) {
            Node* temp = root -> m_right;
            root -> m_right = nullptr;
            delete root;
            return temp;
        }
        else if (!root -> m_right) {
            Node * temp = root -> m_left;
            root -> m_left = nullptr;
            delete root;
            return temp;
        }
        else {
            root -> m_value = successor(root -> m_right) -> m_value; 
            root -> m_right = remove_helper(root -> m_right, root -> m_value);
        }
    }

    if (Balanced_factor(root) > 1) {
        if (Balanced_factor(root -> m_left) < 0) {
            root -> m_left = left_rotated(root -> m_left);
        }
        return right_rotated(root);
    }

    if (Balanced_factor(root) < -1) {
        if (Balanced_factor(root -> m_right) > 0) {
            root -> m_right = right_rotated(root -> m_right);
        }
            return left_rotated(root);
    }

    return root;
}

template <typename T>
AVL<T>::Node * AVL<T>::get_min(Node * root) {
    while (root && root -> m_left) {
        root = root -> m_left;
    }
    return root;
}

template <typename T>
AVL<T>::Node * AVL<T>::get_max(Node * root) {
    while (root && root -> m_right) {
        root = root -> m_right;
    }
    return root;
}

template <typename T>
AVL<T>::Node * AVL<T>::successor(Node * root) {
    if (root -> m_right) {
        return get_min(root -> m_right);
    }
    Node * successor = nullptr;
    Node * current = m_root;
    while (current) {
        if (current -> m_value < root -> m_value) {
            current = current -> m_right;
        } 
        else if (current -> m_value > root -> m_value) {
            successor = current;
            current = current -> m_left;
        } 
        else {
            break;
        }
    }
    return successor;
}

template <typename T>
AVL<T>::Node * AVL<T>::predecessor(Node * root) {
    if (root -> m_left) {
        return get_max(root -> m_left);
    }
    Node * predecessor = nullptr;
    Node * current = m_root;
    while (current) {
        if (current -> m_value > root -> m_value) {
            current = current -> m_left;
        }
        else if (current -> m_value < root -> m_value) {
            predecessor = current;
            current = current -> m_right;
        }
        else {
            break; 
        }
    }
    return predecessor;
}

template <typename T>
bool AVL<T>::find(value_type value) {
    return find_helper(m_root, value);
}

template <typename T>
bool AVL<T>::find_helper(Node * root, value_type value) {
    if (!root) {
        return false;
    } 
    else if (root -> m_value == value) {
        return true;
    }
    else if (root -> m_value < value) {
        return find_helper(root -> m_right, value);
    }
    else if (root -> m_value > value) {
        return find_helper(root -> m_left, value);
    }
    return false;
}

template <typename T>
size_t AVL<T>::get_height() {
    return get_height_helper(m_root);
}

template <typename T>
size_t AVL<T>::get_height_helper(Node * root) {
    if (!root) {
        return 0;
    }
    return std::max(get_height_helper(root -> m_left), get_height_helper(root -> m_right)) + 1;
}

template <typename T>
void AVL<T>::pre_traverce() {
    pre_traverce_helper(m_root);
    return;
}

template <typename T>
void AVL<T>::pre_traverce_helper(Node * node) {
    if (!node) {
        return;
    }
    std::cout << node -> m_value << std::endl;
    pre_traverce_helper(node -> m_left);
    pre_traverce_helper(node -> m_right);
    return;
}

template <typename T>
void AVL<T>::in_traverce() {
    in_traverce_helper(m_root);
    return;
}

template <typename T>
void AVL<T>::in_traverce_helper(Node * node) {
    if (!node) {
        return;
    }
    in_traverce_helper(node -> m_left);
    std::cout << node -> m_value << std::endl;
    in_traverce_helper(node -> m_right);
    return;
}

template <typename T>
void AVL<T>::post_traverce() {
    post_traverce_helper(m_root);
    return;
}

template <typename T>
void AVL<T>::post_traverce_helper(Node * node) {
    if (!node) {
        return;
    }
    post_traverce_helper(node -> m_left);
    post_traverce_helper(node -> m_right);
    std::cout << node -> m_value << std::endl;
    return;
}

template <typename T>
int AVL<T>::Balanced_factor(Node * node) {
    if (!node) { 
        return 0;
    }
    return get_height_helper(node -> m_left) - get_height_helper(node -> m_right);
}

template <typename T>
AVL<T>::Node * AVL<T>::right_rotated(Node * node) {
    Node * left = node -> m_left;
    Node * right = left -> m_right;
    left -> m_right = node;
    node -> m_left = right;
    return left;
}

template <typename T>
AVL<T>::Node * AVL<T>::left_rotated(Node * node) {
    Node * right = node -> m_right;
    Node * left = right -> m_left;
    right -> m_left = node;
    node -> m_right = left;
    return right;
}
 

#endif //IMPLEMENTATION