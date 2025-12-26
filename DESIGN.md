---
title: Design
---

# Design Document: OXC Routing Heuristic

## Design Goals
...


1. **Correctness**
   - Every routed flow must correspond to a valid OXC optical connection.
2. **Low Maximum Congestion**
   - Optimize the worst-case link usage rather than average load.
3. **Topology Stability**
   - Minimize OXC reconfiguration across queries.
4. **Determinism**
   - Identical inputs always produce identical outputs.

---

## Network Model

- Multi-group leaf–spine architecture
- OXCs connect spines across groups
- Multiple independent planes
- Each OXC port can connect to only one other port

---

## Core Heuristics

### 1. Persistent OXC Topology
OXC connections are preserved across queries.  
Ports are only rewired when a required connection does not already exist.

This drastically reduces reconfiguration cost.

---

### 2. Plane-Isolated Routing
Each flow is routed entirely within a single plane.
This prevents cross-plane congestion and simplifies load balancing.

---

### 3. Group-Pair–Aware Distribution
Flows between the same `(GroupA, GroupB)` pair are distributed in a round-robin fashion across spines and OXCs.

This avoids systematic hotspots.

---

### 4. Congestion-Aware Cost Function

Routing decisions minimize:


with a small secondary bias toward reuse of existing OXC connections.

---

### 5. Deterministic Strategy
No randomness is used.  
This ensures:
- reproducibility
- judge safety
- real-world deployability

---

## Design Tradeoffs

| Choice | Benefit | Cost |
|------|--------|------|
| Persistent topology | Low β cost | Less flexibility |
| No randomness | Stability | Lower ceiling |
| Single-pass routing | Safety | Suboptimal peak |
| Greedy heuristic | Speed | No global optimum |

---

## Rationale

The final design prioritizes **engineering robustness** over aggressive leaderboard optimization.  
This reflects real-world system constraints more accurately than high-risk heuristics.

