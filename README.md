# Parallel Task Scheduling Simulator

A highly optimized, multi-core CPU task scheduling simulator with advanced work-stealing and load-balancing algorithms.

## Overview

The **Parallel Task Scheduling Simulator** is a C++ project that implements a custom, dynamic deque data structure to power an efficient task queuing system for a multi-core CPU environment. The simulator features intelligent work-stealing and load-balancing mechanisms to ensure optimal utilization of available processing resources.

## Key Features

- **Highly Optimized Multi-Core Task Scheduler**  
  A robust task scheduling system that efficiently distributes and balances workloads across multiple CPU cores.

- **Custom Dynamic Deque**  
  A highly efficient, custom dynamic deque to power the task queuing system.

- **Work-Stealing and Load-Balancing**  
  Sophisticated algorithms to ensure tasks are assigned to the cores with the least amount of work, maximizing parallel processing.

- **Comprehensive Error Handling**  
  Robust mechanisms to ensure stability and fault-tolerance even under extreme workloads.

## Technical Details

- The core of the system is powered by a **custom dynamic deque** data structure, engineered for efficient task queue management.
- The simulator employs **work-stealing** and **load-balancing** algorithms to improve CPU core utilization and reduce idle times.
- The task scheduling system is optimized to handle both small and large workloads efficiently.
