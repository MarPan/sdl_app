#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <utility>
#include <map>
#include <vector>
#include <functional>

template <typename Event>
class Notifier
{
public:
  // disclaimer: this is only a slight modification of
  // C++11 Observer pattern from juanchopanzacpp.wordpress.com.
  template <typename Observer>
  void registerObserver(const Event& event, Observer&& observer)
  {
    m_observers[event].push_back(std::forward<Observer>(observer));
  }

  template <typename Observer>
  void registerObserver(Event&& event, Observer&& observer)
  {
    m_observers[std::move(event)].push_back(std::forward<Observer>(observer));
  }

  void notify(const Event& event) const
  {
    if (m_observers.empty())
      return;
    for (const auto& observer : m_observers.at(event))
      observer();
  }

private:
 std::map<Event, std::vector<std::function<void()>>> m_observers;
};

#endif // NOTIFIER_H
