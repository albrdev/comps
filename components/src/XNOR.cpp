#include "XNOR.hpp"

bool XNOR::GetResult(void) const { return !(m_A ^ m_B); }

XNOR::XNOR(const bool a, const bool b, const bool autoID) : LogicGate2x(a, b, autoID) { }
