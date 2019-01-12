#include <iostream>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <string>
#include <vector>

template <class K, class V>
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
	Node& search (const K& key);

    public:
    BinaryTree() = default;
    ~BinaryTree() = default;
    BinaryTree (const BinaryTree& bt);
    BinaryTree& operator=(const BinaryTree& bt);
    BinaryTree(BinaryTree&& bt) noexcept = default;
    BinaryTree& operator=(BinaryTree&& bt) noexcept;
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
    template <class k,class v> 
    friend std::ostream& operator<<(std::ostream&, const BinaryTree<k,v>&);

    void copy_util(const BinaryTree::Node& old);

    std::vector<std::pair<K, V>> to_list() const;
};

template <class K, class V>

class BinaryTree<K,V>::Iterator : public std::iterator<std::forward_iterator_tag,V>
{
    using Node = BinaryTree<K,V>::Node;
    Node* pointed;

    public:
    Iterator(Node* node) : pointed{node} {}
    Iterator(const Iterator&) = default;
    V& operator*() const {return pointed->entry.second;} 
	std::pair<const K, V> entry() const {return pointed->entry;} //########<<<<<
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

template <class K, class V>
typename BinaryTree<K,V>::Iterator& BinaryTree<K,V>::Iterator::operator++()
{
    if(pointed->_right)
    {   
        pointed = pointed->_right.get();
        while(pointed->_left)
            pointed = pointed->_left.get();
        return (*this);
    }
    auto key = pointed->entry.first; 
    while(pointed != nullptr && pointed->entry.first <= key)
    {
        pointed = pointed->_parent;
    }
    return (*this);

}

template <class K, class V>
typename BinaryTree<K,V>::Node* BinaryTree<K,V>::first_node() const
{
    Node* node = root.get();
    while(node->_left != nullptr)
        node = node->_left.get();
    return node;
}

template <class K, class V>

class BinaryTree<K,V>::ConstIterator : public BinaryTree<K,V>::Iterator
{ 
    public:
        using non_const_it = BinaryTree<K,V>::Iterator;
        using non_const_it::Iterator;
        const V& operator*() const {return non_const_it::operator*(); }

};

template <class K, class V>

BinaryTree<K,V>::BinaryTree (const BinaryTree& bt)
{
    BinaryTree new_tree{};
    new_tree.copy_util(bt.root);
}

template <class K, class V>
void BinaryTree<K,V>::copy_util(const BinaryTree::Node& old)
{
    insert(old.entry.second, old.entry.first);
    if(old._left)
        copy_util(old._left);
    if(old._right)
        copy_util(old._right);
}

template <class K, class V>
BinaryTree<K,V>& BinaryTree<K,V>::operator=(const BinaryTree& bt)
{
    root.reset();
    auto tmp = bt;
    (*this) = std::move(tmp);
}

template <class K, class V>
void BinaryTree<K,V>::insert (const K& key, const V& value)
{
	
	if(!root)
	{
		root.reset(new Node(key,value,nullptr));
		return;
	}
	Node& node = search(key);

	if(node.entry.first == key)
		node.entry.second = value;

	if(node.entry.first < key)
		node._right.reset(new Node(key,value,&node));
	else 
		node._left.reset(new Node(key,value,&node));
}

template <class K, class V>
typename BinaryTree<K,V>::Node& BinaryTree<K,V>::search (const K& key)
{
	Node* node = root.get();
	std::cout << "qui ci sono arrivato";
	auto k = node->entry.first;
	std::cout << k;
	while(node->_left || node->_right)
	{
		
		std::cout << k;

		if(key==k)
			return *node;

    		if(key>k)
        	{
			if(node->_right)
				node=node->_right.get();
			else return *node;
        	}
	
		if(key<k)
        	{
			if(node->_left)
				node=node->_left.get();
			else return *node;
        	}
		k = node->entry.first;
	}
	
	return *node;
}

template <class K, class V>
typename BinaryTree<K,V>::Iterator BinaryTree<K,V>::find(const K& key)
{
	Node& node = search(key);
	
	if(node.entry.first == key)
		return Iterator(node);

	else return end();
}

template <class k,class v> 
std::ostream& operator<<(std::ostream& os, const BinaryTree<k,v>& bt)
{
    for(const auto& vals : bt )
        os << vals << " ";
    os << std::endl;
    return os;
}


template<class T>
std::vector<T> reorder(std::vector<T> list)
{
	std::vector<T> v{};
	//std::sort(list.begin(),list.end());
	//riordinare il vettore

	if(list.size()<2)
		return list;
	
	int middle = int(list.size()/2);

	std::vector<T> left = std::vector<T>(list.begin(), list.begin() + middle);
	left = reorder(left);

	std::vector<T> right = std::vector<T>(list.begin() + middle + 1, list.end());
	right = reorder(right);

	v.push_back(list[middle]);
	for(auto e : left) v.push_back(e);
	for(auto e : right) v.push_back(e);

	return v;
}

template <class K, class V>
std::vector<std::pair<K, V>> BinaryTree<K,V>::to_list() const
{
	std::vector<std::pair<K, V>> list{};
	auto it = begin(); 
	while(it!=nullptr)
	{
		list.push_back(it.entry());
		++it;
	}

	return list;
	//return std::vector<std::pair<const K, V>>(begin(), end());
}


template <class K, class V>
void BinaryTree<K,V>::balance()
{
	auto list = to_list();
	//std::sort(list.begin(),list.end()); //maybe not needed
	list = reorder(list);

	BinaryTree<K,V> *bt = new BinaryTree<K,V>;
	for(auto e : list)
		bt->insert(e.first,e.second);

	std::cout << *bt << std::endl;
	
	this->root.reset(bt->root.get());
	
}

/*
template <class K, class V>
const V& BinaryTree<K,V>::operator[](const K& key) const noexcept
{
	Iterator it = find(key);
	if(it!=nullptr) return *it;
}

template <class K, class V>
V& BinaryTree<K,V>::operator[](const K& key) noexcept
{
	Iterator it = find(key);
	if(it!=nullptr) return *it;
	else insert(key, new V());
}
*/



int main()
{
    int keys[10]{1,2,3,4,5,6,7,8,9,10};
    std::string values[10]{"a","b","c","d","e","f","g","h","i","l"};
    BinaryTree<int, std::string> bt{};
    for(int i = 0; i < 10; ++i)
        bt.insert(keys[i], values[i]);

	std::cout << bt << std::endl;

	bt.balance();
	
	/*
	auto vect = bt.to_list();  

	std::pair<const int, std::string> a{2,"miao"};
	std::pair<const int, std::string> b{0,"zero"};
	
	std::vector<std::pair<const int, std::string>> v{a,b};

	std::sort(v.begin(), v.end());
	*/


    return 0;
}
