if(MSVC)
    include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

    ExternalProject_Add(zlib
    GIT_REPOSITORY "${git_protocol}://github.com/madler/zlib.git"
    GIT_TAG "v1.2.12"
    SOURCE_DIR zlib
    BINARY_DIR zlib-build
    INSTALL_DIR zlib-install
    CMAKE_CACHE_ARGS
        ${ep_common_args}
        -DZLIB_MANGLE_PREFIX:STRING=itkexamples_zlib_
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    )
    set(zlib_DIR "${CMAKE_BINARY_DIR}/zlib-install" CACHE PATH "zlib dir" FORCE)
    set(ZLIB_ROOT ${zlib_DIR} CACHE PATH "zlib root" FORCE)
    set(ZLIB_INCLUDE_DIR ${CMAKE_BINARY_DIR}/zlib CACHE PATH "zlib include dir" FORCE)
    set(ZLIB_LIBRARY ${zlib_DIR}/lib/zlib.lib CACHE FILEPATH "zlib library" FORCE)
endif()
