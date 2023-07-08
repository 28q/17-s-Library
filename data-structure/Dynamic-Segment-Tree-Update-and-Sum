struct DinamicLazySegmentTreeUpdateSum{
  struct node{
    long long value;
    long long lazy;
    bool islz;
    node* left;
    node* right;
    node(long long value) : value(value), left(nullptr), right(nullptr) {
      islz = false;
    };
  };
  int n;
  node* root = new node(0);
  void mk(node*& t){
    if(!t) t = new node(0);
  }
  void eval(node*& t){
    if(t->islz == false) return;
    mk(t->left);
    t->left->lazy = t->lazy/2;
    t->left->islz = true;
    mk(t->right);
    t->right->lazy = t->lazy/2;
    t->right->islz = true;
    t->value = t->lazy;
    t->islz = false;
  }
  void update(node*& t, long long a, long long b, long long l, long long r, long long x){
    mk(t);
    eval(t);
    if(b <= l || r <= a) return;
    if(l <= a && b <= r){
      t->lazy = x*(b-a);
      t->islz = true;
      eval(t);
      return;
    }
    if(a-b != 1){
      long long c = (a+b)>>1;
      update(t->left, a, c, l, r, x);
      update(t->right, c, b, l, r, x);
    }
    t->value = t->left->value + t->right->value;
  }
  long long sum(node*& t, long long a, long long b, long long l, long long r){
    if(!t || b <= l || r <= a) return 0;
    eval(t);
    if(l <= a && b <= r) return t->value;
    long long c = (a+b)>>1;
    return sum(t->left, a, c, l, r) + sum(t->right, c, b, l, r);
  }
  //[a, b) -> x
  void update(long long a, long long b, long long x){
    update(root, -(1LL<<62), (1LL<<62), a, b, x);
  }
  //sum[a, b)
  long long sum(long long a, long long b){
    return sum(root, -(1LL<<62), (1LL<<62), a, b);
  }
};
