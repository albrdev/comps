#ifndef _COMPONENT_HPP_
#define _COMPONENT_HPP_

#include <string>
#include <ostream>

enum CircuitConnectionType
{
    CCT_INVALID = -1,
    CCT_SERIAL = 0,
    CCT_PARALLEL = 1
};

class Component
{
private:
    friend std::ostream &operator <<(std::ostream &stream, const Component &object);

    static int s_CurrentID;

    int m_ID = -1;

    double m_MaxEffect = 0.0;
    double m_InnerResistance = 0.0;

public:
    int GetID(void) const;
    void SetID(const int value);
    void SetID(void);

    double GetMaxEffect(void) const;
    void SetMaxEffect(const double value);

    double GetInnerResistance(void) const;
    void SetInnerResistance(const double value);

    virtual std::string ToString() const;

    Component(const double maxEffect, const double innerResistance, const bool autoID = true);
    Component(const bool autoID = true);
};

#endif // _COMPONENT_HPP_
