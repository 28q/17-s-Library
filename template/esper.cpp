pair<long long, long long> rat_convert(long long x, long long m, long long d = 1000){
  long long n = m / (2 * d);
  pair<long long, long long> u = make_pair(m, 0);
  pair<long long, long long> v = make_pair(x, 1);
  while(v.first != 0 && (v.first >= n || v.second >= d)){
    long long q = u.first / v.first;
    pair<long long, long long> r = make_pair(u.first - q * v.first, u.second + q * v.second);
    u = v;
    v = r;
  }
  if(v.first < n && v.second < d) return v;
}
namespace esper{
  vector<pair<string, vector<long long>>> series = {
    {"phi_", {1, 1, 2, 2, 4, 2, 6, 4, 6, 4, 10, 4, 12, 6, 8, 8, 16, 6, 18, 8, 12, 10, 22, 8, 20, 12, 18, 12, 28, 8, 30, 16, 20, 16, 24, 12, 36, 18, 24, 16, 40, 12, 42, 20, 24, 22, 46, 16, 42, 20, 32, 24, 52, 18, 40, 24, 36, 28, 58, 16, 60, 30, 36, 32, 48, 20, 66, 32, 44}},
    {"2^", {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576}},
    {"3^", {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441, 1594323, 4782969, 14348907, 43046721, 129140163, 387420489}},
    {"4^", {1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 1048576, 4194304, 16777216, 67108864}},
    {"5^", {1, 5, 25, 125, 625, 3125, 15625, 78125, 390625, 1953125, 9765625, 48828125}},
    {"6^", {1, 6, 36, 216, 1296, 7776, 46656, 279936, 1679616, 10077696}},
    {"12^", {1, 12, 144, 1728, 20736, 248832, 2985984}}    
  };  
  void esper(vector<long long> d){
    long long gd = 0;
    for(auto x:d) gd = gcd(gd, x);
    for(auto &x:d) x/=gd;
    if(gd > 1) cerr << "GCD : " << gd << endl;    
  }
}  
