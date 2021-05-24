/*
*Author: Rodolfo Tolloi, Giulia Bernardi.
*
*Purpouse: create a custom struct named iterator which 
*implements an iterator for a binary search tree (BST). 
*Each iterator has one raw pointer to a node, named current.
*
*Date: May, 2021.
*/

#include<iterator>

template<typename node_type, typename attr_type>
struct _iterator {

  /**Raw pointer to the starting node.*/
  node_type* current;

  /**Interface for the iterators*/
  using value_type = attr_type;
  using reference = value_type&;
  using pointer = value_type*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  /**Default costructor and destructor.*/
  _iterator() = default;
  ~_iterator() = default;

  /**Custom costructor which takes as input a raw
  * pointer to a node.*/
  explicit _iterator (node_type* input) noexcept:
      current{input} {};

  /**Dereference operator.*/
  reference operator*() const noexcept { return current->attr; }

  /**Access operator.*/
  pointer operator->() const noexcept { return &**this; }

  /**Pre-increment operator.*/
  /** The pre-increment operator allows us to navigate the
  * tree in ascending order from a starting node.
  * To do so, we have to find the node with the smallest
  * bigger key with respect to the starting node.
  * First we check if the node has a right child. If that is 
  * the case we check iteratively if there are left children of the
  * right child. Once we reach a point in which there are no more left children,
  * we reached the right node and therefore can stop.
  * If on the other hand the starting node had no right child, then
  * we need to go back to its parent. We continue to go back until
  * we either reach the head of the tree or we reach a node which is
  * a right child. In the first case the root is the node we were
  * looking for, while in the second case the parent of the right
  * child node is the one we were looking for.*/
  _iterator &operator++() noexcept {

    node_type* dad;

      if (current->right)
      {
        current = current->right.get();

          while (current->left)
          {
              current = current->left.get();
          }

        return *this;
      }

      else 
      {
        dad = current->parent;
  
          while (dad && dad->right.get() == current)
          {
            dad = dad->parent;
            current = current->parent;            
          }
          
        current = dad;
        return *this;  
      }

  }
  
  /** Custom overloading of the put to operator. It was
  *implemented mainly for debugging purposes.*/
  friend
  std::ostream& operator<<(std::ostream& os, const _iterator& x) {
  os << x.current;
  return os;
  }
  
  /**Logic equal.*/
  bool operator==(const _iterator& input) const noexcept {
    return input.current == current;
  }

  /**Logic not equal.*/
  bool operator!=(const _iterator& input) const noexcept {
    return !(input == *this);
  }

};



