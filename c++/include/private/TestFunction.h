#ifdef __TESTBTFUN__

template<class K, class V, class F>
int BinaryTree<K,V,F>::height(Node* node) const noexcept {
        return (node == nullptr) ? 0: 1 + std::max(height(node->_left.get()),height(node->_right.get()));
}

template<class K, class V, class F>
bool BinaryTree<K,V,F>::isBalanced(Node* node) const noexcept {
    return (node == NULL) ||
                (isBalanced(node->_left.get()) &&
                isBalanced(node->_right.get()) &&
                std::abs(height(node->_left.get()) - height(node->_right.get())) <=1);
}



#endif
