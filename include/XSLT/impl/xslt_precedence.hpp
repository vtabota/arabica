#ifndef ARABICA_XSLT_PRECEDENCE_HPP
#define ARABICA_XSLT_PRECEDENCE_HPP

class Precedence
{
public:
  static const Precedence& InitialPrecedence()
  {
    static Precedence initial_(0);
    return initial_;
  } // Precedence

  static const Precedence& FrozenPrecedence()
  {
    static Precedence frozen_(-1);
    return frozen_;
  } // Precedence

  Precedence() : 
    precedence_()
  { 
    //precedence_.push_back(0);
  } // Precedence

  Precedence(const Precedence& rhs) : 
    precedence_(rhs.precedence_)
  { 
  } // Precedence

private:
  //Precedence(const std::vector<int> precedence) : 
  Precedence(int precedence) : 
    precedence_(precedence)
  {
  } // Precedence

public:
  ~Precedence() { }

  bool operator==(const Precedence& rhs) const 
  { 
    return precedence_ == rhs.precedence_;
  } // operator==

  bool operator>(const Precedence& rhs) const
  {
    return precedence_ > rhs.precedence_;
  } // operator>

  Precedence& operator=(const Precedence& rhs) 
  { 
    //std::vector<int> other(rhs.precedence_);
    //precedence_.swap(other);
    precedence_ = rhs.precedence_;
    return *this;
  } // operator=

  Precedence nextGeneration(int p) const
  {
    Precedence next(p);
    //Precedence next(precedence_);
    //next.precedence_.push_back(p);
    return next;
  } // nextGeneration

private:
  // std::vector<int> precedence_;  
  int precedence_;

  friend bool operator<(const Precedence& lhs, const Precedence& rhs);
}; // class Precedence

bool operator<(const Precedence& lhs, const Precedence& rhs)
{
  return lhs.precedence_ < rhs.precedence_;
} // PrecedenceCompare

class PrecedenceStack
{
public:
  PrecedenceStack() :
    stack_()
  {
    stack_.push(Precedence::InitialPrecedence());
  } // PrecedenceStack

  PrecedenceStack(const PrecedenceStack& rhs) : 
    stack_(rhs.stack_)
  {
  } // PrecedenceStack

  const Precedence& top() const { return stack_.top(); }
  void push() { stack_.push(top().nextGeneration(count_++)); }
  void pop() { stack_.pop(); }
  void freeze() 
  { 
    while(!stack_.empty())
      stack_.pop();
    stack_.push(Precedence::FrozenPrecedence());
  } // freeze

private:
  std::stack<Precedence> stack_;
  static int count_;
}; // class PrecedenceStack

int PrecedenceStack::count_ = 0;
#endif
