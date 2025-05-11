#ifndef MATCHEVENT_H
#define MATCHEVENT_H

class MatchEvent {
public:
    enum class EventType {
        Serve,
        Attack,
        Block,
        Fault,
        // Добавь нужные типы
    };

    explicit MatchEvent(EventType type);
    EventType type() const;

private:
    EventType m_type;
};

#endif // MATCHEVENT_H
