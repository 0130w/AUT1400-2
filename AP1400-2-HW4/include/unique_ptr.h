#ifndef UNIQUE_PTR
#define UNIQUE_PTR
#include <utility>

template <class T>
class UniquePtr {
    public:
        UniquePtr(T* object = nullptr) : _p(std::move(object)) {}
        ~UniquePtr() { if(!_p) { delete _p; _p = nullptr; } }
        UniquePtr(const UniquePtr&) = delete;
        UniquePtr& operator=(const UniquePtr&) = delete;

        T* get() { return _p; }
        T operator*() {if(_p) { return *_p; } else { throw std::runtime_error("cannot dereference a nullptr"); } }
        T* operator->() { return _p; }
        void reset() { if(_p) { delete _p; _p = nullptr; }}
        void reset(T* object) { if(_p) { delete _p; } _p = object; }
        T* release() { T* temp = _p; _p = nullptr; return temp; }
        explicit operator bool() { return _p != nullptr; }
    private:
        T* _p;
};

template <class T, typename... Args>
UniquePtr<T> make_unique(Args&& ... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif //UNIQUE_PTR