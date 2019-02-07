#ifndef _NOT_HPP_
#define _NOT_HPP_

#include "LogicGate1x.hpp"

class NOT : public LogicGate1x
{
public:
    bool GetResult(void) const override;

    NOT(const bool a, const bool autoID = true);
};

#endif // _NOT_HPP_
