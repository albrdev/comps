#include "LogicGate1x.hpp"
#include <sstream>

bool LogicGate1x::GetA(void) const { return m_A; }
void LogicGate1x::SetA(const bool value) { m_A = value; }

LogicGate1x::operator bool() const { return GetResult(); }

std::string LogicGate1x::ToString(void) const
{
    std::ostringstream oss;
    oss << GetResult();
    return oss.str();
}

LogicGate1x::LogicGate1x(const bool a, const bool autoID) : Component(autoID)
{
    SetA(a);
}

std::ostream& operator <<(std::ostream& stream, const LogicGate1x& object)
{
    return stream << object.ToString();
}
