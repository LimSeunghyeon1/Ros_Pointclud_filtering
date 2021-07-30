import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
x=list()
y=list()
z=list()
f=open('3rd/soa3.txt','r')
if f is None:
    print("not opened")
while True:
    line=f.readline().rstrip()
    temp_list=line.split(' ')
    #print(temp_list)
    if len(temp_list)==3:
        #print("here")
        x.append(float(temp_list[0]))
        y.append(float(temp_list[1]))
        z.append(float(temp_list[2]))
    #print(temp_list)
    if not line: break
    #print(line)
f.close()
x=np.array(x)
y=np.array(y)
z=np.array(z)
x_result=["1.0~1.1","1.1~1.2","1.2~1.3","1.3~1.4","1.4~1.5"]
point_zero=0
point_one=0
point_two=0
point_three=0
point_four=0
for i in x:
    if i>=1.0 and i<=1.1:
        point_zero+=1
    elif i>1.1 and i<=1.2:
        point_one+=1
    elif i>1.2 and i<=1.3:
        point_two+=1
    elif i>1.3 and i<=1.4:
        point_three+=1
    elif i>=1.4 and i<=1.5:
        point_four+=1

print(f"mean value: x: {round(np.mean(x),3)}, y: {round(np.mean(y),3)}, z: {round(np.mean(z),3)}")
print(f"stdev value: x: {round(np.std(x),3)}, y: {round(np.std(y),3)}, z: {round(np.std(z),3)}")
print(f"length {len(x)}")
plt.plot([i for i in x_result],[point_zero,point_one,point_two,point_three,point_four])
plt.xlabel('X(m)')
plt.ylabel('Points')
plt.title('Soa PointCloud data')
#print(f"x size is {len(x)} y size is {len(y)} and z size is {len(z)}")
plt.show()
print("finished")
