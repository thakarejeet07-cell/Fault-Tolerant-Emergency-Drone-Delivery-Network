#ifndef DRONE_MESH_DISPATCHER_HPP
#define DRONE_MESH_DISPATCHER_HPP

#include <string>
#include "../../include/domain/Mission.hpp"

namespace simulator {
namespace mesh {
namespace domain {

class Dispatcher {
public:
    // NESTED CLASS:
    // DispatchRecord only ever makes sense in the context of a Dispatcher's
    // bookkeeping, so it lives inside Dispatcher's scope rather than as a
    // free-standing class. Outside this class it must be named
    // Dispatcher::DispatchRecord.
    class DispatchRecord {
    private:
        std::string missionId;
        bool wasPreemptive;

    public:
        DispatchRecord(const std::string& missionId, bool wasPreemptive);

        const std::string& getMissionId() const;
        bool isPreemptive() const;

        void print() const;
    };

    // METHOD OVERLOADING:
    // Standard dispatch using default prioritization
    void dispatchMission(const Mission& mission);

    // METHOD OVERLOADING:
    // Preemptive dispatch for critical emergencies
    void dispatchMission(const Mission& mission, bool preemptActiveDrones);

    // STATIC FUNCTION: total dispatch count across every Dispatcher object
    // that has existed (there's normally only one, but the counter is a
    // class-wide fact, not tied to any single instance).
    static int getTotalDispatches();

private:
    // STATIC VARIABLE: shared across all Dispatcher instances.
    static int totalDispatches;
};

} // namespace domain
} // namespace mesh
} // namespace simulator

#endif // DRONE_MESH_DISPATCHER_HPP
