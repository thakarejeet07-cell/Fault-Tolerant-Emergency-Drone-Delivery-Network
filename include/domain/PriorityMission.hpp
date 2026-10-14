#ifndef DRONE_MESH_PRIORITY_MISSION_HPP
#define DRONE_MESH_PRIORITY_MISSION_HPP

#include "../../include/domain/Mission.hpp"

namespace simulator {
namespace mesh {
namespace domain {

// PriorityMission adds an escalation tier on top of a standard Mission
// (e.g. the Tier 0 "Override Priority Queue" use case). It is deliberately
// NOT 'final' -- unlike QuadCopter, further specialization here is
// plausible (an OrganTransplantMission, say), so nothing blocks it.
class PriorityMission : public Mission {
private:
    int priorityTier;
    std::string escalationReason;

public:
    PriorityMission(
        const std::string& missionId,
        int priorityTier,
        const std::string& escalationReason
    );

    int getPriorityTier() const;
    const std::string& getEscalationReason() const;

    // Overrides Mission::printDetails(). This override is only ever reached
    // through a PriorityMission (or a reference/pointer to one) -- a Mission
    // that was copied BY VALUE from a PriorityMission loses this override,
    // because it stops being a PriorityMission at all. See
    // demonstrateObjectSlicing() below.
    void printDetails() const override;
};

// OBJECT SLICING DEMO:
// Free function declared here, defined in PriorityMission.cpp, that builds
// a PriorityMission and shows what happens when it is copied into a plain
// Mission by value.
void demonstrateObjectSlicing();

} // namespace domain
} // namespace mesh
} // namespace simulator

#endif // DRONE_MESH_PRIORITY_MISSION_HPP
