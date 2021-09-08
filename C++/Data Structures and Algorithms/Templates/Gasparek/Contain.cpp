#include "CommonLib.h"
#pragma hdrstop

#pragma package(smart_init)

// ***********************************************************************
// Constructs a linked list node containing 'new_el' with pointers 'new_prev' & 'new_next'.
TNode::TNode (void *new_el, TNode *new_prev, TNode *new_next)
{
  FElement = new_el;
  prev = new_prev;
  next = new_next;
}

// ***********************************************************************
// Default constructor
TPointerLinkList::TPointerLinkList ()
{
  FElements = last_element = 0;
  head = tail = last_node = NULL;
  destroy_fn = NULL;
  cmp_fn = NULL;
}

// ***********************************************************************
// Removes all elements and destroys the object.
// If the list owns the elements, the elements are destroyed.
TPointerLinkList::~TPointerLinkList ()
{
  try {
    remove_all_ptrs ();
  }
  catch(Exception &Error){
    ShowMessage(Error.Message);
  }
}

// ***********************************************************************
// Returns the node at index 'el'.
// Updates 'last_node' and 'last_element'.
TNode *TPointerLinkList::node (int el)
{
  const int START_HEAD = 0, START_TAIL = 1, START_FORWARDS = 2, START_BACKWARDS = 3;

  assert ((el >= 0) && (el < FElements));

  int start;
  // Do the most likely (fastest) operations first & work through the possibilities.
  if (last_node) {
    // Next
    if (el == last_element + 1) {
      last_element++;
      last_node = last_node->next;
      return last_node;
    }

    // Same
    if (el == last_element)
      return last_node;

    // Previous
    if (el == last_element - 1) {
      last_element--;
      last_node = last_node->prev;
      return last_node;
    }

    // Start at 0
    if (!el) {
      last_element = 0;
      last_node = head;
      return last_node;
    }

    // Start at head ?
    start = START_HEAD;
    int delta = el;

    // Start at tail
    if (FElements - el < delta) {
      delta = FElements - el;
      start = START_TAIL;
    }

    if (abs (el - last_element) < delta) {
    // Start at last_element - forwards
      if (el > last_element) {
        // delta = el - last_element; UPDATE - why was this here ?
        start = START_FORWARDS;
      }
      else {
      // Start at last_element - backwards
        //delta = last_element - el; UPDATE - why was this here ?
        start = START_BACKWARDS;
      }
    }
  }
  else
    start = (FElements - el > el) ? START_HEAD : START_TAIL;

  int direction;
  TNode *nd;
  switch (start) {
    case START_HEAD:
      nd = head;
      last_element = 0;
      direction = 1;
      break;
    case START_TAIL:
      nd = tail;
      last_element = FElements - 1;
      direction = -1;
      break;
    case START_FORWARDS:
      nd = last_node;
      direction = 1;
      break;
    case START_BACKWARDS:
      nd = last_node;
      direction = -1;
      break;
  }

  if (direction > 0) {
    for (int n = last_element; n < el; n++)
      nd = nd->next;
  }
  else {
    for (int n = last_element; n > el; n--)
      nd = nd->prev;
  }

  last_element = el;
  last_node = nd;

  return nd;
}

// ***********************************************************************
// Adds 'new_element' at index 'el' and returns the index.
int TPointerLinkList::add_ptr (void *new_element, int el)
{
  assert ((el >= 0) && (el <= FElements));

  if (!new_element)
    return -1;

  TNode *prev = el ? node (el - 1) : NULL;
  TNode *next = !prev ? head : prev->next;

  TNode *new_node = new TNode (new_element, prev, next);
  FElements++;

  // Adjust the list pointers
  if (prev)
    prev->next = new_node;
  else
    head = new_node;

  if (next)
    next->prev = new_node;
  else
    tail = new_node;

  // Record the cursor position
  last_element = el;
  last_node = new_node;

  return el;
}

// ***********************************************************************
// Removes the element at index 'el'.
// If the list owns the elements, the element is destroyed.
void TPointerLinkList::remove_ptr (int el)
{
  assert ((el >= 0) && (el < FElements));

  TNode *nd = node (el);

  // Destroy the element
  if (destroy_fn)
    (*destroy_fn) (nd->FElement);

  // Adjust the list pointers
  if (nd->prev)
    nd->prev->next = nd->next;
  else
    head = nd->next;

  if (nd->next)
    nd->next->prev = nd->prev;
  else
    tail = nd->prev;

  // Record the cursor position
  last_node = nd->prev;
  last_element = el - 1;

  delete nd;
  FElements--;
}

// ***********************************************************************
// Removes all the elements.
// If the list owns the elements, the elements are destroyed.
void TPointerLinkList::remove_all_ptrs ()
{
  // Record the cursor position
  last_node = head;
  last_element = 0;

  while (FElements)
    remove_ptr (0);
}

// ***********************************************************************
// Moves the element at index 'el' to index 0 (head).
void TPointerLinkList::move_ptr_to_head (int el)
{
  // Is already head ?
  if (!el)
    return;

  assert ((el >= 1) && (el < FElements));

  // Find node
  TNode *nd = node (el);

  // Unlink from existing place
  nd->prev->next = nd->next;
  if (nd->next)
    nd->next->prev = nd->prev;
  else
    tail = nd->prev;

  // Put at front
  head->prev = nd;
  nd->next = head;
  head = nd;
  nd->prev = NULL;

  // Re-position at head
  last_node = head;
  last_element = 0;
}

// ***********************************************************************
// Returns true if 'key' is found and sets the index 'pos' of the node.
bool TPointerLinkList::find_ptr (const void *key, int &pos)
{
  // Binary search
  int btm = 0, top = FElements - 1;
  while (top - btm >= 2) {
    int half = (top + 1 + btm) / 2;
    const void *elem = node (half)->FElement;

    // Compare FElements
    int cmp = (*cmp_fn) (key, elem);
    if (cmp == 0) {
      pos = half;
      return true;
    }
    if (cmp == 1)
      btm = half;
    else
      top = half;
  }

  // Linear serch
  int found = false;
  while (btm <= top) {
    const void *elem = node (btm)->FElement;

    // Compare FElements
    int cmp = (*cmp_fn) (key, elem);
    if (cmp > 0)
      btm++;
    else {
      if (cmp == 0)
        found = true;
      break;
    }
  }

  pos = btm;
  return found;
}

// ***********************************************************************
// Moves to the start of the list.
// Sets the 'last_node' & 'last_element' cursor members to the head.
void TPointerLinkList::set_to_start ()
{
  // Record the cursor position
  last_element = 0;
  last_node = head;
}

// ***********************************************************************
// Moves to the next element in the list.
void TPointerLinkList::set_to_next ()
{
  // Record the cursor position
  last_element++;
  last_node = last_node->next;
}

// ***********************************************************************
// Moves to the first element.
void *TPointerLinkList::first_ptr (TLinkListIterator &iterator) const
{
  iterator.node = head;
  return iterator.node ? iterator.node->FElement : NULL;
}

// ***********************************************************************
// Moves to the next element.
void *TPointerLinkList::next_ptr (TLinkListIterator &iterator) const
{
  assert (iterator.node != NULL);
  iterator.node = iterator.node->next;
  return iterator.node ? iterator.node->FElement : NULL;
}

// VECTOR

// ***********************************************************************
// Constructs a vector with a starting array size of 'StartSize'.
TPointerVector::TPointerVector(int StartSize)
{
  FStartSize = StartSize ? StartSize : szHysteresis;
  FArraySize = 0;
  FElements = 0;
  destroy_fn = NULL;
}

// ***********************************************************************
// Removes all elements and destroys the object.
// If the vector owns the elements, the elements are destroyed.
TPointerVector::~TPointerVector ()
{
  try {
    remove_all_ptrs ();
  }
  catch(Exception &Error){
    ShowMessage(Error.Message);
  }
}

// ***********************************************************************
// Adds 'new_element' at index 'el' & returns the index.
int TPointerVector::add_ptr (void *new_element, int el)
{
  assert ((el >= 0) && new_element);

  // Array full ?
  if (FElements >= FArraySize) {
    // Resize the array
		int NewArraySize = _max(FStartSize, FArraySize << 1);
    if(FArraySize) {
      FElement = (void**)realloc(FElement, NewArraySize * sizeof (void*));
      if(!FElement)
        throw Exception("Out of memory");
    }
    else
      FElement = new void* [NewArraySize];
    FArraySize = NewArraySize;
  }

  // Move the FElements along
  if (el < FElements)
    memmove (FElement + el + 1, FElement + el, (FElements - el) * sizeof(void *));

  // Insert the element into the hole
  FElement [el] = new_element;
  FElements++;

  return el;
}

// ***********************************************************************
// Removes all elements and destroys the object.
// If the vectorowns the elements, the elements are destroyed.
void TPointerVector::remove_ptr (int el)
{
  assert ((el >= 0) && (el < FElements));

  // Destroy element if own elements
  if (destroy_fn)
    (*destroy_fn) (FElement [el]);

  FElements--;

  // Move top of list down
  if (el < FElements)
    memmove (FElement + el, FElement + el + 1, (FElements - el) * sizeof (void *));

  // Array too big (take hysteresis into account) ?
  if (FElements <= (FArraySize >> 1) - szHysteresis) {
    // Resize the array
    FArraySize = FElements + szHysteresis;
    FElement = (void**)realloc(FElement, FArraySize * sizeof (void*));
    if(!FElement)
      throw Exception("Out of memory");
  }
}

// ***********************************************************************
// Removes all the elements.
// If the vector owns the elements, the elements are destroyed.
void TPointerVector::remove_all_ptrs ()
{
	if (destroy_fn)
	{
		for(int n = 0; n < FElements; n++)
		{
			try
			{
				if (FElement[n] != NULL)
					(*destroy_fn) (FElement [n]);
			}
			catch(...)
			{}
		}
	}

	FArraySize = 0;
	FElements = 0;
	FElement.Destroy();
}

// ***********************************************************************
// Moves the element at index 'from' to index 'To'.
void TPointerVector::MovePtr(int From, int To)
{
  // Is already there ?
  if(From == To)
    return;

  assert((To < FElements) && (From < FElements));

  // Hold node
  void *Temp = FElement[From];

  if(From > To)
    memmove(FElement + To + 1, FElement + To, (From - To) * sizeof (void*));
  else
    memmove(FElement + From, FElement + From + 1, (To - From) * sizeof (void*));

  FElement[To] = Temp;
}

// ***********************************************************************
// Sorts the elements passing 'cmp_fn' to a quicksort function.
void TPointerVector::SortPtrs(fnPtrCompare cmp_fn)
{
  if(FElement)
    qsort (FElement, FElements, sizeof (void*), (fnCompare) cmp_fn);
}

// ***********************************************************************
// Finds 'Key' by passing 'cmp_fn' to a binary search function.
// Returns a pointer to the element or NULL if not found.
// The elements must be sorted.
void *TPointerVector::BinaryFindPtr(void *Key, fnPtrCompare cmp_fn)
{
  return bsearch(&Key, FElement, FElements, sizeof (void*), (fnCompare) cmp_fn);
}

// ***********************************************************************
// Finds 'Key' by passing 'cmp_fn' to a binary search function.
// Returns the element's index or -1 if not found.
// The elements must be sorted.
int TPointerVector::BinaryFindPtrIndex(void *Key, fnPtrCompare cmp_fn)
{
  return LocatePtr(BinaryFindPtr(Key, cmp_fn));
}

// ***********************************************************************
// Finds 'Key' by passing 'cmp_fn' to a linear search function.
// Returns a pointer to the element or NULL if not found.
// The elements need NOT be sorted.
void *TPointerVector::LinearFindPtr(void *Key, fnPtrCompare cmp_fn)
{
  unsigned int Size = FElements;
  return lfind(&Key, FElement, &Size, sizeof (void*), (fnCompare) cmp_fn);
}

// ***********************************************************************
// Finds 'Key' by passing 'cmp_fn' to a linear search function.
// Returns the element's index or -1 if not found.
// The elements need NOT be sorted.
int TPointerVector::LinearFindPtrIndex(void *Key, fnPtrCompare cmp_fn)
{
  return LocatePtr(LinearFindPtr(Key, cmp_fn));
}

// ***********************************************************************
// Returns the index of 'Pointer' or -1 if 'Pointer' is NULL.
// 'Pointer MUST point to an element in the vector.
int TPointerVector::LocatePtr(const void *Pointer) const
{
  return Pointer ? ((void**)Pointer - (void**)FElement) : -1;
}

// ***********************************************************************
// Returns the index of 'Pointer' or -1 if 'Pointer' is not in the vector.
int TPointerVector::GetPtrIndex(const void *ItemPointer) const
{
  for(int Index = 0; Index < Count(); Index++) {
    if(FElement[Index] == ItemPointer)
      return Index;
  }

  return -1;
}


