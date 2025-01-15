#include <array>

/// @brief Buffer with static size, default initialized. Keeps as many as <SIZE> most recent elements for iterating
/// @tparam T Type of elements
/// @tparam SIZE static size
template <typename T, unsigned int SIZE>
class HistoryBuffer
{
private:
    unsigned int _WriteIndex = 0;
    std::array<T, SIZE> _Buffer = {0};

    T const &At(unsigned int index)
    {
        return _Buffer[index];
    }

public:
    class Iterator
    {
    private:
        unsigned int _Index;
        T const * &_From;

    public:
        Iterator(HistoryBuffer const &from) : _Index{(from._WriteIndex + SIZE - 1) % SIZE} {};

        Iterator &operator++()
        {
            _Index = (_Index + 1) % SIZE;
        }

        T const &operator*() const
        {
            return _From.At(_Index);
        }

        bool operator!=(const Iterator &other) const
        {
            return _Index != other._Index;
        }
    };

    /// @brief Enqueue a element.
    /// @param value element
    void Enqueue(T const &value)
    {
        _Buffer[_WriteIndex] = value;
        _WriteIndex = (_WriteIndex + 1) % SIZE;
        // WriteIndex bumps into ReadIndex?
        if (_WriteIndex == _ReadIndex)
            _ReadIndex = (_ReadIndex + 1) % SIZE;
    }

    Iterator begin() const
    {
        return Iterator(*this);
    }

    Iterator end() const
    {
        return Iterator(5); // Assuming the end condition
    }
};