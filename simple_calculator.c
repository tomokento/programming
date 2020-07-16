#include <stdio.h>

  int main(){

    int a,b;
    char op;
    int ans;

      while(1){
        scanf("%d %c %d",&a,&op,&b);

        //文字列の囲いは　'　'　を使うこと " "だと
        //コンパイルエラーになる。

        if(op == '+'){
          ans = a+b;
        }
        else if(op == '-')ans = a - b;
        else if(op == '*')ans = a*b;
        else if(op == '/')ans = a/b;
        else break;
//\nを間違えないこと、
        printf("%d\n",ans);
    }
  }
