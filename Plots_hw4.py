import numpy as np
import matplotlib.pyplot as plt
import sys

if __name__ == '__main__':
    for i in range(1,len(sys.argv)):
        input_file=sys.argv[i]
        dat=np.genfromtxt(input_file)
        if(input_file.split("_")[1]!="RK.txt" and input_file.split("_")[0]!="promedio"):
            fig=plt.figure(i+1)
            ax=fig.gca(projection='3d')
            plt.xlabel("x (cm)")
            plt.ylabel("y (cm)")
            plt.title("Caso "+input_file.split("_")[1].split(".")[0]+": Distribucion de temperaturas en t="+input_file.split(".")[0]+"."+input_file.split(".")[1].split("_")[0])
            x = np.linspace(-25, 25, dat.shape[1])
            y = np.linspace(-25, 25, dat.shape[0])
            X, Y = np.meshgrid(x, y)
            surf = ax.plot_surface(X, Y, dat, cmap="jet", linewidth=0, antialiased=False, vmin = 10, vmax = 100)
            ax.set_zlim(10, 100)
            fig.colorbar(surf, label = "Temperatura (C)")
            #plt.show(i+1)
            fig.savefig(input_file.split("_")[0]+"_"+input_file.split("_")[1].split(".")[0]+".pdf")
            plt.close(i+1)

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
    plt.close(1)

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
            plt.close(i*100)


    s=plt.figure(80)
    plt.title('Trayectorias del proyectil con diferentes angulos')
    for i in range(1,len(sys.argv)):
        input_file=sys.argv[i]
        if(input_file.split("_")[1]=="RK.txt" and input_file!="45_RK.txt"):
            dat=np.genfromtxt(input_file)
            t=dat[:,0]
            x=dat[:,1]
            y=dat[:,2]
            plt.plot(x,y,label=input_file.split("_")[0])
    plt.legend()
    plt.xlabel('x')
    plt.ylabel('y')
    #plt.show(4)
    s.savefig('trayectorias.pdf')
    plt.close(80)
