#include "Component.hpp"

int Component::s_CurrentID = 0;

std::ostream &operator <<(std::ostream &stream, const Component &object)
{
    return stream << object.ToString();
}
