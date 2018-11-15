#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

#define N 200

int main(){
  double k=1.62;
  double c=820;
  double rho=2710;
  double v=k/(c*rho);
  double L=0.5;
  double r=0.05;
  double dx=L/N;
  double dy=dx;
  double dt=(dx*dx*dy*dy)/(2.0*v*(dx*dx+dy*dy));

  double presente[N][N];
  double futuro[N][N];
  double m[N][N];

//Condicion inicial.
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if(((i*dx-L/2.0)*(i*dx-L/2.0)+(j*dy-L/2.0)*(j*dy-L/2.0))<=r*r){
        presente[j][i]=100.0;
        futuro[j][i]=presente[j][i];
      }
      else{
        presente[j][i]=10.0;
        futuro[j][i]=presente[j][i];
      }
    }
  }

//Derivadas
  for(int t=0;t<20000.0/dt;t++){
    for(int j=1;j<N-1;j++){
      for(int i=1;i<N-1;i++){
        if(((i*dx-L/2.0)*(i*dx-L/2.0)+(j*dy-L/2.0)*(j*dy-L/2.0))>r*r){
          futuro[j][i]=((dt*v)/(dx*dx))*(presente[j+1][i]+presente[j-1][i]+presente[j][i+1]+presente[j][i-1]-4.0*presente[j][i])+presente[j][i];
        }
        else{
          futuro[j][i]=100.0;
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
