#include <Image.h>

#include <fstream>

namespace Raytracing
{
    constexpr size_t nColors = 3;

    Image::Image(size_t height, size_t width)
        : m_height(height)
        , m_width(width)
        , m_size(height * width)
        , m_values(nColors * m_size, 0.0F)
    {}

    size_t Image::getIdx(size_t i, size_t j, Color color) const
    {
        const size_t colorOffset = [&color]() {
            switch(color)
            {
                case Color::Red: return 0;
                case Color::Green: return 1;
                case Color::Blue: return 2;
                default: throw std::runtime_error("Unknown color");
            }
        }();

        return (m_width * nColors) * i + j * nColors + colorOffset;
    }

    float &Image::operator()(size_t i, size_t j, Color color)
    {
        return m_values[getIdx(i, j, color)];
    }

    float Image::operator()(size_t i, size_t j, Color color) const
    {
        return m_values[getIdx(i, j, color)];
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
                auto ir = static_cast<int>(255.999 * m_values[getIdx(i, j, Color::Red)]);
                auto ig = static_cast<int>(255.999 * m_values[getIdx(i, j, Color::Green)]);
                auto ib = static_cast<int>(255.999 * m_values[getIdx(i, j, Color::Blue)]);
                stream << ir << ' ' << ig << ' ' << ib << '\n';
            }
        }
        stream.close();
    }

} // namespace Raytracing