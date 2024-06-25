#include <iostream>
#include <vector>
#include "parsing.hpp"
#include "PMergeMe.hpp"
#include "PMergeMeVector.hpp"
#include "PMergeMeDeque.hpp"

int main(int argc, char** argv)
{
    PMergeMeVector      fjohnson_vector;
    PMergeMeDeque       fjohnson_deque;
    std::vector<int>    input_sequence;

    input_sequence.reserve(argc);
    if (!parse_arguments(argc, argv, input_sequence))
        return 1;

    fjohnson_vector.print_unsorted_elements(input_sequence);

    fjohnson_vector.fjohnson_algorithm(input_sequence);
    fjohnson_deque.fjohnson_algorithm(input_sequence);

    fjohnson_vector.print_sorted_elements();

    fjohnson_vector.print_time_to_process("std::vector");
    fjohnson_deque.print_time_to_process("std::deque");
    return 0;
}