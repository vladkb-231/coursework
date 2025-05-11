#include "matchevent.h"

MatchEvent::MatchEvent(EventType type)
    : m_type(type)
{}

MatchEvent::EventType MatchEvent::type() const {
    return m_type;
}
