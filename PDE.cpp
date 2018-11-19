#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define N 200

void PDE(int z);

int main(){
  PDE(1);
}




void PDE(int z){
  double k=1.62;
  double c=820.0;
  double rho=2710.0;
  double v=k/(c*rho);
  double L=0.5;
  double r=0.05;
  double dx=L/N;
  double dy=dx;
  double dt=(dx*dx*dy*dy)/(2.0*v*(dx*dx+dy*dy));

  double presente[N][N];
  double futuro[N][N];
  double promedio;

  ofstream prom;
  prom.open("promedio_"+to_string(z)+".txt");
//Derivadas
  for(int t=0;t<30000.0/dt;t++){
    for(int j=1;j<N-1;j++){
      for(int i=1;i<N-1;i++){
        if(t==0.0){
          if(((i*dx-L/2.0)*(i*dx-L/2.0)+(j*dy-L/2.0)*(j*dy-L/2.0))<=r*r){
            presente[j][i]=100.0;
            futuro[j][i]=presente[j][i];
          }
          else{
            presente[j][i]=10.0;
            futuro[j][i]=presente[j][i];
          }
        }
        else{
          if(((i*dx-L/2.0)*(i*dx-L/2.0)+(j*dy-L/2.0)*(j*dy-L/2.0))>r*r){
            futuro[j][i]=((dt*v)/(dx*dx))*(presente[j+1][i]+presente[j-1][i]+presente[j][i+1]+presente[j][i-1]-4.0*presente[j][i])+presente[j][i];
          }
          else{
            futuro[j][i]=100.0;
          }
        }
      }
    }
    promedio=0.0;
    for(int j=0;j<N;j++){
      for(int i=0;i<N;i++){
        presente[j][i]=futuro[j][i];
        promedio+=presente[j][i];
      }
    }
    prom << t*dt << " " << promedio/(N*N) << endl;
    if(t==0 || t==int(30000.0/dt-1) || t==500 || t==1000){
      ofstream datos;
      datos.open(to_string(t*dt)+"_"+to_string(z)+".txt");
      for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
          datos << presente[i][j] << " ";
        }
        datos << endl;
      }
      datos.close();
    }
  }
  prom.close();
}
