import java.io.*;

public class Main {

    // ==================== FAST INPUT ====================
    private static final int IBSZ = 1 << 16;
    private static final byte[] ib = new byte[IBSZ];
    private static int ibp = 0, ibl = 0;

    private static int rb() throws IOException {
        if (ibp >= ibl) {
            ibl = System.in.read(ib);
            ibp = 0;
            if (ibl <= 0) return -1;
        }
        return ib[ibp++];
    }

    private static final byte[] tk = new byte[64];
    private static int tl;

    // Read next whitespace-delimited token into tk[0..tl-1]
    private static boolean rt() throws IOException {
        tl = 0;
        int c = rb();
        while (c >= 0 && c <= ' ') c = rb();
        if (c < 0) return false;
        while (c > ' ') {
            tk[tl++] = (byte) c;
            c = rb();
        }
        return tl > 0;
    }

    // Parse current token as int
    private static int ti() {
        int v = 0, i = 0;
        boolean neg = false;
        if (tl > 0 && tk[0] == '-') { neg = true; i = 1; }
        else if (tl > 0 && tk[0] == '+') i = 1;
        for (; i < tl; i++) v = v * 10 + (tk[i] - '0');
        return neg ? -v : v;
    }

    // Parse current token as double
    private static double td() {
        return Double.parseDouble(new String(tk, 0, tl));
    }

    // Convenience: read token + parse
    private static int ri() throws IOException { rt(); return ti(); }
    private static double rd() throws IOException { rt(); return td(); }

    // ==================== FAST OUTPUT ====================
    private static final int OBSZ = 1 << 16;
    private static final byte[] ob = new byte[OBSZ];
    private static int op = 0;

    private static void wb(int b) throws IOException {
        if (op >= OBSZ) wf();
        ob[op++] = (byte) b;
    }

    private static final byte[] nb = new byte[12];

    private static void wi(int v) throws IOException {
        if (v < 0) { wb('-'); v = -v; }
        if (v == 0) { wb('0'); return; }
        int p = 12;
        while (v > 0) { nb[--p] = (byte) ('0' + v % 10); v /= 10; }
        while (p < 12) wb(nb[p++]);
    }

    private static void wn() throws IOException { wb('\n'); }
    private static void wsp() throws IOException { wb(' '); }

    private static void wf() throws IOException {
        if (op > 0) {
            System.out.write(ob, 0, op);
            op = 0;
        }
        System.out.flush();
    }

    // ==================== ASSIGNMENT BUFFER ====================
    // Buffer assignment lines separately, then prepend count
    private static final byte[] ab = new byte[1 << 14];
    private static int ap = 0;
    private static int asgN = 0;

    private static void aB(int b) { ab[ap++] = (byte) b; }

    private static void aI(int v) {
        if (v < 0) { aB('-'); v = -v; }
        if (v == 0) { aB('0'); return; }
        int p = 12;
        while (v > 0) { nb[--p] = (byte) ('0' + v % 10); v /= 10; }
        while (p < 12) aB(nb[p++]);
    }

    private static void aS(String s) {
        for (int i = 0; i < s.length(); i++) aB(s.charAt(i));
    }

    private static void aN() { aB('\n'); }

    // ==================== CONFIGURATION ====================
    static int K, NL, BPT;
    static double S, LAT, BW;
    static double SLO1, SLO2, TPUB, TPB, DSTB, WTP, WC;

    // ==================== TASK-TIME TABLE ====================
    // Columns: 0=prefill_pre, 1=prefill_proc, 2=prefill_post,
    //          3=decode_pre, 4=decode_proc, 5=decode_post
    static final int C_PP = 0, C_PPR = 1, C_PPO = 2;
    static final int C_DP = 3, C_DPR = 4, C_DPO = 5;
    static int[][] ttK = new int[6][];   // sorted batch sizes per column
    static double[][] ttV = new double[6][]; // values per column
    static int[] ttN = new int[6];       // count per column

    static void buildTT() throws IOException {
        int N = ri();
        int[] rawBS = new int[N];
        double[][] rawV = new double[N][6];
        for (int i = 0; i < N; i++) {
            rawBS[i] = ri();
            for (int c = 0; c < 6; c++) rawV[i][c] = rd();
        }
        for (int c = 0; c < 6; c++) {
            int cnt = 0;
            for (int i = 0; i < N; i++) if (rawV[i][c] > -0.5) cnt++;
            ttK[c] = new int[cnt];
            ttV[c] = new double[cnt];
            int idx = 0;
            for (int i = 0; i < N; i++) {
                if (rawV[i][c] > -0.5) {
                    ttK[c][idx] = rawBS[i];
                    ttV[c][idx] = rawV[i][c];
                    idx++;
                }
            }
            ttN[c] = cnt;
            // Insertion sort by batch size
            for (int i = 1; i < cnt; i++) {
                int kb = ttK[c][i]; double kv = ttV[c][i];
                int j = i - 1;
                while (j >= 0 && ttK[c][j] > kb) {
                    ttK[c][j + 1] = ttK[c][j];
                    ttV[c][j + 1] = ttV[c][j];
                    j--;
                }
                ttK[c][j + 1] = kb;
                ttV[c][j + 1] = kv;
            }
        }
    }

    // Lookup with linear interpolation
    static double lu(int col, int bs) {
        int n = ttN[col];
        if (n == 0) return 1.0;
        int[] k = ttK[col]; double[] v = ttV[col];
        if (bs <= k[0]) return v[0];
        if (bs >= k[n - 1]) return v[n - 1];
        // Binary search
        int lo = 0, hi = n - 1;
        while (lo < hi - 1) {
            int mid = (lo + hi) >>> 1;
            if (k[mid] <= bs) lo = mid; else hi = mid;
        }
        if (k[lo] == bs) return v[lo];
        if (k[hi] == bs) return v[hi];
        double frac = (double) (bs - k[lo]) / (k[hi] - k[lo]);
        return v[lo] + frac * (v[hi] - v[lo]);
    }

    // ==================== REQUEST STATE MACHINE ====================
    static final int MR = 2001;
    // States
    static final byte ST_NONE     = 0;
    static final byte ST_PPRE_E   = 1;  // P PRE eligible (arrived)
    static final byte ST_PPRE_F   = 2;  // P PRE in-flight
    static final byte ST_W_UP_P   = 3;  // waiting input UP XDN
    static final byte ST_PPRC_E   = 4;  // P PROC eligible
    static final byte ST_PPRC_F   = 5;  // P PROC in-flight
    static final byte ST_W_DN_P   = 6;  // waiting input DOWN XDN
    static final byte ST_PPST_E   = 7;  // P POST eligible
    static final byte ST_PPST_F   = 8;  // P POST in-flight
    static final byte ST_OUT_R    = 9;  // output ready (D PRE eligible)
    static final byte ST_DPRE_F   = 10; // D PRE in-flight
    static final byte ST_W_UP_D   = 11; // waiting output UP XDN
    static final byte ST_DPRC_E   = 12; // D PROC eligible
    static final byte ST_DPRC_F   = 13; // D PROC in-flight
    static final byte ST_W_DN_D   = 14; // waiting output DOWN XDN
    static final byte ST_DPST_E   = 15; // D POST eligible
    static final byte ST_DPST_F   = 16; // D POST in-flight
    static final byte ST_FIN      = 17; // finished

    static byte[]   rs  = new byte[MR];    // state
    static int[]    rln = new int[MR];     // input length Lin
    static int[]    rrm = new int[MR];     // assigned remote (-1=unassigned)
    static int[]    rnp = new int[MR];     // next P PROC piece start
    static double[] rat = new double[MR];  // arrival time
    static double[] rrt = new double[MR];  // time became output-ready
    static int[]    roi = new int[MR];     // output iteration (0-based)

    // Resource state
    static boolean lcF;                    // local free
    static boolean[] rcF = new boolean[8]; // remote k free
    static int[] rcL = new int[8];         // remote k load (active request count)

    static int maxR = -1; // highest rid seen

    // FIN deferral
    static int fnN;
    static int[] fnR = new int[MR];

    // Temp buffer for eligible rids
    static int[] tmp = new int[MR];

    // ==================== TDN PROCESSING ====================
    static void processTDN(double ts) throws IOException {
        // TDN server P|D PRE|PROC|POST ... dur
        rt(); // server token
        int sv;
        if (tk[0] == 'E') {
            sv = -1;
            lcF = true;
        } else { // Ck
            sv = 0;
            for (int i = 1; i < tl; i++) sv = sv * 10 + (tk[i] - '0');
            if (sv >= 0 && sv < K) rcF[sv] = true;
        }

        rt(); // P or D
        boolean isP = (tk[0] == 'P');

        rt(); // PRE, PROC, or POST
        int step; // 0=PRE, 1=PROC, 2=POST
        if (tl == 3 && tk[2] == 'E') step = 0;      // PRE
        else if (tl == 4 && tk[2] == 'O' && tk[3] == 'C') step = 1; // PROC
        else step = 2; // POST

        if (isP) {
            if (step == 0) {
                // P PRE: remote rid dur
                int remote = ri(); int rid = ri(); rd();
                rs[rid] = ST_W_UP_P;
            } else if (step == 1) {
                // P PROC: ls le remote rid dur
                int ls = ri(); int le = ri(); int remote = ri(); int rid = ri(); rd();
                if (le >= NL) {
                    rs[rid] = ST_W_DN_P;
                } else {
                    rs[rid] = ST_PPRC_E;
                    rnp[rid] = le;
                }
            } else {
                // P POST: remote rid dur
                int remote = ri(); int rid = ri(); rd();
                rs[rid] = ST_OUT_R;
                rrt[rid] = ts;
            }
        } else {
            if (step == 0) {
                // D PRE: -1 m rid... dur
                ri(); // -1
                int m = ri();
                for (int i = 0; i < m; i++) {
                    int rid = ri();
                    rs[rid] = ST_W_UP_D;
                }
                rd(); // dur
            } else if (step == 1) {
                // D PROC: remote m rid... dur
                ri(); // remote
                int m = ri();
                for (int i = 0; i < m; i++) {
                    int rid = ri();
                    rs[rid] = ST_W_DN_D;
                }
                rd(); // dur
            } else {
                // D POST: -1 m rid... dur
                ri(); // -1
                int m = ri();
                for (int i = 0; i < m; i++) {
                    int rid = ri();
                    rs[rid] = ST_OUT_R;
                    roi[rid]++;
                    rrt[rid] = ts;
                }
                rd(); // dur
            }
        }
    }

    // ==================== XDN PROCESSING ====================
    static void processXDN() throws IOException {
        // XDN UP|DOWN remote size PRE|DEC m rid...
        rt(); // UP or DOWN
        boolean isUp = (tk[0] == 'U');
        ri(); // remote (ignored for state transition)
        ri(); // size (ignored)
        rt(); // PRE or DEC
        boolean isPre = (tk[0] == 'P');
        int m = ri();
        for (int i = 0; i < m; i++) {
            int rid = ri();
            if (isUp && isPre)       rs[rid] = ST_PPRC_E;  // input UP → P PROC eligible
            else if (!isUp && isPre) rs[rid] = ST_PPST_E;  // input DOWN → P POST eligible
            else if (isUp)           rs[rid] = ST_DPRC_E;  // output UP → D PROC eligible
            else                     rs[rid] = ST_DPST_E;  // output DOWN → D POST eligible
        }
    }

    // ==================== REMOTE SELECTION ====================
    static int selectRemote() {
        int best = 0, bestLoad = rcL[0];
        boolean bestFree = rcF[0];
        for (int k = 1; k < K; k++) {
            int load = rcL[k]; boolean free = rcF[k];
            // Prefer: free > busy, then lower load, then lower index
            if ((!bestFree && free) || (bestFree == free && load < bestLoad)) {
                best = k; bestLoad = load; bestFree = free;
            }
        }
        return best;
    }

    // ==================== GROUP SIZE SELECTION ====================
    static int chooseDPreGroup(int cnt, double ts) {
        if (cnt <= 1) return cnt;

        // Transfer time for 1 token
        double xfer1 = LAT + 8.0 * BPT / (BW * 1e6);

        int best = 1;
        double bestEff = 0;

        // Incremental remote distribution tracking
        int[] remCnt = new int[K];
        int numRem = 0, maxPR = 0;

        for (int m = 1; m <= cnt; m++) {
            int r = rrm[tmp[m - 1]];
            if (r >= 0) {
                if (remCnt[r]++ == 0) numRem++;
                if (remCnt[r] > maxPR) maxPR = remCnt[r];
            }

            double dpre = lu(C_DP, m);
            double dproc = lu(C_DPR, maxPR);
            double dpost = lu(C_DPO, m);

            int nr = Math.max(numRem, 1);
            // UP transfers: serialized per remote
            // Each remote transfers its member count tokens worth of data
            // Approximate: each transfer = xfer for that remote's member count
            // Total UP ≈ sum of individual transfers ≈ nr * (LAT + 8*ceil(m/nr)*BPT/(BW*1e6))
            // Simplify: nr * xfer for average members
            double upTotal = 0;
            for (int k = 0; k < K; k++) {
                if (remCnt[k] > 0) {
                    upTotal += LAT + 8.0 * remCnt[k] * BPT / (BW * 1e6);
                }
            }
            double downTotal = upTotal; // symmetric approximation

            double totalCycle = (S + dpre) + upTotal + (S + dproc) + downTotal + (S + dpost);
            double eff = (double) m / totalCycle;

            if (eff > bestEff) {
                bestEff = eff;
                best = m;
            }
        }

        // Clean up remCnt
        for (int i = 0; i < cnt; i++) {
            int r = rrm[tmp[i]];
            if (r >= 0) remCnt[r] = 0;
        }

        // Age-aware override: if oldest request waiting too long, limit group
        if (SLO2 > 0) {
            double maxAge = 0;
            for (int i = 0; i < cnt; i++) {
                double age = ts - rrt[tmp[i]];
                if (age > maxAge) maxAge = age;
            }
            if (maxAge > SLO2 * 0.8) {
                // Urgent: schedule at least the oldest requests quickly
                best = Math.min(best, Math.max(1, cnt / 2));
            }
        }

        return best;
    }

    // ==================== EMIT FUNCTIONS ====================
    static void emitPPre(int remote, int rid) {
        aS("E P PRE "); aI(remote); aB(' '); aI(rid); aN();
        rs[rid] = ST_PPRE_F;
        rrm[rid] = remote;
        rcL[remote]++;
        asgN++;
        lcF = false;
    }

    static void emitPProc(int k, int rid) {
        int ls = rnp[rid];
        int le = NL; // one full remaining piece
        aB('C'); aI(k); aS(" P PROC "); aI(ls); aB(' '); aI(le);
        aB(' '); aI(k); aB(' '); aI(rid); aN();
        rs[rid] = ST_PPRC_F;
        rnp[rid] = le;
        asgN++;
        rcF[k] = false;
    }

    static void emitPPost(int rid) {
        aS("E P POST "); aI(rrm[rid]); aB(' '); aI(rid); aN();
        rs[rid] = ST_PPST_F;
        asgN++;
        lcF = false;
    }

    static void emitDPre(int groupSize) {
        aS("E D PRE -1 "); aI(groupSize);
        for (int i = 0; i < groupSize; i++) {
            aB(' '); aI(tmp[i]);
            rs[tmp[i]] = ST_DPRE_F;
        }
        aN();
        asgN++;
        lcF = false;
    }

    static void emitDProc(int k, int cnt) {
        aB('C'); aI(k); aS(" D PROC "); aI(k); aB(' '); aI(cnt);
        for (int i = 0; i < cnt; i++) {
            aB(' '); aI(tmp[i]);
            rs[tmp[i]] = ST_DPRC_F;
        }
        aN();
        asgN++;
        rcF[k] = false;
    }

    static void emitDPost(int cnt) {
        aS("E D POST -1 "); aI(cnt);
        for (int i = 0; i < cnt; i++) {
            aB(' '); aI(tmp[i]);
            rs[tmp[i]] = ST_DPST_F;
        }
        aN();
        asgN++;
        lcF = false;
    }

    // ==================== SCHEDULING ====================
    static void scheduleLocal(double ts) {
        // Priority: D POST > P POST > D PRE > P PRE

        // 1. D POST — produces tokens (highest value)
        {
            int cnt = 0;
            for (int r = 0; r <= maxR; r++) {
                if (rs[r] == ST_DPST_E) tmp[cnt++] = r;
            }
            if (cnt > 0) { emitDPost(cnt); return; }
        }

        // 2. P POST — stops TDR timer (high value for waiting time)
        {
            int bestRid = -1;
            double bestAge = -1;
            for (int r = 0; r <= maxR; r++) {
                if (rs[r] == ST_PPST_E) {
                    double age = ts - rat[r];
                    if (age > bestAge) { bestAge = age; bestRid = r; }
                }
            }
            if (bestRid >= 0) { emitPPost(bestRid); return; }
        }

        // 3. D PRE — starts output iteration
        {
            int cnt = 0;
            for (int r = 0; r <= maxR; r++) {
                if (rs[r] == ST_OUT_R) tmp[cnt++] = r;
            }
            if (cnt > 0) {
                // Sort by rrt ascending (oldest first) for fairness
                // Simple selection for first few elements is enough
                for (int i = 0; i < cnt - 1; i++) {
                    int minIdx = i;
                    for (int j = i + 1; j < cnt; j++) {
                        if (rrt[tmp[j]] < rrt[tmp[minIdx]]) minIdx = j;
                    }
                    if (minIdx != i) {
                        int t = tmp[i]; tmp[i] = tmp[minIdx]; tmp[minIdx] = t;
                    }
                }
                int gs = chooseDPreGroup(cnt, ts);
                emitDPre(gs);
                return;
            }
        }

        // 4. P PRE — starts input stage for new request
        {
            int bestRid = -1;
            double bestAge = -1;
            for (int r = 0; r <= maxR; r++) {
                if (rs[r] == ST_PPRE_E) {
                    double age = ts - rat[r];
                    if (age > bestAge) { bestAge = age; bestRid = r; }
                }
            }
            if (bestRid >= 0) {
                int remote = selectRemote();
                emitPPre(remote, bestRid);
            }
        }
    }

    static void scheduleRemote(int k, double ts) {
        // Priority: D PROC > P PROC

        // 1. D PROC — produces output data
        {
            int cnt = 0;
            for (int r = 0; r <= maxR; r++) {
                if (rs[r] == ST_DPRC_E && rrm[r] == k) tmp[cnt++] = r;
            }
            if (cnt > 0) { emitDProc(k, cnt); return; }
        }

        // 2. P PROC — processes input
        {
            for (int r = 0; r <= maxR; r++) {
                if (rs[r] == ST_PPRC_E && rrm[r] == k) {
                    emitPProc(k, r);
                    return;
                }
            }
        }
    }

    static void schedule(double ts) throws IOException {
        ap = 0;
        asgN = 0;

        // Schedule local task (if free)
        if (lcF) scheduleLocal(ts);

        // Schedule remote tasks (if free)
        for (int k = 0; k < K; k++) {
            if (rcF[k]) scheduleRemote(k, ts);
        }

        // Write output: count + assignment lines + flush
        wi(asgN); wn();
        for (int i = 0; i < ap; i++) wb(ab[i]);
        wf();
    }

    // ==================== MAIN ====================
    public static void main(String[] args) throws IOException {
        // Read startup configuration line 1
        K = ri();
        S = rd();
        LAT = rd();
        BW = rd();
        BPT = ri();
        NL = ri();

        // Read startup configuration line 2
        SLO1 = rd();
        SLO2 = rd();
        TPUB = rd();
        TPB = rd();
        DSTB = rd();
        WTP = rd();
        WC = rd();

        // Read task-time table
        buildTT();

        // Initialize resources
        lcF = true;
        for (int i = 0; i < K; i++) { rcF[i] = true; rcL[i] = 0; }

        // Main interaction loop
        while (true) {
            if (!rt()) break; // EOF
            // Check for END
            if (tl == 3 && tk[0] == 'E' && tk[1] == 'N' && tk[2] == 'D') break;

            double ts = td(); // timestamp
            int ne = ri();    // event count

            fnN = 0;

            // Read and process all events
            for (int ev = 0; ev < ne; ev++) {
                rt(); // event type
                if (tk[0] == 'A') {
                    // ARR rid Lin
                    int rid = ri();
                    int lin = ri();
                    if (rid > maxR) maxR = rid;
                    rs[rid] = ST_PPRE_E;
                    rln[rid] = lin;
                    rrm[rid] = -1;
                    rnp[rid] = 0;
                    rat[rid] = ts;
                    rrt[rid] = ts;
                    roi[rid] = 0;
                } else if (tk[0] == 'T') {
                    // TDN
                    processTDN(ts);
                } else if (tk[0] == 'X') {
                    // XDN
                    processXDN();
                } else {
                    // FIN rid
                    fnR[fnN++] = ri();
                }
            }

            // Process deferred FINs (must be after TDN/XDN)
            for (int i = 0; i < fnN; i++) {
                int rid = fnR[i];
                if (rrm[rid] >= 0 && rrm[rid] < K) {
                    rcL[rrm[rid]]--;
                }
                rs[rid] = ST_FIN;
            }

            // Schedule and output response
            schedule(ts);
        }
    }
}
