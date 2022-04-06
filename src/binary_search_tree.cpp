#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    insert(key, value, root_);
  }

  bool BinarySearchTree::Remove(int key) {
    return remove(key, root_);
  }

  void BinarySearchTree::Clear() {
    clear(root_);
    root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    Node* temp = find(key, root_);
    if (temp == nullptr) {
      return std::nullopt;
    }
    return temp->value;
  }

  bool BinarySearchTree::Contains(int key) const {
    if (Find(key) != std::nullopt) {
      return true;
    }
    return false;
  }

  bool BinarySearchTree::IsEmpty() const {
    return root_ == nullptr;
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    if (root_ != nullptr) {
      return find_min(root_) -> value;
    }
    return std::nullopt;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    if (root_ != nullptr) {
      return find_max(root_) -> value;
    }
    return std::nullopt;
  }

  Node* BinarySearchTree::root() const {
    if (root_ != nullptr) {
      return root_;
    }
    return nullptr;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if (node == nullptr){
      node = new Node(key, value);
      return;
    }
    if(key == node->key){
      node->value = value;
      return;
    }
    if(key > node->key){
      insert(key, value, node->right);
    }else{
      insert(key, value, node->left);
    }
  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if(node == nullptr) return false;
    if(key > node->key){
      remove(key, node->right);
    }else if (key < node->key) {
      remove(key, node->left);
    }else if(node->right != nullptr && node->left != nullptr) {
      if(node->right->left == nullptr){
        node->value = node->right->value;
        node->key = node->right->key;
        node->right = node->right->right;
      }else{
        node->key = find_min(node->right)->key;
        remove(node->key, node->right);
      }
    }else if(node->left != nullptr){
      node = node->left;
    }else if(node->right != nullptr){
      node = node->right;
    }else{
      node = nullptr;
    }
    return true;
  }

  void BinarySearchTree::clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    clear(node -> left);
    clear(node -> right);
    delete node;
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (key < node -> key) {
      return find(key, node -> left);
    }
    if (key > node -> key) {
      return find(key, node -> right);
    }
    return node;
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    if (node -> left != nullptr) {
      return find_min(node -> left);
    }
    return node;
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    if (node -> right != nullptr) {
      return find_max(node -> right);
    }
    return node;
  }

}  // namespace assignment
