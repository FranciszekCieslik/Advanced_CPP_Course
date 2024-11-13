#include <cstring>
#include <string>
#include <cstdlib>
#include <concepts>

template <typename T, typename U>
inline decltype(auto) add(T *a, U *b)
{
    auto res = *a + *b;
    return res;
}

// Overloaded function for C-style strings
char *add(const char *str1, const char *str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    int totalLen = len1 + len2 + 1;
    char *res = new char[totalLen];

    if (res)
    {
        strcpy(res, str1);
        strcat(res, str2);
    }

    return res;
};


template <typename T>
concept Arithmetic = 
!std::is_same_v<T, char> &&                     
!std::is_same_v<T, std::string> &&              
!std::is_array_v<T> &&                          
!std::is_array_v<std::remove_reference_t<T>>;

template <Arithmetic T, Arithmetic ... Ts>
inline decltype(auto) add_total(T const& first, Ts const&... rest) {
    double sum = first; 
    if constexpr (sizeof...(rest) > 0) {        
        sum += add_total(rest...);
    } 
    return sum;
};
