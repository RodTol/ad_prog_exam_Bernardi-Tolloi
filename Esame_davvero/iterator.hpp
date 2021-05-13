/*
Author: Rodolfo Tolloi, Giulia Bernardi.

Purpouse:   VA SCRITTO !!!!!!!!!!!!!!!11.

Date: May, 2021.
*/

#include<iterator>

template<typename node_type, typename key_type>
class _iterator {

    /*raw pointer to the starting node*/
    node_type* current;

public:
  /*type of the attribute of the node*/
  using value_type = key_type;
  /*type of reference and pointer from the iterator*/
  using reference = value_type&;
  using pointer = value_type*;

  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

    /*custom costr. Mettiamo explicit e quindi dobbiamo
    chiamare il costr ogni volta, poichè non abbiamo la 
    conversione automatica da nodo a iterator*/
    explicit _iterator(node_type* input):
        current{input}
    {
      std::cout << "iterator custom constructor" << std::endl;
    };

    /*default cost and destr*/
    _iterator() = default;
    ~_iterator() = default;

    /*dereference operator*/
    reference operator*() const { return current->attr; }

    /*acces operator*/
    pointer operator->() const { return &**this; }

    /*pre-increment operator*/
    _iterator &operator++() {

     node_type* dad;
     node_type* start;

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

          /*salvo il punto di partenza*/
          start = current;
          
          
            while ( dad->right.get() == current )
            {
              dad = dad->parent;
              current = current->parent;
              
              /*metto un esclusione nel caso sono gia 
              nel nodo end (quello più alto)*/

              //NOTA:: se vuoi mettilo con end
              if (!dad)
              {
                current = start;
                std::cout << "we are already at the end" << std::endl;
                return *this;
              }
              
            }
          current = current->parent;
          return *this;  
        }

    }
    
    /*put to*/
    friend
    std::ostream& operator<<(std::ostream& os, const _iterator& x) {
    os << x.current;
    return os;
    }
    

};



