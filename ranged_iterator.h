#ifndef RANGED_ITERATOR_H
#define RANGED_ITERATOR_H

#include <type_traits>
#include <cmath>

/**
 * Requirement:
 * - Type T must support these operators: <, +=, !=
 * - Step size must be specified if T can not be constructed from int
 */

#define DEFAULT_RANGE_STEP 1

/** Bidirectional: allowing both counting up and down
 *  I intended to create 2 aliases (range & brange) but alias template deduction is only availble since C++20 :(
 */

template <typename T, bool Bidirectional = true>
class range {
public:
    // https://stackoverflow.com/questions/64697790/sfinae-enable-if-cannot-be-used-to-disable-this-declaration
    template <int..., typename Ty = T, typename std::enable_if<std::is_convertible<int, Ty>::value, bool>::type = true>
    constexpr range(T to)
        : m_from(0), m_to(to), m_step(DEFAULT_RANGE_STEP), m_i(1) { }

    template <int..., typename Ty = T, typename std::enable_if<std::is_convertible<int, Ty>::value, bool>::type = true>
    constexpr range(T from, T to)
        : m_from(from), m_to(to), m_step(DEFAULT_RANGE_STEP), m_i(from) { }

    constexpr range(T from, T to, T step)
        : m_from(from), m_to(to), m_step(step), m_i(from) { }

    constexpr range<T>& step(T step) {
        m_step = step;
        return *this;
    }

    constexpr range<T> begin() const {
        return range<T>(m_from, m_to, m_step);
    }

    constexpr range<T> end() const {
        range<T> iter(m_from, m_to, m_step);
        iter.m_i = m_to;
        return iter;
    }

    constexpr bool operator!= (const range<T>& rhs) const {
        if (m_i == rhs.m_i)
            return false;

        // don't count down
        if (m_step < 0 || m_to < m_from)
            return false;

        // since we allow arbitrary step, we must check i is actual in range or not
        // if we only checks for the differences, it can cause infinite loop (stepped to far from the end iterator)
        if (m_i < m_from || m_to < m_i)
            return false;
        return true;
    }

    constexpr const range<T>& operator++() {
        m_i += m_step;
        return *this;
    }

    constexpr const T& operator* () const {
        return m_i;
    }

private:
    const T m_from, m_to;
    T m_step, m_i;
};

#endif // RANGED_ITERATOR_H
