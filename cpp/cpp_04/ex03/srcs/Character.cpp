#include "Character.hpp"

const std::string Character::M_DEFAULT_NAME = "John Doe";

/*
** ------------------------- Constructors / Overloads --------------------------
*/

// Constructor/destructor
Character::Character(): m_name(M_DEFAULT_NAME) 
{
    initItemsAndGarbage();
}

Character::Character(const std::string& name): m_name(name)
{
    // Check emptiness of name
    if (name.empty())
        m_name = M_DEFAULT_NAME;
    initItemsAndGarbage();
}

Character::Character(const Character& character): m_name(character.getName())
{
    for (int i = 0; i < M_MAX_ITEMS; ++i)
    {
        if (character.m_inventory[i])
            m_inventory[i] = character.m_inventory[i]->clone();
        else
            m_inventory[i] = 0;
    }
    for (int i = 0; i < M_MAX_GARBAGE; ++i)
        m_garbage[i] = 0;
}

Character::~Character() 
{
    for (int i = 0; i < M_MAX_ITEMS; ++i)
    {
        if (m_inventory[i])
            delete m_inventory[i];
    }
    for (int i = 0; i < M_MAX_GARBAGE; ++i)
    {
        if (m_garbage[i])
            delete m_garbage[i];
    }
}

// Operator Overload
Character& Character::operator=(const Character& rhs)
{
    if (this != &rhs)
    {
        m_name = rhs.m_name;
        // Copy items in inventory (delete old one)
        // Doesn't copy garbage collector - waste of performance and no value
        for (int i = 0; i < M_MAX_ITEMS; ++i)
        {
            if (m_inventory[i])
                delete m_inventory[i];
            if (rhs.m_inventory[i])
                m_inventory[i] = rhs.m_inventory[i]->clone();
            else
                m_inventory[i] = 0;
        }
    }
    return *this;
}

/*
** ------------------------- Public member's functions -------------------------
*/
// Members Functions
void Character::equip(AMateria* m)
{
    int i = 0;

    // Find first slot available in inventory
    while (i < M_MAX_ITEMS && m_inventory[i])
    {
        if (m_inventory[i] == m)
        {
            std::cerr << "This item is already equiped.\n";
            return;
        }
        i++;
    }
    
    // Fill inventory if not full
    if (i < M_MAX_ITEMS)
        m_inventory[i] = m;
    else
        fillGarbage(m);
}

void Character::unequip(int idx)
{
    // Check index is not out of bound
    if (idx < 0 && idx >= M_MAX_ITEMS)
        return ;

    if (m_inventory[idx])
    {
        // Save position of materia in garbage collector and unequip it
        fillGarbage(m_inventory[idx]);
        m_inventory[idx] = 0;
    }
}

void Character::use(int idx, ICharacter& target)
{
    // Check index is not out of bound
    if (idx < 0 && idx <= M_MAX_ITEMS)
        return ;

    // Call use function on materia if it exists
    if (m_inventory[idx])
        m_inventory[idx]->use(target);
}

// Accessers
const std::string& Character::getName() const { return m_name; }

/*
** ------------------------- Private Helper's functions ------------------------
*/
void Character::fillGarbage(AMateria* m)
{
    static int  oldest = 0;
    int         i = 0;

    while (m_garbage[i])
        i++;
    
    if (i < M_MAX_GARBAGE)
        m_garbage[i] = m;
    else
    {
        // Delete oldest garbage and replace with new one
        delete m_garbage[oldest];
        m_garbage[oldest] = m;
        ++oldest;
        // Reset oldest if it reaches MAX_GARBAGE
        if (oldest >= M_MAX_GARBAGE)
            oldest = 0;
    }
}

void Character::initItemsAndGarbage()
{
    for (int i = 0; i < M_MAX_ITEMS; ++i)
        m_inventory[i] = 0;
    for (int i = 0; i < M_MAX_GARBAGE; ++i)
        m_garbage[i] = 0;
}