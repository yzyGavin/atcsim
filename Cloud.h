/* 
 * File:   Cloud.h
 * Author: michael
 *
 * Created on 26. mars 2013, 16:44
 */

#ifndef CLOUD_H
#define	CLOUD_H


#include "Polygon.h"


class Cloud : public Polygon {
  
public:
  
  // There is no default constructor.
  Cloud() = delete;
  Cloud(const std::vector<int16_t>& xPoints, const std::vector<int16_t>& yPoints,
        float cape, unsigned int velocity);
  
  // Use the default (member to member) copy ctor and copy assignment operator.
  Cloud(const Cloud& orig) = default;
  Cloud& operator=(const Cloud& orig) = default;
  // Use the default (member to member) move ctor and move assignment operator.
  Cloud(Cloud&& orig) = default;
  Cloud& operator=(Cloud&& orig) = default;
  
  // Default : call base class'es destructor and destructors of all members.
  // Do not throw any exception (which is what we want for a dtor).
  virtual ~Cloud() noexcept(true) = default;
    
  // Redeclaration of virtual methods inherited from Entity class.
  virtual void compute(enum PosType posType, int gameFieldWidth, int gameFieldHeight) final;
  
  // Redirection method used to implement double dispatching (visitor pattern).
  virtual void checkForCollisionDispatch(Entity& entity, enum PosType posType) const final;
  
protected:
  
private:

};

#endif	/* CLOUD_H */

