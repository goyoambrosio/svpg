/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: GrayImage.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:27 $
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


#include <CVL/Image.h>

#include <math.h>
#include <ipl.h>

using namespace GAC;
using namespace std;

/********Image*************************************************************\
		
  	  
		                    Class Image::Pixel


\**************************************************************************/

Image::Pixel::~Pixel()
{

}

//Setting
Image::Pixel &Image::Pixel::Set(unsigned char Level)
{
    Pixel::Level= Level;
	return *this;
}

Image::Pixel &Image::Pixel::Set(double Row, double Col, unsigned char Level)
{
	Point2D::Set(Row,Col);
    Pixel::Level= Level;
	return *this;
}

//Operators

bool Image::Pixel::operator== (Pixel &P)
{
	return (x()==P.x())&&(y()==P.y())&&(Level==P.Level);
}
bool Image::Pixel::operator!=(Pixel &P)
{
	return (x()!=P.x() || y()!=P.y() || Level!=P.Level);
}
bool Image::Pixel::operator<  (Pixel &P)
{
	return (Level<P.Level);
}


//Visualization
void Image::Pixel::Show()
{
    printf("[%.30g,%.30g] = %i\n",x(),y(),Level);
//	cout << "["<<x()<<","<<y()<<"] = "<< (unsigned int)Level << endl;
}


ostream &GAC::operator<<(ostream &s, Image::Pixel P)
{
	s << "["<<P.x()<<","<<P.y()<<"] = "<< (unsigned int)P.Level << endl;
	return s;
}

/*
//Serialize
size_t Image::Pixel::Serialize(FILE * stream)
{
	size_t count   = 0;

	count += Point::Serialize(stream);
	count += sizeof(unsigned char)*fwrite(&Level, sizeof(unsigned char),1,stream);

	return count;
}
*/

/********Image*************************************************************\
		
  	  
		                    Class Image::PixelVector


\**************************************************************************/

Image::PixelVector::PixelVector()
{

}

Image::PixelVector::~PixelVector()
{

}

//Visualization
void Image::PixelVector::Show()
{
	PixelVector::iterator it;
	Pixel Px;
	for (it = begin(); it != end(); it++)
	{
		Px = *it;
		Px.Show();	
	}
}

/*
//Serialize
size_t Image::PixelVector::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t PVsize = 0;

	PVsize = size();
	count += sizeof(size_t)*fwrite(&PVsize, sizeof(size_t),1,stream);

	PixelVector::iterator it;
	for (it = begin(); it != end(); it++)
	{
		count += (*it).Serialize(stream);	
	}

	return count;
}
*/

/********Image*************************************************************\
		
  	  
		                    Class Image::Segment


\**************************************************************************/

/**Segment*****************************\
		       operator< 
\**************************************/
bool Image::Segment::operator< (Segment &S){
    return Label < S.Label;
}

/**Segment*****************************\
		   EndPointDistance
\**************************************/
// Computes the minimum distance between the nearest endpoints of segments

double Image::Segment::EndPointDistance(Segment& S)
{
	vector<double> DistVector;
	vector<double>::iterator Dit;
	double Distance;

	DistVector.clear();
	DistVector.push_back(p().Distance(S.p()));
	DistVector.push_back(p().Distance(S.q()));
	DistVector.push_back(q().Distance(S.p()));
	DistVector.push_back(q().Distance(S.q()));
	Dit = min_element(DistVector.begin(), DistVector.end()) ;
	Distance = *Dit;
	return Distance;
}

/**Segment*****************************\
		   MidPointDistance
\**************************************/
// Computes the minimum distance between midpoint of segments
double Image::Segment::MidPointDistance(Segment& S)
{
	double Distance;

	Distance = MidPoint().Distance(S.MidPoint());
	return Distance;
}

/**ImgSegment**************************\
		   OverlapMod
\**************************************/
//Computes the module of the overlapping between this segment and the perpendicular 
//projection of S over this segment
double Image::Segment::OverlapMod(Segment& S)
{
	Segment Saux,SOverlap;
	Point2D CutA;
	Point2D CutB;

	CutA = Intersection(S.PerpLine(S.p()));
	CutB = Intersection(S.PerpLine(S.q()));

    if (Overlap(Segment(0,CutA,CutB),SOverlap))
		return SOverlap.Mod();
	else 
		return 0.0;
}

/**Segment*****************************\
		       Show
\**************************************/
void Image::Segment::Show()
{
    printf("%i:(%.30g,%.30g)->(%.30g,%.30g)\n",Label,p().x(),p().y(),q().x(),q().y());
//	cout << Label << ":" << p() << "->" << q() << endl;
}

/**Segment*****************************\
		       operator<<
\**************************************/
/*
ostream &GAC::operator<<(ostream &s, Image::Segment &S)
{
	cout << S.Label << ":" << S.p() << "->" << S.q() << endl;
	return s;
}
*/
/**Segment*****************************\
		       Serialize
\**************************************/
/*
size_t Image::Segment::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t PVsize = 0;

	count += sizeof(unsigned int)*fwrite(&Label, sizeof(unsigned int),1,stream);
	count += Vector2D::Serialize(stream);
	count += Line::Serialize(stream);
	return count;
}
*/

/********Image*************************************************************\
		
  	  
		                    Class Image::SegmentGraph


\**************************************************************************/

Image::SegmentGraph::SegmentGraph(){}
Image::SegmentGraph::~SegmentGraph(){};

/**SegmentGraph************************\
		    SetAdjacencyMatrix
\**************************************/
Image::SegmentGraph & Image::SegmentGraph::SetAdjacencyMatrix(DoubleMatrix M)
{
	size_t i,j;
	size_t NumRows,NumCols;

//	SetErrorCode(0);

	if (!M.IsSquare()){
//		SetErrorCode(2000);
		return *this;
	}

	del_all_nodes();
	del_all_edges();
	leda_node u,v;
	leda_edge e;
	map<size_t,leda_node> MNode;

	NumRows = M.Depth();
	NumCols = M.Width();

	for (i=0;i<NumRows;i++){
		u = new_node();
	}

	i = 0;
	forall_nodes(u,*this) MNode[i++] = u;

	for (i=0;i<NumRows;i++)
		for (j=i;j<NumCols;j++)
			if (M[i][j]) {
                u = MNode[i];
				v = MNode[j];
				e = new_edge(u,v);
				assign(e,M[i][j]);
			}

	return *this;
}

/**SegmentGraph****************************\
		    GetAdjacencyMatrix
\******************************************/
DoubleMatrix Image::SegmentGraph::GetAdjacencyMatrix()
{
	size_t i,j;
	size_t NumRows,NumCols;
	leda_node u,v;
	leda_edge e;
	map<leda_node,size_t> MNode;

	NumRows = NumCols = number_of_nodes();
	DoubleMatrix AffMatrix(NumRows,NumCols);
	AffMatrix.Init();

	i = 0;
	forall_nodes(u,*this) MNode[u] = i++;

	forall_edges(e,*this) {
		u = source(e);
		v = target(e);
		AffMatrix[MNode[u]][MNode[v]] = inf(e);
		AffMatrix[MNode[v]][MNode[u]] = inf(e);
	}

	return AffMatrix;
}

/**SegmentGraph****************************\
		            Edit
\******************************************/
Image::SegmentGraph & Image::SegmentGraph::Edit(int AnimationSteps)
{
	GraphWin gw(*this,650,500,"Segment Graph. (c) Goyo A.C. 2000. Revision 4");

//	gw.update_graph();

	gw.set_node_label_font(roman_font,4);
	gw.set_node_width(8);
    gw.set_node_height(8);
	gw.set_edge_width(1);
    gw.set_zoom_objects(true);
	gw.set_animation_steps(AnimationSteps);

	gw.message("Department of System Engineering and Automation. University of Malaga");
	gw.set_node_label_type(index_label);	
//	gw.set_edge_direction(undirected_edge);

	gw.display();
	gw.place_into_win();
	gw.redraw();
	gw.edit();

	return *this;
}


/********Image*************************************************************\
		
  	  
		                    Class Image::SegmentVector


\**************************************************************************/

Image::SegmentVector::SegmentVector(){}
Image::SegmentVector::~SegmentVector(){};

/**SegmentVector***********************\
		       operator<<
\**************************************/
/*
ostream &GAC::operator<<(ostream &s, Image::SegmentVector &SV)
{
  
    Image::SegmentVector::const_iterator it;
    Image::Segment S;
	for (it = SV.begin(); it != SV.end(); it++)
	{
		S = *it;
		s << S;	
	}
	return s;
}
*/

/**SegmentVector********************\
		        Show
\***********************************/
void Image::SegmentVector::Show()
{
	SegmentVector::iterator it;
	Segment S;
	for (it = begin(); it != end(); it++)
	{
		S = *it;
		S.Show();	
	}
}

/********Image*************************************************************\
		
  	  
		                    Class Image


\**************************************************************************/

/**Image*******************************\
		       Image
\**************************************/
Image::Image():UcharMatrix() 
{
//	InitializeErrors();
}

Image::Image(size_t Rows, size_t Cols):UcharMatrix(Rows,Cols)
{
//	InitializeErrors();
}

//Type casting scales M between 0 and 255 (I1(i,j)=M(i,j)/M.Max()*255
Image::Image (DoubleMatrix &M)
{	size_t i,j;
    double Max;
    Destroy();
	Initialize(M.Depth(),M.Width());
    Max = M.Max();
    for (i=0;i<M.Depth();i++){
        for (j=0;j<M.Width();j++){
		    pM[i*NumCols + j]=(unsigned char)(M[i][j]/Max*255);
        }
	}                                        
}

//Type casting scales M between 0 and 255 (I1(i,j)=M(i,j)/M.Max()*255
Image::Image (FloatMatrix &M)
{	size_t i,j;
    float Max;
    Destroy();
	Initialize(M.Depth(),M.Width());
    Max = M.Max();
    for (i=0;i<M.Depth();i++){
        for (j=0;j<M.Width();j++){
		    pM[i*NumCols + j]=(unsigned char)(M[i][j]/Max*255);
        }
	}                                        
}

//Type casting True 1=255 False 0=0
Image::Image (BoolMatrix &M)
{	size_t i,j;
    float Max;
    Destroy();
	Initialize(M.Depth(),M.Width());
    Max = M.Max();
    for (i=0;i<M.Depth();i++){
        for (j=0;j<M.Width();j++){
		    pM[i*NumCols + j]=(unsigned char)(M[i][j]*255);
        }
	}                                        
}

Image::~Image()
{

}


/**Image***************************\
		    InitializeErrors
\**************************************/
/*
void Image::InitializeErrors()
{
	insert(Error::value_type(0,"No error"));
	insert(Error::value_type(1000,"I1000: Not a valid .BMP file"));
	insert(Error::value_type(1001,"I1001: This program currently support uncompressed .BMP files"));
	insert(Error::value_type(1002,"I1002: This program supports only images with at most 256 colors (8 bits per pixel)"));
	insert(Error::value_type(1003,"I1003: The file does not exist or is corrupted"));
	insert(Error::value_type(1004,"I1004: Not a valid .PGM file"));
}
*/

/**Image***************************\
		       Serialize
\**************************************/
/*
size_t Image::Serialize(FILE * stream)
{
	size_t count   = 0;

	count += Serialize(stream);

	return count;
}
*/


/**Image***************************\
		       SavePGM
\**************************************/
size_t Image::SavePGM(char *FileName)
{
	size_t i,j;
	FILE *stream;
	size_t NumWritten = 0;
	size_t NumRows,NumCols;
	stream = fopen(FileName,"wb");
	UcharMatrix Maux;

	Maux = Trans();

	NumRows = Maux.Depth();
	NumCols = Maux.Width();

	NumWritten += fprintf(stream,"P5\n");
	NumWritten += fprintf(stream,"# Gregorio Ambrosio Cestero\n");
	NumWritten += fprintf(stream,"# University of Malaga\n");
	NumWritten += fprintf(stream,"# Department of System Engineering and Automation\n");
	NumWritten += fprintf(stream,"# Email: goyo@computer.org\n");
	
	NumWritten += fprintf(stream,"%d %d\n",NumRows,NumCols);
	NumWritten += fprintf(stream,"%d\n",255);

	for (j=0;j<NumCols;j++)
		for (i=0;i<NumRows;i++)
		{
			NumWritten += fwrite(&Maux[i][j], sizeof(unsigned char),1,stream);
			//cout << "(" << i << "," << j << ") = " << M[i][j] << endl;
		}
		
	fclose (stream);
	return NumWritten;

}

/**Image***************************\
		       LoadPGM
\**************************************/
Image &Image::LoadPGM(char *FileName)
{
	size_t i,j;
	FILE *stream;
	size_t NumRead = 0;
	size_t NumRows,NumCols;
	UcharMatrix Maux;

	char pfType[256];
	char Aux[256];
	char *token;
	char seps[]   = " ";//" ,\t\n";
	char *stopstring;

//	SetErrorCode(0);

	if ((stream = fopen(FileName,"rb")) == NULL){
//		SetErrorCode(1003);
		return *this;
	}

	if( (fgets( pfType, 100, stream ) == NULL)){
//		SetErrorCode(1004);
		fclose(stream);
		return *this;
	}
	else
		strncpy(Aux, pfType, 2 );
		if (strncmp(pfType,"P5",2)){
//			SetErrorCode(1004);
			fclose(stream);
			return *this;
	}

	Aux[0]='#'; 
	while (Aux[0]=='#'){
		fgets( Aux, 256, stream);
	}

	token = strtok(Aux, seps );
	NumRows = strtol(token,&stopstring, 10);
	//Get next token
	token = strtok( NULL, seps );
	NumCols = strtol(token,&stopstring, 10);
	//This strip the number of grays information. Since we know they are 255
	//a priori, there isn't need to capture this information
	fgets(Aux, 256, stream);
	
	//Read the image

	Maux.Resize(NumRows,NumCols);
	Resize(NumCols,NumRows);

	for (j=0;j<NumCols;j++)
		for (i=0;i<NumRows;i++)
			NumRead += fread(&Maux[i][j], sizeof(unsigned char),1,stream);

	for (i=0;i<NumRows;i++)
		for (j=0;j<NumCols;j++)
			pM[j*NumRows + i]=Maux[i][j];

	fclose (stream);
	return *this;
}

/**Image*******************************\
		       LoadBMP
\**************************************/
Image &Image::LoadBMP(char *FileName)
{
	int i,j;
	FILE *stream;
	size_t NumRead = 0;
	size_t NumRows,NumCols;

	//BMP data
	char  bfType[10];
	short status;
	int   bfSize;
	long dummy;
	long bfOffs;
	long biSize;
	long biWidth;
	long biHeight;
	unsigned short biPlanes;
	unsigned short biBitCnt;
	unsigned int nCol;
	long biCompr;
	long biSizeIm;
	long biXPelsPerMeter;
	long biYPelsPerMeter;
	long biClrUsed;
	long biClrImportant;
	long MapLength;
	long ndata;
	long Width;

//	SetErrorCode(0);

	if ((stream = fopen(FileName,"rb")) == NULL){
//		SetErrorCode(1003);
		return *this;
	}

	NumRead += fread(bfType,sizeof(char),2,stream);

	if (strncmp(bfType,"BM",2)){
//		SetErrorCode(1000);
		fclose(stream);
		return *this;
	}

	//Read file length (bytes)
	status = fseek(stream,0,SEEK_END);
	bfSize = ftell(stream);
	status = fseek(stream,6,SEEK_SET);
	NumRead = 6;

	//Read bytes reserved for later extensions
	NumRead += fread(&dummy,sizeof(long),1,stream);

	//Read offset from beginning fo file to first data byte
	NumRead += fread(&bfOffs,sizeof(long),1,stream);

	//BMP INFO-BLOCK
	
	//Bitmap information header

	//Read length of bitmap information header
	NumRead += fread(&biSize,sizeof(long),1,stream);
	//Read width of bitmap
	NumRead += fread(&biWidth,sizeof(long),1,stream);
	//Read height of bitmap
	NumRead += fread(&biHeight,sizeof(long),1,stream);
	//Read number of color planes
	NumRead += fread(&biPlanes,sizeof(unsigned short),1,stream);
	//Read number of bits per pixel
	NumRead += fread(&biBitCnt,sizeof(unsigned short),1,stream);
	nCol = pow(2.0,double(biBitCnt));
	//Read type of data compression
	NumRead += fread(&biCompr,sizeof(long),1,stream);
	if (biCompr){
//		SetErrorCode(1001);
		fclose(stream);
		return *this;
	}
	//Read size of compressed image
	NumRead += fread(&biSizeIm,sizeof(long),1,stream);
	//Read horizontal resolution (pixels/meter)
	NumRead += fread(&biXPelsPerMeter,sizeof(long),1,stream);
	//Read vertical resolution (pixels/meter)
	NumRead += fread(&biYPelsPerMeter,sizeof(long),1,stream);
	//Read number of used colors
	NumRead += fread(&biClrUsed,sizeof(long),1,stream);
	//Read number of importants colors
	NumRead += fread(&biClrImportant,sizeof(long),1,stream);

	//Colormap
	MapLength = (bfOffs-54)/4;
	status = fseek(stream,MapLength*4,SEEK_CUR);
	NumRead += MapLength*4;

	//Bitmap data
	ndata = bfSize-bfOffs;
	Width = (ndata*8/biBitCnt)/biHeight;

	NumRows = biHeight;
	NumCols = Width;

//printf("biHeight:%i,Width:%i\n",biHeight,Width);


//	UcharMatrix M;
//	M.Resize(NumCols,NumRows);
	Resize(NumRows,NumCols);

	if (biBitCnt!=8){
//		SetErrorCode(1002);
		fclose(stream);
		return *this;
	}

	for (i=NumRows-1;i>=0;i--)
		for (j=0;j<NumCols;j++)
			NumRead += fread(&pM[i*NumCols + j], sizeof(unsigned char),1,stream);

	fclose (stream);

	return *this;
}


/**Image****************************\
              GetpM
\***********************************/
/*
char* Image::GetpM(){
    return (char*)pM;
}
*/
/**Image****************************\
              GetpRow
\***********************************/
/*
char** Image::GetpRow(){
    return (char**)pRow;
}
*/

/***********************************\
  Functions for edge detection
\***********************************/

Image Image::Sobel3x3(double Threshold, DoubleMatrix &GradientModule)
{
	//Construyo el operador 3x3 de Sobel para las filas y para las columnas
    double K = 2;
	DoubleMatrix Hr(3,3),Hc(3,3);
	Hr[0][0]=1;Hr[0][1]=0;Hr[0][2]=-1;
	Hr[1][0]=K;Hr[1][1]=0;Hr[1][2]=-K;
	Hr[2][0]=1;Hr[2][1]=0;Hr[2][2]=-1;

	Hr *= (double)1/(2+K);
	Hc = Hr.Trans();

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de Fila (Gr) y el Gradiente de Columna (Gc)
	DoubleMatrix Gr,Gc,I;
    Image SobelImage;

    I=*this;

	Gr = I.Conv(Hr,1);
    Gc = I.Conv(Hc,1);

    // Hago un 'and' de los bordes horizontales y verticales
    // Calculo la Imagen Gradiente formada por el módulo del gradiente de cada píxel
    // sqrt(Gr^2+Gc^2) que se aproxima a |Gr|+|Gc|
    GradientModule = Gr.Abs() + Gc.Abs();

    if (Threshold > Epsilon){
        SobelImage = (UcharMatrix)((GradientModule>Threshold)*255.0);
    }
    else {
        SobelImage = GradientModule;  //Type casting DoubleMatrix to Image (scaling between 0 and 2559
    }

	return SobelImage;
}

Image Image::Sobel5x5(double Threshold, DoubleMatrix &GradientModule)
{
    //Construyo el operador 5x5 de Sobel para las filas y para las columnas
	DoubleMatrix Hr(5,5),Hc(5,5);
	Hr[0][0]=1;Hr[0][1]=2;Hr[0][2]=0;Hr[0][3]=-2;Hr[0][4]=-1;
	Hr[1][0]=2;Hr[1][1]=3;Hr[1][2]=0;Hr[1][3]=-3;Hr[1][4]=-2;
	Hr[2][0]=3;Hr[2][1]=5;Hr[2][2]=0;Hr[2][3]=-5;Hr[2][4]=-3;
	Hr[3][0]=2;Hr[3][1]=3;Hr[3][2]=0;Hr[3][3]=-3;Hr[3][4]=-2;
	Hr[4][0]=1;Hr[4][1]=2;Hr[4][2]=0;Hr[4][3]=-2;Hr[4][4]=-1;

	Hr *= (double)1/18;
	Hc = Hr.Trans();

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de Fila (Gr) y el Gradiente de Columna (Gc)
	DoubleMatrix Gr,Gc,I;
    Image SobelImage;

	I=*this;

	Gr = I.Conv(Hr,1);
	Gc = I.Conv(Hc,1);

    // Hago un 'and' de los bordes horizontales y verticales
    // Calculo la Imagen Gradiente formada por el módulo del gradiente de cada píxel
    // sqrt(Gr^2+Gc^2) que se aproxima a |Gr|+|Gc|
    GradientModule = Gr.Abs() + Gc.Abs();

    if (Threshold > Epsilon){
        SobelImage = (UcharMatrix)((GradientModule>Threshold)*255.0);
    }
    else {
        SobelImage = GradientModule;  //Type casting DoubleMatrix to Image (scaling between 0 and 2559
    }

	return SobelImage;

	return *this;
}


Image Image::Prewitt3x3(double Threshold, DoubleMatrix &GradientModule)
{
	//Construyo el operador 3x3 de Prewitt para las filas y para las columnas
    double K = 1;
	DoubleMatrix Hr(3,3),Hc(3,3);
	Hr[0][0]=1;Hr[0][1]=0;Hr[0][2]=-1;
	Hr[1][0]=K;Hr[1][1]=0;Hr[1][2]=-K;
	Hr[2][0]=1;Hr[2][1]=0;Hr[2][2]=-1;

	Hr *= (double)1/(2+K);
	Hc = Hr.Trans();

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de Fila (Gr) y el Gradiente de Columna (Gc)
	DoubleMatrix Gr,Gc,I;
    Image PrewittImage;

	I= *this;

	Gr = I.Conv(Hr,1);
	Gc = I.Conv(Hc,1);

    // Hago un 'and' de los bordes horizontales y verticales
    // Calculo la Imagen Gradiente formada por el módulo del gradiente de cada píxel
    // sqrt(Gr^2+Gc^2) que se aproxima a |Gr|+|Gc|
    GradientModule = Gr.Abs() + Gc.Abs();

    if (Threshold > Epsilon){
        PrewittImage = (UcharMatrix)((GradientModule>Threshold)*255.0);
    }
    else {
        PrewittImage = GradientModule;  //Type casting DoubleMatrix to Image (scaling between 0 and 2559
    }

	return PrewittImage;
}

Image Image::Prewitt5x5(double Threshold, DoubleMatrix &GradientModule)
{
    //Construyo el operador 5x5 de Prewitt para las filas y para las columnas
	DoubleMatrix Hr(5,5),Hc(5,5);
	Hr[0][0]=1;Hr[0][1]=1;Hr[0][2]=0;Hr[0][3]=-1;Hr[0][4]=-1;
	Hr[1][0]=2;Hr[1][1]=2;Hr[1][2]=0;Hr[1][3]=-2;Hr[1][4]=-2;
	Hr[2][0]=3;Hr[2][1]=3;Hr[2][2]=0;Hr[2][3]=-3;Hr[2][4]=-3;
	Hr[3][0]=2;Hr[3][1]=2;Hr[3][2]=0;Hr[3][3]=-2;Hr[3][4]=-2;
	Hr[4][0]=1;Hr[4][1]=1;Hr[4][2]=0;Hr[4][3]=-1;Hr[4][4]=-1;

	Hr *= (double)1/18;
	Hc = Hr.Trans();

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de Fila (Gr) y el Gradiente de Columna (Gc)
	DoubleMatrix Gr,Gc,I;
    Image PrewittImage;

	I= *this;

	Gr = I.Conv(Hr,1);
	Gc = I.Conv(Hc,1);

    // Hago un 'and' de los bordes horizontales y verticales
    // Calculo la Imagen Gradiente formada por el módulo del gradiente de cada píxel
    // sqrt(Gr^2+Gc^2) que se aproxima a |Gr|+|Gc|
    GradientModule = Gr.Abs() + Gc.Abs();

    if (Threshold > Epsilon){
        PrewittImage = (UcharMatrix)((GradientModule>Threshold)*255.0);
    }
    else {
        PrewittImage = GradientModule;  //Type casting DoubleMatrix to Image (scaling between 0 and 2559
    }

	return PrewittImage;
}

Image Image::FreiChen(double Threshold, DoubleMatrix &GradientModule)
{
	//Construyo el operador 3x3 de Frei-Chen para las filas y para las columnas
    double K = sqrt(2.0);
	DoubleMatrix Hr(3,3),Hc(3,3);
	Hr[0][0]=1;Hr[0][1]=0;Hr[0][2]=-1;
	Hr[1][0]=K;Hr[1][1]=0;Hr[1][2]=-K;
	Hr[2][0]=1;Hr[2][1]=0;Hr[2][2]=-1;

	Hr *= (double)1/(2+K);
	Hc = Hr.Trans();

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de Fila (Gr) y el Gradiente de Columna (Gc)
	DoubleMatrix Gr,Gc,I;
    Image FreiChenImage;

	I= *this;

	Gr = I.Conv(Hr,1);
	Gc = I.Conv(Hc,1);

    // Hago un 'and' de los bordes horizontales y verticales
    // Calculo la Imagen Gradiente formada por el módulo del gradiente de cada píxel
    // sqrt(Gr^2+Gc^2) que se aproxima a |Gr|+|Gc|
    GradientModule = Gr.Abs() + Gc.Abs();

    if (Threshold > Epsilon){
        FreiChenImage = (UcharMatrix)((GradientModule>Threshold)*255.0);
    }
    else {
        FreiChenImage = GradientModule;  //Type casting DoubleMatrix to Image (scaling between 0 and 2559
    }

	return FreiChenImage;
}

Image Image::Robert(double Threshold, DoubleMatrix &GradientModule)
{
	//Construyo el operador 3x3 de Robert para las filas y para las columnas
	DoubleMatrix Hr(3,3),Hc(3,3);
	Hr[0][0]= 0;Hr[0][1]= 0;Hr[0][2]= 0;
	Hr[1][0]= 0;Hr[1][1]= 0;Hr[1][2]= 1;
	Hr[2][0]= 0;Hr[2][1]=-1;Hr[2][2]= 0;

	Hc[0][0]=-1;Hc[0][1]= 0;Hc[0][2]= 0;
	Hc[1][0]= 0;Hc[1][1]= 1;Hc[1][2]= 0;
	Hc[2][0]= 0;Hc[2][1]= 0;Hc[2][2]= 0;

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de Fila (Gr) y el Gradiente de Columna (Gc)
	DoubleMatrix Gr,Gc,I;
    Image RobertImage;

	I= *this;

	Gr = I.Conv(Hr,1);
	Gc = I.Conv(Hc,1);

    // Hago un 'and' de los bordes horizontales y verticales
    // Calculo la Imagen Gradiente formada por el módulo del gradiente de cada píxel
    // sqrt(Gr^2+Gc^2) que se aproxima a |Gr|+|Gc|
    GradientModule = Gr.Abs() + Gc.Abs();

    if (Threshold > Epsilon){
        RobertImage = (UcharMatrix)((GradientModule>Threshold)*255.0);
    }
    else {
        RobertImage = GradientModule;  //Type casting DoubleMatrix to Image (scaling between 0 and 2559
    }

	return RobertImage;
}

Image Image::DrogS(double Sigma,double Threshold, DoubleMatrix &GradientModule)
{
	//Construyo el operador Drog para las filas y para las columnas
	DoubleMatrix Hr,Hc;
	Hr = DrogOpS(Sigma);
	Hc = Hr.Trans();

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de Fila (Gr) y el Gradiente de Columna (Gc)
	DoubleMatrix Gr,Gc,I;
    Image DrogSImage;

	I= *this;

	Gr = I.Conv(Hr,1);
	Gc = I.Conv(Hc,1);

    // Hago un 'and' de los bordes horizontales y verticales
    // Calculo la Imagen Gradiente formada por el módulo del gradiente de cada píxel
    // sqrt(Gr^2+Gc^2) que se aproxima a |Gr|+|Gc|
    GradientModule = Gr.Abs() + Gc.Abs();

    if (Threshold > Epsilon){
        DrogSImage = (UcharMatrix)((GradientModule>Threshold)*255.0);
    }
    else {
        DrogSImage = GradientModule;  //Type casting DoubleMatrix to Image (scaling between 0 and 2559
    }

	return DrogSImage;
}

Image Image::DrogW(double W,double Threshold, DoubleMatrix &GradientModule)
{
	//Construyo el operador Drog para las filas y para las columnas
	DoubleMatrix Hr,Hc;
	Hr = DrogOpW(W);
	Hc = Hr.Trans();

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de Fila (Gr) y el Gradiente de Columna (Gc)
	DoubleMatrix Gr,Gc,I;
    Image DrogWImage;

	I= *this;

	Gr = I.Conv(Hr,1);
	Gc = I.Conv(Hc,1);

    // Hago un 'and' de los bordes horizontales y verticales
    // Calculo la Imagen Gradiente formada por el módulo del gradiente de cada píxel
    // sqrt(Gr^2+Gc^2) que se aproxima a |Gr|+|Gc|
    GradientModule = Gr.Abs() + Gc.Abs();

    if (Threshold > Epsilon){
        DrogWImage = (UcharMatrix)((GradientModule>Threshold)*255.0);
    }
    else {
        DrogWImage = GradientModule;  //Type casting DoubleMatrix to Image (scaling between 0 and 2559
    }

	return DrogWImage;
}

Image Image::Lap4()
{
	// Función para la detección de bordes.
	// Basada en el operador Laplaciana de 4-vecinos

    // Construyo el operador laplaciana.
	DoubleMatrix H(3,3);
	H[0][0]= 0;H[0][1]=-1;H[0][2]= 0;
	H[1][0]=-1;H[1][1]= 4;H[1][2]=-1;
	H[2][0]= 0;H[2][1]=-1;H[2][2]= 0;
	H *= 1.0/4.0;

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de la matriz (G)
	DoubleMatrix G,I;
    Image Lap4Image;

	I= *this;
	G = I.Conv(H,1);

	Lap4Image = ZCross(G);
	return Lap4Image;
}

Image Image::Lap8()
{
	// Función para la detección de bordes.
	// Basada en el operador Laplaciana de 8-vecinos

    // Construyo el operador laplaciana.
	DoubleMatrix H(3,3);
	H[0][0]=-1;H[0][1]=-1;H[0][2]=-1;
	H[1][0]=-1;H[1][1]= 8;H[1][2]=-1;
	H[2][0]=-1;H[2][1]=-1;H[2][2]=-1;
	H *= 1.0/8.0;

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de la matriz (G)
	DoubleMatrix G,I;
    Image Lap8Image;

	I= *this;
	G = I.Conv(H,1);

	Lap8Image = ZCross(G);
	return Lap8Image;
}


Image Image::LogS(double Sigma)
{
	//Construyo el operador Log para las filas y para las columnas
	DoubleMatrix H;
	H = LogOpS(Sigma);

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de la matriz (G)
	DoubleMatrix G,I;
    Image LogSImage;

	I= *this;
	G = I.Conv(H,1);

	LogSImage = ZCross(G);
	return LogSImage;
}

Image Image::LogW(double W)
{
	//Construyo el operador Log para las filas y para las columnas
	DoubleMatrix H;
	H = LogOpW(W);

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de la matriz (G)
	DoubleMatrix G,I;
    Image LogWImage;

	I= *this;
	G = I.Conv(H,1);

	LogWImage = ZCross(G);
	return LogWImage;
}

Image Image::SLogS(double Sigma)
{
	//Construyo el operador Log para las filas y para las columnas
	DoubleMatrix H;
	H = SLogOpS(Sigma);

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de la matriz (G)
	DoubleMatrix G,I;
    Image SLogSImage;

	I= *this;
	G = I.Conv(H,1);

	SLogSImage = ZCross(G);
	return SLogSImage;
}

Image Image::SLogW(double W)
{
	//Construyo el operador Log para las filas y para las columnas
	DoubleMatrix H;
	H = SLogOpW(W);

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de la matriz (G)
	DoubleMatrix G,I;
    Image SLogWImage;

	I= *this;
	G = I.Conv(H,1);

	SLogWImage = ZCross(G);
	return SLogWImage;
}

Image Image::DogS(double Sigma)
{
	//Construyo el operador Log para las filas y para las columnas
	DoubleMatrix OP;
	OP = DogOpS(Sigma);

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de la matriz (G)
	DoubleMatrix G,I;
    Image DogSImage;

	I= *this;
	G = I.Conv(OP,1);

	DogSImage = ZCross(G);
	return DogSImage;
}

Image Image::DogW(double W)
{
	//Construyo el operador Log para las filas y para las columnas
	DoubleMatrix OP;
	OP = DogOpW(W);

	// Aplico el operador mediante la convolución
    // Obteniendo el Gradiente de la matriz (G)
	DoubleMatrix G,I;
    Image DogWImage;

	I= *this;
	G = I.Conv(OP,1);

	DogWImage = ZCross(G);
	return DogWImage;
}


/**Image*******************************\
		       CannyW
\**************************************/
Image Image::CannyW(double W,unsigned char LowH, unsigned char HighH)
{
	double c = W/3.0;			// El tamaño del operador debe ser el triple
								// de la anchura del lóbulo central (W>=3*c)
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.
	double		Sigma	= c/(2.0*sqrt(2.0));// Cálculo de la anchura del lóbulo central de la Gaussiana

	return CannyS(Sigma,LowH,HighH);
}

/**Image*******************************\
		       CannyS
\**************************************/
Image Image::CannyS(double Sigma,unsigned char LowH, unsigned char HighH)
{
	DoubleMatrix AuxCannyImage;
	Image   CannyImageMag;
	UcharMatrix CannyImageOrnt;
	UcharMatrix AuxCannyImageMag;
	UcharMatrix AuxCannyImageOrnt;

	DoubleMatrix G;
	DoubleMatrix Retina_Gx,Retina_Gy;

	DoubleMatrix dG;
	DoubleMatrix Retina_dGx,Retina_dGy;

	double g0,gc,gn,gs,gw,ge,gnw,gne,gsw,gse;
	double ux,uy;
	int	   t;
	unsigned char Value;
	double t1,t2;
	register i,j,k;

	//Convoluciones x e y con las gaussianas
	G=Gauss1dOpS(Sigma);
	size_t W = G.Width(); //Filter width

	AuxCannyImage = *this;
	AuxCannyImage = AuxCannyImage.SetAround(W,W,0);

	size_t AuxNumRows = AuxCannyImage.Depth();
	size_t AuxNumCols = AuxCannyImage.Width();

	Retina_Gx.Resize(AuxNumRows,AuxNumCols);
	Retina_Gy.Resize(AuxNumRows,AuxNumCols);

	for (i=W;i<AuxNumRows-W;i++){
		for(j=W;j<AuxNumCols-W;j++){
			t1=AuxCannyImage[i][j]*G[0][0];
			t2=t1;
			for(k=1;k<W;k++){
				  t1+=G[0][k]*(AuxCannyImage[i][j-k]+AuxCannyImage[i][j+k]);
				  t2+=G[0][k]*(AuxCannyImage[i-k][j]+AuxCannyImage[i+k][j]);
			}
			Retina_Gx[i][j]=t1;
			Retina_Gy[i][j]=t2;
		}
	}

	//Convoluciones x e y con las derivadas de las gaussianas
	dG=dGauss1dOpS(Sigma);

	Retina_dGx.Resize(AuxNumRows,AuxNumCols);
	Retina_dGy.Resize(AuxNumRows,AuxNumCols);

	for (i=W;i<AuxNumRows-W;i++){
		for(j=W;j<AuxNumCols-W;j++){
			t1=0;
			t2=t1;
			for(k=1;k<W;k++){
				  t1+=dG[0][k]*(Retina_Gx[i][j-k]-Retina_Gx[i][j+k]);
				  t2+=dG[0][k]*(Retina_Gy[i-k][j]-Retina_Gy[i+k][j]);
			}
			Retina_dGx[i][j]=t1;
			Retina_dGy[i][j]=t2;
		}
	}

	//Supresion de no-maximos (4 casos para la orientacion de
	//las lineas de maxima pendiente)
	AuxCannyImageMag.Resize(AuxNumRows,AuxNumCols);
	AuxCannyImageOrnt.Resize(AuxNumRows,AuxNumCols);

	for (i=W;i<AuxNumRows-W;i++)
	{
	  for (j=W;j<AuxNumCols-W;j++)
		{
			ux=Retina_dGx[i][j];
			uy=Retina_dGy[i][j];
			gc=MyHypot(ux,uy);
			// escalamos gc para meterlo en el rango de 0..255
			t=(int) (gc*20.0);
			Value=(t<256 ? t : 255);
			gn	= MyHypot(Retina_dGx[i-1][j]  ,Retina_dGy[i-1][j]  );	//n
			gs	= MyHypot(Retina_dGx[i+1][j]  ,Retina_dGy[i+1][j]  );	//s
			gw	= MyHypot(Retina_dGx[i]  [j-1],Retina_dGy[i]  [j-1]);	//w
			ge	= MyHypot(Retina_dGx[i]  [j+1],Retina_dGy[i]  [j+1]);	//e
			gne	= MyHypot(Retina_dGx[i-1][j+1],Retina_dGy[i-1][j+1]);	//ne
			gse	= MyHypot(Retina_dGx[i+1][j+1],Retina_dGy[i+1][j+1]);	//se
			gsw	= MyHypot(Retina_dGx[i+1][j-1],Retina_dGy[i+1][j-1]);	//sw
			gnw	= MyHypot(Retina_dGx[i-1][j-1],Retina_dGy[i-1][j-1]);	//nw
		
			if (ux*uy>0)
				{
			  if(fabs(ux)<fabs(uy))
					{
			  if((g0=fabs(uy*gc))
						 < fabs(ux*gse+(uy-ux)*gs) ||
						 g0<=fabs(ux*gnw+(uy-ux)*gn))
						continue;
					}
			  else
					{
			  if((g0=fabs(ux*gc))
						 < fabs(uy*gse+(ux-uy)*ge) ||
						 g0<=fabs(uy*gnw+(ux-uy)*gw))
						continue;
					}
				}
			else
				{
			  if(fabs(ux)<fabs(uy))
					{
			  if((g0=fabs(uy*gc))
						 < fabs(ux*gne-(uy+ux)*gn) ||
						 g0<=fabs(ux*gsw-(uy+ux)*gs))
				continue;
					}
			  else
					{
			  if((g0=fabs(ux*gc))
						 < fabs(uy*gne-(ux+uy)*ge) ||
						 g0<=fabs(uy*gsw-(ux+uy)*gw))
				continue;
					}
				}
			
			AuxCannyImageMag[i][j] = Value;
			/* pi*40 ~= 128 - direction es un signed byte */
			AuxCannyImageOrnt[i][j]=(unsigned char) atan2(uy, ux)*4; //El cuatro es un factor de escalado de la orientación
		}
	}

	//Extraigo la parte central de la imagen quitando una corona de
	//W+1 pixels alrededor para eliminar un marco que se forma en la 
	//imagen de bordes que despues se interpretarian como segmentos
	AuxCannyImageMag  = AuxCannyImageMag.GetBlock(W+1,W+1,AuxNumRows-(2*(W+1)),AuxNumCols-(2*(W+1)));
	AuxCannyImageOrnt = AuxCannyImageOrnt.GetBlock(W+1,W+1,AuxNumRows-(2*(W+1)),AuxNumCols-(2*(W+1)));
	AuxCannyImageMag  = AuxCannyImageMag.SetAround(1,1,0);
	AuxCannyImageOrnt = AuxCannyImageOrnt.SetAround(1,1,0);
	CannyImageMag.Resize(NumRows,NumCols);
	CannyImageOrnt.Resize(NumRows,NumCols);
	CannyImageMag.Init();

// Buscamos ejes en la retina de magnitud empezando en los puntos que 
// excedan el valor de histeresis "high" y continuando a lo largo de los puntos
// cuyo nivel sea superior a "low"

    for (i=0;i<NumRows;i++)
        for (j=0;j<NumCols;j++)
            if (AuxCannyImageMag[i][j]>=HighH)
				Hysteresis(AuxCannyImageMag,CannyImageMag,i,j,LowH);

    for (i=0;i<NumRows;i++)
        for (j=0;j<NumCols;j++)
            if (!CannyImageMag.pM[i*NumCols + j])
				CannyImageMag.pM[i*NumCols + j]=0;

	PostCanny(CannyImageMag);
	PostCanny(CannyImageMag);

	return CannyImageMag;
}

/**Image*******************************\
		       GaussS
\**************************************/
Image Image::GaussS(double Sigma)
{
	DoubleMatrix H,I;
    Image GaussImage;

    H = Gauss2dOpS(Sigma);
	I= *this;

	// Aplico el operador mediante la convolución
	GaussImage = (UcharMatrix)I.Conv(H,1);  //Type casting DoubleMatrix to Image (scaling between 0 and 255)

	return GaussImage;
}

/**Image*******************************\
		       GaussW
\**************************************/
Image Image::GaussW(double W)
{
	DoubleMatrix H,I;
    Image GaussImage;

    H = Gauss2dOpW(W);
	I= *this;

	// Aplico el operador mediante la convolución
	GaussImage = (UcharMatrix)I.Conv(H,1);  //Type casting DoubleMatrix to Image (scaling between 0 and 255)

	return GaussImage;
}

Image Image::GaussWipl(double W)
{

    IplConvKernel *iCK;
    IplImage      *I;
    IplImage      *J;

    IntMatrix H;
	DoubleMatrix Hr(5,5),Hc(5,5);
	Hr[0][0]=1;Hr[0][1]=2;Hr[0][2]=0;Hr[0][3]=-2;Hr[0][4]=-1;
	Hr[1][0]=2;Hr[1][1]=3;Hr[1][2]=0;Hr[1][3]=-3;Hr[1][4]=-2;
	Hr[2][0]=3;Hr[2][1]=5;Hr[2][2]=0;Hr[2][3]=-5;Hr[2][4]=-3;
	Hr[3][0]=2;Hr[3][1]=3;Hr[3][2]=0;Hr[3][3]=-3;Hr[3][4]=-2;
	Hr[4][0]=1;Hr[4][1]=2;Hr[4][2]=0;Hr[4][3]=-2;Hr[4][4]=-1;

	Hr *= (double)1/18*100;
	Hc = Hr.Trans();

    Image GaussImage;

//    H   = Gauss2dOpW(W);
    H = Hr;
    iCK = iplCreateConvKernel(H.Width(),H.Depth(),floor(H.Width()/2)+1,floor(H.Depth()/2)+1,H[0],0);

//    iplGetConvKernel(iCK,NF,NC,AX,AY,

    I = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is uchar
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_DWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

    J = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is uchar
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_DWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled
                                    
    /// allocate image data without filling
    iplAllocateImage( J, 0, 0 );   

    I->imageData = (char*)pM;

//    iplConvolve2D( I, J, &iCK, 1, IPL_SUM );
    iplFixedFilter(I,J,IPL_GAUSSIAN_5x5);

    GaussImage.Resize(NumRows,NumCols);
    GaussImage.pM = (unsigned char *)J->imageData;


	return GaussImage;
}

/**Image*******************************\
		  SegmentExtraction
\**************************************/

Image::SegmentVector Image::SegmentExtraction(double MaxDistance, unsigned int MinNumOfPixels)
	//  MaxDistance;				//Max. distance allowed allowed from the pixels to the segment that they compose.
	//	MinNumOfPixels;				//Minimo numero de pixels que deben formar un segmento
{
	//Var declarations
	SegmentVector ImgSegmentImage;
	
	size_t xmax,ymax,i,j;
	int aux;
	
	unsigned int ImgSegmentCounter = 0;					//Numero de segmentos
	UcharMatrix AuxRetina;								//Matriz de trabajo copia de la matriz Retina de la imagen

	PixelVector CandidatePixels; //Lista de pixels candidatos que iran formando el segmento
	Pixel PxAux;
	Pixel PxA,PxB;
	Line CandidateLine,AuxCandidateLine;
	Segment		CandidateImgSegment;
	Segment     AuxImgSegment;

	//Variables necesarias dentro del bucle do
	PixelVector LPVA;			//Lista de Pixels vecinos activos
	PixelVector LPVB;			//Lista de Pixels vecinos activos
	Pixel BestPxV;				//Pixel vecino con menor distancia a la recta que se está construyendo
	Pixel BestNewPxA;			//Pixel vecino con menor distancia a la recta que se está construyendo
	Pixel BestNewPxB;			//Pixel vecino con menor distancia a la recta que se está construyendo
	Pixel PxNeigh;				//Un pixel vecino activo cualquiera	
	bool TheBestIsPxA;			//Para saber si el pixel de menor distancia viene del extremo A o del B
	double DistAux;
	double DistA,DistB;
	double AuxMaxDistance;

	PixelVector::iterator PVitNotZero;
	PixelVector::iterator PVit;
	PixelVector::iterator DistPVit;
	
	//Copio la informacion sobre la extraccion de segmentos a la variable privada
	//que despues uso para serializar.
//	ImgSegmentData = SData;

	//Copio la matrix EdgeRetinaMag a la matriz de trabajo AuxRetina
	AuxRetina = *this;
	xmax=AuxRetina.Depth();
	ymax=AuxRetina.Width();

	//Obtengo una lista de pixels cuya intensidad es distinta de cero
	PixelVector VectorPixNotZero;
	for (i=0;i<xmax-1;i++)
		for (j=0;j<ymax-1;j++)
			if (AuxRetina[i][j]!=0)
				VectorPixNotZero.push_back(Pixel(i,j,AuxRetina[i][j]));


	if (VectorPixNotZero.empty()) return ImgSegmentImage; //Si no hay pixels activos devuelvo la lista de segmentos vacia
	
	//Recorro la lista de pixels para formar nuevos segmentos
	// 123
	// 4X5 Para cada pixel busco un vecino en el orden 5678
	// 678

	//Incrementos que hay que sumar a i y a j
	//para obtener los vecinos en el orden de preferencia 58763214
	//char I[8] = { 0, 1, 1, 1,-1,-1,-1, 0};
	//char J[8] = { 1, 1, 0,-1, 1, 0,-1,-1};
	//orden 12345678
	//char I[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
	//char J[8] = {-1, 0, 1,-1, 1,-1, 0, 1};
	//orden 57423861
	//Primero se chequean los horizontales y verticales
	//y despues los diagonales
	char I[8] = { 0, 1, 0,-1,-1, 1, 1,-1};
	char J[8] = { 1, 0,-1, 0, 1, 1,-1,-1};
											
	// Loop through the pixels not equals to zero.
	for (PVitNotZero = VectorPixNotZero.begin();PVitNotZero != VectorPixNotZero.end();PVitNotZero++){

        //Initialize PxA with a non-zero pixel
        PxA=*PVitNotZero;
		// If pixel (i,j) is free to belong to a segment.
		if (AuxRetina[(int)PxA.x()][(int)PxA.y()]) { 

			//Look for the end of the segment
			PxB.Set(0,0,0);
			for (aux=0;aux<8;aux++){
				i = PxA.x()+I[aux];
				j = PxA.y()+J[aux];
				if (i>=0 && i<xmax && j>=0 && j<ymax) {
					if (AuxRetina[i][j]) {
						PxB.Set(i,j,AuxRetina[i][j]);
						break;
					}
				}
			}

			// If I have found a valid segment's end PB
			if (PxB.Level!=0){ 

				//Initialize the Candidate Pixels Vector
				CandidatePixels.clear();

				//Add PA
				CandidatePixels.push_back(PxA);	

				//Add PB
				CandidatePixels.push_back(PxB);

				//We set the seed segment
				CandidateLine.Set(PxA,PxB);	

				do {
					BestPxV.Set(0,0,0);
					BestNewPxA.Set(0,0,0);
					BestNewPxB.Set(0,0,0);

					//We make a list with free neighbors for each end PA and PB
					LPVA.clear();
					LPVB.clear();

					for (aux=0;aux<8;aux++){
						i = PxA.x()+I[aux];
						j = PxA.y()+J[aux];
						if (i>=0 && i<xmax && j>=0 && j<ymax) {
							if (AuxRetina[i][j]) LPVA.push_back(Pixel(i,j,AuxRetina[i][j]));
						}
					}
					for (int aux=0;aux<8;aux++){
						i = PxB.x()+I[aux];
						j = PxB.y()+J[aux];
						if (i>=0 && i<xmax && j>=0 && j<ymax) {
							if (AuxRetina[i][j]) LPVB.push_back(Pixel(i,j,AuxRetina[i][j]));
						}
					}
					
					// If lists are empty then we finish (the segment) and go out of do-while loop
					if (LPVA.empty()&&LPVB.empty()){
						break;	
					}

					//We find out for PA the pixel with smallest Euclidean Distance to the segment
					if (!LPVA.empty()){
						DistPVit    =  LPVA.begin();
						BestNewPxA	= *DistPVit;							             //Setting the first pixel
						DistA	    =  abs(CandidateLine.EuclideanDistance(BestNewPxA)); //and first Distance
						DistPVit++;

						for (DistPVit;DistPVit!=LPVA.end();DistPVit++){
							PxNeigh=*DistPVit;
							DistAux = abs(CandidateLine.EuclideanDistance(PxNeigh));
							if (DistAux<DistA){
								BestNewPxA=PxNeigh;
								DistA = DistAux;
							}
						}
					}

					//We find out for PB the pixel with smallest Euclidean Distance to the segment
					if (!LPVB.empty()){
						DistPVit    =  LPVB.begin();
						BestNewPxB	= *DistPVit;						                 //Setting the first pixel
						DistB	    =  abs(CandidateLine.EuclideanDistance(BestNewPxB)); //and first Distance
						DistPVit++;

						for (DistPVit;DistPVit!=LPVB.end();DistPVit++){
							PxNeigh=*DistPVit;
							DistAux = abs(CandidateLine.EuclideanDistance(PxNeigh));
							if (DistAux<DistB){
								BestNewPxB=PxNeigh;
								DistB = DistAux;
							}
						}
					}

                    //We choose the best of the two candidates.
					if (!LPVA.empty()&&!LPVB.empty()){
						BestPxV = (DistA<=DistB)?BestNewPxA:BestNewPxB;
						TheBestIsPxA = (DistA<=DistB)?true:false;
					}
					else if (!LPVA.empty()&&LPVB.empty()){
						BestPxV = BestNewPxA;
						TheBestIsPxA = true;
					}
					else if	(!LPVB.empty()&&LPVA.empty()){
						BestPxV = BestNewPxB;
						TheBestIsPxA = false;
					}

                    //If the candidate pixel is free.
					if (BestPxV.Level!=0){
						//Add to the Candidates vector
						CandidatePixels.push_back(BestPxV);

						if (TheBestIsPxA){
							AuxCandidateLine.Set(BestPxV,PxB);
							AuxMaxDistance = MaxDistanceFromLine(CandidatePixels, AuxCandidateLine);
							if (AuxMaxDistance < MaxDistance) {
								//Deactivate the pixel that now belongs to the segment
								PxA=BestPxV;
								AuxRetina[(int)PxA.x()][(int)PxA.y()]=0;
								CandidateLine = AuxCandidateLine;
							}
						}
						else {
							AuxCandidateLine.Set(PxA,BestPxV);
							AuxMaxDistance = MaxDistanceFromLine(CandidatePixels, AuxCandidateLine);
							if (AuxMaxDistance < MaxDistance) {
								//Deactivate the pixel that now belongs to the segment
								PxB=BestPxV;
								AuxRetina[(int)PxB.x()][(int)PxB.y()]=0; 
								CandidateLine = AuxCandidateLine;
							}
						}
					}
					else
						//salgo del while porque no he encontrado un BestPxV valido
						break;

				} while (AuxMaxDistance < MaxDistance);

				if (CandidatePixels.size()>MinNumOfPixels) { //Si el numero de pixels supera el minimo admitido para formar un segmento
					//Si el final del while ha sido por desbordamiento del LRError
					//utilizo la linea candidata anterior a la introduccíon del pixel
					//que ha desbordado el LRError
					if (AuxMaxDistance >= MaxDistance){ //Si el error de la regresion esta por debajo del permitido añado el pixel a la lista de candidatos a formar el segmento
						//Desestimo el ultimo punto que provoco el desbordamiento
						//del error
						CandidatePixels.pop_back();
					}


					//El primer extremo es aquel que nos encontramos recorriendo el eje Y positivo en el sentido horario de PI a 0
					//Es decir aquel cuya linea que forma con el origen tiene un angulo mayor
					Line LOA(Point2D(0,0),PxA),LOB(Point2D(0,0),PxB);
					if (LOA.PosFi() >= LOB.PosFi()){
                        AuxImgSegment=Segment(0,PxA,PxB);
					}
					else 
						AuxImgSegment=Segment(0,PxB,PxA);

					ImgSegmentCounter++; //Aumento el contador de segmentos
					AuxImgSegment.Label = ImgSegmentCounter;

//			AuxImgSegment.SetPixelChain(CandidatePixels);
					//   - Obtengo información auxiliar como intensidad media de los vecinos, etc.
//			ImgSegmentSidesAvgGrayLevel(AuxImgSegment);

                    //Adds the new AuxImgSegment to the SegmentVector named ImgSegmentImage 
                    ImgSegmentImage.push_back(AuxImgSegment);
//AuxImgSegment.Show();
                    //Check if ends could belong to other segments
					//if so then pixel gets free.
					for (aux=0;aux<8;aux++){
						i = PxA.x()+I[aux];
						j = PxA.y()+J[aux];
						if (i>=0 && i<xmax && j>=0 && j<ymax) {
							if (AuxRetina[i][j]) {
								AuxRetina[(int)PxA.x()][(int)PxA.y()]=PxA.Level;
								break;
							}
						}
					}
					for (aux=0;aux<8;aux++){
						i = PxB.x()+I[aux];
						j = PxB.y()+J[aux];
						if (i>=0 && i<xmax && j>=0 && j<ymax) {
							if (AuxRetina[i][j]) {
								AuxRetina[(int)PxB.x()][(int)PxB.y()]=PxB.Level;
								break;
							}
						}
					}
				}
				else {
					// No almaceno el segmento
					// y devuelvo los pixels a posibles candidatos poniendoles
					// el valor de intensidad.
					for (PVit = CandidatePixels.begin();PVit != CandidatePixels.end();PVit++){
						PxAux=*PVit;
						AuxRetina[(int)PxAux.x()][(int)PxAux.y()]=PxAux.Level; //Desactivo el pixel que pertenece al nuevo segmento
					}
				}
			}
		}
	}
	return ImgSegmentImage;
}


/**Image*******************************\
		  ImgSegmentExtractionGAC
\**************************************/
/*
ImgSegmentMap Image::ImgSegmentExtractionGAC(double          MaxDistance,
												 unsigned int	 MinNumOfPixels)
	//  MaxDistance;				//Max. distance allowed allowed from the pixels to the segment that they compose.
	//	MinNumOfPixels;				//Minimo numero de pixels que deben formar un segmento
{
	//Var declarations
	ImgSegmentMap ImgSegmentImage;
	
	size_t xmax,ymax,i,j;
	int aux;
	
	unsigned int ImgSegmentCounter = 0;					//Numero de segmentos
	UcharMatrix AuxRetina;								//Matriz de trabajo copia de la matriz Retina de la imagen

	PixelVector CandidatePixels; //Lista de pixels candidatos que iran formando el segmento
	Pixel PxAux;
	Pixel PxA,PxB;
	StraightLine CandidateLine,AuxCandidateLine;
	ImgSegment		 CandidateImgSegment;
	ImgSegment      AuxImgSegment;

	//Variables necesarias dentro del bucle do
	PixelVector LPVA;			//Lista de Pixels vecinos activos
	PixelVector LPVB;			//Lista de Pixels vecinos activos
	Pixel BestPxV;				//Pixel vecino con menor distancia a la recta que se está construyendo
	Pixel BestNewPxA;			//Pixel vecino con menor distancia a la recta que se está construyendo
	Pixel BestNewPxB;			//Pixel vecino con menor distancia a la recta que se está construyendo
	Pixel PxNeigh;				//Un pixel vecino activo cualquiera	
	bool TheBestIsPxA;			//Para saber si el pixel de menor distancia viene del extremo A o del B
	double DistAux;
	double DistA,DistB;
	double AuxMaxDistance;

	PixelVector::iterator PVitNotZero;
	PixelVector::iterator PVit;
	PixelVector::iterator DistPVit;
	
	
	//Copio la informacion sobre la extraccion de segmentos a la variable privada
	//que despues uso para serializar.
//	ImgSegmentData = SData;

	//Copio la matrix EdgeRetinaMag a la matriz de trabajo AuxRetina
	AuxRetina = *this;
	xmax=AuxRetina.Depth();
	ymax=AuxRetina.Width();

	//Obtengo una lista de pixels cuya intensidad es distinta de cero
	PixelVector VectorPixNotZero;
	for (i=0;i<xmax-1;i++)
		for (j=0;j<ymax-1;j++)
			if (AuxRetina[i][j]!=0)
				VectorPixNotZero.push_back(Pixel(i,j,AuxRetina[i][j]));


	if (VectorPixNotZero.empty()) return ImgSegmentImage; //Si no hay pixels activos devuelvo la lista de segmentos vacia
	
	//Recorro la lista de pixels para formar nuevos segmentos
	// 123
	// 4X5 Para cada pixel busco un vecino en el orden 5678
	// 678

	//Incrementos que hay que sumar a i y a j
	//para obtener los vecinos en el orden de preferencia 58763214
	//char I[8] = { 0, 1, 1, 1,-1,-1,-1, 0};
	//char J[8] = { 1, 1, 0,-1, 1, 0,-1,-1};
	//orden 12345678
	//char I[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
	//char J[8] = {-1, 0, 1,-1, 1,-1, 0, 1};
	//orden 57423861
	//Primero se chequean los horizontales y verticales
	//y despues los diagonales
	char I[8] = { 0, 1, 0,-1,-1, 1, 1,-1};
	char J[8] = { 1, 0,-1, 0, 1, 1,-1,-1};
											

	// Loop through the pixels not equals to zero.
	for (PVitNotZero = VectorPixNotZero.begin();PVitNotZero != VectorPixNotZero.end();PVitNotZero++){
		PxA=*PVitNotZero;

		// If pixel (i,j) is free to belong to a segment.
		if (AuxRetina[(int)PxA.i][(int)PxA.j]) { 

			//Look for the end of the segment
			PxB.Set(0,0,0);
			for (aux=0;aux<8;aux++){
				i = PxA.i+I[aux];
				j = PxA.j+J[aux];
				if (i>=0 && i<xmax && j>=0 && j<ymax) {
					if (AuxRetina[i][j]) {
						PxB.Set(i,j,AuxRetina[i][j]);
						break;
					}
				}
			}

			// If I have found a valid segment's end PB
			if (PxB.GrayLevel!=0){ 

				//Initialize the Candidate Pixels Vector
				CandidatePixels.clear();

				//Add PA
				CandidatePixels.push_back(PxA);	

				//Add PB
				CandidatePixels.push_back(PxB);

				//We set the seed segment
				CandidateLine.Set(PxA,PxB);	

				do {
					BestPxV.Set(0,0,0);
					BestNewPxA.Set(0,0,0);
					BestNewPxB.Set(0,0,0);

					//We make a list with free neighbors for each end PA and PB
					LPVA.clear();
					LPVB.clear();

					for (aux=0;aux<8;aux++){
						i = PxA.i+I[aux];
						j = PxA.j+J[aux];
						if (i>=0 && i<xmax && j>=0 && j<ymax) {
							if (AuxRetina[i][j]) LPVA.push_back(Pixel(i,j,AuxRetina[i][j]));
						}
					}
					for (int aux=0;aux<8;aux++){
						i = PxB.i+I[aux];
						j = PxB.j+J[aux];
						if (i>=0 && i<xmax && j>=0 && j<ymax) {
							if (AuxRetina[i][j]) LPVB.push_back(Pixel(i,j,AuxRetina[i][j]));
						}
					}
					
					// If lists are empty then we finish (the segment) and go out of do-while loop
					if (LPVA.empty()&&LPVB.empty()){
						break;	
					}

					//We find out for PA the pixel with smallest Euclidean Distance to the segment
					if (!LPVA.empty()){
						DistPVit    =  LPVA.begin();
						BestNewPxA	= *DistPVit;							             //Setting the first pixel
						DistA	    =  abs(CandidateLine.EuclideanDistance(BestNewPxA)); //and first Distance
						DistPVit++;

						for (DistPVit;DistPVit!=LPVA.end();DistPVit++){
							PxNeigh=*DistPVit;
							DistAux = abs(CandidateLine.EuclideanDistance(PxNeigh));
							if (DistAux<DistA){
								BestNewPxA=PxNeigh;
								DistA = DistAux;
							}
						}
					}

					//We find out for PB the pixel with smallest Euclidean Distance to the segment
					if (!LPVB.empty()){
						DistPVit    =  LPVB.begin();
						BestNewPxB	= *DistPVit;						                 //Setting the first pixel
						DistB	    =  abs(CandidateLine.EuclideanDistance(BestNewPxB)); //and first Distance
						DistPVit++;

						for (DistPVit;DistPVit!=LPVB.end();DistPVit++){
							PxNeigh=*DistPVit;
							DistAux = abs(CandidateLine.EuclideanDistance(PxNeigh));
							if (DistAux<DistB){
								BestNewPxB=PxNeigh;
								DistB = DistAux;
							}
						}
					}

                    //We choose the best of the two candidates.
					if (!LPVA.empty()&&!LPVB.empty()){
						BestPxV = (DistA<=DistB)?BestNewPxA:BestNewPxB;
						TheBestIsPxA = (DistA<=DistB)?true:false;
					}
					else if (!LPVA.empty()&&LPVB.empty()){
						BestPxV = BestNewPxA;
						TheBestIsPxA = true;
					}
					else if	(!LPVB.empty()&&LPVA.empty()){
						BestPxV = BestNewPxB;
						TheBestIsPxA = false;
					}

                    //If the candidate pixel is free.
					if (BestPxV.GrayLevel!=0){
						//Add to the Candidates vector
						CandidatePixels.push_back(BestPxV);

						if (TheBestIsPxA){
							AuxCandidateLine.Set(BestPxV,PxB);
							AuxMaxDistance = MaxDistanceFromLine(CandidatePixels, AuxCandidateLine);
							if (AuxMaxDistance < MaxDistance) {
								//Deactivate the pixel that now belongs to the segment
								PxA=BestPxV;
								AuxRetina[(int)PxA.i][(int)PxA.j]=0;
								CandidateLine = AuxCandidateLine;
							}
						}
						else {
							AuxCandidateLine.Set(PxA,BestPxV);
							AuxMaxDistance = MaxDistanceFromLine(CandidatePixels, AuxCandidateLine);
							if (AuxMaxDistance < MaxDistance) {
								//Deactivate the pixel that now belongs to the segment
								PxB=BestPxV;
								AuxRetina[(int)PxB.i][(int)PxB.j]=0; 
								CandidateLine = AuxCandidateLine;
							}
						}
					}
					else
						//salgo del while porque no he encontrado un BestPxV valido
						break;

				} while (AuxMaxDistance < MaxDistance);

				if (CandidatePixels.size()>MinNumOfPixels) { //Si el numero de pixels supera el minimo admitido para formar un segmento
					//Si el final del while ha sido por desbordamiento del LRError
					//utilizo la linea candidata anterior a la introduccíon del pixel
					//que ha desbordado el LRError
					if (AuxMaxDistance >= MaxDistance){ //Si el error de la regresion esta por debajo del permitido añado el pixel a la lista de candidatos a formar el segmento
						//Desestimo el ultimo punto que provoco el desbordamiento
						//del error
						CandidatePixels.pop_back();
					}


					//El primer extremo es aquel que nos encontramos recorriendo el eje Y positivo en el sentido horario de PI a 0
					//Es decir aquel cuya linea que forma con el origen tiene un angulo mayor
					StraightLine LOA(PO,PxA),LOB(PO,PxB);
					if (LOA.PosFi() >= LOB.PosFi()){
						AuxImgSegment=ImgSegment(PxA,PxB);
					}
					else 
						AuxImgSegment=ImgSegment(PxB,PxA);

					ImgSegmentCounter++; //Aumento el contador de segmentos
					AuxImgSegment.Label = ImgSegmentCounter;

//			AuxImgSegment.SetPixelChain(CandidatePixels);
					//   - Obtengo información auxiliar como intensidad media de los vecinos, etc.
//			ImgSegmentSidesAvgGrayLevel(AuxImgSegment);
					ImgSegmentImage[ImgSegmentCounter] = AuxImgSegment;

					//Check if ends could belong to other segments
					//if so then pixel gets free.
					for (aux=0;aux<8;aux++){
						i = PxA.i+I[aux];
						j = PxA.j+J[aux];
						if (i>=0 && i<xmax && j>=0 && j<ymax) {
							if (AuxRetina[i][j]) {
								AuxRetina[(int)PxA.i][(int)PxA.j]=PxA.GrayLevel;
								break;
							}
						}
					}
					for (aux=0;aux<8;aux++){
						i = PxB.i+I[aux];
						j = PxB.j+J[aux];
						if (i>=0 && i<xmax && j>=0 && j<ymax) {
							if (AuxRetina[i][j]) {
								AuxRetina[(int)PxB.i][(int)PxB.j]=PxB.GrayLevel;
								break;
							}
						}
					}


				}
				else {
					// No almaceno el segmento
					// y devuelvo los pixels a posibles candidatos poniendoles
					// el valor de intensidad.
					for (PVit = CandidatePixels.begin();PVit != CandidatePixels.end();PVit++){
						PxAux=*PVit;
						AuxRetina[(int)PxAux.i][(int)PxAux.j]=PxAux.GrayLevel; //Desactivo el pixel que pertenece al nuevo segmento
					}
				}
			} 
		}
	}
	return ImgSegmentImage;
}

/**Image**************************************************************\
		                   Private functions
\*********************************************************************/


/**Image*******************************\
		       Hysteresis
\**************************************/
bool Image::Hysteresis(UcharMatrix &AuxCannyImageMag,UcharMatrix &CannyImageMag,size_t i,size_t j, unsigned char LowH)
{
	int k,l;        
	int i_plus_1,i_minus_1,j_plus_1,j_minus_1;
	bool break_flag;

	i_plus_1  = i+1;
	i_minus_1 = i-1;
	j_plus_1  = j+1;
	j_minus_1 = j-1;
	if (j_plus_1>=NumCols) j_plus_1=NumCols-1;
	if (j_minus_1<0) j_minus_1=0;
	if (i_plus_1>=NumRows) i_plus_1=NumRows-1;
	if (i_minus_1<0) i_minus_1=0;

	if (!CannyImageMag[i][j])
	{
		CannyImageMag[i][j]=AuxCannyImageMag[i][j];
		break_flag=false;
		for (k=i_minus_1;k<=i_plus_1;k++){
			for(l=j_minus_1;l<=j_plus_1;++l){
				if (!(l==j && k==i) &&   
					AuxCannyImageMag[i][j]>=LowH //&& abs(abs(orientacion[index]-orientacion[kindex])-128)>120
					)
					if (Hysteresis(AuxCannyImageMag,CannyImageMag,k,l,LowH))
					{
						break_flag=true;
						break;
					}
			}
			if (break_flag) break;
		}
		return(false);
	}
	else return(false);

}

/**Image*******************************\
		       PostCanny
\**************************************/
void Image::PostCanny(Image &CannyImageMag){
	//Esta funcion realiza el postprocesamiento de la CannyImageMag
	//obtenida mediante el operador de Canny.
	//Las tareas que realiza son:
	//Rellenados de huecos de un pixel xxoxx -> xxxxx
	//Eliminación de pixels paralelos
	//   x
	// xxxxx -> xxxxx
	//Eliminacion de pixels aislados

	//Rellenado de huecos de un pixel

	//Nomenclatura de los 8-vecinos
	// 123
	// 405 
	// 678
	//Incrementos que hay que sumar a i y a j
	//para obtener los vecinos en un orden de preferencia 
	//
	//Posiciones 12345678 (a)round
	char Ia[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
	char Ja[8] = {-1, 0, 1,-1, 1,-1, 0, 1};
	//Posiciones 405 (h)orizontal
	char Ih[3] = { 0, 0, 0};
	char Jh[3] = {-1, 0, 1};
	//Posiciones 207 (v)ertical
	char Iv[3] = {-1, 0, 1};
	char Jv[3] = { 0, 0, 0};
	//Posiciones 123 (h)orizontal (o)ver
	char Iho[3] = {-1,-1,-1};
	char Jho[3] = {-1, 0, 1};
	//Posiciones 678 (h)orizontal (u)nder
	char Ihu[3] = { 1, 1, 1};
	char Jhu[3] = {-1, 0, 1};
	//Posiciones 146 (v)ertical (o)ver
	char Ivl[3] = {-1, 0, 1};
	char Jvl[3] = {-1,-1,-1};
	//Posiciones 358 (v)ertical (u)nder
	char Ivr[3] = {-1, 0, 1};
	char Jvr[3] = { 1, 1, 1};

	size_t NumRows,NumCols;
	size_t i,j;
	size_t aux;
	size_t vi,vj;

	short CountPixNotZero_a;
	short CountPixNotZero_h;
	short CountPixNotZero_v;
	short CountPixNotZero_ho;
	short CountPixNotZero_hu;
	short CountPixNotZero_vl;
	short CountPixNotZero_vr;
	short Pos_ho;
	short Pos_hu;
	short Pos_vl;
	short Pos_vr;
	unsigned char Int_ho;
	unsigned char Int_hu;
	unsigned char Int_vl;
	unsigned char Int_vr;

	NumRows = CannyImageMag.Depth();
	NumCols = CannyImageMag.Width();

	//Eliminacion de pixels paralelos y pixels aislados
	for(i=0;i<NumRows;i++)
		for(j=0;j<NumCols;j++)
			if (CannyImageMag[i][j]){
				CountPixNotZero_h  = 0;
				CountPixNotZero_v  = 0;
				CountPixNotZero_a  = 0;

				for (aux=0;aux<3;aux++){
					vi = i+Ih[aux];
					vj = j+Jh[aux];
					if (vi>=0 && vi<NumRows && vj>=0 && vj<NumCols)
						if (CannyImageMag[vi][vj]){
							CountPixNotZero_h++;
						}
				}
				for (aux=0;aux<3;aux++){
					vi = i+Iv[aux];
					vj = j+Jv[aux];
					if (vi>=0 && vi<NumRows && vj>=0 && vj<NumCols)
						if (CannyImageMag[vi][vj]){
							CountPixNotZero_v++;
						}
				}
				for (aux=0;aux<8;aux++){
					vi = i+Ia[aux];
					vj = j+Ja[aux];
					if (vi>=0 && vi<NumRows && vj>=0 && vj<NumCols)
						if (CannyImageMag[vi][vj]){
							CountPixNotZero_a++;
						}
				}

				//Eliminacion de pixels paralelos
				if (CountPixNotZero_h==3 &&
					i >= 1)
					if (CannyImageMag[i-1][j]) {
							CannyImageMag[i-1][j] = 0;
					}

				if (CountPixNotZero_h==3 &&
					i+1 < NumRows)
					if (CannyImageMag[i+1][j]) {
							CannyImageMag[i+1][j] = 0;
					}
				if (CountPixNotZero_v==3 &&
					j >= 1)
					if (CannyImageMag[i][j-1]) {
							CannyImageMag[i][j-1] = 0;
					}

				if (CountPixNotZero_v==3 &&
					j+1 < NumCols)
					if (CannyImageMag[i][j+1]) {
							CannyImageMag[i][j+1] = 0;
					}

				//Eliminacion de pixels aislados
				if (CountPixNotZero_a==0) {
						CannyImageMag[i][j] = 0;
				}

			}

	for(i=0;i<NumRows;i++)
		for(j=0;j<NumCols;j++)
			if (!CannyImageMag[i][j]){
				CountPixNotZero_h  = 0;
				CountPixNotZero_v  = 0;
				CountPixNotZero_ho = 0;
				CountPixNotZero_hu = 0;
				CountPixNotZero_vr = 0;
				CountPixNotZero_vl = 0;
				Pos_ho = 0;
				Pos_hu = 0;
				Pos_vl = 0;
				Pos_vr = 0;

				for (aux=0;aux<3;aux++){
					vi = i+Iho[aux];
					vj = j+Jho[aux];
					if (vi>=0 && vi<NumRows && vj>=0 && vj<NumCols)
						if (CannyImageMag[vi][vj]){
							CountPixNotZero_ho++;
							Pos_ho = aux;
						}
				}
				for (aux=0;aux<3;aux++){
					vi = i+Ihu[aux];
					vj = j+Jhu[aux];
					if (vi>=0 && vi<NumRows && vj>=0 && vj<NumCols)
						if (CannyImageMag[vi][vj]){
							CountPixNotZero_hu++;
							Pos_hu = aux;
						}
				}
				for (aux=0;aux<3;aux++){
					vi = i+Ivl[aux];
					vj = j+Jvl[aux];
					if (vi>=0 && vi<NumRows && vj>=0 && vj<NumCols)
						if (CannyImageMag[vi][vj]){
							CountPixNotZero_vl++;
							Pos_vl = aux;
						}
				}
				for (aux=0;aux<3;aux++){
					vi = i+Ivr[aux];
					vj = j+Jvr[aux];
					if (vi>=0 && vi<NumRows && vj>=0 && vj<NumCols)
						if (CannyImageMag[vi][vj]){
							CountPixNotZero_vr++;
							Pos_vr = aux;
						}
				}

				//Rellenado de pixels verticales y horizontales
				if (CountPixNotZero_ho==1 &&
					CountPixNotZero_hu==1 &&
					j   >= 1 &&
					j+1 <  NumCols) {
					if (!CannyImageMag[i][j-1] &&
						!CannyImageMag[i][j+1]) {
						Int_ho = CannyImageMag[i+Iho[Pos_ho]][j+Jho[Pos_ho]];
						Int_hu = CannyImageMag[i+Ihu[Pos_hu]][j+Jhu[Pos_hu]];
						if (Pos_ho == Pos_hu){
							CannyImageMag[i][j+Jho[Pos_ho]] = (Int_ho + Int_hu)/2;
						}
						else{
							CannyImageMag[i][j] = (Int_ho + Int_hu)/2;
						}
					}
				}

				if (CountPixNotZero_vl==1 &&
					CountPixNotZero_vr==1 &&
					i   >= 1  &&
					i+1 <  NumRows) {
					if (!CannyImageMag[i-1][j] &&
						!CannyImageMag[i+1][j]) {
						Int_vl = CannyImageMag[i+Ivl[Pos_vl]][j+Jvl[Pos_vl]];
						Int_vr = CannyImageMag[i+Ivr[Pos_vr]][j+Jvr[Pos_vr]];
						if (Pos_vl == Pos_vr){
							CannyImageMag[i+Ivl[Pos_vl]][j] = (Int_vl+Int_vr)/2;
						}
						else{
							CannyImageMag[i][j] = (Int_vl+Int_vr)/2;
						}
					}
				}
			}
}


/**********************************************************************************\
 *									DrogOpS										  *
 * Esta función calcula el operador Drog (Derivada de la Gaussiana), el cual es   *
 * un operador basado en el gradiente combinado con el suavizado. El grado en	  *
 * que se realiza el suavizado se controla mediante el parámetro de la desviación *
 * típica de la gaussiana (sigma).												  *
 * El valor de W (tamaño del operador) se calcula en relación					  *
 * al valor de Sigma (desviación típica de la gaussiana)						  *
\**********************************************************************************/

DoubleMatrix Image::DrogOpS(double Sigma)
{
	double c = 2.0*sqrt(2.0)*Sigma;	// Cálculo de la anchura del lóbulo central de la Gaussiana
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		W		= 2.0*c;				//El tamaño de la máscara que debe ser >= 2*c
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix X(1,NumCols),Y;		//x = -floor(W/2):floor(W/2)
	int i,j;
	for (j=0;j<NumCols;j++){
		X[0][j]=(double)(j-aux);
	}
	Y=X;

	double		Sigma2=pow(Sigma,2.0);
	DoubleMatrix GaussX,GaussY;		//Obtengo la Gaussiana de las máscaras
	GaussX = X.Gauss(Sigma);
	GaussY = Y.Gauss(Sigma);

	// Obtengo el operador mediante
	double GaussFactor;
	DoubleMatrix DrogHr(NumCols,NumCols),DrogHc(NumCols,NumCols);
	for (i=0;i<NumCols;i++)
		for (j=0;j<NumCols;j++) {
			GaussFactor = GaussX[0][i]*GaussY[0][j];
			DrogHr[i][j] = -X[0][i]*GaussFactor/Sigma2;
			DrogHc[i][j] = -Y[0][j]*GaussFactor/Sigma2;
		}

	return DrogHr;
}

/**********************************************************************************\
 *									DrogOpW										  *
 * Esta función calcula el operador Drog (Derivada de la Gaussiana), el cual es   *
 * un operador basado en el gradiente combinado con el suavizado. El grado en	  *
 * que se realiza el suavizado se controla mediante el parámetro de la desviación *
 * típica de la gaussiana (sigma).												  *
 * El valor de Sigma (desviación típica de la gaussiana) se calcula en relación   *
 * al W (tamaño del operador)													  *
\**********************************************************************************/

DoubleMatrix Image::DrogOpW(double W)
{
	double c   = W/2.0;				// Cálculo de la anchura del lóbulo central de la Gaussiana
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño de Sigma se calcula en
	// función del tamaño del lóbulo central.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		Sigma   = c/(2.0*sqrt(2));				//El tamaño de la máscara que debe ser >= 2*c
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix X(1,NumCols),Y;		//x = -floor(W/2):floor(W/2)
	int			i,j;

	for (j=0;j<NumCols;j++){
		X[0][j]=(double)(j-aux);
	}
	Y=X;

	double		Sigma2=pow(Sigma,2.0);
	DoubleMatrix GaussX,GaussY;		//Obtengo la Gaussiana de las máscaras
	GaussX = X.Gauss(Sigma);
	GaussY = Y.Gauss(Sigma);

	// Obtengo el operador
	double GaussFactor;
	DoubleMatrix DrogHr(NumCols,NumCols),DrogHc(NumCols,NumCols);
	for (i=0;i<NumCols;i++)
		for (j=0;j<NumCols;j++) {
			GaussFactor = GaussX[0][i]*GaussY[0][j];
			DrogHr[i][j] = -X[0][i]*GaussFactor/Sigma2;
			DrogHc[i][j] = -Y[0][j]*GaussFactor/Sigma2;
		}

	return DrogHr;
}

/**************************************************************************************\
 *									LogOpS											  *
 * Esta función calcula el operador Log, el cual aplica la Laplaciana de la Gaussiana * 
 * a la imagen.																		  *
 * El valor de W (tamaño del operador) se calcula en relación						  *
 * al valor de Sigma (desviación típica de la gaussiana)							  *
\**************************************************************************************/

DoubleMatrix Image::LogOpS(double Sigma)
{
	double c = 2.0*sqrt(2.0)*Sigma;	// Cálculo de la anchura del lóbulo central de la Gaussiana
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		W		= 3.0*c;				// El tamaño del operador debe ser el triple
												// de la anchura del lóbulo central (W>=3*c)
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix X(1,NumCols),Y;		//x = -floor(W/2):floor(W/2)
	int i,j;
	for (j=0;j<NumCols;j++){
		X[0][j]=(double)(j-aux);
	}
	Y=X;

	double		TwoSigma2=pow(Sigma,2.0)*2.0;
	double		piSigma4=pow(Sigma,4.0)*PI;

	// Obtengo el operador mediante
	DoubleMatrix LogH(NumCols,NumCols);
	double aux1;
	for (i=0;i<NumCols;i++)
		for (j=0;j<NumCols;j++) {
			aux1 = (pow(X[0][i],2.0)+pow(Y[0][j],2.0))/(TwoSigma2);
			LogH[i][j] = exp(-aux1)*(aux1-1)/(piSigma4);
		}

	return LogH;
}


/**************************************************************************************\
 *									LogOpW											  *
 * Esta función calcula el operador Log, el cual aplica la Laplaciana de la Gaussiana * 
 * a la imagen.																		  *
 * El valor de Sigma (desviación típica de la gaussiana) se calcula en relación		  *
 * al W (tamaño del operador)														  *
\**************************************************************************************/

DoubleMatrix Image::LogOpW(double W)
{
	double c = W/3.0;				// El tamaño del operador debe ser el triple
									// de la anchura del lóbulo central (W>=3*c)
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		Sigma	= c/(2.0*sqrt(2.0));	// Cálculo de la anchura del lóbulo central de la Gaussiana
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix X(1,NumCols),Y;		//x = -floor(W/2):floor(W/2)
	int i,j;
	for (j=0;j<NumCols;j++){
		X[0][j]=(double)(j-aux);
	}
	Y=X;

	double		TwoSigma2=pow(Sigma,2.0)*2.0;
	double		piSigma4=pow(Sigma,4.0)*PI;

	// Obtengo el operador mediante
	DoubleMatrix LogH(NumCols,NumCols);
	double aux1;
	for (i=0;i<NumCols;i++)
		for (j=0;j<NumCols;j++) {
			aux1 = (pow(X[0][i],2.0)+pow(Y[0][j],2.0))/(TwoSigma2);
			LogH[i][j] = exp(-aux1)*(aux1-1)/(piSigma4);
		}

	return LogH;
}

/**************************************************************************************\
 *									SLogOpS											  *
 * Esta función calcula el operador Log, el cual aplica la Laplaciana de la Gaussiana * 
 * a la imagen.																		  *
 * Esta función aplica la propiedad de separabilidad de la Gaussiana,				  *
 * con lo cual la formulación se realiza en función  de suma de operadores			  *
 * separables (Huertas y Medioni - 1986)											  *
 * El valor de W (tamaño del operador) se calcula en relación						  *
 * al valor de Sigma (desviación típica de la gaussiana)							  *
\**************************************************************************************/

DoubleMatrix Image::SLogOpS(double Sigma)
{
	
	double c = 2.0*sqrt(2.0)*Sigma;	// Cálculo de la anchura del lóbulo central de la Gaussiana
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		W		= 3.0*c;				// El tamaño del operador debe ser el triple
												// de la anchura del lóbulo central (W>=3*c)
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix X(1,NumCols),Y;		//x = -floor(W/2):floor(W/2)
	int i,j;
	for (j=0;j<NumCols;j++){
		X[0][j]=(double)(j-aux);
	}
	Y=X;

	DoubleMatrix GaussX,GaussY;		//Obtengo la Gaussiana de las máscaras
	GaussX = X.Gauss(Sigma);
	GaussY = Y.Gauss(Sigma);

	double Sigma2			= pow(Sigma,2.0);
	double OneDivPISigma2	= 1.0/(Sigma2*PI);	

	// Obtengo el operador mediante
	DoubleMatrix LogH(NumCols,NumCols);

	for (i=0;i<NumCols;i++)
		for (j=0;j<NumCols;j++) {
			LogH[i][j] = -OneDivPISigma2 * (
				(GaussX[0][i]*(pow(Y[0][j],2.0)/Sigma2 - 1)*GaussY[0][j]) +
				(GaussY[0][j]*(pow(X[0][i],2.0)/Sigma2 - 1)*GaussX[0][i])
			);
		}

	return LogH;
}

/**************************************************************************************\
 *									SLogOpW											  *
 * Esta función calcula el operador Log, el cual aplica la Laplaciana de la Gaussiana * 
 * a la imagen.																		  *
 * Esta función aplica la propiedad de separabilidad de la Gaussiana,				  *
 * con lo cual la formulación se realiza en función  de suma de operadores			  *
 * separables (Huertas y Medioni - 1986)											  *
 * El valor de Sigma (desviación típica de la gaussiana) se calcula en relación       *
 * al W (tamaño del operador)														  *
\**************************************************************************************/

DoubleMatrix Image::SLogOpW(double W)
{
	double c = W/3.0;			// El tamaño del operador debe ser el triple
								// de la anchura del lóbulo central (W>=3*c)
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		Sigma	= c/(2.0*sqrt(2.0));// Cálculo de la anchura del lóbulo central de la Gaussiana
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix X(1,NumCols),Y;		//x = -floor(W/2):floor(W/2)
	int i,j;
	for (j=0;j<NumCols;j++){
		X[0][j]=(double)(j-aux);
	}
	Y=X;

	DoubleMatrix GaussX,GaussY;		//Obtengo la Gaussiana de las máscaras
	GaussX = X.Gauss(Sigma);
	GaussY = Y.Gauss(Sigma);

	double Sigma2			= pow(Sigma,2.0);
	double OneDivPISigma2	= 1.0/(Sigma2*PI);	

	// Obtengo el operador mediante
	DoubleMatrix LogH(NumCols,NumCols);

	for (i=0;i<NumCols;i++)
		for (j=0;j<NumCols;j++) {
			LogH[i][j] = -OneDivPISigma2 * (
				(GaussX[0][i]*(pow(Y[0][j],2.0)/Sigma2 - 1)*GaussY[0][j]) +
				(GaussY[0][j]*(pow(X[0][i],2.0)/Sigma2 - 1)*GaussX[0][i])
			);
		}

	return LogH;
}


/**************************************************************************************\
 *									GaussOpS										  *
 * Esta función calcula el operador Gauss bidimensional								  * 
 * El valor de W (tamaño del operador) se calcula en relación						  *
 * al valor de Sigma (desviación típica de la gaussiana)							  *
\**************************************************************************************/

DoubleMatrix Image::GaussOpS(double Sigma)
{
	double c = 2.0*sqrt(2.0)*Sigma;	// Cálculo de la anchura del lóbulo central de la Gaussiana
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		W		= 3.0*c;				// El tamaño del operador debe ser el triple
												// de la anchura del lóbulo central (W>=3*c)
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix X(1,NumCols),Y;		//x = -floor(W/2):floor(W/2)
	int i,j;
	for (j=0;j<NumCols;j++){
		X[0][j]=(double)(j-aux);
	}
	Y=X;

	//GaussianMatrix (i,j) = exp(-(x(i).^2+y(j).^2)/(2*sigma^2))/(2*pi*sigma^2);
	double		Sigma2      = pow(Sigma,2.0);
	double		TwoSigma2   = Sigma2*2;
	double		TwopiSigma2 = PI*TwoSigma2;

	// Obtengo el operador mediante
	DoubleMatrix GaussH(NumCols,NumCols);
	for (i=0;i<NumCols;i++)
		for (j=0;j<NumCols;j++) {
			GaussH[i][j] = exp(-(pow(X[0][i],2.0)+pow(Y[0][j],2.0))/TwoSigma2)/TwopiSigma2;
		}

	return GaussH;
}

/**************************************************************************************\
 *									GaussOpW										  *
 * Esta función calcula el operador Gauss bidimensional								  * 
 * El valor de Sigma (desviación típica de la gaussiana) se calcula en relación       *
 * al W (tamaño del operador)														  *
\**************************************************************************************/

DoubleMatrix Image::GaussOpW(double W)
{
	double c = W/3.0;			// El tamaño del operador debe ser el triple
								// de la anchura del lóbulo central (W>=3*c)
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		Sigma	= c/(2.0*sqrt(2.0));// Cálculo de la anchura del lóbulo central de la Gaussiana
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix X(1,NumCols),Y;		//x = -floor(W/2):floor(W/2)
	int i,j;
	for (j=0;j<NumCols;j++){
		X[0][j]=(double)(j-aux);
	}
	Y=X;

	//GaussianMatrix (i,j) = exp(-(x(i).^2+y(j).^2)/(2*sigma^2))/(2*pi*sigma^2);
	double		Sigma2      = pow(Sigma,2.0);
	double		TwoSigma2   = Sigma2*2;
	double		TwopiSigma2 = PI*TwoSigma2;

	// Obtengo el operador mediante
	DoubleMatrix GaussH(NumCols,NumCols);
	for (i=0;i<NumCols;i++)
		for (j=0;j<NumCols;j++) {
			GaussH[i][j] = exp(-(pow(X[0][i],2.0)+pow(Y[0][j],2.0))/TwoSigma2)/TwopiSigma2;
		}

	return GaussH;
}

/**************************************************************************************\
 *									DogOpS											  *
 * Esta función calcula el operador Dog, el cual es una aproximación				  *
 * al operador Log mediante diferencia de Gaussianas								  *
 * El valor de W (tamaño del operador) se calcula en relación						  *
 * al valor de Sigma (desviación típica de la gaussiana)							  *
\**************************************************************************************/

DoubleMatrix Image::DogOpS(double Sigma)
{
	double c = 2.0*sqrt(2.0)*Sigma;	// Cálculo de la anchura del lóbulo central de la Gaussiana
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		W		= 3.0*c;				// El tamaño del operador debe ser el triple
												// de la anchura del lóbulo central (W>=3*c)
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix X(1,NumCols),Y;		//x = -floor(W/2):floor(W/2)
	int i,j;
	for (j=0;j<NumCols;j++){
		X[0][j]=(double)(j-aux);
	}
	Y=X;

	double SigmaB = Sigma * 1.6;		// Marr y Hildreth (1980) demuestran que la proporción
								    // Sigma2/Sigma1 = 1.6 es la que mejor aproxima el operador Log

	//DogMatrix = gauss2(x,y,Sigma1) - gauss2(x,y,Sigma2);
	//GaussianMatrix (i,j) = exp(-(x(i).^2+y(j).^2)/(2*sigma^2))/(2*pi*sigma^2);
	double		Sigma2      = pow(Sigma,2.0);
	double		TwoSigma2   = Sigma2*2;
	double		TwopiSigma2 = PI*TwoSigma2;

	double		SigmaB2      = pow(SigmaB,2.0);
	double		TwoSigmaB2   = SigmaB2*2;
	double		TwopiSigmaB2 = PI*TwoSigmaB2;

	// Obtengo el operador mediante
	DoubleMatrix DogH(NumCols,NumCols);
	double GaussA,GaussB;
	for (i=0;i<NumCols;i++)
		for (j=0;j<NumCols;j++) {
			GaussA = exp(-(pow(X[0][i],2.0)+pow(Y[0][j],2.0))/TwoSigma2)/TwopiSigma2;
			GaussB = exp(-(pow(X[0][i],2.0)+pow(Y[0][j],2.0))/TwoSigmaB2)/TwopiSigmaB2;
			DogH[i][j] = GaussA-GaussB;
		}

	return DogH;
}

/**************************************************************************************\
 *									DogOpS											  *
 * Esta función calcula el operador Dog, el cual es una aproximación				  *
 * al operador Log mediante diferencia de Gaussianas								  *
 * El valor de Sigma (desviación típica de la gaussiana) se calcula en relación       *
 * al W (tamaño del operador)														  *
\**************************************************************************************/

DoubleMatrix Image::DogOpW(double W)
{
	double c = W/3.0;			// El tamaño del operador debe ser el triple
								// de la anchura del lóbulo central (W>=3*c)
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		Sigma	= c/(2.0*sqrt(2.0));// Cálculo de la anchura del lóbulo central de la Gaussiana
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix X(1,NumCols),Y;		//x = -floor(W/2):floor(W/2)
	int i,j;
	for (j=0;j<NumCols;j++){
		X[0][j]=(double)(j-aux);
	}
	Y=X;

	double SigmaB = Sigma * 1.6;		// Marr y Hildreth (1980) demuestran que la proporción
								    // Sigma2/Sigma1 = 1.6 es la que mejor aproxima el operador Log

	//DogMatrix = gauss2(x,y,Sigma1) - gauss2(x,y,Sigma2);
	//GaussianMatrix (i,j) = exp(-(x(i).^2+y(j).^2)/(2*sigma^2))/(2*pi*sigma^2);
	double		Sigma2      = pow(Sigma,2.0);
	double		TwoSigma2   = Sigma2*2;
	double		TwopiSigma2 = PI*TwoSigma2;

	double		SigmaB2      = pow(SigmaB,2.0);
	double		TwoSigmaB2   = SigmaB2*2;
	double		TwopiSigmaB2 = PI*TwoSigmaB2;

	// Obtengo el operador mediante
	DoubleMatrix DogH(NumCols,NumCols);
	double GaussA,GaussB;
	for (i=0;i<NumCols;i++)
		for (j=0;j<NumCols;j++) {
			GaussA = exp(-(pow(X[0][i],2.0)+pow(Y[0][j],2.0))/TwoSigma2)/TwopiSigma2;
			GaussB = exp(-(pow(X[0][i],2.0)+pow(Y[0][j],2.0))/TwoSigmaB2)/TwopiSigmaB2;
			DogH[i][j] = GaussA-GaussB;
		}

	return DogH;
}
/*************************************************************\
 *															 *
\*************************************************************/


/**************************************************************************************\
 *									Gauss1dOpS										  *
 * Esta función calcula el operador Gauss unidimensional dimensional				  * 
 * El valor de W (tamaño del operador) se calcula en relación						  *
 * al valor de Sigma (desviación típica de la gaussiana)							  *
\**************************************************************************************/

DoubleMatrix Image::Gauss1dOpS(double Sigma)
{
	double w = 2.0*sqrt(2.0)*Sigma;	// Cálculo de la anchura del lóbulo central de la Gaussiana
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		W		= 3.0*w;				// El tamaño del operador debe ser el triple
												// de la anchura del lóbulo central (W>=3*c)
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix G(1,NumCols);		//x = -floor(W/2):floor(W/2)
	double a,b,c,d;
	int n;

	G.Init();

	for (n=0;n<NumCols;n++) {
            a = GAC::Gauss(n,Sigma);
    //		if (a>0.005 || n<2) {
            b = GAC::Gauss(n-0.5,Sigma);
            c = GAC::Gauss(n+0.5,Sigma);
            d = GAC::Gauss(n,Sigma*0.5);
			G[0][n]= (a+b+c)/3/(6.283185*Sigma*Sigma);
//		}
//		else
//			break;
	}

	return G;
}

/**************************************************************************************\
 *									Gauss1dOpW										  *
 * Esta función calcula el operador Gauss unidimensional								  * 
 * El valor de Sigma (desviación típica de la gaussiana) se calcula en relación       *
 * al W (tamaño del operador)														  *
\**************************************************************************************/

DoubleMatrix Image::Gauss1dOpW(double W)
{
	double w = W/3.0;			// El tamaño del operador debe ser el triple
								// de la anchura del lóbulo central (W>=3*c)
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		Sigma	= w/(2.0*sqrt(2.0));// Cálculo de la anchura del lóbulo central de la Gaussiana
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix G(1,NumCols);		//x = -floor(W/2):floor(W/2)
	double a,b,c,d;
	int n;

	for (n=0;n<NumCols;n++) {
        a = GAC::Gauss(n,Sigma);
//		if (a>0.005 || n<2) {
			b = GAC::Gauss(n-0.5,Sigma);
			c = GAC::Gauss(n+0.5,Sigma);
			d = GAC::Gauss(n,Sigma*0.5);
			G[0][n]= (a+b+c)/3/(6.283185*Sigma*Sigma);
//		}
//		else
//			break;
	}

	return G;
}


/**************************************************************************************\
 *									dGauss1dOpS										  *
 * Esta función calcula la derivada del operador Gauss unidimensional								  * 
 * El valor de W (tamaño del operador) se calcula en relación						  *
 * al valor de Sigma (desviación típica de la gaussiana)							  *
\**************************************************************************************/

DoubleMatrix Image::dGauss1dOpS(double Sigma)
{
	double w = 2.0*sqrt(2.0)*Sigma;	// Cálculo de la anchura del lóbulo central de la Gaussiana
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		W		= 3.0*w;				// El tamaño del operador debe ser el triple
												// de la anchura del lóbulo central (W>=3*c)
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix dG(1,NumCols);		//x = -floor(W/2):floor(W/2)
	double a,b,c,d;
	int n;

	dG.Init();
	for (n=0;n<NumCols;n++) {
		a = GAC::Gauss(n,Sigma);
//		if (a>0.005 || n<2) {
			b = GAC::Gauss(n-0.5,Sigma);
			c = GAC::Gauss(n+0.5,Sigma);
			d = GAC::Gauss(n,Sigma*0.5);
			dG[0][n]= c-b;
//		}
//		else
//			break;
	}

	return dG;
}

/**************************************************************************************\
 *									dGauss1dOpW										  *
 * Esta función calcula la derivada del operador Gauss unidimensional								  * 
 * El valor de Sigma (desviación típica de la gaussiana) se calcula en relación       *
 * al W (tamaño del operador)														  *
\**************************************************************************************/

DoubleMatrix Image::dGauss1dOpW(double W)
{
	double w = W/3.0;			// El tamaño del operador debe ser el triple
								// de la anchura del lóbulo central (W>=3*c)
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		Sigma	= w/(2.0*sqrt(2.0));// Cálculo de la anchura del lóbulo central de la Gaussiana
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix dG(1,NumCols);		//x = -floor(W/2):floor(W/2)
	double a,b,c,d;
	int n;

	for (n=0;n<NumCols;n++) {
		a = GAC::Gauss(n,Sigma);
//		if (a>0.005 || n<2) {
			b = GAC::Gauss(n-0.5,Sigma);
			c = GAC::Gauss(n+0.5,Sigma);
			d = GAC::Gauss(n,Sigma*0.5);
			dG[0][n]= c-b;
//		}
//		else
//			break;
	}

	return dG;
}


/**************************************************************************************\
 *									dGauss1dOpS										  *
 * Esta función calcula la segunda derivada del operador Gauss unidimensional								  * 
 * El valor de W (tamaño del operador) se calcula en relación						  *
 * al valor de Sigma (desviación típica de la gaussiana)							  *
\**************************************************************************************/

DoubleMatrix Image::d2Gauss1dOpS(double Sigma)
{
	double w = 2.0*sqrt(2.0)*Sigma;	// Cálculo de la anchura del lóbulo central de la Gaussiana
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		W		= 3.0*w;				// El tamaño del operador debe ser el triple
												// de la anchura del lóbulo central (W>=3*c)
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix d2G(1,NumCols);		//x = -floor(W/2):floor(W/2)
	double a,b,c,d;
	int n;

	d2G.Init();
	for (n=0;n<NumCols;n++) {
		a = GAC::Gauss(n,Sigma);
//		if (a>0.005 || n<2) {
			b = GAC::Gauss(n-0.5,Sigma);
			c = GAC::Gauss(n+0.5,Sigma);
			d = GAC::Gauss(n,Sigma*0.5);
			d2G[0][n]= 1.6*d-a;
//		}
//		else
//			break;
	}

	return d2G;
}

/**************************************************************************************\
 *									dGauss1dOpW										  *
 * Esta función calcula la segunda derivada del operador Gauss unidimensional								  * 
 * El valor de Sigma (desviación típica de la gaussiana) se calcula en relación       *
 * al W (tamaño del operador)														  *
\**************************************************************************************/

DoubleMatrix Image::d2Gauss1dOpW(double W)
{
	double w = W/3.0;			// El tamaño del operador debe ser el triple
								// de la anchura del lóbulo central (W>=3*c)
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		Sigma	= w/(2.0*sqrt(2.0));// Cálculo de la anchura del lóbulo central de la Gaussiana
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix d2G(1,NumCols);		//x = -floor(W/2):floor(W/2)
	double a,b,c,d;
	int n;

	for (n=0;n<NumCols;n++) {
		a = GAC::Gauss(n,Sigma);
//		if (a>0.005 || n<2) {
			b = GAC::Gauss(n-0.5,Sigma);
			c = GAC::Gauss(n+0.5,Sigma);
			d = GAC::Gauss(n,Sigma*0.5);
			d2G[0][n]= 1.6*d-a;
//		}
//		else
//			break;
	}

	return d2G;
}

/**************************************************************************************\
 *									Gauss2dOpS										  *
 * Esta función calcula el operador Gauss bidimensional								  * 
 * El valor de W (tamaño del operador) se calcula en relación						  *
 * al valor de Sigma (desviación típica de la gaussiana)							  *
\**************************************************************************************/

DoubleMatrix Image::Gauss2dOpS(double Sigma)
{
	double c = 2.0*sqrt(2.0)*Sigma;	// Cálculo de la anchura del lóbulo central de la Gaussiana
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		W		= 3.0*c;				// El tamaño del operador debe ser el triple
												// de la anchura del lóbulo central (W>=3*c)
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix X(1,NumCols),Y;		//x = -floor(W/2):floor(W/2)
	int i,j;
	for (j=0;j<NumCols;j++){
		X[0][j]=(double)(j-aux);
	}
	Y=X;

	//GaussianMatrix (i,j) = exp(-(x(i).^2+y(j).^2)/(2*sigma^2))/(2*pi*sigma^2);
    double		Sigma2      = pow(Sigma,2.0);
	double		TwoSigma2   = Sigma2*2;
	double		TwopiSigma2 = PI*TwoSigma2;

	// Obtengo el operador mediante
	DoubleMatrix GaussH(NumCols,NumCols);
	for (i=0;i<NumCols;i++)
		for (j=0;j<NumCols;j++) {
			GaussH[i][j] = exp(-(pow(X[0][i],2.0)+pow(Y[0][j],2.0))/TwoSigma2)/TwopiSigma2;
		}

	return GaussH;
}

/**************************************************************************************\
 *									Gauss2dOpW										  *
 * Esta función calcula el operador Gauss bidimensional								  * 
 * El valor de Sigma (desviación típica de la gaussiana) se calcula en relación       *
 * al W (tamaño del operador)														  *
\**************************************************************************************/

DoubleMatrix Image::Gauss2dOpW(double W)
{
	double c = W/3.0;			// El tamaño del operador debe ser el triple
								// de la anchura del lóbulo central (W>=3*c)
	// Calculo el tamaño del operador.
	// En el cálculo del operador se usa una anchura de al menos
	// el doble del tamaño del lóbulo central. El tamaño del lóbulo central se calcula en
	// función de Sigma.
	// Para este operador se ha calculado empíricamente observando su representación gráfica.
	// Se ha determinado que la máscara debe ser el doble del tamaño de lóbulo central.

	double		Sigma	= c/(2.0*sqrt(2.0));// Cálculo de la anchura del lóbulo central de la Gaussiana
	int			aux		= floor(W/2.0);
	size_t		NumCols = (2.0*aux)+1.0;	//Se crea una máscara de dimensiones impares
	DoubleMatrix X(1,NumCols),Y;		//x = -floor(W/2):floor(W/2)
	int i,j;
	for (j=0;j<NumCols;j++){
		X[0][j]=(double)(j-aux);
	}
	Y=X;

	//GaussianMatrix (i,j) = exp(-(x(i).^2+y(j).^2)/(2*sigma^2))/(2*pi*sigma^2);
	double		Sigma2      = pow(Sigma,2.0);
	double		TwoSigma2   = Sigma2*2;
	double		TwopiSigma2 = PI*TwoSigma2;

	// Obtengo el operador mediante
	DoubleMatrix GaussH(NumCols,NumCols);
	for (i=0;i<NumCols;i++)
		for (j=0;j<NumCols;j++) {
			GaussH[i][j] = exp(-(pow(X[0][i],2.0)+pow(Y[0][j],2.0))/TwoSigma2)/TwopiSigma2;
		}

	return GaussH;
}


UcharMatrix Image::ZCross(DoubleMatrix  FilteredImage)
{
    // Esta función detecta los cruces por cero en la matriz de entrada compuesta por valores negativos y positivos.
    // Se usa normalmente para la detección de bordes en matrices a las que previamente se le ha aplicado un operador 
    // de tipo laplaciano.
    // Chequea la imágen de fila por fila de izquierda a derecha buscando cruces por cero que serán:
    //   VERTICAL   POSITIVO cuando se pase de negativo a positivo. (i,j) --> (i,j+1)
    //   VERTICAL   NEGATIVO cuando se pase de positivo a negativo. (i,j) --> (i,j+1)
    //   HORIZONTAL POSITIVO cuando se pase de negativo a positivo. (i,j) --> (i+1,j)
    //   HORIZONTAL NEGATIVO cuando se pase de positivo a negativo. (i,j) --> (i+1,j)
	// ZCVertical   Matriz donde m(i,j) = [1|-1]
    //                        1 el pixel i,j   es un cruce por cero VERTICAL POSITIVO
    //                       -1 el pixel i,j+1 es un cruce por cero VERTICAL NEGATIVO
	// ZCHorizontal   Matriz donde m(i,j) = [2|-2]
    //                       2 el pixel i  ,j es un cruce por cero HORIZONTAL POSITIVO
    //                      -2 el pixel i+1,j es un cruce por cero HORIZONTAL NEGATIVO

	CharMatrix ZCVertical;
	CharMatrix ZCHorizontal;

	ZCVertical.Resize  (FilteredImage.Depth(),FilteredImage.Width());
	ZCHorizontal.Resize(FilteredImage.Depth(),FilteredImage.Width());

	ZCVertical.SetAll(0);
	ZCHorizontal.SetAll(0);

	CharMatrix FISign = FilteredImage.Sign();		// Obtengo la matriz de signos (-1:negativo 0:cero +1:positivo)

	// Detección de cruces por cero de izquierda a derecha.
	// El cruce será positivo cuando se pase de negativo a positivo.
	// El cruce será negativo cuando se pase de positivo a negativo.
	size_t i,j;
	for (i=1;i<FilteredImage.Depth()-1;i++)		
		for (j=1;j<FilteredImage.Width()-1;j++)	{
//			cout << i <<","<<j<<" = "<<(int)FISign[i][j]<<endl;
			if (FISign[i][j]!=FISign[i][j+1])
				if (FISign[i][j]>FISign[i][j+1])
					ZCVertical[i][j]=1;				//Cruce por Cero VERTICAL POSITIVO
				else
					ZCVertical[i][j+1]=-1;			//Cruce por Cero VERTICAL NEGATIVO
			if (FISign[i][j]!=FISign[i+1][j])
				if (FISign[i][j]>FISign[i+1][j])
					ZCHorizontal[i][j]=2;				//Cruce por Cero HORIZONTAL POSITIVO
				else
					ZCHorizontal[i+1][j]=-2;			//Cruce por Cero HORIZONTAL NEGATIVO

		}

	CharMatrix VP,VN,H,ZCaux;
	UcharMatrix ZC;
	VP = (ZCVertical== 1);
	VN = (ZCVertical==-1);
	H  = (ZCHorizontal!=0);
			//(ZCH== 1) : Positive zero-crossing
			//(ZCH==-1) : Negative zero-crossing
			//(ZCV!= 0) : Horizontal zero-crossing
	ZCaux = (VP || VN || H);
	ZC = ZCaux;
	return ZC*255; // Se deberia poder hacer esto pero el compilador no lo admite !!!   ZCH==1 || ZCH==-1 || ZCV!=0;


}

/**Image***************************\
		  MaxDistanceFromLine
\**********************************/
double Image::MaxDistanceFromLine(PixelVector PV, Line SL)
{
	PixelVector::iterator PVit;
	double MaxDistance = 0.0;
	double AuxDistance;

	for (PVit = PV.begin();PVit != PV.end();PVit++){
		AuxDistance = SL.EuclideanDistance(*PVit);
		if (AuxDistance > MaxDistance) MaxDistance = AuxDistance;
	}
	return MaxDistance;
}
