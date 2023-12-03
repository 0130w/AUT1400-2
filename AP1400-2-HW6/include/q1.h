// since C++20, std::cos / std::sin are not addressable functions which means
// you can't pass a function pointer to them to your function
// reference: https://stackoverflow.com/questions/77591644/how-to-write-a-general-version-gradient-descent-algorithm-in-c
#ifndef Q1_H
#define Q1_H
#include <functional>
#include <cmath>

namespace q1 
{
    template <typename T, typename Func>
    T gradient_descent(const T& init_value, const T& step, Func func = Func {}) {
        T value = init_value;
        auto accuracy = step * 1e-3;
        auto gradient = [&func, &accuracy](T& value) { return (func(value) - func(value - accuracy)) / accuracy; };
        while(abs(gradient(value)) > accuracy) {
            value = value - step * gradient(value);
        }
        return value;
    }
    template <typename T>
    T gradient_descent(const T& init_value, const T& step, T func(T)) {
        return gradient_descent<T, T(T)>(init_value, step, func);
    }
};

#endif //Q1_H