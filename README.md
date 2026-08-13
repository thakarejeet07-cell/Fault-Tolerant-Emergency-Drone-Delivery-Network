#  Fault-Tolerant Emergency Drone Delivery Network Simulator

##  Overview
In emergency response, seconds dictate survival rates. During events such as multi-alarm fires, natural disasters, or sudden cardiac arrests, traditional ground conveyance is frequently delayed by traffic gridlock, damaged infrastructure, or hazardous environments. 

This project is a **Fault-Tolerant Drone Delivery Network Simulator** designed to bypass these ground-level bottlenecks. It models an autonomous drone mesh network that dynamically coordinates the delivery of highly critical payloads—such as blood transfusions, donor organs, Automated External Defibrillators (AEDs), and first-aid supplies—directly to inaccessible locations.

##  The Problem
Operating a swarm of autonomous drones in a crisis zone introduces severe logistical challenges. Drones may lose communication, suffer battery drain, encounter dynamic no-fly zones (like spreading fires), or suddenly need to reroute due to shifting emergency priorities. Managing this requires a robust, self-healing network capable of complex decision-making.

##  System Architecture & Objectives
Our simulator addresses these challenges by modeling a dynamic, priority-driven mesh network. We designed the system to manage multiple concurrent deliveries without the requirement (and risk) of deploying physical drones. 

### Core Features
* **Intelligent Dispatch System:** Automatically assigns the most suitable drone for a task by evaluating distance, battery capacity, payload constraints, and current availability.
* **Dynamic Priority Queueing:** Deliveries are triaged based on urgency. For example, a drone carrying an AED for a cardiac arrest will dynamically preempt a drone delivering standard first-aid supplies.
* **Autonomous Rerouting & Fault Tolerance:** The network reacts to real-time hazards. If a fire expands into a drone's flight path, or a node fails mid-flight, the system automatically recalculates the route or hands the task off to a healthy relay drone.
* **Real-Time Telemetry & Simulation:** Users can visually monitor the live state of the swarm (Idle, Assigned, Flying, Returning, Charging). 

##  Simulation Analytics
The primary purpose of this system is to stress-test routing and prioritization algorithms. Through the simulation, users can extract vital metrics, including:
* Average delivery latency and priority adherence.
* Drone utilization rates and battery degradation.
* The cascading effects of hardware failure or environmental hazards on the overall network.

By simulating these variables, this system demonstrates how a decentralized drone fleet can coordinate, adapt to chaos, and guarantee the delivery of life-saving resources when traditional logistics fail.
