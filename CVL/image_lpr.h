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


#if !defined(_IMAGE_LPR_H_)
#define _IMAGE_LPR_H_

#include <CVL/Globals.h>
#include <CVL/TypedMatrix.h>
#include <CVL/Polygon.h>
#include <CVL/Image.h>

#include <mil.h>							//Añadido por Juan Antonio
#include <ipl.h>							//Añadido por Juan Antonio

namespace GAC
{

class Image_lpr : public Image
{
public:
	///////////////////////////////////
    // Class Region
    //////////////////////////////////
    /*
	class Region: public Polygon
    {
    public:
	    //Construction
	    Region		():Polygon(){};
		//Region		(unsigned int dim, ...);
   		//Region &Set (unsigned int dim, ...);
		~Region();

		//Visualization
		void Show();
		
    };
	*/
	class Region
	{
	public:
		//Constructors
		Region();
		//Region(int xinit,int yinit,int xoffset,int yoffset,long area,Image image);
		Region(int xinit,int yinit,int xoffset,int yoffset,long area);

		virtual ~Region();
		
		//Accesors		
		int		&InitX()	{return dInitX;}
		int		&InitY()	{return dInitY;}
		int		&OffsetX()	{return dOffsetX;}
		int		&OffsetY()	{return dOffsetY;}
		long	&Area()		{return dArea;}
		//Image*	&SubImage()	{return dImage;}
		//Image	&SubImage() {return dImage;}
		
		
		
		//void	SetSubImage	(Image image);
		
		
		//Visualitation
		void Show();
	
	private:
		//Internal Data
		//Image *dImage;
		//Image dImage;
		int dInitX,dInitY;
		int dOffsetX,dOffsetY;
		long dArea;
	};





    ///////////////////////////////////
    // Class RegionVector
    //////////////////////////////////
    class RegionVector : public vector<Region> 
    {
    public:
	    RegionVector();
	    virtual ~RegionVector();

	    //Visualization
	    void	Show();

    };
	
	
/*
	///////////////////////////////////
    // Class Segment
    //////////////////////////////////
    class Segment : public Image::Segment  
    {
    public:
	    //Construction
		Segment():Image::Segment(){};
		Segment(unsigned int Label, double Pi,double Pj, double Qi, double Qj):Image::Segment(Label,Pi,Pj,Qi,Qj){};
		Segment(unsigned int Label, double Pi,double Pj, double Qi, double Qj,double d,double Sigma):Image::Segment(Label,Pi,Pj,Qi,Qj)
		{
			SetNormal(d,Sigma);
		};
		Segment(unsigned int Label,Point2D P, Point2D Q):Image::Segment(Label,P,Q){};

	    //Operators
//	    bool operator< (Segment &S);
//		const Segment &operator= (const Segment& S);

        // Computes the minimum distance between the nearest endpoints of segments
//		double EndPointDistance(Segment& S);
        // Computes the minimum distance between midpoint of segments
//		double MidPointDistance(Segment& S);
        //Computes the module of the overlapping between this segment and the perpendicular 
        //projection of S over this segment
//		double OverlapMod      (Segment& S);

	    //Visualization
		void Show();
//        friend ostream &operator<<(std::ostream &s, Segment &S);
	    //Serialize
//	    size_t Serialize(FILE * stream);
		//Accesors
//		double &d() {return d_d;};
//		double &sigma() {return d_sigma;};
    public:
	    //Public data
//	    unsigned int Label;			//Etiqueta identificativa del segmento
	protected:
//		double d_d,d_sigma;
    };


    ///////////////////////////////////
    // Class SegmentVector
    //////////////////////////////////
//    class PerceptualGroup; //Early definition
    class SegmentVector : public vector <Segment>
    {
    public:
        SegmentVector(){};
        virtual ~SegmentVector(){};

	    //Visualization
		void Show();
//        friend ostream &operator<<(std::ostream &s, SegmentVector &S);
    };


*/



	///////////////////////////////////
    // Class Image_lpr
    //////////////////////////////////
	//Private Data
	private:
		static MIL_ID	sys,ap,disp;					//For visualization
		static long		cnt;
		MIL_ID			img;
		//#ifdef _USE_INTEL_IPL_
		//Creamos la Imagen IPL para incrementar el rendimiento
		//	iplImage iplImg;
		//#endif
	//Public data
		//No hay datos publicos, solo los heredados

	
	//Public functions
	public:
		Image_lpr ();
		Image_lpr (UcharMatrix  &M);
		Image_lpr (size_t Rows, size_t Cols);
		Image_lpr (DoubleMatrix &M);
		Image_lpr (FloatMatrix  &M);
		Image_lpr (BoolMatrix   &M);

		virtual ~Image_lpr();

		//Visualizacion
		void Show();
		

	//Private Functions
	private:
		//Inizializacion
		void		initialize	(int,int);
		//Inundacion de region a partir de una semilla
		IntMatrix	clFlood		(Image_lpr::Pixel Seed,int RegionId);
		IntMatrix	Flood		(Image_lpr::Pixel Seed,int RegionId);
		Image_lpr	iplFlood	(Image_lpr::Pixel Seed,int RegionId);
		Region		iplFloodBis	(IplImage *src,IplImage *dst,int SeedX,int SeedY,long Max);
	
	
	
	public:
		//io_functions
		//Devuelve el valor de un pixel de la imagen
		Image_lpr::Pixel operator ()		(size_t Row,size_t Col);
		//Image_lpr		&operator=			(const Image_lpr &I);
		unsigned char	 getPixel			(size_t x,size_t y);
		void			 putPixel			(size_t x,size_t y,unsigned char p);


		//Plate Location
		Image_lpr		GlobalThreshold		(unsigned char Threshold);
		SegmentVector	houghtLinesP		(int x_ini,int x_end,int y_ini,int y_end,float p_min,float p_max,float a_min,float a_max,float p_interval, float a_interval,int dup_tol, int max_dis, int seg_tol,int umbral);
		Segment			getSegment			(int x_ini,int x_end,int y_ini,int y_end,float p,float a,int tol,int max_d,int umbral);
		IntMatrix		GetConnectivity		();
		Image_lpr		iplGetConnectivity	();
		RegionVector	iplGetImageRegions	(unsigned char graylevel,int min,int max);
		int				iplGetThreshold		();
		void			getGradient			(FloatMatrix &Angle,UcharMatrix &Module);
		void			iplGetPlate			();  
		void			iplGetPlate2		();
		void			iplGetPlate3		();
    

};







typedef union {
	unsigned char ch;
	int  in;
	long lg;
} MedianResult;
int median(void *data_vector,int length, int data_length,MedianResult *value);

} //namespace GAC

#endif //_IMAGE_LPR_H_
