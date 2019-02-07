#ifndef _OR_HPP_
#define _OR_HPP_

#include <string>
#include <ostream>
#include "LogicGate2x.hpp"

class OR : public LogicGate2x
{
public:
    bool GetResult(void) const override;

    OR(const bool a, const bool b, const bool autoID = true);
};

#endif // _OR_HPP_
