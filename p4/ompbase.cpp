#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

int main (void)
{
    string thread_names[] =
            {"Bill", "John", "Mark", "William", "BMW", "Otto", "Ambulance", "Monkey", "Carrot", "Pie"};
    #pragma omp parallel
    {
        int i = omp_get_thread_num();
        cout << "\nHello from " << thread_names[i];
    }

return 0;
}
