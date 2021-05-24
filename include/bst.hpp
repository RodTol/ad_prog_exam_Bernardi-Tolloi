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
     * This function returns a pointer instead of an iterator and
     * this feature is very useful in other statements.
     * It works by taking the key and comparing it with each node.
     * If it is equal, obviously the pointer to the node is returned.
     * If it is bigger or smaller than the key contained in the node,
     * the pointer will move following the right or left pointer 
     * of the first node.*/
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
    * will return an iterator to the new node, if created, or
    * to the node with equal key, if it already exists.
    * Firstly it removes the equal case by calling the _find()
    * function. If it doesn't find it, it will look for the correct
    * place to create the new node, moving to the right or to
    * the left. The search will stop when it finds a nullptr and then
    * to create the new node it will be performed a call to
    * create_left_child or create_right_child, depending on the case*/
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

    /**Custom constructor, which takes an attribute and creates a node
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
            auto tmp  {tree_to_copy};
            *this = std::move(tmp);
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
     * This function will return an iterator to the leftmost node
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
     * This function will return a const iterator to the
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
     *  It will always return a const iterator to the leftmost
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
     * It will return an iterator to the rightmost node of the
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
     * It will return a const iterator to the rightmost node 
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
     * It will return a const iterator to the rightmost node
     * of the tree.
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

    /** End:
     * It will return an iterator to one-past the last
     * element of the tree.
    */
    iterator end() noexcept{
        return iterator (nullptr);
    }

    /** End:
     * It will return a const iterator to one-past the last
     * element of the const tree.
    */
    const_iterator end() const noexcept{
        return const_iterator (nullptr);
    }

    /** cend:
     * It will return a const_iterator to one-past the
     * last element.
    */
    const_iterator cend() const noexcept{
        return const_iterator (nullptr);
    }

    /**Find:
     * It looks for a node with key equal to the input and if
     * it succeeds it returns an iterator to the node, otherwise,
     * it returns an iterator to nullptr.
    */
    iterator find(const key_type& x) {
        return iterator{_find(x)};
    }

    /** Find:
     * It looks for a node with key equal to the input, and if
     * it succeeds it returns a const iterator to the node, otherwise,
     * it returns a const_iterator to nullptr.
     */
    const_iterator find(const key_type& x) const {
        return const_iterator{_find(x)};
    }

    /** Insert:
     * This function tries to create a node with the key 
     * equal to the input x. It returns a pair made by a 
     * boolean and a iterator. The boolean is false if 
     * the node with key = x already exists, true if the
     * node must be created. The iterator points to the node
     * both if it was just created or if it was already there.
     * This formulation is for l-values.
    */
    std::pair<iterator, bool> insert(const attr_type& x){
        return _insert(x);
    }
    /** Insert:
     * This function tries to create a node with the attribute
     * equal to the input x. It returns a pair made by a 
     * boolean and a iterator. The boolean is false if 
     * the node with key = x already exists, true if the
     * node must be created. The iterator points to the node
     * both if it was just created or it was already there.
     * This formulation is for r-values.
    */
    std::pair<iterator, bool> insert(attr_type&& x){
        return _insert(std::move(x));
    }

    /**Emplace:
     * This function tries to create one or more element 
     * if there is no element with the same key.
    */
    template< class... Types >
    std::pair<iterator,bool> emplace(Types&&... args){
        return insert(attr_type(std::forward<Types>(args)...));
    }


    /**Subscripting operator:
     * This function returns a reference to the value of
     * the node with the key equal to the input x,
     * performing an insertion if that key does not already
     * exist. This formulation is for l-value.
     */
    value_type& operator[](const key_type& x){
        auto f=_find(x);
        if(f)
             return (*f).attr.second;

        _insert<attr_type>( { x,value_type{} } );
        auto f2= _find(x); 
        return (*f2).attr.second;
     }

    /**subscripting operator:
     * This function returns a reference to the value of
     * the node with the key equal to the input x,
     * performing an insertion if that key does not already
     * exist. This formulation is for r-value.
     */
    value_type& operator[](key_type&& x){
        auto f=_find(std::move(x));
        if(f)
             return (*f).attr.second;

        _insert<attr_type>( {std::move(x),value_type{} } );
        auto f2= _find(std::move(x)); 
        return (*f2).attr.second;
     }
    
    /**clear:
     * This function clears the content of the tree by resetting
     * the head pointer to nullptr.
     */
    void clear() {
        head.reset(nullptr);
    }

    /** put-to:
     * Custom overloading of put-to operator that will 
     * print the tree following the traversal.
    */
    friend
    std::ostream& operator<<(std::ostream& os, const bst& x) noexcept {
        for ( const auto& i : x)
        {
            os << i.first << " " << i.second << "\n";
        }
    return os;
    }

    /**size:
     * Function that returns the number of nodes inside
     * the tree.
    */
    std::size_t size() {
        std::size_t _size{0};
        for ( auto i = cbegin(); i != cend(); ++i)
        {
            ++_size;
        }
        
        return _size;
    }

    /**balance:
     * Function that will balance the tree, rewriting it
     * with roughly half of the nodes on the left side and
     * the other half on the right side. This first overloading
     * creates an orderd vector "tmp" by taking the attributes of
     * the nodes in the traversal order. After that it will
     * call the clear function, erasing the content of the 
     * tree. In the end it will call the second overloding
     * which will create the ordered tree.
    */
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

    /**balance:
     * This second overloading of the balance function will
     * take an input vector of attributes and use the insert 
     * function to create the nodes such that the tree will be
     * balanced. To do so, it will start by inserting the
     * node in the middle of the vector (or the roundown value
     * if the size of the vector is odd). Then it will
     * repeat the same process for one half of the vector,
     * inserting another node and by iterating this process
     * it will create the balanced tree.
    */
    void balance(std::vector<attr_type>& tmp, std::size_t left, std::size_t right) noexcept {
    if ( right - left < 1)
        return;
    auto half = ((left + right ) / 2);
    insert(tmp[half]);
    balance(tmp, left, half);
    balance(tmp, half + 1, right);
    }

    /**min_sub:
     * This function returns a pointer to the leftmost node
     * of the subtree of a input node.
    */
    node<attr_type>* min_sub (node<attr_type>* start) {
        while(start -> left) {
            start = start -> left.get();
        }
        return start;
    }    

    /**erase:
     * This function purpouse is to remove a node with key 
     * equal to the the input (if it exists). The first step is
     * to check if this node exists. There are 3 case: the node
     * has no children, it has one child (left or right) or it has 
     * both children. In the first case the function simply removes
     * the node by resetting the father's left or right pointer and the 
     * objective node's parent pointer. In the second case 
     * it will also connect the father node to the objective node's child,
     * preserving the structure of the tree. The last case is
     * solved by moving the left subtree of the objective node
     * to the leftmost element of the right subtree of the
     * objective node. Thanks to this operation, the node will
     * only have a right child, and so the problem can be solved
     * as explained above by calling again the function erase. 
     */ 
    void erase(const key_type& x) {
        if (!_find(x))
        {
            std::cout << "A node with such key doesn't exist \n";
            return;
        }
        else {

            auto tmp = _find(x);
            /*The node with input key has no children*/
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
                    tmp->parent = nullptr;
                }
            }
            /*the node only has a left child*/
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
                    tmp->parent = nullptr;
                }
                
            }
            /*the node only has a right child*/
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
                    tmp->parent = nullptr;
                }
                
            }
            /*the node has both left and right child*/
            else if ( (_find(x)->left) &&  (_find(x)->right))
            {
                /*I move the left subtree of _find(x)* to the left of the
                leftomost of its right subtree. So, I am again in one of 
                the cases above*/
                node<attr_type>* min_of_subtree {min_sub(_find(x)->right.get())};
                _find(x)->left->parent = min_of_subtree;
                min_of_subtree->left = std::move(_find(x)->left);


                erase(x);
                
            }
            
        }
    }


};


