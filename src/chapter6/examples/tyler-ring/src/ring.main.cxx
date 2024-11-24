/// Author: Tyler Swann (tyler.swann05@gmail.com)
/// 
/// Version: v0.1.0
///
/// Date: 22-01-2023
///
/// Copyright: Copyright (c) 2023
/// \file ring.main.cxx
///
/// \godbolt https://www.godbolt.org/z/4qqr7PxYh


#include <algorithm>
#include <iostream>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <numeric>
#include <ranges>
#include <type_traits>
#include <utility>

template<typename Iterator>
class ring_iterator
{
public:
    using iterator_type     = Iterator;
    using iterator_category = std::random_access_iterator_tag;
    using iterator_concept  = std::random_access_iterator_tag;

    using value_type        = std::iter_value_t<Iterator>;
    using difference_type   = std::iter_difference_t<Iterator>;
    using reference         = std::iter_reference_t<Iterator>;
    using pointer           = value_type*;

protected:
    iterator_type m_base;
    difference_type m_index;
    difference_type m_offset;
    difference_type m_size;

public:
    
    constexpr
    ring_iterator() noexcept
        : m_base{ Iterator{} } { }

    explicit constexpr
    ring_iterator(
        iterator_type data,
        difference_type idx,
        difference_type offset,
        difference_type size
    ) noexcept
        : m_base{ data }
        , m_index{ idx }
        , m_offset{ offset }
        , m_size{ size }
    { }

    template<typename Iter>
        requires std::convertible_to<Iter, Iterator>
    constexpr
    ring_iterator(const ring_iterator<Iter>& other) noexcept
        : m_base{ other.m_base() }
        , m_index{ other.m_index }
        , m_offset{ other.m_offset }
        , m_size{ other.m_size }
    { }

    constexpr
    ring_iterator(const iterator_type& other) noexcept
        : m_base{ other.m_base() }
        , m_index{ other.m_index }
        , m_offset{ other.m_offset }
        , m_size{ other.m_size }
    { }

    constexpr auto
    operator* () noexcept -> reference 
    { return m_base[((m_offset + m_index) % m_size)]; }

    constexpr auto
    operator* () const noexcept -> reference 
    { return m_base[((m_offset + m_index) % m_size)]; }

    constexpr auto
    operator->() noexcept -> pointer
        requires std::is_pointer_v<iterator_type> ||
        requires (const iterator_type i) { i.operator->(); }
    { return _S_to_pointer(m_base); }

    constexpr auto
    operator->() const noexcept -> pointer
        requires std::is_pointer_v<iterator_type> ||
        requires (const iterator_type i) { i.operator->(); }
    { return _S_to_pointer(m_base); }

    constexpr auto
    operator++ () noexcept -> ring_iterator& 
    {
        m_index += 1L;
        return *this;
    }

    constexpr auto
    operator++ (int) noexcept -> ring_iterator 
    {
        auto n_iter = *this;
        n_iter.m_index += 1L;
        return n_iter;
    }

    constexpr auto
    operator-- () noexcept -> ring_iterator& 
    {
         m_index -= 1L;
        return *this;
    }

    constexpr auto
    operator-- (int) noexcept -> ring_iterator 
    {
        auto n_iter = *this;
        n_iter.m_index -= 1L;
        return n_iter;
    }

    constexpr auto
    operator[] (difference_type n) noexcept -> reference 
    { return m_base[((m_offset + m_index + n) % m_size)]; }

    constexpr auto
    operator+= (difference_type step) noexcept
        -> ring_iterator& 
    {
        m_index += step;
        return *this;
    }

    constexpr auto
    operator-= (difference_type step) noexcept
        -> ring_iterator& 
    {
        m_index -= step;
        return *this;
    }

    constexpr auto
    operator+ (difference_type step) const noexcept
        -> ring_iterator 
    {
        auto n_iter = *this;
        n_iter.m_index += step;
        return n_iter;
    }

    constexpr auto
    operator- (difference_type step) const noexcept
        -> ring_iterator 
    {
        auto n_iter = *this;
        n_iter.m_index -= step;
        return n_iter;
    }

    constexpr auto
    base() const noexcept -> iterator_type 
    { return m_base; }

    constexpr auto
    index() const noexcept -> difference_type 
    { return m_index; }

    constexpr auto
    offset() const noexcept -> difference_type 
    { return m_offset; }

    constexpr auto
    size() const noexcept -> difference_type 
    { return m_size; }

private:
    
    template<typename P>
    static constexpr auto
    _S_to_pointer(P* ptr) -> P* {
        return ptr;
    }

    template<typename P>
    static constexpr auto
    _S_to_pointer(P obj) -> pointer {
        return obj.operator->();
    }

};

template<typename IterL, typename IterR>
    requires requires (IterL lhsI, IterR rhsI) 
             {
                { lhsI == rhsI } -> std::convertible_to<bool>;
             }
constexpr auto
operator== (const ring_iterator<IterL>& lhs,
            const ring_iterator<IterR>& rhs) 
    noexcept -> bool 
{ 
    return (
           lhs.base() == rhs.base()
        && lhs.index() == rhs.index()
        && lhs.offset() == rhs.offset()
        && lhs.size() == rhs.size()
    );
}

template<typename IterL, typename IterR>
    requires std::three_way_comparable_with<IterL, IterR, std::weak_ordering>
constexpr auto
operator<=> (const ring_iterator<IterL>& lhs,
             const ring_iterator<IterR>& rhs) 
    noexcept -> std::weak_ordering 
{
    return (
           lhs.base() <=> rhs.base()
        && lhs.index() <=> rhs.index()
        && lhs.offset() <=> rhs.offset()
        && lhs.size() <=> rhs.size()
    );
}


template<typename IterL, typename IterR>
constexpr inline auto
operator- (const ring_iterator<IterL>& lhs,
           const ring_iterator<IterR>& rhs) 
    noexcept -> ring_iterator<typename std::common_type<IterL, IterR>::type>::difference_type
{ return lhs.index() - rhs.index(); }

template<typename Iterator>
constexpr inline auto
operator- (const ring_iterator<Iterator>& lhs,
           const ring_iterator<Iterator>& rhs) 
    noexcept -> ring_iterator<Iterator>::difference_type
{ return lhs.index() - rhs.index(); }

template<typename Iterator>
constexpr inline auto
operator+ (typename ring_iterator<Iterator>::difference_type n,
           const ring_iterator<Iterator>& i) 
    noexcept -> ring_iterator<Iterator> 
{ return ring_iterator<Iterator>(i.base(), n + i.index(), i.offset(), i.size()); }

template<typename T, std::size_t N>
class ring
{
public:

    using size_type                 = std::size_t;
    using difference_type           = std::ptrdiff_t;
    using value_type                = T;
    using pointer                   = value_type*;
    using const_pointer             = const value_type*;
    using reference                 = value_type&;
    using const_reference           = const value_type&;
    using iterator                  = ring_iterator<pointer>;
    using const_iterator            = ring_iterator<const pointer>;
    using reverse_iterator          = std::reverse_iterator<iterator>;
    using const_reverse_iterator    = std::reverse_iterator<const_iterator>;

protected:

    size_type m_write;
    size_type m_read;
    size_type m_size;
    std::unique_ptr<T[]> m_buffer;

public:

    constexpr ring() noexcept
        : m_write{ 0 }
        , m_read{ 0 }
        , m_size{ 0 }
        , m_buffer{ std::make_unique<T[]>(N) }
    { }

    constexpr ring(const ring& other) noexcept
        : m_write{ other.m_write }
        , m_read{ other.m_read }
        , m_size{ other.m_size }
        , m_buffer{ std::make_unique<T[]>(N) }
    { std::copy(other.begin(), other.end(), begin()); }

    constexpr ring(ring&& other) noexcept
        : m_write{ std::move(other.m_write) }
        , m_read{ std::move(other.m_read) }
        , m_size{ std::move(other.m_size) }
        , m_buffer{ std::move(other.m_buffer) }
    {
        other.m_write   = size_type{ 0 };
        other.m_read    = size_type{ 0 };
        other.m_size    = size_type{ 0 };
        other.m_buffer  = std::make_unique<T[]>(N);
    }

    ~ring() noexcept = default;

    [[nodiscard]] constexpr auto
    operator= (const ring& other) noexcept -> ring&
    {
        if (*this != other)
        {
            m_write     = other.m_write;
            m_read      = other.m_read;
            m_size      = other.m_size;
            m_buffer    = std::make_unique<T[]>(*other.m_buffer.get());
        }

        return *this;
    }

    [[nodiscard]] constexpr auto
    operator= (ring&& other) noexcept -> ring&
    {
        if (*this != other)
        {
            m_write     = std::move(other.m_write);
            m_read      = std::move(other.m_read);
            m_size      = std::move(other.m_size);
            m_buffer    = std::move(other.m_buffer);

            other.m_buffer  = std::make_unique<T[]>(N);
            other.m_write   = size_type{ 0 };
            other.m_read    = size_type{ 0 };
            other.m_size    = size_type{ 0 };
        }

        return *this;
    }

    constexpr auto
    data() noexcept -> pointer
    { return m_buffer.get(); }

    constexpr auto
    data() const noexcept -> pointer
    { return m_buffer.get(); }

    constexpr auto
    capacity() noexcept -> size_type
    { return N; }

    constexpr auto
    capacity() const noexcept -> size_type
    { return N; }

    constexpr auto
    size() noexcept -> size_type
    { return m_size; }

    constexpr auto
    size() const noexcept -> size_type
    { return m_size; }

    constexpr auto
    full() noexcept -> bool
    { return m_size == N; }

    constexpr auto
    empty() noexcept -> bool
    { return m_size == 0; }

    constexpr auto
    operator[] (size_type idx) -> reference
    { return _M_index(idx); }

    constexpr auto
    operator[] (size_type idx) const -> const_reference
    { return _M_index(idx); }

    constexpr auto
    at(size_type idx) 
        noexcept( noexcept(_M_range_check(idx)) ) -> reference
    { 
        _M_range_check(idx);
        return _M_index(idx); 
    }

    constexpr auto
    at(size_type idx) 
        const noexcept( noexcept(_M_range_check(idx)) ) -> const_reference
    { return _M_index(idx); }

    constexpr auto
    push_back(const value_type& item) 
        noexcept( noexcept(_M_write(item)) ) -> void
    { _M_write(item); }

    constexpr auto
    push_back(value_type&& item)
        noexcept( noexcept(_M_write(item)) ) -> void
    { _M_write(std::move(item)); }

    constexpr auto
    pop_front()
        noexcept( noexcept(_M_read()) ) -> value_type
    { return _M_read(); }

    constexpr auto
    begin() noexcept -> iterator
    { return iterator(m_buffer.get(), 0L, m_read, N); }

    constexpr auto
    begin() const noexcept -> const_iterator
    { return const_iterator(m_buffer.get(), 0L, m_read, N); }

    constexpr auto
    cbegin() const noexcept -> const_iterator
    { return const_iterator(m_buffer.get(), 0L, m_read, N); }

    constexpr auto
    rbegin() noexcept -> reverse_iterator
    { return reverse_iterator(end()); }

    constexpr auto
    rbegin() const noexcept -> const_reverse_iterator
    { return const_reverse_iterator(cend()); }

    constexpr auto
    crbegin() const noexcept -> const_iterator
    { return const_reverse_iterator(cend()); }

    constexpr auto
    end() noexcept -> iterator
    { return iterator(m_buffer.get(), m_size, m_read, N); }

    constexpr auto
    end() const noexcept -> const_iterator
    { return const_iterator(m_buffer.get(), m_size, m_read, N); }

    constexpr auto
    cend() const noexcept -> const_iterator
    { return const_iterator(m_buffer.get(), m_size, m_read, N); }

    constexpr auto
    rend() noexcept -> reverse_iterator
    { return reverse_iterator(begin()); }

    constexpr auto
    rend() const noexcept -> const_reverse_iterator
    { return const_reverse_iterator(cbegin()); }

    constexpr auto
    crend() const noexcept -> const_iterator
    { return const_reverse_iterator(cbegin()); }

private:

    constexpr auto
    _M_range_check(size_type idx) -> void
    {
        if (idx >= m_size)
            throw std::range_error("Out of bound m_index access");
    }

    constexpr auto
    _M_index(size_type idx) noexcept -> reference
    { return m_buffer[((idx + m_read) % N)]; }

    constexpr auto
    _M_index(size_type idx) const noexcept -> const_reference
    { return m_buffer[((idx + m_read) % N)]; }

    constexpr auto
    _M_write(const value_type& item) -> void
    {
        if (full())
            throw std::runtime_error("Ring Full");

        m_buffer[write] = item;

        m_write = (m_write + 1L) % N;
        m_size += 1L;
    }

    constexpr auto
    _M_write(value_type&& item) -> void
    {
        if (full())
            throw std::runtime_error("Ring Full");

        m_buffer[m_write] = std::move(item);

        m_write = (m_write + 1L) % N;
        m_size += 1L;
    } 

    constexpr auto
    _M_read() -> value_type
    {
        if (empty())
            throw std::runtime_error("Ring Empty");

        value_type item = std::move(m_buffer[m_read]);
        m_buffer[m_read] = value_type{};
        m_read = (m_read + 1L) % N;
        m_size -= 1L;
        return item;
    }
};

template<typename T, std::size_t N>
auto println(const ring<T, N>& r) -> void
{
    std::cout << "[< ";
    for (auto i { r.size() }; const auto& e : r)
        std::cout << e << (--i ? ": " : "");
    std::cout << " <]" << std::endl;
}

auto main() -> int
{
    auto r = ring<int, 8>();
    println(r);
    std::cout << std::boolalpha;
    std::cout << "empty? " << r.empty() << std::endl;
    std::cout << "full? " << r.full() << std::endl;
    r.push_back(1);
    println(r);
    r.push_back(2);
    println(r);
    r.push_back(3);
    println(r);
    r.push_back(4);
    println(r);
    r.push_back(5);
    println(r);
    std::cout << "size: " << r.size() << std::endl;
    r.push_back(6);
    println(r);
    r.push_back(7);
    println(r);
    r.push_back(8);
    std::cout << "full? " << r.full() << std::endl;
    println(r);
    auto e0 = r.pop_front();
    std::cout << "e: " << e0 << std::endl;
    println(r);

    auto e1 = r.pop_front();
    println(r);
    auto e2 = r.pop_front();
    println(r);
    auto e3 = r.pop_front();
    println(r);
    auto e4 = r.pop_front();
    println(r);
    auto e5 = r.pop_front();
    println(r);
    auto e6 = r.pop_front();
    println(r);
    r.push_back(99);
    println(r);
    auto e7 = r.pop_front();
    println(r);

    r.pop_front();
    r.push_back(1);
    r.push_back(2);
    r.push_back(3);
    r.push_back(4);
    r.push_back(5);
    r.push_back(6);
    r.push_back(7);
    r.push_back(8);

    auto rc = r;
    std::cout << "Original: ";
    println(r); 
    std::cout << "Copy: ";
    println(rc);

    auto rr = std::move(r);
    std::cout << "Original: ";
    println(r); 
    std::cout << "Copy: ";
    println(rc);
    std::cout << "Move: ";
    println(rr);
    

    return 0;
}