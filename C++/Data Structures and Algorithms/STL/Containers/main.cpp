#include <iostream>
#include <string.h>

#include "Container.h"
#include "Algorithm.h"
#include "RandomNumbers.h"
#include "Utilities.h"
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
    test_Utilities();
    test_Algorithm();

    test_Container_Associative_Containers();
    test_Container_Sequence_Containers();

    test_RandomNumbers();
    
    return 0;
}




