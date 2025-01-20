#pragma once

#include <array>

template <typename T, unsigned int SIZE>
class CircularBufferIterator
{
private:
    T const *const _Item0;
    unsigned int _Position;
    bool _HasRolledOver = false;

public:
    CircularBufferIterator(T const *item0, unsigned int position) : _Item0{item0}, _Position{position} {};

    CircularBufferIterator &operator++()
    {
        _Position = (_Position + 1) % SIZE;
        _HasRolledOver |= _Position == 0; // true as soon as _Position has rolled over to '0'
        return *this;
    }

    T const &operator*() const
    {
        return *(_Item0 + _Position);
    }

    bool operator!=(const CircularBufferIterator &other) const
    {
        return _Position != other._Position;
    }
};

/// @brief Buffer with static storage. Use iterators .begin() and .end() for access
/// @tparam T Type of items
/// @tparam SIZE static size
template <typename T, unsigned int SIZE>
class CircularBuffer
{
private:
    unsigned int _WriteIndex = 0;
    // necessary to distinguish a full buffer from a partially full buffer
    bool _IsFull = false;
    std::array<T, SIZE> _Buffer;

public:
    using ConstIt_t = CircularBufferIterator<T, SIZE>;

    /// @brief Enqueue a item.
    /// @param value item
    void Enqueue(T const &value)
    {
        _Buffer[_WriteIndex] = value;
        _WriteIndex = (_WriteIndex + 1) % SIZE;
        _IsFull |= _WriteIndex = 0; // is full as soon as first time rollover to '0'
    }

    T &Last()
    {
        // funky way to say "_WriteIndex - 1" without integer underflow
        return _Buffer[(_WriteIndex + (SIZE - 1)) % SIZE];
    }

    /// @brief Voids the content
    void Clear()
    {
        _WriteIndex = 0;
        _IsFull = false;
    }

    /// @brief Get number of valid items
    /// @return num of items
    unsigned int NumItems() const
    {
        return _IsFull ? SIZE : _WriteIndex;
    }

    /// @brief Get total capacity
    /// @return static storage size
    constexpr unsigned int Size() const
    {
        return SIZE;
    }

    /// @brief Create iterator to the begin of valid items
    /// @return const it
    ConstIt_t begin() const
    {
        return CircularBufferIterator<T, SIZE>(_Buffer.begin(), _WriteIndex);
    }

    /// @brief Create iterator to the end of valid items
    /// @return const it
    ConstIt_t end() consts
    {
        return CircularBufferIterator<T, SIZE>{_Buffer.begin(), (_WriteIndex + _NumItems) % SIZE};
    }
};