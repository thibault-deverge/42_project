#include "PMergeMeVector.hpp"

/*
** ---------------------------- Coplien's form ---------------------------------
*/
PMergeMeVector::PMergeMeVector() {}
PMergeMeVector::~PMergeMeVector() {}

PMergeMeVector::PMergeMeVector(const PMergeMeVector& other): PMergeMe(other)
{
    _pairs_elements = other._pairs_elements;
    _sorted_elements = other._sorted_elements;
}

PMergeMeVector& PMergeMeVector::operator=(const PMergeMeVector& rhs)
{
    if (this != &rhs)
    {
        PMergeMe::operator=(rhs);
        _pairs_elements = rhs._pairs_elements;
        _sorted_elements = rhs._sorted_elements;
    }
    return *this;
}

/*
** ------------------------ Main functions --------------------------------
*/
void PMergeMeVector::fjohnson_algorithm(const Int_Vector& input_seq)
{
    // Get size of input and preallocate enough memory in the containers
    _input_size = input_seq.size();
    _sorted_elements.reserve(_input_size);
    _pairs_elements.reserve(_input_size / 2);
    generate_fjohnson_sequence();

    // Start timer
    gettimeofday(&_start, NULL); 

    pair_and_compare(input_seq);
    merge_sort(0, _sorted_elements.size());
    insert_smallest_element();
    sort_pairs_by_fjohnson_sequence();
    insert_remaining_elements();

    // End timer
    gettimeofday(&_end, NULL); 
}

/*
** -------------------- STEP1: Grouping into pairs -----------------------------
*/
void PMergeMeVector::pair_and_compare(const Int_Vector& input_seq)
{
    // Make pair of adjacents elements in input_sequence
    for (size_t i=0; i < input_seq.size() - 1; i += 2)
    {
        Int_Pair min_max = pair_min_max(input_seq[i], input_seq[i+1]);

        _pairs_elements.push_back(min_max);
        _sorted_elements.push_back(min_max.second);
    }

    // Handle case input_size is odd
    if (_input_size % 2 == 1)
        _single_odd_element = input_seq.back();
}

std::pair<int, int> PMergeMeVector::pair_min_max(int n1, int n2) const
{
    if (n1 < n2)
        return std::make_pair(n1, n2);
    return std::make_pair(n2, n1);
}

/*
** -------------- STEP2: Sort larger elements (Merge-sort) ---------------------
*/
void PMergeMeVector::merge_sort(int start, int end)
{
    if (end - start <= 1)
        return;
    
    int middle = (start + end) / 2;

    // Recursively apply merge sort to the two halves
    merge_sort(start, middle);
    merge_sort(middle, end);

    // Merge the sorted halves back together
    merge_sort_helper(start, middle, end);
}

void PMergeMeVector::merge_sort_helper(int start, int middle, int end)
{
    Int_Vector temp(end - start);
    int i = start, j = middle, k = 0;

    // Merge and sort elements from both sub-vectors into temp
    while (i < middle && j < end)
    {
        if (_sorted_elements[i] < _sorted_elements[j])
            temp[k++] = _sorted_elements[i++];
        else
            temp[k++] = _sorted_elements[j++];
    }
    while (i < middle)
        temp[k++] = _sorted_elements[i++];
    while (j < end)
        temp[k++] = _sorted_elements[j++];
    
    // Copy back the sorted elements into _sorted_elements
    for (i = start, k = 0; i < end; ++i, ++k)
        _sorted_elements[i] = temp[k];
}

void PMergeMeVector::insert_smallest_element()
{
    Pair_Vector::iterator   it  = _pairs_elements.begin();
    int                     smallest_element = _sorted_elements.front();

    // Find the pair associated with the smallest element in _sorted_elements
    for (; it != _pairs_elements.end(); ++it)
    {
        if (it->second == smallest_element)
        {
            // Insert its pair element at the beginning
            _sorted_elements.insert(_sorted_elements.begin(), it->first);
            _pairs_elements.erase(it); 
            break;
        }
    }
}

/*
** ----------- STEP3: Insert remaining elements (binary search) ----------------
*/
void PMergeMeVector::sort_pairs_by_fjohnson_sequence()
{
    Pair_Vector temp;
    size_t      size_group;

    for (size_t i = 0; i < _fjohnson_sequence.size(); ++i)
    {
        size_group = _fjohnson_sequence[i];
        if (size_group > _pairs_elements.size()) 
            break;
        
        // Insert elements from larger to smaller index
        for (; size_group > 0; --size_group)
            temp.push_back(_pairs_elements[size_group - 1]);

        // Erase these elements in original pair sequence
        Pair_Vector::iterator it = _pairs_elements.begin();
        _pairs_elements.erase(it, it + _fjohnson_sequence[i]);
    }

    size_group = _pairs_elements.size();
    while (size_group > 0)
    {
        temp.push_back(_pairs_elements[size_group - 1]);
        --size_group;
    }
    _pairs_elements = temp;
}

void PMergeMeVector::insert_remaining_elements()
{
    for (size_t i = 0; i < _pairs_elements.size(); ++i)
    {
        int element_to_insert  = _pairs_elements[i].first;
        int upper_element      = _pairs_elements[i].second;

        // Find the index to insert the element (from start the element it is paired with)
        int upper_index     = binary_search(upper_element, _sorted_elements.size() - 1);
        int insert_index    = binary_search(element_to_insert, upper_index);

        _sorted_elements.insert(_sorted_elements.begin() + insert_index, element_to_insert);
    }
    
    if (_single_odd_element != -1)
    {
        int insert_index = binary_search(_single_odd_element, _sorted_elements.size() - 1);
        _sorted_elements.insert(_sorted_elements.begin() + insert_index, _single_odd_element); 
    }
}

int PMergeMeVector::binary_search(int target, int high) const
{
    int low = 0;

    while (low <= high)
    {
        int middle = low + (high - low) / 2;
        int value = _sorted_elements[middle];

        if (value < target)
            low = middle + 1;
        else if (value > target)
            high = middle - 1;
        else
            return middle;
    }
    return low;
}

/*
** ------------------------ Small Helper's Functions ---------------------------
*/
void PMergeMeVector::print_sorted_elements() const
{
    size_t i = 0;
    std::cout << "After:\t";

    while (i < _sorted_elements.size() && i < 4)
    {
        std::cout << _sorted_elements[i] << " ";
        ++i;
    }
    if (i < _sorted_elements.size())
        std::cout << "[...]";

    std::cout << std::endl;
}