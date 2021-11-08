/* Code Snippet: Data Structures/STL Structures/std::set */
// everything in here will be inserted in "Code Snippets.org::Data Structures/STL Structures/std::set"
/* Code Snippet End*/

#include "Container.h"
#include <iostream>
#include <iterator>
#include <string>

#include <set>
#include <map>
#include <stack>
#include <queue>

#include <deque>

using namespace std;

//------------------------------------------------------------------------------
bool isEven(const int& val)
{
    return (val % 2) == 0;
}
//------------------------------------------------------------------------------
void test_set(bool& result)
{
    // set
    set<int> my_set {5,4,1,1};                                                     // 2nd "1" will be removed
    cout << "Size: " << my_set.size() << endl;
    
    my_set.insert(0);
        
    // get values out
    set<int>::iterator it = my_set.begin();
    cout << *it << endl;
    
    my_set.erase(5);
    my_set.erase(it, my_set.end());
    
    int array[] = {5,6,7};
    my_set.insert(array, array + 3);
    
    auto val = my_set.find(6);
    cout << "Found: " << *val << endl;
    
    if (!my_set.empty())
    {
        for(auto i : my_set)
            cout << i << endl;
    }
}
//------------------------------------------------------------------------------
void test_multiset(bool& result)
{
    multiset<int> mset {1,1,2,3,4,5};
 
    mset.insert(6);
    mset.insert(0);
    
    if (!mset.empty())
    {
        for(auto i : mset)
            cout << i << endl;                                                  // it is sorted
    }
}
//------------------------------------------------------------------------------
void test_maps(bool& result)
{
    // no duplicate keys
    map<int, string> my_map;
    
    my_map.insert(pair <int, string> (1, "Bart"));
    my_map.insert(pair <int, string> (2, "Lisa"));
    my_map.insert(pair <int, string> (3, "Marge"));
    my_map.insert(pair <int, string> (4, "Homer"));
    
    map<int, string>::iterator it;
    
    for(it = my_map.begin(); it != my_map.end(); ++it)
    {
        cout << "Key: " << it->first << endl;
        cout << "Value: " << it->second << endl;
    }
}
//------------------------------------------------------------------------------
/*
 * Associative Container: stores sorted data - fast to find, slow to insert
 */
bool test_Container_Associative_Containers()
{
    bool result = true;
    
    //test_set(result);
    //test_multiset(result); 
    test_maps(result);

    return true;
}
//------------------------------------------------------------------------------
/*
 * Sequence Container: not sorted - fast to insert, slow to find
 */
bool test_Container_Sequence_Containers()
{
    // insert front and back
    deque<int> deq1;
    
    deq1.push_back(2);
    deq1.push_front(1);
    deq1.assign({11,12});   // overwrites the rest
    
    // subscript works
    cout << "Element 0: " << deq1[0] << endl;
    cout << "Element 0: " << deq1.at(0) << endl;
    
    // insert, iterator
    deque<int>::iterator it = deq1.begin();
    deq1.insert(it + 2, 3);
    deq1.insert(it + 3, 4);
    deq1.insert(it + 4, 5);
    deq1.insert(it + 10, 6);    // this is strange
    
    int array[] = {6, 7, 8, 9};
    
    deq1.insert(deq1.begin(), array, array + 4);
    
    cout << "Size: " << deq1.size() << endl;
    
    for (int i : deq1)
        cout << i << endl;  
    
    return true;
}