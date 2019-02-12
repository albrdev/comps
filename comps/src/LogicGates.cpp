#include "LogicGates.hpp"
#include <sstream>

#ifndef LogicGate1x
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
#endif

#ifndef LogicGate2x
bool LogicGate2x::GetB(void) const { return m_B; }
void LogicGate2x::SetB(const bool value) { m_B = value; }

LogicGate2x::LogicGate2x(const bool a, const bool b, const bool autoID) : LogicGate1x(a, autoID)
{
    SetB(b);
}
#endif

class NOT;
class OR;
class AND;
class XOR;
class NOR;
class NAND;
class XNOR;

bool NOT::GetResult(void) const { return !m_A; }
NOT::NOT(const bool a, const bool autoID) : LogicGate1x(a, autoID) { }

bool OR::GetResult(void) const { return m_A || m_B; }
OR::OR(const bool a, const bool b, const bool autoID) : LogicGate2x(a, b, autoID) { }

bool AND::GetResult(void) const { return m_A && m_B; }
AND::AND(const bool a, const bool b, const bool autoID) : LogicGate2x(a, b, autoID) { }

bool XOR::GetResult(void) const { return AND(NAND(m_A, m_B), OR(m_A, m_B)); }
XOR::XOR(const bool a, const bool b, const bool autoID) : LogicGate2x(a, b, autoID) { }

bool NOR::GetResult(void) const { return NOT(OR(m_A, m_B)); }
NOR::NOR(const bool a, const bool b, const bool autoID) : LogicGate2x(a, b, autoID) { }

bool NAND::GetResult(void) const { return NOT(AND(m_A, m_B)); }
NAND::NAND(const bool a, const bool b, const bool autoID) : LogicGate2x(a, b, autoID) { }

bool XNOR::GetResult(void) const { return NOT(XOR(m_A, m_B)); }
XNOR::XNOR(const bool a, const bool b, const bool autoID) : LogicGate2x(a, b, autoID) { }
