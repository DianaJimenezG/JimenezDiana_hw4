#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

#define N 501

int main(){
   double k=1620;
   double c=820000000;
   double rho=0.00000271;
   double v=k/(c*rho);
   double r=50;

//Posiciones x y y.
   double x[N];
   double y[N];
   x[0]=0.0;
   y[0]=0.0;
   for(int i=1;i<N;i++){
      x[i]=x[i-1]+1;
      y[i]=y[i-1]+1;
   }

//Condicion inicial.
   double presente[N][N];
   double futuro[N][N];
   double dt=1/(2.0*v);
   for(int i=0;i<N;i++){
     for(int j=0;j<N;j++){
       if(((x[i] - 250) * (x[i] - 250) + (y[j] - 250) * (y[j] - 250)) < r * r){
         presente[j][i]=100.0;
         futuro[j][i]=presente[j][i];
       }
       else if(((x[i] - 250) * (x[i] - 250) + (y[j] - 250) * (y[j] - 250)) == r * r){
         presente[j][i]=10.0;
         futuro[j][i]=presente[j][i];
       }
       else{
         presente[j][i]=10.0;
         futuro[j][i]=presente[j][i];
       }
     }
   }

//Primera iteracion
   for(int t=0;t<1.0/dt;t++){
     for(int j=0;j<N;j++){
       for(int i=0;i<N;i++){
         if(((x[i] - 250) * (x[i] - 250) + (y[j] - 250) * (y[j] - 250)) > r * r){
           futuro[j][i]=(dt*v)/(1.0*1.0)*(presente[j+1][i]+presente[j-1][i]+presente[j][i+1]+presente[j][i-1]-4.0*presente[j][i])+presente[j][i];
         }
       }
     }
     for(int j=0;j<N;j++){
       for(int i=0;i<N;i++){
         presente[j][i]=futuro[j][i];
       }
     }
   }

//Salida de datos.
   ofstream datos;
   datos.open("PDE.txt");
   for(int i=0;i<N;i++){
     for(int j=0;j<N;j++){
       datos << presente[i][j] << " ";
     }
     datos << endl;
   }
   datos.close();
}
