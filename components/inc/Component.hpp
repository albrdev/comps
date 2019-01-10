#ifndef _COMPONENT_HPP_
#define _COMPONENT_HPP_

class Component
{
private:
    static int s_CurrentID;

    int m_ID;

    double m_Resistance;
    double m_MaxEffect;

public:
    double GetResistance(void) const { return m_Resistance; }
    void SetResistance(const double value) { m_Resistance = value; }

    double GetMaxEffect(void) const { return m_MaxEffect; }
    void SetMaxEffect(const double value) { m_MaxEffect = value; }

    Component(const double resistance, const double maxEffect)
    {
        m_Resistance = resistance;
        m_MaxEffect = maxEffect;

        m_ID = s_CurrentID;
        s_CurrentID++;
    }
};

#endif // _COMPONENT_HPP_
