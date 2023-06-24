#include<bits/stdc++.h>
using namespace std;
//実行時間制限
constexpr double kTimeLimit = 5.0;

//乱数
class XorShift{
private:
  uint32_t w,x,y,z,t;
public:
  XorShift(uint32_t w=10101010,uint32_t x=193020102,uint32_t y=30203021,uint32_t z=203902765){
    this->w=w;this->x=x;this->y=y;this->z=z;
  }
  uint32_t next(){
    t=x^(x<<11);
    x=y;y=z;z=w;
    return w=(w^(w>>19))^(t^(t>>8));
  }
};
random_device seed;
mt19937 engine(seed());
XorShift rt(engine());
//[a, b]
long long rand(long long a, long long b){
  return a+rt.next()%(b-a+1);
}

//時間
auto Now() {
  return std::chrono::high_resolution_clock::now();
}
struct Timer {
  Timer() : start(Now()) {} 
  double GetTime() {
    return std::chrono::duration<double>(Now() - start).count();
  }
  const decltype(Now()) start;
};
double myexp(double x){
  double total = 1.0;
  double a = 1.0;
  for(int i = 1; i < 10; i++){
    a = a / i * x;
    total += a;
  }
  return total;
}
struct state_simple{
};
struct state{
  //状態を持つ変数 state_now
  //状態を持つ変数  best_state = 
  stack<state_simple> st;
  //初期化
  void init(){
  }
  //遷移
  double modify(){
    //ランダムにstate_nowを変更し、変更前の状態をstackに積む
    double diff = 0;
    //差分を計算する
    return diff;
  }
  //焼きなまし
  void run(){
    Timer timer;
    double last_time = timer.GetTime();
    double max_time = 0.0;
    double score = 0.0, best_score = 0.0;
    double start_temp;//スコア幅の最大
    double end_temp;//スコア幅の最小
    while (last_time + 2.0 * max_time < kTimeLimit) {
      double temp = start_temp + (end_temp - start_temp) * last_time / kTimeLimit;
      double diff = modify();
      double prob = myexp(diff/temp);
      if(prob > rt.next()%((int)1e9)/(1e9)){
        score += diff;
        if(best_score < score){
          best_score = score;
          best_state = state_now;
        }
      }else{
        while(!st.empty()){
          //遷移を戻す
        }
      }
      const auto time = timer.GetTime();
      max_time = max(max_time, time - last_time);
      last_time = time;
    }
  }
};
