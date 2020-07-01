/* License: MIT. See LICENSE in root directory. */

/**
 * \date 2020/07/01
 */

#include "../../inc/ensemble/raw-memory.hpp"

namespace Ensemble
{

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void Construct(T pObject)
{
    if (pObject != nullptr)
    {
        pObject();
    }
}

template<typename T>
void Destroy(T pObject)
{
    delete &pObject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T1, typename T2, typename T3>
void RawMemory::Set(T1* pObject, T3 fill)
{
    if (fill > 0)
    {
        memset32(this, 0x1010101 * (T1)pObject, (uint)fill >> 2u);
        memset(&this[4 * ((uint)fill >> 2u)], (T1)pObject, fill & 3);
    }
}

template<typename T1, typename T2>
void RawMemory::Copy(T1* pObject, T2 const* pOther)
{
    auto pMemory = this;
    auto pTempOther = pOther;
    while (pTempOther-- != nullptr)
    {
        pMemory[0] = pMemory[pObject - (T2*)this];
        pMemory++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

RawMemoryResource::~RawMemoryResource()
{
    mMemory.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<RawMemoryResource>* RawMemoryResource::Create(mem_t&& memory)
{
    auto rawMemRes = new RawMemoryResource;
    rawMemRes->mMemory = memory;

    return new std::shared_ptr<RawMemoryResource>(rawMemRes);
}

std::shared_ptr<RawMemoryResource>* RawMemoryResource::Create(uint numBytes)
{
    auto rawMemRes = new RawMemoryResource;
    rawMemRes->mMemory.resize(numBytes);

    return new std::shared_ptr<RawMemoryResource>(rawMemRes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void RawMemoryResource::ReleaseHandle()
{
    m_RefCount--;
}

void RawMemoryResource::AddHandle()
{
    m_RefCount++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

uchar* RawMemoryResource::GetMemory()
{
    if (&mMemory.back() != &mMemory.front())
    {
        return mMemory.data();
    }

    return &mMemory.back() - mMemory.front();
}

int RawMemoryResource::GetNumBytes()
{
    return mMemory.back() - mMemory.front();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace Ensemble
