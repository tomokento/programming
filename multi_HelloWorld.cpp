#include <iostream>
//std::out change into cout ,cin
using namespace std;

class Hello{
    //関数は基本的にpublic
    public:
    void communication(){
        cout << "Hello World\n";
    }
};


int main(){
    Hello glee;
    for(int i=0;i<1000;i++){
    glee.communication();
    //cout << "Hello World\n";

  }

}
