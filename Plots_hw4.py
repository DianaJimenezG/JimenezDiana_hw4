import numpy as np
import matplotlib.pyplot as plt
import sys

if __name__ == '__main__':
    for i in range(1,len(sys.argv)):
        input_file=sys.argv[i]
        dat=np.genfromtxt(input_file)
        if(input_file.split("_")[1]!="RK.txt" and input_file.split("_")[0]!="promedio"):
            h=plt.figure(i+1)
            plt.title("Caso "+input_file.split("_")[1].split(".")[0]+": Distribucion de temperaturas en t="+input_file.split(".")[0]+"."+input_file.split(".")[1].split("_")[0])
            plt.imshow(dat, cmap="jet", vmin=10.0, vmax=100.0)
            plt.colorbar(label='Temperatura')
            #plt.show(2)
            h.savefig(input_file.split("_")[0]+"_Caso"+input_file.split("_")[1].split(".")[0]+".pdf")

    g=plt.figure(1)
    plt.title("Temperatura promedio en el tiempo")
    for i in range(1,len(sys.argv)):
        input_file=sys.argv[i]
        if(input_file.split("_")[1]!="RK.txt" and input_file.split("_")[0]=="promedio"):
            dat=np.genfromtxt(input_file)
            t=dat[:,0]
            p=dat[:,1]
            plt.plot(t,p,label="Caso "+input_file.split(".")[0].split("_")[1])
    plt.legend()
    plt.xlabel('Tiempo')
    plt.ylabel('Temperatura promedio')
    #plt.show(1)
    g.savefig('promedios.pdf')

    for i in range(1,len(sys.argv)):
        input_file=sys.argv[i]
        if(input_file=="45_RK.txt"):
            dat=np.genfromtxt(input_file)
            t=dat[:,0]
            x=dat[:,1]
            y=dat[:,2]
            j=plt.figure(i*100)
            plt.title("Trayectoria del proyectil con angulo de 45")
            plt.plot(x,y)
            plt.xlabel('x')
            plt.ylabel('y')
            #plt.show(4)
            j.savefig(str(input_file.split(".")[0])+".pdf")
