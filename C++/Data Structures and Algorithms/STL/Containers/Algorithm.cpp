#include "Algorithm.h"

#include <iostream>     // cout

#include <vector>
#include <list>
#include <map>
#include <algorithm>    // sort, find, count, copy, unique_copy, replace, back_inserter

using namespace std;

//------------------------------------------------------------------------------
bool descending (int i,int j) { 
    return (i > j); 
}
bool ascending (int i,int j) { 
    return (i < j); 
}
//------------------------------------------------------------------------------
// short versions of sort
template<typename T>
void sort(T& t){
    sort(t.begin(), t.end());
}
template<typename T, typename P>
void sort(T& t, P p){
    sort(t.begin(), t.end(), p);
}
//------------------------------------------------------------------------------
void test_Algorithm_sort(){
    
    vector<int> v = {5,3,2,4,1};   
    sort(v, descending);
    
    for(auto e : v)
        cout << e << ", ";

    cout << endl;
}
//------------------------------------------------------------------------------
template<typename T, typename V>
bool contains(const T& t, V e){
    return find(t.begin(), t.end(), e) != t.end();                              // t.end() indicates not found
}
//------------------------------------------------------------------------------
/*
 * Function Object (Functor)
 */
struct GreaterThen{
    int val;
    GreaterThen(int v) : val{v}{}
    bool operator()(const pair<string, int>& r) { return r.second > val; }
};
//------------------------------------------------------------------------------
void printElementInMap(map<string, int>& my_map){
//    auto p = find_if(my_map.begin(), my_map.end(), GreaterThen{42});            // Functor
    auto p = find_if(my_map.begin(), my_map.end(), 
                     [](const pair<string, int>&r){ return r.second > 42; });   // lambda expression
    
    cout << "First element with value greater 42: " << p->second << endl;                     
}
//------------------------------------------------------------------------------
void test_Algorithm_predicate()
{ 
    map<string, int> my_map;
    my_map["a"] = 1;
    my_map["b"] = 2;
    my_map["c"] = 42;
    my_map["d"] = 43;
    my_map["e"] = 44;
    printElementInMap(my_map);     
}
//------------------------------------------------------------------------------
void test_Algorithm_contains(){
    
    string s = {"This is my string"};
    cout << "String \""<< s << "\" contains char: " << contains(s, 'i') << endl;
    cout << "String \""<< s << "\" contains char: " << contains(s, 'q') << endl;
    
    list<int> l = {1,2,3,4};
    cout << "List contains int: " << contains(l, 3) << endl;
    cout << "List contains int: " << contains(l, 10) << endl;          
}
//------------------------------------------------------------------------------
bool test_Algorithm(){
    
    //test_Algorithm_contains(result_local);
    //(test_Algorithm_sort(result_local);
    test_Algorithm_predicate();
    
    return true;
}
