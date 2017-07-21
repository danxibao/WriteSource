#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include<time.h>
using namespace std;

double RandomData[10000][3];
double ROfWD=35,HOfWD=105;
//	int seed[50]={25,13,185,3,1972,554,621,32,19,785,453,1563,951,1,23,55,69,1951,463,251,764,444,6,17,91,2645,333,1789,675,385,18,562,2245,3621,741,621,95,273,82,43,351,26,54,61,375,951,4421,3562,158,491};
//	static double seeddata[3];
int main()
{
	void RandomDataGeneration();
	RandomDataGeneration();

	ofstream output;
	output.open("_SourceDefine.txt",ios::trunc); 
	ofstream output2;
	output2.open("0_RamdomData.txt",ios::trunc); 
	ofstream output3;
	output3.open("0_Activity.txt",ios::trunc); 
	//
	int NuDrums;
	double density;

	int NuSources=35;//随机时设置 
	double radius;//cm
	double angle=0;//度
	double height;//cm，源的高度
	int NoEnergy[4]={0,1,2,5};//MeV 
	double activity=10000000;//bq
	double SumActivity=0;
	int nRamData=0;
	double activitytemp;	

	//设置;
	ROfWD=35;//废物桶半径，cm
	HOfWD=105;//废物桶高度，cm

	//发射源是否随机分布
	bool IsRandom=false;
	//1，密度;
	density=0.5;//g/cm3 *****
	//2，测量方式
	char DetectionType[10]={"SGS"};//SGS ISGS STGS2ER STGS2EB STGS4ER STGS4EB STGS8ER STGS8EB *****
	//3，源高度;
	height=47.25;//cm，源的高度;

	if(!IsRandom) NuDrums=14;
	else NuDrums=99;
	//输出
	for(int nDrum=0;nDrum<NuDrums;nDrum++)
	{
		//废物桶号
		output<<"$$Drum"<<nDrum+1<<endl;
		//密度
		output<<"Detection:"<<DetectionType<<";"<<endl;
		//密度
		output<<"Density:"<<density<<";"<<endl;
		SumActivity=0;		

	if(!IsRandom)
	{
		//源沿半径等分
		NuSources=4;
		radius=nDrum*ROfWD/NuDrums;
		for(int nSource=0;nSource<NuSources;nSource++)
		{

			output<<"##Source"<<nSource+1<<endl;
			output<<"Radius:"<<radius<<";"<<endl;		
			output<<"Angle:"<<angle<<";"<<endl;	
			output<<"Height:"<<height<<";"<<endl;	
			output<<"NoEnergy:"<<NoEnergy[nSource]<<";"<<endl;	
			output<<"Activity:"<<activity<<";"<<endl;
			SumActivity+=activity;
		}

	}
	else
	{		
		//随机	
		for(int nSource=0;nSource<NuSources;nSource++)
		{
			if(nSource%4==0)
			{
			radius=RandomData[nRamData][1];
			height=RandomData[nRamData][0];
			activitytemp=activity*(0.25+0.75*RandomData[nRamData][2]);

			//activitytemp=activity;
			SumActivity+=activitytemp;
			output2<<RandomData[nRamData][0]<<" "<<RandomData[nRamData][1]<<" "<<RandomData[nRamData][2]<<endl;
			nRamData++;
			}
			output<<"##Source"<<nSource+1<<endl;
			output<<"Radius:"<<radius<<";"<<endl;		
			output<<"Angle:"<<angle<<";"<<endl;	
			output<<"Height:"<<height<<";"<<endl;	
			output<<"NoEnergy:"<<NoEnergy[nSource%4]<<";"<<endl;	
			output<<"Activity:"<<activitytemp<<";"<<endl;
		}
	}

		output<<"**SumA:"<<SumActivity<<";"<<endl;
		output<<endl;
		output3<<SumActivity<<endl;
	}
	output<<"End"<<endl;

	output.close();
	output2.close();
	output3.close();
	return 0;
}


void RandomDataGeneration()
{
	int ramdondata1[10000];
		for(int n=0;n<10000;n++)
		{
			ramdondata1[n]=(rand()%1000);
		}

	srand(10);
		for(int n=0;n<10000;n++)
		{
			RandomData[n][0]=HOfWD*((rand()*ramdondata1[n])%10000)/10000.0;
		}
	srand(121);
		for(int n=0;n<10000;n++)
		{
			RandomData[n][1]=ROfWD*sqrt(((rand()*ramdondata1[n])%10000)/10000.0);
		}
	srand(521);
		for(int n=0;n<10000;n++)
		{
			RandomData[n][2]=((rand()*ramdondata1[n])%10000)/10000.0;
		}
/*

	seeddata[1]=28.0*sqrt((rand()%1000)/1000.0);
	//srand(int(seed*(seeddata[1]+1))%10000);
	 seeddata[0]=90.0*(rand()%1000)/1000.0;
	//srand(int(seed*(seeddata[0]+1))%10000);
	// seeddata[1]=28.0*sqrt((rand()%1000)/1000.0);
	 seeddata[2]=1.0*((rand()%1000)/1000.0);
	 */
}