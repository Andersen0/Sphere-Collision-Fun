import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
from itertools import product, combinations


def drawSphere(xCenter, yCenter, zCenter, r):
    #draw sphere
    u, v = np.mgrid[0:2*np.pi:20j, 0:np.pi:10j]
    x=np.cos(u)*np.sin(v)
    y=np.sin(u)*np.sin(v)
    z=np.cos(v)
    # shift and scale sphere
    x = r*x + xCenter
    y = r*y + yCenter
    z = r*z + zCenter
    return x, y, z


text_file = open("test.txt", "r")
data = text_file.read()
data_into_list = data.replace('\n', ' ').split(" ")
box_size = data_into_list.pop(0)
num_spheres = data_into_list.pop(0)
data_into_list.pop()
list_result = [data_into_list[idx:idx+3] for idx in range(0, len(data_into_list), 3)]
array_result = np.array(list_result)
test_array = [1, 2, 3, 4]
print(array_result)
print(test_array)
print(box_size)
print(num_spheres)
print(len(data_into_list))
text_file.close()

fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.axes.set_xlim3d(left=-25, right=25)
ax.axes.set_ylim3d(bottom=-25, top=25)
ax.axes.set_zlim3d(bottom=-25, top=25)

sphere_x = []
sphere_y = []
sphere_z = []

for sphere in array_result:
    sphere_x.append(float(sphere[0]))
    sphere_y.append(float(sphere[1]))
    sphere_z.append(float(sphere[2]))

# ax.scatter3D(sphere_x, sphere_y, sphere_z, s=1)

wall = [-25, 25]
for s, e in combinations(np.array(list(product(wall, wall, wall))), 2):
    if np.sum(np.abs(s-e)) == wall[1]-wall[0]:
        ax.plot3D(*zip(s, e), color="b")

r = np.ones(3000)

# draw a sphere for each data point
for (xi, yi, zi, ri) in zip(sphere_x, sphere_y, sphere_z, r):
    (xs, ys, zs) = drawSphere(xi, yi, zi, ri)
    ax.plot_wireframe(xs, ys, zs, color="r")


plt.show()
