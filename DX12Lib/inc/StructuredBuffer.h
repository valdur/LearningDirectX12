/**
 * Structured buffer resource.
 */
#pragma once

#include "Buffer.h"

#include "ByteAddressBuffer.h"

class StructuredBuffer : public Buffer
{
public:
    StructuredBuffer( const std::wstring& name = L"" );
    StructuredBuffer( const D3D12_RESOURCE_DESC& resDesc, 
        size_t numElements, size_t elementSize,
        D3D12_RESOURCE_STATES initialState = D3D12_RESOURCE_STATE_COMMON,
        const std::wstring& name = L"");

    /**
    * Get the number of elements contained in this buffer.
    */
    virtual size_t GetNumElements() const
    {
        return m_NumElements;
    }

    /**
    * Get the size in bytes of each element in this buffer.
    */
    virtual size_t GetElementSize() const
    {
        return m_ElementSize;
    }

    /**
     * Create the views for the buffer resource.
     * Used by the CommandList when setting the buffer contents.
     */
    virtual void CreateViews( size_t numElements, size_t elementSize ) override;

    /**
     * Get the SRV for a resource.
     */
    virtual D3D12_CPU_DESCRIPTOR_HANDLE GetShaderResourceView() const
    {
        return m_SRV;
    }

    /**
     * Get the UAV for a (sub)resource.
     */
    virtual D3D12_CPU_DESCRIPTOR_HANDLE GetUnorderedAccessView( uint32_t subresource) const override
    {
        return m_UAV;
    }
    virtual D3D12_CPU_DESCRIPTOR_HANDLE GetUnorderedAccessView(uint32_t mipSlice, uint32_t arraySlice, uint32_t planeSlice) const override
    {
        return m_UAV;
    }


    const ByteAddressBuffer& GetCounterBuffer() const
    {
        return m_CounterBuffer;
    }

private:
    size_t m_NumElements;
    size_t m_ElementSize;

    CD3DX12_CPU_DESCRIPTOR_HANDLE m_SRV;
    CD3DX12_CPU_DESCRIPTOR_HANDLE m_UAV;

    // A buffer to store the internal counter for the structured buffer.
    ByteAddressBuffer m_CounterBuffer;
};