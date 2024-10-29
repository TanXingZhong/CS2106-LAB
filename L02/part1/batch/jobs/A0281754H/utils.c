#include <unistd.h>
#include "utils.h"

int sum(int sum_array[], int n) {
    int i, res = 0;

    for(i=0; i<n; i++)
        res += sum_array[i];

    usleep(1800000);
    return res;
}
