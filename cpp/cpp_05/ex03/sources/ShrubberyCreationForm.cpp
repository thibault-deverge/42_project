#include "ShrubberyCreationForm.hpp"

const std::string ShrubberyCreationForm::M_NAME = "Shrubbery Creation";

/*
** ------------------------- Private Member Functions --------------------------
*/
void ShrubberyCreationForm::drawAsciiTree(std::ostream& file) const
{
    std::string indent = "  ";
    
    file << indent + "        # #### ####\n";
    file << indent + "      ### \\/#|### |/####\n";
    file << indent + "     ##\\/ #/ \\||/##_/# ##/_#\n";
    file << indent + "   ###  \\/###|/ \\/ # ###\n";
    file << indent + " ##_\\_\\#\\_# ## | #/###_/_####\n";
    file << indent + "## #### # \\ #| /  #### ##/##\n";
    file << indent + " __#_--###`  |{,###---###-~\n";
    file << indent + "           \\ }{\n";
    file << indent + "            }}{\n";
    file << indent + "            }}{\n";
    file << indent + "       ejm  {{}\n";
    file << indent + "      , -=-~{ .-^- _\n";
}
/*

** ------------------------- Constructors / Overloads --------------------------
*/
// Constructors / Destructor

ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm(M_NAME, "", MIN_SIGN, MIN_EXE) {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm(M_NAME, target, MIN_SIGN, MIN_EXE) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& form)
    : AForm(form) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

/*
** ------------------------- Public Member Functions ---------------------------
*/
// Member functions
void ShrubberyCreationForm::action() const
{
    std::string filename;
    filename = getTarget() + "_shrubbery";

    std::ofstream file(filename.c_str());
    if (file.fail() || file.bad())
        throw std::runtime_error("Unable to open file");

    drawAsciiTree(file);
    std::cout << "A file have been created: " << filename << std::endl;
    file.close();
}
