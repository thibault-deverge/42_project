#include "Span.hpp"

/*
** ------------------------ Constructors / Destructor --------------------------
*/
// Constructors
Span::Span()
{
    m_data.reserve(M_DEFAULT_CAPACITY);
} 

Span::Span(int n)
{
    if (n <= 0)
        throw std::out_of_range("Capacity of the datas should be > 0");
    m_data.reserve(n);
} 

Span::Span(const Span& other)
{
    *this = other;
}

// Destructor
Span::~Span() {}

// Operator overload
Span& Span::operator=(const Span& rhs)
{
    if (this != &rhs)
        m_data = rhs.m_data;
    return *this;
}

/*
** ------------------------- Public Member functions ---------------------------
*/
// Add numbers
void Span::addNumber(int n)
{
    if (m_data.size() < m_data.capacity())
        m_data.push_back(n);
    else
        throw std::out_of_range("Max capacity of data is reached already.");
}

void Span::addNumbers(vector_it begin, vector_it end)
{
    size_t size_numbers = std::distance(begin, end);
    
    if (size_numbers > m_data.capacity())
        throw std::out_of_range("Dataset is not big enough to receive this chunk of numbers.");
    m_data.insert(m_data.begin(), begin, end);
}

// Find spans
int Span::shortestSpan() const
{
    // Throw exception if the dataset size is insufficient
    if (m_data.size() <= 1)
        throw std::length_error("Span is empty or only contains one element.");
    
    std::vector<int>    copy_data(m_data);
    int                 min_span = std::numeric_limits<int>::max();

    // Sort dataset and loop through elements to find the smallest difference
    std::sort(copy_data.begin(), copy_data.end());
    for (size_t i = 1; i < copy_data.size(); ++i)
    {
        int curr_span = copy_data[i] - copy_data[i-1];
        if (curr_span < min_span)
            min_span = curr_span;
    }
    return min_span;
}

int Span::longestSpan() const
{
    // Throw exception if the dataset size is insufficient
    if (m_data.size() <= 1)
        throw std::length_error("Span is empty or only contains one element.");

    const_vector_it min = min_element(m_data.begin(), m_data.end());
    const_vector_it max = max_element(m_data.begin(), m_data.end());
    return *max - *min;
}

/*
** ------------------------- Private Helper functions --------------------------
*/
void Span::printData() const
{
    std::cout << "------ DATA: ------\n";
    for (size_t i = 0; i < m_data.size(); ++i)
    {
        std::cout << m_data[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "-\n";
}