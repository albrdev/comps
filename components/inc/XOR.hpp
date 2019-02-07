#ifndef _XOR_HPP_
#define _XOR_HPP_

#include <string>
#include <ostream>
#include "LogicGate2x.hpp"

class XOR : public LogicGate2x
{
public:
    bool GetResult(void) const override;

    XOR(const bool a, const bool b, const bool autoID = true);
};

#endif // _XOR_HPP_
