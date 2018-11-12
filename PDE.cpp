#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

#define N 501

int main(){
   double k=1.62;
   double c=820.0;
   double rho=2.71;
   double v=k/(c*rho);
   double r=50;

   double x[N];
   double y[N];
   x[0]=0.0;
   y[0]=0.0;
   for(int i=1;i<N;i++){
      x[i]=x[i-1]+1;
      y[i]=y[i-1]+1;
   }

   double m[N][N];
   for(int i=0;i<N;i++){
     for(int j=0;j<N;j++){
       if(((x[i] - N/2) * (x[i] - N/2) + (y[j] - N/2) * (y[j] - N/2)) <= r * r){
         m[j][i]=100.0;
       }
       else{
         m[j][i]=0.0;
       }
     }
   }

   ofstream datos;
   datos.open("PDE.txt");
   for(int i=0;i<N;i++){
     for(int j=0;j<N;j++){
       datos << m[i][j] << " ";
     }
     datos << endl;
   }
   datos.close();
}
