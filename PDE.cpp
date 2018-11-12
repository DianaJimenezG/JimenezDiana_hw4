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
   for(int i=0;i<N;i++){
     for(int j=0;j<N;j++){
       if(((x[i] - N/2) * (x[i] - N/2) + (y[j] - N/2) * (y[j] - N/2)) < r * r){
         presente[j][i]=100.0;
       }
       else if(((x[i] - N/2) * (x[i] - N/2) + (y[j] - N/2) * (y[j] - N/2)) == r * r){
         presente[j][i]=10.0;
       }
       else{
         presente[j][i]=0.0;
       }
     }
   }

//Primera iteracion
   double futuro[N][N];
   double dt=0.0000001;

   for(int t=0;t<0.1/dt;t++){
     for(int i=0;i<N;i++){
       for(int j=0;j<N;j++){
         if(((x[i] - N/2) * (x[i] - N/2) + (y[j] - N/2) * (y[j] - N/2)) >= r * r){
           futuro[i][j]=dt*v/1*((presente[i+1][j]+presente[i-1][j]-2.0*presente[i][j])+(presente[i][j+1]+presente[i][j-1]-2.0*presente[i][j]))+presente[i][j];
         }
       }
     }
     for(int i=0;i<N;i++){
       for(int j=0;j<N;j++){
         presente[i][j]=futuro[i][j];
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
