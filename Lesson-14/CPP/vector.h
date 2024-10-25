#pragma once

#include <new>

template <typename T>
class Vector
{
private:
    T* data;
    size_t sz;// placment new
    size_t cp; // operator new

    static T* Allocate(size_t n)
    {
        return static_cast<T*>(operator new(n * sizeof(T)));
    }

    static void Deallocate(T* buf)
    {
        operator delete(buf);
    }

    static void Construct(void * buf)
    {
        new (buf) T();
    }

    static void Construct(void * buf, const T& elem)
    {
        new (buf) T(elem);
    }

    static void Construct(void * buf, const T&& elem)
    {
        new (buf) T(std::move(elem));
    } 

    static void Destroy(T* buf)
    {
        buf->~T();
    }



public:

    explicit Vector(size_t n = 0)
    {
        data = Allocate(n);

        for(size_t i = 0; i != n; ++i)
        {
            Construct(data + i);
        }

        sz = cp = n;
    }

    Vector(const Vector& other)
    {
        data = Allocate(other.Size());

        for(size_t i = 0; i != other.Size(); ++i)
        {
            Construct(data + i, other[i]);
        }

        sz = cp = other.Size();
    }

    ~Vector();

    void Reserve(size_t n);


    size_t Size() const noexcept
    {
        return sz;
    }

    size_t Capacity() const noexcept
    {
        return cp;
    }

    const T& operator[](size_t i) const
    {
        return data[i];
    }
};