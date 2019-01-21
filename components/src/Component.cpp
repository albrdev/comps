#include "Component.hpp"

int Component::s_CurrentID = 0;

std::ostream &operator <<(std::ostream &stream, const Component &object)
{
    return stream << object.ToString();
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
    m_ID = autoID ? s_CurrentID++ : -1;
}
