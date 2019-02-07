#include "XOR.hpp"

bool XOR::GetResult(void) const { return m_A ^ m_B; }

XOR::XOR(const bool a, const bool b, const bool autoID) : LogicGate2x(a, b, autoID) { }
