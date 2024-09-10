#include <format>
#include <iostream>
#include <stdexcept>

#include "jdct.hpp"

int main()
{
    jpeg::jdct j("../data/clouds-400x300.jpg");

    for (int ci = 0; ci < j.cinfo.num_components; ++ci)
    {
        for (JDIMENSION y = 0; y < j.component_info_ptrs[ci]->height_in_blocks; ++y)
        {
            for (JDIMENSION x = 0; x < j.component_info_ptrs[ci]->width_in_blocks; ++x)
            {
                std::cout << std::format("(ci, x, y): ({}, {}, {})\n", ci, x, y);
                for (JDIMENSION c = 0; c < DCTSIZE2; ++c)
                {
                    std::cout << std::format("{} ", j(ci, x, y, c));
                }
                std::cout << std::endl;
            }
        }
    }

    try
    {
        jpeg::jdct fail("123.123");
    }
    catch (std::runtime_error &e)
    {
        return 0;
    }

    return -1;
}
