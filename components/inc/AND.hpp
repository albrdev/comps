#ifndef _AND_HPP_
#define _AND_HPP_

#include <string>
#include <ostream>
#include "LogicGate2x.hpp"

class AND : public LogicGate2x
{
public:
    bool GetResult(void) const override;

    AND(const bool a, const bool b, const bool autoID = true);
};

#endif // _AND_HPP_
