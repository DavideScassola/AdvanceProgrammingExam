#include <iostream>
#include <memory>
#include <stdexcept>
#include  <algorithms>
#include <utility>

template <class K, class V, class F = less<Value_type<K>>>
class BinaryTree
{
    struct Node
    {
        std::unique_ptr<Node> next;
        std::pair<const K, V> entry; 
        Node(const &K key, const V& value, Node* node) : entry{key, value} next{node} {}
        ~Node() = default;
    }
    std::unique_ptr<Node> root;
    public:
    BinaryTree() = default;
    ~BinaryTree() = default;
    BinaryTree (const BinaryTree& v) = default;
    BinaryTree& operator=(const BinaryTree& v);
    BinaryTree(BinaryTree&& v) noexcept = default;
    BinaryTree& operator=(BinaryTree&& v) noexcept;
    BinaryTree(const K& key, const V& value): BinaryTree() {insert(key, value)}
    void insert (const K& key, const V& value);
    void clear();
    void balance();
    V& operator[] (const K& key)
    class Iterator;
    class ConstIterator;
    Iterator begin() { return Iterator{root.get()}; }
    Iterator end() { return Iterator{nullptr}; }
    ConstIterator begin() const { return ConstIterator{root.get()}; }
    ConstIterator end() const { return ConstIterator{nullptr}; }
    Iterator find(const K& key); 
    friend std::ostream& operator<<(std::ostream&, const BinaryTree<K,V,F>&);
}