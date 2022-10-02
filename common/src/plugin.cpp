#include <dl++.hpp>
#include <iostream>
#include <td/plugin.hpp>

#define VAR_FROM_DLL(sym) sym = libdl::get_value<decltype(sym)>(handle, #sym);
#define FUNC_FROM_DLL(sym) sym = libdl::get_function<libdl::remove_function<decltype(sym)>::type>(handle, #sym);

td::plugin::plugin(std::string& path)
{
    this->handle = libdl::open_lib(path.c_str());

    if (this->handle == nullptr) {
        std::cout << dlerror() << std::endl;
    }

    VAR_FROM_DLL(key)
    VAR_FROM_DLL(name)
    VAR_FROM_DLL(description)
    VAR_FROM_DLL(required_confs)
    VAR_FROM_DLL(required_secrets)

    FUNC_FROM_DLL(get_jobs)
    FUNC_FROM_DLL(process_job)
    FUNC_FROM_DLL(should_skip)
}

td::plugin::~plugin()
{
    dlclose(this->handle);
}