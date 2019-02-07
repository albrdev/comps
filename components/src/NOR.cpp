#include "NOR.hpp"

bool NOR::GetResult(void) const { return !(m_A || m_B); }

NOR::NOR(const bool a, const bool b, const bool autoID) : LogicGate2x(a, b, autoID) { }
