#include "PMergeMeDeque.hpp"

/*
** ---------------------------- Coplien's form ---------------------------------
*/
PMergeMeDeque::PMergeMeDeque() {}
PMergeMeDeque::~PMergeMeDeque() {}

PMergeMeDeque::PMergeMeDeque(const PMergeMeDeque& other): PMergeMe(other)
{
    _pairs_deque = other._pairs_deque;
    _sorted_deque = other._sorted_deque;
}

PMergeMeDeque& PMergeMeDeque::operator=(const PMergeMeDeque& rhs)
{
    if (this != &rhs)
    {
        PMergeMe::operator=(rhs);
        _pairs_deque = rhs._pairs_deque;
        _sorted_deque = rhs._sorted_deque;
    }
    return *this;
}

/*
** ------------------------ Main functions --------------------------------
*/
void PMergeMeDeque::fjohnson_algorithm(const Int_Vector& input_seq)
{
    // Get size of input and preallocate enough memory in the containers
    _input_size = input_seq.size();
    generate_fjohnson_sequence();

    // Start timer
    gettimeofday(&_start, NULL); 

    pair_and_compare(input_seq);
    merge_sort(0, _sorted_deque.size());
    insert_smallest_element();
    sort_pairs_by_fjohnson_sequence();
    insert_remaining_elements();

    // End timer
    gettimeofday(&_end, NULL); 
}

/*
** -------------------- STEP1: Grouping into pairs -----------------------------
*/
void PMergeMeDeque::pair_and_compare(const Int_Vector& input_seq)
{
    // Make pair of adjacents elements in input_sequence
    for (size_t i=0; i < input_seq.size() - 1; i += 2)
    {
        Int_Pair min_max = pair_min_max(input_seq[i], input_seq[i+1]);

        _pairs_deque.push_back(min_max);
        _sorted_deque.push_back(min_max.second);
    }

    // Handle case input_size is odd
    if (_input_size % 2 == 1)
        _single_odd_element = input_seq.back();
}

std::pair<int, int> PMergeMeDeque::pair_min_max(int n1, int n2) const
{
    if (n1 < n2)
        return std::make_pair(n1, n2);
    return std::make_pair(n2, n1);
}

/*
** -------------- STEP2: Sort larger elements (Merge-sort) ---------------------
*/
void PMergeMeDeque::merge_sort(int start, int end)
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

void PMergeMeDeque::merge_sort_helper(int start, int middle, int end)
{
    Int_Deque temp(end - start);
    int i = start, j = middle, k = 0;

    // Merge and sort elements from both sub-deque into temp
    while (i < middle && j < end)
    {
        if (_sorted_deque[i] < _sorted_deque[j])
            temp[k++] = _sorted_deque[i++];
        else
            temp[k++] = _sorted_deque[j++];
    }
    while (i < middle)
        temp[k++] = _sorted_deque[i++];
    while (j < end)
        temp[k++] = _sorted_deque[j++];
    
    // Copy back the sorted elements into _sorted_deque
    for (i = start, k = 0; i < end; ++i, ++k)
        _sorted_deque[i] = temp[k];
}

void PMergeMeDeque::insert_smallest_element()
{
    Pair_Deque::iterator    it  = _pairs_deque.begin();
    int                     smallest_element = _sorted_deque.front();

    // Find the pair associated with the smallest element in _sorted_elements
    for (; it != _pairs_deque.end(); ++it)
    {
        if (it->second == smallest_element)
        {
            // Insert its pair element at the beginning
            _sorted_deque.push_front(it->first);
            _pairs_deque.erase(it); 
            break;
        }
    }
}

/*
** ----------- STEP3: Insert remaining elements (binary search) ----------------
*/
void PMergeMeDeque::sort_pairs_by_fjohnson_sequence()
{
    Pair_Deque   temp;

    for (size_t i = 0; i < _fjohnson_sequence.size(); ++i)
    {
        if (static_cast<size_t>(_fjohnson_sequence[i]) > _pairs_deque.size()) 
            break;
        
        // Insert elements from larger to smaller index
        for (int j = 0; j < _fjohnson_sequence[i]; ++j)
            temp.push_front(_pairs_deque[j]);

        // Erase these elements in original pair sequence
        Pair_Deque::iterator it = _pairs_deque.begin();
        _pairs_deque.erase(it, it + _fjohnson_sequence[i]);
    }

    // Insert remaining element needed to be inserted
    for (size_t i = 0; i < _pairs_deque.size(); ++i)
        temp.push_front(_pairs_deque[i]);
    _pairs_deque = temp;
}

void PMergeMeDeque::insert_remaining_elements()
{
    for (size_t i = 0; i < _pairs_deque.size(); ++i)
    {
        int element_to_insert  = _pairs_deque[i].first;
        int upper_element      = _pairs_deque[i].second;

        // Find the index to insert the element (from start the element it is paired with)
        int upper_index     = binary_search(upper_element, _sorted_deque.size() - 1);
        int insert_index    = binary_search(element_to_insert, upper_index);

        _sorted_deque.insert(_sorted_deque.begin() + insert_index, element_to_insert);
    }
    
    if (_single_odd_element != -1)
    {
        int insert_index = binary_search(_single_odd_element, _sorted_deque.size() - 1);
        _sorted_deque.insert(_sorted_deque.begin() + insert_index, _single_odd_element); 
    }
}

int PMergeMeDeque::binary_search(int target, int high) const
{
    int low = 0;

    while (low <= high)
    {
        int middle = low + (high - low) / 2;
        int value = _sorted_deque[middle];

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
void PMergeMeDeque::print_sorted_elements() const
{
    size_t i = 0;
    std::cout << "After:\t";

    while (i < _sorted_deque.size() && i < 4)
    {
        std::cout << _sorted_deque[i] << " ";
        ++i;
    }
    if (i < _sorted_deque.size())
        std::cout << "[...]";

    std::cout << std::endl;
}