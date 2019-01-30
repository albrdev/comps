#ifndef _LOGICGATE1X_HPP_
#define _LOGICGATE1X_HPP_

#include <string>
#include <ostream>
#include "Component.hpp"

class LogicGate1x : public Component
{
private:
    friend std::ostream &operator <<(std::ostream &stream, const LogicGate1x &object);

protected:
    bool m_A = false;

public:
    bool GetA(void) const;
    void SetA(const bool value);

    virtual bool GetResult(void) const = 0;

    LogicGate1x(const bool a, const bool autoID = true);
};

#endif // _LOGICGATE1X_HPP_
