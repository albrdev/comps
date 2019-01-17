#ifndef _COMPONENT_HPP_
#define _COMPONENT_HPP_

class Component
{
private:
    static int s_CurrentID;

    int m_ID;

    double m_MaxEffect;

public:
    double GetMaxEffect(void) const { return m_MaxEffect; }
    void SetMaxEffect(const double value) { m_MaxEffect = value; }

    Component(const double maxEffect, bool autoID = true)
    {
        m_MaxEffect = maxEffect;

        m_ID = autoID ? s_CurrentID++ : -1;
    }
};

#endif // _COMPONENT_HPP_
