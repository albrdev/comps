#include "OR.hpp"

bool OR::GetResult(void) const { return m_A || m_B; }

OR::OR(const bool a, const bool b, const bool autoID) : LogicGate2x(a, b, autoID) { }
