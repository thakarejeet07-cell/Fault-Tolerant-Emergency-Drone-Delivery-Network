# System Use Cases: Fault-Tolerant Emergency Drone Delivery Network Simulator

This document outlines the core system interactions, actor boundaries, and fault-tolerance edge cases for the emergency drone routing simulator. It strictly defines the boundaries between external triggers and internal system logic.

---

## 1. Actor Taxonomy

### Primary Actors (Initiators)
These entities sit *outside* the system boundary and trigger use cases.
* **Simulation Engineer:** Responsible for the initial setup. Configures the network topology, drone specifications, and the stochastic probabilities for the internal hazard engine.
* **Emergency Dispatcher:** A human operator who interacts with the live simulation. Injects manual delivery requests, monitors active flight paths, and overrides the priority queue when real-world conditions escalate.
* **External Emergency Request System (EERS):** An external, automated dispatch API (e.g., an automated hospital network) that pushes delivery requests and payload parameters into the simulator's intake queue without human prompting.

### Secondary Actors (Service Providers / Receivers)
These entities sit *outside* the system boundary. The simulator interacts with them to complete a use case.
* **GIS / Topography Provider:** An external geographic database that the system queries during setup to load the operational map, valid airspaces, and static obstacles.
* **Receiving Node (Ground Responder):** The final destination entity (e.g., a field medic or hospital receiver) that the system interacts with to confirm a successful payload handover and validate payload integrity (e.g., organ temperature).

---

## 2. Core Use Case Map

### Phase 1: Configuration & Initialization
* **UC1: Configure Network Topology** (Primary: Simulation Engineer)
* **UC2: Load Spatial Environment** (Secondary: GIS Provider) — *<<include>>d in UC1*

### Phase 2: Dispatch & Queue Management
* **UC3: Submit Delivery Request** (Primary: Dispatcher, EERS)
* **UC4: Assign Payload Priority Tier** (System internal) — *<<include>>d in UC3*
* **UC5: Override Priority Queue** (Primary: Dispatcher) — *<<extend>>s UC3*

### Phase 3: Execution (The Simulation Loop)
* **UC6: Request Live Telemetry Stream** (Primary: Dispatcher)
* **UC7: Confirm Payload Handover** (Secondary: Receiving Node) — *Triggered upon drone reaching target*

---