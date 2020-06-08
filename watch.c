#include <stdio.h>
  int main(){
    int s,m,m_other,h,h_other,input;

    scanf("%d",&input);

    h = input / 3600;
    h_other = input % 3600;
    m = h_other / 60;
    m_other = h_other % 60;
    s = m_other;
    printf("%d:%d:%d\n",h,m,s);
    return 0;
  }
