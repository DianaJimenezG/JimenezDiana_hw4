import numpy as np
import matplotlib.pyplot as plt
import sys

if __name__ == '__main__':
    for i in range(1,5):
        input_file=sys.argv[i]

        T=np.genfromtxt(input_file)
        g=plt.figure(1)
        plt.title("Distribucion de temperaturas "+input_file.split(".")[0]+"."+input_file.split(".")[1])
        plt.imshow(T, cmap="jet")
        plt.colorbar(label='Temperatura')
        plt.show(str(input_file.split(".")[0])+".txt")
        #g.savefig(str(input_file.split(".")[0])+".pdf")

    g=plt.figure(2)
    plt.title('Temperatura promedio en el tiempo')
    for i in range(5,6):
        input_file=sys.argv[i]

        dat=np.genfromtxt(input_file)
        t=dat[:,0]
        p=dat[:,1]

        plt.plot(t,p,label="Caso "+input_file.split(".")[0].split("_")[1])
    plt.legend()
    plt.xlabel('Tiempo')
    plt.ylabel('Temperatura promedio')
    plt.show()
    #plt.savefig('promedios.pdf')
