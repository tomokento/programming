#include <iostream>
#include <iomanip>
using namespace std;

class AB{

public:
  void division1(int a,int b){
    int ans_d,ans_r;
    double ans_f;
    ans_d = a/b;
    ans_r = a%b;
    ans_f = (double)a/b;
    //整数同士の計算結果は小数点以下が切り捨てられてしまうから
    //整数の計算ではなく、必ずdouble型の計算として結果を出さなければいけない。
    cout << ans_d << " " << ans_r << " " << fixed << setprecision(6) << ans_f << "\n";
    //<< fixed << setprecision << 変数　とすることで浮動小数点(小数点以下の細かい値)
    //を出すことができる
    };
};

int main(){

  AB ab;
  int a,b;
  cin >> a >> b;

  ab.division1(a,b);


}
