/* License: MIT. See LICENSE in root directory. */

/**
 * \date 2020/07/01
 */

#include <ensemble/raw-memory.hpp>
using Ensemble::RawMemory;

int main()
{
    int sample[100];

    memset32(sample, 47, sizeof(sample) / sizeof(*sample) - 10);

    for (int i = 0; i < sizeof(sample) / sizeof(*sample); ++i)
    {
        printf("%d\n", sample[i]);
    }

    int other[sizeof(sample) / sizeof(*sample)];

    memcpy(other, sample, sizeof(sample) / sizeof(*sample));
}
