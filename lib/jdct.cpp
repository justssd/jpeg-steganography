#include <memory>
#include <stdexcept>

#include "jdct.hpp"

namespace jpeg
{

jdct::jdct(const char *filename)
{
    std::unique_ptr<FILE, int (*)(FILE *)> f(fopen(filename, "rb"), fclose);
    if (f == NULL)
    {
        throw std::runtime_error(std::string("Could not open ") + filename);
    }

    /*
     * Reference: libjpeg-turbo/structure.txt
     *
     * Arrays of DCT-coefficient values use the following data structure:
     * typedef short JCOEF;                a 16-bit signed integer
     * typedef JCOEF JBLOCK[DCTSIZE2];     an 8x8 block of coefficients
     * typedef JBLOCK *JBLOCKROW;          ptr to one horizontal row of 8x8 blocks
     * typedef JBLOCKROW *JBLOCKARRAY;     ptr to a list of such rows
     * typedef JBLOCKARRAY *JBLOCKIMAGE;   ptr to a list of color component arrays
     */

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, f.get());
    jpeg_read_header(&cinfo, true);

    quantized_coeffs = jpeg_read_coefficients(&cinfo);

    for (int ci = 0; ci < cinfo.num_components; ++ci)
    {
        jpeg_component_info *ci_ptr = cinfo.comp_info + ci;
        component_info_ptrs.push_back(ci_ptr);

        JBLOCKARRAY buffer = (*cinfo.mem->access_virt_barray)((j_common_ptr)&cinfo, quantized_coeffs[ci], 0,
                                                              ci_ptr->v_samp_factor, true);
        buffers.push_back(buffer);
    }
}

jdct::jdct(const std::string &filename) : jdct::jdct(filename.c_str())
{
}

JCOEF &jdct::operator()(int ci, JDIMENSION x, JDIMENSION y, JDIMENSION c)
{
    return buffers[ci][y][x][c];
}

const JCOEF &jdct::operator()(int ci, JDIMENSION x, JDIMENSION y, JDIMENSION c) const
{
    return buffers[ci][y][x][c];
}

jdct::~jdct()
{
    (void)jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
}

} // namespace jpeg
