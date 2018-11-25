#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define T double
T c(T x,T y,T r){return sqrt(x*x+y*y)-r;}
T u(T x,T y,T t){return x*cos(t)+y*sin(t);}
T v(T x,T y,T t){return y*cos(t)-x*sin(t);}
T fa(T x,T y){return fmin(c(x,y,0.5),c(x*0.47+0.15,y+0.25,0.3));}
T no(T x,T y){return c(x*1.2+0.97,y+0.25,0.2);}
T nh(T x,T y){return fmin(c(x+0.9,y+0.25,0.03),c(x+0.75,y+0.25,0.03));}
T ea(T x,T y){return fmin(c(x*1.7+0.  3,y+0.7,0.15),c(u(x,y,0.25)*1.7,v(x,y,0.25)+0.65,0.15));}
T ey(T x,T y){return fmin(c(x+0.4,y+0.35,0.1),c(x+0.15,y+0.35,0.1));}
T pu(T x,T y){return fmin(c(x+0.38,y+0.33,0.03),c(x+0.13,y+0.33,0.03));}
T fr(T x,T y){return c(x*1.1-0.3,y+0.1,0.15);}
T mo(T x,T y){return fmax(c(x+0.15,y-0.05,0.2),-c(x+0.15,y,0.25));}
T o(T x,T y,T(*f)(T,T),T i){T r=f(x,y);return fabs(r)<0.02?(atan2(f(x,y+1e-3)-r,f(x+1e-3,y)-r)+0.3)*1.273+6.5:r<0?i:0;}
T s(T x,T y,T(*f)(T,T),T i){return f(x,y)<0?i:0;}
T f(T x,T y){return o(x,y,no,1)?fmax(o(x,y,no,1),s(x,y,nh,12)):fmax(o(x,y,fa,1),fmax(o(x,y,ey,11),fmax(o(x,y,ea,1),fmax(o(x,y,mo,1),fmax(s(x,y,fr,13),s(x,y,pu,12))))));}
int main(int a,char**b){freopen("pig.out", "w", stdout);for(T y=-1,s=a>1?strtod(b[1],0):1;y<0.6;y+=0.05/s,putchar('\n'))for(T x=-1;x<0.6;x+=0.025/s)putchar(" .|/=\\|/=\\| @!"[(int)f(u(x,y,0.3),v(x,y,0.3))]);}
