#pragma once
#include <iostream>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <concepts>
#include <type_traits>
#include <memory>

template <typename T> class VectorConstIterator;
template <typename T> class VectorIterator;

template <typename T>
concept Numeric = (std::integral<T> || std::floating_point<T>)
    && !std::same_as<T, bool>
    && !std::same_as<T, char>
    && !std::same_as<T, wchar_t>
    && !std::same_as<T, char8_t>
    && !std::same_as<T, char16_t>
    && !std::same_as<T, char32_t>;
template<Numeric T>
class Vector
{
private:
    std::unique_ptr<T[]> data_;
    size_t sz = 0;
    size_t cap = 0;
public:

    explicit Vector(){}
    explicit Vector(size_t N) : cap(N) {
        data_ = std::make_unique<T[]>(N);
    }

    Vector(Vector&& other) noexcept :
        data_(std::move(other.data_)),
        cap(other.cap),
        sz(other.sz) 
    {
        other.sz = 0;
        other.cap = 0;
    }
    
    ~Vector() {};
  
    Vector& operator=(Vector&& other) noexcept(std::is_nothrow_move_assignable_v<T>)
    {
        if(this != &other){ // self-assignment guard
            Vector temp(std::move(other));
            temp.swap(*this);
        }
        return *this;
    };
    
    Vector(const Vector&) = delete;
    Vector& operator=(const Vector&) = delete;


    void reserve(size_t N){
        if(N <= this->cap) return;
        Vector temp(N);
        temp.sz = this->sz; 

        for(size_t i = 0; i < this->sz; ++i){
            temp.data_[i] = std::move(this->data_[i]);
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

    void swap(Vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(sz, other.sz);
    std::swap(cap, other.cap);
    }

    
    void push_back(const T& value)
    {
        if(cap <= sz){
            (cap == 0) ? reserve(4) : reserve(cap * 2);
        }
        data_[sz] = value;
        ++sz;
    };

    void pop_back()
    {
        if(empty()){
            return;
        }
        data_[--sz].~T();
    }

    void insert(size_t index, const T& value)
    {
        
        if(index > sz){
            throw std::out_of_range("The index is outside the allowable range");
        }

        if(index == sz){
            push_back(value);
            return;
        }
        if(cap <= sz){
            (cap == 0) ? reserve(4) : reserve(cap * 2);
        }

        T value_copy = value;
        for(size_t i = sz; i > index; --i){
            data_[i] = std::move(data_[i - 1]);
        }
        data_[index] = std::move(value_copy);
        ++sz;
    }

    void erase(size_t index)
    {
        if(index >= sz)
            throw std::out_of_range("The index is outside the allowable range");
        for(size_t i = index; i < (sz - 1); ++i)
        {
            data_[i] = data_[i + 1];
        }
        --sz;
    };
    
    T& operator[](size_t index)
    {
        return data_[index];
    }
    const T& operator[](size_t index) const
    {
        return data_[index];
    }

    T& at(size_t index)
    {
        if(index < sz) return data_[index];
        throw std::out_of_range("The index is outside the allowable range");
    }

    const T& at(size_t index) const
    {
        if(index < sz) return data_[index];
        throw std::out_of_range("The index is outside the allowable range");
    }

    using iterator = VectorIterator<T>;
    using const_iterator = VectorConstIterator<T>;

    iterator begin() {
        return iterator(data_.get());
    }
    iterator end() {
        return iterator(data_.get() + sz);
    }
    const_iterator cbegin() const {
        return const_iterator(data_.get());
    }
    const_iterator cend() const {
        return const_iterator(data_.get() + sz);
    }
};


template <typename T>
class VectorIterator
{
    private:
    T* ptr_;
    public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using iterator_category =
    std::random_access_iterator_tag;

    friend class VectorConstIterator<T>;

    explicit VectorIterator(T* ptr) :
        ptr_(ptr) {}

    VectorIterator& operator++(){
        ++ptr_;
        return *this;
    }

    VectorIterator& operator+=(difference_type n){
        ptr_ += n;
        return *this;
    }

    VectorIterator& operator-=(difference_type n){
        ptr_ -= n;
        return *this;
    }

    VectorIterator operator++(int){
        VectorIterator iterator = *this;
        ptr_++;
        return iterator;
    }

    VectorIterator& operator--(){
        ptr_--;
        return *this;
    }

    VectorIterator operator--(int){
        VectorIterator iterator = *this;
        ptr_--;
        return iterator;
    }

    VectorIterator operator+(difference_type n) const{
        return VectorIterator(ptr_ + n);
    }

    VectorIterator operator-(difference_type n) const{
        return VectorIterator(ptr_ - n);
    }

    reference operator*() const{
        return *ptr_;
    }

    pointer operator->() const{
        return ptr_;
    }

    reference operator[](size_t index) const{
        return *(ptr_ + index);
    }

    bool operator==(const VectorIterator& other) const{
        return ptr_ == other.ptr_;
    }

    bool operator!=(const VectorIterator& other) const{
        return ptr_ != other.ptr_;
    }

    bool operator<(const VectorIterator& other) const{
        return ptr_ < other.ptr_;
    }

    bool operator>(const VectorIterator& other) const{
        return ptr_ > other.ptr_;
    }

    bool operator<=(const VectorIterator& other) const{
        return ptr_ <= other.ptr_;
    }

    bool operator>=(const VectorIterator& other) const{
        return ptr_ >= other.ptr_;
    }

    difference_type operator-(const VectorIterator& other) const{
        return ptr_ - other.ptr_;
    }
};

template <typename T>
class VectorConstIterator
{
    private:
    const T* ptr_;
    public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;
    using iterator_category =
    std::random_access_iterator_tag;

    friend class VectorIterator<T>;

    explicit VectorConstIterator(const T* ptr) :
        ptr_(ptr) {}

    VectorConstIterator& operator++(){
        ptr_++;
        return *this;
    }

    VectorConstIterator operator++(int){
        VectorConstIterator iterator = *this;
        ptr_++;
        return iterator;
    }

    VectorConstIterator& operator--(){
        ptr_--;
        return *this;
    }

    VectorConstIterator operator--(int){
        VectorConstIterator iterator = *this;
        ptr_--;
        return iterator;
    }

    VectorConstIterator& operator+=(difference_type n){
        ptr_ += n;
        return *this;
    }

    VectorConstIterator& operator-=(difference_type n){
        ptr_ -= n;
        return *this;
    }

    VectorConstIterator operator+(difference_type n){
        return VectorConstIterator(ptr_ + n);
    }

    VectorConstIterator operator-(difference_type n){
        return VectorConstIterator(ptr_ - n);
    }

    reference operator*() const{
        return *ptr_;
    }

    pointer operator->() const{
        return ptr_;
    }

    reference operator[](size_t index) const{
        return *(ptr_ + index);
    }

    bool operator==(const VectorConstIterator& other) const{
        return ptr_ == other.ptr_;
    }

    bool operator!=(const VectorConstIterator& other) const{
        return ptr_ != other.ptr_;
    }

    bool operator<(const VectorConstIterator& other) const{
        return ptr_ < other.ptr_;
    }

    bool operator>(const VectorConstIterator& other) const{
        return ptr_ > other.ptr_;
    }

    bool operator<=(const VectorConstIterator& other) const{
        return ptr_ <= other.ptr_;
    }

    bool operator>=(const VectorConstIterator& other) const{
        return ptr_ >= other.ptr_;
    }


    difference_type operator-(const VectorConstIterator& other) const{
        return ptr_ - other.ptr_;
    }
};



