/* License: MIT. See LICENSE in root directory. */

/**
 * \date 2020/07/01
 */

#pragma once

#include <vector>
#include <memory>

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef memset32

// This function is a 32-bit assignment operation similar to standard memset() function.
void memset32(void* pBuffer, int nValue, int nCount)
{
    int* pData = (int*)pBuffer;
    for (int i = 0; i < nCount; ++i)
    {
        *pData++ = nValue;
    }
}

#define memset32(pBuffer, nValue, nCount) \
    memset32((pBuffer), (nValue), (nCount))

#endif

namespace Ensemble
{

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void Construct(T pObject);

template<typename T>
void Destroy(T pObject);

////////////////////////////////////////////////////////////////////////////////////////////////////

class RawMemory
{
public:

    template<typename T1, typename T2, typename T3>
    void Set(T1* pObject, T3 fill);

    template<typename T1 = int, typename T2 = int>
    void Copy(T1* pObject, T2 const* pOther);
};

// todo: fix memory copy replaced by RawMemory template method
#ifndef memcpy
#define memcpy(buffer, data, length) \
    ((RawMemory*)(buffer))->Copy((data), (length));
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////

class RawMemoryResource
{
public:

    using mem_t = std::vector<uchar, std::allocator<uchar>>;

protected:

    uint m_RefCount = 0;

    mem_t mMemory;

public:

    RawMemoryResource() = default;

    ~RawMemoryResource();

public:

    std::shared_ptr<RawMemoryResource>* Create(mem_t&& memory);

    std::shared_ptr<RawMemoryResource>* Create(uint numBytes);

    void ReleaseHandle();

    void AddHandle();

    uchar* GetMemory();

    int GetNumBytes();
};

////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace Ensemble
