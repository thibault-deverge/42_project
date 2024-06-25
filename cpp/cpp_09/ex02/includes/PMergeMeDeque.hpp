#pragma once

#include "PMergeMe.hpp"

class PMergeMeDeque : public PMergeMe
{
    // Member variable
    Pair_Deque   _pairs_deque;
    Int_Deque    _sorted_deque;

    // Step 1: Grouping into pairs
    void pair_and_compare(const Int_Vector& input_seq);

    // Step 2&3 : Recursively sort larger elements (merge-sort)
    void merge_sort(int start, int end);
    void merge_sort_helper(int start, int middle, int end);
    void insert_smallest_element();

    // STEP 3 & 4 : Insert remaining elements (binary search)
    void sort_pairs_by_fjohnson_sequence();
    void insert_remaining_elements();
    int  binary_search(int target, int high) const;

    // Helper methods
    std::pair<int, int> pair_min_max(int n1, int n2) const;

public:
    // Coplien's Form
    PMergeMeDeque();
    PMergeMeDeque(const PMergeMeDeque& other);
    ~PMergeMeDeque();
    PMergeMeDeque& operator=(const PMergeMeDeque& rhs);

    // Public method
    void fjohnson_algorithm(const Int_Vector& input_seq);
    void print_sorted_elements() const;
};