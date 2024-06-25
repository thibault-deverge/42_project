#include "utils.hpp"

static void open_infile(std::ifstream& infile, const std::string& filename);
static void open_outfile(std::ofstream& outfile, std::string& filename);

void search_and_replace(std::string& filename, std::string& str1, std::string& str2)
{
    std::ifstream   input_file;
    std::ofstream   output_file;
    std::string     line;

    open_infile(input_file, filename);
    open_outfile(output_file, filename);
    while (std::getline(input_file, line))
    {
        std::string new_line;
        std::size_t pos;

        while ((pos = line.find(str1)) != std::string::npos)
        {
            new_line += line.substr(0, pos);
            new_line += str2;
            line.erase(0, pos + str1.length());
        }
        new_line += line;
        output_file << new_line << std::endl;  
    }
    input_file.close();
    output_file.close();
}

// ********** Static Functions **********
static void open_infile(std::ifstream& infile, const std::string& filename)
{
    infile.open(filename.c_str());
    if (infile.fail())
        throw std::runtime_error(ERROR_OPEN_FILE);
}

static void open_outfile(std::ofstream& outfile, std::string& filename)
{
    outfile.open(filename.append(".replace").c_str());
    if (outfile.fail())
        throw std::runtime_error(ERROR_CREATE_FAIL);
}