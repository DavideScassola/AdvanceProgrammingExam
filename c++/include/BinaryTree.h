#ifndef BINARY_TREE
#define BINARY_TREE

#include <iostream>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <string>
#include <vector>

template <class K, class V, class F = std::less<K>>
class BinaryTree
{
    struct Node
    {
        std::unique_ptr<Node> _left;
        std::unique_ptr<Node> _right;
        Node* _parent;
        std::pair<const K, V> entry; 
        Node(const K& key, const V& value, Node* parent,Node* left = nullptr, Node* right = nullptr) : _left{left}, _right{right}, _parent{parent},entry{std::pair<K,V>(key,value)} {}
        ~Node() = default;
    };
    std::unique_ptr<Node> root;
    Node* first_node() const;
	Node* search (const K& key);
    F cmp;
    public:
    BinaryTree(F comparison = F{}): cmp{comparison} {}
    ~BinaryTree() = default;
    BinaryTree (const BinaryTree& bt);
    BinaryTree& operator=(const BinaryTree& bt);
    BinaryTree(BinaryTree&& bt) noexcept = default;
    BinaryTree& operator=(BinaryTree&& bt) noexcept;
    

    //clear the content of the tree
    void clear() {root.release();}

    //balance the tree
    void balance();

    //**optional** implement the `value_type& operator[](const key_type& k)` function int the `const` and `non-const` versions). This functions, should return a reference to the value associated to the key `k`. If the key is not present, a new node with key `k` is allocated having the value `value_type{}`
    V& operator[](const K& key) noexcept;
    const V& operator[](const K& key) const noexcept {return (*this)[key];}

    class Iterator;
    class ConstIterator;

    //return an `iterator` to the first node (which likely will not be the root node)
    Iterator begin() {Node* fn = first_node(); return Iterator{fn};}

    //return a proper `iterator`
    Iterator end() { return Iterator{nullptr}; }

    //return a `const_iterator` to the first node
    ConstIterator begin() const {Node* fn = first_node(); return ConstIterator{fn};}

    //return a proper `const_iterator`
    ConstIterator end() const { return ConstIterator{nullptr}; }

    ConstIterator cbegin() const {Node* fn = first_node(); return ConstIterator{fn};}

    ConstIterator cend() const { return ConstIterator{nullptr}; }


    //find a given key and return an iterator to that node. If the key is not found returns `end()`
    Iterator find(const K& key);
    //used to insert a new pair key-value
    std::pair<Iterator,bool> insert (const K& key, const V& value);    
    template <class k,class v, class f> 
    friend std::ostream& operator<<(std::ostream&, const BinaryTree<k,v,f>&);

    void copy_util(const BinaryTree::Node& old);

    std::vector<std::pair<const K, V>> to_list() const;
};

template <class k,class v, class f> 
std::ostream& operator<<(std::ostream& os, const BinaryTree<k,v,f>& bt);

template<class T>
std::vector<T> reorder(std::vector<T> list);

#endif
