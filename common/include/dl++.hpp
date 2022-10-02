#pragma once
#include <functional>
#include <stdexcept>

#ifdef _MSC_VER
#include <libloaderapi.h>
#else
#include <dlfcn.h>
#endif

/**
 * @brief A simple wrapper around libdl in modern C++
 * @todo Add Windows support via LoadLibrary functions
 *
 */
namespace libdl {

/**
 * @brief
 *
 * @param name
 * @return void* pointer returned by dlopen (or equivalent)
 */
inline void* open_lib(std::string name)
{
#ifdef _MSC_VER
    return LoadLibraryA(name.c_str());
#else
    return dlopen(name.c_str(), RTLD_NOW);
#endif
}

/**
 * @brief Get the value object
 *
 * @tparam var_t The type of the variable.
 * @param handle Pointer returned by `dlopen`
 * @param name The name of the symbol
 * @return The variable loaded from the shared object
 */
template <typename var_t>
inline var_t get_value(void* handle, std::string name)
{
#ifdef _MSC_VER
    void* sym = GetProcAddress(handle, name.c_str());
#else
    void* sym = dlsym(handle, name.c_str());
#endif

    if (sym == nullptr) {
        throw std::runtime_error("ERROR: Symbol " + name + " is nullptr");
    }
    return *reinterpret_cast<var_t*>(sym);
}

template <typename func_t>
/*!
 * @brief Get function from loaded symbol
 * @tparam func_t The inner type of the function
 * @param handle Pointer returned by `dlopen`
 * @param name The name of the symbol
 * @return std::function object loaded from the shared object
 */
inline std::function<func_t> get_function(void* handle, std::string name)
{
#ifdef _MSC_VER
    void* sym = GetProcAddress(handle, name.c_str());
#else
    void* sym = dlsym(handle, name.c_str());
#endif

    if (sym == nullptr) {
        throw std::runtime_error("ERROR: Symbol " + name + " is nullptr");
    }
    return reinterpret_cast<func_t*>(sym);
}

/**
 * @brief Removes function wrapper from `std::function`
 * @details Acts similarly to <a href="https://en.cppreference.com/w/cpp/types/remove_pointer">std::remove_pointer</a>
 * or <a href="https://en.cppreference.com/w/cpp/types/remove_reference">std::remove_reference</a>
 *
 * <ul>
 * <li>`std::function<example_t>` -> `example_t`</li>
 * <li>`example_t` -> `example_t`</li>
 * </ul>
 */
template <class in_type>
struct remove_function {
    /*! @brief The output type.*/
    using type = in_type;
};

/**
 * @brief `std::function` template specialisation
 */
template <class in_type>
struct remove_function<std::function<in_type>> {
    /*! @brief The output type.*/
    using type = in_type;
};
}