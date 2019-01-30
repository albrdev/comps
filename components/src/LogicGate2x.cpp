#include "LogicGate2x.hpp"

bool LogicGate2x::GetB(void) const { return m_B; }
void LogicGate2x::SetB(const bool value) { m_B = value; }

LogicGate2x::LogicGate2x(const bool a, const bool b, const bool autoID) : LogicGate1x(a, autoID)
{
    SetB(b);
}
