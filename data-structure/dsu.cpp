struct dsu{
  vector<int> parent;
  dsu(int n):parent(n, -1){}
  int root(int k){return parent[k] < 0 ? k : parent[k] = root(parent[k]);}
  int merge(int x, int y){
    if((x = root(x)) == (y = root(y))) return false;
    if(parent[x] > parent[y]) swap(x, y);
    parent[x] += parent[y];
    parent[y] = x;
    return true;
  }
  int size(int k){return -parent[root(k)];}
  int same(int x, int y){return root(x) == root(y);}
};
