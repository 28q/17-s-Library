#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;
template <typename T>
using V = vector<T>;
template <typename T>
using VV = vector<vector<T>>;
template <typename T>
using VVV = vector<vector<vector<T>>>;
template <typename T>
using VVVV = vector<vector<vector<vector<T>>>>;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vd = vector<double>;
using vb = vector<bool>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using vpll = V<pll>;
using vpii = V<pii>;
template <typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxpq = priority_queue<T>;
constexpr int inf = 1001001001;
constexpr ll INF = 4004004004004004004LL;
template <typename T>
int sz(const T &t) {
  return t.size();
}
template <typename T, typename U>
inline bool chmin(T &x, U y) {
  return (y < x) ? (x = y, true) : false;
}
template <typename T, typename U>
inline bool chmax(T &x, U y) {
  return (x < y) ? (x = y, true) : false;
}
ll max(ll a, int b) {
  return max(a, (ll)b);
}
ll max(int a, ll b) {
  return max((ll)a, b);
}
ll min(ll a, int b) {
  return min(a, (ll)b);
}
ll min(int a, ll b) {
  return min((ll)a, b);
}
template <typename T>
inline T Max(const vector<T> &v) {
  return *max_element(begin(v), end(v));
}
template <typename T>
inline T Min(const vector<T> &v) {
  return *min_element(begin(v), end(v));
}
template <typename T>
inline long long Sum(const vector<T> &v) {
  return accumulate(begin(v), end(v), 0LL);
}
template <typename T, typename U>
pair<T, U> mkp(const T &t, const U &u) {
  return make_pair(t, u);
}
template <typename T>
vector<T> mkrui(const vector<T> &v, bool rev = false) {
  vector<T> ret(v.size() + 1);
  if (rev) {
    for (int i = int(v.size()) - 1; i >= 0; i--) ret[i] = v[i] + ret[i + 1];
  } else {
    for (int i = 0; i < int(v.size()); i++) ret[i + 1] = ret[i] + v[i];
  }
  return ret;
};
template <typename T>
vector<T> mkuni(const vector<T> &v) {
  vector<T> ret(v);
  sort(ret.begin(), ret.end());
  ret.erase(unique(ret.begin(), ret.end()), ret.end());
  return ret;
}
template <typename F>
vector<int> mkord(int N,F f) {
  vector<int> ord(N);
  iota(begin(ord), end(ord), 0);
  sort(begin(ord), end(ord), f);
  return ord;
}
template <typename T>
vector<int> mkinv(vector<T> &v) {
  int max_val = *max_element(begin(v), end(v));
  vector<int> inv(max_val + 1, -1);
  for (int i = 0; i < (int)v.size(); i++) inv[v[i]] = i;
  return inv;
}
vector<int> mkiota(int n) {
  vector<int> ret(n);
  iota(begin(ret), end(ret), 0);
  return ret;
}
template <typename T>
T mkrev(const T &v) {
  T w{v};
  reverse(begin(w), end(w));
  return w;
}
template <typename T>
bool nxp(vector<T> &v) {
  return next_permutation(begin(v), end(v));
}
#define lb lower_bound
#define ub upper_bound
#define lwb(v, x) lower_bound(v.begin(), v.end(), x)
#define upb(v, x) upper_bound(v.begin(), v.end(), x)
template <typename T>
int lbd(const vector<T> &v, const T &a) {
  return lower_bound(begin(v), end(v), a) - begin(v);
}
template <typename T>
int ubd(const vector<T> &v, const T &a) {
  return upper_bound(begin(v), end(v), a) - begin(v);
}
#define each(x, v) for (auto&& x : v)
#define each2(x, y, v) for (auto&& [x, y] : v)
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define rep(i, N) for (long long i = 0; i < (long long)(N); i++)
#define repr(i, N) for (long long i = (long long)(N)-1; i >= 0; i--)
#define rep1(i, N) for (long long i = 1; i <= (long long)(N); i++)
#define repr1(i, N) for (long long i = (N); (long long)(i) > 0; i--)
#define reg(i, a, b) for (long long i = (a); i < (b); i++)
#define regr(i, a, b) for (long long i = (b)-1; i >= (a); i--)
#define fi first
#define se second
#define INT(...)   \
  int __VA_ARGS__; \
  in(__VA_ARGS__)
#define LL(...)         \
  long long __VA_ARGS__; \
  in(__VA_ARGS__)
#define STR(...)      \
  string __VA_ARGS__; \
  in(__VA_ARGS__)
#define CHR(...)      \
  char __VA_ARGS__; \
  in(__VA_ARGS__)
#define in2(s, t)                           \
  for (int i = 0; i < (int)s.size(); i++) { \
    in(s[i], t[i]);                         \
  }
#define in3(s, t, u)                        \
  for (int i = 0; i < (int)s.size(); i++) { \
    in(s[i], t[i], u[i]);                   \
  }
#define in4(s, t, u, v)                     \
  for (int i = 0; i < (int)s.size(); i++) { \
    in(s[i], t[i], u[i], v[i]);             \
  }
long long TWO[60] = {1LL, 2LL, 4LL, 8LL, 16LL, 32LL, 64LL, 128LL, 256LL, 512LL, 1024LL, 2048LL, 4096LL, 8192LL, 16384LL, 32768LL, 65536LL, 131072LL, 262144LL, 524288LL, 1048576LL, 2097152LL, 4194304LL, 8388608LL, 16777216LL, 33554432LL, 67108864LL, 134217728LL, 268435456LL, 536870912LL, 1073741824LL, 2147483648LL, 4294967296LL, 8589934592LL, 17179869184LL, 34359738368LL, 68719476736LL, 137438953472LL, 274877906944LL, 549755813888LL, 1099511627776LL, 2199023255552LL, 4398046511104LL, 8796093022208LL, 17592186044416LL, 35184372088832LL, 70368744177664LL, 140737488355328LL, 281474976710656LL, 562949953421312LL, 1125899906842624LL, 2251799813685248LL, 4503599627370496LL, 9007199254740992LL, 18014398509481984LL, 36028797018963968LL, 72057594037927936LL, 144115188075855872LL, 288230376151711744LL, 576460752303423488LL};
long long THREE[38] = {1LL, 3LL, 9LL, 27LL, 81LL, 243LL, 729LL, 2187LL, 6561LL, 19683LL, 59049LL, 177147LL, 531441LL, 1594323LL, 4782969LL, 14348907LL, 43046721LL, 129140163LL, 387420489LL, 1162261467LL, 3486784401LL, 10460353203LL, 31381059609LL, 94143178827LL, 282429536481LL, 847288609443LL, 2541865828329LL, 7625597484987LL, 22876792454961LL, 68630377364883LL, 205891132094649LL, 617673396283947LL, 1853020188851841LL, 5559060566555523LL, 16677181699666569LL, 50031545098999707LL, 150094635296999121LL, 450283905890997363LL};
long long FIVE[26] = {1LL, 5LL, 25LL, 125LL, 625LL, 3125LL, 15625LL, 78125LL, 390625LL, 1953125LL, 9765625LL, 48828125LL, 244140625LL, 1220703125LL, 6103515625LL, 30517578125LL, 152587890625LL, 762939453125LL, 3814697265625LL, 19073486328125LL, 95367431640625LL, 476837158203125LL, 2384185791015625LL, 11920928955078125LL, 59604644775390625LL, 298023223876953125LL};
long long TEN[18] = {1LL, 10LL, 100LL, 1000LL, 10000LL, 100000LL, 1000000LL, 10000000LL, 100000000LL, 1000000000LL, 10000000000LL, 100000000000LL, 1000000000000LL, 10000000000000LL, 100000000000000LL, 1000000000000000LL, 10000000000000000LL, 100000000000000000LL};
template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  os << p.first << " " << p.second;
  return os;
}
template <typename T, typename U>
istream &operator>>(istream &is, pair<T, U> &p) {
  is >> p.first >> p.second;
  return is;
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  int s = (int)v.size();
  for (int i = 0; i < s; i++) os << (i ? " " : "") << v[i];
  return os;
}
template <typename T>
istream &operator>>(istream &is, vector<T> &v) {
  for (auto &x : v) is >> x;
  return is;
}
istream &operator>>(istream &is, __int128_t &x) {
  string S;
  is >> S;
  x = 0;
  int flag = 0;
  for (auto &c : S) {
    if (c == '-') {
      flag = true;
      continue;
    }
    x *= 10;
    x += c - '0';
  }
  if (flag) x = -x;
  return is;
}
istream &operator>>(istream &is, __uint128_t &x) {
  string S;
  is >> S;
  x = 0;
  for (auto &c : S) {
    x *= 10;
    x += c - '0';
  }
  return is;
}
ostream &operator<<(ostream &os, __int128_t x) {
  if (x == 0) return os << 0;
  if (x < 0) os << '-', x = -x;
  string S;
  while (x) S.push_back('0' + x % 10), x /= 10;
  reverse(begin(S), end(S));
  return os << S;
}
ostream &operator<<(ostream &os, __uint128_t x) {
  if (x == 0) return os << 0;
  string S;
  while (x) S.push_back('0' + x % 10), x /= 10;
  reverse(begin(S), end(S));
  return os << S;
}
void in() {}
template <typename T, class... U>
void in(T &t, U &...u) {
  cin >> t;
  in(u...);
}
void out() { cout << "\n"; }
template <typename T, class... U, char sep = ' '>
void out(const T &t, const U &...u) {
  cout << t;
  if (sizeof...(u)) cout << sep;
  out(u...);
}
void fin() { cout << "\n"; exit(0);}
template <typename T, class... U, char sep = ' '>
void fin(const T &t, const U &...u) {
  cout << t;
  if (sizeof...(u)) cout << sep;
  fin(u...);
}
struct IoSetup{
  IoSetup() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    cerr << fixed << setprecision(7);
  }
} iosetup;
