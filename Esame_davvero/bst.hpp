/*
Author: Rodolfo Tolloi, Giulia Bernardi.

Purpouse:   VA SCRITTO !!!!!!!!!!!!!!!11.

Date: May, 2021.
*/

#include <functional>
#include <utility>

template <typename key_type, typename value_type, typename OP=std::less<key_type> >
class bst
{
    /*creo la coppia key-value che sarà il type degli argomenti
    dei vari nodi. Per velocizzare, chiamo questo type attr_type*/
    using attr_type = std::pair< key_type, value_type>;

    /*creo const_iterator, ossia un iterator con type of attr const*/
    using const_iterator = _iterator<node<const attr_type>, const attr_type>;

    /*members of bst class*/
    
    std::size_t _size;
    OP compare_operator;
   
public:

    std::unique_ptr<node<attr_type>> head;

    /*default constr e destr*/
    bst() = default;
    ~bst() = default;

    /*custom constr with starting node*/
    bst (attr_type starting_attr) :
    _size{1},
    head {std::make_unique<node <attr_type> >(std::forward<attr_type>(starting_attr), nullptr)}
    {std::cout << "bst custom constr" << std::endl;}

    /*metti tutti i const begin cbegin e const tail e ctail!!!!!!!!!!1*/
    /*begin*/
    _iterator<node<attr_type>, key_type> begin(){
            if (!head)
            {
                std::cout << "The tree is empty" << std::endl;
                return _iterator<node<attr_type>, key_type>(nullptr);
            }
        node<attr_type>* curr = head.get();
        while(curr -> left)
        {
            curr = curr -> left.get();
        }
        return _iterator<node<attr_type>, key_type>(curr);
    }
    
    /*tail*/
    _iterator<node<attr_type>, key_type> tail(){
            if (!head)
            {
                std::cout << "The tree is empty" << std::endl;
                return _iterator<node<attr_type>, key_type>(nullptr);
            }
        node<attr_type>* curr = head.get();
        while(curr -> right)
        {
            curr = curr -> right.get();
        }
        return _iterator<node<attr_type>, key_type>(curr);
    }

    /*end*/
    _iterator<node<attr_type>, key_type> end() noexcept{
        return _iterator<node<attr_type>, key_type>(nullptr);
    }



        /*find*/
    _iterator< node<attr_type>, key_type> find(const key_type& x) {
         if (!head)
            {
                std::cout << "The tree is empty" << std::endl;
                return _iterator<node<attr_type>, key_type>(nullptr);
            }
        node<attr_type>* curr = head.get();

        while (curr)
        {
         /*se sono minore guardo a sx*/
         if ( compare_operator(x, curr->attr.first) ) 
            {
                curr = curr-> left.get();
            }
         else if ( compare_operator(curr->attr.first, x) )
            {
                curr = curr -> right.get();
            }
         else 
            {
                std::cout << "iterator at node with serched key" << std::endl;
                return  _iterator< node<attr_type>, key_type> (curr);
            }
        }
        std::cout << "I wasn't able to find a node with this key\n";
        return end();


        
    } 



    

};
