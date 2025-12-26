# Postmortem: Lessons Learned

## What Worked Well

- Persistent OXC topology significantly reduced reconfiguration cost
- Plane isolation simplified routing logic
- Group-pair aggregation reduced systematic congestion
- Deterministic behavior avoided instability and WA issues

---

## What Did Not Work

- Aggressive striping across spines and OXCs increased worst-case congestion
- Hash-based routing destroyed locality
- Multi-pass rerouting increased reconfiguration cost more than it reduced congestion
- Over-diversification worsened max-link usage

---

## Key Insights

- Worst-case congestion dominates scoring
- Stability matters more than cleverness
- Reducing variance is often better than reducing averages
- Physical constraints must never be violated
- Many top leaderboard solutions rely on offline or multi-run techniques

---

## Engineering Takeaway

In large-scale systems:
> A stable, correct solution often outperforms aggressive heuristics under uncertainty.

This project reinforced the importance of:
- respecting hardware constraints
- understanding scoring metrics deeply
- avoiding premature optimization


