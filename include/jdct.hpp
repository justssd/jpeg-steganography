#ifndef INCLUDE_JDCT_HPP
#define INCLUDE_JDCT_HPP

#include <jpeglib.h>
#include <string>
#include <vector>

namespace jpeg
{

class jdct
{
  public:
    jdct(const char *filename);
    jdct(const std::string &filename);
    ~jdct();

    JCOEF &operator()(int ci, JDIMENSION x, JDIMENSION y, JDIMENSION c);
    const JCOEF &operator()(int ci, JDIMENSION x, JDIMENSION y, JDIMENSION c) const;

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    jvirt_barray_ptr *quantized_coeffs;
    std::vector<jpeg_component_info *> component_info_ptrs;
    std::vector<JBLOCKARRAY> buffers;
};

} // namespace jpeg

#endif // INCLUDE_JDCT_HPP
