#ifndef _XNOR_HPP_
#define _XNOR_HPP_

#include "LogicGate2x.hpp"

class XNOR : public LogicGate2x
{
public:
    bool GetResult(void) const override;

    XNOR(const bool a, const bool b, const bool autoID = true);
};

#endif // _XNOR_HPP_
