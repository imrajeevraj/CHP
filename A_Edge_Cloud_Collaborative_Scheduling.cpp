#include <algorithm>
#include <bitset>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// ==================== FAST I/O ====================
static const int IBUF_SIZE = 1 << 16;
static char ibuf[IBUF_SIZE];
static int ibuf_pos = 0, ibuf_len = 0;

inline int read_char() {
  if (ibuf_pos >= ibuf_len) {
    ibuf_len = fread(ibuf, 1, IBUF_SIZE, stdin);
    ibuf_pos = 0;
    if (ibuf_len == 0)
      return -1;
  }
  return ibuf[ibuf_pos++];
}

static char token[64];
static int token_len = 0;

inline bool read_token() {
  token_len = 0;
  int c = read_char();
  while (c >= 0 && c <= ' ')
    c = read_char();
  if (c < 0)
    return false;
  while (c > ' ') {
    token[token_len++] = (char)c;
    c = read_char();
  }
  token[token_len] = '\0';
  return true;
}

inline int parse_int() {
  int v = 0, i = 0;
  bool neg = false;
  if (token_len > 0 && token[0] == '-') {
    neg = true;
    i = 1;
  } else if (token_len > 0 && token[0] == '+')
    i = 1;
  for (; i < token_len; i++)
    v = v * 10 + (token[i] - '0');
  return neg ? -v : v;
}

inline double parse_double() { return atof(token); }

inline int next_int() {
  read_token();
  return parse_int();
}
inline double next_double() {
  read_token();
  return parse_double();
}

static const int OBUF_SIZE = 1 << 16;
static char obuf[OBUF_SIZE];
static int obuf_pos = 0;

inline void write_char(char c) {
  if (obuf_pos >= OBUF_SIZE) {
    fwrite(obuf, 1, obuf_pos, stdout);
    obuf_pos = 0;
  }
  obuf[obuf_pos++] = c;
}

inline void write_int(int v) {
  if (v < 0) {
    write_char('-');
    v = -v;
  }
  if (v == 0) {
    write_char('0');
    return;
  }
  char buf[12];
  int p = 0;
  while (v > 0) {
    buf[p++] = (char)('0' + v % 10);
    v /= 10;
  }
  while (p > 0)
    write_char(buf[--p]);
}

inline void write_string(const char *s) {
  while (*s)
    write_char(*s++);
}

inline void flush_out() {
  if (obuf_pos > 0) {
    fwrite(obuf, 1, obuf_pos, stdout);
    obuf_pos = 0;
  }
  fflush(stdout);
}

// Assignment buffer
static char abuf[1 << 14];
static int abuf_pos = 0;
static int assign_count = 0;

inline void a_char(char c) { abuf[abuf_pos++] = c; }
inline void a_string(const char *s) {
  while (*s)
    a_char(*s++);
}
inline void a_int(int v) {
  if (v < 0) {
    a_char('-');
    v = -v;
  }
  if (v == 0) {
    a_char('0');
    return;
  }
  char buf[12];
  int p = 0;
  while (v > 0) {
    buf[p++] = (char)('0' + v % 10);
    v /= 10;
  }
  while (p > 0)
    a_char(buf[--p]);
}

// ==================== PARAMS & TASK-TIME TABLE ====================
int K, NL, BPT;
double S, LAT, BW;
double SLO1, SLO2, TPUB, TPB, DSTB, WTP, WC;

const int COL_PP = 0, COL_PPR = 1, COL_PPO = 2;
const int COL_DP = 3, COL_DPR = 4, COL_DPO = 5;

vector<int> ttK[6];
vector<double> ttV[6];

void build_task_table() {
  int N = next_int();
  vector<int> rawBS(N);
  vector<vector<double>> rawV(N, vector<double>(6));
  for (int i = 0; i < N; i++) {
    rawBS[i] = next_int();
    for (int c = 0; c < 6; c++)
      rawV[i][c] = next_double();
  }
  for (int c = 0; c < 6; c++) {
    vector<pair<int, double>> entries;
    for (int i = 0; i < N; i++) {
      if (rawV[i][c] > -0.5) {
        entries.push_back({rawBS[i], rawV[i][c]});
      }
    }
    sort(entries.begin(), entries.end());
    for (auto &e : entries) {
      ttK[c].push_back(e.first);
      ttV[c].push_back(e.second);
    }
  }
}

double lookup(int col, int bs) {
  int n = ttK[col].size();
  if (n == 0)
    return 1.0;
  if (bs <= ttK[col][0])
    return ttV[col][0];
  if (bs >= ttK[col][n - 1])
    return ttV[col][n - 1];

  int lo = 0, hi = n - 1;
  while (lo < hi - 1) {
    int mid = lo + (hi - lo) / 2;
    if (ttK[col][mid] <= bs)
      lo = mid;
    else
      hi = mid;
  }
  if (ttK[col][lo] == bs)
    return ttV[col][lo];
  if (ttK[col][hi] == bs)
    return ttV[col][hi];
  double frac = (double)(bs - ttK[col][lo]) / (ttK[col][hi] - ttK[col][lo]);
  return ttV[col][lo] + frac * (ttV[col][hi] - ttV[col][lo]);
}

// ==================== STATE MACHINE ====================
const int MAX_REQ = 2005;

enum State : uint8_t {
  ST_NONE = 0,
  ST_PPRE_E = 1,
  ST_PPRE_F = 2,
  ST_W_UP_P = 3,
  ST_PPRC_E = 4,
  ST_PPRC_F = 5,
  ST_W_DN_P = 6,
  ST_PPST_E = 7,
  ST_PPST_F = 8,
  ST_OUT_R = 9,
  ST_DPRE_F = 10,
  ST_W_UP_D = 11,
  ST_DPRC_E = 12,
  ST_DPRC_F = 13,
  ST_W_DN_D = 14,
  ST_DPST_E = 15,
  ST_DPST_F = 16,
  ST_FIN = 17
};

uint8_t rs[MAX_REQ];
int rln[MAX_REQ];
int rrm[MAX_REQ];
int rnp[MAX_REQ];
double rat[MAX_REQ];
double rrt[MAX_REQ];
int roi[MAX_REQ];

bool lcF;
bool rcF[8];
int rcL[8];
int maxR = -1;

vector<int> fnR;
int tmp[MAX_REQ];

// ==================== EVENTS ====================
void processTDN(double ts) {
  read_token(); // server
  int sv;
  if (token[0] == 'E') {
    sv = -1;
    lcF = true;
  } else {
    sv = 0;
    for (int i = 1; i < token_len; i++)
      sv = sv * 10 + (token[i] - '0');
    if (sv >= 0 && sv < K)
      rcF[sv] = true;
  }

  read_token(); // P or D
  bool isP = (token[0] == 'P');

  read_token(); // PRE, PROC, POST
  int step;
  if (token_len == 3 && token[2] == 'E')
    step = 0;
  else if (token_len == 4 && token[2] == 'O' && token[3] == 'C')
    step = 1;
  else
    step = 2;

  if (isP) {
    if (step == 0) {
      int remote = next_int();
      int rid = next_int();
      next_double();
      rs[rid] = ST_W_UP_P;
    } else if (step == 1) {
      int ls = next_int();
      int le = next_int();
      int remote = next_int();
      int rid = next_int();
      next_double();
      if (le >= NL) {
        rs[rid] = ST_W_DN_P;
      } else {
        rs[rid] = ST_PPRC_E;
        rnp[rid] = le;
      }
    } else {
      int remote = next_int();
      int rid = next_int();
      next_double();
      rs[rid] = ST_OUT_R;
      rrt[rid] = ts;
    }
  } else {
    if (step == 0) {
      next_int(); // -1
      int m = next_int();
      for (int i = 0; i < m; i++)
        rs[next_int()] = ST_W_UP_D;
      next_double();
    } else if (step == 1) {
      next_int(); // remote
      int m = next_int();
      for (int i = 0; i < m; i++)
        rs[next_int()] = ST_W_DN_D;
      next_double();
    } else {
      next_int(); // -1
      int m = next_int();
      for (int i = 0; i < m; i++) {
        int rid = next_int();
        rs[rid] = ST_OUT_R;
        roi[rid]++;
        rrt[rid] = ts;
      }
      next_double();
    }
  }
}

void processXDN() {
  read_token();
  bool isUp = (token[0] == 'U');
  next_int();
  next_int();
  read_token();
  bool isPre = (token[0] == 'P');
  int m = next_int();
  for (int i = 0; i < m; i++) {
    int rid = next_int();
    if (isUp && isPre)
      rs[rid] = ST_PPRC_E;
    else if (!isUp && isPre)
      rs[rid] = ST_PPST_E;
    else if (isUp)
      rs[rid] = ST_DPRC_E;
    else
      rs[rid] = ST_DPST_E;
  }
}

// ==================== SCHEDULING ====================
int selectRemote() {
  int best = 0, bestLoad = rcL[0];
  bool bestFree = rcF[0];
  for (int k = 1; k < K; k++) {
    int load = rcL[k];
    bool free = rcF[k];
    if ((!bestFree && free) || (bestFree == free && load < bestLoad)) {
      best = k;
      bestLoad = load;
      bestFree = free;
    }
  }
  return best;
}

int chooseDPreGroup(int cnt, double ts) {
  if (cnt <= 1)
    return cnt;

  int best = 1;
  double bestEff = 0;
  int remCnt[8] = {0};

  for (int m = 1; m <= cnt; m++) {
    int r = rrm[tmp[m - 1]];
    if (r >= 0 && r < K)
      remCnt[r]++;

    int maxPR = 0;
    for (int k = 0; k < K; k++) {
      if (remCnt[k] > maxPR)
        maxPR = remCnt[k];
    }

    double dpre = lookup(COL_DP, m);
    double dproc = lookup(COL_DPR, maxPR);
    double dpost = lookup(COL_DPO, m);

    double upTotal = 0;
    for (int k = 0; k < K; k++) {
      if (remCnt[k] > 0)
        upTotal += LAT + 8.0 * remCnt[k] * BPT / (BW * 1e6);
    }
    double downTotal = upTotal;

    double totalCycle =
        (S + dpre) + upTotal + (S + dproc) + downTotal + (S + dpost);
    double eff = (double)m / totalCycle;

    if (eff > bestEff) {
      bestEff = eff;
      best = m;
    }
  }

  if (SLO2 > 0) {
    double maxAge = 0;
    for (int i = 0; i < cnt; i++) {
      double age = ts - rrt[tmp[i]];
      if (age > maxAge)
        maxAge = age;
    }
    if (maxAge > SLO2 * 0.8) {
      best = min(best, max(1, cnt / 2));
    }
  }
  return best;
}

inline void emitPPre(int remote, int rid) {
  a_string("E P PRE ");
  a_int(remote);
  a_char(' ');
  a_int(rid);
  a_char('\n');
  rs[rid] = ST_PPRE_F;
  rrm[rid] = remote;
  rcL[remote]++;
  assign_count++;
  lcF = false;
}

inline void emitPProc(int k, int rid) {
  int ls = rnp[rid];
  int le = NL; // One chunk for maximum protocol safety
  a_char('C');
  a_int(k);
  a_string(" P PROC ");
  a_int(ls);
  a_char(' ');
  a_int(le);
  a_char(' ');
  a_int(k);
  a_char(' ');
  a_int(rid);
  a_char('\n');
  rs[rid] = ST_PPRC_F;
  rnp[rid] = le;
  assign_count++;
  rcF[k] = false;
}

inline void emitPPost(int rid) {
  a_string("E P POST ");
  a_int(rrm[rid]);
  a_char(' ');
  a_int(rid);
  a_char('\n');
  rs[rid] = ST_PPST_F;
  assign_count++;
  lcF = false;
}

inline void emitDPre(int gs) {
  a_string("E D PRE -1 ");
  a_int(gs);
  for (int i = 0; i < gs; i++) {
    a_char(' ');
    a_int(tmp[i]);
    rs[tmp[i]] = ST_DPRE_F;
  }
  a_char('\n');
  assign_count++;
  lcF = false;
}

inline void emitDProc(int k, int cnt) {
  a_char('C');
  a_int(k);
  a_string(" D PROC ");
  a_int(k);
  a_char(' ');
  a_int(cnt);
  for (int i = 0; i < cnt; i++) {
    a_char(' ');
    a_int(tmp[i]);
    rs[tmp[i]] = ST_DPRC_F;
  }
  a_char('\n');
  assign_count++;
  rcF[k] = false;
}

inline void emitDPost(int cnt) {
  a_string("E D POST -1 ");
  a_int(cnt);
  for (int i = 0; i < cnt; i++) {
    a_char(' ');
    a_int(tmp[i]);
    rs[tmp[i]] = ST_DPST_F;
  }
  a_char('\n');
  assign_count++;
  lcF = false;
}

void scheduleLocal(double ts) {
  int cnt = 0;
  for (int r = 0; r <= maxR; r++)
    if (rs[r] == ST_DPST_E)
      tmp[cnt++] = r;
  if (cnt > 0) {
    emitDPost(cnt);
    return;
  }

  int bestRid = -1;
  double bestAge = -1;
  for (int r = 0; r <= maxR; r++) {
    if (rs[r] == ST_PPST_E) {
      double age = ts - rat[r];
      if (age > bestAge) {
        bestAge = age;
        bestRid = r;
      }
    }
  }
  if (bestRid >= 0) {
    emitPPost(bestRid);
    return;
  }

  cnt = 0;
  for (int r = 0; r <= maxR; r++)
    if (rs[r] == ST_OUT_R)
      tmp[cnt++] = r;
  if (cnt > 0) {
    for (int i = 0; i < cnt - 1; i++) {
      int minIdx = i;
      for (int j = i + 1; j < cnt; j++) {
        if (rrt[tmp[j]] < rrt[tmp[minIdx]])
          minIdx = j;
      }
      if (minIdx != i)
        swap(tmp[i], tmp[minIdx]);
    }
    int gs = chooseDPreGroup(cnt, ts);
    emitDPre(gs);
    return;
  }

  bestRid = -1;
  bestAge = -1;
  for (int r = 0; r <= maxR; r++) {
    if (rs[r] == ST_PPRE_E) {
      double age = ts - rat[r];
      if (age > bestAge) {
        bestAge = age;
        bestRid = r;
      }
    }
  }
  if (bestRid >= 0) {
    emitPPre(selectRemote(), bestRid);
  }
}

void scheduleRemote(int k, double ts) {
  int cnt = 0;
  for (int r = 0; r <= maxR; r++) {
    if (rs[r] == ST_DPRC_E && rrm[r] == k)
      tmp[cnt++] = r;
  }
  if (cnt > 0) {
    emitDProc(k, cnt);
    return;
  }

  for (int r = 0; r <= maxR; r++) {
    if (rs[r] == ST_PPRC_E && rrm[r] == k) {
      emitPProc(k, r);
      return;
    }
  }
}

void schedule(double ts) {
  abuf_pos = 0;
  assign_count = 0;

  if (lcF)
    scheduleLocal(ts);
  for (int k = 0; k < K; k++)
    if (rcF[k])
      scheduleRemote(k, ts);

  write_int(assign_count);
  write_char('\n');
  for (int i = 0; i < abuf_pos; i++)
    write_char(abuf[i]);
  flush_out();
}

int main() {
  K = next_int();
  S = next_double();
  LAT = next_double();
  BW = next_double();
  BPT = next_int();
  NL = next_int();
  SLO1 = next_double();
  SLO2 = next_double();
  TPUB = next_double();
  TPB = next_double();
  DSTB = next_double();
  WTP = next_double();
  WC = next_double();

  build_task_table();

  lcF = true;
  for (int i = 0; i < K; i++) {
    rcF[i] = true;
    rcL[i] = 0;
  }
  memset(rs, 0, sizeof(rs));

  while (read_token()) {
    if (token_len == 3 && token[0] == 'E' && token[1] == 'N' && token[2] == 'D')
      break;
    double ts = parse_double();
    int ne = next_int();
    fnR.clear();

    for (int ev = 0; ev < ne; ev++) {
      read_token();
      if (token[0] == 'A') {
        int rid = next_int();
        int lin = next_int();
        if (rid > maxR)
          maxR = rid;
        rs[rid] = ST_PPRE_E;
        rln[rid] = lin;
        rrm[rid] = -1;
        rnp[rid] = 0;
        rat[rid] = ts;
        rrt[rid] = ts;
        roi[rid] = 0;
      } else if (token[0] == 'T') {
        processTDN(ts);
      } else if (token[0] == 'X') {
        processXDN();
      } else {
        fnR.push_back(next_int());
      }
    }

    for (int rid : fnR) {
      if (rrm[rid] >= 0 && rrm[rid] < K)
        rcL[rrm[rid]]--;
      rs[rid] = ST_FIN;
    }
    schedule(ts);
  }
  return 0;
}
