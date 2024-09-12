#include <fstream>
#include <iostream>
#include <vector>

#include <jpeglib.h>

#include "jdct.hpp"
#include "jsteg.hpp"

using namespace std::literals;

void print_usage()
{
    std::cerr << "Usage:\n"
              << "      ./js embed cover.jpg payload.txt stego.jpg\n"
              << "      ./js extract cover.jpg out.txt\n";
}

int main(int argc, char **argv)
{
    if (argc == 5 && argv[1] == "embed"sv)
    {
        try
        {
            jpeg::jdct j(argv[2]);
            jpeg::embed(j, argv[3], argv[4]);
        }
        catch (std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    else if (argc == 4 && argv[1] == "extract"sv)
    {
        try
        {
            jpeg::jdct j(argv[2]);
            jpeg::extract(j, argv[3]);
        }
        catch (std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    else
    {
        print_usage();
        return 1;
    }
}
