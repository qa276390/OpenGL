#include <iostream>
#include <string>
using namespace std;

class Node{
private:
	double x;
	double y;
	int cavepoint;
	double vecx;
	double vecy;
	double outter;
	double angle;

public:
	int NO;
	Node(){x=0;y=0;}
	Node * nextNode;
	Node * lastNode;
	void setNode(double xn,double yn)
	{x=xn;y=yn;}	
	void setvec(double xn,double yn)
	{vecx=xn;vecy=yn;}
	void setoutter(double i){outter=i;}
	double getoutter(){return outter;}
	double getvecx(){return vecx;}
	double getvecy(){return vecy;}
	double getx(){return x;}
	double gety(){return y;}
	void setcavepoint(int a){cavepoint=a;}
	double getcavepoint(){return cavepoint;}
	void setangle(double a){angle=a;}
	double getangle(){return angle;}
};


class Poly{
public:
	
	bool concave;
	int n;
	Node *start;
	bool simple;
	Poly(){simple=true;}
	int getN(){return n;}
	void setN(int nN){n=nN;}
	Node* getstart(){return start;}
	string intersects;
};
