#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "Poly.h"
using namespace std;

#define PI 3.1415926

bool Simple(Poly* pl);
float cross(Node* o,Node* a,Node* b);
bool intersect1D(double ,double,double,double);
bool intersect(Node*,Node*,Node*,Node*);
void concave(int pos,int neg,double PArea,double NArea,Poly* poly);
void show(Poly* poly);

int main(){
	int num,nNode;
	cout<<"How many Polygon\n";
	cin>>num;
	
	string str1,str2;
	Poly *polylist= new Poly [num];
	for(int idx=0;idx<num;idx++){
		cout<<"How many Nodes\n";
		cin>>nNode;
		polylist[idx].setN(nNode);
		polylist[idx].start=new Node();
		Node *tmNode=polylist[idx].getstart();
		for(int jdx=0;jdx<polylist[idx].getN();jdx++){
			cout<<"Input your coordinate \"x y\" \n";
			cin>>str1>>str2;
			tmNode->setNode(atof(str1.c_str()),atof(str2.c_str()));
			tmNode->NO=jdx;
			Node *oldNode=tmNode;
			if(jdx==nNode-1)
			{tmNode->nextNode=polylist[idx].getstart();}
			else
			{tmNode->nextNode=new Node();}
	
			tmNode=tmNode->nextNode;
			tmNode->lastNode=oldNode;
		}
	
	}
	for(int idx=0;idx<num;idx++){
		
		Node *tmNode=polylist[idx].getstart();
		double xed=tmNode->getx();
		double yed=tmNode->gety();
		double xnew=0,ynew=0,angle=0,minangle=0;
		tmNode=tmNode->nextNode;
		for(int jdx=1;jdx<=polylist[idx].getN();jdx++){
			xnew=tmNode->getx();
			ynew=tmNode->gety();
			tmNode->lastNode->setvec(xnew-xed,ynew-yed);
			
			xed=xnew;
			yed=ynew;
			tmNode=tmNode->nextNode;
		}
		Node *tmpNode=polylist[idx].getstart();
		double vxed,vyed,outter;
		int pos,neg,cavesign;
		double Pxed,Pyed,PArea,Nxed,Nyed,NArea;
		//calculate outter product and angle
		for(int jdx=0;jdx<=polylist[idx].getN();jdx++)
		{
			vxed=tmpNode->lastNode->getvecx();
			vyed=tmpNode->lastNode->getvecy();
			outter=vxed*(tmpNode->getvecy())-vyed*(tmpNode->getvecx());
			tmpNode->setoutter(outter);
			tmpNode->setangle(atan2(tmpNode->getvecy(),tmpNode->getvecx())-atan2(vyed,vxed));
			if(outter>0)
				pos++;
			if(outter<0)
				neg++;
			if(tmpNode->getoutter()>0)
			{	
				PArea+=abs(tmpNode->gety()*Pxed-tmpNode->getx()*Pyed);
				Pyed=tmpNode->gety();
				Pxed=tmpNode->getx();
			}
			if(tmpNode->getoutter()<0)
			{
				NArea+=abs(tmpNode->gety()*Nxed-tmpNode->getx()*Nyed);
				Nyed=tmpNode->gety();
				Nxed=tmpNode->getx();
			}
			tmpNode=tmpNode->nextNode;
		}
		bool intersects=false;
		
		tmpNode=polylist[idx].getstart();
		Node* itmpNode;
		for(int jdx=0;jdx<polylist[idx].getN();jdx++)
		{	
			itmpNode=tmpNode->nextNode->nextNode;
			for(int kdx=jdx+2;kdx<polylist[idx].getN();kdx++)
			{
				if(tmpNode->lastNode==itmpNode)
				{	itmpNode=itmpNode->nextNode;continue;}
				if(intersect(tmpNode,tmpNode->nextNode,itmpNode,itmpNode->nextNode))
				{
					if(tmpNode->NO < itmpNode->NO && abs(tmpNode->NO - itmpNode->NO)>=2)
					{
						
						intersects=true;
						polylist[idx].simple=false;
						string str1=to_string(tmpNode->NO);
						string str2=to_string(itmpNode->NO);
						polylist[idx].intersects+=(str1+"-"+str2+" ");
					}
					itmpNode=itmpNode->nextNode;
				}
				tmpNode=tmpNode->nextNode;

			}	
		}
		if(intersects==false)
			concave(pos,neg,PArea,NArea,&polylist[idx]);
		
		show(&polylist[idx]);	
	}		
} 
void show(Poly* poly)
{
	if(poly->simple==false)
	{
		cout<<"\n(a) This polygon is not a simple polygon."<<endl;
		cout<<"(b) Intersected Edges:"<<poly->intersects<<endl;
		
	}
	else
	{
		cout<<"\n(a) This polygon is a simple polygon."<<endl;
		if(poly->concave==true)
		{
			cout<<"(b) This polygon is a concave one.\nVertex ";
			Node *tmpNode=poly->getstart();
			int count=0;
			for(int idx=0;idx<poly->getN();idx++)
			{
				if(tmpNode->getcavepoint()==1)
				{
					if(count)
						cout<<",";
						
					cout<<tmpNode->NO;
					count++;
				}
				tmpNode=tmpNode->nextNode;
			}
			cout<<" is concave.\n";
		}
		else
			cout<<"(b) This polygon is not a concave one. \n";
		
	}

}
void concave(int pos,int neg,double PArea,double NArea,Poly* poly)
{
	int cavesign;

	if(pos<3||neg<3)
	{cavesign=(pos>neg)?-1:1;}
	else
	{cavesign=(PArea>NArea)?-1:1;}
	Node* tmpNode=poly->getstart();
	for(int jdx=0;jdx<poly->getN();jdx++)
	{	
		if(tmpNode->getoutter()*cavesign>0)
		{
			tmpNode->setcavepoint(1);
			poly->concave=true;
		}
		tmpNode=tmpNode->nextNode;
		
	}
}
float cross(Node* o,Node* a,Node* b)
{
	return (a->getx()-o->getx())*(b->gety()-o->gety())-(a->gety()-o->gety())*(b->getx()-o->getx());
}
bool intersect1D(double a1,double a2,double b1,double b2)
{
	if(a1>a2){
		double tmp=a1;
		a1=a2;
		a2=tmp;
	}
	if(b1>b2){
		double tmp=b1;
		b1=b2;
		b2=tmp;
	}
	return max(a1,b1) <= min(a2,b2);
}
bool intersect(Node *a1,Node *a2,Node *b1,Node *b2)
{
	return intersect1D(a1->getx(),a2->getx(),b1->getx(),b2->getx())
	&& intersect1D(a1->gety(),a2->gety(),b1->gety(),b2->gety())
	&& cross(a1,a2,b1)*cross(a1,a2,b2)<=0
	&& cross(b1,b2,a1)*cross(b1,b2,a2)<=0;

}
