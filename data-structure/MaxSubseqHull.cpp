struct MaxSubseqHull{
  struct Point{
    long long x,y;
  };
  MaxSubseqHull(vector<int> a):a(a){
    int n = a.size();
    hull = solve(0, n);
  }
  bool check(Point a, Point b, Point c){
    return (__int128_t)(b.x - a.x)*(c.y - a.y)-(__int128_t)(b.y - a.y)*(c.x - a.x) >= 0;
  }
  vector<Point> make_hull(vector<Point> p, int is_sorted = 0){
    if(!is_sorted){
      sort(p.begin(), p.end(), [](Point a, Point b){
        return a.x == b.x ? a.y > b.y : a.x < b.x;
      });
    }
    vector<Point> h;
    for(auto &x : p){
      if(h.size() > 0 && h.back().x == x.x) continue;
      while(h.size() > 1 && check(h[h.size() - 2], h.back(), x)){
        h.pop_back();
      }
      h.push_back(x);
    }
    return h;
  }
  vector<Point> max_plus_convolution(vector<Point> &a, vector<Point> &b){
    vector<Point> c;
    if((int)a.size() == 0 || (int)b.size() == 0) return c;
    c.push_back({a[0].x + b[0].x, a[0].y + b[0].y});
    for(int i = 0, j = 0; i < (int)a.size() - 1 || j < (int)b.size() - 1;){
      if(i == (int)a.size() - 1){
        c.push_back({a[i].x + b[j + 1].x, a[i].y + b[j + 1].y});
        j++;
      }else if(j == (int)b.size() - 1){
        c.push_back({a[i + 1].x + b[j].x, a[i + 1].y + b[j].y});
        i++;
      }else{
        __int128_t dx_a = a[i + 1].x - a[i].x;
        __int128_t dy_a = a[i + 1].y - a[i].y;
        __int128_t dx_b = b[j + 1].x - b[j].x;
        __int128_t dy_b = b[j + 1].y - b[j].y;
        if(dy_a * dx_b >= dy_b * dx_a){
          c.push_back({a[i + 1].x + b[j].x, a[i + 1].y + b[j].y});
          i++;
        }else{
          c.push_back({a[i].x + b[j + 1].x, a[i].y + b[j + 1].y});
          j++;
        }
      }
    }
    return c;
  }
  vector<Point> solve(int l, int r){
    int mid = (l + r) / 2;
    if(r - l == 0){
      return {};
    }
    if(r - l == 1){
      return {{1, a[l]}};
    }
    vector<Point> L_hell = solve(l, mid);
    vector<Point> R_hell = solve(mid, r);
    vector<Point> L, R;
    long long l_sum = 0, r_sum = 0;
    for(int i = mid-1; i >= l; i--){
      l_sum += a[i];
      L.push_back({mid - i, l_sum});
    }
    for(int i = mid; i < r; i++){
      r_sum += a[i];
      R.push_back({i - mid + 1, r_sum});
    }
    vector<Point> L_mid = make_hull(L, 1);
    vector<Point> R_mid = make_hull(R, 1);
    vector<Point> mid_hell = max_plus_convolution(L_mid, R_mid);
    vector<Point> ans;
    for(int i = 0, j = 0, k = 0; i < L_hell.size() || j < R_hell.size() || k < mid_hell.size();){
      Point A = i < L_hell.size() ? L_hell[i] : Point{LLONG_MAX, LLONG_MAX};
      Point B = j < R_hell.size() ? R_hell[j] : Point{LLONG_MAX, LLONG_MAX};
      Point C = k < mid_hell.size() ? mid_hell[k] : Point{LLONG_MAX, LLONG_MAX};
      if((A.x < B.x || A.x == B.x && A.y >= B.y) && (A.x < C.x || A.x == C.x && A.y >= C.y)){
        ans.push_back(A);
        i++;
      }else if((B.x < C.x || B.x == C.x && B.y >= C.y) && (B.x < A.x || B.x == A.x && B.y >= A.y)){
        ans.push_back(B);
        j++;
      }else{
        ans.push_back(C);
        k++;
      }
    }
    ans = make_hull(ans, 1);
    return ans;
  }
  vector<Point> get_hull(){
    return hull;
  }
  //凸包f(x)に対して, max(f(x) + x * k)を返す
  long long query(long long x) {
    if(hull.size() == 1){
      return hull[0].y + hull[0].x * x;
    }
    int l = -1;
    int r = (int)hull.size() - 1;
    while(r - l > 1){
      int mid = (l + r) / 2;
      long long v_mid = hull[mid].y + hull[mid].x * x;
      long long v_nx = hull[mid + 1].y + hull[mid + 1].x * x;
      if(v_mid > v_nx){
        r = mid;
      }else{
        l = mid;
      }
    }
    return hull[r].y + hull[r].x * x;
  }
  private:
  int n;
  vector<int> a;
  vector<Point> hull;
};
