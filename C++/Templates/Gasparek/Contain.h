#ifndef _CONTAIN
#define _CONTAIN

// These are non-template container classes which do all the work.
// From these, template classes are derived which have all in-line functions.
// These are type safe but have no overhead.

// This class takes a reference to a bool 'Flag' & stores its value.
// The 'Flag' is set to the 'NewValue' supplied.
// On destruction, it restores the 'Flag's original value.
// It is used to avoid Set/Reset pairs of statements where exceptions may occur in between.
class PACKAGE TSetFlag {
  private:
    bool FOrigValue;
    bool &FFlag;
  public:
    TSetFlag(bool &Flag, bool NewValue);
    ~TSetFlag();
};

// This template class holds an internal pointer to any type of object.
// It is used to avoid new/delete pairs of statements where exceptions may occur in between.
// Objects of this class can be passed to functions wherever the internal pointer is required.
// The constructor is passed the pointer to the constructed object.
// When it goes out of scope, this destructor will delete the internal pointer.
// 'Destroy()' can delete the internal object and set the internal pointer to NULL.
// 'GetPointer()' can 'remove' the internal pointer and pass it on.
template <class T> class TBasePtr {
    T *FPtr;
  public:
    TBasePtr() { FPtr = NULL; }
    TBasePtr(T *Ptr) { FPtr = Ptr; }
    ~TBasePtr() { delete FPtr; }
    void Destroy() { delete FPtr; FPtr = NULL; }
    operator T*() const { return FPtr; }
    T* operator->() const { return FPtr; }
    T* operator()() const { return FPtr; }
    T* operator=(T *Ptr) { FPtr = Ptr; return FPtr; }
    T* GetPointer() { T *Copy = FPtr; FPtr = NULL; return Copy; }
};

// This template class holds an internal pointer to any type of object.
// The default constructor will call new to create an internal object.
// It is used to avoid new/delete pairs of statements where exceptions may occur in between.
// Objects of this class can be passed to functions wherever the internal pointer is required.
// The constructor is passed the pointer to the constructed object.
// When it goes out of scope, this destructor will delete the internal pointer.
// 'Destroy()' can delete the internal object and set the internal pointer to NULL.
// 'GetPointer()' can 'remove' the internal pointer and pass it on.
template <class T> class TObjectPtr {
    T *FPtr;
  public:
    TObjectPtr() { FPtr = new T; }
    TObjectPtr(T *Ptr) { FPtr = Ptr; }
    ~TObjectPtr() { delete FPtr; }
    void Destroy() { delete FPtr; FPtr = NULL; }
    operator T*() const { return FPtr; }
    T* operator->() const { return FPtr; }
    T* operator()() const { return FPtr; }
    T* operator=(T *Ptr) { FPtr = Ptr; return FPtr; }
    T* GetPointer() { T *Copy = FPtr; FPtr = NULL; return Copy; }
};

// This template class holds an internal pointer to an array of any type of object.
// It is used to avoid new/delete pairs of statements where exceptions may occur in between.
// Objects of this class can be passed to functions wherever the internal pointer is required.
// The constructor is passed the pointer to the constructed array.
// When it goes out of scope, this destructor will delete the internal pointer.
// 'Destroy()' can delete the internal array and set the internal pointer to NULL.
// 'GetPointer()' can 'remove' the internal pointer and pass it on.
template <class T> class TArrayPtr {
  protected:
    T *FPtr;
    size_t FSize;
  public:
    TArrayPtr() { FPtr = NULL; FSize = 0; }
    TArrayPtr(size_t s) { FPtr = new T[s]; FSize = s; }
    TArrayPtr(T *Ptr) { FPtr = Ptr; FSize = 0; }
    ~TArrayPtr() { delete[] FPtr; }
    void Destroy() { delete[] FPtr; FPtr = NULL; }
    operator T*() const { return FPtr; }
    T* operator()() const { return FPtr; }
    T &operator[] (int index) const { return FPtr[index]; }
    T* operator=(T *Ptr) { FPtr = Ptr; return FPtr; }
    T* GetPointer() { T *Copy = FPtr; FPtr = NULL; return Copy; }
    void New(size_t s) { delete[] FPtr; FPtr = new T[s]; FSize = s; }
    int Size() { return FSize; }
};

// Define the types of function pointers
typedef bool (*fnIsEqual) (const void *key, const void *elem);
typedef unsigned int (*fnHashValue) (const void *elem);
typedef void (*fnDestroy) (void *el);
typedef int (__cdecl *fnCompare) (const void *key, const void *elem);
typedef int (*fnPtrCompare) (const void **key, const void **elem);

// This is the node which forms the double linked list.
class PACKAGE TNode {
  public:
    TNode (void *new_el, TNode *new_prev, TNode *new_next);

    // Pointer to the object to contain in the list.
    void *FElement;
    // Pointer to the previous node in the list.
    TNode *prev;
    // Pointer to the next node in the list.
    TNode *next;
};

// Iterator for the linked list.
// The 'First()' & 'Next()' functions of the list use this iterator to hold the current position (node).
class PACKAGE TLinkListIterator {
  friend class TPointerLinkList;
  private:
    // Pointer to the current node.
    TNode *node;
  public:
    // Default constructor.
    TLinkListIterator () {}
    // Copy constructor.
    TLinkListIterator (TLinkListIterator &other) : node (other.node) {}
    // Equals operator.
    TLinkListIterator &operator= (TLinkListIterator &other) { node = other.node; return *this; }
};

// This is the base class for a double linked list template class.
// All the work is done by this class so the template class has no overhead.
class PACKAGE TPointerLinkList {
  protected:
    // Pointer to the head of the list.
    TNode *head;
    // Pointer to the tail of the list.
    TNode *tail;
    // Number of elements (nodes) in the list.
    int FElements;

    // The last accessed node.
    // Used when traversing the list.
    TNode *last_node;
    // Index of the last accessed node.
    // Used when traversing the list.
    int last_element;

    // Pointer to a function to call when an element needs to be destroyed.
    // This vector can own the elements.
    fnDestroy destroy_fn;
    // Pointer to a function to pass into sorting & searching functions.
    fnCompare cmp_fn;

    bool find_ptr (const void *key, int &pos);
    void set_to_start ();
    void set_to_next ();
    void *first_ptr (TLinkListIterator &iterator) const;
    void *next_ptr (TLinkListIterator &iterator) const;

    TNode *node (int el);
    int add_ptr (void *new_element, int el);
    void remove_ptr (int el);
    void remove_all_ptrs ();
    void move_ptr_to_head (int el);

    TPointerLinkList ();
    ~TPointerLinkList ();

  public:
    // Returns the number of elements in the list.
    int Count () const { return FElements; }
};

// **********************************************************************
// This is the base class for a dynamic vector template class.
// All the work is done by this class so the template class has no overhead.
// The array size grows to double when an element is added to a full array.
class PACKAGE TPointerVector {
  protected:
    // The hysteresis stops repeated growing & shrinking of dynamic memory.
    // A common situation is where the array is full and an element is repeatedly added & removed.
    // eg an array of 16 pointers with 16 elements (array full) has a 17th element added.
    // It grows to an array of 32 pointers with 17 elements.
    // When the 17th element is removed, it will not shrink, because it has to shrink to 16 - szHysteresis(4).
    enum {
      szHysteresis = 4
    };

    // Array of pointers to hold elements.
    TArrayPtr<void*> FElement;
    // The array size to start with.
    int FStartSize;
    // The current array size.
    int FArraySize;
    // The current number of elements in the array.
    int FElements;

    // Pointer to a function to call when an element needs to be destroyed.
    // This vector can own the elements.
    fnDestroy destroy_fn;

    int add_ptr (void *new_element, int el);
    void remove_ptr (int el);
    void remove_all_ptrs ();
    void MovePtr(int From, int To);
    // Moves the element at index 'el' to index 0 (the head).
    void move_ptr_to_head(int el) { MovePtr(el, 0); }

    void SortPtrs(fnPtrCompare cmp_fn);

    void *BinaryFindPtr(void *Key, fnPtrCompare cmp_fn);
    int BinaryFindPtrIndex(void *Key, fnPtrCompare cmp_fn);
    // Returns true if 'Key' exists in the vector using 'cmp_fn' in a binary search.
    // The vector must be sorted.
    bool BinaryContainsPtr(void *Key, fnPtrCompare cmp_fn) { return BinaryFindPtr(Key, cmp_fn) != NULL; }

    void *LinearFindPtr(void *Key, fnPtrCompare cmp_fn);
    int LinearFindPtrIndex(void *Key, fnPtrCompare cmp_fn);
    // Returns true if 'Key' exists in the vector using 'cmp_fn' in a linear search.
    // The vector need NOT be sorted.
    bool LinearContainsPtr(void *Key, fnPtrCompare cmp_fn) { return LinearFindPtr(Key, cmp_fn) != NULL; }

    int LocatePtr(const void *Pointer) const;
    int GetPtrIndex(const void *ItemPointer) const;

    TPointerVector (int StartSize);
    ~TPointerVector ();

  public:
    // Returns the number of elements contained.
    int Count() const { return FElements; }
};

// **********************************************************************
// The hash node is contained in a hash table.
// This node allows collisions to be resolved.
// If no elements are contained in the node, the pointer is NULL;
// If one element is contained, the pointer points to that element.
// If more than one element is contained, the pointer points to a dynamically allocated array of pointers.
// The array holds the pointrs to all the elements in this node.
// A search of the hash table will then have to do a linear search of that array.
class PACKAGE THashNode {
  protected:
    // Pointer to either an element OR an array of pointers to many elements.
    void **FElement;
    // Number of elements in this node.
    char FElements;

    void adjust (int direction);
    int pos (const void *key, fnIsEqual is_equal_fn) const;

  public:
    THashNode ();
    ~THashNode ();

    // Returns the number of elements contained.
    int Count () const { return FElements; }

    bool AddPointer (void *new_element);
    void *RemovePointerNoDestroy (const void *key, fnIsEqual is_equal_fn);
    bool RemovePointer (const void *key, fnIsEqual is_equal_fn, fnDestroy destroy_fn);
    void *RemovePointer (int el, fnDestroy destroy_fn);
    void RemoveAllPointers (fnDestroy destroy_fn);

    void *FindPointer (const void *key, fnIsEqual is_equal_fn) const;
};

// The hash table contains elements in an array of hash nodes.
// The node used allows collisions to be resolved.
// If no elements are contained in the node, the pointer is NULL;
// If one element is contained, the pointer points to that element.
// If more than one element is contained, the pointer points to a dynamically allocated array of pointers.
// The array holds the pointers to all the elements in this node.
// A search of the hash table will then have to do a linear search of that node's array.
class PACKAGE TPointerHashList {
    // A list of prime numbers to use for table sizes.
    // Prime numbers reduce collisions.
    static int _close_prime [];

  protected:
    // Array of hash nodes.
    THashNode *node;
    // Number of nodes in the array.
    int nodes;
    // Number of elements contained.
    int FElements;

    // Pointer to a function to call when an element needs to be destroyed.
    // This hash list can own the elements.
    fnDestroy DestroyFn;
    // Pointer to a function to pass into searching functions.
    fnIsEqual IsEqualFn;
    // Pointer to a function that calculates the hash value for the type of element contained.
    fnHashValue HashValueFn;

    bool add_ptr (void *new_element);
    bool remove_ptr (const void *key);
    void *remove_ptr_no_destroy (const void *key);
    void remove_all_ptrs ();

    void *find_ptr (const void *key) const;

    TPointerHashList (int new_max_size);
    ~TPointerHashList ();

  public:
    // Returns the number of elements contained.
    int Count () const { return (FElements); }

    static int ClosePrime (int above);
};

#endif


