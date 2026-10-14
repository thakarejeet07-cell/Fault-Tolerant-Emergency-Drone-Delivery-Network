#ifndef DRONE_MESH_QUADCOPTER_HPP
#define DRONE_MESH_QUADCOPTER_HPP

#include "../../include/domain/Drone.hpp"

namespace simulator {
namespace mesh {
namespace domain {

// FINAL:
// QuadCopter is a concrete leaf in the Drone hierarchy. Marking the class
// 'final' means nobody can write "class HeavyLiftQuadCopter : public
// QuadCopter" -- it's a compile error. This also lets the compiler
// devirtualize/inline calls made through a QuadCopter type, since it knows
// no further override of flyTo() can exist.
class QuadCopter final : public Drone {
public:
    QuadCopter(const std::string& droneId, const Coordinate& startLocation);

    // 'override' checks this really does override Drone's pure virtual;
    // 'final' additionally forbids any further override. It's redundant
    // with the class-level 'final' above (nothing can derive from
    // QuadCopter anyway) but is included to show the method-level syntax.
    void flyTo(const Coordinate& destination) override final;
};

} // namespace domain
} // namespace mesh
} // namespace simulator

#endif // DRONE_MESH_QUADCOPTER_HPP
