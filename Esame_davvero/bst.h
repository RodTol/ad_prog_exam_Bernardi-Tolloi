/*
Author: Rodolfo Tolloi, Giulia Bernardi.

Purpouse:   VA SCRITTO !!!!!!!!!!!!!!!11.

Date: May, 2021.
*/

#include <functional>
#include <utility>

template <typename key_t, typename value_t, typename OP=std::less<key_t> >
class bst
{
    /*creo la coppia key-value che sarà il type degli argomenti
   dei vari nodi. Per velocizzar, chiamo questo type attr_type*/
   using attr_type = std::pair<const key_t, value_t>;

    /*members of bst class*/
   std::unique_ptr<node<attr_type>> head;
   std::size_t _size;
   OP compare;
   
   

   

public:

    /*default constr e destr*/
    bst() = default;
    ~bst() = default;

    /*INSERT*/
    //std::pair<iterator,bool> insert (attr_type& x)

};
