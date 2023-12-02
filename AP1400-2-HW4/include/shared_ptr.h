#ifndef SHARED_PTR
#define SHARED_PTR
#include <utility>

template <class T>
class SharedPtr {
    public:
        SharedPtr(T* object = nullptr) : _p(object) {
            if(!count) { count = new size_t(1); }
        }
        ~SharedPtr() {
            if(count) {
                (*count)--;
                if(*count == 0 && _p) {
                    delete count; delete _p;
                }
                count = nullptr, _p = nullptr;
            }
        }
        SharedPtr(const SharedPtr& other) : _p(other._p), count(other.count) { (*count)++; }
        SharedPtr& operator=(const SharedPtr& other) {
            if(&other != this) {
                _p = other._p;
                count = other.count;
                (*count)++;
            }
            return *this;
        }
        size_t use_count() { return count ? *count : 0; }
        T* get() { return _p; }
        T operator*() { if(_p) { return *_p; } else { throw std::runtime_error("cannot dereference a nullptr."); }}
        T* operator->() { return _p; }
        void reset() {
            if(count) {
                (*count)--;
                if(*count == 0 && _p) { delete count; delete _p; }
                count = nullptr, _p = nullptr;
            }
        }
        void reset(T* object) {
           if(count) {
                (*count)--;
                if(*count == 0 && _p) { delete count; delete _p; }
           }
           _p = object; count = new size_t(1);
        }
        explicit operator bool() const { return _p != nullptr; }
    private:
        T* _p = nullptr;
        size_t* count = nullptr;
};

template <class T, typename... Args>
SharedPtr<T> make_shared(Args&&... args) {
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

#endif //SHARED_PTR