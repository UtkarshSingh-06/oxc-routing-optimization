# OXC Routing & Topology Optimization

## Overview

This project implements a **scoring-oriented heuristic routing and topology optimization system** for large-scale AI clusters using **Optical Circuit Switches (OXC)**.

The solution was developed for the **ICPC 2025 Online Winter Challenge (Huawei)**, a competitive optimization problem focused on balancing **network congestion** and **hardware reconfiguration cost** under strict physical constraints.

The final solution achieved a **stable top-200 global rank** while prioritizing correctness, determinism, and engineering robustness.

---

## Problem Context

Modern AI clusters rely on **optical circuit switches** to interconnect tens of thousands of accelerators efficiently.  
Unlike packet switches, OXCs impose a **one-to-one port matching constraint**, making routing and topology optimization a non-trivial systems problem.

Each traffic flow must be routed as:

