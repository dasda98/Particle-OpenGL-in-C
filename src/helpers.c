#include <helpers.h>
#include <stdlib.h>


float randomFloat(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}
