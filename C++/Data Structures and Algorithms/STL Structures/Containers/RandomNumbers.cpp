// Code Snippet Begin
#include<iostream>

#include<random>

//------------------------------------------------------------------------------
template<Typename T>
class RandomInteger
{    
public:
    RandomInteger(int low, int high) : Low(low), High(high), UniformDistribution{low, high}{}
    
    
    int operator()(){ return UniformDistribution(RandomEngine); }         
    
    int getLow(){ return Low; }
    int getHigh(){ return High; }
private:
    int Low, High;
    std::default_random_engine RandomEngine;
    std::uniform_int_distribution<> UniformDistribution;
    std::normal_distribution<> NormalDistribution{5,2};
};
//------------------------------------------------------------------------------
int rollTheDie()
{
    std::default_random_engine random_engine;
    std::uniform_int_distribution<> distribution{1,6};

    return distribution(random_engine);
}
//------------------------------------------------------------------------------
void printDistribution(RandomInteger &rng)
{
    int nr_of_samples = 200;
    std::vector<int> histogram(rng.getHigh() - rng.getLow() + 1);
    
    for (int i = 0; i != nr_of_samples; ++i)
        ++histogram[rng() - rng.getLow()];
    
    for (int i = 0; i != histogram.size(); ++i)
    {
        std::cout << i << "\t";
        for (int j = 0; j!=histogram[i]; ++j)
            std::cout << "*";
        std::cout << "\n";
    }
}
//------------------------------------------------------------------------------
bool test_RandomNumbers()
{
    RandomInteger rng{1,10};
    
    for (int i = 0; i < 10; i++)
        std::cout << "random integer: " << rng() << "\n";
    
    for (int i = 0; i < 10; i++)
        std::cout << "random integer: " << rng() << "\n";
    
    printDistribution(rng);
    
    return true;
}
// Code Snippet End