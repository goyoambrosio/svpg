/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Graph.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:26 $
  $Name:  $

****/

/******************************************************************************\                                                                          *
* SoftVision Toolbox. Software for Computer Vision                             *
*                                                                              *
* Author  : Gregorio Ambrosio Cestero (goyo@computer.org)                      *
*           System Engineering and Automation Department                       *
*           University of Malaga. Spain                                        *
*                                                                              *
*               Copyright (c) 2000, Gregorio Ambrosio cestero                  *
*                          All Rights Reserved                                 *
*                                                                              *
* Permission to use, copy, modify, and distribute this software and its        *
* associated documentation for non-commercial purposes is hereby granted,      *
* provided that the above copyright notice appears in all copies, derivative   *
* works or modified versions of the software and any portions thereof, and     *
* that both the copyright notice and this permission notice appear in the      *
* documentation.  Gregorio Ambrosio Cestero (GAC for short) shall be given     *
* a copy of any such derivative work or modified version of the software and   *
* GAC shall be granted permission to use, copy, modify and distribute the      *
* software for his own use and research. This software is experimental.        *
* GAC does not make any representations regarding the suitability of this      *
* software for any purpose and GAC will not support the software.              *
*                                                                              *
* THE SOFTWARE IS PROVIDED AS IS.  GAC DOES NOT MAKE ANY WARRANTIES            *
* EITHER EXPRESS OR IMPLIED WITH REGARD TO THE SOFTWARE. GAC ALSO              *
* DISCLAIMS ANY WARRANTY THAT THE SOFTWARE IS FREE OF INFRINGEMENT OF ANY      *
* INTELLECTUAL PROPERTY RIGHTS OF OTHERS.  NO OTHER LICENSE EXPRESS OR         *
* IMPLIED IS HEREBY GRANTED. GAC SHALL NOT BE LIABLE FOR ANY DAMAGES,          *
* INCLUDING GENERAL, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, ARISING    *
* OUT OF THE USE OR INABILITY TO USE THE SOFTWARE.                             *
*                                                                              *
\******************************************************************************/


#if !defined(_GRAPH_H_)
#define _GRAPH_H_

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include <algorithm>
#include <deque>
#include <vector>
#include <map>
#include "Matrix.h"
#include "Error.h"
#include "LabelVector.h"

namespace GAC
{

/**************************************\
 *            class Vertex            *
\**************************************/
template <class TV> class Vertex
{
public:
	Vertex();
	Vertex(int Label);
	Vertex(int Label, TV Content);
	virtual ~Vertex();

	// Public data
	Label   Label;  //Data type Label defined in LabelVector.h
	TV      Content;

	//Public functions
	friend operator==(const Vertex<TV>& V1,const Vertex<TV>& V2);
	friend operator!=(const Vertex<TV>& V1,const Vertex<TV>& V2);
	friend operator< (const Vertex<TV>& V1,const Vertex<TV>& V2);
private:

};

//Constructors and Destructors
template <class TV> Vertex<TV>::Vertex()
{

}
template <class TV> Vertex<TV>::Vertex(int Label)
{
	Vertex<TV>::Label = Label;
}
template <class TV> Vertex<TV>::Vertex(int Label, TV Content)
{
	Vertex<TV>::Label   = Label;
	Vertex<TV>::Content = Content;
}
template <class TV> Vertex<TV>::~Vertex()
{

}

//Implementation
template <class TV> 
bool operator==(const Vertex<TV>& V1,const Vertex<TV>& V2){
	return (V1.Label   == V2.Label //&&
			//V1.Content == V2.Content
		   );
}
template <class TV>
bool operator!=(const Vertex<TV>& V1,const Vertex<TV>& V2){
	return (V1.Label   != V2.Label   //&&
			//V1.Content != V2.Content
		   );
}
template <class TV>
bool operator< (const Vertex<TV>& V1,const Vertex<TV>& V2){
	return (V1.Label   < V2.Label   //&&
			//V1.Content < V2.Content
		   );
}

/**************************************\
 *            class Edge              *
\**************************************/

template <class TE> class Edge
{
public:
	Edge();
	Edge(TE Weight);
	Edge(TE Weight,int Label);
	virtual ~Edge();

	// Public data
	int        Label;
	TE         Weight;

	//Public functions
	friend operator==(const Edge<TE>& E1,const Edge<TE>& E2);
	friend operator!=(const Edge<TE>& E1,const Edge<TE>& E2);
	friend operator< (const Edge<TE>& E1,const Edge<TE>& E2);

private:


};

//Constructors and Destructors
template <class TE> Edge<TE>::~Edge()
{

}

//Implementation
template <class TE> Edge<TE>::Edge()
{

}

template <class TE> Edge<TE>::Edge(TE Weight)
{
	Edge<TE>::Weight    = Weight;
}

template <class TE> Edge<TE>::Edge(TE Weight,int Label)
{
	Edge<TE>::Weight   = Weight;
	Edge<TE>::Label    = Label;
}

//Implementation
template <class TE> 
bool operator==(const Edge<TE>& E1,const Edge<TE>& E2){
	return (E1.Label   == E2.Label //&&
			//V1.Content == V2.Content
		   );
}
template <class TE>
bool operator!=(const Edge<TE>& E1,const Edge<TE>& E2){
	return (E1.Label   != E2.Label   //&&
			//V1.Content != V2.Content
		   );
}
template <class TE>
bool operator< (const Edge<TE>& E1,const Edge<TE>& E2){
	return (E1.Label   < E2.Label   //&&
			//V1.Content < V2.Content
		   );
}

/**************************************\
 *            class Graph             *
\**************************************/

template <class TV, class TE> class Graph : public Error
{
public:
	Graph();
	Graph(bool Weighted,TE MaxWeight,TE ZeroWeight);
    virtual	~Graph();

//Public data
public:
	TE MaxWeight;   //Max  Weight -used in Shortest-Path Algorithms-
	TE ZeroWeight;	//Zero Weight -used in Shortest-Path Algorithms-

//Public data types
public:
	typedef map<Label,TV> VertexMap;

	typedef multimap<Label,TE>		   VertexEdgeMMap;
	typedef map<Label,VertexEdgeMMap>  VertexEdgeVertexMap;

	typedef Graph<TV,TE>                    GraphTVTE;
	typedef vector<GraphTVTE>               GraphVector;
	class PredecessorInfo
	{
	//Public data
	public:
		TE    d;
		Label p;
	};
	typedef map<Label,PredecessorInfo>	PredecessorMap; 
	class TimeInfo
	{
	//Public data
	public:
		unsigned int d;
		unsigned int f;
	};
	typedef map<Label,TimeInfo>	TimeMap; 

//Public functions
public:
	bool isDirected();
	bool isWeighted();
	void           ShowAdjacencyList();
	void           ShowAdjacencyMatrix();
	void           ShowPredecessorMap   (PredecessorMap PM);
	void           ShowTimeMap          (TimeMap TM);
	Graph<TV,TE> & AddVertex       (Vertex<TV> u);
	Graph<TV,TE> & RemoveVertex    (Label u);
	Graph<TV,TE> & RemoveVertex    (LabelVector LV);
	Graph<TV,TE> & AddEdge         (Label u,Label v,TE w);
	Graph<TV,TE> & RemoveEdge      (Label u,Label v);
	Graph<TV,TE> & RemoveEdge      (Label u,Label v,TE w);
	Graph<TV,TE> & RemoveEdgesTo   (Label u);
	Graph<TV,TE> & RemoveEdgesFrom (Label u);
	Graph<TV,TE> & RemoveIsolatedVertexes();
	Graph<TV,TE> & Clear           ();
	bool           GetVertex       (Label u,Vertex<TV> & vx);
	bool           GetVertex       (TV Content, Label & u);
	LabelVector    GetParents      (Label u);
	LabelVector    GetChildren     (Label u);
	LabelVector    GetIsolatedVertexes();
	LabelVector    GetSourceVertexes  ();
	LabelVector    GetSinkVertexes    ();
	bool           GetWeight       (Label u,Label v, TE & w);

	pair<unsigned int,unsigned int> Size(); //Num.ofVertex,Num.ofEdges
	VertexEdgeVertexMap GetAdjacencyList ();
	VertexMap      GetVertexList();
	Matrix<TE>     GetAdjacencyMatrix();
	Graph<TV,TE>   GetUndirectedGraph   ();
	Graph<TV,TE> & SetAsUndirectedGraph (); //Forward change unreversible.
	LabelVector    GetV                 ();
	LabelVector    GetVs                (Label s);
	void           SS_SP_Dijkstra       (Label s,PredecessorMap & PM);
	void           SS_SP_DAG            (Label s,PredecessorMap & PM);
	LabelVector    ExtractVisitedVertexFromPredecessorMap(PredecessorMap PM);
	void           DepthFirstSearch     (TimeMap & TM);
	LabelVector    DAG_TopologicalSort  (TimeMap & TM);
	void           BreathFirstSearch    (Label s,PredecessorMap & PM);
	void           Subgraphs            (GraphVector & GV);
	Graph<TV,TE>   GetSubgraph          (LabelVector LV);

	friend bool operator==(Graph<TV,TE> G1,Graph<TV,TE> G2);
	friend bool operator!=(Graph<TV,TE> G1,Graph<TV,TE> G2);
	friend bool operator< (Graph<TV,TE> G1,Graph<TV,TE> G2);

//Private data types
private:
	//To be used in DepthFirstSearch
	typedef enum{white,gray,black} colors;
	class VisitInfo
	{
	//Public data
	public:
		colors c;
		Label  p;
	};
	typedef map<Label,VisitInfo> VisitMap; 

	//To be used in Shortest-Path Algorithms
	class Qclass
	{
	//Public functions
	public:
		Qclass(){};
		Qclass(TE d,Label Vertex){Qclass::d = d;Qclass::Vertex = Vertex;};
		bool operator < (const Qclass &aux){return (d <  aux.d);};
		bool operator ==(const Qclass &aux){return (d == aux.d);};
		bool operator !=(const Qclass &aux){return (d != aux.d);};
	//Public data
	public:
		TE			d;
		Label	Vertex;
	};

//Private data
private:
	bool Directed;
	bool Weighted;
	VertexMap VertexList;
	VertexEdgeVertexMap AdjacencyList;


//Private functions
private:
	Graph<TV,TE> & InitializeErrors();
	void InitializeSingleSource(Label s,PredecessorMap & PM);
	void Relax                 (Label u,Label v,PredecessorMap & PM);
	void DepthFirstSearchVisit (Label u,VisitMap & VM,TimeMap & TM, unsigned int &GlobalTime);
};


/**Graph*************************\
  Constructors and Destructors
\********************************/
template <class TV, class TE> Graph<TV,TE>::Graph()
{
	Graph<TV,TE>::Directed = true;
	Graph<TV,TE>::Weighted = true;
	InitializeErrors();
}


template <class TV, class TE> Graph<TV,TE>::Graph(bool Weighted,TE MaxWeight,TE ZeroWeight)
{
	Graph<TV,TE>::Directed   = true;
	Graph<TV,TE>::Weighted   = Weighted;
	Graph<TV,TE>::MaxWeight  = MaxWeight;
	Graph<TV,TE>::ZeroWeight = ZeroWeight;

	InitializeErrors();
}
template <class TV, class TE> Graph<TV,TE>::~Graph()
{

}

template <class TV, class TE> Graph<TV,TE> & Graph<TV,TE>::InitializeErrors()
{
	insert(Error::value_type(0,"No error"));
	insert(Error::value_type(1,"Available"));
	insert(Error::value_type(2,"Available"));

	return *this;
}

/**Graph*************************\
			Operators
\********************************/
template <class TV, class TE> 
bool operator==(Graph<TV,TE> G1,Graph<TV,TE> G2)
{
	if ((G1.MaxWeight!=G2.MaxWeight) || (G1.ZeroWeight!=G2.ZeroWeight))
		return false;

	if ((G1.isDirected()!=G2.isDirected()) || (G1.isWeighted()!=G2.isWeighted()))
		return false;

	pair<unsigned int,unsigned int> S1,S2;
	S1=G1.Size();
	S2=G2.Size();
	if((S1.first!=S2.first)||(S1.second!=S2.second))
		return false;

	if (G1.VertexList != G2.VertexList)
		return false;

	if (G1.AdjacencyList != G2.AdjacencyList)
		return false;

	return true;
}

template <class TV, class TE>
bool operator!=(Graph<TV,TE> G1,Graph<TV,TE> G2){
	return !(G1==G2);
}
template <class TV, class TE>
bool operator< (Graph<TV,TE> G1,Graph<TV,TE> G2){
	return (G1.GetV()<G2.GetV());
	pair<unsigned int,unsigned int> S1,S2;
	S1=G1.Size();
	S2=G2.Size();
	return ((S1.first<S2.first)&&(S1.second<S2.second));
}

//Implementation

/**Graph*************************\
        ShowAdjacencyList
\********************************/
template <class TV, class TE> void Graph<TV,TE>::ShowAdjacencyList()
{
	VertexEdgeMMap::iterator      VEMMit;
	VertexEdgeVertexMap::iterator VEVMit;
	VertexEdgeMMap VEMM;
	Label u, v;
	TE w;

	printf("Graph visualization: Adjacency List Mode\n\n");

	for (VEVMit=AdjacencyList.begin();VEVMit!=AdjacencyList.end();VEVMit++){
		u     = (*VEVMit).first;
		VEMM  = (*VEVMit).second;

		printf("u:%i\n",u);

		for (VEMMit=VEMM.begin();VEMMit!=VEMM.end();VEMMit++){
			v = (*VEMMit).first;
			w = (*VEMMit).second;

//			printf("\tv:%i (%.30g)\n",v, w);
    		printf("\tv:%i\n",v);
//			printf("\t\t");
//			w.Show();

		}
	}
}

/**Graph*************************\
        ShowAdjacencyMatrix
\********************************/
template <class TV, class TE> void Graph<TV,TE>::ShowAdjacencyMatrix()
{
	GetAdjacencyMatrix().Show();
}

/**Graph*************************\
        isDirected
		idWeighted
\********************************/
template <class TV, class TE> bool Graph<TV,TE>::isDirected() {return Directed;}
template <class TV, class TE> bool Graph<TV,TE>::isWeighted() {return Weighted;}

/**Graph*************************\
		AddVertex
\********************************/
template <class TV, class TE> Graph<TV,TE> & Graph<TV,TE>::AddVertex(Vertex<TV> u)
{
	VertexList[u.Label]=u.Content;
	AdjacencyList[u.Label];
	return *this;
}

/**Graph*************************\
		RemoveVertex
\********************************/
template <class TV, class TE> Graph<TV,TE> & Graph<TV,TE>::RemoveVertex(Label u)
{
	VertexEdgeVertexMap::iterator VEVMit;

	VertexList.erase(u);
	AdjacencyList.erase(u);
	
	for (VEVMit=AdjacencyList.begin();VEVMit!=AdjacencyList.end();VEVMit++){
		(*VEVMit).second.erase(u);
	}
	return *this;
}

/**Graph*************************\
		RemoveVertex
\********************************/
template <class TV, class TE> Graph<TV,TE> & Graph<TV,TE>::RemoveVertex(LabelVector LV)
{
	VertexEdgeVertexMap::iterator VEVMit;
	LabelVector::iterator LVit;


	for (LVit=LV.begin();LVit!=LV.end();LVit++){
		VertexList.erase(*LVit);
		AdjacencyList.erase(*LVit);
	
		for (VEVMit=AdjacencyList.begin();VEVMit!=AdjacencyList.end();VEVMit++){
			(*VEVMit).second.erase(*LVit);
		}
	}
	return *this;
}

/**Graph*************************\
		AddEdge
\********************************/
template <class TV, class TE> Graph<TV,TE> & Graph<TV,TE>::AddEdge(Label u,Label v,TE w)
{

	VertexEdgeVertexMap::iterator VEVMit;
	VertexEdgeMMap::iterator VEMMit;
	VertexEdgeMMap VEMM;

	AdjacencyList[u];
	AdjacencyList[v];

	VEVMit    = AdjacencyList.find(u);
	VEMM     = (*VEVMit).second;
	for (VEMMit=VEMM.begin();VEMMit!=VEMM.end();VEMMit++)
		if ((*VEMMit)==VertexEdgeMMap::value_type(v,w)) break;
	if (VEMMit == VEMM.end())
		AdjacencyList[u].insert(VertexEdgeMMap::value_type(v,w));

	return *this;

}

/**Graph*************************\
		RemoveEdge
\********************************/
template <class TV, class TE> Graph<TV,TE> & Graph<TV,TE>::RemoveEdge(Label u, Label v)
{
	VertexEdgeVertexMap::iterator VEVMit;

	VEVMit = AdjacencyList.find(u);
	if (VEVMit != AdjacencyList.end()) {
		(*VEVMit).second.erase(v);
	}
	return *this;
}

/**Graph*************************\
		RemoveEdge
\********************************/
template <class TV, class TE> Graph<TV,TE> & Graph<TV,TE>::RemoveEdge(Label u, Label v, TE w)
{
	VertexEdgeVertexMap::iterator VEVMit;
	VertexEdgeMMap::iterator VEMMit;

	VEVMit = AdjacencyList.find(u);
	if (VEVMit != AdjacencyList.end()) {
		for (VEMMit=(*VEVMit).second.begin();VEMMit!=(*VEVMit).second.end();VEMMit++)
			if ((*VEMMit)==VertexEdgeMMap::value_type(v,w)) break;
		if (VEMMit != (*VEVMit).second.end()){
			AdjacencyList[u].erase(VEMMit);
		}
	}
	return *this;
}

/**Graph*************************\
		RemoveEdgesFrom
\********************************/
template <class TV, class TE> Graph<TV,TE> & Graph<TV,TE>::RemoveEdgesFrom(Label u)
{
	VertexEdgeVertexMap::iterator VEVMit;

	VEVMit = AdjacencyList.find(u);
	if (VEVMit != AdjacencyList.end()) {
		(*VEVMit).second.erase((*VEVMit).second.begin(),(*VEVMit).second.end());
	}
	return *this;
}

/**Graph*************************\
		RemoveEdgesTo
\********************************/
template <class TV, class TE> Graph<TV,TE> & Graph<TV,TE>::RemoveEdgesTo(Label u)
{
	VertexEdgeVertexMap::iterator VEVMit;
	VertexEdgeMMap VEMM;

	for (VEVMit=AdjacencyList.begin();VEVMit!=AdjacencyList.end();VEVMit++){
		VEMM     = (*VEVMit).second;
		(*VEVMit).second.erase(u);
	}
	return *this;
}

/**Graph*************************\
        Clear
\********************************/
template <class TV, class TE> Graph<TV,TE> & Graph<TV,TE>::Clear()
{
	VertexEdgeVertexMap::iterator VEVMit;

	for (VEVMit=AdjacencyList.begin();VEVMit!=AdjacencyList.end();VEVMit++){
		(*VEVMit).second.clear();
	}
	AdjacencyList.clear();
	VertexList.clear();
	return *this;
}

/**Graph*************************\
		GetWeight
\********************************/
template <class TV, class TE> bool Graph<TV,TE>::GetWeight(Label u,Label v,TE & w)
{
	VertexEdgeVertexMap::iterator VEVMit;
	VertexEdgeMMap::iterator VEMMit;

	VEVMit = AdjacencyList.find(u);
	VEMMit = (*VEVMit).second.find(v);

	if ((VEVMit!=AdjacencyList.end()) && (VEMMit!=(*VEVMit).second.end())){
		w = (*VEMMit).second;
		return true;
	}
	else
		return false;
}

/**Graph*************************\
		GetVertex
\********************************/
template <class TV, class TE> bool Graph<TV,TE>::GetVertex(Label u,Vertex<TV> & vx)
{
	VertexMap::iterator VMit;

	vx.Label   = u;
	VMit      = VertexList.find(u);
	if (VMit!=VertexList.end()){
		vx.Content = (*VMit).second;
		return true;
	}
	else
		return false;
}

/**Graph*************************\
		GetVertex
\********************************/
template <class TV, class TE> bool Graph<TV,TE>::GetVertex(TV Content, Label & u)
{
	VertexMap::iterator VMit;

	for (VMit=VertexList.begin();VMit!=VertexList.end();VMit++)
		if ((*VMit).second == Content) break;

	if (VMit!=VertexList.end()){
		u = (*VMit).first;
		return true;
	}
	else
		return false;
}

/**Graph*************************\
		GetChildren
\********************************/
template <class TV, class TE> LabelVector Graph<TV,TE>::GetChildren(Label u)
{
	LabelVector Children;
	LabelVector::iterator LVit;

	VertexEdgeVertexMap::iterator VEVMit;
	VertexEdgeMMap::iterator VEMMit;
	VertexEdgeMMap VEMM;

	VEVMit    = AdjacencyList.find(u);
	VEMM     = (*VEVMit).second;
	for (VEMMit=VEMM.begin();VEMMit!=VEMM.end();VEMMit++){
		for (LVit=Children.begin();LVit!=Children.end();LVit++)
			if ((*LVit) == (*VEMMit).first) break;
		if (LVit == Children.end()) Children.push_back((*VEMMit).first);
	}

	return Children;

}

/**Graph*************************\
		GetParents
\********************************/
template <class TV, class TE> LabelVector Graph<TV,TE>::GetParents(Label u)
{
	LabelVector Fathers;
	LabelVector::iterator LVit;

	VertexEdgeVertexMap::iterator VEVMit;
	VertexEdgeMMap::iterator VEMMit;
	VertexEdgeMMap VEMM;

	for (VEVMit=AdjacencyList.begin();VEVMit!=AdjacencyList.end();VEVMit++){
		VEMM     = (*VEVMit).second;
		for (VEMMit=VEMM.begin();VEMMit!=VEMM.end();VEMMit++){
			if ((*VEMMit).first == u){
				for (LVit=Fathers.begin();LVit!=Fathers.end();LVit++)
					if ((*LVit) == (*VEVMit).first) break;
				if (LVit == Fathers.end()) Fathers.push_back((*VEVMit).first);
			}				
		}
	}
	return Fathers;
}
/**Graph*************************\
		GetIsolatedVertexes
\********************************/
template <class TV, class TE> LabelVector Graph<TV,TE>::GetIsolatedVertexes()
{
	VertexMap::iterator VMit;
	Label u;
	LabelVector IsolatedVector;

	for (VMit=VertexList.begin();VMit!=VertexList.end();VMit++){
		u = (*VMit).first;
		if (GetChildren(u).size()==0 && GetParents(u).size()==0)
			IsolatedVector.push_back(u);
	}
	return IsolatedVector;
}
/**Graph*************************\
		GetSourceVertexes
\********************************/
template <class TV, class TE> LabelVector Graph<TV,TE>::GetSourceVertexes()
{
	VertexMap::iterator VMit;
	Label u;
	LabelVector SourceVector;

	for (VMit=VertexList.begin();VMit!=VertexList.end();VMit++){
		u = (*VMit).first;
		if (GetChildren(u).size()!=0)
			SourceVector.push_back(u);
	}
	return SourceVector;
}
/**Graph*************************\
		GetSinkVertexes
\********************************/
template <class TV, class TE> LabelVector Graph<TV,TE>::GetSinkVertexes()
{
	VertexMap::iterator VMit;
	Label u;
	LabelVector SinkVector;

	for (VMit=VertexList.begin();VMit!=VertexList.end();VMit++){
		u = (*VMit).first;
		if (GetChildren(u).size()==0 && GetParents(u).size()!=0)
			SinkVector.push_back(u);
	}
	return SinkVector;
}
/**Graph*************************\
		RemoveIsolatedVertexes
\********************************/
template <class TV, class TE> Graph<TV,TE> & Graph<TV,TE>::RemoveIsolatedVertexes()
{
	LabelVector IsolatedVector;
	
	IsolatedVector = GetIsolatedVertexes();
	RemoveVertex(IsolatedVector);

	return *this;
}
/**Graph*************************\
		Size
\********************************/
template <class TV, class TE> pair<unsigned int,unsigned int> Graph<TV,TE>::Size()
{
	unsigned int EdgeCount = 0;

	VertexEdgeVertexMap::iterator VEVMit;
	VertexEdgeMMap VEMM;

	for (VEVMit=AdjacencyList.begin();VEVMit!=AdjacencyList.end();VEVMit++){
		VEMM     = (*VEVMit).second;
		EdgeCount+=(*VEVMit).second.size();
	}
	return (make_pair(AdjacencyList.size(),EdgeCount));
}

/**Graph*************************\
		GetAdjacencyList
\********************************/
template <class TV, class TE> Graph<TV,TE>::VertexEdgeVertexMap Graph<TV,TE>::GetAdjacencyList()
{
	return AdjacencyList;
}

/**Graph*************************\
		GetVertexList
\********************************/
template <class TV, class TE> Graph<TV,TE>::VertexMap Graph<TV,TE>::GetVertexList()
{
	return VertexList;
}

/**Graph*************************\
		GetAdjacencyMatrix
\********************************/
template <class TV, class TE> Matrix<TE> Graph<TV,TE>::GetAdjacencyMatrix()
{
	VertexEdgeVertexMap::iterator VEVMit;
	VertexEdgeMMap::iterator VEMMit;
	VertexEdgeMMap VEMM;
	Matrix<TE> M;
	pair<unsigned int, unsigned int> Size;
	size_t i;

	//Index table from Vertex to its order in AdjacencyList
	typedef map<Label,size_t> VindexMap; //size_t is the j coor. in the matrix
	VindexMap j;
	VindexMap::iterator jit;


	//Set the index table j
	i=0;
	for (VEVMit=AdjacencyList.begin();VEVMit!=AdjacencyList.end();VEVMit++){
		j.insert(VindexMap::value_type((*VEVMit).first,i));
		i++;
	}

	//Set matrix M with appropiate dimensions
	Size = Graph<TV,TE>::Size();
	M.Resize(Size.first, Size.first);

	//Loop the AdjacencyList to set the matrix M
	i=0;
	for (VEVMit=AdjacencyList.begin();VEVMit!=AdjacencyList.end();VEVMit++){
		VEMM     = (*VEVMit).second;
		for (VEMMit=VEMM.begin();VEMMit!=VEMM.end();VEMMit++){
			jit = j.find((*VEMMit).first);
			M[i][(*jit).second]=(*VEMMit).second;
		}
		i++;
	}
	return M;
}

/**Graph*************************\
		GetUndirectedGraph
\********************************/
template <class TV, class TE> Graph<TV,TE> Graph<TV,TE>::GetUndirectedGraph()
{
	Graph<TV,TE> UG;
	VertexEdgeMMap::iterator      VEMMit;
	VertexEdgeVertexMap::iterator VEVMit;
	VertexEdgeMMap VEMM;
	Label u, v;
	TE    w;

	if (!isDirected())
		UG = *this;
	else {
		UG.VertexList = VertexList;
		for (VEVMit=AdjacencyList.begin();VEVMit!=AdjacencyList.end();VEVMit++){
			u = (*VEVMit).first;
			VEMM     = (*VEVMit).second;
			for (VEMMit=VEMM.begin();VEMMit!=VEMM.end();VEMMit++){
				v  = (*VEMMit).first;
				w  = (*VEMMit).second;
				UG.AddEdge(u,v,w);
				UG.AddEdge(v,u,w);
			}
		}
	}
	UG.Directed = true;
	return UG;
}

/**Graph*************************\
		SetAsUndirectedGraph
\********************************/
template <class TV, class TE> Graph<TV,TE> & Graph<TV,TE>::SetAsUndirectedGraph()
{
	VertexEdgeMMap::iterator      VEMMit;
	VertexEdgeVertexMap::iterator VEVMit;
	VertexEdgeVertexMap VEVM;
	VertexEdgeMMap VEMM;
	Label u, v;
	TE    w;

	VEVM = AdjacencyList;
	if (isDirected())
		for (VEVMit=VEVM.begin();VEVMit!=VEVM.end();VEVMit++){
			u = (*VEVMit).first;
			VEMM     = (*VEVMit).second;
			for (VEMMit=VEMM.begin();VEMMit!=VEMM.end();VEMMit++){
				v = (*VEMMit).first;
				w = (*VEMMit).second;
				AddEdge(v,u,w);
			}
		}
	Directed = false;
	return *this;
}
/**Graph*************************\
		ShowPredecessorMap
\********************************/
template <class TV, class TE> void Graph<TV,TE>::ShowPredecessorMap(PredecessorMap PM)
{
	PredecessorMap::iterator PMit;

	for (PMit=PM.begin();PMit!=PM.end();PMit++){
		printf("u:%i,d:%.30g,p:%i\n",(*PMit).first,(*PMit).second.d,(*PMit).second.p);
	}
}

/**Graph*************************\
		ShowTimeMap
\********************************/
template <class TV, class TE> void Graph<TV,TE>::ShowTimeMap(TimeMap TM)
{
	TimeMap::iterator TMit;

	for (TMit=TM.begin();TMit!=TM.end();TMit++){
		printf("u:%i,d:%i,f:%i\n",(*TMit).first,(*TMit).second.d,(*TMit).second.f);
	}
}
/**Graph*************************\
		InitializeSingleSource
\********************************/
//Reference: Introduction to Algorithms. 
//           Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest
//           MIT Press
template <class TV, class TE> void Graph<TV,TE>::InitializeSingleSource(Label s,PredecessorMap & PM)
{
	VertexEdgeVertexMap::iterator VEVMit;
	PredecessorInfo PInfo;

	PM.clear();

	for (VEVMit=AdjacencyList.begin();VEVMit!=AdjacencyList.end();VEVMit++){
		PInfo.d = MaxWeight;
		PInfo.p = (*VEVMit).first;
		PM.insert(PredecessorMap::value_type((*VEVMit).first,PInfo));
	}
	PM[s].d = ZeroWeight;
	
}

/**Graph*************************\
		Relax
\********************************/
//Reference: Introduction to Algorithms. 
//           Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest
//           MIT Press
template <class TV, class TE> void Graph<TV,TE>::Relax(Label u,Label v,PredecessorMap & PM)
{
	TE w;
	GetWeight(u,v,w);
	if ((PM[u].d != MaxWeight) &&
		(PM[v].d > PM[u].d + w)) {
		PM[v].d = PM[u].d + w;
		PM[v].p = u;
	}
}

/**Graph*************************\
		SS_SP_Dijkstra
\********************************/
//Reference: Introduction to Algorithms. 
//           Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest
//           MIT Press
template <class TV, class TE> void Graph<TV,TE>::SS_SP_Dijkstra(Label s,PredecessorMap & PM)
{
	Graph<TV,TE> Path;
	PredecessorMap::iterator PMit;
	VertexEdgeMMap VEMM;
	VertexEdgeMMap::iterator VEMMit;

	Label u;
	LabelVector S;

	Qclass         Qaux;
	vector<Qclass> Q;
	vector<Qclass>::iterator Qit;


	InitializeSingleSource(s,PM);

	for (PMit=PM.begin();PMit!=PM.end();PMit++){
		Q.push_back(Qclass((*PMit).second.d,(*PMit).first));
	}
	

	while (Q.size()!=0){
		Qit = min_element(Q.begin(),Q.end());
		u = (*Qit).Vertex;
		Q.erase(Qit);
		S.push_back(u);
		VEMM = AdjacencyList[u];
		for (VEMMit=VEMM.begin();VEMMit!=VEMM.end();VEMMit++){
			Relax(u,(*VEMMit).first,PM);
		}

		for (Qit=Q.begin();Qit!=Q.end();Qit++){
			u        = (*Qit).Vertex;
			(*Qit).d = PM[u].d;
		}
	}

}

/**Graph*************************\
		DepthFirstSearch
\********************************/
//Reference: Introduction to Algorithms. 
//           Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest
//           MIT Press
template <class TV, class TE> void Graph<TV,TE>::DepthFirstSearch(TimeMap & TM)
{
	VertexEdgeVertexMap::iterator VEVMit;
	unsigned int GlobalTime = 0;
	VisitMap VM;

	TM.clear();

	for (VEVMit=AdjacencyList.begin();VEVMit!=AdjacencyList.end();VEVMit++){
		VM[(*VEVMit).first].c = white;
		VM[(*VEVMit).first].p = (*VEVMit).first;
	}

	for (VEVMit=AdjacencyList.begin();VEVMit!=AdjacencyList.end();VEVMit++){
		if (VM[(*VEVMit).first].c==white)
			DepthFirstSearchVisit((*VEVMit).first,VM,TM,GlobalTime);
	}

}

/**Graph*************************\
		DepthFirstSearchVisit
\********************************/
//Reference: Introduction to Algorithms. 
//           Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest
//           MIT Press
template <class TV, class TE> void Graph<TV,TE>::DepthFirstSearchVisit(Label u,VisitMap & VM,TimeMap & TM, unsigned int &GlobalTime)
{
	VertexEdgeMMap VEMM;
	VertexEdgeMMap::iterator VEMMit;
	Label v;
	
	VM[u].c = gray;
	TM[u].d = ++GlobalTime;

	VEMM = AdjacencyList[u];
	for (VEMMit=VEMM.begin();VEMMit!=VEMM.end();VEMMit++){
		v = (*VEMMit).first;
		if (VM[v].c == white){
			VM[v].p = u;
			DepthFirstSearchVisit(v,VM,TM,GlobalTime);
		}
	}
	VM[u].c = black;
	TM[u].f = ++GlobalTime;
}

/**Graph*************************\
		DAG_TopologicalSort
\********************************/
//Reference: Introduction to Algorithms. 
//           Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest
//           MIT Press
template <class TV, class TE> LabelVector Graph<TV,TE>::DAG_TopologicalSort(TimeMap & TM)
{
	typedef pair<unsigned int, Label> pair_f_Label;
	vector<pair_f_Label> TVV;
	vector<pair_f_Label>::iterator TVVit;
	TimeMap::iterator TMit;
	LabelVector LV;

	DepthFirstSearch(TM);

	TM.clear();
	LV.clear();
	DepthFirstSearch(TM);

	for (TMit=TM.begin();TMit!=TM.end();TMit++){
		TVV.push_back(make_pair((*TMit).second.f,(*TMit).first));
	}
	sort(TVV.begin(),TVV.end());

	for (TVVit=TVV.end()-1;TVVit!=TVV.begin();TVVit--){
		LV.push_back((*TVVit).second);
	}
	LV.push_back((*TVV.begin()).second);

	return LV;
}

/**Graph*************************\
		SS_SP_DAG
\********************************/
//Reference: Introduction to Algorithms. 
//           Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest
//           MIT Press

template <class TV, class TE> void Graph<TV,TE>::SS_SP_DAG(Label s,PredecessorMap & PM)
{
	TimeMap TM;
	LabelVector LV;
	LabelVector::iterator LVit;
	VertexEdgeMMap VEMM;
	VertexEdgeMMap::iterator VEMMit;
//1	pVertexTV u,v;

	LV = DAG_TopologicalSort(TM);
	InitializeSingleSource(s,PM);

	for (LVit=LV.begin();LVit!=LV.end();LVit++){
		VEMM = AdjacencyList[*LVit];
//1		u = *LVit;
		for (VEMMit=VEMM.begin();VEMMit!=VEMM.end();VEMMit++){
//1			v = (*VEMMit).first;
//1			Relax(u,v,PM);
			Relax(*LVit,(*VEMMit).first,PM); // For clarity this line can be replaced by //1
		}
	}
}

	
/**Graph*************************\
		BreathFirstSearch
\********************************/
//Reference: Introduction to Algorithms. 
//           Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest
//           MIT Press
template <class TV, class TE> void Graph<TV,TE>::BreathFirstSearch(Label s,PredecessorMap & PM)
{
	VertexEdgeMMap VEMM;
	VertexEdgeMMap::iterator VEMMit;
	VertexEdgeVertexMap::iterator VEVMit;
	VisitMap VM;
	deque<Label> Q;
	deque<Label>::iterator Qit;
	Label u,v;
	Graph<TV,TE> GU;

	PM.clear();
	isDirected()?GU=GetUndirectedGraph():GU=*this;

	for (VEVMit=GU.AdjacencyList.begin();VEVMit!=GU.AdjacencyList.end();VEVMit++)
		if ((*VEVMit).first !=s) {
			VM[(*VEVMit).first].c = white;
			PM[(*VEVMit).first].d = MaxWeight;
			PM[(*VEVMit).first].p = (*VEVMit).first;

		}	
	VM[s].c = gray;
	PM[s].d = ZeroWeight;
	PM[s].p = s;
	
//printf("Q.size():%i\n",Q.size());
//for (Qit=Q.begin();Qit!=Q.end();Qit++)
//	printf("%i,",(*Qit)->Label);
//printf("\n"); 
//ShowPredecessorMap(PM);

	Q.push_back(s);

	while(Q.size()!=0){
for (Qit=Q.begin();Qit!=Q.end();Qit++); //There is a problem with deque container. This line eliminates it in a non ortodoxe way.
		u = Q.front();
		VEMM = GU.AdjacencyList[u];
		for (VEMMit=VEMM.begin();VEMMit!=VEMM.end();VEMMit++){
			v = (*VEMMit).first;
			if (VM[v].c == white) {
				VM[v].c = gray;
				PM[v].d = PM[u].d + 1;
				PM[v].p = u;
				Q.push_back(v);
			}
		}
		Q.pop_front();
		VM[u].c = black;
	}
}

/**Graph*************************\
		Subgraphs
\********************************/
template <class TV, class TE> void Graph<TV,TE>::Subgraphs(GraphVector & GV)
{
	LabelVector V,Vs,Vd;
	LabelVector::iterator Vditend;
	PredecessorMap PM;
	Label s;
	Graph<TV,TE> G;

	GV.clear();
	Vd = GetV();
	
	while (Vd.size()!=0){
		V = Vd;
		s = *V.begin();
		Vs = GetVs(s);
		G.Clear();
		G = GetSubgraph(Vs);
//G.ShowAdjacencyList();
		GV.push_back(G);
		//In this case I know Vd.size() will be V.size()-Vs.size() because Vs is a subset of V
		//thus Vditend will be equal to Vd.end();
		Vd.resize(V.size()-Vs.size());
		Vditend = set_difference(V.begin(),V.end(),Vs.begin(),Vs.end(),Vd.begin());

//		printf("Vd.size():%i\n",Vd.size());
//		V.Show();
//		Vs.Show();
//		printf("\n");
//		Vd.Show();
	} 
}


/**Graph*************************\
		GetSubgraph
\********************************/

template <class TV, class TE> Graph<TV,TE> Graph<TV,TE>::GetSubgraph(LabelVector LV)
{
	Graph<TV,TE> G;
	LabelVector V,Vd;
	LabelVector::iterator LVit,Vditend;

	V = GetV();
	Vd.resize(V.size()-LV.size());
	Vditend = set_difference(V.begin(),V.end(),LV.begin(),LV.end(),Vd.begin());
	
	G = *this;

	for (LVit=Vd.begin();LVit!=Vd.end();LVit++)
		G.RemoveVertex(*LVit);

	return G;
}

//template <class TV, class TE> void Graph<TV,TE>::find(pVertexTV u, pVertexTVVector pVV,pVertexTVVector::iterator &pVVit)
//{
//	for (pVVit=pVV.begin();pVVit!=pVV.end();pVVit++)
//		if ((*pVVit)==u) break;
//}


/**Graph*************************\
 ExtractVisitedVertexFromPredecessorMap
\********************************/
template <class TV, class TE> LabelVector Graph<TV,TE>::ExtractVisitedVertexFromPredecessorMap(PredecessorMap PM)
{
	PredecessorMap::iterator PMit;
	LabelVector LV;

	LV.clear();
	for (PMit=PM.begin();PMit!=PM.end();PMit++)
		if ((*PMit).second.d != MaxWeight)
			LV.push_back((*PMit).first);
	return LV;
}

/**Graph*************************\
		GetV
\********************************/
template <class TV, class TE> LabelVector Graph<TV,TE>::GetV()
{
	VertexEdgeVertexMap::iterator VEVMit;
	LabelVector V;
	V.clear();
	for (VEVMit=AdjacencyList.begin();VEVMit!=AdjacencyList.end();VEVMit++){
		V.push_back((*VEVMit).first);
	}
	return V;
}

/**Graph*************************\
		GetVs
\********************************/
template <class TV, class TE> LabelVector Graph<TV,TE>::GetVs(Label s)
{
	PredecessorMap PM;
	LabelVector Vs;

	Vs.clear();
	BreathFirstSearch(s,PM);
	Vs = ExtractVisitedVertexFromPredecessorMap(PM);

	return Vs;
}

} //namespace GAC

#endif // !defined(_GRAPH_H_)
