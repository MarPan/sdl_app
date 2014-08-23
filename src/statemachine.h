#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <type_traits>

template <class T>
class StateMachine
{
public:
  // this mojo ensures that one cannot create StateMachine with types with consts  or references,
  typedef typename ::std::remove_reference< typename ::std::remove_cv< T >::type >::type state_type;

  StateMachine()
  : m_state(nullptr)
  { }

protected:
  inline void setState( const state_type& state );
  inline state_type getState() const;

private:
  state_type m_state;
};

template < class T >
inline void StateMachine<T>::setState( const typename StateMachine<T>::state_type& state )
{
  if (m_state) {
//    m_state->onExit();
    delete m_state;
  }
  m_state = state;
//  m_state->onEnter(*this);
}

template < class T >
inline typename StateMachine<T>::state_type StateMachine<T>::getState() const
{
    return m_state;
}


#endif // STATEMACHINE_H
