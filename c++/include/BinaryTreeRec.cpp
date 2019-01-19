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

/**
 * @brief Class that implements a binary tree 
 * 
 * The implementation is a simple not autobalancing Binary tree, it is constructed with
 * a constant templated key, a templated value and a templated comparing function (the default
 *  is the < operator of the key type). It has a unique pointer to the root node.
 * 
 * @tparam K the key type
 * @tparam V the value stored in the node
 * @tparam std::less<K> the comparing function(defaul <)
 */
template <class K, class V, class F = std::less<K>>
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
    std::unique_ptr<Node> root;
    /**
     * @brief A function to calculate the first node (following the key order)
     * @return Node* a pointer to the first node
     */
    Node* first_node() const;
    /** The comparison operator, a functional object that returns a boolean */
    F cmp;

    /**
    * @brief auxiliary recursive function that implements the search algorithm used in insert and find functions
    * 
    * 
    * Given a pointer to a node (branch), a key, and a pointer to a parent, this function look for the 
    * correct place where to find (or to put) an element with this key in the subtree determined by the given node (branch).
    * This function will return also the correct parent to assign to the node in the case of insertion.
    * The correct parent is the first ancestor which key is greater than the actual node's key.
    *
    * @tparam std::unique_ptr<Node>& reference to a unique pointer to a node
    * @tparam const K& reference to the key
    * @tparam Node* pointer to the parent
    * @return std::pair< std::unique_ptr<Node>&, Node* > pair with the reference to the target branch and the pointer to the correct parent
    */
    std::pair< std::unique_ptr<Node>&, Node* > search (std::unique_ptr<Node>& node,const K& key, Node* old );

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
 
    public:
    using s_pair = std::pair<std::unique_ptr<typename BinaryTree<K,V,F>::Node>&,typename BinaryTree<K,V,F>::Node*>;

    BinaryTree(F comparison = F{}): cmp{comparison} {}
    ~BinaryTree() noexcept = default;
    BinaryTree (const BinaryTree& bt) {this->copy_util(*bt.root);}
    BinaryTree& operator=(const BinaryTree& bt);
    BinaryTree(BinaryTree&& bt) noexcept = default;
    BinaryTree& operator=(BinaryTree&& bt) noexcept = default;

#ifdef __TESTBTFUN__
    bool isBalanced(Node* node);
    int height(Node* node);
    Node* root_get() {return root.get();};
#endif


    //clear the content of the tree
    void clear() {root.reset();}

    /**
    * @brief function that balance the tree
    * 
    * 
    * Calling this function the tree will be balanced. The underlying algorithm consists in extracting the list of
    * al pairs (key,value) of the current tree, clearing the current tree, and then inserting all the pairs in such
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
    *
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
    * @brief a function that return an Iterator to the end
    * 
    * 
    * This function returns an iterator initialized with nullptr that represents the end 
    *
    * @return Iterator iterator to the end
    */
    Iterator end() { return Iterator{nullptr}; }

    //return a `const_iterator` to the first node
    ConstIterator begin() const {Node* fn = first_node(); return ConstIterator{fn};}

    //return a proper `const_iterator`
    ConstIterator end() const { return ConstIterator{nullptr}; }

    ConstIterator cbegin() const {Node* fn = first_node(); return ConstIterator{fn};}

    ConstIterator cend() const { return ConstIterator{nullptr}; }

    //find a given key and return an iterator to that node. If the key is not found returns `end()`
    Iterator find(const K& key)
    {
        Iterator it = Iterator(search(root,key,nullptr).first.get());
        return it;
    }
    //used to insert a new pair key-value
    std::pair<Iterator,bool> insert (const K& key, const V& value);
    std::pair<Iterator,bool> insert (std::pair<const K&, const V&> p) {return insert(p.first,p.second);}
    
    template <class k,class v, class f> 
    friend std::ostream& operator<<(std::ostream&, const BinaryTree<k,v,f>&);

    void copy_util(const BinaryTree::Node& old);
};

template <class K, class V, class F>
class BinaryTree<K,V,F>::Iterator : public std::iterator<std::forward_iterator_tag,V>
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
    bool operator==(const Iterator& other) {return pointed == other.pointed;}
    bool operator!=(const Iterator& other)  {return !(*this == other);}

};

template <class K, class V, class F>
typename BinaryTree<K,V,F>::Iterator& BinaryTree<K,V,F>::Iterator::operator++()
{
    if(pointed->_right != nullptr)
    {   
        pointed = pointed->_right.get();
        while(pointed->_left)
            pointed = pointed->_left.get();
    }
    else
        pointed = pointed->_parent;
    return (*this);
}

template <class K, class V, class F>
typename BinaryTree<K,V,F>::Node* BinaryTree<K,V,F>::first_node() const
{
    Node* node = root.get();
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
void BinaryTree<K,V,F>::copy_util(const BinaryTree::Node& old)
{
    insert(old.entry.first, old.entry.second);
    if(old._left != nullptr)
        copy_util(*old._left);
    if(old._right != nullptr)
        copy_util(*old._right);
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
    bool modified = node_pair.first ==nullptr;
    if(modified) node_pair.first.reset(new Node(key,value,node_pair.second));
    return std::pair<Iterator,bool>{Iterator{node_pair.first.get()},modified};
}

template <class K, class V,class F>
typename BinaryTree<K, V, F>::s_pair BinaryTree<K,V,F>::search (std::unique_ptr<typename BinaryTree<K,V,F>::Node>& node, const K& key, typename BinaryTree<K,V,F>::Node* old)
{
    if(node == nullptr || (!cmp(node->entry.first,key) && !cmp(key,node->entry.first)) )
        return BinaryTree<K, V, F>::s_pair{node,old};       
    else 
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
    clear();
	balance(list, 0, int(list.size() - 1));
}

template <class K, class V, class F>
void BinaryTree<K,V,F>::balance(std::vector<std::pair<const K, V>>& list, int begin,int end)
{
    if(begin > end) return;
    int middle = begin + (end - begin)/2;
    insert(list[middle].first, list[middle].second);
    balance(list, begin, middle - 1);
    balance(list, middle + 1, end);
}
