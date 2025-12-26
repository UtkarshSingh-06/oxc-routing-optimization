#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, S, L;
    cin >> N >> S >> L;

    int M, K, P;
    cin >> M >> K >> P;

    int spines_per_plane = S / P;
    int oxcs_per_plane   = M / P;
    int R = N * spines_per_plane * K;

    // Persistent OXC topology
    vector<vector<int>> oxc(M, vector<int>(R, -1));

    auto port_id = [&](int g, int spine, int k) {
        return g * spines_per_plane * K
             + (spine % spines_per_plane) * K
             + k;
    };

    static int next_pair[26][26] = {};

    for (int query = 0; query < 5; query++) {
        int Q;
        cin >> Q;

        vector<int> gA(Q), lA(Q), gB(Q), lB(Q);
        for (int i = 0; i < Q; i++)
            cin >> gA[i] >> lA[i] >> gB[i] >> lB[i];

        vector<vector<int>> spine_load(P, vector<int>(spines_per_plane, 0));
        vector<vector<vector<int>>> link_load(
            P, vector<vector<int>>(spines_per_plane, vector<int>(K, 0))
        );

        vector<array<int,5>> routes(Q);

        int rewires = 0;  // NEW: rewire counter per query

        for (int i = 0; i < Q; i++) {
            int best_cost = INF;
            int bp=0, sa=0, sb=0, ka=0, kb=0, best_oxc=0;

            int idx = next_pair[gA[i]][gB[i]]++;

            for (int p = 0; p < P; p++) {
                for (int a = 0; a < spines_per_plane; a++) {
                    for (int b = 0; b < spines_per_plane; b++) {
                        for (int x = 0; x < K; x++) {
                            for (int y = 0; y < K; y++) {

                                int oxc_id = p * oxcs_per_plane
                                           + (idx % oxcs_per_plane);

                                int spineA = p * spines_per_plane + a;
                                int spineB = p * spines_per_plane + b;

                                int pA = port_id(gA[i], spineA, x);
                                int pB = port_id(gB[i], spineB, y);

                                int cost = max({
                                    spine_load[p][a],
                                    spine_load[p][b],
                                    link_load[p][a][x],
                                    link_load[p][b][y]
                                }) * 10
                                + spine_load[p][a] + spine_load[p][b];

                                // -------- ADAPTIVE REUSE BIAS (SAFE) --------
                                int reuse_bonus = 4;
                                if (rewires > Q / 4) reuse_bonus = 6;
                                if (rewires > Q / 2) reuse_bonus = 8;

                                if (oxc[oxc_id][pA] == pB)
                                    cost -= reuse_bonus;
                                // ------------------------------------------

                                if (cost < best_cost) {
                                    best_cost = cost;
                                    bp = p; sa = a; sb = b;
                                    ka = x; kb = y;
                                    best_oxc = oxc_id;
                                }
                            }
                        }
                    }
                }
            }

            int spineA = bp * spines_per_plane + sa;
            int spineB = bp * spines_per_plane + sb;

            int pA = port_id(gA[i], spineA, ka);
            int pB = port_id(gB[i], spineB, kb);

            // Always enforce connectivity (unchanged, SAFE)
            if (oxc[best_oxc][pA] != pB) {
                if (oxc[best_oxc][pA] != -1) {
                    int old = oxc[best_oxc][pA];
                    oxc[best_oxc][old] = -1;
                }
                if (oxc[best_oxc][pB] != -1) {
                    int old = oxc[best_oxc][pB];
                    oxc[best_oxc][old] = -1;
                }
                oxc[best_oxc][pA] = pB;
                oxc[best_oxc][pB] = pA;
                rewires++;  // NEW: count rewires
            }

            spine_load[bp][sa]++;
            spine_load[bp][sb]++;
            link_load[bp][sa][ka]++;
            link_load[bp][sb][kb]++;

            routes[i] = {spineA, ka, best_oxc, spineB, kb};
        }

        // OUTPUT (unchanged)
        for (int m = 0; m < M; m++) {
            for (int i = 0; i < R; i++)
                cout << oxc[m][i] << (i + 1 < R ? ' ' : '\n');
        }

        for (auto &r : routes) {
            cout << r[0] << " " << r[1] << " "
                 << r[2] << " " << r[3] << " " << r[4] << "\n";
        }
    }

    return 0;
}
