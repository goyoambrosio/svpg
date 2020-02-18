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


#if !defined(_SEGMENTMULTIAHGRAPH_H_)
#define _SEGMENTMULTIAHGRAPH_H_

#define LEDA_PREFIX
//#define LEDA_STD_HEADERS

#include <CVL/Image.h>
#include <CVL/MultiAHgraph.h>
#include <CVL/CGALgeometry.h>
#include <CVL/CGALpoint.h>
#include <CVL/CGALsegment.h>

#include <vector>
#include <LEDA/ugraph.h>
#include <LEDA/graph_alg.h>
#include <LEDA/graphwin.h>



namespace GAC
{

/********************************************\
 *             SegmentNodeValue             *
\********************************************/
class SegmentNodeValue : public vector<CGALSegment*>
{
public:
    SegmentNodeValue();
    virtual ~SegmentNodeValue();

    show();
    friend ostream &operator<<(ostream &s,const SegmentNodeValue & snv);

    //Image:Segment EquivalentSegment();
};

/********************************************\
 *           SegmentNodeAnnotation          *
\********************************************/
class SegmentNodeAnnotation
{
public:
    SegmentNodeAnnotation();
    virtual ~SegmentNodeAnnotation();

    show();
    friend ostream &operator<<(ostream &s,const SegmentNodeAnnotation & sna);

    unsigned int d_label;
    CGALSegment d_abstractSegment;

};

/********************************************\
 *           SegmentAnnotatedNode           *
\********************************************/
class SegmentAnnotatedNode:public AnnotatedNode<SegmentNodeValue,SegmentNodeAnnotation>
{
public:
    SegmentAnnotatedNode():AnnotatedNode<SegmentNodeValue,SegmentNodeAnnotation>(){};
    SegmentAnnotatedNode(const AnnotatedNode<SegmentNodeValue,SegmentNodeAnnotation> &r):AnnotatedNode<SegmentNodeValue,SegmentNodeAnnotation>(r){};

    //Visualization
    show();
	friend  ostream &operator<<(ostream &s, SegmentAnnotatedNode san);
	friend  istream &operator>>(istream &s, SegmentAnnotatedNode san);

    virtual ~SegmentAnnotatedNode();

};

/********************************************\
 *               SegmentArcCost             *
\********************************************/
class SegmentArcCost
{
public:
    SegmentArcCost();
    virtual ~SegmentArcCost();

    double d_affinity;

    show();

};

/********************************************\
 *           SegmentArcAnnotation           *
\********************************************/
class SegmentArcAnnotation
{
public:
    SegmentArcAnnotation();
    virtual ~SegmentArcAnnotation();

    enum PerceptualSuit {ARC_TYPE_PERONA,ARC_TYPE_PROX,ARC_TYPE_PAR,ARC_TYPE_COL,ARC_TYPE_CONV};

    PerceptualSuit d_type;

    struct d_perona_struct{
        double d_d0;             //Initial parameter to compute Perona's affinity
        double d_theta0;         //Initial parameter to compute Perona's affinity
        double d_delta;          //Initial parameter to compute Perona's affinity
        double d_alfai;
        double d_alfaj;
        double d_dij;
        double d_proximity;      //Affinity
        double d_collinearity;   //Affinity
        double d_cocircularity;  //Affinity
    } d_perona;

    struct d_parallel_struct{
        double d_dij;
        double d_alfaij;
        double d_overlap;
    } d_parallel;

    struct d_collinear_struct{
        double d_dij;
        double d_alfai;
        double d_alfaj;
    } d_collinear;

    struct d_convex_struct{
        double d_dij;
        double d_alfai;
        double d_alfaj;
    } d_convex;

    struct d_proximal_struct{
        double d_dij;
    } d_proximal;

    show();
};

/********************************************\
 *           SegmentAnnotatedArc            *
\********************************************/
class SegmentAnnotatedArc:public AnnotatedArc<SegmentArcCost,SegmentArcAnnotation>
{
public:
    SegmentAnnotatedArc();
    virtual ~SegmentAnnotatedArc();

    show();

};

/********************************************\
 *           SegmentPUAmultigraph           *
\********************************************/
class SegmentPUAmultigraph:public PUAmultigraph<SegmentNodeValue,SegmentNodeAnnotation,SegmentArcCost,SegmentArcAnnotation>
{
public:

    SegmentPUAmultigraph();
    virtual ~SegmentPUAmultigraph();

    edit();
	bool s(SegmentPUAmultigraph &newGraph); //abstraction function

    SegmentPUAmultigraph &setPeronaArcs   (double d0, double theta0, double delta);
    SegmentPUAmultigraph &setParallelArcs (double d0, double theta0, double delta);
    SegmentPUAmultigraph &setCollinearArcs(double d0, double theta0, double delta);
    SegmentPUAmultigraph &setConvexArcs   (double d0, double theta0, double delta);
    SegmentPUAmultigraph &setProximalArcs (double d0, double theta0, double delta);

    SegmentPUAmultigraph &hideEdgesOfType(SegmentArcAnnotation::PerceptualSuit type);
    SegmentPUAmultigraph &restoreEdgesOfType(SegmentArcAnnotation::PerceptualSuit type);

private:
    enum Colormap {RED,GREEN,BLUE,ORANGE};

    double affinityPerona(double d0, 
                          double theta0, 
                          double delta, 
                          double dij,
                          double alfai,
                          double alfaj);
    double affinityProximity    (double d0,double dij);
    double affinityCollinearity (double theta0,double alfai,double alfaj);
    double affinityCocircularity(double theta0,double delta,double alfai,double alfaj);
    double affinityParallelism  (double theta0,double delta,double alfaij);

    bool areConvex(Image::Segment S1,Image::Segment S2,double maxNoConvexityThreshold);
    Level2Color (double level,int &r, int &g, int &b, Colormap cm);

};


/********************************************\
 *          MultiAHgraphArcCost             *
\********************************************/
class MultiAHgraphArcCost
{
public:
    MultiAHgraphArcCost();
    virtual ~MultiAHgraphArcCost();

};

/********************************************\
 *        MultiAHgraphArcAnnotation         *
\********************************************/
class MultiAHgraphArcAnnotation
{
public:
    MultiAHgraphArcAnnotation();
    virtual ~MultiAHgraphArcAnnotation();

};

/********************************************\
 *        MultiAHgraphAnnotatedArc          *
\********************************************/
class MultiAHgraphAnnotatedArc:public AnnotatedArc<MultiAHgraphArcCost,MultiAHgraphArcAnnotation>
{
public:
    MultiAHgraphAnnotatedArc();
    virtual ~MultiAHgraphAnnotatedArc();

};

/********************************************\
 *           SegmentMultiAHgraph            *
\********************************************/
class SegmentMultiAHgraph:public MultiAHgraph<SegmentPUAmultigraph,MultiAHgraphArcCost,MultiAHgraphArcAnnotation>
{
public:
    SegmentMultiAHgraph();
    virtual ~SegmentMultiAHgraph();

    //Parameters for abstraction levels
    //d_propertyParameters[0] --> parameters for ground hierarchical level
    //d_propertyParameters[1] --> parameters for first hierarchical level
    // ...
    //d_propertyParameters.last() --> parameters for universal hierarchical level
//    vector<d_parallelismParametersStruct>  d_parallelismParameters;
//    vector<d_collinearityParametersStruct> d_collinearityParameters;
//    vector<d_convexityParametersStruct>    d_convexityParameters;
//    vector<d_proximityParametersStruct>    d_proximityParameters;

    struct PeronaParametersStruct {
        double d0;
        double theta0;
        double delta;
    };
    typedef pair <unsigned int const,PeronaParametersStruct> PeronaParameters;


    struct ParallelParametersStruct {
        double d0;
        double theta0;
        double delta;
    };
    typedef pair <unsigned int const,ParallelParametersStruct> ParallelParameters;

  
    struct CollinearParametersStruct {
        double d0;
        double theta0;
        double delta;
    };
    typedef pair <unsigned int const,CollinearParametersStruct> CollinearParameters;


    struct ConvexParametersStruct {
        double d0;
        double theta0;
        double delta;
    };
    typedef pair <unsigned int const,ConvexParametersStruct> ConvexParameters;

    struct ProximalParametersStruct {
        double d0;
        double theta0;
        double delta;
    };
    typedef pair <unsigned int const,ProximalParametersStruct> ProximalParameters;


    multimap<unsigned int, PeronaParametersStruct>       d_peronaParameters;
    multimap<unsigned int, ParallelParametersStruct>     d_parallelParameters;
    multimap<unsigned int, CollinearParametersStruct>    d_collinearParameters;
    multimap<unsigned int, ConvexParametersStruct>       d_convexParameters;
    multimap<unsigned int, ProximalParametersStruct>     d_proximalParameters;


    edit();
    SegmentMultiAHgraph &setL0(Image::SegmentVector &initialSegmentSet);
    SegmentMultiAHgraph &addL0(ParallelParametersStruct  parallelParameters,
                               CollinearParametersStruct collinearParameters,
                               ConvexParametersStruct    convexParameters,
                               ProximalParametersStruct  proximityParameters
                               );
                                                
    SegmentMultiAHgraph &generateAbstraction();


private:

    CGALSegmentVector segmentSetCGAL;

    Image::SegmentVector segmentSet;

    SegmentPUAmultigraph nodeCreation(SegmentPUAmultigraph &baseG);

};

} //namespace GAC

#endif // !defined(_SEGMENTMULTIAHGRAPH_H_)
