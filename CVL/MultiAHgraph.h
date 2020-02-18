/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: GrayImage.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:28 $
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
/**************************************************************************\
* Name      :
* Member of : 
* Purpose   : 
* Returns   :    
* Parameters: 
* Notes     :
* Author    : 
* Date      : 
* Modified  :
\**************************************************************************/


#if !defined(_MULTIAHGRAPH_H_)
#define _MULTIAHGRAPH_H_

#define LEDA_PREFIX
#define LEDA_STD_HEADERS

#include <iostream>  //For use with CGAL's stlport. Comment for use with STL-3.2

#include <vector>
#include <LEDA/ugraph.h>

using namespace std; //For use with CGAL's stlport. Comment for use with STL-3.2

namespace GAC
{
/********************************************\
 * Plain Directed Annotated Multigraph Node *
\********************************************/
template <class ValueType, class AnnotationType>
class AnnotatedNode
{
public:
    AnnotatedNode();
	AnnotatedNode(const AnnotatedNode<ValueType,AnnotationType> &an);
    virtual ~AnnotatedNode();

    //Visualization
	friend ostream &operator<<(ostream &s,const AnnotatedNode<ValueType, AnnotationType> &N);
	friend istream &operator>>(istream &s,const AnnotatedNode<ValueType, AnnotationType> &N);

    ValueType      d_value;
    AnnotationType d_annotation;

	AnnotatedNode<ValueType, AnnotationType>         *d_supernode;  //each node can be mapped in zero (null) or just one supernode
	vector<AnnotatedNode<ValueType, AnnotationType>*> d_infranodes; //if it's a supernode, this vector contains pointer to nodes which composed it
	bool isSupernode();

};

/********************************************\
 * Plain Directed Annotated Multigraph Arc *
\********************************************/
template <class CostType, class AnnotationType>
class AnnotatedArc
{
public:
    AnnotatedArc();
    virtual ~AnnotatedArc();

    //Visualization
	friend  ostream &operator<<(ostream &s, AnnotatedArc<CostType, AnnotationType> E);
	friend  istream &operator>>(istream &s, AnnotatedArc<CostType, AnnotationType> E);

    CostType       d_cost;
    AnnotationType d_annotation;

};


/***************************************\
 * Plain Directed Annotated Multigraph *
\***************************************/
//NOTES:
//- User is responsible for suplying abstraction functions for nodes in herisated classes
template <class NodeValueType, class NodeAnnotationType, class ArcCostType, class ArcAnnotationType>
class PDAmultigraph : public GRAPH<AnnotatedNode<NodeValueType,NodeAnnotationType>, AnnotatedArc<ArcCostType,ArcAnnotationType> >
{
public:
    PDAmultigraph();
    virtual ~PDAmultigraph();
};

/***************************************\
 *Plain Undirected Annotated Multigraph*
\***************************************/
//NOTES:
//- User is responsible for suplying abstraction functions for nodes in herisated classes
template <class NodeValueType, class NodeAnnotationType, class ArcCostType, class ArcAnnotationType>
class PUAmultigraph : public UGRAPH<AnnotatedNode<NodeValueType,NodeAnnotationType>, AnnotatedArc<ArcCostType,ArcAnnotationType> >
{
public:
    PUAmultigraph();
    virtual ~PUAmultigraph();
};

/***************************************\
 *  Annotated Hierarchical Multigraph  *
\***************************************/
//NOTES:
//- User is responsible for suplying abstraction functions for nodes in herisated classes

template <class GraphType>
class AHgraph : public vector<GraphType>
{
public:
    //CREATORS
    AHgraph();
    virtual ~AHgraph();

    //MANIPULATORS

    //ACCESORS
    unsigned int getDepth();
    GraphType getHierarchicalLevel         (unsigned int L);
    GraphType getGroundHierarchicalLevel   ();
    GraphType getUniversalHierarchicalLevel();

};


/***************************************\
 *       Labelled MultiAHgraphs        *
\***************************************/
//NOTES:
//- User is responsible for suplying abstraction functions for nodes in herisated classes
template <class NodeValueType, class NodeAnnotationType, class ArcCostType, class ArcAnnotationType>
class MultiAHgraph : public GRAPH<AnnotatedNode<NodeValueType,NodeAnnotationType>,AnnotatedArc<ArcCostType,ArcAnnotationType> >
{
public:
    //CREATORS
    MultiAHgraph();
    virtual ~MultiAHgraph();

    //MANIPULATORS

    //ACCESORS

//TO DO
//	map<unsigned int, vector<GraphType*> > getHiearchyMap();

//    unsigned int getDepth();
//    GraphType getHierarchicalLevel         (unsigned int L);
//    GraphType getGroundHierarchicalLevel   ();
//    GraphType getUniversalHierarchicalLevel();

//private:
//	map<unsigned int, vector<*GraphType> > hierarchyMap;

};


/**************************************************************************\
*		                                                                   *
*		                    DEFINITIONS                                    *
*                                                                          *
\**************************************************************************/


/********AnnotatedNode*****************************************************\
		
  	  
		                    Class AnnotatedNode


\**************************************************************************/

/**AnnotatedNode***********************\
		      AnnotatedNode
\**************************************/
template <class ValueType, class AnnotationType>
AnnotatedNode<ValueType,AnnotationType>::AnnotatedNode(){
	d_supernode = NULL;
}

/**AnnotatedNode***********************\
		      AnnotatedNode
\**************************************/

template <class ValueType, class AnnotationType>
AnnotatedNode<ValueType,AnnotationType>::AnnotatedNode(const AnnotatedNode<ValueType,AnnotationType> &an){
    d_value      = an.d_value;
    d_annotation = an.d_annotation;
	d_supernode  = an.d_supernode;
	copy(an.d_infranodes.begin(),an.d_infranodes.end(),d_infranodes.begin());

}

/**AnnotatedNode***********************\
		      ~AnnotatedNode
\**************************************/
template <class ValueType, class AnnotationType>
AnnotatedNode<ValueType,AnnotationType>::~AnnotatedNode(){

}

/**AnnotatedNode***********************\
		      operator<<
\**************************************/
template <class ValueType, class AnnotationType>
ostream &operator<<(ostream &s,const AnnotatedNode<ValueType,AnnotationType> &N)
{
	return s;
}

/**AnnotatedNode***********************\
		      operator>>
\**************************************/
template <class ValueType, class AnnotationType>
istream &operator>>(istream &s,const AnnotatedNode<ValueType,AnnotationType> &N)
{
	return s;
}

/**AnnotatedNode***********************\
		      isSupernode
\**************************************/
template <class ValueType, class AnnotationType>
bool AnnotatedNode<ValueType,AnnotationType>::isSupernode(){
	return !d_infranodes.empty();
}

/********AnnotatedArc*****************************************************\
		
  	  
		                    Class AnnotatedArc


\**************************************************************************/

/**AnnotatedArc***********************\
		      AnnotatedArc
\**************************************/
template <class CostType, class AnnotationType>
AnnotatedArc<CostType,AnnotationType>::AnnotatedArc(){

}

/**AnnotatedArc***********************\
		     ~AnnotatedArc
\**************************************/
template <class CostType, class AnnotationType>
AnnotatedArc<CostType,AnnotationType>::~AnnotatedArc(){

}

/**AnnotatedArc***********************\
		     operator<<
\**************************************/
template <class CostType, class AnnotationType>
ostream &operator<<(ostream &s, AnnotatedArc<CostType,AnnotationType> E)
{
	s << "Arc" << endl;
	return s;
}

/**AnnotatedArc***********************\
		     operator>>
\**************************************/
template <class CostType, class AnnotationType>
istream &operator>>(istream &s, AnnotatedArc<CostType,AnnotationType> E)
{
	return s;
}


/********PDAmultigraph*****************************************************\
		
  	  
		                    Class PDAmultigraph


\**************************************************************************/

/**PDAmultigraph***********************\
		      PDAmultigraph
\**************************************/
template <class NodeValueType, class NodeAnnotationType, class ArcCostType, class ArcAnnotationType>
PDAmultigraph <NodeValueType,NodeAnnotationType,ArcCostType,ArcAnnotationType>
::PDAmultigraph(){

}

/**PDAmultigraph***********************\
		      ~PDAmultigraph
\**************************************/
template <class NodeValueType, class NodeAnnotationType, class ArcCostType, class ArcAnnotationType>
PDAmultigraph <NodeValueType,NodeAnnotationType,ArcCostType,ArcAnnotationType>
::~PDAmultigraph(){

}

/********PUAmultigraph*****************************************************\
		
  	  
		                    Class PUAmultigraph


\**************************************************************************/

/**PUAmultigraph***********************\
		      PUAmultigraph
\**************************************/
template <class NodeValueType, class NodeAnnotationType, class ArcCostType, class ArcAnnotationType>
PUAmultigraph <NodeValueType,NodeAnnotationType,ArcCostType,ArcAnnotationType>
::PUAmultigraph(){

}

/**PUAmultigraph***********************\
		      ~PUAmultigraph
\**************************************/
template <class NodeValueType, class NodeAnnotationType, class ArcCostType, class ArcAnnotationType>
PUAmultigraph <NodeValueType,NodeAnnotationType,ArcCostType,ArcAnnotationType>
::~PUAmultigraph(){

}

/********AHgraph*************************************************************\
		
  	  
		                    Class AHgraph


\**************************************************************************/

/**AHgraph*****************************\
		       AHgraph
\**************************************/
template <class GraphType>
AHgraph<GraphType>::AHgraph(){

}

/**AHgraph*****************************\
		       ~AHgraph
\**************************************/
template <class GraphType>
AHgraph<GraphType>::~AHgraph(){

}

/**************************************************************************\
* Name      : Depth
* Member of : AHgraph
* Purpose   : 
* Returns   : The number of hierarchical levels of the AHgraph   
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 15.04.00
* Modified  :
\**************************************************************************/
template <class GraphType>
unsigned int AHgraph<GraphType>::getDepth() {
    return size();
}

/**************************************************************************\
* Name      : HierarchicalLevel
* Member of : AHgraph
* Purpose   : 
* Returns   : The graph in the level L   
* Parameters: 
*    L - Level number
* Notes     : L = 0 ---> GroundHierarchicalLevel
* Author    : GAC
* Date      : 15.04.00
* Modified  : 
\**************************************************************************/
template <class GraphType>
GraphType AHgraph<GraphType>::getHierarchicalLevel(unsigned int L){
    return *this[L];
}


/**************************************************************************\
* Name      : GroundHierarchicalLevel
* Member of : AHgraph
* Purpose   : To obtain the data with the maximun amount of data available.
* Returns   : The graph in the level 0   
* Parameters: 
*    L - Level number
* Notes     :
* Author    : GAC
* Date      : 15.04.00
* Modified  :
\**************************************************************************/
template <class GraphType>
GraphType AHgraph<GraphType>::getGroundHierarchicalLevel(){
    return front();
}

/**************************************************************************\
* Name      : UniversalHierarchicalLevel
* Member of : AHgraph
* Purpose   : To obtain the data with the minimun amount of detail.
* Returns   : The graph in the last level   
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 15.04.00
* Modified  :
\**************************************************************************/
template <class GraphType>
GraphType AHgraph<GraphType>::getUniversalHierarchicalLevel(){
    return back();
}


/********MultiAHgraph******************************************************\
		
  	  
		                    Class MultiAHgraph


\**************************************************************************/

/**MultiAHgraph************************\
		       MultiAHgraph
\**************************************/

template <class NodeValueType, class NodeAnnotationType, class ArcCostType, class ArcAnnotationType>
MultiAHgraph<NodeValueType,NodeAnnotationType,ArcCostType,ArcAnnotationType>::MultiAHgraph(){

}

/**MultiAHgraph************************\
		       ~MultiAHgraph
\**************************************/

template <class NodeValueType, class NodeAnnotationType, class ArcCostType, class ArcAnnotationType>
MultiAHgraph<NodeValueType,NodeAnnotationType,ArcCostType,ArcAnnotationType>::~MultiAHgraph(){

}


} //namespace GAC

#endif // !defined(_MULTIAHGRAPH_H_)
