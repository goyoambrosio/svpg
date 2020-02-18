//#include <SVA/Image.h>
#include <CVL/Image_lpr.h>

#include <string>
#include <algorithm>

#include <math.h>
#include <ipl.h>
#include <fstream.h>

using namespace GAC;
using namespace std;





/********Image_lpr*************************************************************\
		
  	  
	                    Class Image_lpr


\******************************************************************************/



/********Image_lpr*************************************************************\
	                    Class Region
\******************************************************************************/

///////////////////////////
//   Constructors
///////////////////////////
Image_lpr::Region::Region()
{
	dInitX=dInitY=dOffsetX=dOffsetY=dArea=0;
	//dImage=NULL;
}		


//Image_lpr::Region::Region(int xinit,int yinit,int xoffset,int yoffset,long area,Image image)
Image_lpr::Region::Region(int xinit,int yinit,int xoffset,int yoffset,long area)
{
	dInitX=xinit;
	dInitY=yinit;
	dOffsetX=xoffset;
	dOffsetY=yoffset;
	dArea=area;

	//dImage = new(Image)(image);
	//dImage = image;
}


Image_lpr::Region::~Region()
{
	//if (dImage!=NULL)
		//dImage->~Image();
	//dImage.~Image();
}


//void Image_lpr::Region::SetSubImage(Image image)
//{
	//if (dImage!=NULL) 
	//	dImage->~Image();
	
	//if ((image.Height()>(dInitY+dOffsetY)) || (image.Width()>(dInitX+dOffsetX))) {
		//UcharMatrix Subset=image.GetBlock(dInitY,dInitX,dOffsetY,dOffsetX);
		//dImage = new(Image)(Subset);
	//	Image Subset((UcharMatrix) image.GetBlock(dInitY,dInitX,dOffsetY,dOffsetX));
	//	dImage = Subset;
	//}
	//else
		//dImage = new(Image)(image);
	//	dImage = image;

	//(*dImage) = (UcharMatrix)dImage->SetAround(5,5,0);
	//dImage.SetAround(5,5,0);

//}

///////////////////////////
//Visualization
///////////////////////////
void Image_lpr::Region::Show()
{
	printf("Region [  (%3d,%3d)  ,  (%3d,%3d)  ] -> Area: %5d\n",dInitX,dInitY,dOffsetX,dOffsetY,dArea);
	//if (dImage) dImage->jaaShow();
	//if (dImage.Height() && dImage.Width()) dImage.jaaShow();
}




/********Image_lpr*************************************************************\
	                    Class RegionVector
\******************************************************************************/
Image_lpr::RegionVector::RegionVector()
{

}

Image_lpr::RegionVector::~RegionVector()
{

}

//Visualization
void Image_lpr::RegionVector::Show()
{
	RegionVector::const_iterator it;
	Region Rx;
	for (it = begin(); it != end(); it++)
	{
		Rx = *it;
		Rx.Show();	
	}

}



/********Image_lpr*************************************************************\
	                    Class Segment
\******************************************************************************/

/**Segment*****************************\
		       operator< 
\*************************************

bool Image_lpr::Segment::operator< (Segment &S){
    return Label < S.Label;
}


/**Segment*****************************\
		   EndPointDistance
\**************************************
// Computes the minimum distance between the nearest endpoints of segments

double Image_lpr::Segment::EndPointDistance(Segment& S)
{
	return ((Image::Segment)(*this)).EndPointDistance(S);
}

/**Segment*****************************\
		   MidPointDistance
\**************************************
// Computes the minimum distance between midpoint of segments

double Image_lpr::Segment::MidPointDistance(Segment& S)
{
	return ((Image::Segment)(*this)).MidPointDistance(S);
}

/**ImgSegment**************************\
		   OverlapMod
\**************************************
//Computes the module of the overlapping between this segment and the perpendicular 
//projection of S over this segment
double Image_lpr::Segment::OverlapMod(Segment& S)
{
	return ((Image::Segment)(*this)).OverlapMod(S);
}
/**Segment*****************************\
		       Show
\**************************************
void Image_lpr::Segment::Show()
{
    printf("%i:(%.30g,%.30g)->(%.30g,%.30g):[%.30g,%.30g]\n",Label,p().x(),p().y(),q().x(),q().y(),d(),Sigma());
//	cout << Label << ":" << p() << "->" << q() << endl;
}


/**Segment*****************************\
		  operator =
\**************************************

const Image_lpr::Segment &Image_lpr::Segment::operator= (const Image_lpr::Segment& S) {
/memcpy(this,&S,sizeof(Image_lpr::Segment));
	//Image::Segment(*this)=Image::Segment(S);
	p   = S.;
	d_d = S.d_d;
	d_sigma = S.d_sigma;
	return *this;
}



/**SegmentVector********************\
		        Show
\***********************************
void Image_lpr::SegmentVector::Show()
{
	SegmentVector::const_iterator it;
	Segment S;
	for (it = begin(); it != end(); it++)
	{
		S = *it;
		S.Show();	
	}
}
*/



/********Image_lpr*************************************************************\
	                    Constructors
\******************************************************************************/

//Inicializacion de atributos estatiticos para la clase
MIL_ID	Image_lpr::sys	= 0;
MIL_ID	Image_lpr::ap	= 0;
MIL_ID	Image_lpr::disp	= 0;
long	Image_lpr::cnt	= 0;

void Image_lpr::initialize(int numRows,int numCols)
{
	if (!cnt) {
		MappAllocDefault (M_SETUP, &ap, &sys, M_NULL, M_NULL, M_NULL);
		MdispAlloc(sys,1,M_DISPLAY_SETUP,M_DEFAULT,&disp);
	}	
	cnt++;
	//Reservar memoria para una imagen MIL
	MbufAlloc2d (sys, numCols, numRows, 8, M_IMAGE + M_DISP, &img);
/*
#ifdef _USE_INTEL_IPL_
	iplImg = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is uchar
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      numCols, numRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

	iplImg->imageData = (char *) pM;
#endif
*/
};


Image_lpr::Image_lpr ():Image()
{
	initialize(1,1);
};

Image_lpr::Image_lpr (UcharMatrix  &M):Image(M)
{
	initialize(M.Depth(),M.Width());
};

Image_lpr::Image_lpr (size_t Rows, size_t Cols):Image(Rows,Cols)
{
	initialize(Rows,Cols);

};

Image_lpr::Image_lpr (DoubleMatrix &M):Image(M)
{
	initialize(M.Depth(),M.Width());

};

Image_lpr::Image_lpr (FloatMatrix  &M):Image(M)
{
	initialize(M.Depth(),M.Width());

};

Image_lpr::Image_lpr (BoolMatrix   &M):Image(M)
{
	initialize(M.Depth(),M.Width());

};

Image_lpr::~Image_lpr()
{
	//cnt--;
	
	MbufFree(img);
	if (!cnt) {
	//	MdispFree(disp);
	//	MsysFree(sys);
	//	MappFree(ap);
	}
	//*/
};



/********Image_lpr*************************************************************\
	                    Metodos
\******************************************************************************/
/**Image_lpr***************************\
	    Show
\**************************************/

void Image_lpr::Show()
{
	
	size_t cols,rows;

	//MbufInquire(this->img,M_SIZE_X,&cols);
	//MbufInquire(this->img,M_SIZE_Y,&rows);

	//Reservar memoria para una imagen
	//if ((cols!=NumCols) || (rows!=NumRows)) {
		MbufFree (img);
		MbufAlloc2d (sys, NumCols, NumRows, 8, M_IMAGE + M_DISP, &img);
	//}
	
	//Poner un buffer de uchar en una imagen MIL
	MbufPut(img,(uchar *)pM);
	
	//Asignar una imagen a un display o ventana
	MdispSelect(disp,img);

	//MbufFree(img);
}


/***Image_lpr***********************************************\
		operator ():	Devuelve un pixel de la imagen
						Referencia un pixel de la imagen
\***********************************************************/
Image_lpr::Pixel Image_lpr::operator () (size_t Row,size_t Col)
{
	Image_lpr::Pixel Px(Row,Col,pM[Row*NumCols + Col]);
	return Px;
};

/*
unsigned char& Image_lpr::operator  ()(Image_lpr::Pixel Px)
{
	//return &(pM[(Px.Row()*NumCols)+Px.Col()]);
	return (pRow1[Px.Row()][Px.Col()]);
};
*/
/*Image_lpr		&Image_lpr::operator=	(const Image_lpr &I)
{
	//return (Image_lpr &)Image::operator =(I);
	Image::operator =(I);


}
*/


/***Image_lpr***********************************************\
		getPixel:	Devuelve el valor de gris del pixel indexado
					por x e y
\***********************************************************/
unsigned char	 Image_lpr::getPixel			(size_t x,size_t y)
{
#ifdef _USE_INTEL_IPL_
	unsigned char p;
	iplGetPixel(iplImg,x,y,&p);
	return p;
#else
	return (*this)[y][x];
#endif
}


/***Image_lpr***********************************************\
		putPixel:	Graba el valor de gris del pixel indexado
					por x e y
\***********************************************************/
void	Image_lpr::putPixel			(size_t x,size_t y,unsigned char p)
{
#ifdef _USE_INTEL_IPL_
	iplPutPixel(iplImg,x,y,&p);
#else
	(*this)[y][x]= p;
#endif
}


/***Image_lpr***********************************************\
		clFlood:Algoritmo de inundacion de regiones
				Utilizando metodos de clase
\***********************************************************/

IntMatrix Image_lpr::clFlood(Image_lpr::Pixel Seed,int RegionId)
{
	//Donde vamos a asignar las regiones
	IntMatrix Region(NumRows,NumCols);
	BoolMatrix IsBorder(NumRows,NumCols);
	//Donde vamos a almacenar los bordes actuales
	Image_lpr::PixelVector Borders;
	Image_lpr::Pixel PixelActual;
	Image_lpr::Pixel Vecino;
	int f,c,df,dc;
	long ind;
	
	
	//Copiamos las semillas en el array destino e inicializamos los arrays
	Region.SetAll(0);
	IsBorder.SetAll(false);
	Borders.push_back(Seed);
	IsBorder(Seed.Row(),Seed.Col()) = true;

	ind=0;
	while (!Borders.empty()) {
		//Mientras haya bordes sin explorar hacer
		//Hacemos el primer borde pixel actual de observacion,
		//y lo marcamos como que ya no es un borde
		PixelActual = Borders.front();
		Borders.erase(Borders.begin());
		IsBorder(PixelActual.Row(),PixelActual.Col()) = false;
		if (PixelActual.Level == Seed.Level) {
			//El pixel pertenece a la region y lo añadimos a ella
			ind++;
			Region(PixelActual.Row(),PixelActual.Col()) = RegionId;
			for (df=-1;df<=1;df++)
				for (dc=-1;dc<=1;dc++) {
					f = PixelActual.Row() + df;c = PixelActual.Col() + dc;
					//Se analizan los 8 vecinos, pero no el pixel central
					//if ((abs(df)+abs(dc)) && Between(f,1,NumRows) && Between(c,1,NumCols)) {
					//Se analizan los 4 vecinos, pero no el pixel central
					if ((abs(df)+abs(dc)) && !(df && dc) && BETWEEN(f,1,NumRows) && BETWEEN(c,1,NumCols)) {
						//Si esta dentro de la imagen
						Vecino = (*this)(f,c);	//Sobrecarga de operador () para Pixel
						if (!Region(f,c)) {		//No esta asignado
							if (!IsBorder(f,c)) {
								Borders.push_back(Vecino);
								IsBorder(f,c) = true;
							}
						}
					}
				}
			//end for(df)
		} //end if(level)
	} // end while

	return Region;
}




/***Image_lpr***********************************************\
		Flood:	Algoritmo de inundacion de regiones
				Sin utilizar los Pixel vector para almacenar
				los Bordes
\***********************************************************/

IntMatrix Image_lpr::Flood(Image_lpr::Pixel Seed,int RegionId)
{
	//Variables utilizadas
	IntMatrix Region(NumRows,NumCols);
	BoolMatrix Borders(NumRows,NumCols);
	//unsigned char *a;								//Imagen de origen (a)
	//unsigned char *ASIG;							//Pixeles asignados
	//bool *Borders;									//Pixeles bordes de region, y de destino
	int *row,*col,*b;								//Almacenan los indices de los bordes
	long binit=0,bfin=0;
	//int *MED;										//media de cada region
	//long *SUM, *NP;									//suma y numero de puntos de cada region
	int sizeX,sizeY,i,f,c,df,dc,p,dp,cand,fin,asig,m,total,nf,nc;
	long ind=0;
	
	// Obtenemos el tamaño de las imagenes
	sizeX = NumCols;
	sizeY = NumRows;

	//creamos los arrays necesarios
	//if ((a = (uchar *) malloc (sizeX *sizeY * sizeof(uchar))) == NULL) return -1;
	//a = pM;
	//if ((b = (int *) malloc (sizeX *sizeY * sizeof(int))) == NULL) exit(-1);
	//b = Region.jaaData();
	//if ((ASIG = (uchar *) malloc (sizeX *sizeY * sizeof(uchar))) == NULL) return -1;
	//if ((Borders = (bool *) malloc (sizeX *sizeY * sizeof(bool))) == NULL) exit(-1);
	//if ((MED = (int *) malloc (N * sizeof(int))) == NULL) return -1;
	//if ((SUM = (long *) malloc (N * sizeof(long))) == NULL) return -1;
	//if ((NP = (long *) malloc (N * sizeof(long))) == NULL) return -1;
	if ((row = (int *) malloc (sizeX *sizeY * sizeof(int))) == NULL) exit(-1);
	if ((col = (int *) malloc (sizeX *sizeY * sizeof(int))) == NULL) exit(-1);

	
	//for (ind=0;ind<sizeX*sizeY;ind++) b[ind]=0;
	//memset(b,0,sizeX*sizeY);
	Region.SetAll(0);
	Borders.SetAll(false);
	//memset(Borders,false,sizeX*sizeY);
	
	//Introducimos la semilla como primer borde de la region
	row[bfin]=Seed.Row();col[bfin++]=Seed.Col();
	Borders(row[binit],col[binit]) = true;
	
	// Bucle principal de la segmentacion
	total =0;
	fin = 0;
	asig =0;
	while (binit<bfin) {
		f = row[binit];c=col[binit++];
		//p = (f-1)*sizeX+(c-1);
		//Borders[p]=false;
		//Hay que comprobar el valor del pixel para añadirlo o no a la region
		//printf("Analizando pixel [%d,%d]\n",f,c);
		//if (a[p]==Seed.Level) {
		if ((*this)(f,c).Level==Seed.Level) {
			//El pixel pertenece a la region y lo añadimos a ella
			ind++;
			//b[p] = RegionId;
			Region(f,c) = RegionId;
			//printf("Pixel [%d,%d] pernetece a la region (%d)\n",f,c,ind);
			//Ahora comprobamos cada uno de los vecinos
			for (df=-1;df<=1;df++)
				for (dc=-1;dc<=1;dc++) {
					//dp = ((f+df-1)*sizeX)+c+dc-1;
					nf=f+df;nc=c+dc;
					if ((df || dc) && !(df && dc)) {
						//Comprobamos que no es el pixel central ni uno de los vecinos diagonales
						//if ((dp>0) && ((f+df)<=sizeY) && ((c+dc)<=sizeX)) {
						if (BETWEEN(nf,1,NumRows) && BETWEEN(nc,1,NumCols)) {
							//Comprobamos que esta dentro de la imagen
							//if (!b[dp]) {			//No esta asignado
							if (!Region(nf,nc)) {
								if (!Borders(nf,nc)) {	//No esta marcado como borde
									row[bfin]=nf;col[bfin++]=nc;
									Borders(nf,nc) = true;
									//printf("Borde encontrado, vecino [%d,%d],%d\n",f+df,c+dc,bfin-binit);
								}	
							}
						}
					}
				}
			//end for(df)
		}	//end if (level)
	}	//end while


	//free(Borders);
	free(col);
	free(row);

	return Region;

}



/***Image_lpr***********************************************\
	iplFlood:Algoritmo de inundacion de regiones
			 Utilizando imagenes intel
\***********************************************************/

Image_lpr Image_lpr::iplFlood(Image_lpr::Pixel Seed,int RegionId)
{

	Image_lpr Region(NumRows,NumCols);
	int VecinoX[] = {0,-1, 1,1, 0, 1,-1,-1};
	int VecinoY[] = {1,-1, 0,1,-1,-1, 0, 1};
	int *Bx;
	int *Berrugay;
	int binit=0,bfin=0;
	char isB[1]={1};
	int x,y,dx,dy;
	int sizeX,sizeY,ArraySize;
	unsigned char pixel[1];
	unsigned char asig[1];
	int  Region_Id[1]={RegionId};
	long area=0;
	
	//////////////////////////
	// Utilizando Intel IPL
	//////////////////////////
	IplImage      *I;
    IplImage      *J;
	IplImage	  *Borders;

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
      IPL_DEPTH_8U,                // data type is int
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_DWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled
                                    
    
	Borders = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_1U,                 // data type is uchar
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_DWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

	/// allocate image data without filling
    //iplAllocateImage( J      , 1, 0 );   
	iplAllocateImage( Borders, 1, 0 );   


    Region.SetAll(0);
	J->imageData = (char*)Region.pM;
	I->imageData = (char*)pM;


	sizeX=NumCols;
	sizeY=NumRows;
	ArraySize = 2*(sizeX +sizeY);
	if ((Bx = (int *) malloc ( ArraySize * sizeof(int))) == NULL) exit(-1);
	
	if ((Berrugay = (int *) malloc ( ArraySize * sizeof(int))) == NULL) exit(-1);

	
	
	//Introducimos la semilla como primer borde de la region
	Berrugay[bfin]=Seed.Row()-1;
	Bx[bfin++]=Seed.Col()-1;
	iplPutPixel(Borders,Bx[binit],Berrugay[binit],isB);
		
	// Bucle principal de la segmentacion
	while (binit!=bfin) {
		y = Berrugay[binit];x=Bx[binit];binit=(binit+1)%ArraySize;
		iplGetPixel(I,x,y,pixel);
		if (*pixel==Seed.Level) {
			//El pixel pertenece a la region y lo añadimos a ella
			area++;
			iplPutPixel(J,x,y,Region_Id);
			//Ahora comprobamos cada uno de los vecinos
			for (int *vx=VecinoX,*vy=VecinoY;vx<VecinoX+8,vy<VecinoY+8;vx+=1,vy+=1) {
				dx=x+*vx;dy=y+*vy;
				if (BETWEEN(dx,0,sizeX-1) && BETWEEN(dy,0,sizeY-1)) {
					//Comprobamos que esta dentro de la imagen
					//if (!b[dp]) {			//No esta asignado
					iplGetPixel(J,dx,dy,asig);
					if (!*asig) {
						iplGetPixel(Borders,dx,dy,isB);
						if (!*isB) {	//No esta marcado como borde
							Berrugay[bfin]=dy;Bx[bfin]=dx;bfin=(bfin+1)%ArraySize;
							iplPutPixel(Borders,x,y,isB);
							*isB=1;iplPutPixel(Borders,dx,dy,isB);
							//printf("Borde encontrado, vecino [%d,%d],%d\n",f+df,c+dc,bfin-binit);
						}	
					}
				}
			}
			
		}	//end if (level)
	}	//end while


	
	free(Bx);
	free(Berrugay);
	
	
	iplDeallocateImage(Borders);
	iplDeallocate(I,IPL_IMAGE_HEADER);
	iplDeallocate(J,IPL_IMAGE_HEADER);


	cout << "Area de la region: " << area << endl;
	Region *= 255;
	Region.Show();
	Region /= 255;
	return Region;
}







/***Image_lpr***********************************************\
	ipdFloodBis:Algoritmo de inundacion de regiones
				Utilizando imagenes intel
\***********************************************************/

Image_lpr::Region Image_lpr::iplFloodBis(IplImage *source,IplImage *dest,int SeedX,int SeedY,long Max)
{
	Region Reg;
	int VecinoX[] = {0,-1, 1,1, 0, 1,-1,-1};
	int VecinoY[] = {1,-1, 0,1,-1,-1, 0, 1};
	int *Bdx;
	int *Bdy;
	int binit=0,bfin=0;
	char isB[1]={1};
	int x,y,dx,dy;
	int sizeX,sizeY,ArraySize;
	unsigned char pixel[1],seed[1];
	unsigned char asig[1];
	int  Region_Id[1]={255};
	long area=0;
	int xinit=0,yinit=0,xfin=0,yfin=0;
	IplImage *src=(IplImage *)source,*dst=(IplImage *)dest;
	
	//////////////////////////
	// Utilizando Intel IPL
	//////////////////////////
	IplImage	  *Borders;

    
	Borders = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_1U,                 // data type is uchar
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

	iplAllocateImage( Borders, 1, 0 );   


    //Image_lpr Fuente(NumRows,NumCols);
	//Fuente.Copy((const unsigned char *)src->imageData);
	//Fuente.jaaShow();
	
	sizeX=NumCols;
	sizeY=NumRows;
	ArraySize = 2*(sizeX +sizeY);
	if ((Bdx = (int *) malloc ( ArraySize * sizeof(int))) == NULL) exit(-1);
	if ((Bdy = (int *) malloc ( ArraySize * sizeof(int))) == NULL) exit(-1);

	
	//Introducimos la semilla como primer borde de la region
	xinit=xfin=Bdx[bfin]=SeedX;
	yinit=yfin=Bdy[bfin++]=SeedY;
	iplGetPixel(src,SeedX,SeedY,seed);
	iplPutPixel(Borders,Bdx[binit],Bdy[binit],isB);
		
	// Bucle principal de la segmentacion
	while (binit!=bfin) {
		y = Bdy[binit];x=Bdx[binit];binit=(binit+1)%ArraySize;
		iplGetPixel(src,x,y,pixel);
		if (*pixel==*seed) {
			//El pixel pertenece a la region y lo añadimos a ella
			//actualizando todos los delimitadores
			xinit = min(xinit,x);yinit = min(yinit,y);
			xfin  = max(xfin ,x);yfin  = max(yfin ,y);
			area++;
			//if (area>=Max) break;
			iplPutPixel(dst,x,y,Region_Id);
			//Ahora comprobamos cada uno de los vecinos
			for (int *vx=VecinoX,*vy=VecinoY;vx<VecinoX+8,vy<VecinoY+8;vx+=1,vy+=1) {
				dx=x+*vx;dy=y+*vy;
				if (BETWEEN(dx,0,sizeX-1) && BETWEEN(dy,0,sizeY-1)) {
					//Comprobamos que esta dentro de la imagen
					//if (!b[dp]) {			//No esta asignado
					iplGetPixel(dst,dx,dy,asig);
					if (!*asig) {
						iplGetPixel(Borders,dx,dy,isB);
						if (!*isB) {	//No esta marcado como borde
							Bdy[bfin]=dy;Bdx[bfin]=dx;bfin=(bfin+1)%ArraySize;
							iplPutPixel(Borders,x,y,isB);
							*isB=1;iplPutPixel(Borders,dx,dy,isB);
							//printf("Borde encontrado, vecino [%d,%d],%d\n",f+df,c+dc,bfin-binit);
						}	
					}
				}
			}
			
		}	//end if (level)
	}	//end while


	
	free(Bdx);
	free(Bdy);
	
	
	iplDeallocateImage(Borders);
	
	
	Reg.InitX()		=  xinit;
	Reg.InitY()		=  yinit;
	Reg.OffsetX()	=  xfin-xinit;
	Reg.OffsetY()	=  yfin-yinit;
	Reg.Area()		=  area;
	return Reg;
}











/***Image_lpr***********************************************\
		GlobalThreshold: Umbral global de la imagen
\***********************************************************/

Image_lpr Image_lpr::GlobalThreshold(unsigned char Threshold)
{
	
	Image_lpr GlobalThresholdImage(NumRows,NumCols);

	//GlobalThresholdImage = (UcharMatrix)(((*this)>Threshold)*255);

	///*
	//////////////////////////
	// Utilizando Intel IPL
	//////////////////////////
	IplImage      *I;
    IplImage      *J;

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

	//iplBlur(J,J,3,3,1,1);
	iplThreshold(I,J,(int) Threshold);
	//iplClose(J,J,1);
	//iplOpen(J,J,3);
	//iplErode(J,J,1);
	//iplDilate(J,J,1);
	
	

    
	//GlobalThresholdImage.Resize(NumRows,NumCols);
    GlobalThresholdImage.pM = (unsigned char *)J->imageData;
	//*/

	return GlobalThresholdImage;

};



/**************************************************************************\
* Name      : getSegment
* Member of : Image_lpr
* Purpose   : Obtein the segment in the line p=x*sin(a) + y*cos(a)
* Returns   : The segment
* Parameters: ROI ,distance to origin p, angle a, tolarance, max_d and umbral
* Notes     : 
* Author    : JAA
* Date      : 25.05.00
* Modified  : 
\**************************************************************************/
Image_lpr::Segment Image_lpr::getSegment			(int x_ini,int x_end,int y_ini,int y_end,float p,float a,int tol,int max_d,int umbral)
{
	
#define P_EVAL_Y_L(x,y) (((y)>=y_ini) && (pM[(y)*NumCols+(x)]>128))
#define P_EVAL_Y_H(x,y) (((y)<y_end) && (pM[(y)*NumCols+(x)]>128))
#define P_EVAL_X_L(x,y) (((x)>=x_ini) && (pM[(y)*NumCols+(x)]>128))
#define P_EVAL_X_H(x,y) (((x)<x_end) && (pM[(y)*NumCols+(x)]>128))

	Segment seg(0,0,0,0,0);
	register x, y, i;
	int sx_ini,sx_end,sy_ini,sy_end,last_x,last_y;
	float sin_a,cos_a;
	SegmentVector sv;
	int cnt=1;
	int length=0;
	bool eval;

	a=(a*-1)+90;
	sin_a=sin(a*PI/180);
	cos_a=cos(a*PI/180);
	//Buscamos por toda la imagen
	if (!(fabs(90-a)<45.0)) {
		//Recorremos en el eje de las y
		//printf("\nRecorriendo las Y\n");
		y=y_ini;
		while (y<y_end) {
			x=Round((p-(y*sin_a))/cos_a);
			if (BETWEEN(x,x_ini,x_end)) {
				eval = P_EVAL_X_L(x,y);
				for (i=1;(i<=tol) && !eval;i++) {
					eval |= P_EVAL_X_L(x-i,y);
					eval |= P_EVAL_X_H(x+i,y);
				}
				//if (P_EVAL_X_L(x,y) || P_EVAL_X_L(x-1,y) || P_EVAL_X_L(x-2,y) || P_EVAL_X_H(x+1,y) || P_EVAL_X_H(x+2,y)) {
				if (eval) {
					if (!length) {
						sx_ini=x;sy_ini=y;
					}
					last_x=x;last_y=y;
					length++;
				}
				else if (!((y-last_y)<=max_d) && length) {
					eval = P_EVAL_X_L(last_x,last_y);
					for (i=1;(i<=tol) && !eval;i++) {
						eval |= P_EVAL_X_L(last_x-i,last_y);
						eval |= P_EVAL_X_H(last_x+i,last_y);
					}
					//if ((pM[last_y*NumCols+last_x] || ((last_x>x_ini) && pM[last_y*NumCols+last_x-1]) || ((last_x<x_end) && pM[last_y*NumCols+last_x+1])) 
					if (eval) {
						length = hypot(sx_ini-last_x,sy_ini-last_y);
						if (length>=umbral) {
							//Tenemos que introducir el segmento
							//if (sx_ini<last_x)
								sv.push_back(Segment(length,sx_ini,sy_ini,last_x,last_y,p,a));
							//else
							//	sv.push_back(Segment(length,last_x,last_y,sx_ini,sy_ini));
							cnt++;
						}
					}
					length=0;
					last_x=x;last_y=y;
				}
			}
			
			y++;
		} //end while(x)

		if (y==y_end) {
			length=hypot(sx_ini-last_x,sy_ini-last_y);
			if (length>=umbral) {
				//if (sx_ini<last_x)
					sv.push_back(Segment(length,sx_ini,sy_ini,last_x,last_y,p,a));
				//else
				//	sv.push_back(Segment(length,last_x,last_y,sx_ini,sy_ini));
				cnt++;
			}
		}
	} //end if(a)
	else {
		//Recorremos en el eje de las x
		//printf("\nRecorriendo las X\n");
		x=x_ini;
		while (x<x_end) {
			y=Round(((p-(x*cos_a))/sin_a));
			if (BETWEEN(y,y_ini,y_end)) {
				// Si el pixel, el superior o el inferior son >0 seguimos con la linea
				eval = P_EVAL_Y_L(x,y);
				for (i=1;(i<=tol) && !eval;i++) {
					eval |= P_EVAL_Y_L(x,y-i);
					eval |= P_EVAL_Y_H(x,y+i);
				}
				//if (P_EVAL_X_L(x,y) || P_EVAL_X_L(x-1,y) || P_EVAL_X_L(x-2,y) || P_EVAL_X_H(x+1,y) || P_EVAL_X_H(x+2,y)) {
				if (eval) {
					if (!length) {
						sx_ini=x;sy_ini=y;
					}
					last_x=x;last_y=y;
					length++;
					
				}
				else if (!((x-last_x)<=max_d) && length) {
					//Si el corte es demasiado grande, comprobamos si la ultima linea analizada cumple los
					//requisitos, si es asi la metemos en el vector
					eval = P_EVAL_Y_L(last_x,last_y);
					for (i=1;(i<=tol) && !eval;i++) {
						eval |= P_EVAL_Y_L(last_x,last_y-i);
						eval |= P_EVAL_Y_H(last_x,last_y+i);
					}
					//if ((pM[last_y*NumCols+last_x] || ((last_x>x_ini) && pM[last_y*NumCols+last_x-1]) || ((last_x<x_end) && pM[last_y*NumCols+last_x+1])) 
					if (eval) {
						length = hypot(sx_ini-last_x,sy_ini-last_y);
						if (length>=umbral) {
							//Tenemos que introducir el segmento
							//if (sy_ini<last_y)
								sv.push_back(Segment(length,sx_ini,sy_ini,last_x,last_y,p,a));
							//else
							//	sv.push_back(Segment(length,last_x,last_y,sx_ini,sy_ini));
							//cnt++;
						}
					}
					length=0;
					last_x=x;last_y=y;
				}
			}
			x++;
		} //end while(x)

		//Si llegamos a los limites de la ROI, tenemos que ver si dejamos la ultima linea
		//analizada sin meter.
		if (x==x_end) {
			length=hypot(sx_ini-last_x,sy_ini-last_y);
			if (length>=umbral) {
				//if (sy_ini<last_y)
					sv.push_back(Segment(length,sx_ini,sy_ini,last_x,last_y,p,a));
				//else
				//	sv.push_back(Segment(length,last_x,last_y,sx_ini,sy_ini));
				cnt++;
			}
		}
	}

	sv.Show();
	if (sv.size()>0) {
		Image_lpr::Segment *it = max_element(sv.begin(),sv.end());
		seg=*it;
	}

	#undef P_EVAL_Y_L(x,y)
	#undef P_EVAL_Y_H(x,y)
	#undef P_EVAL_X_L(x,y)
	#undef P_EVAL_X_H(x,y)

	return seg;


}


/**************************************************************************\
* Name      : houghtLinesP
* Member of : Image_lpr
* Purpose   : Obtain lines using Hought transform (Polar coordenates)
* Returns   : SegmentVector with the finded segments
* Parameters: x_ini,x_end,y_ini,y_end: ROI, p_min,p_max,a_min,a_max Param space range
* Notes     : 
* Author    : JAA
* Date      : 25.05.00
* Modified  : 
\**************************************************************************/
Image_lpr::SegmentVector Image_lpr::houghtLinesP(int x_ini,int x_end,int y_ini,int y_end,float p_min,float p_max,float a_min,float a_max,float p_interval, float a_interval,int dup_tol, int max_dis, int seg_tol,int umbral)
{
	int p_size=(abs(p_max-p_min)/p_interval)+1,a_size=(abs(a_max-a_min)/a_interval)+1;
	SegmentVector segments;
	Matrix<long> param_s(p_size,a_size);
	param_s.SetAll(0);

	
	//Obtener el modulo y la dirección del gradiente.
	//FloatMatrix g_dir(NumRows,NumCols);
	//UcharMatrix g_mag(NumRows,NumCols);
	//getGradient(g_dir,g_mag);
	
	
	SegmentVector vl;
	Segment line;

	float *sens,*coss;
	register p,a,x,y;
	
	sens	= (float *) malloc (a_size*sizeof(float));
	coss	= (float *) malloc (a_size*sizeof(float));

	
	//Table with cos and sen values
	a_min+=90;a_max+=90;
	float angle=a_min;
	for (a=0;a<a_size;a++) {
		sens[a] = sin((angle*PI)/180);
		coss[a] = cos((angle*PI)/180);
		angle+=a_interval;
	}


	float p_eval,dir;
	for (y=y_ini;y<y_end;y++) {
		for (x=x_ini;x<x_end;x++) {
			/*
			if (g_mag[y][x]>0) {
				dir = g_dir[y][x];
				if (dir>=180) dir-=360;
				dir*=-1;
				if (dir>90) dir-=180;
				else if (dir<=-90) dir+=180;
				a=(dir-a_min-90)/a_interval;
				if (BETWEEN(dir,a_min,a_max)) {
					p_eval=x*coss[a]+y*sens[a];
					printf("\n[%3d,%3d] -> (%3d,%g,%d,%f)", x,y,g_mag[y][x],dir,a,p_eval);
					param_s[Round((p_eval-p_min)/p_interval)][a]++;
				}
			}
			*/
			
			if (pM[y*NumCols+x]>128) {
				for (a=0;a<a_size;a++) {
					p_eval=x*coss[a]+y*sens[a];
					//printf("\nValor (%d,%d) [%d,%4.2f]",x,y,p_eval,atan(sens[a]/coss[a]));
					if (BETWEEN(p_eval,p_min,p_max)) {
						param_s[Round((p_eval-p_min)/p_interval)][a]++;
					}
				}
			}
			//*/
		}
	}

	
	//cout << param_s;
	long votos;
	float pos,ang;
	for (p=0;p<p_size;p++)
		for (a=0;a<a_size;a++) { 
			votos = param_s[p][a]*3/2;
			if (votos>umbral) {
			//if (votos) {
				pos=(p*p_interval)+p_min;
				ang=(a*a_interval)+a_min;
				ang-=90;ang*=-1;
				//printf("\nLinea en [%-4.2f,%4.2f]. Coincidencias=%d.",pos,ang,votos);
				
				//Metemos las lineas en un vector para analizarlas
				line=Segment(votos,pos,ang,0,0);
				vl.push_back(line);
				
			}
		}

	/************  Eliminación de lineas multiples antes de sacar los segmentos ************/
	cout << "\nNumero de lineas: " << vl.size() << endl;
	if (vl.size()>0) {
		sort(vl.begin(),vl.end());

		//vl.Show();
		
		//Ahora tenemos que eliminar los duplicados
		Point2D pointx,pointy;
		SegmentVector::iterator pxs,pys;
		Segment xs,ys;
		float max_d=hypot(dup_tol*a_interval,2*dup_tol*p_interval);
		for (pxs=vl.end()-1;pxs>=vl.begin();pxs--) {
			xs=*pxs;pointx = xs.p();
			//cout << "\nDistancia maxima permitida(Linea " << *xs << "): " << max_d << endl;
			//cout << "\nxs: " << *xs;
			for (pys=pxs+1;pys<vl.end();pys++) {
				float d;   //=point.Distance(pys->p());
				ys=*pys;pointy=ys.p();
				d=pointy.Distance(pointx);
				//cout << " ys: " << *ys;
				if (d<max_d) {
					//Ahi que borrar la linea de la posicion X
					//cout << "\nborrando Linea " << pointx << "  " << pointy << " Distancia: "  << d;
					vl.erase(pxs);
					break;
				}
			}
		}
		
		//vl.Show();
		printf("\n");
		for (pxs=vl.begin();pxs<vl.end();pxs++) {
			p=pxs->p().x();
			a=pxs->p().y();
			line = getSegment(x_ini,x_end,y_ini,y_end,p,a,max_dis,seg_tol,umbral);
			if (line.Label>0) {
				line.Label = line.p().x();
				segments.push_back(line);
				
				////////////////////////////////////////////////////////////////////
				//Dibujar las lineas en la imagen
				a=(a*-1)+90;
				float sin_a=sin(a*PI/180);
				float cos_a=cos(a*PI/180);
				
				if (!(fabs(90-a)<45.0)) {
					if (line.p().y()<line.q().y()) {
						for (y=line.p().y();y<line.q().y();y++) {
							x=Round((p-(y*sin_a))/cos_a);
							pM[y*NumCols+x]=255;
							
						}
					} 
					else {
						for (y=line.q().y();y<line.p().y();y++) {
							x=Round((p-(y*sin_a))/cos_a);
							pM[y*NumCols+x]=255;
							
						}
					}
				}
				else {
					for (x=line.p().x();x<line.q().x();x++) {
						y=Round((p-(x*cos_a))/sin_a);
						pM[y*NumCols+x]=255;
					}
				}
				////////////////////////////////////////////////////////////////////
				

			}
		}
		sort(segments.begin(),segments.end());
		//segments.Show();
	}
	//*/
		
	
		
	/*********************** Eliminación de segmentos duplicados **********************
	if (vl.size()>0) {
		SegmentVector p_as;			
		SegmentVector sames;
		float max_d,d;
		SegmentVector::iterator pxs,pys,pss,pp_as;
		Point2D pointx,pointy;
		Segment xs,ys,ss;
		bool ins;
		

		sort(vl.begin(),vl.end());

		//vl.Show();
		
		//Ahora tenemos que eliminar los duplicados
		max_d=hypot(dup_tol*a_interval,2*dup_tol*p_interval);
		for (pxs=vl.end()-1;pxs>=vl.begin();pxs--) {
			xs=*pxs;pointx = xs.p();
			//cout << "\nDistancia maxima permitida(Linea " << *xs << "): " << max_d << endl;
			//cout << "\nxs: " << *xs;
			for (pys=pxs+1;pys<vl.end();pys++) {
				float d;   //=point.Distance(pys->p());
				ys=*pys;pointy=ys.p();
				d=pointy.Distance(pointx);
				//cout << " ys: " << *ys;
				if (d<max_d) {
					//Ahi que borrar la linea de la posicion X
					//cout << "\nborrando Linea " << pointx << "  " << pointy << " Distancia: "  << d;
					vl.erase(pxs);
					break;
				}
			}
		}
		
		
		max_d=dup_tol*4;
		for (pxs=vl.begin();pxs<vl.end();pxs++) {
			//cout << "\nAnalizando linea " << *pxs ;
			p=pxs->p().x();
			a=pxs->p().y();
			line = getSegment(x_ini,x_end,y_ini,y_end,p,a,max_dis,seg_tol,umbral);
			if (line.Label>0) {
				//Ahora hay que eliminar cualquier otro segmento que se le parezca
				ins=true;
				for (pss=segments.begin(),pp_as = p_as.begin();pss<segments.end();pss++,pp_as++) {
					ss=*pss;
					d=ss.p().Distance(line.p()) + ss.q().Distance(line.q());
					if (d<max_d) {
						if (ss.Label<line.Label) {
							segments.erase(pss);
							p_as.erase(pp_as);
							ins=true;
						}
						else {
							ins=false;
							break;
						}
					}
				}
				if (ins) {
					segments.push_back(line);
					p_as.push_back(*pxs);
				}
			}
		}
	
		//Ahora los dibujamos en la imagen
		for (pss=segments.begin(),pp_as=p_as.begin();pss<segments.end();pss++,pp_as++) {
			line = *pss;
			//p = pp_as->p().x();
			//a = pp_as->p().y();
			p = pss->d();
			a = pss->sigma();
			////////////////////////////////////////////////////////////////////
			//Dibujar las lineas en la imagen
			a=(a*-1)+90;
			float sin_a=sin(a*PI/180);
			float cos_a=cos(a*PI/180);
			
			if (!(fabs(90-a)<45.0)) {
				if (line.p().y()<line.q().y()) {
					for (y=line.p().y();y<line.q().y();y++) {
						x=Round((p-(y*sin_a))/cos_a);
						pM[y*NumCols+x]=255;
						
					}
				} 
				else {
					for (y=line.q().y();y<line.p().y();y++) {
						x=Round((p-(y*sin_a))/cos_a);
						pM[y*NumCols+x]=255;
						
					}
				}
			}
			else {
				for (x=line.p().x();x<line.q().x();x++) {
					y=Round((p-(x*cos_a))/sin_a);
					pM[y*NumCols+x]=255;
				}
			}
			////////////////////////////////////////////////////////////////////
			pss->Label = pss->p().x();
		}
		
		sort(segments.begin(),segments.end());
	
	} //end if(vl.size)
	//*/	
		
	free(sens);
	free(coss);

	
	return segments;
}








/***Image_lpr***********************************************\
		GetConnectivity: Divide la imagen en regiones conexas
\***********************************************************/
IntMatrix Image_lpr::GetConnectivity()
{
	int f,c,region_id=1;
	IntMatrix Connectivity(NumRows,NumCols);
	Image_lpr ThisRegion(NumRows,NumCols);
	Image_lpr AllRegions(NumRows,NumCols);
	Image_lpr::Pixel pixel;
	
	Connectivity.SetAll(0);
	AllRegions.SetAll(0);
	for (f=1;f<=NumRows;f++)
		for (c=1;c<=NumCols;c++) 
			if ((pM1[f*NumCols+c]!=0) && (AllRegions(f,c).Level==0)) {
				pixel.Set(f,c,pM1[f*NumCols+c]);
				cout << "Nuevo Pixel: " << pixel;
				ThisRegion = iplFlood(pixel,1);
				Connectivity += (IntMatrix)(ThisRegion * (256-region_id));
				AllRegions = (UcharMatrix)Connectivity;
				printf("Nueva region %d\n",region_id);
				AllRegions.Show();
				region_id++;
				if (region_id>255) return Connectivity;
			}	

	cout << "Regiones detectadas: " << region_id << endl;
	return Connectivity;

}





/***Image_lpr***********************************************\
		iplGetConnectivity: Divide la imagen en regiones conexas
					Usando Intel IPL images
\***********************************************************/
Image_lpr Image_lpr::iplGetConnectivity()
{
	int x,y,region_cnt=0,area;
	IplImage *src,*dst;
	//IplImage *Borders;
	unsigned char pixel[1],asigned[1];

	src = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is uchar
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

    dst = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is int
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled
                                    
    src->imageData = (char *)pM;
	iplAllocateImage(dst,1,0);

	//(*this).jaaShow();
	
	for (y=0;y<NumRows;y++)	
		for (x=0;x<NumCols;x++) {
			iplGetPixel(dst,x,y,asigned);
			if (!(*asigned)) {
				iplGetPixel(src,x,y,pixel);
				if (*pixel) {
					//El pixel pertenece a una region y no está asignado
					//area = iplFloodBis(src,dst,x,y,160 + (region_cnt*5)%95);
					if (area) {
						region_cnt++;
						//printf("Numero de regiones encontradas: %d. AreaRegion[%d]=%d\n",region_cnt,region_cnt,area);
					}
				}
			}
		}
					
		
	Image_lpr Destino(NumRows,NumCols);
	Destino.pM = (unsigned char *) dst->imageData;
	return Destino;

}









/***Image_lpr***********************************************\
		iplGetImageRegions: Divide la imagen en regiones conexas
							Usando Intel IPL images
\***********************************************************/
Image_lpr::RegionVector Image_lpr::iplGetImageRegions(unsigned char graylevel,int min,int max)
{
	RegionVector Regions;
	
	int x,y,region_cnt=0,area;
	IplImage *src,*dst,*tmp;
	unsigned char pixel[1],asigned[1];

	src = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is uchar
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

    dst = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is int
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled
                                    
	tmp = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is int
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

    
	src->imageData = (char *)pM;
	iplAllocateImage(dst,1,0);
	iplAllocateImage(tmp,1,0);

	//(*this).jaaShow();
	
	for (y=0;y<NumRows;y++)	
		for (x=0;x<NumCols;x++) {
			iplGetPixel(dst,x,y,asigned);
			if (!(*asigned)) {
				iplGetPixel(src,x,y,pixel);
				if (*pixel==graylevel) { 
					//El pixel pertenece a una region y no está asignado
					iplSet(tmp,0);
					Region reg = iplFloodBis(src,tmp,x,y,max);
					iplAdd(dst,tmp,dst);
					long area=reg.Area();
					if (((min!=-1) && (max!=-1) && BETWEEN(area,min,max)) ||
						((min!=-1) && (max==-1) && (area>=min)) ||
						((min==-1) && (max!=-1) && (area<=max))) {
					//if (Between(area,min,max)) {
						region_cnt++;
						//printf("Numero de regiones encontradas: %d. AreaRegion[%d]=%d\n",region_cnt,region_cnt,area);
						//pM = (unsigned char *) tmp->imageData;
						//reg.SetSubImage(*this);
						//pM = (unsigned char *) src->imageData;
						//reg.Show();
						Regions.push_back(reg);
						//cout << "Metido " << region_cnt << endl;
					}
				}
			}
		}
					
		
	return Regions;

}




/***Image_lpr***********************************************\
		iplGetThreshold: Busca el umbral optimo para segmentar
						 la imagen
						 Usando Intel IPL images
\***********************************************************/

int	Image_lpr::iplGetThreshold		()
{
	int x,y,region_cnt=0,umbral;
	IplImage *src,*dst;
	IplConvKernel *edge;
	//int ed_f[]={-1, 2, -1};
	int ed_f[]= {-1, 0, 1};
	

	src = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is uchar
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled
	

    dst = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8S,                // data type is int
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

	src->imageData = (char *)pM;
	iplAllocateImage(dst,1,0);
	
	//Show();
	

	//edge = iplCreateConvKernel(3,1,1,0,ed_f,1);
	edge = iplCreateConvKernel(3,1,1,0,ed_f,1);

	iplScale(src,dst);
	
	//Suavizado de la imagen
	iplBlur(dst,dst,3,3,1,1);
	//iplBlur(src,src,3,3,1,1);
	
	//Extraccíon de bordes verticales
	//cout << "Aplicando convolucion" << endl;
	iplConvolve2D(dst,dst,&edge,1,IPL_SUM);
	iplMultiplyS(dst,dst,3);
	//cout << iplErrorStr(iplGetErrStatus()) << endl; 
	
/*
	fstream fout("pixeles.txt",ios::out | ios::trunc);
	fout.setf(ios::dec,ios::basefield);
	fout.width(5);
	fout.setf(ios::right, ios::adjustfield);

	for (y=0;y<NumRows;y++) {
		//printf ("\nFila %d\n",y);
		fout << "\nFila : " << y << endl;
		for(x=0;x<NumCols;x++) {
			signed char pixel;
			iplGetPixel(dst,x,y,&pixel);
			//cout << pixel << " ";
			//printf("%8d",pixel);
			fout << (int)pixel << " ";
		}
	}

//*/
	

	//unsigned char *umbrales = (unsigned char*)malloc(sizeof(unsigned char)*NumRows);
	//memset(umbrales,0,NumRows);
	unsigned char max_of_mins=0,min_of_maxs=255;
	
	for (y=2;y<NumRows-2;y+=2) {
		unsigned char *maximos=(unsigned char *)malloc(sizeof(unsigned char)*NumCols/2);
		unsigned char *minimos=(unsigned char *)malloc(sizeof(unsigned char)*NumCols/2);
		unsigned char *sec	  =(unsigned char *)malloc(sizeof(unsigned char)*NumCols);
		memset(sec,48,NumCols);

		int cambios=0;

		
		//printf("\nChequeando linea %d",y);
		
		///*
		unsigned char max_r=0,min_r=255,med_r=0;
		unsigned char px;
		for (int xm=0;xm<NumCols;xm++) {
			iplGetPixel(src,xm,y,&px);
			min_r=(min_r<px)?min_r:px;
			max_r=(max_r>px)?max_r:px;
			//med_r+=px;
		}
		//med_r/=x;
		
		
		signed char dx,diff=(max_r-min_r)*0.5;
		char ultimo_cambio='0';
		
		
		//Ahora buscamos cambios bruscos en la imagen
		if (diff>15) {
			//Lineas en la imagen muy uniforme
			x=2;
			while (x<NumCols-2) {
				//if ((y==214) &&(x>125))
				//	dx=2;
				iplGetPixel(dst,x,y,&dx);
				if (dx>diff) {
					//Significa cambio brusco creciente, 
					//transición de negro a blanco
					iplGetPixel(src,x-2,y,maximos+cambios);
					iplGetPixel(src,x+2,y,minimos+cambios);
					//sec[x]='-';
					//printf("-");
					cambios++;
				}
				else if (dx<-diff) {
					//Significa cambio brusco decreciente, 
					//transición de negro a blanco
					iplGetPixel(src,x+2,y,maximos+cambios);
					iplGetPixel(src,x-2,y,minimos+cambios);
					//sec[x]='+';
					//printf("+");
					cambios++;
				}
				sec[x]='0';
				//printf("0");
				x++;
			}
			//if (Between(y,200,225)) 
			//		printf("\nNumero de cambios en linea %d:  %d",y,cambios);
			
			//Si se han producido un gran numero de cambios bruscos
			// en la imagen posible haya matricula en esta linea
			if (cambios >18) {
				
				//Ahora tenemos que calcular la media de los maximos 
				//y la de los mínimos para calcular el umbral optimo
				int med_max=0,med_min=0;
				for (int c=0;c<cambios;c++) {
					med_max+=maximos[c];
					med_min+=minimos[c];
				}
				med_max/=cambios;
				med_min/=cambios;

				printf("\nLinea: %4d. Cambios: %3d. Media Maximo: %4d. Media Minimo: %4d\n",y,cambios,med_max,med_min);
				//printf("\nSecuencia\n");for (int i=0;i<NumCols;i++) {printf("%c",(char) sec[i]);}
				max_of_mins=(max_of_mins>med_min)?max_of_mins:med_min;
				min_of_maxs=(min_of_maxs<med_max)?min_of_maxs:med_max;
				//umbrales[y] = (med_max*23+2*med_min) /25;
				//printf("\nPosible matricula en linea %d.Nº de cambios: %d",y,cambios);

				
			}
			free(maximos);
			free(minimos);
			free(sec);
		}
		
	}

	//Ahora calculamos el umbral

	umbral=0;
	/*
	int cnt=0;
	for (y=0;y<NumRows;y++) 
		if (umbrales[y]) {
			//printf("\nUmbral linea %d: %4d",y,umbrales[y]);
			umbral+=umbrales[y];
			cnt++;
		}

	if (cnt) umbral/=cnt;	
	
	try {
		umbral/=cnt;
	}
	catch(...) {
		umbral=0;
	}
	*/
	//free(umbrales);
	
	iplDeallocate(src ,IPL_IMAGE_HEADER);
	iplDeallocate(dst ,IPL_IMAGE_HEADER|IPL_IMAGE_DATA);
	
	printf("\nMaximo de los minimos: %4d. Minimo de los maximos: %4d",max_of_mins,min_of_maxs);
	umbral = (min_of_maxs*4+max_of_mins*1)/5;
	return umbral;

}




/*
int	Image_lpr::iplGetThreshold		()
{
	int x,y,region_cnt=0,umbral;
	IplImage *src,*dst;
	IplConvKernel *edge;
	//int ed_f[]={-1, 2, -1};
	int ed_f[]= {-1,0, 0, 1};
	

	src = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is uchar
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled
	

    dst = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8S,                // data type is int
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

	src->imageData = (char *)pM;
	iplAllocateImage(dst,1,0);
	
	//Show();
	

	//edge = iplCreateConvKernel(3,1,1,0,ed_f,1);
	edge = iplCreateConvKernel(4,1,1,0,ed_f,1);

	//Suavizado de la imagen
	iplBlur(src,src,3,3,1,1);
	
	iplScale(src,dst);
	
	//Extraccíon de bordes verticales
	//cout << "Aplicando convolucion" << endl;
	iplConvolve2D(dst,dst,&edge,1,IPL_SUM);
	//iplMultiplyS(dst,dst,3);
	//cout << iplErrorStr(iplGetErrStatus()) << endl; 
	
	/*
	fstream fout("pixeles.txt",ios::out | ios::trunc);
	fout.setf(ios::dec,ios::basefield);
	fout.width(5);
	fout.setf(ios::right, ios::adjustfield);

	for (y=0;y<NumRows;y++) {
		//printf ("\nFila %d\n",y);
		fout << "\nFila : " << y << endl;
		for(x=0;x<NumCols;x++) {
			signed char pixel;
			iplGetPixel(dst,x,y,&pixel);
			//cout << pixel << " ";
			//printf("%8d",pixel);
			fout << (int)pixel << " ";
		}
	}


	//unsigned char *umbrales = (unsigned char*)malloc(sizeof(unsigned char)*NumRows);
	//memset(umbrales,0,NumRows);
	unsigned char max_of_mins=0,min_of_maxs=255;
	
	for (y=2;y<NumRows-2;y+=2) {
		unsigned char *maximos=(unsigned char *)malloc(sizeof(unsigned char)*NumCols/2);
		unsigned char *minimos=(unsigned char *)malloc(sizeof(unsigned char)*NumCols/2);
		unsigned char *sec	  =(unsigned char *)malloc(sizeof(unsigned char)*NumCols);
		memset(sec,48,NumCols);

		int cambios=0;

		
		signed char max_r=0,min_r=255,med_r=0;
		signed char px;
		for (int xm=0;xm<NumCols;xm++) {
			iplGetPixel(dst,xm,y,&px);
			min_r=(min_r<px)?min_r:px;
			max_r=(max_r>px)?max_r:px;
			//med_r+=px;
		}
		//med_r/=x;

		
		signed char dx,diff=(max_r+abs(min_r))*0.40;
		char	ult_cambio='0';
		
		printf("\nFila %d. Maximo_r: %4d. Minimo_r: %4d. Differencia: %4d\n",y,max_r,min_r,diff);
		//Ahora buscamos cambios bruscos en la imagen
		if (diff>15) {
			//Lineas en la imagen muy uniforme
			x=2;
			while (x<NumCols-2) {
				//if ((y==214) &&(x>125))
				//	dx=2;
				iplGetPixel(dst,x,y,&dx);
				if (dx>diff) {
					if (ult_cambio!='-') {
						//Significa cambio brusco decreciente, 
						//transición de blanco a negro
						iplGetPixel(src,x-2,y,maximos+cambios);
						iplGetPixel(src,x+2,y,minimos+cambios);
						//sec[x]='-';
						ult_cambio='-';
						printf("-");
						cambios++;
					}
					//else if (((x-x_ult_cambio)<=2) && cambios) {
					//	iplGetPixel(src,x+1,y,minimos-cambios-1);
						
					//}
					//x_ult_cambio=x;
				}
				else if (dx<-diff) {
					if (ult_cambio!='+') {
						//Significa cambio brusco creciente, 
						//transición de negro a blanco
						iplGetPixel(src,x+2,y,maximos+cambios);
						iplGetPixel(src,x-2,y,minimos+cambios);
						//sec[x]='+';
						printf("+");
						ult_cambio='+';
						cambios++;
					}
					//else if (((x-x_ult_cambio)<=2) && cambios) {
					//	iplGetPixel(src,x+1,y,maximos+cambios-1);
					//}
					//x_ult_cambio=x;
				}
				//sec[x]='0';
				//printf("0");
				x++;
			}
			//if (Between(y,200,225)) 
			//		printf("\nNumero de cambios en linea %d:  %d",y,cambios);
			
			//Si se han producido un gran numero de cambios bruscos
			// en la imagen posible haya matricula en esta linea
			if (cambios >= 14) {
				
				//Ahora tenemos que calcular la media de los maximos 
				//y la de los mínimos para calcular el umbral optimo
				int med_max=0,med_min=0;
				for (int c=0;c<cambios;c++) {
					med_max+=maximos[c];
					med_min+=minimos[c];
				}
				med_max/=cambios;
				med_min/=cambios;

				printf("\nLinea: %4d. Cambios: %3d. Media Maximo: %4d. Media Minimo: %4d\n",y,cambios,med_max,med_min);
				//printf("\nSecuencia\n");for (int i=0;i<NumCols;i++) {printf("%c",(char) sec[i]);}
				max_of_mins=(max_of_mins>med_min)?max_of_mins:med_min;
				min_of_maxs=(min_of_maxs<med_max)?min_of_maxs:med_max;
				//umbrales[y] = (med_max*23+2*med_min) /25;
				//printf("\nPosible matricula en linea %d.Nº de cambios: %d",y,cambios);

				
			}
			free(maximos);
			free(minimos);
			free(sec);
		}
		
	}

	//Ahora calculamos el umbral

	umbral=0;
//	int cnt=0;
//	for (y=0;y<NumRows;y++) 
//		if (umbrales[y]) {
//			//printf("\nUmbral linea %d: %4d",y,umbrales[y]);
//			umbral+=umbrales[y];
//			cnt++;
//		}
//
//	if (cnt) umbral/=cnt;	
	
	//free(umbrales);
	
	iplDeallocate(src ,IPL_IMAGE_HEADER);
	iplDeallocate(dst ,IPL_IMAGE_HEADER|IPL_IMAGE_DATA);
	
	printf("\nMaximo de los minimos: %4d. Minimo de los maximos: %4d",max_of_mins,min_of_maxs);
	umbral = (min_of_maxs*4+max_of_mins*1)/5;
	return umbral;

}
*/







/**************************************************************************\
* Name      : getGradient
* Member of : Image_lpr
* Purpose   : Obtein Direction and Module of Gradient
* Returns   : void	
* Parameters: Matrix where direction and module will be stored
* Notes     : 
* Author    : JAA
* Date      : 07/06/00
* Modified  : 
\**************************************************************************/
void Image_lpr::getGradient			(FloatMatrix &Angle,UcharMatrix &Module)
{
	
//#ifdef _USE_INTEL_IPL
	//Usaremos imagenes Intel para la creacion del algoritmo
/*
	//Version 1: Sin operar con las flotantes de Intel
	IplConvKernel *edge[4];
	IplConvKernel *edge0,*edge1;
	int sobel3x3v[]	=	{1 , 0, -1, 2, 0, -2, 1, 0, -1};
	int sobel3x3vi[]=	{-1, 0, 1, -2, 0, 2,-1, 0, 1};
	int sobel3x3h[] =	{1, 2, 1, 0, 0, 0, -1, -2, -1};
	int sobel3x3hi[]=	{-1, -2, -1, 0, 0, 0, 1, 2, 1};
	
	IplImage *src,*ver,*hor,*iDir,*iMod;
	
	src = iplCreateImageHeader( 
		1,                            // 1 channel
		0,                            // no alpha channel
		IPL_DEPTH_8U,                // data type
		"GRAY",                       // color model
		"GRAY",                       // channel sequence
		IPL_DATA_ORDER_PIXEL,         // channel arrangement
		IPL_ORIGIN_TL,                // top left orientation
		IPL_ALIGN_QWORD,              // 4 bytes align
		NumCols, NumRows,             // image width and height
		NULL, NULL,                   // no ROI, no mask ROI
		NULL, NULL);                  // image ID, not tiled

	


	ver = iplCreateImageHeader( 
		1,                            // 1 channel
		0,                            // no alpha channel
		IPL_DEPTH_8S,                // data type
		"GRAY",                       // color model
		"GRAY",                       // channel sequence
		IPL_DATA_ORDER_PIXEL,         // channel arrangement
		IPL_ORIGIN_TL,                // top left orientation
		IPL_ALIGN_QWORD,              // 4 bytes align
		NumCols, NumRows,             // image width and height
		NULL, NULL,                   // no ROI, no mask ROI
		NULL, NULL);                  // image ID, not tiled

	hor = iplCreateImageHeader( 
		1,                            // 1 channel
		0,                            // no alpha channel
		IPL_DEPTH_8S,                // data type
		"GRAY",                       // color model
		"GRAY",                       // channel sequence
		IPL_DATA_ORDER_PIXEL,         // channel arrangement
		IPL_ORIGIN_TL,                // top left orientation
		IPL_ALIGN_QWORD,              // 4 bytes align
		NumCols, NumRows,             // image width and height
		NULL, NULL,                   // no ROI, no mask ROI
		NULL, NULL);                  // image ID, not tiled

	iDir = iplCreateImageHeader( 
		1,                            // 1 channel
		0,                            // no alpha channel
		IPL_DEPTH_32S,                // data type
		"GRAY",                       // color model
		"GRAY",                       // channel sequence
		IPL_DATA_ORDER_PIXEL,         // channel arrangement
		IPL_ORIGIN_TL,                // top left orientation
		IPL_ALIGN_QWORD,              // 4 bytes align
		NumCols, NumRows,             // image width and height
		NULL, NULL,                   // no ROI, no mask ROI
		NULL, NULL);                  // image ID, not tiled

	iMod = iplCreateImageHeader( 
		1,                            // 1 channel
		0,                            // no alpha channel
		IPL_DEPTH_8U,                // data type
		"GRAY",                       // color model
		"GRAY",                       // channel sequence
		IPL_DATA_ORDER_PIXEL,         // channel arrangement
		IPL_ORIGIN_TL,                // top left orientation
		IPL_ALIGN_QWORD,              // 4 bytes align
		NumCols, NumRows,             // image width and height
		NULL, NULL,                   // no ROI, no mask ROI
		NULL, NULL);                  // image ID, not tiled




	//Reservamos memoria para las imagenes
	src->imageData = (char *) pM;
	iplAllocateImage(ver,1,0);
	iplAllocateImage(hor,1,0);
	
	
	iDir->imageData = (char *) Angle[0];
	Angle.SetAll(360);
	
	iMod->imageData = (char *) Module[0];


	//Creamos los filtros y los aplicamos
	edge[0] = iplCreateConvKernel(3,3,1,1,sobel3x3v,1);
	edge[1] = iplCreateConvKernel(3,3,1,1,sobel3x3h,1);
	edge[2] = iplCreateConvKernel(3,3,1,1,sobel3x3vi,1);
	edge[3] = iplCreateConvKernel(3,3,1,1,sobel3x3hi,1);

	//iplBlur(src,src,3,3,1,1);
	iplConvert(src,hor);
	iplConvert(src,ver);
	iplConvert(src,iMod);
	iplConvolve2D(hor,hor,&edge[1],1,IPL_SUM);
	iplConvolve2D(ver,ver,&edge[0],1,IPL_SUM);
	iplConvolve2D(iMod,iMod,&edge[0],2,IPL_SUMSQROOT);
	
	
	
	//Visualizar
	//iplConvert(iMod,src);
	//iplMultiplyS(src,src,2);
	//Show();
	//getchar();
		
	
	//Ahora calculamos la dirección del gradiente
	//cout << "\nArcoTangente: " << atan2(1,0)*180/PI << endl;
	register x,y;
	float dir;
	float mod;
	unsigned char v,h;
	for (y=0;y<NumRows;y++)
		for (x=0;x<NumCols;x++) {
			iplGetPixel(ver,x,y,&v);
			iplGetPixel(hor,x,y,&h);
			if (v || h) {
				//mod = hypot(v,h);//sqrt(v*v+h*h);
				//iplPutPixel(iMod,x,y,&mod);
				dir = atan2(v,h)*180/PI;
				iplPutPixel(iDir,x,y,&dir);
			}
			//if (v+h) {
			//	iplGetPixel(iDir,x,y,&dir);
			//	iplGetPixel(iMod,x,y,&mod);
			//	printf("\nModulo y angulo de [%3d,%3d] = (%3d,%3d,%3f,%3f)",x,y,v,h,mod,dir);
			//}
		}

	
	//Liberamos las imagenes
	iplDeallocate(src ,IPL_IMAGE_HEADER);
	iplDeallocate(ver ,IPL_IMAGE_HEADER | IPL_IMAGE_DATA);
	iplDeallocate(hor ,IPL_IMAGE_HEADER | IPL_IMAGE_DATA);
	iplDeallocate(iDir,IPL_IMAGE_HEADER );//| IPL_IMAGE_DATA);
	iplDeallocate(iMod,IPL_IMAGE_HEADER );//| IPL_IMAGE_DATA);
		
	iplDeleteConvKernel(edge[0]);
	iplDeleteConvKernel(edge[1]);
	iplDeleteConvKernel(edge[2]);
	iplDeleteConvKernel(edge[3]);

//*/		
/*
	//Version 2: Operando con las flotantes de Intel
	
	//Usaremos imagenes Intel para la creacion del algoritmo
	IplConvKernelFP *edgeFP[2];
	IplConvKernel *edge0,*edge1;
	float sobel3x3vFP[] =	{1 , 0, -1, 2, 0, -2, 1, 0, -1};
	float sobel3x3hFP[] =	{1, 2, 1, 0, 0, 0, -1, -2, -1};
	
	

	IplImage *src,*ver,*hor,*iDir,*iMod;
	
	 src = iplCreateImageHeader( 
		1,                            // 1 channel
		0,                            // no alpha channel
		IPL_DEPTH_8U,                // data type
		"GRAY",                       // color model
		"GRAY",                       // channel sequence
		IPL_DATA_ORDER_PIXEL,         // channel arrangement
		IPL_ORIGIN_TL,                // top left orientation
		IPL_ALIGN_QWORD,              // 4 bytes align
		NumCols, NumRows,             // image width and height
		NULL, NULL,                   // no ROI, no mask ROI
		NULL, NULL);                  // image ID, not tiled
  
	ver = iplCreateImageHeader( 
		1,                            // 1 channel
		0,                            // no alpha channel
		IPL_DEPTH_32F,                // data type
		"GRAY",                       // color model
		"GRAY",                       // channel sequence
		IPL_DATA_ORDER_PIXEL,         // channel arrangement
		IPL_ORIGIN_TL,                // top left orientation
		IPL_ALIGN_DWORD,              // 4 bytes align
		NumCols, NumRows,             // image width and height
		NULL, NULL,                   // no ROI, no mask ROI
		NULL, NULL);                  // image ID, not tiled

	hor = iplCreateImageHeader( 
		1,                            // 1 channel
		0,                            // no alpha channel
		IPL_DEPTH_32F,                // data type
		"GRAY",                       // color model
		"GRAY",                       // channel sequence
		IPL_DATA_ORDER_PIXEL,         // channel arrangement
		IPL_ORIGIN_TL,                // top left orientation
		IPL_ALIGN_DWORD,              // 4 bytes align
		NumCols, NumRows,             // image width and height
		NULL, NULL,                   // no ROI, no mask ROI
		NULL, NULL);                  // image ID, not tiled

	iDir = iplCreateImageHeader( 
		1,                            // 1 channel
		0,                            // no alpha channel
		IPL_DEPTH_32F,                // data type
		"GRAY",                       // color model
		"GRAY",                       // channel sequence
		IPL_DATA_ORDER_PIXEL,         // channel arrangement
		IPL_ORIGIN_TL,                // top left orientation
		IPL_ALIGN_DWORD,              // 4 bytes align
		NumCols, NumRows,             // image width and height
		NULL, NULL,                   // no ROI, no mask ROI
		NULL, NULL);                  // image ID, not tiled

	iMod = iplCreateImageHeader( 
		1,                            // 1 channel
		0,                            // no alpha channel
		IPL_DEPTH_32F,                // data type
		"GRAY",                       // color model
		"GRAY",                       // channel sequence
		IPL_DATA_ORDER_PIXEL,         // channel arrangement
		IPL_ORIGIN_TL,                // top left orientation
		IPL_ALIGN_DWORD,              // 4 bytes align
		NumCols, NumRows,             // image width and height
		NULL, NULL,                   // no ROI, no mask ROI
		NULL, NULL);                  // image ID, not tiled




	//Reservamos memoria para las imagenes
	src->imageData = (char *) pM;
	iplAllocateImageFP(ver,1,0);
	iplAllocateImageFP(hor,1,0);
	//iplAllocateImageFP(iDir,1,0);
	//iplAllocateImageFP(iMod,1,0);
	
	
	iDir->imageData = (char *) Angle[0];
	//Angle.SetAll(360);
	iplSetFP(iDir,360);
	
	iMod->imageData = (char *) Module[0];
	iplSetFP(iMod,0);


	edgeFP[0] = iplCreateConvKernelFP(3,3,1,1,sobel3x3vFP);
	edgeFP[1] = iplCreateConvKernelFP(3,3,1,1,sobel3x3hFP);
	
	//iplBlur(src,src,3,3,1,1);
	iplConvert(src,hor);
	iplConvert(src,ver);
	iplConvert(src,iMod);
	iplConvolve2DFP(hor,hor,&edgeFP[1],1,IPL_SUM);
	iplConvolve2DFP(ver,ver,&edgeFP[0],1,IPL_SUM);
	iplConvolve2DFP(iMod,iMod,&edgeFP[0],2,IPL_SUMSQROOT);
	
	
	
	//Visualizar
	//iplConvert(iMod,src);
	//iplMultiplyS(src,src,2);
	//Show();
	//getchar();
		
	
	//Ahora calculamos la dirección del gradiente
	//cout << "\nArcoTangente: " << atan2(1,0)*180/PI << endl;
	register x,y;
	float dir;
	float mod;
	float v,h;
	for (y=0;y<NumRows;y++)
		for (x=0;x<NumCols;x++) {
			iplGetPixel(ver,x,y,&v);
			iplGetPixel(hor,x,y,&h);
			if (v || h) {
				mod = hypot(v,h);//sqrt(v*v+h*h);
				iplPutPixel(iMod,x,y,&mod);
				dir = atan2(v,h)*180/PI;
				iplPutPixel(iDir,x,y,&dir);
			}
			if (v+h) {
				iplGetPixel(iDir,x,y,&dir);
				iplGetPixel(iMod,x,y,&mod);
				printf("\nModulo y angulo de [%3d,%3d] = (%3f,%3f,%3f,%3f)",x,y,v,h,mod,dir);
			}
		}

	
		

	
	
	
	//Liberamos las imagenes
	iplDeallocate(src ,IPL_IMAGE_HEADER);
	iplDeallocate(ver ,IPL_IMAGE_HEADER | IPL_IMAGE_DATA);
	iplDeallocate(hor ,IPL_IMAGE_HEADER | IPL_IMAGE_DATA);
	iplDeallocate(iDir,IPL_IMAGE_HEADER );//| IPL_IMAGE_DATA);
	iplDeallocate(iMod,IPL_IMAGE_HEADER );//| IPL_IMAGE_DATA);

	iplDeleteConvKernelFP(edgeFP[0]);
	iplDeleteConvKernelFP(edgeFP[1]);
	
//*/	
//*	
	//Version 3: Usando librerias Matrox
	MIL_ID magnitude,direction,src;
	MbufAlloc2d(sys,NumCols,NumRows,8 + M_UNSIGNED,M_IMAGE+M_PROC+M_DISP,&magnitude);
	MbufAlloc2d(sys,NumCols,NumRows,32 + M_FLOAT  ,M_IMAGE+M_PROC,&direction);
	MbufAlloc2d(sys,NumCols,NumRows,8 + M_UNSIGNED,M_IMAGE+M_PROC+M_DISP,&src);
	MbufPut(src,(uchar *)pM);

	MimEdgeDetect(src,magnitude,direction,M_SOBEL+M_OVERSCAN_DISABLE,M_FAST_EDGE_DETECT,20);

		
	MbufGet(magnitude,(char  *)Module[0]);
	MbufGet(direction,(float *)Angle[0]);

	MbufFree(magnitude);
	MbufFree(direction);
	MbufFree(src);

//*/


//#else
//#endif



}
/***Image_lpr***********************************************\
		iplGetPlate:	Intenta encontrar la situacion de la placa
						utilizando los cambios de intensidad de la
						imagen
						Usando Intel IPL images
\***********************************************************/

void Image_lpr::iplGetPlate	()
{
	//Parametros de la matricula
	int UMBRAL		= 40;
	int min_plate_h;
	int max_plate_h;
	int min_plate_w;
	int max_border_d;
	int min_border_d;
	float HxWfactor = 6.05;
	
	
	//Estructura de datos donde se reune toda la información 
	//que se pueda obtener sobre los bordes de las filas
	typedef struct {
		int NumRow;
		int NumPeeks;
		float Mean,Std;
		int *Peeks,*PeeksValues;
		unsigned char *Maxs,*Mins;
	} TPeeksData;

	TPeeksData *PeeksData;
	int NumberOfRows=0;
	
	
	//Estructuras para almacenar las regiones encontradas
	typedef struct {
		int y_ini,y_fin;
		int r_ini,r_fin;
		int width,height;
		int *x_ini,*x_fin,*n_row;
		int NumberOfPlates;
	} TRegionsData;
	
	TRegionsData *RegionsData;
	int NumberOfRegions=0;
	//RegionVector	RegionData;
	//Region			Reg;

	
	
	int x,y,region_cnt=0,umbral,i,j;
	IplImage *src,*dst,*tmp;
	IplConvKernel *edge[2];
	IplConvKernel *edge0,*edge1;
	int ed_f[]=		{-1, 1,-1, 1,-1, 1,-1, 1,-1, 1};
	int sobel3x3[]	=	{1 , 0, -1, 2, 0, -2, 1, 0, -1};
	int sobel3x5[]	=	{1 , 0, -1, 1, 0, -1, 2, 0, -2, 1, 0, -1, 1, 0, -1};
	int sobel3x3h[] =	{1, 2, 1, 0, 0, 0, -1, -2, -1};
	int laplace[]	=	{-1, -3, -4, -3, -1,-3, 0, 6, 0,-3,-4, 6, 20, 6, -4,-3, 0, 6, 0,-3,-1,-3,-4,-3,-1};
	int lapl[]		=	{-1, 2, -1}; 
	int Gauss5x5[]	=	{2, 7, 12, 7, 2, 7, 31, 52, 31, 7, 12, 52, 127, 52, 12, 7, 31, 52, 31, 7, 2, 7, 12, 7, 2};
	int GaussV[]	=	{2, 7, 12, 7, 2};
	int Gauss3x3[]	=	{1, 2, 1, 2, 4, 2, 1, 2, 1};

	signed char pixel_g,pixel_p;

	//Variables utilizadas para guardar los picos de la imagen (gradientes bruscos)
	int *Picos;
	int *Valor_Picos;
	unsigned char *Maximos;
	unsigned char *Minimos;
	int cnt_picos=0;

	//Variables utilizadas para obtener la mayor concentración de bordes
	float sum=0,mean=0,std=0;


	

	src = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is uchar
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled
	

    dst = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8S,                // data type is int
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

	
	tmp = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8S,                // data type is int
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

	src->imageData = (char *)pM;
	iplAllocateImage(dst,1,0);
	iplAllocateImage(tmp,1,0);
	
	//Show();
	

	Picos		= (int *) malloc (NumCols * sizeof(int));
	Valor_Picos = (int *) malloc (NumCols * sizeof(int));
	Maximos		= (unsigned char *) malloc (NumCols * sizeof(unsigned char));
	Minimos		= (unsigned char *) malloc (NumCols * sizeof(unsigned char));
	PeeksData	= (TPeeksData *)	malloc (NumRows * sizeof(TPeeksData));
	RegionsData	= (TRegionsData *)	malloc ((NumRows/2) * sizeof (TRegionsData));


	//edge[0] = iplCreateConvKernel(3,3,1,1,sobel3x3,1);
	//edge[1] = iplCreateConvKernel(3,3,1,1,sobel3x3h,1);
	
	//Suavizado de la imagen
	if (NumCols<460) {
		edge[0] = iplCreateConvKernel(3,3,1,1,Gauss3x3,4);
		iplConvolve2D(src,src,edge,1,IPL_SUM);
		//iplBlur(src,src,3,3,1,1);
		min_plate_h		= 20;
		max_border_d	= 25;
	}
	else {
		edge[0] = iplCreateConvKernel(5,5,2,2,Gauss5x5,9);
		iplConvolve2D(src,src,edge,1,IPL_SUM);
		//iplBlur(src,src,5,5,2,2);
		min_plate_h		= 35;
		max_border_d	= 45;
	}
	min_plate_h = 20;
	max_plate_h = NumCols / HxWfactor;
	
	iplScale(src,dst);
	
	//Extraccíon de bordes verticales
	//edge[1] = iplCreateConvKernel(3,3,1,1,sobel3x3,1);
	edge[1] = iplCreateConvKernel(2,3,0,1,ed_f,1);
	iplConvolve2D(dst,dst,&edge[1],1,IPL_SUM);
	
	
	///// Multiplicar la imagen para obtener un poco mas de contraste         /////
	//iplMultiplyS(dst,dst,3); //Multipico x 3
	//iplRShiftS(dst,dst,1);	 //Divido x 2
	///// Multiplicar la imagen para obtener un poco mas de contraste         /////
	
	
	
	////////////////////////////////////////
	// Primera pasada:Obtener informacion //
	////////////////////////////////////////
	for (y=1;y<NumRows-1;y+=1) {
		
		//Busqueda de escalones absolutos en le nivel de gris
		int x_sec=0,x_cnt=0,esc=0,value=0,x_max,v_max;
		cnt_picos=0;
		sum=0;mean=0;std=0;
		x=1;
		while (x<NumCols-1) {
			
			iplGetPixel(dst,x,y,&pixel_g);
			//if (abs(pixel_g)>2) {
				//Si es un cambio 
				iplPutPixel(dst,x,y,&value);
				if (pixel_g>0) {
					if (esc > 0) {
						//Se continua con un escalon ascendente
						esc+=pixel_g;x_cnt++;
						if (pixel_g>v_max) {v_max=pixel_g;x_max=x;}
						
					}
					//else if (esc < 0) {			 
					//	//En medio de un descendente nos encontramos una subida
					//	//Terminamos la sección y empezamos una nueva ascendente
					//	if (esc<-UMBRAL) 
					//		//es un cambio brusco y lo asignamos al pixel entre x_sec y x
					//		iplPutPixel(dst,x_max,y,&esc);

					//	esc = v_max = pixel_g;
					//	x_sec = x_max = x; 
					//}
					//else {	//esc==0;
					//	//Comienza una nueva sección
					//	esc = v_max = pixel_g;
					//	x_sec = x_max = x; 
					//}
					else {
						//Terminamos la sección y comenzamos una nueva
						if (esc<-UMBRAL) {
							//es un cambio brusco y lo asignamos al pixel entre x_sec y x
							iplPutPixel(dst,x_max,y,&esc);
							// y lo guardamos como pico, y el valor maximo y minimo
							iplGetPixel(src,x,y,Maximos+cnt_picos);
							iplGetPixel(src,x_sec,y,Minimos+cnt_picos);
							Valor_Picos	[cnt_picos]		= esc;
							Picos		[cnt_picos++]	= x;
							//Guardamos su posicion
							sum+=x;
							//value=127;
						}
						
						esc = v_max = pixel_g;
						x_sec = x_max = x; 
					}

				}
				else if (pixel_g<0) {
					if (esc < 0) {
						//Se continua con un escalon descendente
						esc+=pixel_g;x_cnt++;
						if (pixel_g<v_max) {v_max=pixel_g;x_max=x;}
						
					}
					//else if (esc > 0) {			 
					//	//En medio de un ascendente nos encontramos una bajada
					//	//Terminamos la sección y empezamos una nueva descendente
					//	if (esc>UMBRAL) 
					//		//es un cambio brusco y lo asignamos al pixel entre x_sec y x
					//		iplPutPixel(dst,(x_sec+x+1)/2,y,&esc);

					//	esc = v_max = pixel_g;
					//	x_sec = x_max = x; 
					//}
					//else {	//esc==0;
					//	//Comienza una nueva sección
					//	esc = v_max = pixel_g;
					//	x_sec = x_max = x; 
					//}
					else {
						//Comenzamos una nueva sección
						if (esc>UMBRAL) {
							//es un cambio brusco y lo asignamos al pixel entre x_sec y x
							iplPutPixel(dst,x_max,y,&esc);
							// y guardamos el Pico producido
							iplGetPixel(src,x_sec,y,Maximos+cnt_picos);
							iplGetPixel(src,x,y,Minimos+cnt_picos);
							Valor_Picos	[cnt_picos]		= esc;
							Picos		[cnt_picos++]	= x;
							//Guardamos su posicion
							sum+=x;
							//value=0;
						}
						
						esc = v_max = pixel_g;
						x_sec = x_max = x; 
					}
				}

			//} 
			//else {
			//	iplPutPixel(dst,x,y,&value0);
			//}	//end if(abs(pixel))
			
			
			/////////////////////////////////////////////////////////////////////////////////
			/*
			//Eliminacion de los No maximos locales
			//Ahora tenemos una imagen con solo valore positivos
			//A los masimos se les asigna el valor 255, en otro caso 0
			unsigned char PixelAnt,PixelPost;
			iplGetPixel(src,x,y,&pixel_g);
			iplGetPixel(src,x-1,y,&PixelAnt);
			iplGetPixel(src,x+1,y,&PixelPost);
						
			if ((pixel_g>PixelAnt) && (pixel_g>PixelPost) && (pixel_g>20)) {
				//Es un maximo local
				value=255;
				iplPutPixel(src,x,y,&value);
				value=0;
				iplPutPixel(src,x-1,y,&value);
				x++;
			}
			else {
				value=0;
				iplPutPixel(src,x-1,y,&value);
			}
			*/
			//Esto es una mierda
			/////////////////////////////////////////////////////////////////////////////////
			
			x++;
		} //end while (x<NumCols-1)

		//*
		//Calcular desv std
		mean=sum/cnt_picos;
		std=0;
		for (int i=0;i<cnt_picos;i++) {
			float val=mean-Picos[i];
			std+=(val*val);
		}
		std/=cnt_picos;
		std=sqrt(std);

		//Filtrado de la Desv Standart
//		float std2=0;
//		int cnt_picos2=0;
//		for (i=0;i<cnt_picos;i++) {
//			float val=abs(mean-Picos[i]);
//				std2+=(val*val);
//				cnt_picos2++;
//			}
//		}
//		std2/=cnt_picos2;
//		std2=sqrt(std2);

		
		//Guardar datos en PeeksData
		if (cnt_picos>16) {
			PeeksData[NumberOfRows].NumRow		= y;
			PeeksData[NumberOfRows].NumPeeks	= cnt_picos;
			PeeksData[NumberOfRows].Mean		= mean;
			PeeksData[NumberOfRows].Std			= std;
			PeeksData[NumberOfRows].Peeks		= (int *) malloc (cnt_picos * sizeof(int));
			PeeksData[NumberOfRows].PeeksValues	= (int *) malloc (cnt_picos * sizeof(int));
			PeeksData[NumberOfRows].Maxs		= (unsigned char *) malloc (cnt_picos * sizeof(unsigned char));
			PeeksData[NumberOfRows].Mins		= (unsigned char *) malloc (cnt_picos * sizeof(unsigned char));
			memcpy(PeeksData[NumberOfRows].Peeks,Picos,cnt_picos * sizeof(int));
			memcpy(PeeksData[NumberOfRows].PeeksValues,Valor_Picos,cnt_picos * sizeof(int));
			memcpy(PeeksData[NumberOfRows].Maxs,Maximos,cnt_picos * sizeof(unsigned char));
			memcpy(PeeksData[NumberOfRows].Mins,Minimos,cnt_picos * sizeof(unsigned char));
			NumberOfRows++;
			//cout << endl << endl;
			//for (int i=0;i<cnt_picos;i++) printf("%5d",Picos[i]);
		}

		
		//Mostrar datos
		//if (cnt_picos>16) {
		//	printf("\n\nPicos fila %3d=(%d). Media= %4.3f.Desv. Std: %4.3f\n\n",y,cnt_picos,mean,std);
		//	for (int i=0;i<cnt_picos;i++) printf("%5d",Picos[i]);
		//}
		//*/
		
	} //end for(y)
	
	
	
	
	//Liberacion de variables no utilizadas
	free(Picos);
	free(Valor_Picos);
	free(Maximos);
	free(Minimos);

	
	//Mostrar imagen.
	iplAbs(dst,dst);
	iplConvert(dst,src);
	iplThreshold(src,src,UMBRAL);
	//iplMultiplyS(src,src,3);
	Show();
	
	//pM = (unsigned char *) src->imageData;
	/*
	fstream fout("pixeles.txt",ios::out | ios::trunc);
	fout.setf(ios::dec,ios::basefield);
	fout.width(5);
	fout.setf(ios::right, ios::adjustfield);

	for (y=0;y<NumRows;y++) {
		//printf ("\nFila %d\n",y);
		fout << "\nFila : " << y << endl;
		for(x=0;x<NumCols;x++) {
			signed char pixel;
			iplGetPixel(dst,x,y,&pixel);
			//cout << pixel << " ";
			//printf("%8d",pixel);
			fout << (int)pixel << " ";
		}
	}
	//*/


	
	//Mostrar todos los datos
//	for (i=0;i<NumberOfRows;i++) {
//		TPeeksData *p=PeeksData+i;
//		printf("\nFila: %4d(%d). Media: %7.3f. DesvStd: %7.3f\n",p->NumRow,p->NumPeeks,p->Mean,p->Std);
//		for (j=0;j<p->NumPeeks;j++) {
			//printf("[%3d,%4d]",p->Peeks[j],p->PeeksValues[j]);
			//printf("%4d",p->Peeks[j]);
//			printf("[%3d,%3d,%3d]",p->Peeks[j],(unsigned char)p->Maxs[j],(unsigned char)p->Mins[j]);
//		}
//		printf("\n");
//	}
	

	//Analisis de los datos
	//Primero analizamos las lineas continuas que tienen gran cantidad de cambios
	int y_init=0,y_fin=0,height=0,r_init=0,r_fin=0,r=0;
	//y=0;
	while (r<NumberOfRows-1) {
		r_init=r;
		while ((r<NumberOfRows-1) && ((PeeksData[r+1].NumRow-PeeksData[r].NumRow)<=2)) 
			r++;
		
		r_fin=r;
		
		y_init=PeeksData[r_init].NumRow;
		y_fin =PeeksData[r_fin].NumRow;
		height = y_fin-y_init;
		//printf("\n %d %d %d \n",height,min_plate_h,max_plate_h);
		if (BETWEEN(height,min_plate_h,max_plate_h)) {
			min_plate_w=Round((float)(y_fin-y_init)*HxWfactor);
			if (min_plate_w < NumCols) {
				//Almacenamos la posible region de matricula
				RegionsData[NumberOfRegions].r_ini = r_init;
				RegionsData[NumberOfRegions].r_fin = r_fin;
				RegionsData[NumberOfRegions].x_ini= (int *) malloc ((1+r_fin-r_init)*sizeof(int));
				RegionsData[NumberOfRegions].x_fin= (int *) malloc ((1+r_fin-r_init)*sizeof(int));
				RegionsData[NumberOfRegions].n_row= (int *) malloc ((1+r_fin-r_init)*sizeof(int));
				RegionsData[NumberOfRegions].NumberOfPlates=0;
				RegionsData[NumberOfRegions].width = min_plate_w;
				RegionsData[NumberOfRegions].height= y_fin-y_init;
				RegionsData[NumberOfRegions].y_ini = y_init;
				RegionsData[NumberOfRegions++].y_fin = y_fin;
				
				printf("\nPosible matricula en lineas %3d a %3d. (%d)\n",y_init,y_fin,height);
				printf(  "Ancho minimo aproximado: %4d\n\n",min_plate_w);
			}
		}
		r++;
	}

	
	//Analisis de cada una de las filas de las regiones encontradas
	printf("\n\nNumero de regiones encontradas: %d\n",NumberOfRegions);
	for (i=0;i<NumberOfRegions;i++) {
		/*
		//Preparando datos
		int r_mean = (RegionsData[i].r_fin + RegionsData[i].r_ini) / 2;
		TPeeksData *pd = &PeeksData[r_mean];
		int x_ini=0,x_fin=0,p_cnt=0;
		max_border_d = (int)(RegionsData[i].height * 0.9);
		printf("\nAnalizando fila: %d.Altura: %d.Maxima distancia: %d.Ancho minimo: %d\n",pd->NumRow,RegionsData[i].height,max_border_d,RegionsData[i].width);
		int p=0;
		
		//Analizamos la linea
		while (p<pd->NumPeeks-1) {
			//Aqui vamos viendo que la distancia entre cambios bruscos de exceda de max_border_d
			x_ini=pd->Peeks[p];
			while	((p<pd->NumPeeks-1) && 
					((pd->Peeks[p+1]-pd->Peeks[p])<max_border_d))// &&
					//(abs(pd->Maxs[p+1]-pd->Maxs[p])<40) &&
					//(abs(pd->Mins[p+1]-pd->Mins[p])<40))
				p++;
			x_fin=pd->Peeks[p];
			
			//puede que sea una matricula si ...
			if (BETWEEN(x_fin-x_ini,RegionsData[i].width,Round(RegionsData[i].width * 1.30))) {
				printf("Posible matricula encontrada: [%3d,%3d]. Ancho: %3d\n\n",x_ini,x_fin,x_fin-x_ini);
				break;
			}
			else {
				printf("Region encontrada:            [%3d,%3d]. Ancho: %3d\n\n",x_ini,x_fin,x_fin-x_ini);
			}

			p++;
		}
		*/
		//Analizamos las linea
		for (j=RegionsData[i].r_ini;j<=RegionsData[i].r_fin;j++) {
			TPeeksData *pd = &PeeksData[j];
			int x_ini=0,x_fin=0,p_cnt=0;
			MedianResult max_value;
			MedianResult min_value;
			max_border_d = (int)(RegionsData[i].height * 115)/100;
			min_border_d = (int)(RegionsData[i].height * 3)/50;
			median((void *) (pd->Maxs),pd->NumPeeks,8,&max_value);
			median((void *) (pd->Mins),pd->NumPeeks,8,&min_value);
			//printf("\nFila %3d. Valor Maximo: %3d. Valor Minimo: %3d",pd->NumRow,max_value.ch,min_value.ch);
			//printf("\nAnalizando fila: %d.Altura: %d.Maxima distancia: %d.Ancho minimo: %d\n",pd->NumRow,RegionsData[i].height,max_border_d,RegionsData[i].width);
			int p=0;
			
			//Analizamos la linea
			while (p<pd->NumPeeks-1) {
				//Aqui vamos viendo que la distancia entre cambios bruscos de exceda de max_border_d
				x_ini=pd->Peeks[p];
				while	((p<pd->NumPeeks-1) && 
						((pd->Peeks[p+1]-pd->Peeks[p])<max_border_d))// &&
						//((pd->Peeks[p+1]-pd->Peeks[p])>min_border_d))
						//(abs(pd->Maxs[p+1]-pd->Maxs[p])<40) &&
						//(abs(pd->Mins[p+1]-pd->Mins[p])<40))
						//(((abs(pd->Maxs[p]-max_value.in)<max_value.in*0.3) ||
						// (abs(pd->Maxs[p+1]-max_value.in)<max_value.in*0.3))) &&
						//(((abs(pd->Mins[p]-min_value.in)<min_value.in*0.3) ||
						// (abs(pd->Mins[p+1]-min_value.in)<min_value.in*0.3))))
					p++;
				x_fin=pd->Peeks[p];
				
				//puede que sea una matricula si ...
				if (BETWEEN(x_fin-x_ini,RegionsData[i].width,Round(RegionsData[i].width * 1.30))) {
				//if ((x_fin-x_ini)>(RegionsData[i].width*0.6)) {
					//printf("Posible matricula encontrada: [%3d,%3d]. Ancho: %3d\n\n",x_ini,x_fin,x_fin-x_ini);
					RegionsData[i].x_ini[RegionsData[i].NumberOfPlates] = x_ini;
					RegionsData[i].x_fin[RegionsData[i].NumberOfPlates] = x_fin;
					RegionsData[i].n_row[RegionsData[i].NumberOfPlates++] = pd->NumRow;
					break;
				}
				else {
					printf("Region encontrada fila %3d:            [%3d,%3d]. Ancho: %3d\n\n",pd->NumRow,x_ini,x_fin,x_fin-x_ini);
				}

				p++;
			} //end while(p)
		}	//end for(RegionsData[i].r_ini)
	} //end for(NumberOfRegions)
	
	
	//Mostrar datos sobre regiones
	for (i=0;i<NumberOfRegions;i++) {
		TRegionsData *rd=&RegionsData[i];
		printf("\nRegion %d de %d: [%d,%d]\n",i+1,NumberOfRegions,rd->y_ini,rd->y_fin);
		for (j=0;j<rd->NumberOfPlates;j++) printf("[%3d,%3d,%3d]  ",rd->n_row[j],rd->x_ini[j],rd->x_fin[j]);
	}


	printf("\n");
	//Analizar los datos de cada region
	for (i=0;i<NumberOfRegions;i++) {
		TRegionsData *rd=RegionsData+i;
		printf("\nRegion %d de %d: [%d,%d]",i,NumberOfRegions,rd->y_ini,rd->y_fin);
		if (rd->NumberOfPlates >= min_plate_h-5) {
			//Para regiones que no cumplen con el alto minimo no hacemos nada
			printf("\nSe cumple el alto %d",rd->NumberOfPlates);
			//int med_x_ini=0,med_x_fin=0,width=0;
			/*
			for (j=0;j<rd->NumberOfPlates;j++) {
				med_x_ini+=rd->x_ini[j];
				med_x_fin+=rd->x_fin[j];
			}
			med_x_ini/=j;
			med_x_fin/=j;
			rd->width=med_x_fin-med_x_ini;
			//rd->height=rd->n_row[rd->NumberOfPlates-1]-rd->n_row[0];
			rd->height=j;
			*/
			MedianResult med_x_ini,med_x_fin;
			median((void *)rd->x_ini,rd->NumberOfPlates,16,&med_x_ini);
			median((void *)rd->x_fin,rd->NumberOfPlates,16,&med_x_fin);
			rd->width=med_x_fin.in-med_x_ini.in;
			rd->height=rd->n_row[rd->NumberOfPlates-1]-rd->n_row[0];
			printf("\nX_INI: %3d. X_FIN: %3d. Altura: %3d. Anchura: %3d",med_x_ini.in,med_x_fin.in,rd->height,rd->width);

			//Comprobamos las proporciones
			if ( fabs(((float)rd->width/(float)rd->height)-HxWfactor)<(HxWfactor*0.4) ) {
				//Y si las cumple podemos pensar que es una matricula
				int frame = (rd->width * 24)/300;
				printf("\nMatricula de [%3d,%3d] -> [%3d,%3d]",med_x_ini.in-frame,rd->y_ini-frame,med_x_fin.in+frame,rd->y_fin+frame);
			}
		} // end if(min_plate_h)
	}
	
	for (i=0;i<NumberOfRows;i++) {
		free(PeeksData[i].Peeks);
		free(PeeksData[i].PeeksValues);
		free(PeeksData[i].Mins);
		free(PeeksData[i].Maxs);
	}
	free(PeeksData);
	
	for (j=0;j<NumberOfRegions;j++) {
		free(RegionsData[j].x_ini);
		free(RegionsData[j].x_fin);
		free(RegionsData[j].n_row);
	}
	free(RegionsData);

	iplDeallocate(src ,IPL_IMAGE_HEADER);
	iplDeallocate(dst ,IPL_IMAGE_HEADER|IPL_IMAGE_DATA);
	iplDeallocate(tmp ,IPL_IMAGE_HEADER|IPL_IMAGE_DATA);
	iplDeleteConvKernel(edge[0]);
	iplDeleteConvKernel(edge[1]);


} //end iplGetPlate



/**************************************************************************\
* Name      : iplGetPlate2
* Member of : Image_lpr
* Purpose   : Obtain the number plate location
* Returns   :    
* Parameters: 
* Notes     : Using vertical projections of Regions
* Author    : JAA
* Date      : 22.05.00
* Modified  :
\**************************************************************************/
void Image_lpr::iplGetPlate2() {

//Parametros de la matricula
	int UMBRAL		= 30;
	int min_plate_h;
	int max_plate_h;
	int min_plate_w;
	int max_border_d;
	int min_border_d;
	float HxWfactor = 6.05;
	
	
	//Estructura de datos donde se reune toda la información 
	//que se pueda obtener sobre los bordes de las filas
	typedef struct {
		int NumRow;
		int NumPeeks;
		float Mean,Std;
		int *Peeks,*PeeksValues;
		unsigned char *Maxs,*Mins;
	} TPeeksData;

	TPeeksData *PeeksData;
	int NumberOfRows=0;
	
	
	//Estructuras para almacenar las regiones encontradas
	typedef struct {
		int y_ini,y_fin;
		int r_ini,r_fin;
		int width,height;
		int *x_ini,*x_fin,*n_row;
		int NumberOfPlates;
	} TRegionsData;
	
	TRegionsData *RegionsData;
	int NumberOfRegions=0;
	//RegionVector	RegionData;
	//Region			Reg;

	
	register i,j,k;
	int x,y,region_cnt=0,umbral;
	unsigned char value;
	IplImage *src,*dst,*tmp;
	IplConvKernel *edge[2];
	IplConvKernel *edge0,*edge1;
	int ed_f[]=		{-1, 1,-1, 1,-1, 1,-1, 1,-1, 1};
	int sobel3x3[]	=	{1 , 0, -1, 2, 0, -2, 1, 0, -1};
	int sobel3x5[]	=	{1 , 0, -1, 1, 0, -1, 2, 0, -2, 1, 0, -1, 1, 0, -1};
	int sobel3x3h[] =	{1, 2, 1, 0, 0, 0, -1, -2, -1};
	int laplace[]	=	{-1, -3, -4, -3, -1,-3, 0, 6, 0,-3,-4, 6, 20, 6, -4,-3, 0, 6, 0,-3,-1,-3,-4,-3,-1};
	int lapl[]		=	{-1, 2, -1}; 
	int Gauss5x5[]	=	{2, 7, 12, 7, 2, 7, 31, 52, 31, 7, 12, 52, 127, 52, 12, 7, 31, 52, 31, 7, 2, 7, 12, 7, 2};
	int GaussV[]	=	{2, 7, 12, 7, 2};
	int Gauss3x3[]	=	{1, 2, 1, 2, 4, 2, 1, 2, 1};

	signed char pixel_g,pixel_p;

	//Variables utilizadas para guardar los picos de la imagen (gradientes bruscos)
	int *Picos;
	int *Valor_Picos;
	unsigned char *Maximos;
	unsigned char *Minimos;
	int cnt_picos=0;

	//Variables utilizadas para obtener la mayor concentración de bordes
	float sum=0,mean=0,std=0;


	

	src = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is uchar
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled
	

    dst = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8S,                // data type is int
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

	
	tmp = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is int
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

	src->imageData = (char *)pM;
	iplAllocateImage(dst,1,0);
	iplAllocateImage(tmp,1,0);
	
	//Show();
	

	Picos		= (int *) malloc (NumCols * sizeof(int));
	Valor_Picos = (int *) malloc (NumCols * sizeof(int));
	Maximos		= (unsigned char *) malloc (NumCols * sizeof(unsigned char));
	Minimos		= (unsigned char *) malloc (NumCols * sizeof(unsigned char));
	PeeksData	= (TPeeksData *)	malloc (NumRows * sizeof(TPeeksData));
	RegionsData	= (TRegionsData *)	malloc ((NumRows/2) * sizeof (TRegionsData));


	//edge[0] = iplCreateConvKernel(3,3,1,1,sobel3x3,1);
	//edge[1] = iplCreateConvKernel(3,3,1,1,sobel3x3h,1);
	
	//Suavizado de la imagen
	if (NumCols<460) {
		edge[0] = iplCreateConvKernel(3,3,1,1,Gauss3x3,4);
		iplConvolve2D(src,src,edge,1,IPL_SUM);
		//iplBlur(src,src,3,3,1,1);
		min_plate_h		= 20;
		max_border_d	= 25;
	}
	else {
		edge[0] = iplCreateConvKernel(5,5,2,2,Gauss5x5,9);
		iplConvolve2D(src,src,edge,1,IPL_SUM);
		//iplBlur(src,src,5,5,2,2);
		min_plate_h		= 35;
		max_border_d	= 45;
	}
	min_plate_h = 20;
	max_plate_h = NumCols / HxWfactor;
	
	iplScale(src,dst);
	
	//Extraccíon de bordes verticales
	//edge[1] = iplCreateConvKernel(3,3,1,1,sobel3x3,1);
	edge[1] = iplCreateConvKernel(2,3,0,1,ed_f,1);
	iplConvolve2D(dst,dst,&edge[1],1,IPL_SUM);
	
	
	////////////////////////////////////////
	// Primera pasada:Obtener informacion //
	////////////////////////////////////////
	for (y=1;y<NumRows-1;y+=1) {
		
		//Busqueda de escalones absolutos en le nivel de gris
		int x_sec=0,x_cnt=0,esc=0,value=0,x_max,v_max;
		cnt_picos=0;
		sum=0;mean=0;std=0;
		x=1;
		while (x<NumCols-1) {
			
			iplGetPixel(dst,x,y,&pixel_g);
			//if (abs(pixel_g)>2) {
				//Si es un cambio 
				iplPutPixel(dst,x,y,&value);
				if (pixel_g>0) {
					if (esc > 0) {
						//Se continua con un escalon ascendente
						esc+=pixel_g;x_cnt++;
						if (pixel_g>v_max) {v_max=pixel_g;x_max=x;}
						
					}
					else {
						//Terminamos la sección y comenzamos una nueva
						if (esc<-UMBRAL) {
							//es un cambio brusco y lo asignamos al pixel entre x_sec y x
							iplPutPixel(dst,x_max,y,&esc);
							// y lo guardamos como pico, y el valor maximo y minimo
							iplGetPixel(src,x,y,Maximos+cnt_picos);
							iplGetPixel(src,x_sec,y,Minimos+cnt_picos);
							Valor_Picos	[cnt_picos]		= esc;
							Picos		[cnt_picos++]	= x_max;
							//Guardamos su posicion
							sum+=x;
							//value=127;
						}
						
						esc = v_max = pixel_g;
						x_sec = x_max = x; 
					}

				}
				else if (pixel_g<0) {
					if (esc < 0) {
						//Se continua con un escalon descendente
						esc+=pixel_g;x_cnt++;
						if (pixel_g<v_max) {v_max=pixel_g;x_max=x;}
						
					}
					else {
						//Comenzamos una nueva sección
						if (esc>UMBRAL) {
							//es un cambio brusco y lo asignamos al pixel entre x_sec y x
							iplPutPixel(dst,x_max,y,&esc);
							// y guardamos el Pico producido
							iplGetPixel(src,x_sec,y,Maximos+cnt_picos);
							iplGetPixel(src,x,y,Minimos+cnt_picos);
							Valor_Picos	[cnt_picos]		= esc;
							Picos		[cnt_picos++]	= x_max;
							//Guardamos su posicion
							sum+=x;
							//value=0;
						}
						
						esc = v_max = pixel_g;
						x_sec = x_max = x; 
					}
				}

			
			x++;
		} //end while (x<NumCols-1)

		//*
		//Calcular desv std
		mean=sum/cnt_picos;
		std=0;
		for (int i=0;i<cnt_picos;i++) {
			float val=mean-Picos[i];
			std+=(val*val);
		}
		std/=cnt_picos;
		std=sqrt(std);

		
		//Guardar datos en PeeksData
		if (cnt_picos>16) {
			PeeksData[NumberOfRows].NumRow		= y;
			PeeksData[NumberOfRows].NumPeeks	= cnt_picos;
			PeeksData[NumberOfRows].Mean		= mean;
			PeeksData[NumberOfRows].Std			= std;
			PeeksData[NumberOfRows].Peeks		= (int *) malloc (cnt_picos * sizeof(int));
			PeeksData[NumberOfRows].PeeksValues	= (int *) malloc (cnt_picos * sizeof(int));
			PeeksData[NumberOfRows].Maxs		= (unsigned char *) malloc (cnt_picos * sizeof(unsigned char));
			PeeksData[NumberOfRows].Mins		= (unsigned char *) malloc (cnt_picos * sizeof(unsigned char));
			memcpy(PeeksData[NumberOfRows].Peeks,Picos,cnt_picos * sizeof(int));
			memcpy(PeeksData[NumberOfRows].PeeksValues,Valor_Picos,cnt_picos * sizeof(int));
			memcpy(PeeksData[NumberOfRows].Maxs,Maximos,cnt_picos * sizeof(unsigned char));
			memcpy(PeeksData[NumberOfRows].Mins,Minimos,cnt_picos * sizeof(unsigned char));
			NumberOfRows++;
			//cout << endl << endl;
			//for (int i=0;i<cnt_picos;i++) printf("%5d",Picos[i]);
		}

		
		//Mostrar datos
		//if (cnt_picos>16) {
		//	printf("\n\nPicos fila %3d=(%d). Media= %4.3f.Desv. Std: %4.3f\n\n",y,cnt_picos,mean,std);
		//	for (int i=0;i<cnt_picos;i++) printf("%5d",Picos[i]);
		//}
		//*/
		
	} //end for(y)
	
	
	
	
	//Liberacion de variables no utilizadas
	//free(Picos);
	//free(Valor_Picos);
	//free(Maximos);
	//free(Minimos);

	
	//Mostrar imagen.
	//iplAbs(dst,dst);
	//iplConvert(dst,src);
	//iplThreshold(src,src,UMBRAL);
	//iplMultiplyS(src,src,3);
	//Show();
	
	
	//Mostrar todos los datos
//	for (i=0;i<NumberOfRows;i++) {
//		TPeeksData *p=PeeksData+i;
//		printf("\nFila: %4d(%d). Media: %7.3f. DesvStd: %7.3f\n",p->NumRow,p->NumPeeks,p->Mean,p->Std);
//		for (j=0;j<p->NumPeeks;j++) {
			//printf("[%3d,%4d]",p->Peeks[j],p->PeeksValues[j]);
			//printf("%4d",p->Peeks[j]);
//			printf("[%3d,%3d,%3d]",p->Peeks[j],(unsigned char)p->Maxs[j],(unsigned char)p->Mins[j]);
//		}
//		printf("\n");
//	}
	

	//Analisis de los datos
	//Primero analizamos las lineas continuas que tienen gran cantidad de cambios
	int y_init=0,y_fin=0,height=0,r_init=0,r_fin=0,r=0;
	//y=0;
	while (r<NumberOfRows-1) {
		r_init=r;
		while ((r<NumberOfRows-1) && ((PeeksData[r+1].NumRow-PeeksData[r].NumRow)<=2)) 
			r++;
		
		r_fin=r;
		
		y_init=PeeksData[r_init].NumRow;
		y_fin =PeeksData[r_fin].NumRow;
		height = y_fin-y_init;
		//printf("\n %d %d %d \n",height,min_plate_h,max_plate_h);
		if (BETWEEN(height,min_plate_h,max_plate_h)) {
			min_plate_w=Round((float)(y_fin-y_init)*HxWfactor);
			if (min_plate_w < NumCols) {
				//Almacenamos la posible region de matricula
				RegionsData[NumberOfRegions].r_ini = r_init;
				RegionsData[NumberOfRegions].r_fin = r_fin;
				RegionsData[NumberOfRegions].x_ini= (int *) malloc ((1+r_fin-r_init)*sizeof(int));
				RegionsData[NumberOfRegions].x_fin= (int *) malloc ((1+r_fin-r_init)*sizeof(int));
				RegionsData[NumberOfRegions].n_row= (int *) malloc ((1+r_fin-r_init)*sizeof(int));
				RegionsData[NumberOfRegions].NumberOfPlates=0;
				RegionsData[NumberOfRegions].width = min_plate_w;
				RegionsData[NumberOfRegions].height= y_fin-y_init;
				RegionsData[NumberOfRegions].y_ini = y_init;
				RegionsData[NumberOfRegions++].y_fin = y_fin;
				
				printf("\nPosible matricula en lineas %3d a %3d. (%d)\n",y_init,y_fin,height);
				printf(  "Ancho minimo aproximado: %4d\n\n",min_plate_w);
			}
		}
		r++;
	}
	
	
	
	//Analisis de cada una de las regiones mediante el estudio de sus proyecciones verticales
	for (i=0;i<NumberOfRegions;i++) {
		TRegionsData *rd = &RegionsData[i];
		unsigned long *v_prj=(unsigned long *) malloc (NumCols * sizeof(unsigned long));
		memset(v_prj,0,NumCols*sizeof(unsigned long));
		unsigned char p_prj;
		for (j=rd->y_ini;j<rd->y_fin;j++) {
			//Ahora proyectamos los niveles de gris sobre un array	
			for (k=0;k<NumCols;k++) {
				iplGetPixel(src,k,j,&p_prj);
				v_prj[k]+=p_prj;
			} //end for (k)
		} //end for(y_ini->y_fin)
		iplSet(tmp,0);
		for (k=0;k<NumCols;k++) {
			v_prj[k]/=rd->height;
			//Ahora rellenamos el destino para visualizarlo
			register l=0;
			value=128;
			for (l=0;l<v_prj[k];l++) 
				iplPutPixel(tmp,k,NumRows-l-1,&value);
			//iplPutPixel(tmp,k,NumRows-v_prj[k]-1,&value);
		} //end for(k)
		
		
		
		iplSetBorderMode(tmp,IPL_BORDER_CONSTANT,IPL_SIDE_ALL,0);
		//Ahora tenemos que analizar la proyeccion como una linea sola. Las proyecciones deben
		//haber reducido la probabilidad de error.
		memset(Picos,0,NumCols * sizeof(int));
		memset(Valor_Picos,0,NumCols * sizeof(int));
		memset(Maximos,0,NumCols * sizeof(unsigned char));
		memset(Minimos,0,NumCols * sizeof(unsigned char));
		value=255;
		UMBRAL = UMBRAL*2/3;
		int cnt_picos=0,esc=0,v_max=0,x_max=0,sum=0,x_sec=0;
		x=0;
		while (x<NumCols-1) {
			pixel_g = v_prj[x+1]-v_prj[x];
			if (pixel_g>0) {
				if (esc > 0) {
					//Se continua con un escalon ascendente
					esc+=pixel_g;
					if (pixel_g>v_max) {v_max=pixel_g;x_max=x;}
					
				}
				else {
					//Terminamos la sección y comenzamos una nueva
					if (esc<-UMBRAL) {
						//es un cambio brusco y lo asignamos al pixel entre x_sec y x
						
						//Si el anterior pico tambien era descendente lo quitamos
						if (cnt_picos && (Valor_Picos[cnt_picos-1]<0)) {
							printf("\nRealizando filtrado descendente x=%3d",x);
							cnt_picos--;
							esc+=Valor_Picos[cnt_picos];
							x_sec=Picos[cnt_picos];
						}

						Picos[cnt_picos] = x;
						// y lo guardamos como pico, y el valor maximo y minimo
						Maximos[cnt_picos]=v_prj[x_sec];
						Minimos[cnt_picos]=v_prj[x];
						Valor_Picos	[cnt_picos++]		= esc;
					}
					else if (cnt_picos) {
						//Comprobamos si la diferencia con el pico anterior supera el umbral, si
						//es así, lo ponemos.
						if ((Valor_Picos[cnt_picos-1]<0) && (v_prj[x]<v_prj[Picos[cnt_picos-1]])) {
							printf("\nCorrecion de picos descendentes x=%3d",x);
							esc+=Valor_Picos[cnt_picos-1];
							cnt_picos--;
							Picos[cnt_picos] = x;
							Minimos[cnt_picos] = v_prj[x];
							Valor_Picos[cnt_picos++] = esc;
						}
					}
					esc = v_max = pixel_g;
					x_sec = x_max = x; 
				}

			}
			else if (pixel_g<0) {
				if (esc < 0) {
					//Se continua con un escalon descendente
					esc+=pixel_g;
					if (pixel_g<v_max) {v_max=pixel_g;x_max=x;}
					
				}
				else {
					//Comenzamos una nueva sección
					if (esc>UMBRAL) {
						//es un cambio brusco y lo asignamos al pixel entre x_sec y x
						
						//Si el anterior pico tambien era ascendente lo quitamos
						if (cnt_picos && (Valor_Picos[cnt_picos-1]>0)) {
							printf("\nRealizando filtrado ascendente  x=%3d",x);
							cnt_picos--;
							esc+=Valor_Picos[cnt_picos];
							x_sec=Picos[cnt_picos];
						}

						Picos[cnt_picos]=x;
						// y guardamos el Pico producido
						Maximos[cnt_picos]=v_prj[x];
						Minimos[cnt_picos]=v_prj[x_sec];
						Valor_Picos	[cnt_picos++]		= esc;
					}
					else  if (cnt_picos) {
						//Comprobamos si la diferencia con el pico anterior supera el umbral, si
						//es así, lo ponemos.
						
						if ((Valor_Picos[cnt_picos-1]>0) && (v_prj[x]>v_prj[Picos[cnt_picos-1]])) {
							printf("\nCorrecion de picos ascendentes x=%3d",x);
							esc+=Valor_Picos[cnt_picos-1];
							cnt_picos--;
							Picos[cnt_picos] = x;
							Maximos[cnt_picos] = v_prj[x];
							Valor_Picos[cnt_picos++] = esc;
						}
					}
					
					esc = v_max = pixel_g;
					x_sec = x_max = x; 
				}
			}
			x++;
		} //end while (x<NumCols-1)
		
		
					
		int corte;
		MedianResult r;
		median((void*)Maximos,cnt_picos,8,&r);
		corte=r.ch*3;
		printf("\nNumero de Picos: %d. Maximo: %3d.",cnt_picos,r.ch);
		median((void*)Minimos,cnt_picos,8,&r);
		corte+=r.ch*2;corte/=5;
		printf("  Minimos: %3d. Valor de corte: %3d",r.ch,corte);

		
		//Descartamos los picos maximos por debajo y los minimos por encima del valor de corte.
		int *picos_r,*valor_picos_r,cnt_picos_r=0;
		unsigned char *maximos_r,*minimos_r;
		picos_r			= (int *) malloc (cnt_picos * sizeof(int));
		valor_picos_r	= (int *) malloc (cnt_picos * sizeof(int));
		maximos_r		= (unsigned char *) malloc (cnt_picos * sizeof(unsigned char));
		minimos_r		= (unsigned char *) malloc (cnt_picos * sizeof(unsigned char));
		for (j=0;j<cnt_picos;j++) 
			if (((Valor_Picos[j]>0) && (v_prj[Picos[j]]>corte)) ||
				((Valor_Picos[j]<0) && (v_prj[Picos[j]]<corte))) {
				picos_r[cnt_picos_r]=Picos[j];
				valor_picos_r[cnt_picos_r]=Valor_Picos[j];
				maximos_r[cnt_picos_r]=Maximos[j];
				minimos_r[cnt_picos_r++]=Minimos[j];
			}
		printf("\nPicos fuera de lugar: %3d",cnt_picos-cnt_picos_r);

		printf("\nValores de pico:\n");
		for (x=0;x<cnt_picos_r;x++) {
			printf("[%d,%d,%d]\t",picos_r[x],valor_picos_r[x],v_prj[picos_r[x]]);
		}
		
		//Dibujamos los Picos
		value=255;
		for (x=0;x<cnt_picos_r;x++)
		//for(x=0;x<cnt_picos;x++)
			for (j=-1;j<=1;j++)
				for (k=-1;k<=1;k++) {
					iplPutPixel(tmp,picos_r[x]+j,NumRows-v_prj[picos_r[x]]-2+k,&value);
					iplPutPixel(tmp,picos_r[x]+j,NumRows-20+k,&value);
					//iplPutPixel(tmp,Picos[x]+j,NumRows-v_prj[Picos[x]]-2+k,&value);
					//iplPutPixel(tmp,Picos[x]+j,NumRows-20+k,&value);
				}
		
		value=200;
		for (x=0;x<NumCols;x++) iplPutPixel(tmp,x,NumRows-corte-1,&value);
					
		memcpy(tmp->imageData,src->imageData+(rd->y_ini*NumCols),rd->height*NumCols);
		Image_lpr Proy(NumRows,NumCols);
		memcpy(Proy.pM,tmp->imageData,NumCols*NumRows);
		printf("\nRegion %d. De y=%3d a %3d",i+1,rd->y_ini,rd->y_fin);
		Proy.Show();
		
		
		
		/*
		//Analizamos la linea
		int p=0;
		while (p<cnt_picos-1) {
			//Aqui vamos viendo que la distancia entre cambios bruscos de exceda de max_border_d
			x_ini=pd->Peeks[p];
			while	((p<pd->NumPeeks-1) && 
					((pd->Peeks[p+1]-pd->Peeks[p])<max_border_d))// &&
					//(abs(pd->Maxs[p+1]-pd->Maxs[p])<40) &&
					//(abs(pd->Mins[p+1]-pd->Mins[p])<40))
				p++;
			x_fin=pd->Peeks[p];
			
			//puede que sea una matricula si ...
			if (BETWEEN(x_fin-x_ini,RegionsData[i].width,Round(RegionsData[i].width * 1.30))) {
				printf("Posible matricula encontrada: [%3d,%3d]. Ancho: %3d\n\n",x_ini,x_fin,x_fin-x_ini);
				break;
			}
			else {
				printf("Region encontrada:            [%3d,%3d]. Ancho: %3d\n\n",x_ini,x_fin,x_fin-x_ini);
			}

			p++;
		}
		//*/
		
		getchar();
		free(v_prj);
	} //end for(NumberOfRegions)
	
	
	
	
	
	
	
	
	for (i=0;i<NumberOfRows;i++) {
		free(PeeksData[i].Peeks);
		free(PeeksData[i].PeeksValues);
		free(PeeksData[i].Mins);
		free(PeeksData[i].Maxs);
	}
	free(PeeksData);
	
	for (j=0;j<NumberOfRegions;j++) {
		free(RegionsData[j].x_ini);
		free(RegionsData[j].x_fin);
		free(RegionsData[j].n_row);
	}
	free(RegionsData);

	iplDeallocate(src ,IPL_IMAGE_HEADER);
	iplDeallocate(dst ,IPL_IMAGE_HEADER|IPL_IMAGE_DATA);
	iplDeallocate(tmp ,IPL_IMAGE_HEADER|IPL_IMAGE_DATA);
	iplDeleteConvKernel(edge[0]);
	iplDeleteConvKernel(edge[1]);


} //end iplGetPlate2


/**************************************************************************\
* Name      : iplGetPlate3
* Member of : Image_lpr
* Purpose   : Obtain the number plate location
* Returns   :    
* Parameters: 
* Notes     : Using Hought transform
* Author    : JAA
* Date      : 26.05.00
* Modified  :
\**************************************************************************/
void Image_lpr::iplGetPlate3() {

//Parametros de la matricula
	int UMBRAL		= 30;
	int min_plate_h;
	int max_plate_h;
	int min_plate_w;
	int max_border_d;
	int min_border_d;
	float HxWfactor = 6.05;
	
	
	//Estructura de datos donde se reune toda la información 
	//que se pueda obtener sobre los bordes de las filas
	typedef struct {
		int NumRow;
		int NumPeeks;
		float Mean,Std;
		int *Peeks,*PeeksValues;
		unsigned char *Maxs,*Mins;
	} TPeeksData;

	TPeeksData *PeeksData;
	int NumberOfRows=0;
	
	
	//Estructuras para almacenar las regiones encontradas
	typedef struct {
		int y_ini,y_fin;
		int r_ini,r_fin;
		int width,height;
		int *x_ini,*x_fin,*n_row;
		int NumberOfPlates;
	} TRegionsData;
	
	TRegionsData *RegionsData;
	int NumberOfRegions=0;
	//RegionVector	RegionData;
	//Region			Reg;

	
	register i,j,k;
	int x,y,region_cnt=0,umbral;
	unsigned char value;
	IplImage *src,*dst,*v_edges,*h_edges;
	IplConvKernel *edge[4];
	IplConvKernel *edge0,*edge1;
	int ed_f[]=		{-1, 1,-1, 1,-1, 1,-1, 1,-1, 1};
	int sobel3x3v[]	=	{1 , 0, -1, 2, 0, -2, 1, 0, -1};
	int sobel3x3vi[]=	{-1, 0, 1, -2, 0, 2,-1, 0, 1};
	int sobel3x5[]	=	{1 , 0, -1, 1, 0, -1, 2, 0, -2, 1, 0, -1, 1, 0, -1};
	int sobel3x3h[] =	{1, 2, 1, 0, 0, 0, -1, -2, -1};
	int sobel3x3hi[]=	{-1, -2, -1, 0, 0, 0, 1, 2, 1};
	int laplace[]	=	{-1, -3, -4, -3, -1,-3, 0, 6, 0,-3,-4, 6, 20, 6, -4,-3, 0, 6, 0,-3,-1,-3,-4,-3,-1};
	int lapl[]		=	{-1, 2, -1}; 
	int Gauss5x5[]	=	{2, 7, 12, 7, 2, 7, 31, 52, 31, 7, 12, 52, 127, 52, 12, 7, 31, 52, 31, 7, 2, 7, 12, 7, 2};
	int GaussV[]	=	{2, 7, 12, 7, 2};
	int Gauss3x3[]	=	{1, 2, 1, 2, 4, 2, 1, 2, 1};

	signed char pixel_g,pixel_p;

	//Variables utilizadas para guardar los picos de la imagen (gradientes bruscos)
	int *Picos;
	int *Valor_Picos;
	unsigned char *Maximos;
	unsigned char *Minimos;
	int cnt_picos=0;

	//Variables utilizadas para obtener la mayor concentración de bordes
	float sum=0,mean=0,std=0;


	

	src = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is uchar
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled
	

    dst = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8S,                // data type is int
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

	
	v_edges = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is int
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled

	h_edges = iplCreateImageHeader( 
      1,                            // 1 channel
      0,                            // no alpha channel
      IPL_DEPTH_8U,                // data type is int
      "GRAY",                       // color model
      "GRAY",                       // channel sequence
      IPL_DATA_ORDER_PIXEL,         // channel arrangement
      IPL_ORIGIN_TL,                // top left orientation
      IPL_ALIGN_QWORD,              // 4 bytes align
      NumCols, NumRows,             // image width and height
      NULL, NULL,                   // no ROI, no mask ROI
      NULL, NULL);                  // image ID, not tiled


	src->imageData = (char *)pM;
	iplAllocateImage(dst,1,0);
	
	
	//Show();
	

	Picos		= (int *) malloc (NumCols * sizeof(int));
	Valor_Picos = (int *) malloc (NumCols * sizeof(int));
	Maximos		= (unsigned char *) malloc (NumCols * sizeof(unsigned char));
	Minimos		= (unsigned char *) malloc (NumCols * sizeof(unsigned char));
	PeeksData	= (TPeeksData *)	malloc (NumRows * sizeof(TPeeksData));
	RegionsData	= (TRegionsData *)	malloc ((NumRows/2) * sizeof (TRegionsData));


	//edge[0] = iplCreateConvKernel(3,3,1,1,sobel3x3,1);
	//edge[1] = iplCreateConvKernel(3,3,1,1,sobel3x3h,1);
	
	//Suavizado de la imagen
	if (NumCols<460) {
		edge[0] = iplCreateConvKernel(3,3,1,1,Gauss3x3,4);
		iplConvolve2D(src,src,edge,1,IPL_SUM);
		//iplBlur(src,src,3,3,1,1);
		min_plate_h		= 20;
		max_border_d	= 25;
	}
	else {
		edge[0] = iplCreateConvKernel(5,5,2,2,Gauss5x5,9);
		iplConvolve2D(src,src,edge,1,IPL_SUM);
		//iplBlur(src,src,5,5,2,2);
		min_plate_h		= 35;
		max_border_d	= 45;
	}
	min_plate_h = 20;
	max_plate_h = NumCols / HxWfactor;
	
	iplScale(src,dst);
	
	//Extraccíon de bordes verticales
	//edge[1] = iplCreateConvKernel(3,3,1,1,sobel3x3,1);
	edge[1] = iplCreateConvKernel(2,3,0,1,ed_f,1);
	iplConvolve2D(dst,dst,&edge[1],1,IPL_SUM);
	
	
	////////////////////////////////////////
	// Primera pasada:Obtener informacion //
	////////////////////////////////////////
	for (y=1;y<NumRows-1;y+=1) {
		
		//Busqueda de escalones absolutos en le nivel de gris
		int x_sec=0,x_cnt=0,esc=0,value=0,x_max,v_max;
		cnt_picos=0;
		sum=0;mean=0;std=0;
		x=1;
		while (x<NumCols-1) {
			
			iplGetPixel(dst,x,y,&pixel_g);
			//if (abs(pixel_g)>2) {
				//Si es un cambio 
				iplPutPixel(dst,x,y,&value);
				if (pixel_g>0) {
					if (esc > 0) {
						//Se continua con un escalon ascendente
						esc+=pixel_g;x_cnt++;
						if (pixel_g>v_max) {v_max=pixel_g;x_max=x;}
						
					}
					else {
						//Terminamos la sección y comenzamos una nueva
						if (esc<-UMBRAL) {
							//es un cambio brusco y lo asignamos al pixel entre x_sec y x
							iplPutPixel(dst,x_max,y,&esc);
							// y lo guardamos como pico, y el valor maximo y minimo
							iplGetPixel(src,x,y,Maximos+cnt_picos);
							iplGetPixel(src,x_sec,y,Minimos+cnt_picos);
							Valor_Picos	[cnt_picos]		= esc;
							Picos		[cnt_picos++]	= x_max;
							//Guardamos su posicion
							sum+=x;
							//value=127;
						}
						
						esc = v_max = pixel_g;
						x_sec = x_max = x; 
					}

				}
				else if (pixel_g<0) {
					if (esc < 0) {
						//Se continua con un escalon descendente
						esc+=pixel_g;x_cnt++;
						if (pixel_g<v_max) {v_max=pixel_g;x_max=x;}
						
					}
					else {
						//Comenzamos una nueva sección
						if (esc>UMBRAL) {
							//es un cambio brusco y lo asignamos al pixel entre x_sec y x
							iplPutPixel(dst,x_max,y,&esc);
							// y guardamos el Pico producido
							iplGetPixel(src,x_sec,y,Maximos+cnt_picos);
							iplGetPixel(src,x,y,Minimos+cnt_picos);
							Valor_Picos	[cnt_picos]		= esc;
							Picos		[cnt_picos++]	= x_max;
							//Guardamos su posicion
							sum+=x;
							//value=0;
						}
						
						esc = v_max = pixel_g;
						x_sec = x_max = x; 
					}
				}

			
			x++;
		} //end while (x<NumCols-1)

		//*
		//Calcular desv std
		mean=sum/cnt_picos;
		std=0;
		for (int i=0;i<cnt_picos;i++) {
			float val=mean-Picos[i];
			std+=(val*val);
		}
		std/=cnt_picos;
		std=sqrt(std);

		
		//Guardar datos en PeeksData
		if (cnt_picos>16) {
			PeeksData[NumberOfRows].NumRow		= y;
			PeeksData[NumberOfRows].NumPeeks	= cnt_picos;
			PeeksData[NumberOfRows].Mean		= mean;
			PeeksData[NumberOfRows].Std			= std;
			PeeksData[NumberOfRows].Peeks		= (int *) malloc (cnt_picos * sizeof(int));
			PeeksData[NumberOfRows].PeeksValues	= (int *) malloc (cnt_picos * sizeof(int));
			PeeksData[NumberOfRows].Maxs		= (unsigned char *) malloc (cnt_picos * sizeof(unsigned char));
			PeeksData[NumberOfRows].Mins		= (unsigned char *) malloc (cnt_picos * sizeof(unsigned char));
			memcpy(PeeksData[NumberOfRows].Peeks,Picos,cnt_picos * sizeof(int));
			memcpy(PeeksData[NumberOfRows].PeeksValues,Valor_Picos,cnt_picos * sizeof(int));
			memcpy(PeeksData[NumberOfRows].Maxs,Maximos,cnt_picos * sizeof(unsigned char));
			memcpy(PeeksData[NumberOfRows].Mins,Minimos,cnt_picos * sizeof(unsigned char));
			NumberOfRows++;
			//cout << endl << endl;
			//for (int i=0;i<cnt_picos;i++) printf("%5d",Picos[i]);
		}

		
		//Mostrar datos
		//if (cnt_picos>16) {
		//	printf("\n\nPicos fila %3d=(%d). Media= %4.3f.Desv. Std: %4.3f\n\n",y,cnt_picos,mean,std);
		//	for (int i=0;i<cnt_picos;i++) printf("%5d",Picos[i]);
		//}
		//*/
		
	} //end for(y)
	
	
	
	
	//Liberacion de variables no utilizadas
	//free(Picos);
	//free(Valor_Picos);
	//free(Maximos);
	//free(Minimos);

	
	//Mostrar imagen.
	//iplAbs(dst,dst);
	//iplConvert(dst,src);
	//iplThreshold(src,src,UMBRAL);
	//iplMultiplyS(src,src,3);
	//Show();
	
	
	//Mostrar todos los datos
//	for (i=0;i<NumberOfRows;i++) {
//		TPeeksData *p=PeeksData+i;
//		printf("\nFila: %4d(%d). Media: %7.3f. DesvStd: %7.3f\n",p->NumRow,p->NumPeeks,p->Mean,p->Std);
//		for (j=0;j<p->NumPeeks;j++) {
			//printf("[%3d,%4d]",p->Peeks[j],p->PeeksValues[j]);
			//printf("%4d",p->Peeks[j]);
//			printf("[%3d,%3d,%3d]",p->Peeks[j],(unsigned char)p->Maxs[j],(unsigned char)p->Mins[j]);
//		}
//		printf("\n");
//	}
	

	//Analisis de los datos
	//Primero analizamos las lineas continuas que tienen gran cantidad de cambios
	int y_init=0,y_fin=0,height=0,r_init=0,r_fin=0,r=0;
	//y=0;
	while (r<NumberOfRows-1) {
		r_init=r;
		while ((r<NumberOfRows-1) && ((PeeksData[r+1].NumRow-PeeksData[r].NumRow)<=2)) 
			r++;
		
		r_fin=r;
		
		y_init=PeeksData[r_init].NumRow;
		y_fin =PeeksData[r_fin].NumRow;
		height = y_fin-y_init;
		//printf("\n %d %d %d \n",height,min_plate_h,max_plate_h);
		if (BETWEEN(height,min_plate_h,max_plate_h)) {
			min_plate_w=Round((float)(y_fin-y_init)*HxWfactor);
			if (min_plate_w < NumCols) {
				//Almacenamos la posible region de matricula
				RegionsData[NumberOfRegions].r_ini = r_init;
				RegionsData[NumberOfRegions].r_fin = r_fin;
				RegionsData[NumberOfRegions].x_ini= (int *) malloc ((1+r_fin-r_init)*sizeof(int));
				RegionsData[NumberOfRegions].x_fin= (int *) malloc ((1+r_fin-r_init)*sizeof(int));
				RegionsData[NumberOfRegions].n_row= (int *) malloc ((1+r_fin-r_init)*sizeof(int));
				RegionsData[NumberOfRegions].NumberOfPlates=0;
				RegionsData[NumberOfRegions].width = min_plate_w;
				RegionsData[NumberOfRegions].height= y_fin-y_init;
				RegionsData[NumberOfRegions].y_ini = y_init;
				RegionsData[NumberOfRegions++].y_fin = y_fin;
				
				printf("\nPosible matricula en lineas %3d a %3d. (%d)\n",y_init,y_fin,height);
				printf(  "Ancho minimo aproximado: %4d\n\n",min_plate_w);
			}
		}
		r++;
	}
	
	
	
	///////////////////////////////////////////////////////////////////////////////////////////7
	//Aplicamos Hought a cada region
	///////////////////////////////////////////////////////////////////////////////////////////7
	Image_lpr hor_edges(NumRows,NumCols),ver_edges(NumRows,NumCols);
	DoubleMatrix GrModule(NumRows,NumCols);
	SegmentVector sg,sg_hi,sg_hs;
	v_edges->imageData = (char *) ver_edges.pM;
	h_edges->imageData = (char *) hor_edges.pM;
	ver_edges=CannyW(5,100,100);
	//ver_edges = DrogS(5,50,GrModule);
	//iplCopy(src,v_edges);
	iplCopy(v_edges,h_edges);
	
	edge[0] = iplCreateConvKernel(3,3,1,1,sobel3x3v,1);
	edge[2] = iplCreateConvKernel(3,3,1,1,sobel3x3h,1);
	edge[1] = iplCreateConvKernel(3,3,1,1,sobel3x3vi,1);
	edge[3] = iplCreateConvKernel(3,3,1,1,sobel3x3hi,1);

	
	//iplConvolve2D(src,h_edges,&edge[2],2,IPL_SUMSQROOT);
	iplThreshold(h_edges,h_edges,UMBRAL);
	iplRShiftS(h_edges,h_edges,1);
	iplAddS(h_edges,h_edges,20);
	
	//iplConvolve2D(src,v_edges,edge,2,IPL_SUMSQROOT);
	iplThreshold(v_edges,v_edges,UMBRAL);
	iplRShiftS(v_edges,v_edges,1);
	iplAddS(v_edges,v_edges,20);
	//ver_edges.Show();
	//getchar();

	for (i=0;i<NumberOfRegions;i++) {
		//Para cada region analizamos las lineas verticales y horizontales
		float D=sqrt(NumCols*NumCols+NumRows*NumRows);
		printf("\nAnalizando region: %d",i+1);
		TRegionsData *rd = &RegionsData[i];
		//Horizontales
		/*  // NO TOCAR // FUNCIONA BASTANTE BIEN // UTILIZANDO SOBEL
		printf("\nHorizontales");
		//Parte inferior de la matricula
		hor_edges.houghtLinesP(	0,NumCols,
						MAX(rd->y_fin-10,0),MIN(rd->y_fin+10,NumRows),		//Limites de la region
						-D,D,-5,5,											//Limites en el espacio de parámetros		
						1,1,												//Divisiones del espacio de parámetros
						2,													//Tolerancia para la eliminación de duplicados
						3,													//Maxima distancia para el seguimiento del segmento
						1,													//Maxima desviacion del segmento (en pixeles)
						rd->width*0.8);										//Longitud minima del segmento
		//Parte superior de la matricula
		hor_edges.houghtLinesP(	0,NumCols,
						MAX(rd->y_ini-10,0),MIN(rd->y_ini+10,NumRows),		//Limites de la region
						-D,D,-5,5,											//Limites en el espacio de parámetros		
						1,1,												//Divisiones del espacio de parámetros
						2,													//Tolerancia para la eliminación de duplicados
						3,													//Maxima distancia para el seguimiento del segmento
						1,													//Maxima desviacion del segmento (en pixeles)
						rd->width*0.8);										//Longitud minima del segmento
		hor_edges.Show();
		//getchar();
		//Verticales
		printf("\nVerticales");
		ver_edges.houghtLinesP(	0,NumCols,
						MAX(rd->y_ini-20,0),MIN(rd->y_fin+20,NumRows),		//Limites de la region
						-D,D,85,95,											//Limites en el espacio de parámetros		
						1,1,												//Divisiones del espacio de parámetros
						3,													//Tolerancia para la eliminación de duplicados
						2,													//Maxima distancia para el seguimiento del segmento
						1,													//Maxima desviacion del segmento (en pixeles)
						rd->height*0.8);									//Longitud minima del segmento

		ver_edges.Show();
		//getchar();
		*/
		

		
		printf("\n\n\nHorizontales");
		//Parte inferior de la matricula
		sg_hi=hor_edges.houghtLinesP(	0,NumCols,
						MAX(rd->y_fin-20,0),MIN(rd->y_fin+20,NumRows),		//Limites de la region
						-D,D,-5,5,											//Limites en el espacio de parámetros		
						1,1,												//Divisiones del espacio de parámetros
						1,													//Tolerancia para la eliminación de duplicados
						2,													//Maxima distancia para el seguimiento del segmento
						1,													//Maxima desviacion del segmento (en pixeles)
						rd->width*0.5);										//Longitud minima del segmento
		cout << "\nSegmentos horizontales inferiores: " << sg.size();
		//Parte superior de la matricula
		sg_hs=hor_edges.houghtLinesP(	0,NumCols,
						MAX(rd->y_ini-20,0),MIN(rd->y_ini+20,NumRows),		//Limites de la region
						-D,D,-5,5,											//Limites en el espacio de parámetros		
						1,1,												//Divisiones del espacio de parámetros
						1,	//1												//Tolerancia para la eliminación de duplicados
						2,	//2												//Maxima distancia para el seguimiento del segmento
						1,	//1												//Maxima desviacion del segmento (en pixeles)
						rd->width*0.5);										//Longitud minima del segmento
		cout << "\nSegmentos horizontales superiores: " << sg.size();
		hor_edges.Show();
		//getchar();
		//Verticales
		printf("\n\n\nVerticales");
		sg=ver_edges.houghtLinesP(	0,NumCols,
						MAX(rd->y_ini-20,0),MIN(rd->y_fin+20,NumRows),		//Limites de la region
						-D,D,85,95,											//Limites en el espacio de parámetros		
						1,1,												//Divisiones del espacio de parámetros
						3,	//3												//Tolerancia para la eliminación de duplicados
						3,	//3												//Maxima distancia para el seguimiento del segmento
						1,	//1												//Maxima desviacion del segmento (en pixeles)
						rd->height*0.7);									//Longitud minima del segmento
		cout << "\nSegmentos verticales: " << sg.size();

		ver_edges.Show();
		//getchar();
		
		iplOr(h_edges,v_edges,src);
		Show();

	
		//Analisis de las lineas encontradas. SOLO VERTICALES
		if (sg.size()>1) {
			sg.Show();
			float dist,length,height,width,lj,lk;
			int *y_ini_p,*y_end_p,*x_ini_p,*x_end_p;
			MedianResult m;

			y_ini_p = (int *) malloc (sg.size() * sizeof(int) +1);
			x_ini_p = (int *) malloc (sg.size() * sizeof(int) +1);
			y_end_p = (int *) malloc (sg.size() * sizeof(int) +1);
			x_end_p = (int *) malloc (sg.size() * sizeof(int) +1);
			for (j=0;j<sg.size();j++) {
				y_ini_p[j]=sg[j].p().y();
				x_ini_p[j]=sg[j].p().x();
				y_end_p[j]=sg[j].q().y();
				x_end_p[j]=sg[j].q().x();
			}
			/*
			median((void *) y_ini_p,sg.size(),16,&m);
			y_ini_p[0] = m.in;
			median((void *) x_ini_p,sg.size(),16,&m);
			x_ini_p[0] = m.in;
			median((void *) y_end_p,sg.size(),16,&m);
			y_end_p[0] = m.in;
			median((void *) x_end_p,sg.size(),16,&m);
			x_end_p[0] = m.in;
			printf("\n_ini: %3d. x_end: %3d. y_ini: %3d. y_end: %3d.",x_ini_p[0],x_end_p[0],y_ini_p[0],y_end_p[0]);
			*/
			
			//Almacenamos los posibles emparejamientos. Solo almacenamos los indices j y k
			//de los segmentos origen y destino
			//int *srcs,*dsts,n_plates=0;
			

			for (j=0;j<sg.size()-1;j++) {
				for (k=j+1;k<sg.size();k++) {
					//printf("[%3d,%3d] ",j,k);
					dist = sg[j].MidPointDistance(sg[k]);
					lj=sg[j].Length();lk=sg[k].Length();
					height = (lj+lk) / 2;
					width = (height*315)/64;
					//printf("\nComprobando de %3d,%3d a %3d,%3d. Dist: %f.Altura: %f.Anchura: %f",x_ini_p[j],x_end_p[j],x_ini_p[k],x_end_p[k],dist,height,width);
					if (	(abs(lj-lk)<height*0.25)							&&
							(abs(y_ini_p[j]-y_ini_p[k])<dist*sin(5.0*PI/180))	&&
							(abs(y_end_p[j]-y_end_p[k])<dist*sin(5.0*PI/180))	&&
							(BETWEEN(dist,width*0.8,width*1.2))					) {
						
						//Si se cumple esta primera condición, es decir,que la diferencia de longitud de los
						//segmentos inicial y final no sea demasiado grande, que la altura a la que se encuentran
						//no difiera más de 5 grados, y que la distancia entre ellos entre dentro de los rangos
						//de una matricula, hay que ver si hay algun segmento horizontal cuyos extremos coincidan
						//con los extremos verticales encontrados
						printf("\nPrimera pasada: [%3d,%3d],[%3d,%3d] a [%3d,%3d],[%3d,%3d]\n",
								x_ini_p[j],y_ini_p[j],x_end_p[j],y_end_p[j],x_ini_p[k],y_ini_p[k],x_end_p[k],y_end_p[k]);
						register jhs,jhi;
						bool shs=false,shi=false;
						int v;
						for (jhs=0;((jhs<sg_hs.size()) && !shs);jhs++) {
							v =		abs(sg_hs[jhs].p().x()-x_ini_p[j]) +
									abs(sg_hs[jhs].p().y()-y_ini_p[j]) +
									abs(sg_hs[jhs].q().x()-x_ini_p[k]) +
									abs(sg_hs[jhs].q().y()-y_ini_p[k]);
							shs |= (v<12);
						}

						for (jhi=0;((jhi<sg_hi.size()) && !shi);jhi++) {
							v =		abs(sg_hi[jhi].p().x()-x_end_p[j]) +
									abs(sg_hi[jhi].p().y()-y_end_p[j]) +
									abs(sg_hi[jhi].q().x()-x_end_p[k]) +
									abs(sg_hi[jhi].q().y()-y_end_p[k]);
							shi |= (v<12);
						}

						
						if (shs) {
							printf("\nSegmento superior %3d.  ",jhs-1);
							//sg_hs[jhs-1].Show();
						}
						if (shi) {
							printf("\nSegmento inferior %3d   ",jhi-1);
							//sg_hi[jhi-1].Show();
						}
						
						if (shs || shi)
							printf("\nPosible matricula de [%3d,%3d],[%3d,%3d] a [%3d,%3d],[%3d,%3d]\n",
							x_ini_p[j],y_ini_p[j],x_end_p[j],y_end_p[j],x_ini_p[k],y_ini_p[k],x_end_p[k],y_end_p[k]);
					}
				} //end for(k)
			} //end for (sg.size())
			
			free(y_ini_p);
			free(x_ini_p);
			free(y_end_p);
			free(x_end_p);
		} //end if (sg.size()>1)

	
	} //end for(NumberOfRegions)
	
	
	
	
	
	
	
	
	for (i=0;i<NumberOfRows;i++) {
		free(PeeksData[i].Peeks);
		free(PeeksData[i].PeeksValues);
		free(PeeksData[i].Mins);
		free(PeeksData[i].Maxs);
	}
	free(PeeksData);
	
	for (j=0;j<NumberOfRegions;j++) {
		free(RegionsData[j].x_ini);
		free(RegionsData[j].x_fin);
		free(RegionsData[j].n_row);
	}
	free(RegionsData);

	iplDeallocate(src ,IPL_IMAGE_HEADER);
	iplDeallocate(v_edges ,IPL_IMAGE_HEADER);
	iplDeallocate(h_edges ,IPL_IMAGE_HEADER);
	iplDeallocate(dst ,IPL_IMAGE_HEADER|IPL_IMAGE_DATA);
	iplDeleteConvKernel(edge[0]);
	iplDeleteConvKernel(edge[1]);
	iplDeleteConvKernel(edge[2]);
	iplDeleteConvKernel(edge[3]);



	////////////////////////////
	
	////////////////////////////


} //end iplGetPlate3

  
/**************************************************************************\
* Name      : Median
* Member of : -
* Purpose   : Obtain the median value of the vector
* Returns   : Error code 0:w/o fail, <0: fail 
* Parameters: Pointer to values, vector's length, data length (8,16,32),pointer to result
* Notes     :
* Author    : JAA
* Date      : 22.05.00
* Modified  :
\**************************************************************************/
int GAC::median(void *data_vector,int length, int data_length,MedianResult *value)
{
	char *values=(char *) malloc (length * data_length/8);
	memcpy(values,data_vector,length);

#ifdef USE_INTEL_IPL
	IplImage *ipl_vector;
	
	switch (data_length) {
	case 8:	
		ipl_vector = iplCreateImageHeader( 
			  1,                            // 1 channel
			  0,                            // no alpha channel
			  IPL_DEPTH_8U,                // data type is uchar
			  "GRAY",                       // color model
			  "GRAY",                       // channel sequence
			  IPL_DATA_ORDER_PIXEL,         // channel arrangement
			  IPL_ORIGIN_TL,                // top left orientation
			  IPL_ALIGN_QWORD,              // 4 bytes align
			  length, 1,		             // image width and height
			  NULL, NULL,                   // no ROI, no mask ROI
			  NULL, NULL);                  // image ID, not tiled
		ipl_vector->imageData = (char *) values;
		break;
	case 16:
		ipl_vector = iplCreateImageHeader( 
			  1,                            // 1 channel
			  0,                            // no alpha channel
			  IPL_DEPTH_16S,                // data type is uchar
			  "GRAY",                       // color model
			  "GRAY",                       // channel sequence
			  IPL_DATA_ORDER_PIXEL,         // channel arrangement
			  IPL_ORIGIN_TL,                // top left orientation
			  IPL_ALIGN_QWORD,              // 4 bytes align
			  length, 1,		             // image width and height
			  NULL, NULL,                   // no ROI, no mask ROI
			  NULL, NULL);                  // image ID, not tiled
		ipl_vector->imageData = (char *) values;
		break;
	case 32:
		ipl_vector = iplCreateImageHeader( 
			  1,                            // 1 channel
			  0,                            // no alpha channel
			  IPL_DEPTH_32S,                // data type is uchar
			  "GRAY",                       // color model
			  "GRAY",                       // channel sequence
			  IPL_DATA_ORDER_PIXEL,         // channel arrangement
			  IPL_ORIGIN_TL,                // top left orientation
			  IPL_ALIGN_QWORD,              // 4 bytes align
			  length, 1,		             // image width and height
			  NULL, NULL,                   // no ROI, no mask ROI
			  NULL, NULL);                  // image ID, not tiled
		ipl_vector->imageData = (char *) values;
		break;
	default:
		return -1;
	}


	iplMedianFilter(ipl_vector,ipl_vector,length,1,0,0);

	*value = values[0];
	return 0;
#else
	//Using STL sort
	switch (data_length) {
	case 8: {
			unsigned char *v=(unsigned char *) malloc (length * sizeof(unsigned char));
			memcpy(v,data_vector,length*sizeof(unsigned char));
			sort(v,v+length);
			value->ch = v[length/2];
			return 0;
		}
	case 16: {
			int *v=(int *) malloc (length * sizeof(int));
			memcpy(v,data_vector,length*sizeof(int));
			sort(v,v+length);
			value->in = v[length/2];
			return 0;
		}
	case 32: {
			long *v=(long *) malloc (length * sizeof(long));
			memcpy(v,data_vector,length*sizeof(long));
			sort(v,v+length);
			value->lg = v[length/2];
			return 0;
		}
	default:
			return -1;
	}

#endif
}