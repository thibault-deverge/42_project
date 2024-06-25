#include "PMergeMe.hpp"

PMergeMe::PMergeMe(): _input_size(0), _single_odd_element(-1) {}
PMergeMe::~PMergeMe() {}

PMergeMe::PMergeMe(const PMergeMe& other)
{
    _input_size = other._input_size;
    _single_odd_element = other._single_odd_element;
    _fjohnson_sequence = other._fjohnson_sequence;
}

PMergeMe& PMergeMe::operator=(const PMergeMe& rhs)
{
    if (this != &rhs)
    {
        _input_size = rhs._input_size;
        _single_odd_element = rhs._single_odd_element;
        _fjohnson_sequence = rhs._fjohnson_sequence;
    }
    return *this;
}

void PMergeMe::generate_fjohnson_sequence()
{
    // Initialize the F. Johnson sequence with the first two elements
    _fjohnson_sequence.insert(_fjohnson_sequence.begin(), 2, 2);

    int sum_sequence_elements = 4;
    // Generate the sequence based on the input size
    while (sum_sequence_elements < _input_size / 2)
    {
        Int_Vector::iterator it = _fjohnson_sequence.end() - 2;

        int new_element = (2 * (*it)) + *(it + 1);  // 2 * before_last + last

        _fjohnson_sequence.push_back(new_element);
        sum_sequence_elements += new_element;
    }
}

void PMergeMe::print_unsorted_elements(const Int_Vector& input_sequence) const
{
    size_t i = 0;
    std::cout << "before:\t";

    // Prints up to the first four elements.
    while (i < input_sequence.size() && i < 4)
    {
        std::cout << input_sequence[i] << " ";
        ++i;
    }
    if (i < input_sequence.size())
        std::cout << "[...]";

    std::cout << std::endl;
}

void PMergeMe::print_time_to_process(const std::string& container) const
{
    long start = (_start.tv_sec * 1000000) + _start.tv_usec;
    long end = (_end.tv_sec * 1000000) + _end.tv_usec;

    std::cout   << "Time to process a range of " << _input_size
                << " elements with " << container << ": "
                << end - start << " us." << std::endl;
}