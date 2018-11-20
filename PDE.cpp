#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define N 200

double fronteras(int z,int i,int j,double f[N][N]);
void PDE(int z, double tiempo);

int main(){
  PDE(1,30000.0);
  PDE(2,400000.0);
  PDE(3,400000.0);
}

//Funcion que determina las condiciones de frontera correspondientes al caso dado y a la posicion.
double fronteras(int z,int i,int j,double f[N][N]){
  if(z==1){
    return 10.0;
  }
  else if(z==2){
    if(i==0.0){
      return f[j][i+1];
    }
    else if(j==0.0){
      return f[j+1][i];
    }
    else if(i==N-1){
      return f[j][i-1];
    }
    else{
      return f[j-1][i];
    }
  }
  else{
    if(i==N-1 || i==0){
      return f[j][N-2];
    }
    else{
      return f[N-2][i];
    }
  }
  return -1;
}

//Funcion que dado el caso correspondiente calcula la distribucion de temperaturas en el tiempo. Guarda archivos con 4 tiempos diferentes.
void PDE(int z, double tiempo){
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
  for(int t=0;t<tiempo/dt;t++){
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
    for(int j=0;j<N;j++){
      for(int i=0;i<N;i++){
        if(i==0 || i==N-1 || j==0 || j==N-1){
          futuro[j][i]=fronteras(z,i,j,futuro);
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
    if(t==0 || t==int(tiempo/dt-1) || t==int(tiempo/(dt*6.0)) || t==int(tiempo/(dt*4.0))){
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
