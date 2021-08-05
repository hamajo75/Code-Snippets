#include <iostream>
#include <string.h>
#include <set>
#include <unordered_set>
#include <vector>
#include <memory>

//-------------------------------------------------------------------------------
void OwnerBasedComparison() {
  int * p = new int (10);

  std::shared_ptr<int> a(new int (20));
  std::shared_ptr<int> b(a, p);  // alias constructor: co-owns a, points to p

  // standard set container: cannot contain duplicates.
  std::set < std::shared_ptr<int> > value_based;  // uses std::less
  std::set < std::weak_ptr<int>, std::owner_less<std::weak_ptr<int>> > owner_based;

  value_based.insert(a);
  value_based.insert(b);  // ok, different value

  owner_based.insert(a);
  owner_based.insert(b);  // overwrites (same owned pointer)

  std::cout << "value_based.size() is " << value_based.size() << '\n';
  std::cout << "owner_based.size() is " << owner_based.size() << '\n';

  delete p;
}
//-------------------------------------------------------------------------------
void SetOfWeakPointers() {
  // std::set < std::weak_ptr<int>, std::owner_less<std::weak_ptr<int>> > my_set;
  std::unordered_set< std::weak_ptr<int>, std::owner_less<std::weak_ptr<int>> > my_set;
  auto shared_ptr {std::make_shared<int>(1)};

  // std::weak_ptr<int> w = shared_ptr;

  my_set.insert(shared_ptr);
}
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[]) {
  std::set<int>  mySet{5, 6, 2, 1, 1, 1};

  std::cout << "Size of set: " << mySet.size() << "\n";

  mySet.insert(0);
  mySet.insert(0);  // it won't be inserted again
  // mySet[0]; this doesn't work

  auto it = mySet.begin();  // get an iterator
  it++;
  std::cout << *it << "\n";

  mySet.erase(0);

  // erase the last two elements
  it = mySet.end();
  std::advance(it, -2);
  mySet.erase(it, mySet.end());

  int array[] = {8, 9, 10};
  mySet.insert(array, array + 3);

  // sorted output
  for (int i : mySet)
    std::cout << i << "\n";

  auto it2 = mySet.find(1);
  if (it2 != mySet.end())
    std::cout << "Found element: " << *it2 << "\n";

  OwnerBasedComparison();

  return 0;
}




