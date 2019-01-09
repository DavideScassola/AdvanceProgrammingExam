#include <iostream>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <utility>

template <class K, class V>
class BinaryTree
{
    struct Node
    {
        std::unique_ptr<Node> _left;
        std::unique_ptr<Node> _right;
        std::pair<const K, V> entry; 
        Node(const K& key, const V& value, Node* left, Node* right) : _left{left}, _right{right}, entry{std::pair<K,V>(key,value)} {}
        ~Node() = default;
    };
    std::unique_ptr<Node> root;
    public:
    BinaryTree() = default;
    ~BinaryTree() = default;
    BinaryTree (const BinaryTree& v) = default;
    BinaryTree& operator=(const BinaryTree& v);
    BinaryTree(BinaryTree&& v) noexcept = default;
    BinaryTree& operator=(BinaryTree&& v) noexcept;
    BinaryTree(const K& key, const V& value): BinaryTree() {insert(key, value);}

    //used to insert a new pair key-value
    void insert (const K& key, const V& value);

    //clear the content of the tree
    void clear();

    //balance the tree
    void balance();

    //**optional** implement the `value_type& operator[](const key_type& k)` function int the `const` and `non-const` versions). This functions, should return a reference to the value associated to the key `k`. If the key is not present, a new node with key `k` is allocated having the value `value_type{}`
    V& operator[](const K& key) noexcept;
    const V& operator[](const K& key) const noexcept;

    class Iterator;
    class ConstIterator;

    //return an `iterator` to the first node (which likely will not be the root node)
    Iterator begin() { return Iterator{root.get()}; }

    //return a proper `iterator`
    Iterator end() { return Iterator{nullptr}; }

    //return a `const_iterator` to the first node
    ConstIterator begin() const { return ConstIterator{root.get()}; }

    //return a proper `const_iterator`
    ConstIterator end() const { return ConstIterator{nullptr}; }

    //find a given key and return an iterator to that node. If the key is not found returns `end()`
    Iterator find(const K& key);
    template <class k,class v> 
    friend std::ostream& operator<<(std::ostream&, const BinaryTree<k,v>&);
};
