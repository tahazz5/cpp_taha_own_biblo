#pragma once
#include<iostream>
template<typename T>

class uniquepointer{
    private:
    T *m_ptr=nullptr;
    public:
    uniquepointer()=default ;
    uniquepointer(T*ptr):m_ptr(ptr){
    }
    uniquepointer(const uniquepointer& other)= delete ;
    uniquepointer& operator=(const uniquepointer& other) = delete ;
    
    uniquepointer& operator=(uniquepointer&& other)noexcept {
        if(this!=&other){
            this->m_ptr=other.m_ptr;
            other.m_ptr=nullptr; 
            return *this;
        }
        return *this ;
    }
    uniquepointer(uniquepointer&& other)noexcept {
        this->m_ptr=other.m_ptr;
        other.m_ptr=nullptr;
    }
    ~uniquepointer(){
        delete m_ptr;
    }
    T& operator*(){
        return *m_ptr;
    }
    T* operator->(){
        return m_ptr;
    }
    T* get() const {
        return m_ptr;
    }
    T* release(){
        T* m= m_ptr;
         m_ptr= nullptr;
        return m ;

    }
    void reset(T* ptr = nullptr) {
        delete m_ptr;
        m_ptr = nullptr;
        m_ptr = ptr;
    }
    
};


