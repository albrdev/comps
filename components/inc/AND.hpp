#ifndef _AND_HPP_
#define _AND_HPP_

#include <string>
#include <ostream>
#include "LogicGate2x.hpp"

class AND : public LogicGate2x
{
private:
    friend std::ostream &operator <<(std::ostream &stream, const AND &object);

public:
    bool GetResult(void) const override;

    AND(const bool a, const bool b, const bool autoID = true);
};

#endif // _AND_HPP_
