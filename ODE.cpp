define _USE_MATdt_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define g 10.0
#define m 0.2
#define c 0.2
#define dt 0.00001
#define tiempo 7.0

double ddx(double vx);
double ddy(double vy);
double ddvx(double vx, double vy);
double ddvy(double vx, double vy);
double * RungeKutta(double t_pasado, double x_pasado, double y_pasado, double vx_pasado, double vy_pasado);

int main(){
  double t=0.0;
  double x=0.0;
  double y=0.0;
  double vx;
  double vy;

  ofstream archivo1;
  archivo1.open("45_RK.txt");
  vx=300*cos(45*M_PI/180);
  vy=300*sin(45*M_PI/180);
  for(int i=0; i<int(tiempo/dt); i++){
    if(y>=0.0){
      archivo1 << t << " " << x << " " << y << " " << vx << " " << vy << endl;
      t=RungeKutta(t, x, y, vx, vy)[0];
      x=RungeKutta(t, x, y, vx, vy)[1];
      y=RungeKutta(t, x, y, vx, vy)[2];
      vx=RungeKutta(t, x, y, vx, vy)[3];
      vy=RungeKutta(t, x, y, vx, vy)[4];
    }
  }
  cout << "Distancia recorrida =" << x << " [m]" << endl;
  archivo1.close();

  double xi[7];
  for(int i=1;i<8;i++){
    ofstream archivo2;
    archivo2.open(to_string(10*i)+"_RK.txt");
    t=0.0;
    x=0.0;
    y=0.0;
    vx=300*cos(10*i*M_PI/180);
    vy=300*sin(10*i*M_PI/180);
    for(int i=0;i<int(tiempo/dt);i++){
      if(y>=0.0){
        archivo2 << t << " " << x << " " << y << " " << vx << " " << vy << endl;
        t=RungeKutta(t, x, y, vx, vy)[0];
        x=RungeKutta(t, x, y, vx, vy)[1];
        y=RungeKutta(t, x, y, vx, vy)[2];
        vx=RungeKutta(t, x, y, vx, vy)[3];
        vy=RungeKutta(t, x, y, vx, vy)[4];
      }
    }
    xi[i-1]=x;
    archivo2.close();
  }
  double x_max=*max_element(begin(xi), end(xi));
  for(int i=1;i<sizeof(xi);i++){
    if(x_max==xi[i]){
      cout << "La mayor distancia recorrida es " << x_max << " [m] a un angulo de " << (i+1)*10.0 << endl;
    }
  }
}

double ddx(double vx){
  return vx;
}

double ddy(double vy){
  return vy;
}

double ddvx(double vx, double vy){
  return -c*sqrt(vx*vx+vy*vy)*vx/m;
}

double ddvy(double vx, double vy){
  return -g-c*sqrt(vx*vx+vy*vy)*vy/m;
}

double * RungeKutta(double t_pasado, double x_pasado, double y_pasado, double vx_pasado, double vy_pasado){
  double k_1_x=ddx(vx_pasado);
  double k_1_y=ddy(vy_pasado);
  double k_1_vx=ddvx(vx_pasado,vy_pasado);
  double k_1_vy=ddvy(vx_pasado,vy_pasado);

  double x_1=x_pasado+(dt/2.0)*k_1_x;
  double y_1=y_pasado+(dt/2.0)*k_1_y;
  double vx_1=vx_pasado+(dt/2.0)*k_1_vx;
  double vy_1=vy_pasado+(dt/2.0)*k_1_vy;
  double k_2_x=ddx(vx_1);
  double k_2_y=ddy(vy_1);
  double k_2_vx=ddvx(vx_1, vy_1);
  double k_2_vy=ddvy(vx_1, vy_1);

  double x_2=x_pasado+(dt/2.0)*k_2_x;
  double y_2=y_pasado+(dt/2.0)*k_2_y;
  double vx_2=vx_pasado+(dt/2.0)*k_2_vx;
  double vy_2=vy_pasado+(dt/2.0)*k_2_vy;
  double k_3_x=ddx(vx_2);
  double k_3_y=ddy(vy_2);
  double k_3_vx=ddvx(vx_2, vy_2);
  double k_3_vy=ddvy(vx_2, vy_2);

  double x_3=x_pasado+dt*k_3_x;
  double y_3=y_pasado+dt*k_3_y;
  double vx_3=vx_pasado+dt*k_3_vx;
  double vy_3=vy_pasado+dt*k_3_vy;
  double k_4_x=ddx(vx_3);
  double k_4_y=ddy(vy_3);
  double k_4_vx=ddvx(vx_3, vy_3);
  double k_4_vy=ddvy(vx_3, vy_3);

  double promedio_k_1=(1.0/6.0)*(k_1_x+2.0*k_2_x+2.0*k_3_x+k_4_x);
  double promedio_k_2=(1.0/6.0)*(k_1_y+2.0*k_2_y+2.0*k_3_y+k_4_y);
  double promedio_k_3=(1.0/6.0)*(k_1_vx+2.0*k_2_vx+2.0*k_3_vx+k_4_vx);
  double promedio_k_4=(1.0/6.0)*(k_1_vy+2.0*k_2_vy+2.0*k_3_vy+k_4_vy);

  static double rk[5];
  rk[0]=t_pasado+dt;
  rk[1]=x_pasado+dt*promedio_k_1;
  rk[2]=y_pasado+dt*promedio_k_2;
  rk[3]=vx_pasado+dt*promedio_k_3;
  rk[4]=vy_pasado+dt*promedio_k_4;

  return rk;
}
