#ifndef _NOT_HPP_
#define _NOT_HPP_

#include <string>
#include <ostream>
#include "LogicGate1x.hpp"

class NOT : public LogicGate1x
{
private:
    friend std::ostream &operator <<(std::ostream &stream, const NOT &object);

public:
    bool GetResult(void) const override;

    NOT(const bool a, const bool autoID = true);
};

#endif // _NOT_HPP_
