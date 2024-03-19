namespace math{
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Waddress"
  
  template <class T> using is_integral = typename std::is_integral<T>;
  template <class T>
  using is_signed_int =
  typename std::conditional<is_integral<T>::value && std::is_signed<T>::value,
  std::true_type,
  std::false_type>::type;
  template <class T>
  using is_unsigned_int =
  typename std::conditional<is_integral<T>::value &&
  std::is_unsigned<T>::value,
  std::true_type,
  std::false_type>::type;
  template <class T>
  using to_unsigned =
  typename std::conditional<is_signed_int<T>::value,
  std::make_unsigned<T>,
  std::common_type<T>>::type;
  template <class T>
  using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;
  template <class T>
  using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;
  template <class T>
  using to_unsigned_t = typename to_unsigned<T>::type;
  
  constexpr long long safe_mod(long long x, long long m){
    x %= m;
    if(x < 0) x += m;
    return x;
  }
  struct barrett{
    unsigned int m;
    unsigned long long im;
    explicit barrett(unsigned int _m):m(_m), im((unsigned long long)(-1)/_m+1){}
    unsigned int umod()const{return m;}
    unsigned int mul(unsigned int a, unsigned int b)const{
      unsigned long long z = a;
      z *= b;
      //unsigned long long x = (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
      unsigned long long x = (z>>32)*(im>>32)+(((z>>32)*((im<<32)>>32))>>32)+(((im>>32)*((z<<32)>>32))>>32);
      unsigned long long x1 = (((z>>32)*((im<<32)>>32))<<32);
      unsigned long long x2 = (((im>>32)*((z<<32)>>32))<<32);
      unsigned long long x3 = (((z<<32)>>32)*((im<<32)>>32));
      x += ((-x1) <= x2);
      x1 += x2;
      x += ((-x1) <= x3);
      unsigned long long y = x*m;
      return (unsigned int)(z-y+(z<y?m:0));
    }
  };
  constexpr long long pow_mod_constexpr(long long x, long long n, int _m){
    if(_m == 1) return 0;
    unsigned int m = _m;
    unsigned long long r = 1;
    unsigned long long y = safe_mod(x, m);
    while(n){
      if(n&1) r = r*y%m;
      y = y*y%m;
      n >>= 1;
    }
    return r;
  }
  constexpr std::pair<int, int> inv_gcd(int a, int b){
    a = safe_mod(a, b);
    if(a == 0) return {b, 0};
    int s = b, t = a, m0 = 0, m1 = 1;
    while(t){
      int u = s/t;
      s -= t*u;
      m0 -= m1*u;
      int tmp = s;
      s = t;
      t = tmp;
      tmp = m0;
      m0 = m1;
      m1 = tmp;
    }
    if(m0 < 0) m0 += b/s;
    return {s, m0};
  }
  struct modint_base{};
  struct static_modint_base:modint_base{};
  template <class T> using is_modint = std::is_base_of<modint_base, T>;
  template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;
  template <int m, std::enable_if_t<(1 <= m)>* = nullptr>
  struct static_modint:static_modint_base{
    using mint = static_modint;
    public:
    static constexpr int mod(){return m;}
    static constexpr mint raw(int v){
      mint x;
      x._v = v;
      return x;
    }
    static_modint():_v(0){}
    template <class T, is_signed_int_t<T>* = nullptr>
    static_modint(T v){
      long long x = (long long)(v%(long long)(umod()));
      if(x < 0) x += umod();
      _v = (unsigned int)(x);
    }
    template <class T, is_unsigned_int_t<T>* = nullptr>
    static_modint(T v){
      _v = (unsigned int)(v%umod());
    }
    unsigned int val()const{return _v;}
    mint& operator++(){
      _v++;
      if(_v == umod()) _v = 0;
      return *this;
    }
    mint& operator--(){
      if(_v == 0) _v = umod();
      _v--;
      return *this;
    }
    mint operator++(int){
      mint result = *this;
      ++*this;
      return result;
    }
    mint operator--(int){
      mint result = *this;
      --*this;
      return result;
    }
    mint& operator+=(const mint& rhs){
      _v += rhs._v;
      if (_v >= umod()) _v -= umod();
      return *this;
    }
    mint& operator-=(const mint& rhs){
      _v += mod()-rhs._v;
      if (_v >= umod()) _v += umod();
      return *this;
    }
    mint& operator*=(const mint& rhs){
      unsigned long long z = _v;
      z *= rhs._v;
      _v = (unsigned int)(z % umod());
      return *this;
    }
    mint& operator/=(const mint& rhs){return *this = *this * rhs.inv();}
    mint operator+()const{return *this;}
    mint operator-()const{return mint() - *this;}
    mint pow(long long n)const{
      assert(0 <= n);
      mint x = *this, r = 1;
      while(n){
        if(n & 1) r *= x;
        x *= x;
        n >>= 1;
      }
      return r;
    }
    mint inv()const{
      if(is_prime_mod){
        assert(_v);
        return pow(umod() - 2);
      }else{
        auto eg = inv_gcd(_v, m);
        assert(eg.first == 1);
        return eg.second;
      }
    }
    friend mint operator+(const mint& lhs, const mint& rhs){
      return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs){
      return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs){
      return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs){
      return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs){
      return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs){
      return lhs._v != rhs._v;
    }
    private:
    static constexpr bool is_prime_mod = []()->bool{
      if(m == 1) return 0;
      if(m == 2 || m == 7 || m == 61) return 1;
      if(m % 2 == 0) return 0;
      unsigned int d = m-1;
      while(d % 2 == 0) d /= 2;
        for(unsigned int a:{2, 7, 61}){
          unsigned int t = d, t2 = d, a2 = a;
          //mint y = mint(a).pow(t);
          unsigned long long y = 1;
          while(t2){
            if(t2 & 1) y = y*a2%m;
            a2 = a2*a2%m;
            t2 >>= 1;
          }
          while(t != m-1 && y != 1 && y != m-1){
            y = y*y%m;
            t <<= 1;
          }
          if(y != m-1 && t % 2 == 0) return 0;
        }
      return 1;
    };
    unsigned int _v;
    static constexpr unsigned int umod(){return m;}
  };
  template<int id>
  struct dynamic_modint:modint_base{
    using mint = dynamic_modint;
    public:
    static int mod(){return (int)(bt.umod());}
    static void set_mod(int m){
      assert(1 <= m);
      bt = barrett(m);
    }
    static mint raw(int v){
      mint x;
      x._v = v;
      return x;
    }
    dynamic_modint():_v(0){}
    template <class T, is_signed_int_t<T>* = nullptr>
    dynamic_modint(T v){
      long long x = (long long)(v%(long long)(mod()));
      if(x < 0) x += mod();
      _v = (unsigned int)(x);
    }
    template <class T, is_unsigned_int_t<T>* = nullptr>
    dynamic_modint(T v){
      _v = (unsigned int)(v%mod());
    }
    unsigned int val()const{return _v;}
    mint& operator++(){
      _v++;
      if(_v == umod()) _v = 0;
      return *this;
    }
    mint& operator--(){
      if(_v == 0) _v = umod();
      _v--;
      return *this;
    }
    mint operator++(int){
      mint result = *this;
      ++*this;
      return result;
    }
    mint operator--(int){
      mint result = *this;
      --*this;
      return result;
    }
    mint& operator+=(const mint& rhs){
      _v += rhs._v;
      if(_v >= umod()) _v -= umod();
      return *this;
    }
    mint& operator-=(const mint& rhs){
      _v += mod()-rhs._v;
      if(_v >= umod()) _v += umod();
      return *this;
    }
    mint& operator*=(const mint& rhs){
      _v = bt.mul(_v, rhs._v);
      return *this;
    }
    mint& operator/=(const mint& rhs){return *this = *this * rhs.inv();}
    mint operator+()const{return *this;}
    mint operator-()const{return mint() - *this;}
    mint pow(long long n)const{
      assert(0 <= n);
      mint x = *this, r = 1;
      while(n){
        if(n & 1) r *= x;
        x *= x;
        n >>= 1;
      }
      return r;
    }
    mint inv()const{
      auto eg = inv_gcd(_v, mod());
      assert(eg.first == 1);
      return eg.second;
    }
    friend mint operator+(const mint& lhs, const mint& rhs){
      return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs){
      return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs){
      return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs){
      return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs){
      return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs){
      return lhs._v != rhs._v;
    }
    private:
    unsigned int _v;
    static barrett bt;
    static unsigned int umod() { return bt.umod(); }
  };
  template <int id> barrett dynamic_modint<id>::bt(998244353);
  using modint = dynamic_modint<-1>;
  using modint998244353 = static_modint<998244353>;
  using modint1000000007 = static_modint<1000000007>;
  using modint1000000009 = static_modint<1000000009>;
  #pragma GCC diagnostic pop
};using namespace math;
