# CRC Cards: Drone Delivery Network Simulator

## Overview
This document contains the Class-Responsibility-Collaborator (CRC) cards for the core domain classes of the Fault-Tolerant Emergency Drone Delivery Network Simulator.

---

### Class: Simulation
| Responsibilities | Collaborators |
| :--- | :--- |
| Initializes the system environment and system parameters. | `EventScheduler` |
| Starts, pauses, and terminates the main execution loop. | `ThreadPool` |
| Bootstraps the initial state of the grid and the drone fleet. | `Dispatcher` |

---

### Class: ThreadPool
| Responsibilities | Collaborators |
| :--- | :--- |
| Manages the lifecycle of a fixed pool of OS worker threads. | `EventScheduler` |
| Fetches the next available event from the scheduler. | `Event` |
| Executes the `process()` logic of dispatched events concurrently. | |

---

### Class: EventScheduler
| Responsibilities | Collaborators |
| :--- | :--- |
| Maintains the thread-safe Priority Queue of future events. | `Event` |
| Sorts events based on their simulation timestamp (min-heap). | `ThreadPool` |
| Inserts new events generated during simulation execution. | `Simulation` |
| Pops the highest-priority/earliest event to feed the ThreadPool. | |

---

### Class: Event (Abstract)
| Responsibilities | Collaborators |
| :--- | :--- |
| Encapsulates the timestamp of when an action occurs. | `Drone` (for drone events) |
| Defines a pure virtual `execute()` method for subclasses. | `Dispatcher` (for dispatch events) |
| Stores the priority level of the event itself. | |

---

### Class: Dispatcher
| Responsibilities | Collaborators |
| :--- | :--- |
| Maintains the global list of all pending and active missions. | `Mission` |
| Evaluates incoming emergencies for preemption/interruption. | `Drone` |
| Selects the optimal available drone based on distance and battery. | `EventScheduler` |
| Reallocates missions when a drone experiences a critical fault. | |

---

### Class: Mission
| Responsibilities | Collaborators |
| :--- | :--- |
| Encapsulates task data: pickup/drop-off coordinates, payload type. | (Passed as a data object; primarily manipulated by `Dispatcher` and `Drone`) |
| Tracks the priority level (e.g., organ transplant vs. standard). | |
| Maintains mission lifecycle status (Pending, Active, Completed, Aborted).| |

---

### Class: Drone
| Responsibilities | Collaborators |
| :--- | :--- |
| Maintains local telemetry data (battery level, current coordinates). | `Mission` |
| Updates its own internal state machine (`IDLE`, `EN_ROUTE`, etc.). | `EventScheduler` |
| Executes collision avoidance and local fault recovery logic. | |
| Generates new status or fault events and posts them to the timeline. | |