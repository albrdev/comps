#ifndef _COMPONENT_HPP_
#define _COMPONENT_HPP_

#include <string>
#include <ostream>

enum CircuitConnectionType
{
    CCT_SERIAL = 1,
    CCT_PARALLEL = 2
};

class Component
{
private:
    friend std::ostream &operator <<(std::ostream &stream, const Component &object);

    static int s_CurrentID;

    int m_ID;

    double m_MaxEffect = 0.0;
    double m_InnerResistance = 0.0;

public:
    double GetMaxEffect(void) const { return m_MaxEffect; }
    void SetMaxEffect(const double value) { m_MaxEffect = value; }

    virtual std::string ToString() const { return typeid(this).name(); }

    Component(const double maxEffect, const double innerResistance, bool autoID = true) : Component(autoID)
    {
        m_MaxEffect = maxEffect;
        m_InnerResistance = innerResistance;
    }

    Component(bool autoID = true)
    {
        m_ID = autoID ? s_CurrentID++ : -1;
    }
};

#endif // _COMPONENT_HPP_
