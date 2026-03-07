#pragma once
#include<iostream>
template<typename T>
class shared_pointer{
    private:
    T* m_ptr=nullptr ;
    int* count=nullptr ;
    void release(){
        if(count){
            (*count)--;
            if(*count==0){
                delete m_ptr;
                delete count;
            }
            else{
                m_ptr=nullptr;
                count=nullptr;
            }

        }
    }
    public:
    shared_pointer()=default;
    
    shared_pointer(T* ptr):m_ptr(ptr){
        if(ptr) count= new int(1);
    }
    shared_pointer(const shared_pointer& other){
        m_ptr=other.m_ptr ;
        count=other.count ;
        if(count) (*count)++;
    }
    shared_pointer(shared_pointer&& other) noexcept {
        m_ptr=other.m_ptr ;
        count=other.count ;
        other.m_ptr=nullptr;
        other.count=nullptr ;

        
    }
    shared_pointer& operator=(shared_pointer& other){
        if(this !=&other){
            release();
            this->m_ptr=other.m_ptr;
            this->count=other.count;
            if(count)(*count)++;
        } 
        return *this;
    }
    shared_pointer& operator=(shared_pointer&& other)noexcept {
        if(this !=&other){
            release();
            this->m_ptr=other.m_ptr;
            this->count=other.count;
            other.m_ptr=nullptr;
            other.count=nullptr;

        }
        return *this;
    }
    ~shared_pointer(){
        release();
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

    
};