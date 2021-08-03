#ifndef _LIST_CLASS
#define _LIST_CLASS

//TPointerVector is defined in Contain.cpp

namespace CommonLib {

// **********************************************************************
// This template list class can make a double linked list of any type of pointers.
// The list can own the pointers & destroy them on removal.
// This is a type safe wrapper around 'TPointerLinkList' with no overhead.
// eg TLinkList<TString *> Strings
template <class T>
class TLinkList : public TPointerLinkList {
  protected:
    // A pointer to this function is passed to 'Remove()' to destroy elements.
    static void destroy (void *el);

  public:
    // Constructs a list setting ownership by 'list_owns_pointers'.
    TLinkList (bool list_owns_pointers) : TPointerLinkList () {
      if (list_owns_pointers) destroy_fn = TLinkList<T>::destroy;
    }

    // Adds 'new_element' and returns the index of its position in the list.
    int Add (T new_element) { return (add_ptr ((void *) new_element, FElements)); }
    // Adds 'new_element' at index 'el' and returns 'el' (the index of its position in the list).
    int Add (T new_element, int el) { return (add_ptr ((void *) new_element, el)); }

    // Removes the element at index 'el' & destroys it if the list owns the elements.
    void Remove (int el) { remove_ptr (el); }
    // Removes the the last element & destroys it if the list owns the elements.
    void Remove () { remove_ptr (FElements - 1); }
    // Removes all the elements & destroys them if the list owns the elements.
    void RemoveAll () { remove_all_ptrs (); }

    // Moves the element at index 'el' to index 0 (the head).
    void MoveToHead (int el) { TPointerLinkList::move_ptr_to_head (el); }

    // Returns the element at index 'el'.
    T operator[] (int el) { return (T) node (el)->FElement; }
    // Returns the first element in the list.
    T First (TLinkListIterator &iterator) const { return (T) first_ptr (iterator); }
    // Returns the next element in the list.
    T Next (TLinkListIterator &iterator) const { return (T) next_ptr (iterator); }
};
template <class T> void TLinkList<T>::destroy (void *el) { delete (T) el; }

// **********************************************************************
// This template list class can make a sorted double linked list of any type of pointers.
// The list can own the pointers & destroy them on removal.
// This is a type safe wrapper around 'TPointerLinkList' with no overhead.
// eg TSortList<TString *> Strings
template <class T>
class TSortList : public TPointerLinkList {
  protected:
    // A pointer to this function is passed to 'Remove()' to destroy elements.
    static void destroy (void *el);
    // A pointer to this function is passed to the search functions.
    static int compare (T key, T elem) { return ((*key > *elem) ? 1 : ((*key == *elem) ? 0 : -1)); }
    // Can enforce uniqueness of items in the list.
    bool FUniqueItems;
    // Ownership
    bool FOwnsPointers;
  public:
    // Constructs a list setting ownership by 'list_owns_pointers'.
    // Uniqueness of elements is set with 'UniqueItems'.
    TSortList (bool list_owns_pointers, bool UniqueItems = false) : TPointerLinkList () {
      FUniqueItems = UniqueItems;
      FOwnsPointers = list_owns_pointers;
      if(FOwnsPointers)
        destroy_fn = TSortList<T>::destroy;
      cmp_fn = (fnCompare) TSortList<T>::compare;
    }

    // Adds 'new_element' and returns the index of its position in the list.
    int Add (T new_element) {
      int el_to_find;
      if(Find (new_element, el_to_find) && FUniqueItems) {
        if(FOwnsPointers)
          delete new_element;
        return el_to_find;
      }
      return add_ptr (new_element, el_to_find);
    }

    // Removes the element at index 'el' & destroys it if the list owns the elements.
    void Remove (int el) { remove_ptr (el); }
    // Removes the the last element & destroys it if the list owns the elements.
    void Remove () { remove_ptr (FElements - 1); }
    // Removes all the elements & destroys them if the list owns the elements.
    void RemoveAll () { remove_all_ptrs (); }

    // Returns the first element in the list.
    T First (TLinkListIterator &iterator) const { return (T) first_ptr (iterator); }
    // Returns the next element in the list.
    T Next (TLinkListIterator &iterator) const { return (T) next_ptr (iterator); }
    // Returns the element at index 'el'.
    T operator[] (int el) { return ((T) node (el)->FElement); }
    // Returns true if the element matching 'key' is found.
    // Sets 'pos' top the index if found.
    bool Find (T key, int &pos) { return (find_ptr (key, pos)); }
    // Returns true if the element matching 'key' is found.
    bool Contains (T key) {
      int pos;
      return (find_ptr (key, pos));
    }
};
template <class T> void TSortList<T>::destroy (void *el) { delete (T) el; }

// **********************************************************************
// This template container class can make a dynamic vector of any type of pointers.
// It grows double when its size is exceeded.
// It can own the pointers & destroy them on removal.
template <class T>
class TVector : public TPointerVector {
  protected:
    // A pointer to this function is passed to 'Remove()' to destroy elements.
    static void destroy (void *el) { delete (T) el; }

  public:
    // Constructs a vector setting ownership by 'list_owns_pointers'.
    TVector(bool list_owns_pointers = true) : TPointerVector (szHysteresis) {
      if(list_owns_pointers) destroy_fn = TVector<T>::destroy;
    }
    // Constructs a vector with initial size 'new_start_size'.
    // The ownership is set by 'list_owns_pointers'.
    TVector(int new_start_size, bool list_owns_pointers) : TPointerVector (new_start_size) {
      if(list_owns_pointers) destroy_fn = TVector<T>::destroy;
    }

    // Adds 'new_element' and returns the index of its position.
    int Add(T new_element) { return (add_ptr ((void *) new_element, FElements)); }
    // Adds 'new_element' at index 'el' and returns 'el' (the index of its position).
    int Add(T new_element, int el) { return (add_ptr ((void *) new_element, el)); }

    // Removes the element at index 'el' & destroys it if the vector owns the elements.
    void Remove(int el) { remove_ptr (el); }
    // Removes the the last element & destroys it if the list vector the elements.
    void Remove() { Remove (FElements - 1); }
    // Removes the elemnt matching the specified Item.
	 void Remove(const T Item)
	 {
		int i = GetIndex(Item);
		if (i >= 0)
			Remove (GetIndex(Item));
	 }
    // Removes all the elements & destroys them if the vector owns the elements.
    void RemoveAll() { remove_all_ptrs (); }

    // Moves the element at 'From' to index 'To'.
    void MoveElement(int From, int To) { MovePtr(From, To); }
    // Moves the element at index 'el' to index 0 (the head).
    void MoveToHead (int el) { TPointerVector::move_ptr_to_head (el); }

    // Returns the element at index 'el'.
    T operator[] (int el) const { return (FElement == NULL ? NULL : (T) FElement [el]); }
    // Returns the index of the element 'Item'.
    int GetIndex(const T Item) const { return GetPtrIndex(Item); }
};

// *************************************************************************
// This template container class can make a stack based on a dynamic vector.
// It grows double when its size is exceeded.
// It does NOT own the elements, so they can they can be used on removal.
template <class T>
class TStack : protected TVector<T> {
  public:
    // Default constructor.
    TStack () : TVector<T> (false) {}

    // Pushes 'NewElement' onto the top of the stack.
    void Push (T NewElement) { Add(NewElement); }
    // Pops an element' off the stack & returns it.
    T Pop () { T Temp = (*this) [FElements - 1]; Remove(); return Temp; }
    // Returns the element' on the top of the stack.
    T Top () const { return (*this) [FElements - 1]; }
    // Returns the height of the stack.
    int Level () const { return Count (); }
};

// *************************************************************************
// This template container class can make a sortable dynamic vector of any type of pointers.
// It grows double when its size is exceeded.
// It can own the pointers & destroy them on removal.
// The elements must be sorted by an explicit call to 'Sort()'.
template <class T>
class TSortableVector : public TVector<T> {
  protected:
    // A pointer to this function is passed to the sort & search functions.
    static int Compare (T *key, T *elem) { return ((**key > **elem) ? 1 : ((**key == **elem) ? 0 : -1)); }
    // A pointer to this function is passed to the reverse sort & search functions.
    static int ReverseCompare (T *key, T *elem) { return ((**key > **elem) ? -1 : ((**key == **elem) ? 0 : 1)); }
    // Sorting can be in reverse order.
    bool FReverse;
  public:
    // Constructs a sortable vector setting ownership by 'list_owns_pointers'.
    TSortableVector(bool list_owns_pointers = true) : TVector<T> (list_owns_pointers) { FReverse = false; }
    // Constructs a sortable vector with initial size 'new_start_size'.
    // The setting of ownership is by 'list_owns_pointers'.
    TSortableVector(int new_start_size, bool list_owns_pointers) : TVector<T> (new_start_size, list_owns_pointers) {}

    // Sort the elements in order set by 'Reverse'.
    void Sort(bool Reverse = false) { FReverse = Reverse; SortPtrs((fnPtrCompare)(Reverse ? ReverseCompare : Compare)); }
    // Sort the elements using 'cmp_fn'.
    void Sort(fnPtrCompare cmp_fn) { FReverse = false; SortPtrs(cmp_fn); }

    // Returns the index of the element matching 'key' using a binary search.
    // 'Sort()' must be called first.
    int BinaryFind(T Key) { return BinaryFindPtrIndex(Key, (fnPtrCompare)(FReverse ? ReverseCompare : Compare)); }
    // Returns the index of the element matching 'key' with 'cmp_fn', using a binary search.
    // 'Sort()' must be called first.
    int BinaryFind(T Key, fnPtrCompare cmp_fn) { return BinaryFindPtrIndex(Key, cmp_fn); }
    // Returns true if the element matching 'key' is found using a binary search.
    // 'Sort()' must be called first.
    bool BinaryContains(T Key) { return BinaryContainsPtr(Key, (fnPtrCompare)(FReverse ? ReverseCompare : Compare)); }

    // Returns the index of the element matching 'key' using a linear search.
    // 'Sort()' need NOT be called first.
    int Find(T Key) { return LinearFindPtrIndex(Key, (fnPtrCompare)Compare); }
    // Returns the index of the element matching 'key' with 'cmp_fn', using a linear search.
    // 'Sort()' need NOT be called first.
    int Find(T Key, fnPtrCompare cmp_fn) { return LinearFindPtrIndex(Key, cmp_fn); }
    // Returns true if the element matching 'key' is found using a linear search.
    // 'Sort()' need NOT be called first.
    bool Contains(T Key) { return LinearContainsPtr(Key, (fnPtrCompare)Compare); }
};

// **********************************************************************
// This template container class can make a dynamic array of any type of objects.
// It does NOT own the elements.
template <class T>
class TArray {
  protected:
    // Default start size.
    enum {
      DefaultSize = 4
    };

    // Array of elements
    TArrayPtr<T> FElement;
    // Start size.
    int FStartSize;
    // Current array size.
    int FArraySize;

    // Changes the size of the array to 'Size'.
    void ResizeTo(int Size);

  public:
    // Constructs an array with initial size of 'StartSize'.
    TArray(int StartSize = DefaultSize);

    // Expands the array to 'Size'.
    void GrowTo(int Size);
    // Shrinks the array to 'Size'.
    void ShrinkTo(int Size);
    // Returns the array size (not necessarily the number of elements).
    int Count() const { return FArraySize; }

    // Returns the element at 'Position'.
    T& operator[] (int Position);
};
template <class T> TArray<T>::TArray(int StartSize)
{
  FStartSize = StartSize;
  FArraySize = 0;
}
template <class T> void TArray<T>::ResizeTo(int Size) {
  if(!Size) {
    // Blank array.
    FElement.Destroy();
    FArraySize = 0;
  }
  else {
    // Create a new array & copy the elements.
    TArrayPtr<T> NewElement(Size);
    for(int n = 0; n < min(FArraySize, Size); n++)
      NewElement[n] = FElement[n];
    FElement.Destroy();
    FElement = NewElement.GetPointer();
    FArraySize = Size;
  }
}
template <class T> void TArray<T>::GrowTo(int Size) {
  if(Size > FArraySize)
    ResizeTo(Size);
}
template <class T> void TArray<T>::ShrinkTo(int Size) {
  if(Size < FArraySize)
    ResizeTo(Size);
}
template <class T> T& TArray<T>::operator[] (int Position) {
  if(Position >= FArraySize) {
    int Size = max(Position + 1, max(FStartSize, FArraySize * 2));
    GrowTo(Size);
  }
  return FElement[Position];
}

}
#endif

