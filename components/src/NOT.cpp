#include "NOT.hpp"

bool NOT::GetResult(void) const { return !m_A; }

NOT::NOT(const bool a, const bool autoID) : LogicGate1x(a, autoID) { }
