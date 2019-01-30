#include "AND.hpp"

bool AND::GetResult(void) const { return m_A && m_B; }

AND::AND(const bool a, const bool b, const bool autoID) : LogicGate2x(a, b, autoID) { }
