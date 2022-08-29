#ifndef RANGED_ITERATOR_H
#define RANGED_ITERATOR_H

#include <type_traits>

/**
 * Requirement:
 * - Type T must support these operators: <, +=, !=
 * - Step size must be specified if T can not be constructed from int
 */

#define DEFAULT_RANGE_STEP 1

template <typename T>
class RangedIterator {
public:
    // https://stackoverflow.com/questions/64697790/sfinae-enable-if-cannot-be-used-to-disable-this-declaration
    template <int..., typename Ty = T, typename std::enable_if<std::is_convertible<int, Ty>::value, bool>::type = true>
    constexpr RangedIterator(T to)
        : m_from(0), m_to(to), m_step(DEFAULT_RANGE_STEP), m_i(1) { }

    template <int..., typename Ty = T, typename std::enable_if<std::is_convertible<int, Ty>::value, bool>::type = true>
    constexpr RangedIterator(T from, T to)
        : m_from(from), m_to(to), m_step(DEFAULT_RANGE_STEP), m_i(from) { }

    constexpr RangedIterator(T from, T to, T step)
        : m_from(from), m_to(to), m_step(step), m_i(from) { }

    constexpr RangedIterator<T>& step(T step) {
        m_step = step;
        return *this;
    }

    constexpr RangedIterator<T> begin() const {
        return RangedIterator<T>(m_from, m_to, m_step);
    }

    constexpr RangedIterator<T> end() const {
        RangedIterator<T> iter(m_from, m_to, m_step);
        iter.m_i = m_to;
        return iter;
    }

    constexpr bool operator!= (const RangedIterator<T>& rhs) const {
        if (m_i == rhs.m_i)
            return false;
        // since we allow arbitrary step, we must check i is actual in range or not
        // if we only checks for differentness, it can cause infinite loop (stepped to far from the end iterator)
        if (m_i < std::min(m_from, m_to) || std::max(m_from, m_to) < m_i)
            return false;
        return true;
    }

    constexpr const RangedIterator<T>& operator++() {
        if (m_from < m_to)
            m_i += m_step;
        else
            m_i -= m_step;
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
