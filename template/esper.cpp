pair<long long, long long> rational_convert(long long x, long long m, long long d = 1000){
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
