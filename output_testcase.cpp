#include <iostream>
using namespace std;

class repete{
public:
  void print(int x,int i){
    cout << "Case " << i << ": " << x << "\n";
  }
};


int main(){
  int i=0;
  int x;
  repete rep;
  while(1){
    cin >> x;
    if(x == 0)break;
    else {
      i++;
      rep.print(x,i);
    }
  }
}
