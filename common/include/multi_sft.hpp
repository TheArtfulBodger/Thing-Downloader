#pragma once

#include <memory>

/* Trick to allow multiple inheritance of objects
 * inheriting shared_from_this.
 * Based on https://stackoverflow.com/a/12793989/587407
 */

namespace sft {
template <class pointer_t, class base_t>
class multi : public base_t {
public:
    std::shared_ptr<pointer_t> shared_from_this()
    {
        return std::dynamic_pointer_cast<pointer_t>(base_t::shared_from_this());
    }
    /* Utility method to easily downcast.
     * Useful when a child doesn't inherit directly from enable_shared_from_this
     * but wants to use the feature.
     */
    template <class down_t>
    std::shared_ptr<down_t> downcasted_shared_from_this()
    {
        return std::dynamic_pointer_cast<down_t>(base_t::shared_from_this());
    }
};
}