// Author: Sean Davis
#ifndef maxfinderH
#define maxfinderH
#include <iostream>
#include "NetDriver.h"
#include <stdbool.h>
#include <string.h>
#include "QuadraticProbing.h"

class Computer;
class Edge;
//class Computer2;
class Edges2;
class ComputerLocation;

class Edges2
{
public:
  Edges2()
  {
    capacity = 0;
    flow = 0;
    residual = 0;
    tampered = false;
    index = -1;
  }
  short capacity;
  short flow;
  short residual;
  bool tampered;
  int index;
}; // class Edges2

class Computer2
{
public:
  Computer2()
  {
    IP[0] = '\0';
    adjcount = 0;
    dv = 0;
    known = false;
    PV[0] = '\0';
    edgeback = 0;
    edgeforward = 0;
    index = -1;
  }
  char IP[16];
  Edges2 adjs[100];
  int adjcount;
  //Djikstra's
  int dv;
  bool known;
  char PV[16];
  int edgeback;
  int edgeforward;
  int index;
  Computer2& operator=(const Computer2& c2)
  {
  	//std::cout<<dv<<std::endl;
  	//std::cout<<c2.dv<<std::endl;
    dv = c2.dv;
  	edgeback = c2.edgeback;
  	edgeforward = c2.edgeforward;
  	//std::cout<<"C1 "<<known<<std::endl;
  	//std::cout<<"c2 "<<c2.known<<std::endl;
  	known = c2.known;
  	//std::cout<<"C1 "<<known<<std::endl;
  	adjcount = c2.adjcount;
  	strcpy(IP, c2.IP);
  	strcpy(PV, c2.PV);
    index = c2.index;
  	for (int i = 0; i < adjcount; i++)
  	{
  	  adjs[i].capacity = c2.adjs[i].capacity;
  	  adjs[i].flow = c2.adjs[i].flow;
  	  adjs[i].residual = c2.adjs[i].residual;
  	  adjs[i].tampered = c2.adjs[i].tampered;
  	  //strcpy(adjs[i].IP, c2.adjs[i].IP);
  	}
  	return *this;
  }
  bool operator!=(const Computer2& rhs) const
  {
    if (strncmp(IP, rhs.IP, 16) == 0)
      return false;
    else
      return true;
  }
  //bool operator!=(const Computer2& rhs) const
  //{return !(*this == rhs);}

}; //class Computer2

class MaxFinder
{
public:
  MaxFinder(const Computer*, int, int);
  int calcMaxFlow(Edge *edges, int numEdges);
  Computer2 comp[5000];
  void makeComp2List(const Computer *computers);
  void update(Computer2& comp1, Computer2& comp2, int i);
  int numCom;
  int numTerm;
  ComputerLocation compLoc;
  QuadraticHashTable<ComputerLocation> hash_table;
}; // class MaxFinder
#endif

