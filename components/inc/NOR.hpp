#ifndef _NOR_HPP_
#define _NOR_HPP_

#include "LogicGate2x.hpp"

class NOR : public LogicGate2x
{
public:
    bool GetResult(void) const override;

    NOR(const bool a, const bool b, const bool autoID = true);
};

#endif // _NOR_HPP_
