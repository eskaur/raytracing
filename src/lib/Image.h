#pragma once

#include <Vec.h>

#include <string>
#include <vector>

namespace Raytracing
{
    class Image
    {
    public:
        Image(size_t height, size_t width);
        Color3 &operator()(size_t i, size_t j);
        Color3 operator()(size_t i, size_t j) const;
        size_t height() const;
        size_t width() const;
        size_t size() const;
        void save(const std::string &file) const;

    private:
        const size_t m_height;
        const size_t m_width;
        const size_t m_size;
        std::vector<Color3> m_values;
    };
} // namespace Raytracing