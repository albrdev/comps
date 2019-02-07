#ifndef _NAND_HPP_
#define _NAND_HPP_

#include "LogicGate2x.hpp"

class NAND : public LogicGate2x
{
public:
    bool GetResult(void) const override;

    NAND(const bool a, const bool b, const bool autoID = true);
};

#endif // _NAND_HPP_
