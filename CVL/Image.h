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


#if !defined(_IMAGE_H_)
#define _IMAGE_H_

#define LEDA_PREFIX
//#define LEDA_STD_HEADERS

#include <CVL/Globals.h>
#include <CVL/DirectedLineSegment.h>
#include <CVL/TypedMatrix.h>

#include <algorithm>
#include <string>                     //From SGI STL. For ios functions. It's like #include <iostream>

#include <LEDA/ugraph.h>
#include <LEDA/graph_alg.h>
#include <LEDA/graphwin.h>

namespace GAC
{

class Image : public UcharMatrix
{

public:
    ///////////////////////////////////
    // Class Pixel
    //////////////////////////////////
    class Pixel: public Point2D
    {
    public:
	    //Construction
	    Pixel():Point2D(){Level = 0;};
        Pixel(double Row,double Col, unsigned char Level):Point2D(Row,Col){Pixel::Level = Level;};
	    virtual ~Pixel();

	    //Setting
	    Pixel &Set(unsigned char Level);
	    Pixel &Set(double Row, double Col, unsigned char Level);

	    //Operators
	    bool operator==(Pixel &P);
	    bool operator< (Pixel &P);
	    bool operator!=(Pixel &P);

	    //Visualization
	    friend  ostream &operator<<(ostream &s, Pixel P);
	    void Show();

	    //Serialize
//	    size_t Serialize(FILE * stream);


    public:
	    //Public data
	    unsigned char Level;
    };

    ///////////////////////////////////
    // Class PixelVector
    //////////////////////////////////
    class PixelVector : public vector<Pixel> 
    {
    public:
	    PixelVector();
	    virtual ~PixelVector();

	    //Visualization
	    void Show();

	    //Serialize
//	    size_t Serialize(FILE * stream);

    };

    ///////////////////////////////////
    // Class Segment
    //////////////////////////////////
    class Segment : public DirectedLineSegment  
    {
    public:
	    //Construction
	    Segment():DirectedLineSegment(){};
        Segment(unsigned int Label, double Pi,double Pj, double Qi, double Qj):DirectedLineSegment(Pi,Pj,Qi,Qj){Segment::Label = Label;};
	    Segment(unsigned int Label,Point2D P, Point2D Q):DirectedLineSegment(P,Q){Segment::Label = Label;};
//	    Segment(unsigned int Label,Pixel P, Pixel Q):DirectedLineSegment(Point2D(P),Point2D(Q)){Segment::Label = Label;};

	    //Operators
	    bool operator< (Segment &S);

        // Computes the minimum distance between the nearest endpoints of segments
	    double EndPointDistance(Segment& S);
        // Computes the minimum distance between midpoint of segments
	    double MidPointDistance(Segment& S);
        //Computes the module of the overlapping between this segment and the perpendicular 
        //projection of S over this segment
	    double OverlapMod      (Segment& S);

	    //Visualization
	    void Show();
        friend ostream &operator<<(ostream &s,const Segment &S){}; //Only for leda's GRAPH<Segment,...> type declaration
        friend istream &operator>>(istream &s,const Segment &S){}; //Only for leda's GRAPH<Segment,...> type declaration

	    //Serialize
//	    size_t Serialize(FILE * stream);
    public:
	    //Public data
	    unsigned int Label;			//Etiqueta identificativa del segmento
    };

    ///////////////////////////////////
    // Class SegmentGraph
    //////////////////////////////////

    class SegmentGraph : public UGRAPH<Segment*, double>
    {
    public:
        SegmentGraph();
        virtual ~SegmentGraph();

	    SegmentGraph &SetAdjacencyMatrix(DoubleMatrix M);
	    DoubleMatrix  GetAdjacencyMatrix();
        SegmentGraph &Edit(int AnimationSteps = 16);
    };



    ///////////////////////////////////
    // Class SegmentVector
    //////////////////////////////////
//    class PerceptualGroup; //Early definition
    class SegmentVector : public vector <Segment>
    {
    public:
        SegmentVector();
        virtual ~SegmentVector();

	    //Visualization
	    void Show();
//        friend ostream &operator<<(std::ostream &s, SegmentVector &S);
/*
        SegmentGraph EndPointDistanceGraph();
	    SegmentGraph MidPointDistanceGraph();
	    SegmentGraph ShortAngleGraph();
	    SegmentGraph OverlapModGraph();

	    DoubleMatrix EndPointDistanceMatrix();
	    DoubleMatrix MidPointDistanceMatrix();
	    DoubleMatrix ShortAngleMatrix();
	    DoubleMatrix OverlapModMatrix();
	    

	    void ParallelGraph	(SegmentGraph & DistanceGraph,
						     SegmentGraph & AngleGraph,
						     SegmentGraph & OverlapGraph,
						     double MaxDistance,double MinDistance,double MaxAngle);

	    void CollinearGraph (SegmentGraph & DistanceGraph, 
						     double MaxDistance,double MaxAngle,double MaxParallelDistance = 1.0);

	    void ConvexGraph    (SegmentGraph & DistanceGraph,
						     SegmentGraph & ClockwiseAngleGraph,
						     SegmentGraph & CircularityGraph, 
						     double MaxDistance,double MaxNoConvexityThreshold = 3.0);

	    SegmentGraph ProximityAffGraph (double MaxDistance,double d0p = 0.5);
	    SegmentGraph ParallelAffGraph  (double MaxDistance,double MaxAngle);
	    SegmentGraph CollinearAffGraph (double MaxDistance,double MaxAngle,double MaxParallelDistance = 1.0);

	    SegmentVector ExtractSegmentsFromTJunctions (double          MinMod                  = 20,
												      double          MaxDistBetwConvexSegments = 30,
							                          double          MaxNoConvexityThreshold   = 3.0,
							                          bool            JacobExtension_1 = true,
							                          bool            JacobExtension_2 = true,
												      bool            IncludeOriginal  = true);
	    SegmentVector TwoOrientation();

	    //map <Label,PerceptualGroup> ParallelGrouping(double MaxDistance,double MaxAngle);
*/


    };

public:
	Image();
    Image (UcharMatrix  &M):UcharMatrix(M){};
	Image (size_t Rows, size_t Cols);
    Image (DoubleMatrix &M);
    Image (FloatMatrix  &M);
    Image (BoolMatrix   &M);

    virtual ~Image();

	//io functions
	size_t SavePGM(char *FileName);
	Image& LoadPGM(char *FileName);
	Image& LoadBMP(char *FileName);
	size_t Serialize(FILE * stream);

	//Edge operators
	Image Sobel3x3	 (double Threshold, DoubleMatrix &GradientModule);
    Image Sobel5x5	 (double Threshold, DoubleMatrix &GradientModule);
	Image Prewitt3x3 (double Threshold, DoubleMatrix &GradientModule);
	Image Prewitt5x5 (double Threshold, DoubleMatrix &GradientModule);
	Image FreiChen	 (double Threshold, DoubleMatrix &GradientModule);
	Image Robert	 (double Threshold, DoubleMatrix &GradientModule);
	Image DrogS		 (double Sigma, double Threshold, DoubleMatrix &GradientModule);
	Image DrogW		 (double W    , double Threshold, DoubleMatrix &GradientModule);
	Image Lap4		 ();
    Image Lap8		 ();
	Image LogS		 (double Sigma);
	Image LogW		 (double W);
	Image SLogS	     (double Sigma);
	Image SLogW	     (double W);
	Image DogS		 (double Sigma);
	Image DogW		 (double W);
    Image CannyS	 (double Sigma,unsigned char LowH, unsigned char HighH);
	Image CannyW	 (double W    ,unsigned char LowH, unsigned char HighH);

    Image GaussS     (double Sigma);
    Image GaussW     (double W);
    Image GaussWipl  (double W);

    //Segment related functions
	SegmentVector SegmentExtraction(double MaxDistance, unsigned int MinNumOfPixels);


//Private data
private:
//	int ErrorCode; //Almacena un codigo de error generado en algun proceso
//	char StrError[256]; //Almacena una cadena que describe el error

//Private functions
private:
//	void InitializeErrors();
	bool   Hysteresis          (UcharMatrix &AuxCannyImageMag,UcharMatrix &CannyImageMag,size_t i,size_t j, unsigned char LowH);
	void   PostCanny           (Image & EdgeImage);
	double MaxDistanceFromLine (PixelVector PV, Line SL);

	//Operators and functions for edge extraction
	DoubleMatrix Gauss1dOpS   (double Sigma);
	DoubleMatrix Gauss1dOpW   (double W);
	DoubleMatrix dGauss1dOpS  (double Sigma);
	DoubleMatrix dGauss1dOpW  (double W);
	DoubleMatrix d2Gauss1dOpS (double Sigma);
	DoubleMatrix d2Gauss1dOpW (double W);
	DoubleMatrix Gauss2dOpS   (double Sigma);
	DoubleMatrix Gauss2dOpW   (double W);
    DoubleMatrix GaussOpS     (double Sigma);
	DoubleMatrix GaussOpW     (double W);
	DoubleMatrix DrogOpS      (double Sigma);
	DoubleMatrix DrogOpW      (double W);
	DoubleMatrix LogOpS       (double Sigma);
	DoubleMatrix LogOpW       (double W);
	DoubleMatrix SLogOpS      (double Sigma);
	DoubleMatrix SLogOpW      (double W);
	DoubleMatrix DogOpS       (double Sigma);
	DoubleMatrix DogOpW       (double W);
   	UcharMatrix  ZCross	      (DoubleMatrix  FilteredImage);


};

} //namespace GAC

#endif // !defined(_IMAGE_H_)
