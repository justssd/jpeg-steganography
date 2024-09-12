#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>

#include "jdct.hpp"

namespace jpeg
{

void serialize(const std::string &filename, std::vector<bool> &buffer)
{
    std::filesystem::path p{filename};
    uint32_t size = std::filesystem::file_size(p);
    for (int i = 0; i < 32; ++i)
    {
        buffer.push_back((size >> i) & 1);
    }

    std::ifstream f(filename, std::ios::binary);
    char c;
    while (f.get(c))
    {
        for (int i = 7; i >= 0; --i)
        {
            buffer.push_back((c >> i) & 1);
        }
    }
}

void embed(jpeg::jdct &j, const std::string &payload, const std::string &out)
{
    std::vector<bool> data;
    serialize(payload, data);

    unsigned long int count = 0;

    for (int ci = 0; ci < j.cinfo.num_components; ++ci)
    {
        for (JDIMENSION y = 0; y < j.component_info_ptrs[ci]->height_in_blocks; ++y)
        {
            for (JDIMENSION x = 0; x < j.component_info_ptrs[ci]->width_in_blocks; ++x)
            {
                for (JDIMENSION c = 0; c < DCTSIZE2; ++c)
                {
                    if (count >= data.size())
                    {
                        goto write;
                    }
                    int bit = data.at(count++) ? 1 : 0;
                    j(ci, x, y, c) = (j(ci, x, y, c) & ~1) | bit;
                }
            }
        }
    }
write:
    j.write_to_file(out);
}

void extract(const jpeg::jdct &j, const std::string &out)
{
    std::ofstream stego(out, std::ios::binary);

    char byte = 0;
    short bit_pos = 0;

    uint32_t size = 0;
    uint32_t read_count = 0;

    for (int ci = 0; ci < j.cinfo.num_components; ++ci)
    {
        for (JDIMENSION y = 0; y < j.component_info_ptrs[ci]->height_in_blocks; ++y)
        {
            for (JDIMENSION x = 0; x < j.component_info_ptrs[ci]->width_in_blocks; ++x)
            {
                for (JDIMENSION c = 0; c < DCTSIZE2; ++c)
                {
                    bool bit = j(ci, x, y, c) & 1;
                    ++read_count;
                    if (read_count <= 32)
                    {
                        size |= (bit << (read_count - 1));
                        continue;
                    }
                    else if (read_count - 32 > size * 8)
                    {
                        return;
                    }

                    byte = byte << 1 | bit;
                    if (++bit_pos == 8)
                    {
                        stego.write(&byte, 1);
                        byte = 0;
                        bit_pos = 0;
                    }
                }
            }
        }
    }
}

} // namespace jpeg
