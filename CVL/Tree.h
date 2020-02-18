/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Tree.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:05:17 $
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


#if !defined(_TREE_H_)
#define _TREE_H_

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include <algorithm>
#include "Graph.h"

namespace GAC
{

template <class TV, class TE> class Tree : public Graph<TV,TE>
{
//Public functions
public:
	Tree():Graph<TV,TE>(){};
	Tree(bool Weighted,TE MaxWeight,TE ZeroWeight):Graph<TV,TE>(Weighted,MaxWeight,ZeroWeight){};
	Tree(const Graph<TV,TE> &G):Graph<TV,TE>(G){}; //Default copy constructor
    virtual	~Tree(){};

	void SetRoot         (Label s);
	size_t      Height   (Label n);    //Tree's depth
	size_t      Depth    (Label n);    //Node's depth
	Tree<TV,TE> SubTree  (Label n);
	bool        isLeaf   (Label n);
	LabelVector GetLeafs ();
	LabelVector GetNodesAtDepth(size_t d,Label n);
	LabelVector Path(Label n);
//Private functions
private:
	Label Root;

};

/**Tree**************************\
			Path
\********************************/
template <class TV, class TE> LabelVector Tree<TV,TE>::Path(Label n)
{
	LabelVector PathVector,Parents;

	Parents = GetParents(n);

	if (Parents.size() == 0) {
		PathVector.push_back(n);
		return PathVector;
	}
	else {
		PathVector = Path(*(Parents.begin()));
		PathVector.push_back(n);
		return 		PathVector;
	}
}

/**Tree**************************\
			GetNodesAtDepth
\********************************/
template <class TV, class TE> LabelVector Tree<TV,TE>::GetNodesAtDepth(size_t d,Label n)
{
	LabelVector NodesAtDepth,NodesAtNextDepth,Children;
	LabelVector::const_iterator LVit,LV1it;
	size_t MaxDepth = 0;
	typedef Tree<TV,TE> TreeTVTE;
	vector<TreeTVTE> TreeVector;

	Children = GetChildren(n);

	if (d == 1)
		return Children;
	else {
		for (LVit = Children.begin();LVit!=Children.end();LVit++){
			NodesAtNextDepth = GetNodesAtDepth(d-1,(*LVit));
			for (LV1it = NodesAtNextDepth.begin();LV1it!=NodesAtNextDepth.end();LV1it++)
				NodesAtDepth.push_back(*LV1it);
		}
		return NodesAtDepth;
	}
}

/**Tree**************************\
			GetLeafs
\********************************/
template <class TV, class TE> LabelVector Tree<TV,TE>::GetLeafs()
{
	return GetSinkVertexes();
}


/**Tree**************************\
			isLeaf
\********************************/
template <class TV, class TE> bool Tree<TV,TE>::isLeaf(Label s)
{
	return (GetChildren.size()==0);
}

/**Tree**************************\
			SetRoot
\********************************/
template <class TV, class TE> void Tree<TV,TE>::SetRoot(Label s)
{
	Root = s;
}

/**Tree**************************\
			Height
\********************************/
template <class TV, class TE> size_t Tree<TV,TE>::Height(Label n)
{
	LabelVector Children;
	LabelVector::const_iterator LVit;
	size_t MaxDepth = 0;

	Children = GetChildren(n);

	if (Children.size() == 0) return 0;
	else {
		for (LVit = Children.begin();LVit!=Children.end();LVit++){
			MaxDepth = _MAX(MaxDepth,Height(*LVit));
		}
		return MaxDepth+1;
	}
}

/**Tree**************************\
			Depth
\********************************/
template <class TV, class TE> size_t Tree<TV,TE>::Depth(Label n)
{
	LabelVector Parents;
	LabelVector::const_iterator LVit;
	size_t MaxDepth = 0;

	Parents = GetParents(n);

	if (Parents.size() == 0) return 0;
	else {
		for (LVit = Parents.begin();LVit!=Parents.end();LVit++){
			MaxDepth = _MAX(MaxDepth,Depth(*LVit));
		}
		return MaxDepth+1;
	}
}


/**Tree**************************\
			Subtree
\********************************/
template <class TV, class TE> Tree<TV,TE> Tree<TV,TE>::SubTree(Label n)
{
	Tree<TV,TE> ST;
	PredecessorMap PM;

	SS_SP_DAG(n,PM);
	ST = GetSubgraph(ExtractVisitedVertexFromPredecessorMap(PM));
	return ST;
}

} //namespace GAC

#endif // !defined(_TREE_H_)