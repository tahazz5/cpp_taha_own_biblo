#pragma once

#include <cstddef>
#include <utility>

template <typename T>
class mylist {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
        Node(T&& d) : data(std::move(d)), prev(nullptr), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

public:
    mylist() : head_(nullptr), tail_(nullptr), size_(0) {}

    ~mylist() {
        clear();
    }

    mylist(const mylist& other) : head_(nullptr), tail_(nullptr), size_(0) {
        for (Node* n = other.head_; n; n = n->next) {
            push_back(n->data);
        }
    }

    mylist(mylist&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    mylist& operator=(const mylist& other) {
        if (this != &other) {
            clear();
            for (Node* n = other.head_; n; n = n->next) {
                push_back(n->data);
            }
        }
        return *this;
    }

    mylist& operator=(mylist&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (!tail_) {
            head_ = tail_ = new_node;
        } else {
            tail_->next = new_node;
            new_node->prev = tail_;
            tail_ = new_node;
        }
        ++size_;
    }

    void push_back(T&& value) {
        Node* new_node = new Node(std::move(value));
        if (!tail_) {
            head_ = tail_ = new_node;
        } else {
            tail_->next = new_node;
            new_node->prev = tail_;
            tail_ = new_node;
        }
        ++size_;
    }

    void push_front(const T& value) {
        Node* new_node = new Node(value);
        if (!head_) {
            head_ = tail_ = new_node;
        } else {
            new_node->next = head_;
            head_->prev = new_node;
            head_ = new_node;
        }
        ++size_;
    }

    void push_front(T&& value) {
        Node* new_node = new Node(std::move(value));
        if (!head_) {
            head_ = tail_ = new_node;
        } else {
            new_node->next = head_;
            head_->prev = new_node;
            head_ = new_node;
        }
        ++size_;
    }

    void pop_back() {
        if (!tail_) return;
        Node* temp = tail_;
        if (head_ == tail_) {
            head_ = tail_ = nullptr;
        } else {
            tail_ = tail_->prev;
            tail_->next = nullptr;
        }
        delete temp;
        --size_;
    }

    void pop_front() {
        if (!head_) return;
        Node* temp = head_;
        if (head_ == tail_) {
            head_ = tail_ = nullptr;
        } else {
            head_ = head_->next;
            head_->prev = nullptr;
        }
        delete temp;
        --size_;
    }

    T& front() {
        return head_->data;
    }

    const T& front() const {
        return head_->data;
    }

    T& back() {
        return tail_->data;
    }

    const T& back() const {
        return tail_->data;
    }

    std::size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void clear() {
        while (head_) {
            Node* temp = head_;
            head_ = head_->next;
            delete temp;
        }
        tail_ = nullptr;
        size_ = 0;
    }

    template <typename... Args>
    void emplace_back(Args&&... args) {
        push_back(T(std::forward<Args>(args)...));
    }

    template <typename... Args>
    void emplace_front(Args&&... args) {
        push_front(T(std::forward<Args>(args)...));
    }
};