#include "NAND.hpp"

bool NAND::GetResult(void) const { return !(m_A && m_B); }

NAND::NAND(const bool a, const bool b, const bool autoID) : LogicGate2x(a, b, autoID) { }
