#ifndef DRONE_MESH_MISSION_HPP
#define DRONE_MESH_MISSION_HPP

#include <string>

namespace simulator {
namespace mesh {
namespace domain {

class Mission {
private:
    std::string missionId;

    // STATIC VARIABLE: shared by every Mission instance, not per-object.
    // Tracks how many Mission objects have ever been constructed in the
    // simulation (base-class constructions only; PriorityMission counts too,
    // since its constructor delegates to this one).
    static int missionsCreated;

public:
    // Constructor
    Mission(const std::string& missionId);

    // Virtual destructor: required now that Mission is used polymorphically
    // (see PriorityMission), so that destroying a derived object through a
    // Mission* cleans up correctly.
    virtual ~Mission() = default;

    // Getter
    const std::string& getMissionId() const;

    // Virtual on purpose: PriorityMission overrides this. It is what makes
    // the object-slicing demo in PriorityMission.cpp meaningful -- a sliced
    // object always calls THIS version, never the derived one.
    virtual void printDetails() const;

    // STATIC FUNCTION: callable as Mission::getMissionsCreated(), no object
    // required, since it only touches the static variable above.
    static int getMissionsCreated();
};

} // namespace domain
} // namespace mesh
} // namespace simulator

#endif // DRONE_MESH_MISSION_HPP
