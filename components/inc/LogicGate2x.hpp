#ifndef _LOGICGATE2X_HPP_
#define _LOGICGATE2X_HPP_

#include <string>
#include <ostream>
#include "LogicGate1x.hpp"

class LogicGate2x : public LogicGate1x
{
private:
    friend std::ostream &operator <<(std::ostream &stream, const LogicGate2x &object);

protected:
    bool m_B = false;

public:
    bool GetB(void) const;
    void SetB(const bool value);

    LogicGate2x(const bool a, const bool b, const bool autoID = true);
};

#endif // _LOGICGATE2X_HPP_
