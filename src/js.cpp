#include <fstream>
#include <iostream>

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
        std::ifstream cover(argv[2], std::ios::binary);
        if (!cover)
        {
            std::cerr << "Could not open " << argv[2] << "\n";
            return 1;
        }

        std::ifstream payload(argv[3], std::ios::binary);
        if (!payload)
        {
            std::cerr << "Could not open " << argv[3] << "\n";
            return 1;
        }

        std::ofstream stego(argv[4], std::ios::binary);
        if (!stego)
        {
            std::cerr << "Could not open " << argv[4] << "\n";
            return 1;
        }
    }
    else if (argc == 4 && argv[1] == "extract"sv)
    {
        std::ifstream cover(argv[2], std::ios::binary);
        if (!cover)
        {
            std::cerr << "Could not open " << argv[2] << "\n";
            return 1;
        }

        std::ofstream out(argv[3], std::ios::binary);
        if (!out)
        {
            std::cerr << "Could not open " << argv[3] << "\n";
            return 1;
        }
    }
    else
    {
        print_usage();
        return 1;
    }
}
