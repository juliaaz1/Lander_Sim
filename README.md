# Lander_Sim
# NASA SpaceX Lander Simulator Readme

This project implements an interface that allows control of a set of space landers attempting to land on a newly discovered planet. Each lander is managed by a central tower on Earth and a simulator that controls the thrusters of each lander to ensure safe landings.

## Lander.h Contents

### 1. Lander Class

The `lander` class represents individual space landers and provides methods for accessing and manipulating their attributes. Here are the key attributes and methods of the `lander` class:

- `flow_rate`: Throttle percentage for the thrusters.
- `velocity`: Velocity of the lander.
- `altitude`: Altitude (height) from the surface.
- `fuel_amount`: Amount of fuel in the tank for the lander.
- `stillLanding`: Boolean indicating whether the lander is still airborne.
- `id`: Unique identifier for the lander.
- `timesSimulated`: Counter denoting the number of times the lander has been processed.
- `LANDER_MASS`: Mass of the lander.
- `MAX_FUEL_CONSUMPTION_RATE`: Maximum amount of fuel that can be burned for each activation of the thrusters.
- `MAX_THRUST`: Maximum thrust the thrusters can exert.

Additionally, the `lander` class provides methods for:
1. Retrieving information about the lander (`get_velocity()`, `get_altitude()`, `get_fuel_amount()`, `get_id()`, `get_mass()`, `get_status()`).
2. Simulating its movement (`change_flow_rate()`, `simulate()`). The `operator?` is also implemented to compare the priority of two lander objects for use in a priority queue.

### 2. Priority Queue Class

The `priorityQ` class implements a priority queue for storing and managing lander objects. Here are the key attributes and methods of the `priorityQ` class: The `priorityQ` class is truly templated to work with any data type using a comparison operator overload.

- `heapArray`: Array containing the elements of the priority queue.
- `capacity`: Length of the heapArray.
- `items`: Number of items currently stored in the heap.

The `priorityQ` class provides methods for inserting (`insert()`), deleting the highest priority item (`deleteHighestPriority()`), retrieving the highest priority item (`getHighestPriority()`), checking if the queue is empty (`isEmpty()`), and getting the size of the queue (`getSize()`). Additionally, it includes methods for bubbling up and down elements to maintain the heap property.

## Main Contents

1. Prompt for input files containing lander data and simulation info.
2. For each line of lander data, a lander object is created and inserted into the priority queue.
3. Then, for each line of simulation info, the highest priority lander is selected, its flow rate updated, and a simulation step performed. This process continues until either all landers have landed or crashed, or the end of the simulation info file is reached.

## Helper Functions

The helper functions are simple to understand. They are non-member functions.

| Helper Function   | Description                                                              |
|-------------------|--------------------------------------------------------------------------|
| `checkFileOpen()` | Checks if a file is open.                                                |
| `readLanderFile()`| Reads lander info and populates a priority queue.                         |
| `printLanderInfo()` | Prints lander information.                                             |
| `printMissionStatus()` | Prints the mission status of the landers.                             |
| `simulateLanding()` | 1. Opens a sim file and checks for valid input from file.                |
|                     | 2. Gets the lander with the highest priority and prints its info.        |
|                     | 3. Program updates the flow rate, simulates landing, and prints the mission status. |

Now, you're ready to embark on your journey to control the NASA SpaceX landers and ensure their safe landing on the newly discovered planet! 🚀🪐
