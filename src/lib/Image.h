#pragma once

#include <string>
#include <vector>

namespace Raytracing
{
    enum class Color
    {
        Red,
        Green,
        Blue
    };

    class Image
    {
    public:
        Image(size_t height, size_t width);
        float &operator()(size_t i, size_t j, Color color);
        float operator()(size_t i, size_t j, Color color) const;
        size_t height() const;
        size_t width() const;
        size_t size() const;
        void save(const std::string &file) const;

    private:
        const size_t m_height;
        const size_t m_width;
        const size_t m_size;
        std::vector<float> m_values;

        size_t getIdx(size_t i, size_t j, Color color) const;
    };
} // namespace Raytracing