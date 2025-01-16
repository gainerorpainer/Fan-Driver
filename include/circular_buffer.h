#include <array>

template <typename T, unsigned int SIZE>
class CircularBufferIterator
{
private:
    T const *const _Item0;
    unsigned int _Position;

public:
    CircularBufferIterator(T const *item0, unsigned int position) : _Item0{item0}, _Position{} {};

    CircularBufferIterator &operator++()
    {
        _Position = (_Position + 1) % SIZE;
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
    unsigned int _NumItems = 0;
    std::array<T, SIZE> _Buffer;

public:
    using ConstIt_t = CircularBufferIterator<T, SIZE>;

    /// @brief Enqueue a item.
    /// @param value item
    void Enqueue(T const &value)
    {
        _Buffer[_WriteIndex] = value;
        _WriteIndex = (_WriteIndex + 1) % SIZE;
        _NumItems = min(_NumItems + 1, SIZE);
    }

    /// @brief Voids the content
    void Clear()
    {
        _NumItems = 0;
    }

    /// @brief Get number of valid items
    /// @return num of items
    unsigned int NumItems() const
    {
        return _NumItems;
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
    ConstIt_t end() const
    {
        return CircularBufferIterator<T, SIZE>{_Buffer.begin(), (_WriteIndex + _NumItems) % SIZE};
    }
};