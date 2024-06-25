/*
** ----------------------- Constructors / Destructor ---------------------------
*/
template <typename T>
Array<T>::Array() 
{
    m_array = 0;
    m_size = 0;
}

template <typename T>
Array<T>::Array(unsigned int n) 
{
    m_size = n;
    m_array = new T[n]();
}

template <typename T>
Array<T>::Array(const Array& array)
{
    m_size = array.size();
    m_array = new T[m_size]();
    for (unsigned int i = 0; i < m_size; ++i)
        m_array[i] = array[i];
}

template <typename T>
Array<T>::~Array() 
{
    delete[] m_array;
}

/*
** --------------------------- Operators overload ------------------------------
*/
template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& rhs)
{
    if (this != &rhs)
    {
        delete[] m_array;
        m_size = rhs.size();
        m_array = new T[m_size]();
        for (unsigned int i = 0; i < m_size; ++i)
            m_array[i] = rhs[i];
    }
    return *this;
}

template <typename T>
T& Array<T>::operator[](unsigned int index)
{
    if (index < m_size)
        return m_array[index];
    else
        throw std::out_of_range("Try to access array outside boundaries");
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const
{
    if (index < m_size)
        return m_array[index];
    else
        throw std::out_of_range("Try to access array outside boundaries");
}

/*
** --------------------------- Helper Function ---------------------------------
*/
template <typename T>
unsigned int Array<T>::size() const { return m_size; }

template <typename T>
void Array<T>::print() const
{
    for (unsigned int i = 0; i < m_size; ++i)
        std::cout << m_array[i] << ' ';
    std::cout << "\n";
}