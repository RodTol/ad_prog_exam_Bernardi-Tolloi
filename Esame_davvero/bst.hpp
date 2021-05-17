/*
Author: Rodolfo Tolloi, Giulia Bernardi.

Purpouse:   VA SCRITTO !!!!!!!!!!!!!!!11.

Date: May, 2021.
*/

#include <functional>
#include <utility>
#include <vector>

template <typename key_type, typename value_type, typename OP=std::less<key_type> >
class bst
{
    /*template for the argument of each node*/
    using attr_type = std::pair<const key_type, value_type>;
    /*template for a argument with const value type for each node*/
    using const_attr_type = const std::pair< const key_type, value_type>;
    /*template for the _iterator class*/
    using iterator = _iterator< node<attr_type>, attr_type>;
    /*template for the _iterator class with constant arguments of the nodes*/
    using const_iterator = _iterator<node<attr_type>, const_attr_type>;

    /*members of bst class*/
    OP compare_operator;

    /*Find utility function to return a pointer instead of an iterator. This
    feature is very useful in other statements. This function has a const
    keyword at the end beacuse it will not modify the tree which is called upon*/

    //SPIEGA COME FUNZIONA
    node<attr_type>* _find(const key_type& x) const {

        if (!head) {
            std::cout << "The tree is empty\n";
            return nullptr;
        }

        node<attr_type>* curr = head.get();
        while (curr) {

            if ( compare_operator(x, curr->attr.first) ) {
                curr = curr-> left.get();
            }

            else if ( compare_operator(curr->attr.first, x) ) {
                curr = curr -> right.get();
            }
                
            else {
                //std::cout << "Iterator at node with serched key" << std::endl;
                return  curr;
            }
        }
        std::cout << "I wasn't able to find a node with this key\n";
        return nullptr;
    }

    /* Insert utility function
    This function is used for both insert and emplace.
    
     SCRIVI COME FUNZIA*/
    template <typename O>
    std::pair< iterator, bool> _insert(O&& x)
    {
        node<attr_type>* found {_find(x.first)};
        if (found) {
            std::cout << "There is already a node with this key\n";
            return  std::make_pair (iterator{found} , false);
        }
        else {
            node<attr_type>* curr = head.get();
            while (curr) {
                /*se sono minore e esiste il figlio sx mi sposto a sx*/
                if ( compare_operator(x.first, curr->attr.first) ) {
                    
                    if (curr->left.get()) {
                        curr = curr-> left.get();
                    }

                    else {
                        (*curr).create_left_child(x);
                        std::cout << "Inserted left child\n";
                        return std::make_pair ( iterator{curr->left.get()} , true);
                    }
                }
                /*se non sono minore, sono per return  std::make_pair (iterator{found} , false);*/
                else {

                    if (curr->right.get()) {
                        curr = curr-> right.get();
                    }
                    else {
                        (*curr).create_right_child(x);
                        std::cout << "Inserted right child\n";
                        return std::make_pair ( iterator{curr->right.get()} , true);
                    }
                }
            }

            head = std::make_unique<node<attr_type>>(std::forward<O>(x),nullptr);
            std::cout << "Inserted as head" << std::endl;
            return std::make_pair (iterator{head.get()} , true); 
        }
    }

public:

    std::unique_ptr<node<attr_type>> head;

    /*default constr e destr*/
    bst() = default;
    ~bst() = default;

    /*custom constr with starting node*/
    explicit bst (attr_type starting_attr) noexcept:
    head {std::make_unique<node <attr_type> >(std::forward<attr_type>(starting_attr), nullptr)} {}

    /*copy ctor*/
    explicit bst(const bst& tree_to_copy):
    compare_operator {tree_to_copy.compare_operator},
    head {std::make_unique<node <attr_type> >(*tree_to_copy.head.get(), nullptr)} {}

    /*copy assignement*/
    bst& operator=(const bst& tree_to_copy) {
        if (this!=&tree_to_copy)
        {
             clear();
            head = std::make_unique<node <attr_type> >(*tree_to_copy.head.get(), nullptr);
        }
        return *this;
    }   

    /*move ctor*/
    explicit bst(bst&& tree_to_copy):
    compare_operator {std::move(tree_to_copy.compare_operator)},
    head {std::move(tree_to_copy.head)} {}

    /*move assignement*/
    bst& operator=(bst&& tree_to_copy) {
        if (this!=&tree_to_copy)
        {
            compare_operator = std::move(tree_to_copy.compare_operator);
            head = std::move(tree_to_copy.head);
        }
        std::cout << "move ass" << std::endl;
        return *this;
    }

    /*begin*/
    iterator begin() noexcept {
        if (!head) {
            std::cout << "The tree is empty" << std::endl;
            return iterator (nullptr);
        }
        node<attr_type>* curr = head.get();
        while(curr -> left) {
            curr = curr -> left.get();
        }
        return iterator(curr);
    }
    
    /*begin called for a const object*/
    const_iterator begin() const noexcept {
        if (!head) {
            std::cout << "The tree is empty" << std::endl;
            return const_iterator (nullptr);
        }
        node<attr_type>* curr = head.get();
        while(curr -> left) {
            curr = curr -> left.get();
        }
        return const_iterator(curr);
    }

    /*cbegin called for a  object. It will always return a const_iterator*/
    const_iterator cbegin() const noexcept {
        if (!head) {
            std::cout << "The tree is empty" << std::endl;
            return const_iterator (nullptr);
        }
        node<attr_type>* curr = head.get();
        while(curr -> left) {
            curr = curr -> left.get();
        }
        return const_iterator(curr);
    }

    /*tail*/
    iterator tail() noexcept{
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

    /*tail*/
    const_iterator tail() const noexcept{
            if (!head)
            {
                std::cout << "The tree is empty" << std::endl;
                return const_iterator(nullptr);
            }
        node<attr_type>* curr = head.get();
        while(curr -> right)
        {
            curr = curr -> right.get();
        }
        return const_iterator(curr);
    }

    /*ctail*/
    const_iterator ctail() const noexcept{
            if (!head)
            {
                std::cout << "The tree is empty" << std::endl;
                return const_iterator(nullptr);
            }
        node<attr_type>* curr = head.get();
        while(curr -> right)
        {
            curr = curr -> right.get();
        }
        return const_iterator(curr);
    }

    /*end*/
    iterator end() noexcept{
        return iterator (nullptr);
    }

    /*end*/
    const_iterator end() const noexcept{
        return const_iterator (nullptr);
    }

    /*cend*/
    const_iterator cend() const noexcept{
        return const_iterator (nullptr);
    }

    /*find*/
    iterator find(const key_type& x) {
        return iterator{_find(x)};
    }

    /*find with const_iterator*/
    const_iterator find(const key_type& x) const {
        return const_iterator{_find(x)};
    }

    /*insert l-value*/
    std::pair<iterator, bool> insert(const attr_type& x){
        return _insert(x);
    }

    /*insert r-value*/
    std::pair<iterator, bool> insert(attr_type&& x){
        return _insert(std::move(x));
    }

    /*emplace*/
    template< class... Types >
    std::pair<iterator,bool> emplace(Types&&... args){
        return insert(attr_type(std::forward<Types>(args)...));
    }


    /*subscripting operator for l-value*/
    value_type& operator[](const key_type& x){
        auto f=_find(x);
        if(f)
             return (*f).attr.second;

        _insert<attr_type>( { x,value_type{} } );
        auto f2= _find(x); 
        return (*f2).attr.second;
     }

    /*subscripting operator for r-value*/
    value_type& operator[](key_type&& x){
        auto f=_find(std::move(x));
        if(f)
             return (*f).attr.second;

        _insert<attr_type>( {std::move(x),value_type{} } );
        auto f2= _find(std::move(x)); 
        return (*f2).attr.second;
     }
    
    /*clear function*/
    void clear() {
        head.reset(nullptr);
    }

    /*put to*/
    friend
    std::ostream& operator<<(std::ostream& os, const bst& x) noexcept {
        for ( const auto& i : x)
        {
            os << i.first << " " << i.second << "\n";
        }
    return os;
    }

    /*size*/
    std::size_t size() {
        std::size_t _size{0};
        for ( auto i = cbegin(); i != cend(); ++i)
        {
            ++_size;
        }
        
        return _size;
    }

    /*balance*/
    /*speigalo bene dio madonna*/
    void balance() {

        if (!head) {
         std::cout << "The tree is empty" << std::endl;
        return;
        }

        std::vector<attr_type> tmp {};
        for (auto i = cbegin(); i != cend(); ++i)
        {
            tmp.push_back(*i);
        }

        clear();
        balance(tmp, 0, tmp.size());
    }



    /*side function for the balance function*/
    void balance(std::vector<attr_type>& tmp, std::size_t left, std::size_t right) noexcept {
    if ( right - left < 1)
        return;
    auto half = ((left + right ) / 2);
    insert(tmp[half]);
    std::cout << "From function balance:\n" << tmp[half].first << std::endl;
    balance(tmp, left, half);
    balance(tmp, half + 1, right);
    }

    /*find min of the a subtree*/
    node<attr_type>* min_sub (node<attr_type>* start) {
        while(start -> left) {
            start = start -> left.get();
        }
        return start;
    }    

    /*erase*/
    /*speiga come funziona con il fatto che prendi il min del subtree di 
    dx e lo metti come nuovo nodo*/
    void erase(const key_type& x) {
        if (!_find(x))
        {
            std::cout << "A node with such key doesn't exist \n";
            return;
        }
        else {
            /*the node with searched key has no child*/
            if ( !(_find(x)->left)  &&  !(_find(x)->right) ) 
            {
                if ( !(_find(x)->parent))
                {
                    head.reset();
                }
                else
                {
                    if (_find(x)->parent->left.get() == _find(x))
                    {
                        _find(x)->parent->left.reset(); 
                    }
                    else
                    {
                        _find(x)->parent->right.reset();
                    }
                }
            }
            /*the node has only left child*/
            else if ( (_find(x)->left) &&  !(_find(x)->right) )
            {
                if ( !(_find(x)->parent) )
                {
                    _find(x)->left-> parent = nullptr;
                    head.reset(_find(x)->left.release());
                }
                else
                {
                    _find(x)->left->parent = _find(x)->parent;
                    if (_find(x)->parent ->left.get() == _find(x))
                    {
                        _find(x)->parent->left.reset(_find(x)->left.release());
                    }
                    else 
                    {
                        _find(x)->parent->right.reset(_find(x)->left.release());
                    }

                }
                
            }
            /*the node has only right child*/
            else if ( !(_find(x)->left) &&  (_find(x)->right) )
            {
                if ( !(_find(x)->parent) )
                {
                    _find(x)->right-> parent = nullptr;
                    head.reset(_find(x)->right.release());
                }
                else
                {
                    _find(x)->right->parent = _find(x)->parent;
                    if (_find(x)->parent ->left.get() == _find(x))
                    {
                        _find(x)->parent->left.reset(_find(x)->right.release());
                    }
                    else 
                    {
                        _find(x)->parent->right.reset(_find(x)->right.release());
                    }

                }
                
            }
            /*the node has both left and right child*/
            else if ( (_find(x)->left) &&  (_find(x)->right))
            {
                /*i move the left subtree of _find(x)* to the left of the
                leftomost of his right subtree. So, i am again in one of 
                the case above*/

                /*NOTA: il leftmost di un tree non ha per forza un left,
                altrimenti non sarebbe tale*/

                node<attr_type>* min_of_subtree {min_sub(_find(x)->right.get())};
                _find(x)->left->parent = min_of_subtree;
                min_of_subtree->left = std::move(_find(x)->left);


                erase(x);
                
            }
            
        }
    }


};


