
import os
import random as rd
if not os.path.isdir("Detection"):
    os.mkdir("Detection")
    
f1=open("Detection\\_SourceDefine.txt",'w')
f2=open("Detection\\0_RamdomData.txt",'w')
f3=open("Detection\\0_Activity.txt",'w')


NuSources=35#随机时设置
radius=0.0
angle=0.0
height=0.0
NoEnergy=[0,1,2,5]#MeV
activity=10000000.0#bq
SumActivity=0.0

activitytemp=0.0

#设置
#废物桶半径，cm
ROfWD=35
#废物桶高度，cm
HOfWD=105

#发射源是否随机分布
IsRandom=False
#密度，g/cm3
density=0.5
#测量方式//SGS ISGS STGS2ER STGS2EB STGS4ER STGS4EB STGS8ER STGS8EB *****
DetectionType="SGS"
#源高度
height=47.25

#随机分布单桶99个点源，
NuDrums=99 if IsRandom else 14

#输出
for nDrum in range(NuDrums):
    f1.write("$$Drum"+str(nDrum+1)+"\n")
    f1.write("Detection:"+str(DetectionType)+";\n")
    f1.write("Density:"+str(density)+";\n")
    SumActivity=0
    
    if not IsRandom:
        NuSources=4
        radius=1.0*nDrum*ROfWD/NuDrums
        for nSource in range(NuSources):
            f1.write("##Source"+str(nSource+1)+'\n')
            f1.write("Radius:"+str(radius)+";\n")
            f1.write("Angle:"+str(angle)+";\n")
            f1.write("Height:"+str(height)+";\n")
            f1.write("NoEnergy:"+str(NoEnergy[nSource])+";\n")
            SumActivity+=activity
    else:
        for nSource in range(NuSources):
            if nSource%4==0:
                
                tmp=rd.randint(0,999)
                rand1=HOfWD*((rand()*tmp)%10000)/10000.0
                rand2=ROfWD*sqrt(((rand()*tmp)%10000)/10000.0)
                rand3=((rand()*tmp)%10000)/10000.0
                height=rand1
                radius=rand2
                activitytemp=activity*(0.25+0.75*rand3)
                SumActivity+=activitytemp
                f2.write(str(rand1)+" "+str(rand2)+" "+str(rand3)+"\n")
            
            f1.write("##Source"+str(nSource+1)+'\n')
            f1.write("Radius:"+str(radius)+";\n")
            f1.write("Angle:"+str(angle)+";\n")
            f1.write("Height:"+str(height)+";\n")
            f1.write("NoEnergy:"+str(NoEnergy[nSource%4])+";\n")
            f1.write("activity:"+str(activitytemp)+";\n")
    
    f1.write("**SumA:"+str(SumActivity)+";\n")
    f1.write("\n")
    
    f3.write("End\n")
    
                    
                       