#include <iostream>
#include <vector>
#include <type_traits>
#include <concepts>

namespace cpplab
{
    template <typename T>
    class vector
    {
    private:
        T *data = nullptr;
        size_t Size = 0;
        size_t capacity = 0;

    public:
        typedef T value_type;

    private:
        void realloc(size_t newcap);

    public:
        vector();
        vector(size_t initsize);
        vector(const vector &v);
        vector(vector &&other) noexcept;
        vector(std::initializer_list<T> l);
        vector &operator=(const vector &other);
        vector &operator=(vector &&other) noexcept;
        ~vector();

        void resize(size_t new_size);
        void pop_back();
        const T &operator[](size_t index) const;
        T &operator[](size_t index);
        void push_back(const T &el);
        void push_back(){};
        size_t size() const;

        template <typename First, typename... Args>
        void emplace_back(First &&first, Args &&...args);

        void emplace_back(){};
    };

    template <typename T>
    vector<T>::vector() : Size(0), capacity(0), data(nullptr) {}

    template <typename T>
    vector<T>::vector(size_t initsize) : Size(initsize), capacity(initsize), data(new T[initsize]) {}

    template <typename T>
    vector<T>::vector(const vector &v) : Size(v.Size), capacity(v.capacity), data(new T[v.Size])
    {

        for (size_t i(0); i < this->Size; i++)
            this->data[i] = v.data[i];
    }

    template <typename T>
    vector<T>::vector(vector &&other) noexcept : Size(other.Size), capacity(other.capacity), data(other.data)
    {
        other.data = nullptr;
        other.capacity = 0;
        other.Size = 0;
    }

    template <typename T>
    vector<T>::vector(std::initializer_list<T> l) : Size(0), capacity(0), data(nullptr)
    {
        for (const T &elem : l)
        {
            push_back(elem);
        }
    }

    template <typename T>
    vector<T> &vector<T>::operator=(const vector &other)
    {
        capacity = other.capacity;
        Size = other.Size;
        data = new T[Size];

        for (size_t i(0); i < this->Size; i++)
            data[i] = other.data[i];

        return *this;
    }

    template <typename T>
    vector<T> &vector<T>::operator=(vector &&other) noexcept
    {
        capacity = other.capacity;
        Size = other.Size;
        data = other.data;

        other.capacity = 0;
        other.Size = 0;
        other.data = nullptr;

        return *this;
    }

    template <typename T>
    vector<T>::~vector()
    {
        delete[] data;
        resize(0);
    }

    template <typename T>
    void vector<T>::realloc(size_t newcap)
    {
        if (newcap < Size)
            newcap = Size;

        T *new_data = new T[newcap];

        for (size_t i(0); i < Size; i++)
            new_data[i] = data[i];

        delete[] data;
        capacity = newcap;
        data = new_data;
    }

    template <typename T>
    void vector<T>::resize(size_t new_size)
    {
        if (new_size <= capacity)
        {
            Size = new_size;
        }
        else
        {
            Size = new_size;
            realloc(new_size);
        }
    }

    template <typename T>
    void vector<T>::pop_back()
    {
        if (Size > 0)
        {
            resize(Size - 1);
        }
    }

    template <typename T>
    const T &vector<T>::operator[](size_t index) const
    {
        return data[index];
    }

    template <typename T>
    T &vector<T>::operator[](size_t index)
    {
        return data[index];
    }

    template <typename T>
    void vector<T>::push_back(const T &el)
    {
        if (Size >= capacity)
        {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            realloc(capacity);
        }
        data[Size] = el;
        Size++;
    }

    template <typename T>
    size_t vector<T>::size() const
    {
        return Size;
    }

    template <typename T>
    concept is_float_or_int = requires {
        typename T::value_type;
        std::is_integral_v<typename T::value_type> || std::is_floating_point_v<typename T::value_type>;
    };

    template <typename T>
    concept HasSizeMemberFunction = requires {
        {
            std::declval<T>().size()
        } -> std::same_as<std::size_t>;
    };

    template <typename T>
    concept HasSubscriptOperator = requires {
        {
            std::declval<T>()[0]
        } -> std::same_as<decltype(std::declval<T>()[0])>;
    };

    template <typename T>
    concept all_three = is_float_or_int<T> && HasSizeMemberFunction<T> && HasSubscriptOperator<T> && std::is_class<T>::value;

    template <all_three T, all_three U>
    auto operator*(const T &a, const U &b) -> decltype((a[0] * b[0]))
    {
        if (a.size() != b.size() || b.size() == 0 || a.size() == 0)
            throw std::out_of_range("different or zero number of argument components");

        decltype((a[0] * b[0])) result = 0;

        for (size_t i(0); i < a.size(); ++i)
        {
            result += a[i] * b[i];
        }

        return result;
    }

    template <typename T>
    template <typename First, typename... Args>
    void vector<T>::emplace_back(First &&first, Args &&...args)
    {
        push_back(std::forward<First>(first));
        emplace_back(std::forward<Args>(args)...);
    };

    template <typename T>
    void print_V(const cpplab::vector<T> &v)
    {
        if (v.size() != 0)
        {
            std::cout << "[";
            for (size_t i(0); i < v.size() - 1; i++)
                std::cout << v[i] << ",";
            std::cout << v[v.size() - 1] << "]\n";
        }
    }
}
