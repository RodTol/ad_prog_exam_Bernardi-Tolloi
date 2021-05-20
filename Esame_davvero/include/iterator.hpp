/*
Author: Rodolfo Tolloi, Giulia Bernardi.

Purpouse:   VA SCRITTO !!!!!!!!!!!!!!!11.

Date: May, 2021.
*/

#include<iterator>

template<typename node_type, typename attr_type>
struct _iterator {

  /*raw pointer to the starting node*/
  node_type* current;

  /*interface for the iterators*/
  using value_type = attr_type;
  using reference = value_type&;
  using pointer = value_type*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  /*default cost and destr*/
  _iterator() = default;
  ~_iterator() = default;

  /*custom costr. Mettiamo explicit e quindi dobbiamo
  chiamare il costr ogni volta, poichè non abbiamo la 
  conversione automatica da nodo a iterator*/
  explicit _iterator (node_type* input) noexcept:
      current{input} {};

  /*dereference operator*/
  reference operator*() const noexcept { return current->attr; }

  /*acces operator*/
  pointer operator->() const noexcept { return &**this; }

  /*pre-increment operator*/
  /*SPIEGA COME FUNZIONA*/
  _iterator &operator++() noexcept {

    node_type* dad;

      if (current->right)
      {
        /*metto current uguale a un raw pointer (grazie a .get) che punta
        all'elemnto puntato da right del mio current originale*/
        current = current->right.get();

          /*finchè ho un left*/
          while (current->left)
          {
              current = current->left.get();
          }

        return *this;
      }

      else 
      {
        /*passo al genitore*/
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
  
  /*put to*/
  friend
  std::ostream& operator<<(std::ostream& os, const _iterator& x) {
  os << x.current;
  return os;
  }
  
  /*logic equal*/
  bool operator==(const _iterator& input) const noexcept {
    return input.current == current;
  }

  /*logic not equal*/
  bool operator!=(const _iterator& input) const noexcept {
    return !(input == *this);
  }

};



