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
    using attr_type = std::pair<const key_type, value_type>;
    /*keyword iterator*/
    using iterator = _iterator< node<attr_type>, const attr_type>;
    /*creo const_iterator, ossia un iterator con type of attr const*/
    using const_iterator = _iterator<node<const attr_type>, const attr_type>;

    

    /*members of bst class*/
    OP compare_operator;


    //Find utility function

    node<attr_type>* _find(const key_type& x) const {

        if (!head)
        {
        std::cout << "The tree is empty" << std::endl;
        return nullptr;
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
        return  curr;
        }
        }
        std::cout << "I wasn't able to find a node with this key\n";
        return nullptr;
    }


    // Insert utility function
    //SGAIATA: ricicleremo la funzione per emplace
    template <typename O>
    std::pair< iterator, bool> _insert(O&& x)
    {
        node<attr_type>* found {_find(x.first)};
        /*controllare se c'è*/
        if (found)
        {
            std::cout << "there is already a node with this key" << std::endl;
            return  std::make_pair (iterator{found} , false);
        }
        else
        {
            node<attr_type>* curr = head.get();
            while (curr)
            {
                /*se sono minore e esiste il figlio sx mi sposto a sx*/
                if ( compare_operator(x.first, curr->attr.first) ) 
                {
                    if (curr->left.get())
                    {
                         curr = curr-> left.get();
                    }
                    else
                    {
                        (*curr).create_left_child(x);
                        std::cout << "inserted left child" << std::endl;
                        return std::make_pair ( iterator{curr->left.get()} , true);
                    }
               
                }
                /*se non sono minore, sono per return  std::make_pair (iterator{found} , false);*/
                {
                    if (curr->right.get())
                    {
                         curr = curr-> right.get();
                    }
                    else
                    {
                        (*curr).create_right_child(x);
                        std::cout << "inserted right child" << std::endl;
                        return std::make_pair ( iterator{curr->right.get()} , true);
                    }
                }
            }
            head = std::make_unique<node<attr_type>>(std::forward<O>(x),nullptr);
            std::cout << "inserted head" << std::endl;
            return std::make_pair (iterator{head.get()} , true); 
        }
    }
   
public:

    std::unique_ptr<node<attr_type>> head;

    /*default constr e destr*/
    bst() = default;
    ~bst() = default;

    /*custom constr with starting node*/
    bst (attr_type starting_attr) :
    head {std::make_unique<node <attr_type> >(std::forward<attr_type>(starting_attr), nullptr)}
    {std::cout << "bst custom constr" << std::endl;}

    /*metti tutti i const begin cbegin e const tail e ctail!!!!!!!!!!1*/
    /*begin*/
    iterator begin(){
            if (!head)
            {
                std::cout << "The tree is empty" << std::endl;
                return iterator (nullptr);
            }
        node<attr_type>* curr = head.get();
        while(curr -> left)
        {
            curr = curr -> left.get();
        }
        return iterator(curr);
    }
    
    /*tail*/
    iterator tail(){
            if (!head)
            {
                std::cout << "The tree is empty" << std::endl;
                return iterator(nullptr);
            }
        node<attr_type>* curr = head.get();
        while(curr -> right)
        {
            curr = curr -> right.get();
        }
        return iterator(curr);
    }

    /*end*/
    iterator end() noexcept{
        return iterator (nullptr);
    }



        /*find*/
    iterator find(const key_type& x) {
        return iterator{_find(x)};
    }

    /*insert*/
    std::pair<iterator, bool> insert(const attr_type& x){
        return _insert(x);
    }
    std::pair<iterator, bool> insert(attr_type&& x){
        return _insert(std::move(x));
    }

    /*emplace*/
    //Ricilciamo brutalmente _insert
    template< class... Types >
    std::pair<iterator,bool> emplace(Types&&... args){
        return insert(attr_type(std::forward<Types>(args)...));
    }


    /*subscripting operator*/
    value_type& operator[](const key_type& x){
        auto f=_find(x);
        if(f)
             return (*f).attr.second;

        _insert<attr_type>( { x,value_type{} } );
        auto f2= _find(x); 
        return (*f2).attr.second;
     }

    value_type& operator[](key_type&& x){
        auto f=_find(std::move(x));
        if(f)
             return (*f).attr.second;

        _insert<attr_type>( {std::move(x),value_type{} } );
        auto f2= _find(std::move(x)); 
        return (*f2).attr.second;
     }
    
    void clear() {
        head.reset(nullptr);
    }

    friend
    std::ostream& operator<<(std::ostream& os, /*const*/  bst& x) noexcept {
        for (/*const*/ auto& i : x)
        {
            os << i.first << " " << i.second << "\n";
        }
    return os;
    }

};
