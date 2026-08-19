# Noun-Verb Analysis for Drone Delivery Network Simulator

## 1. The Four Elimination Filters
During noun extraction, candidate classes are evaluated against these four standard object-oriented filters:
1. **Redundancy (Synonyms):** Nouns that refer to the same concept as another noun.
2. **Irrelevance (Out of Scope):** Nouns that describe concepts outside the software system's boundary, meta-language, or hardware that the software does not model.
3. **Attribute (Property):** Nouns that describe a primitive data type, state, or property belonging to a class rather than an independent entity.
4. **Operation (Action/Method):** Nouns that represent processes, actions, or algorithmic steps which should be modeled as methods or states.

---

## 2. Raw Candidate Extraction

### Extracted Nouns (Candidate Classes)
Architecture, Drone, State Machine, State, Simulation, OS Thread, Worker-Thread Pool, Drone Update, Event, Event Scheduler, Critical Event, Failure, Collision Avoidance, Communication Loss, Emergency Rerouting, Simulator, Node, Central Dispatcher, Mission Reallocation, Prioritization, Organ Transplant Delivery, Lower-priority Mission, Factor, Battery Level, Distance, Payload, Current State, Drone Node, Local State, Flight Status, Fault Handling, Handover, Coordination, Local Safety Decision.

### Extracted Verbs (Candidate Methods)
Maintain, Dedicate, Process, Prioritize, Scale, Isolate, Handle, Occur, Interrupt, Reprioritize, Select, Manage, Negotiate (Noted as explicitly *not* done), Keep, Allow, Remain.

---

## 3. Filter Application & Eliminations

| Discarded Candidate | Filter Applied | Justification |
| :--- | :--- | :--- |
| Architecture | Filter 2 (Irrelevant) | Meta-project description, not a system object. |
| OS Thread | Filter 2 (Irrelevant) | Managed by the OS/Language library; outside domain model. |
| Factor | Filter 2 (Irrelevant) | Vague conversational term. |
| Simulator / Node / Drone Node / Central Dispatcher | Filter 1 (Redundancy) | Synonyms for `Simulation`, `Drone`, and `Dispatcher`. |
| State Machine | Filter 4 (Operation) / Filter 3 | Implementation pattern of how a drone behaves, not a class itself. |
| State / Local State / Current State / Flight Status | Filter 3 (Attribute) | Enum/properties belonging to the `Drone` class. |
| Battery Level / Battery | Filter 3 (Attribute) | Numeric property belonging to `Drone`. |
| Distance | Filter 3 (Attribute) | Calculated float value. |
| Payload | Filter 3 (Attribute) | Property of `Drone` or `Mission`. |
| Drone Update | Filter 4 (Operation) | Represents the action of updating, handled by `Simulation`. |
| Collision Avoidance | Filter 4 (Operation) | An algorithmic behavior (`triggerCollisionAvoidance()`). |
| Emergency Rerouting | Filter 4 (Operation) | A method handled by `Dispatcher`. |
| Mission Reallocation | Filter 4 (Operation) | An action (`reallocateMission()`) performed by `Dispatcher`. |
| Prioritization / Coordination / Fault Handling | Filter 4 (Operation) | System behaviors mapped to class methods. |
| Handover | Filter 4 (Operation) | An action that changes mission ownership. |
| Local Safety Decision | Filter 4 (Operation) | An algorithmic outcome executed by `Drone`. |
| Organ Transplant Delivery | Filter 1 (Redundancy) / Filter 3 | A specific instance/priority-level of a `Mission`. |

---

## 4. Surviving Classes

These nouns survived the filters and represent the core entities of the domain model:

1. **Simulation** (The top-level container/engine)
2. **ThreadPool / WorkerPool** (Manages concurrency mechanics)
3. **EventScheduler** (Manages the timeline and triggers events)
4. **Event** (Abstract concept. Specific types like *Failure*, *Communication Loss*, *Critical Event* will be subclasses)
5. **Dispatcher** (Centralized authority for orchestration)
6. **Mission** (The task being executed, including lower-priority missions)
7. **Drone** (The autonomous node executing missions)

---

## 5. Verb-to-Method Mapping

The verbs from the text map cleanly to responsibilities within the surviving classes:

*   **Process / Prioritize:** Maps to `EventScheduler.processEvents()` and `Dispatcher.prioritizeMissions()`.
*   **Maintain / Manage (State):** Maps to `Drone.updateState()`.
*   **Handle / Reprioritize / Interrupt:** Maps to `Dispatcher.evaluatePreemption()` and `Dispatcher.interruptMission()`.
*   **Select:** Maps to `Dispatcher.selectDrone()`.
