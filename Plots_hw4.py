import numpy as np
import matplotlib.pyplot as plt
import sys

#if __name__ == '__main__':
#    dat=sys.argv[1]
#    output_file = sys.argv[2]

T = np.genfromtxt('PDE.txt')
s = T.shape
x = np.linspace(0, s[1]-1, s[1])
y = np.linspace(0, s[0]-1, s[0])
xv, yv = np.meshgrid(x, y)

g = plt.figure(1)
plt.title("Distribucion de temperaturas")
plt.contourf(xv, yv, T, 50, cmap = 'jet')
plt.colorbar(label = 'Temperatura')
plt.show()
#g.savefig('p.pdf')
