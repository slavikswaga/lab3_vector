#pragma once
#include <iostream>
#include <utility>

template <typename T>
class Container
{
private:
    T* data_ptr = nullptr;
    size_t sz = 0;
    size_t cap = 0;
public:

    explicit Container(){}
    explicit Container(size_t N){
        data_ptr = new T[N];
        cap = N;
    }

    Container(Container&& other) noexcept{
        this->sz = other.sz;
        this->cap = other.cap;
        this->data_ptr = other.data_ptr;
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
        if(this != &other){
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
        for(size_t i = 0; i < this->sz; ++i){
            temp.data_ptr[i] = this->data_ptr[i];
        }
        temp.swap(std::move(*this));
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

    void swap(Container&& other){
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

    
    //void push_back(const T& value);
    //void erase(size_t index);
    
    //T& operator[](size_t index);
    //const T& operator[](size_t index) const;

   // using iterator = T*;
   // using const_iterator = const T*;

    //iterator begin() {}
    //iterator end() {}
    //const_iterator begin() const {}
    //const_iterator end() const {}
};


