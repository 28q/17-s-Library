//モノイドの型, 集合の型, モノイドの演算, モノイドの作用, モノイドの単位元
template<class S, class T>
struct DLP{
  int m;
  S f;
  T s, t;
  long long n;
  DLP(S _f, long long N, T _s, T _t):
    n(N), f(_f), s(_s), t(_t)
    {m = sqrt(N);}
  DLP(S _f, long long N, T _s, T _t, long long _m):
    n(N), f(_f), s(_s), t(_t)
    {m = _m;}
  template<S (*op)(S, S), T (*apply)(S, T), S (*e)()> int solve() const {
    T t2 = t;
    //unordered_mapにするとlogが落ちる
    map<T, bool> H;
    for(int i = 0; i < m; i++){
      t2 = apply(f, t2);
      H[t2] = true;
    }
    S g = e();
    S f2 = f;
    int m2 = m;
    while(m2){
      if(m2&1) g = op(g, f2);
      f2 = op(f2, f2);
      m2 >>= 1;
    }
    //pow(f, m);
    S g2 = g;
    S g3 = e();
    int isok = 2;
    long long k = 0;
    while(++k && isok > 0 && (k-1)*m <= n){
      if(H.contains(apply(g2, s))){
        isok--;
        S g4 = g3;
        for(int i = 0; i <= m; i++){
          if(apply(g4, s) == t) return (k-1)*m+i;
          g4 = op(g4, f);
        }
      }
      g2 = op(g2, g);
      g3 = op(g3, g);
    }
    return -1;
  }
};
/*verify
struct S{
  long long a;
  long long b;
};
using T = long long;
long long p;
S op(S x, S y){
  S ret;
  ret.a = x.a*y.a%p;
  ret.b = (x.b*y.a+y.b)%p;
  return ret;
}
T apply(S x, T y){
  return (y*x.a+x.b)%p;
}
S e(){
  S ret;
  ret.a = 1;
  ret.b = 0;
  return ret;
}
int main(){
  int t;
  cin >> t;
  while(t--){
    long long a, b, s, g;
    cin >> p >> a >> b >> s >> g;
    S f(a, b);
    DLP<S, T> d(f, p, s, g);
    cout << d.solve<op, apply, e>() << endl;
  }
}
*/
