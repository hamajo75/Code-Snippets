#include <iostream>
#include <vector>

using namespace std;

struct point_t
{
    int row;
    int col;
};

typedef vector<point_t>  river_t;

vector<river_t> rivers;
//----------------------------------------------------------
void belongsTo(vector<river_t> &rivers, const point_t p)
{
    for(auto &r: rivers)
    {
        for(auto pr: r)
        {
            if ((p.col == pr.col && pr.row == p.row - 1) ||
                (p.row == pr.row && pr.col == p.col - 1))
            {
                r.push_back(p);
                return;
            }
        }
    }

    river_t rv {p};
    rivers.push_back(rv);
}
//----------------------------------------------------------
vector<int> riverSizes(const vector<vector<int>> matrix) 
{  
    for(int row = 0; row < matrix.size(); row++)
        for(int col = 0; col < matrix[row].size(); col++)
            if(matrix[row][col])
            {
                belongsTo(rivers, point_t {row, col});        
            }
    
    vector<int> sizes;
    for(auto r: rivers)
    sizes.push_back(r.size());

    return sizes;
}
//----------------------------------------------------------
int main()
{
    vector<vector<int>> matrix = 
    {
        {1,0,0,1,0},
        {1,0,1,0,0},
        {0,0,1,0,1},
        {1,0,1,0,1},
        {1,0,1,1,0},
        {1,0,1,1,0}
    };
    
    vector<int> sizes = riverSizes(matrix);    

    cout << sizes.size() << endl;

  for(auto s: sizes)
    cout << s << endl;
   
   system("pause"); 
}
