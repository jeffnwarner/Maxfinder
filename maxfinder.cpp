// Author: Sean Davis
#include <iostream>
#include "NetDriver.h"
#include "maxfinder.h"
#include "BinaryHeap.h"
#include <cstring>


MaxFinder::MaxFinder(const Computer *computers, int numComputers, int numTerminals) : hash_table(compLoc, 5000)
  {
  	numCom = numComputers;
    numTerm = numTerminals;
    makeComp2List(computers);
  } // MaxFinder()

int MaxFinder::calcMaxFlow(Edge *edges, int numEdges)
{   
  ComputerLocation cmp;
  strcpy(cmp.IP, "\0");
  cmp.index = -1;
  //QuadraticHashTable <Computer2> hash_table(cmp, 5000); //hash table of computers
  BinaryHeap <Computer2> heap(5000);
  int last = numCom - 1;
  int maxTotal = 0;
  int totalCount = 0;
  bool noChange = false;
 /* for (int i = 0; i < numCom; i++)
  {
  	ComputerLocation compLoc;
  	strcpy(compLoc.IP, comp[i].IP);
  	compLoc.index = i;
    std::cout<<"insert comp[i] IP "<<comp[i].IP<<std::endl;
    hash_table.insert(compLoc);
    //std::cout<<"hash just inserted IP "<<(hash_table.find(comp[i])).IP<<std::endl;
  }
  */
  //for (int i = 0; i < numTerm; i++)
    //heap.insert(comp[i]);
  //delete [] comp;

  //makeAdjacency(edges, numEdges);
  for (int j = 0; j < numEdges; j++)
  {
  	int location;
    ComputerLocation dummyLoc;
    ComputerLocation dummyLoc2;
    strcpy(dummyLoc.IP, edges[j].src);
    //std::cout<<"dummyLoc "<<dummyLoc.IP<<std::endl;
    strcpy(dummyLoc2.IP, edges[j].dest);
    //std::cout<<"src "<<edges[j].src<<std::endl;
    location = (hash_table.find(dummyLoc)).index;
    //std::cout<<"location "<<location<<std::endl;
    //std::cout<<"if start"<<std::endl;
    if (dummyLoc.IP[0] != '\0' && dummyLoc2.IP[0] != '\0')
    {
      //std::cout<<"if doing"<<std::endl;
      //std::cout<<"comp[location] "<<comp[location].IP<<std::endl;
      int count = comp[location].adjcount;
      comp[location].adjs[count].index =  (hash_table.find(dummyLoc2)).index;
      std::cout<<"loc index "<<(hash_table.find(dummyLoc2)).index<<std::endl;
      comp[location].adjs[count].capacity = edges[j].capacity;
      //dummy.adjs[count].flow = 0;
      comp[location].adjcount = count + 1;
      std::cout<<"comp[location] IP "<<comp[location].IP<<std::endl;
      std::cout<<"comp[location] adjcount "<<comp[location].adjcount<<std::endl;
      std::cout<<"comp[location].adjs.[count].index "<<comp[location].adjs[count - 1].index<<std::endl;
      //dummy.adjs[count].tampered = false;
      //hash_table.remove(dummy);
      //hash_table.insert(dummy);
      location = (hash_table.find(dummyLoc2)).index;
      //std::cout<<"location2 "<<location<<std::endl;
      //std::cout<<"comp[location]2 "<<comp[location].IP<<std::endl;
      count = comp[location].adjcount;
      comp[location].adjs[count].index =  (hash_table.find(dummyLoc)).index;
      comp[location].adjs[count].capacity = edges[j].capacity;
      comp[location].adjcount = count + 1;
      //std::cout<<"comp[location]2 adjcount "<<comp[location].adjcount<<std::endl;
    } //if  
    //std::cout<<"if end"<<std::endl;
    /*std::cout<<"ha "<<(hash_table.find(dummy)).IP<<std::endl;
    strcpy(dummy.IP, edges[j].dest);
    std::cout<<"dest "<<edges[j].dest<<std::endl;
    dummy = hash_table.find(dummy);
    if (strncmp(edges[j].dest, dumDum.IP, 16) == 0 && p == 0)
    {
      dumDum.dv = 2147483647;
      dummy = dumDum;
      p++;
    }
    if (dummy.IP[0] != '\0')
    {
      int count = dummy.adjcount;
      strcpy(dummy.adjs[count].IP, edges[j].src);
      dummy.adjs[count].capacity = edges[j].capacity;
      //dummy.adjs[count].flow = 0;
      dummy.adjcount = count + 1;
      //dummy.adjs[count].tampered = false;
      hash_table.remove(dummy);
      hash_table.insert(dummy);
      std::cout<<"flow "<<dummy.dv<<std::endl;
    } //if
    std::cout<<"ha2 "<<(hash_table.find(dummy)).IP<<std::endl;
    std::cout<<"ha3 "<<(hash_table.find(dummy)).adjcount<<std::endl;
    */
  } //for i
  for (int i = 0; i < numTerm; i++)
  {
    //std::cout<<"inserting heap "<<comp[i].IP<<std::endl;
    heap.insert(comp[i]);
    //std::cout<<"in heap "<<(heap.findMax()).IP<<std::endl;
  }
  /*
  for (int i = 0; i < numTerm; i++)
  {
  	Computer2 stupid;
    strcpy(stupid.IP, term[i].IP);
  	getShortestPath(stupid);
  }
  */
  
  //Dijkstra's algorithm to find max flow
  while (!noChange)
  {
  	////std::cout<<"Fuker"<<std::endl;
    while (!(comp[last]).known)
    {
      Computer2 dummy;
      //int ijk = 0;
      dummy = heap.findMax();
      dummy = comp[dummy.index];
      //ijk = (heap.findMax()).index;
      std::cout<<"dummy.index "<<dummy.index<<std::endl;
      //std::cout<<"heap "<<(heap.findMax()).IP<<std::endl;
      //std::cout<<"not underflow"<<std::endl;
      dummy.known = true;
      heap.deleteMax();
      //int h = 0;
      int location;
      //std::cout<<dummy.adjcount<<std::endl;
      for (int i = 0; i < dummy.adjcount; i++)
      {
        Computer2 dummy2;
        location = dummy.adjs[i].index;
        std::cout<<"location"<<location<<std::endl;
        dummy2 = comp[location];
        //strcpy(fuck.IP, "176.24.154.60");
        //std::cout<<"fuck "<<(hash_table.find(fuck)).IP<<std::endl;
       //std::cout<<"dummy.adjs[i] IP "<<dummy.adjs[i].IP<<std::endl;
        //dummy2 = comp[hash_table.find(dummy2).index];
        std::cout<<"dummy IP "<<dummy.IP<<std::endl;
        std::cout<<"dummy2 IP "<<dummy2.IP<<std::endl;
        if (dummy2.known == false)
        {
          if (strncmp(dummy2.IP, dummy.PV, 16) != 0)
          { 
          	std::cout<<"dummy 1 IP "<<dummy.IP<<std::endl;
          	std::cout<<"dummy 2 IP "<<dummy2.IP<<std::endl;
          	update(dummy, dummy2, i);
          	heap.insert(dummy2);
          	comp[dummy.index] = dummy;
            comp[dummy2.index] = dummy2;
          }
        }
      } //for
      //std::cout<<"dummy 1 IP "<<dummy.IP<<std::endl;
      /*if (strncmp(comp[0].IP, dummy.IP, 16) == 0)
      {
        std::cout<<"happens"<<std::endl;
        strcpy(dummy.IP, "43.209.93.90");
      }
      hash_table.remove(dummy);
      hash_table.insert(dummy);
      */
      //std::cout<<"dummy 1 IP "<<(hash_table.find(dummy)).IP<<std::endl;
    }
    
    Computer2 dupe;
    Computer2 dupe2;
    dupe = comp[last];
    //int i = 0;
    //int loc;
    while (dupe.PV[0] != '\0')
    {
      int eb = dupe.edgeback;
      dupe2 = comp[dupe.adjs[dupe.edgeback].index];
      int ef = dupe2.edgeforward;
      if (dupe.dv < dupe2.dv)
      {
        dupe.adjs[eb].flow -= dupe.dv;
        dupe2.adjs[ef].flow = dupe.adjs[eb].flow;
        dupe2.dv = dupe.dv;
        dupe.dv = 0;
        dupe.known = false;
        dupe2.known = false;
      }
      comp[dupe.index] = dupe;
      comp[dupe2.index] = dupe2;
      //hash_table.insert(dupe);
      //hash_table.insert(dupe2);
      dupe = dupe2;
      //i++;
    }
    
    totalCount = 0;
    for (int j = 0; j < comp[last].adjcount; j++)	
    {
      //std::cout<<"total count "<<totalCount<<std::endl;
      totalCount = totalCount + comp[last].adjs[j].flow;
    }
   
    if (maxTotal == totalCount)
      noChange = true;
    else
      maxTotal = totalCount;
  }
  if (maxTotal != 0)
    return maxTotal;
  
  return 0;  // bad result :(
} // calcMaxFlow()

void MaxFinder::makeComp2List(const Computer *computers)
{
  //Computer2 dummy;
  for (int i = 0; i < numTerm; i++)
  {
  	ComputerLocation cL;
  	strcpy(comp[i].IP, computers[i].address);
  	strcpy(cL.IP, comp[i].IP);
    //std::cout<<"cL "<<cL.IP<<std::endl;
  	cL.index = i;
  	hash_table.insert(cL);
    //std::cout<<"hash iP "<<(hash_table.find(cL)).IP<<std::endl;
    comp[i].index = i;
  	//dummy.adjcount = 0;
  	//dummy.dv = 0;
  	//dummy.PV[0] = '\0';
    //memset(comp[i].PV, 0, 16);
  	//dummy.known = false;
  	//comp[i] = dummy;
  } //for i
  
  for (int i = numTerm; i < numCom; i++)
  {

    ComputerLocation cL;
  	strcpy(comp[i].IP, computers[i].address);
  	strcpy(cL.IP, comp[i].IP);
    //std::cout<<"comp[i] "<<comp[i].IP<<std::endl;
  	cL.index = i;
  	hash_table.insert(cL);
    comp[i].dv = 2147483647;
    //dummy.PV[0] = '\0';
  	//memset(comp[i].PV, 0, 16);
  	//dummy.known = false;
  	//comp[i] = dummy;
  }
  /*
  for (int i = 0; i < numTerm; i++)
  {
  	strcpy(term[i].IP , computers[i].address);
  }
  */
} //make Comp2List

void MaxFinder::update(Computer2& comp1, Computer2& comp2, int i)
{
  int a = 0;

  if (comp1.dv == 0)
  {
    comp2.dv = comp1.adjs[i].capacity;
    comp1.adjs[i].flow = comp2.dv;
    //residual update
  }
  
  else if (comp1.dv > comp1.adjs[i].capacity)
  {
    comp2.dv = comp1.adjs[i].capacity;
    comp1.dv = comp2.dv;
    comp1.adjs[i].flow = comp2.dv;
    //residual update
  }
  
  else if (comp1.adjs[i].flow != 0 && comp1.dv >= comp1.adjs[i].capacity - comp1.adjs[i].flow)
  {
    comp2.dv = comp1.adjs[i].capacity - comp1.adjs[i].flow;
    comp1.dv = comp2.dv;
    comp1.adjs[i].flow += comp2.dv;
    //residual update
  }
  
  else 
  {  
    comp2.dv = comp1.dv;
    comp1.adjs[i].flow += comp2.dv;
    //residual update
  }
  
  
  for (int j = 0; j < comp2.adjcount; j++)
  {
    if (comp2.adjs[j].index == comp1.index)
      a = j;
  }
  comp2.adjs[a].flow = comp2.dv;
  strcpy(comp2.PV, comp1.IP);
  comp2.edgeback = a;
  comp1.edgeforward = i;
}//update