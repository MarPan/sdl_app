#ifndef STATE_H
#define STATE_H

class State
{
public:
  State();
  virtual ~State();
  virtual void onEnter();
  virtual void onExit();
};

#endif // STATE_H
