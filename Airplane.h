/* 
 * File:   Airplane.h
 * Author: michael
 *
 * Created on 25. mars 2013, 21:39
 */

#ifndef AIRPLANE_H
#define	AIRPLANE_H


#include <string>

#include "Entity.h"


namespace ATCsim {  // Project ATCsim namespace.


// Forward declarations (no header includes) (namespace pollution, build time).
class Cloud;
class ForbiddenZone;
class Surface;


class Airplane : public Entity {
  
public:
  
  
  
  // Cardinal points from which airplanes enter and quit simulation.
enum CardinalPoints {N, S, E, W};


struct CardinalPoint {
  
  CardinalPoints cardinalPoint;
  
  CardinalPoint(CardinalPoints point) : cardinalPoint(point) {}
  
  Point getPosition() const {
    Point ret;
    switch(cardinalPoint) {
      default:
      case N: ret = Point(359,      0+15); break;
      case S: ret = Point(382,    551-15); break;
      case E: ret = Point(800-15, 470);    break;
      case W: ret = Point(  0+15, 383);    break;
    }
    return ret;
  }
  
  std::string toString() const {
    std::string ret;
    switch(cardinalPoint) {
      default:
      case N: ret = "North"; break;
      case S: ret = "Sud";   break;
      case E: ret = "East";  break;
      case W: ret = "West";  break;
    }
    return ret;
  }
  
};






  // Constructor takes number, identification, altitude, cape, velocity and
  // input / output cardinal points of a new airplane.
  Airplane(unsigned int number, std::string identification, unsigned int
           altitude, float cape, unsigned int velocity,
           CardinalPoint in, CardinalPoint out);
  
  // Use the default (member to member) copy ctor and copy assignment operator.
  Airplane(const Airplane& orig) = default;
  Airplane& operator=(const Airplane& orig) = default;
  // Use the default (member to member) move ctor and move assignment operator.
  Airplane(Airplane&& orig) = default;
  Airplane& operator=(Airplane&& orig) = default;
  
  // Default : call base class'es destructor and destructors of all members.
  // Does not throw any exception (which is what we want for a dtor).
  virtual ~Airplane() noexcept(true) = default;
  
  // Redefinition of virtual methods inherited from Entity class.
  virtual void compute(PosTypes posType, int gameFieldWidth, int gameFieldHeight) final;
  virtual void render(Surface& displaySurf) const final;
  
  // Redirection method used to implement double dispatching (visitor pattern).
  virtual void checkForCollisionDispatch(Entity& entity, PosTypes posType) const final;
  
  // Return the airplane altitude.
  unsigned int getAltitude() const;
  
  // Check if a point is inside an entity.
  virtual bool isInside(Point point, PosTypes posType = realPosition,
                        bool mouse = false) const final;
  
protected:
  
private:
  
  // Airplane number, used to place side panel informations.
  unsigned int number_;
  
  // Airplane specific attributes : flight number and altitude.
  std::string identification_;
  unsigned int altitude_;
  
  // Airplane in and out cardinal points.
  CardinalPoint in_;
  CardinalPoint out_;
  
  // Indicate if the airplane is visible or not.
  bool hidden_;
  
//  std::queue<Point> pastPositions_;
  
  // Collision handling functions : take different actions based on entity type.
  virtual void checkForCollision(const Airplane* airplane,
                                 PosTypes posType) final;
  virtual void checkForCollision(const Cloud* cloud,
                                 PosTypes posType) final;
  virtual void checkForCollision(const Airway* airway,
                                 PosTypes posType) final;
  virtual void checkForCollision(const ForbiddenZone* forbiddenZone,
                                 PosTypes posType) final;
  
  // Print informations about the airplane on the side panel.
  void renderSidePanelInfo(Surface& displaySurf) const;
  
  // Trace a line from the airplane center to an end point.
  void traceLineFromAirplane(Surface& displaySurf, Point endPoint, uint8_t red, uint8_t green, uint8_t blue) const;
  
  // Prohibit default constructor usage.
  // Mark methods that won’t be implemented with '= delete' (C++11).
  Airplane() = delete;
  
};
  

}  // End of project ATCsim namespace.


#endif	/* AIRPLANE_H */

