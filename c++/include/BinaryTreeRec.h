/**
 * @file BinaryTreeRec.cpp
 * @author Salvatore Milite and Davide Scassola 
 * @brief Advanced Programming and Scientific Computing final c++ project
 * @version 0.1
 * @date 2019-01-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <iostream>
#include <memory>
#include <algorithm>
#include <utility>
#include <string>
#include <vector>

namespace {
template <class K>
bool default_comparator(const K& k1, const K& k2) {return k1 < k2;}
}

/**
 * @brief Class that implements a binary tree 
 * 
 * The implementation is a simple not autobalancing Binary tree, it is constructed with
 * a constant templated key, a templated value and a templated comparing default_comparatorion (the default
 *  is the < operator of the key type). It has a unique pointer to the root node.
 * 
 * @tparam K the key type
 * @tparam V the value stored in the node
 * @tparam std::less<K> the comparing function(defaul <)
 */
template <class K, class V, class F = decltype(&::default_comparator<K>)>
class BinaryTree
{
    /**
     * @brief A structure that represent the node of the tree
     * A private container that takes the unique pointers to the left and right child, a pointer
     * to the parent and the entry, a pair with key and value.
     */
    struct Node
    {   
        /** left child */
        std::unique_ptr<Node> _left;
        /** right child */
        std::unique_ptr<Node> _right;
        /** parent node */
        Node* _parent;
        /** pair with key and value */
        std::pair<const K, V> entry; 
        /** construct a new Node object */
        Node(const K& key, const V& value, Node* parent,Node* left = nullptr, Node* right = nullptr): 
        _left{left}, _right{right}, _parent{parent},entry{std::pair<K,V>(key,value)} {}
        /** default destructor */
        ~Node() noexcept = default;
    };
    /** Unique pointer to the root */
    std::unique_ptr<Node> root = nullptr;
    /**
     * @brief A function to calculate the first node (following the key order)
     * @return Node* a pointer to the first node
     */
    Node* first_node() const noexcept;
    /** The comparison operator, a functional object that returns a boolean */
    F cmp;

    /**
    * @brief auxiliary recursive function that implements the search algorithm used in insert and find functions
    * 
    * 
    * Given a pointer to a node, a key, and a pointer to a parent, this function look for the 
    * correct place where to find (or to put) an element with this key in the subtree determined by the given node.
    * This function will return also the correct parent to assign to the node in the case of insertion.
    * The correct parent is the first ancestor which key is greater than the actual node's key.
    *
    * @tparam std::unique_ptr<Node>& reference to a unique pointer to a node
    * @tparam const K& reference to the key
    * @tparam Node* pointer to the right parent for the insertion
    * @return std::pair< std::unique_ptr<Node>&, Node* > pair with the reference to the target branch and the pointer to the correct parent
    */
    std::pair< std::unique_ptr<Node>&, Node* > search(std::unique_ptr<Node>& node,const K& key, Node* old ) const;

    /**
    * @brief auxiliary recursive function that implements the balancing algorithm used in the balance() function
    * 
    * 
    * Given a list of pair (key,value), this function insert in the tree the elements of the list from a given begin index to 
    * a given end index, in an order such that the tree will be perfectly balanced. 
    *
    * @tparam std::vector<std::pair<const K, V>>& reference to the list
    * @tparam int begin index
    * @tparam int end index
    * 
    */
    void balance(std::vector<std::pair<const K, V>>& list, int begin, int end);
    /**
     * @brief An utility for the copy constructor
     * It starts a recursive copy of a BT starting from a given node(ideally the root).
     * @param old the node from which to start the copy. If is root then it copy an entire tree, else just a subtree
     */
    void copy_util(const BinaryTree::Node& old, std::unique_ptr<Node>& copied);
 
    
    using s_pair = std::pair<std::unique_ptr<typename BinaryTree<K,V,F>::Node>&,typename BinaryTree<K,V,F>::Node*>;
    public:

    /**
     * @brief Construct a new Binary Tree object
     */
    BinaryTree(F f = ::default_comparator): cmp{f} {};
    /**
     * @brief Destroy the Binary Tree object
     * 
     */
    ~BinaryTree() noexcept = default;
    /**
     * @brief Creates a deep copy of a binary tree
     * 
     * @param bt the tree to be copied
     */
    BinaryTree (const BinaryTree& bt) : cmp{bt.cmp} {this->copy_util(*bt.root, this->root);}
    /**
     * @brief Copy assignement
     * 
     * @param bt the tree to be copied
     * @return BinaryTree& 
     */
    BinaryTree& operator=(const BinaryTree& bt);
    BinaryTree(BinaryTree&& bt) noexcept = default;
    BinaryTree& operator=(BinaryTree&& bt) noexcept = default;
/**
 * @brief These functions works only if you deefine __TESTBTFUN__ and include "TestFunctions.h"
 * 
 */
#ifdef __TESTBTFUN__
    /**
     * @brief Finds out if the tree is balanced
     * 
     * It compares recursively the hegihts of all the branches, and if the difference in height is <= 1, it returns true 
     * @param node the starting node, usually the root
     * @return true if the tree is balanced
     * @return false if the tree is not balanced
     */
    bool isBalanced(Node* node) const noexcept;
    /**
     * @brief Returns the height of a tree or subtree starting by a specific node
     * 
     * @param node the node from where to stard
     * @return int the height 
     */
    int height(Node* node) const noexcept;
    /**
     * @brief A getter method for the root node
     * 
     * @return Node* a pointer to the root node
     */
    Node* root_get() const noexcept {return root.get();}
#endif


    //clear the content of the tree
    void clear() noexcept {root.reset();} 

    /**
    * @brief function that balance the tree
    * 
    * 
    * Calling this function the tree will be balanced. The underlying algorithm consists in extracting the list of
    * all pairs (key,value) of the current tree, clearing the current tree, and then inserting all the pairs in such
    * an order that the tree will balanced.
    *
    */
    void balance();

    /**
    * @brief operator that return the value corresponding to a given key
    * 
    * 
    * If the given key corresponds to an element in the tree this operator will return the value corresponding to
    * that element. If not present, a new pair with the given key and a default value will be inserted in the tree, 
    * and the a reference to this new value will be returned.
    *
    * @tparam const K& the key of the searched value 
    * @return V& reference to the value
    */
    V& operator[](const K& key);

     /**
    * @brief operator that return the value corresponding to a given key
    * 
    * 
    * The functioning of this operator is analogous to the non const one, but this time if an element corresponding 
    * to the given key is not found, then an exception will be thrown. In this way the tree will be surely unmodified. 
    * @throws runtime_errors
    * @tparam const K& the key of the searched value 
    * @return const V& reference to the value
    */
    const V& operator[](const K& key) const;

    class Iterator;
    class ConstIterator;

     /**
    * @brief a function that return an Iterator to the first element
    * 
    * 
    * This function returns the iterator to the first element, in the sense that it correspond to the element
    * for wich the key is the minimum between the all the keys according to the tree comparing function
    *
    * @return Iterator iterator to the first element
    */
    Iterator begin() {Node* fn = first_node(); return Iterator{fn};}

     /**
    * @brief A function that return an Iterator to one past the last node
    * 
    * 
    * This function returns an iterator initialized with nullptr that represents the end of the BinaryTree
    *
    * @return Iterator iterator to the end
    */
    Iterator end() { return Iterator{nullptr}; }

    /**
     * @brief A constant iterator version of begin()
     * 
     * @return ConstIterator constant iterator to the first node
     */
    ConstIterator begin() const {Node* fn = first_node(); return ConstIterator{fn};}

    /**
     * @brief A constant interator version of end()
     * 
     * @return ConstIterator returns a constant iterator to the end of the Data Structure
     */
    ConstIterator end() const { return ConstIterator{nullptr}; }

    /**
     * @brief Same as ConstIterator begin() but explicit
     * 
     * @return ConstIterator constant iterator to the first node
     */
    ConstIterator cbegin() const {Node* fn = first_node(); return ConstIterator{fn};}

    /**
     * @brief Same as ConstIterator end() but explicit
     * 
     * @return ConstIterator constant iterator to the end of the Data Structure 
     */
    ConstIterator cend() const { return ConstIterator{nullptr}; }

    /**
     * @brief Finds a value with a given key and returns an iterator to it
     * @param key the key of the node to be searched
     * @return Iterator an Iterator to the node with the key or to end() if its not present  
     */
    Iterator find(const K& key)
    {
        Iterator it = Iterator(search(root,key,nullptr).first.get());
        return it;
    }
    /**
     * @brief Insert a new node with given key and value
     * It returns a std::pair with an iterator to the node and a bool. If the key is not present, the new node is effectively added and the bool as value true. In case
     * the key was already in the tree the bool has value false, and the user has to change the node value manually from the iterator. 
     * @param key the key of the new node
     * @param value the value of the new node
     * @return std::pair<Iterator,bool> a pair with an iterator to the inserted (or where the key is already present) node and a bool that indicates if the new has been added
     */
    std::pair<Iterator,bool> insert (const K& key, const V& value);
    /**
     * @brief An insert which takes directly an std::pair with the right types
     * 
     * @param p the std::pair to be added in the new node 
     * @return std::pair<Iterator,bool> same as the other insert()
     */
    std::pair<Iterator,bool> insert (std::pair<const K&, const V&> p) {return insert(p.first,p.second);}
    
    template <class k,class v, class f> 
    /**
     * @brief Overloading of the operator<< for printing and writing on files
     * 
     * @return std::ostream& 
     */
    friend std::ostream& operator<<(std::ostream&, const BinaryTree<k,v,f>&);

   
};

template <class K, class V, class F>
class BinaryTree<K,V,F>::Iterator : public std::iterator<std::forward_iterator_tag,std::pair<const K, V>>
{
    using Node = BinaryTree<K,V,F>::Node;
    Node* pointed;

    public:
    Iterator(Node* node) : pointed{node} {}
    Iterator(const Iterator&) = default;
    std::pair<const K, V>& operator*() const {return pointed->entry;} 

    Iterator& operator++(); 
    Iterator operator++(int)
    {
        Iterator it{*this};
        ++(*this);
        return it;
    }
    bool operator==(const Iterator& other) const noexcept {return pointed == other.pointed;}
    bool operator!=(const Iterator& other)  const noexcept {return !(*this == other);}

};

template <class K, class V, class F>
typename BinaryTree<K,V,F>::Iterator& BinaryTree<K,V,F>::Iterator::operator++()
{
    // when you can go right
    if(pointed->_right != nullptr)
    {   
        pointed = pointed->_right.get();
        // and than down to the smaller key on that branch
        while(pointed->_left)
            pointed = pointed->_left.get();
    }
    // else go up
    else
    // we can do this thanks to our implementation of iterator()
        pointed = pointed->_parent;
    return (*this);
}

template <class K, class V, class F>
typename BinaryTree<K,V,F>::Node* BinaryTree<K,V,F>::first_node() const noexcept
{
    Node* node = root.get();
    //find the leftmost node
    while(node->_left != nullptr)
        node = node->_left.get();
    return node;
}

template <class K, class V, class F>
class BinaryTree<K,V,F>::ConstIterator : public BinaryTree<K,V,F>::Iterator
{ 
    public:
        using non_const_it = BinaryTree<K,V,F>::Iterator;
        using non_const_it::Iterator;
        const std::pair<const K, V>& operator*() const {return non_const_it::operator*(); }
};

template <class K, class V, class F>
void BinaryTree<K,V,F>::copy_util(const BinaryTree::Node& old, std::unique_ptr<BinaryTree::Node>& copied )
{
    copied.reset(new Node(old.entry.first, old.entry.second, old._parent));
    if(old._left != nullptr)
        copy_util(*old._left, copied->_left);
    if(old._right != nullptr)
        copy_util(*old._right, copied->_right);
}

template <class K, class V, class F>
BinaryTree<K,V,F>& BinaryTree<K,V,F>::operator=(const BinaryTree& bt)
{
    root.reset();
    auto tmp = bt;
    (*this) = std::move(tmp);
    return *this;
}

template <class K, class V,class F>
std::pair<typename BinaryTree<K,V,F>::Iterator,bool> BinaryTree<K,V,F>::insert(const K& key, const V& value)
{
    BinaryTree<K, V, F>::s_pair node_pair = search(root,key,nullptr);
    // Look if the key is already present and update the second return value
    bool modified = node_pair.first ==nullptr;
    // if not present insert the new node
    if(modified) node_pair.first.reset(new Node(key,value,node_pair.second));
    return std::pair<Iterator,bool>{Iterator{node_pair.first.get()},modified};
}

template <class K, class V,class F>
typename BinaryTree<K, V, F>::s_pair BinaryTree<K,V,F>::search (std::unique_ptr<typename BinaryTree<K,V,F>::Node>& node, const K& key, typename BinaryTree<K,V,F>::Node* old) const
{
    //stop when the key is present or we have reached the right insertion node
    if(node == nullptr || (!cmp(node->entry.first,key) && !cmp(key,node->entry.first)) )
        return BinaryTree<K, V, F>::s_pair{node,old};       
    else 
        //if we are on a right node, our parent is our father parent
        return cmp(node->entry.first, key) ? search(node->_right,key, node->_parent) : search(node->_left,key, node.get());
}

template <class K, class V, class F>
V& BinaryTree<K,V,F>::operator[](const K& key)  
{
    Iterator s_res = find(key);
    if(s_res != end()) return (*s_res).second;
    return (*insert(key, V{}).first).second;
}

template <class K, class V, class F>
const V& BinaryTree<K,V,F>::operator[](const K& key)  const
{
    Iterator s_res = find(key);
    if(s_res != end()) return (*s_res).second;
    //is a constant method, if it does not find the key it throws an exception
    throw std::runtime_error("You are trying to acces a non existing key");
}

template <class k,class v, class f> 
std::ostream& operator<<(std::ostream& os, const BinaryTree<k,v,f>& bt)
{
    for(const auto& vals : bt )
        os << "(" << vals.first << ":" << vals.second << ") ";
    os << std::endl;
    return os;
}

template <class K, class V, class F>
void BinaryTree<K,V,F>::balance()
{
	if(root == nullptr) return;
    std::vector<std::pair<const K, V>> list(begin(), end());
    //free some space
    clear();
	balance(list, 0, int(list.size()) - 1);
}

template <class K, class V, class F>
void BinaryTree<K,V,F>::balance(std::vector<std::pair<const K, V>>& list, int begin,int end)
{
    if(begin > end) return;
    int middle = begin + (end - begin)/2;
    //int middle = (begin + end)/2;
    insert(list[middle].first, list[middle].second);
    //halve the list and do the same till the end
    balance(list, begin, middle - 1);
    balance(list, middle + 1, end);
}
