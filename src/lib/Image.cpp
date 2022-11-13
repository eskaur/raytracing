#include <Image.h>

#include <cmath>
#include <fstream>

namespace Raytracing
{
    Image::Image(size_t height, size_t width)
        : m_height(height)
        , m_width(width)
        , m_size(height * width)
        , m_values(m_size, Color3())
    {}

    Color3 &Image::operator()(size_t i, size_t j)
    {
        return m_values[m_width * i + j];
    }

    Color3 Image::operator()(size_t i, size_t j) const
    {
        return m_values[m_width * i + j];
    }

    size_t Image::height() const
    {
        return m_height;
    }
    size_t Image::width() const
    {
        return m_width;
    }
    size_t Image::size() const
    {
        return m_size;
    }

    void Image::save(const std::string &file) const
    {
        std::ofstream stream;
        stream.open(file);

        stream << "P3" << std::endl;
        stream << width() << " " << height() << std::endl;
        stream << "255" << std::endl;

        for(int i = height() - 1; i >= 0; --i)
        {
            for(int j = 0; j < width(); ++j)
            {
                const auto &color = m_values[m_width * i + j];

                // Note: sqrt for gamma-correction
                auto ir = static_cast<int>(255.999 * std::sqrt(color.x()));
                auto ig = static_cast<int>(255.999 * std::sqrt(color.y()));
                auto ib = static_cast<int>(255.999 * std::sqrt(color.z()));
                stream << ir << ' ' << ig << ' ' << ib << '\n';
            }
        }
        stream.close();
    }
} // namespace Raytracing