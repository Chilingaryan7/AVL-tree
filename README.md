 AVL Tree

📘 Overview

This project implements an **AVL Tree**, a self-balancing Binary Search Tree (BST), where the height difference (balance factor) between the left and right subtrees of any node is at most 1. This guarantees that operations such as insertion, deletion, and search are always performed in **O(log n)** time.

🧠 Features

- Automatic balancing after insertions and deletions
- Efficient search
- Tree traversals (inorder, preorder, postorder)
- Height and balance factor calculation
- Rotation handling (LL, RR, LR, RL)

## 🛠️ Available Methods

| Method Name         | Description                             |
|---------------------|-----------------------------------------|
| `insert(key)`       | Inserts a key into the tree             |
| `remove(key)`       | Deletes a key and rebalances the tree   |
| `find(key)`         | Checks if a key exists in the tree      |
| `inorder()`         | Inorder traversal (sorted order)        |
| `preorder()`        | Preorder traversal                      |
| `postorder()`       |  Postorder traversal                     |

## 🔄 Rotations Used for Balancing

To maintain balance, AVL Tree applies one of the following rotations when needed:

- **LL Rotation** (Right rotation)
- **RR Rotation** (Left rotation)
- **LR Rotation** (Left-Right rotation)
- **RL Rotation** (Right-Left rotation)

