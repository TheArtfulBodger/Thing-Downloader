#pragma once

#include <msgpack.hpp>

inline const int download_mode_video = 1;
inline const int download_mode_desc = 2;

struct opera {
    std::string name;
    std::string slug;
    std::string video_id;
    std::string company;
    int operation;

    template <class packer_t>
    void pack(packer_t& pack)
    {
        pack(name, slug, video_id, company, operation);
    }
};