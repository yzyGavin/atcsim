/* 
 * File:   Airways.h
 * Author: michael
 *
 * Created on 23. mai 2013, 00:32
 */

#ifndef AIRWAYS_H
#define	AIRWAYS_H


#include "Polygon.h"


namespace ATCsim {  // Project ATCsim namespace.


class Airway : public Polygon {
  
public:
  
  // Constructor takes x and y coordinates of a new airway.
  Airway(const std::vector<int16_t>& xPoints,
         const std::vector<int16_t>& yPoints);
  
  // Use the default (member to member) copy ctor and copy assignment operator.
  Airway(const Airway& orig) = default;
  Airway& operator=(const Airway& orig) = default;
  // Use the default (member to member) move ctor and move assignment operator.
  Airway(Airway&& orig) = default;
  Airway& operator=(Airway&& orig) = default;
  
  // Default : call base class'es destructor and destructors of all members.
  // Does not throw any exception (which is what we want for a dtor).
  virtual ~Airway() noexcept(true) = default;
  
  // Redeclaration of virtual methods inherited from Entity class.
  virtual void compute(PosTypes posType, int gameFieldWidth, int gameFieldHeight) final;
  
  // Redirection method used to implement double dispatching (visitor pattern).
  virtual void checkForCollisionDispatch(Entity& entity, PosTypes posType) const final;
  
protected:
  
private:

  // Prohibit default constructor usage.
  // Mark methods that won’t be implemented with '= delete' (C++11).
  Airway() = delete;
  
};
  

}  // End of project ATCsim namespace.


#endif	/* AIRWAYS_H */

