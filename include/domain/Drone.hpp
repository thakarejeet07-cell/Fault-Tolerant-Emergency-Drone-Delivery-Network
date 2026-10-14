#ifndef DRONE_MESH_DRONE_HPP
#define DRONE_MESH_DRONE_HPP

#include <string>
#include <mutex>
#include <functional>
#include "../../include/domain/Coordinate.hpp"

namespace simulator {
namespace mesh {
namespace domain {

class Mission; // Forward declaration for 0..1 association

class Drone {
public:
    enum class DroneState {
        IDLE,
        EN_ROUTE,
        REROUTING,
        FAULT_RECOVERY
    };

    using FaultCallback = std::function<void(Drone*, Mission*)>;

protected:
    // Accessible by derived classes such as QuadCopter
    std::string droneId;
    Coordinate currentLocation;

private:
    // Strictly encapsulated
    double batteryLevel;
    DroneState state{DroneState::IDLE};
    Mission* currentMission{nullptr};
    FaultCallback faultCallback;

    // Mutex guarding drone internal state, ensuring thread-safe transitions
    mutable std::mutex droneMutex;

    // Helper for state machine transition validation
    static bool isValidTransition(DroneState from, DroneState to);

    // STATIC VARIABLE: one counter shared across every Drone (and every
    // derived QuadCopter), incremented/decremented as objects are built
    // and destroyed, so the fleet size is always known without iterating
    // over the Dispatcher's tracked fleet.
    static int fleetCount;

public:
    // Constructor
    Drone(const std::string& droneId, const Coordinate& startLocation);

    // Destructor: decrements fleetCount
    virtual ~Drone();

    // Prevent copy/move due to mutex and unique drone identity
    Drone(const Drone&) = delete;
    Drone& operator=(const Drone&) = delete;

    // Getters and Setters
    const std::string& getDroneId() const;

    Coordinate getCurrentLocation() const;
    void setCurrentLocation(const Coordinate& loc);

    double getBatteryLevel() const;
    void setBatteryLevel(double level);
    
    DroneState getState() const;
    void setState(DroneState newState);

    // State machine update: returns false on illegal transition
    bool updateState(DroneState newState);

    // Mission association (Drone 0..1 --> Mission)
    Mission* getCurrentMission() const;
    void setCurrentMission(Mission* mission);

    // Fault handling: transitions to FAULT_RECOVERY, releases current mission,
    // notifies Dispatcher via callback, and returns the released Mission*
    Mission* handleFault();

    // Collision avoidance: transitions to REROUTING without touching mission
    bool triggerCollisionAvoidance();

    void setFaultCallback(FaultCallback callback);

    // STATIC FUNCTION: no 'this' pointer, callable as Drone::getFleetCount()
    // even with zero drones in existence.
    static int getFleetCount();

protected:
    // Accessible by child/derived classes
    void drainBattery(double amount);

public:
    // Pure virtual function
    // Makes Drone an abstract class
    virtual void flyTo(const Coordinate& destination) = 0;
};

} // namespace domain
} // namespace mesh
} // namespace simulator

#endif // DRONE_MESH_DRONE_HPP
