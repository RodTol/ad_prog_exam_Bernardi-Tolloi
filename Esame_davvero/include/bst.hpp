/**
* Author: Rodolfo Tolloi, Giulia Bernardi.
*
* Purpouse: create a custom class that represents a
* binary search tree (bst). This is done by defining a
* compare operator and a head. The first is the relation 
* that will decide where a new node will insert, while
* the second is a unique pointer to the first node of 
* the tree. 
*
* Date: May, 2021.
*/

#include <functional>
#include <utility>
#include <vector>

template <typename key_type, typename value_type, typename OP=std::less<key_type> >
class bst
{
    using attr_type = std::pair<const key_type, value_type>;
    using const_attr_type = const std::pair< const key_type, value_type>;
    using iterator = _iterator< node<attr_type>, attr_type>;
    using const_iterator = _iterator<node<attr_type>, const_attr_type>;

    /**Compare operator*/
    OP compare_operator;

    /** Find utility function:
     * this function return a pointer instead of an iterator and
     * this feature is very useful in other statements.
     * It works by taking the key and comparing it with each node.
     * If it is equal, obviously the pointer to the node is returned.
     * If it is greater or less than the key contained in the node,
     * the pointer will move following the ight or left pointer 
     * of the first node. In this way the search is speeded up,
     * removing automaticcaly the nodes that cannot for sure have
     * equal key */
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
        //std::cout << "I wasn't able to find a node with this key\n";
        return nullptr;
    }

    /** Insert utility function
    * This function is used for both insert and emplace. It
    * will return an iterator to the new node if created, or
    * to the node with equal key if it already exist.
    * Firstly it removes the equal case by calling the _find()
    * function. If it doesn't find it, it will look for the 
    * place to create the new node, moving to the right or to
    * the left. The search will stop when it find a nullptr and then
    * to create the new node it will be performed a call to
    * create_left_child or create_right_child, depending by the case*/
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
                if ( compare_operator(x.first, curr->attr.first) ) {
                    
                    if (curr->left.get()) {
                        curr = curr-> left.get();
                    }

                    else {
                        (*curr).create_left_child(x);
                        return std::make_pair ( iterator{curr->left.get()} , true);
                    }
                }
                else {

                    if (curr->right.get()) {
                        curr = curr-> right.get();
                    }
                    else {
                        (*curr).create_right_child(x);
                        return std::make_pair ( iterator{curr->right.get()} , true);
                    }
                }
            }

            head = std::make_unique<node<attr_type>>(std::forward<O>(x),nullptr);
            return std::make_pair (iterator{head.get()} , true); 
        }
    }

public:

    std::unique_ptr<node<attr_type>> head;

    /**Default constructor*/
    bst() = default;
    /**Default destructor*/
    ~bst() = default;

    /**Custom constructor, who take a attribute and create a node
     * which will be the first of a bst.*/
    explicit bst (attr_type starting_attr) noexcept:
    head {std::make_unique<node <attr_type> >(std::forward<attr_type>(starting_attr), nullptr)} {}

    /**Copy constructor*/
    explicit bst(const bst& tree_to_copy):
    compare_operator {tree_to_copy.compare_operator},
    head {std::make_unique<node <attr_type> >(*tree_to_copy.head.get(), nullptr)} {}

    /**Copy assignement*/
    bst& operator=(const bst& tree_to_copy) {
        if (this!=&tree_to_copy)
        {
             clear();
            head = std::make_unique<node <attr_type> >(*tree_to_copy.head.get(), nullptr);
        }
        return *this;
    }   

    /**Move constructor*/
    explicit bst(bst&& tree_to_copy):
    compare_operator {std::move(tree_to_copy.compare_operator)},
    head {std::move(tree_to_copy.head)} {}

    /**Move assignement*/
    bst& operator=(bst&& tree_to_copy) {
        if (this!=&tree_to_copy)
        {
            compare_operator = std::move(tree_to_copy.compare_operator);
            head = std::move(tree_to_copy.head);
        }
       return *this;
    }

    /**Begin:
     * this function will return an iterator to the leftmost node
     * of the non-const tree.
    */
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
    
    /**Begin:
     * this function will return a const iterator to the
     * leftmost node of the const tree.
     */
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

    /** Cbegin:
     *  it will always return a const_iterator to the leftmost
     *  node of the tree.*/
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

    /** Tail:
     * it will return a iterator to the rightmost node of the
     * non const tree.
    */
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

    /** Tail:
     * it will return a const_iterator to the rightmost node 
     * of the const tree.
    */
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

    /** ctail:
     * it will return a const_iterator to the rightmost node
     * of the tree, both for const and non-const tree.
    */
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
    //std::cout << "From function balance:\n" << tmp[half].first << std::endl;
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


