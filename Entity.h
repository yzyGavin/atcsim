/* 
 * File:   Entity.h
 * Author: michael
 *
 * Created on 25. mars 2013, 16:40
 */

#ifndef ENTITY_H
#define	ENTITY_H


#include "Types.h"


// Forward declarations (no header includes) (namespace pollution, build time).
class Airplane;
class Airway;
class Cloud;
class ForbiddenZone;
class Surface;


class Entity {
  
  // Theses classes need access to checkForCollision() private methods.
  friend class Airplane;
  friend class Airway;
  friend class Cloud;
  friend class ForbiddenZone;
  
  // Allow a non-member template to access class internals.
  // Not a member template because it would have to be const or non-const.
  // Used to implement a const and non-const getPosition method.
  template <typename SRC, typename RET>
  friend RET getPositionT(SRC entity, enum PosType posType);
  
public:

  // There is no default constructor.
  Entity() = delete;
  Entity(float cape, unsigned int velocity, Point initialPosition);
  
  // Use the default (member to member) copy ctor and copy assignment operator.
  Entity(const Entity& orig) = default;
  Entity& operator=(const Entity& orig) = default;
  // Use the default (member to member) move ctor and move assignment operator.
  Entity(Entity&& orig) = default;
  Entity& operator=(Entity&& orig) = default;
  
  // Virtual destructor to avoid undefined behaviours if someone tries to
  // delete an object of type IEntity.
  // For exemple : IEntity * obj = new Airplane(...); delete obj;
  // Default : call base class'es destructor and destructors of all members.
  // Do not throw any exception (which is what we want for a dtor).
  virtual ~Entity() noexcept(true) = default;

  // Abstract methods that will have to be defined by subclasses.
  virtual void compute(enum PosType posType, int gameFieldWidth, int gameFieldHeight) = 0;
  virtual void render(Surface& displaySurf) const = 0;
  
  // Redirection method used to implement double dispatching (visitor pattern).
  virtual void checkForCollisionDispatch(Entity& entity,
                                         enum PosType posType) const = 0;
  
  // Reset the simulation attributes.
  void resetSimulation();
  
  // Check if a point is inside an entity.
  virtual bool isInside(Point point, enum PosType posType = realPosition,
                        bool mouse = false) const = 0;
  
  // Get or set if the entity is selected by the user.
  bool getSelected() const;
  void setSelected(bool selected);
  
  // Set the target cape of an entity.
  void setTargetCape(Point point);
  
  // Get or reset entity status (for airplanes).
  const struct AirplaneStatus* getStatus() const;
  void resetStatus();
  
protected:
  
  // Get a (const, non-const) pointer to the entity real or simulated position.
  const struct Point* getPosition(enum PosType posType) const;
  struct Point* getPosition(enum PosType posType);
  
  // Compute the movement of an entity.
  void computeMovement(enum PosType posType);
  
  // Update current cape up to target cape.
  void updateCape();
  
  float currentCape_;      // Current cape.
  float targetCape_;       // Target cape set by the user.
  
  unsigned int velocity_;  // Entity velocity.
  
  Point realPosition_;     // Real entity position on XY plane.
  Point simPosition_;      // Simulated entity position on XY plane.
  
  // Indicates if the airplane is selected by the user.
  bool selected_;
  
  // Airplane status (real and simulated collisions, out status).
  struct AirplaneStatus status_;
  
private:
  
  // Collision handling functions : take different actions based on entity type.
  virtual void checkForCollision(const Airplane* airplane,
                                 enum PosType posType);
  virtual void checkForCollision(const ForbiddenZone* forbiddenZone,
                                 enum PosType posType);
  virtual void checkForCollision(const Airway* airway,
                                 enum PosType posType);
  virtual void checkForCollision(const Cloud* cloud,
                                 enum PosType posType);
  
  // Pi is needed to convert from degrees to gradiants. We could also have used
  // M_PI (defined in math.h) but it's not standard C++, althought POSIX.
  const float pi_;

};


#endif	/* ENTITY_H */

