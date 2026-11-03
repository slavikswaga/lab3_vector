#pragma once
#include <iostream>
#include <utility>
#include <stdexcept>

template <typename T>
class Container
{
private:
    T* data_ptr = nullptr;
    size_t sz = 0;
    size_t cap = 0;
public:

    explicit Container(){}
    explicit Container(size_t N) :
        data_ptr(new T[N]),
        cap(N), {}

    Container(Container&& other) noexcept :
        sz(other.sz),
        cap(other.cap),
        data_ptr(other.data_ptr) 
    {
        other.data_ptr = nullptr;
        other.sz = 0;
        other.cap = 0;
    }
    
    ~Container()
    {
        delete[] data_ptr;
    };
  
    Container& operator=(Container&& other) noexcept(std::is_nothrow_move_assignable_v<T>)
    {
        if(this != &other){ // self-assignment guard
            Container temp(std::move(other));
            temp.swap(*this);
        }
        return *this;
    };
    
    Container(const Container&) = delete;
    Container& operator=(const Container&) = delete;


    void reserve(size_t N){
        if(N <= this->cap) return;
        Container temp(N);
        temp.sz = this->sz; 

        for(size_t i = 0; i < this->sz; ++i){
            temp.data_ptr[i] = this->data_ptr[i];
        }
        temp.swap(*this);
    }

    size_t size() const{
        return sz;
    };
    size_t capacity() const{
        return cap;
    }
    bool empty() const{
        return sz == 0;
    };

    void swap(Container& other){
        T* temp_data_ptr = other.data_ptr;
        other.data_ptr = this->data_ptr;
        this->data_ptr = temp_data_ptr;

        size_t temp_sz = other.sz;
        other.sz = this->sz;
        this->sz = temp_sz;

        size_t temp_cap = other.cap;
        other.cap = this->cap;
        this->cap = temp_cap;
    }

    
    void push_back(const T& value)
    {
        if(cap <= sz){
            (cap == 0) ? reserve(4) : reserve(cap * 2);
        }
        *(data_ptr +sz) = value;
        ++sz;
    };

    void erase(size_t index)
    {
        if(index >= sz)
            throw std::out_of_range("The index is outside the allowable range");
        for(size_t i = index; i < (sz - 1); ++i)
        {
            *(data_ptr + i) = *(data_ptr + i + 1);
        }
        --sz;
    };
    
    T& operator[](size_t index)
    {
        return data_ptr[index];
    }
    const T& operator[](size_t index) const
    {
        return data_ptr[index];
    }

    T& at(size_t index)
    {
        if(index < sz) return data_ptr[index];
        throw std::out_of_range("The index is outside the allowable range");
    }

    const T& at(size_t index) const
    {
        if(index < sz) return data_ptr[index];
        throw std::out_of_range("The index is outside the allowable range");
    }

   using iterator = T*;
   using const_iterator = const T*;

    //iterator begin() {}
    //iterator end() {}
    //const_iterator begin() const {}
    //const_iterator end() const {}
};


