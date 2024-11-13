#include <iostream>
#include <memory>
#include <stdexcept>
#include <concepts>

namespace cpplab
{

    template <typename T>
    class unique_ptr
    {
    private:
        T *ptr;

    public:
        // Konstruktor
        explicit unique_ptr(T *p = nullptr) : ptr(p) {}

        // Destruktor
        ~unique_ptr()
        {
            delete ptr;
        }

        // Operator przypisania
        unique_ptr &operator=(unique_ptr &&other)
        {
            if (this != &other)
            {
                reset(other.release());
            }
            return *this;
        }

        // Przenoszący konstruktor
        unique_ptr(unique_ptr &&other) : ptr(other.release()) {}

        // Operator dereferencji
        T &operator*() const
        {
            return *ptr;
        }

        // Operator dostępu do składowych
        T *operator->() const
        {
            return ptr;
        }

        // Zwraca wskaźnik i uwalnia odpowiedzialność za niego
        T *release()
        {
            T *temp = ptr;
            ptr = nullptr;
            return temp;
        }

        // Resetuje wskaźnik na nowy obiekt
        void reset(T *p = nullptr)
        {
            if (p != ptr)
            {
                delete ptr;
                ptr = p;
            }
        }

        // Zwraca wskaźnik
        T *get() const
        {
            return ptr;
        }
    };

    template <typename T>
    concept NonNull = requires(T *t) {
        { t != nullptr } -> std::same_as<bool>;
    };

    template <NonNull T>
    class non0_ptr
    {
    private:
        T *ptr;

    public:
        non0_ptr(T *p) : ptr(p)
        {
            if (ptr == nullptr)
            {
                throw std::invalid_argument("non0_ptr cannot be nullptr");
            }
        }

        ~non0_ptr()
        {
            delete ptr;
        }

        T *get() const
        {
            return ptr;
        }
    };
}