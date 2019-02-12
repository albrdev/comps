#ifndef _LOGICGATES_HPP_
#define _LOGICGATES_HPP_

#include <string>
#include <ostream>
#include "Component.hpp"

#ifndef LogicGate1x
class LogicGate1x : public Component
{
private:
    friend std::ostream &operator <<(std::ostream &stream, const LogicGate1x &object);

protected:
    bool m_A = false;

public:
    operator bool() const;

    bool GetA(void) const;
    void SetA(const bool value);

    virtual bool GetResult(void) const = 0;

    virtual std::string ToString(void) const;

    LogicGate1x(const bool a, const bool autoID = true);
};
#endif

#ifndef LogicGate2x
class LogicGate2x : public LogicGate1x
{
protected:
    bool m_B = false;

public:
    bool GetB(void) const;
    void SetB(const bool value);

    LogicGate2x(const bool a, const bool b, const bool autoID = true);
};
#endif

class NOT : public LogicGate1x
{
public:
    bool GetResult(void) const override;

    NOT(const bool a, const bool autoID = true);
};

class OR : public LogicGate2x
{
public:
    bool GetResult(void) const override;

    OR(const bool a, const bool b, const bool autoID = true);
};

class AND : public LogicGate2x
{
public:
    bool GetResult(void) const override;

    AND(const bool a, const bool b, const bool autoID = true);
};

class XOR : public LogicGate2x
{
public:
    bool GetResult(void) const override;

    XOR(const bool a, const bool b, const bool autoID = true);
};

class NOR : public LogicGate2x
{
public:
    bool GetResult(void) const override;

    NOR(const bool a, const bool b, const bool autoID = true);
};

class NAND : public LogicGate2x
{
public:
    bool GetResult(void) const override;

    NAND(const bool a, const bool b, const bool autoID = true);
};

class XNOR : public LogicGate2x
{
public:
    bool GetResult(void) const override;

    XNOR(const bool a, const bool b, const bool autoID = true);
};

#endif // _LOGICGATES_HPP_
