#include "Component.hpp"

int Component::s_CurrentID = -1;

std::ostream &operator <<(std::ostream &stream, const Component &object)
{
    return stream << object.ToString();
}

int Component::GetID(void) const { return m_ID; }
void Component::SetID(const int value) { m_ID = value; }
void Component::SetID(void)
{
    if(m_ID >= 0)
        return;

    m_ID = ++s_CurrentID;
}

double Component::GetMaxEffect(void) const { return m_MaxEffect; }
void Component::SetMaxEffect(const double value) { m_MaxEffect = value; }

double Component::GetInnerResistance(void) const { return m_InnerResistance; }
void Component::SetInnerResistance(const double value) { m_InnerResistance = value; }

std::string Component::ToString() const { return typeid(this).name(); }

Component::Component(const double maxEffect, const double innerResistance, bool autoID) : Component(autoID)
{
    SetMaxEffect(maxEffect);
    SetInnerResistance(innerResistance);
}

Component::Component(bool autoID)
{
    if(autoID)
        SetID();
}
