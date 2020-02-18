/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: GrayAHgraph.cpp,v $
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

#include <CVL/SegmentMultiAHgraph.h>
#include <CGAL/IO/Window_stream.h>

/**************************************************************************\
*		                                                                   *
*		                    DEFINITIONS                                    *
*                                                                          *
\**************************************************************************/

using namespace GAC;
using namespace CGAL;
using namespace std;

/**************************************************************************\
		
  	  
		                   non-member functions


\**************************************************************************/



/********SegmentNodeValue**************************************************\
		
  	  
		                   class SegmentNodeValue


\**************************************************************************/
/**************************************************************************\
* Name      : SegmentNodeValue
* Member of : SegmentNodeValue
* Purpose   : constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentNodeValue::SegmentNodeValue()
{

}

/**************************************************************************\
* Name      : ~SegmentNodeValue
* Member of : SegmentNodeValue
* Purpose   : destructuctor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentNodeValue::~SegmentNodeValue()
{

}

/**************************************************************************\
* Name      : Show
* Member of : SegmentNodeValue
* Purpose   : Writes object data in console
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentNodeValue::show()
{

    vector<CGALSegment*>::iterator it;
	CGALSegment s;
	for (it = begin(); it != end(); it++)
	{
		s = **it;
		cout << s;	
	}

}

/**************************************************************************\
* Name      : operator<<
* Member of : SegmentNodeValue (friend function)
* Purpose   : To define operator<< in SegmentNodeValue class
* Returns   :    
* Parameters: 
*   s   - ostream
*   snv - SegmentNodeValue
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
ostream &operator<<(ostream &s, const SegmentNodeValue & snv)
{
    SegmentNodeValue snvtemp(snv);
    snvtemp.show();
	return s;
}

/********SegmentNodeAnnotation*********************************************\
		
  	  
		               class SegmentNodeAnnotation


\**************************************************************************/
/**************************************************************************\
* Name      : SegmentNodeAnnotation
* Member of : SegmentNodeAnnotation
* Purpose   : constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentNodeAnnotation::SegmentNodeAnnotation()
{

}

/**************************************************************************\
* Name      : ~SegmentNodeAnnotation
* Member of : SegmentNodeAnnotation
* Purpose   : destructuctor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentNodeAnnotation::~SegmentNodeAnnotation()
{

}

/**************************************************************************\
* Name      : Show
* Member of : SegmentNodeAnnotation
* Purpose   : Writes object data in console
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentNodeAnnotation::show()
{
    cout << "d_label : " << d_label << endl;
}

/**************************************************************************\
* Name      : operator<<
* Member of : SegmentNodeAnnotation (friend function)
* Purpose   : To define operator<< in SegmentNodeAnnotation class
* Returns   :    
* Parameters: 
    s   - ostream
    snv - SegmentNodeAnnotation
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
ostream &operator<<(ostream &s, const SegmentNodeAnnotation & sna)
{
    SegmentNodeAnnotation snatemp(sna);
    snatemp.show();
	return s;
}

/********SegmentAnnotatedNode**********************************************\
		
  	  
		               class SegmentAnnotatedNode


\**************************************************************************/
/**************************************************************************\
* Name      : SegmentAnnotatedNode
* Member of : SegmentAnnotatedNode
* Purpose   : constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
/*
SegmentAnnotatedNode::SegmentAnnotatedNode()
{

}
*/

/**************************************************************************\
* Name      : ~SegmentAnnotatedNode
* Member of : SegmentAnnotatedNode
* Purpose   : destructuctor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentAnnotatedNode::~SegmentAnnotatedNode()
{

}

/**************************************************************************\
* Name      : show
* Member of : SegmentAnnotatedNode
* Purpose   : Writes object data in console
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentAnnotatedNode::show()
{
    d_annotation.show();
    d_value.show();
}

/**************************************************************************\
* Name      : operator<<
* Member of : SegmentAnnotatedNode (friend function)
* Purpose   : To define operator<< in SegmentAnnotatedNode class
* Returns   :    
* Parameters: 
*   s   - ostream
*   san - SegmentAnnotatedNode
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
ostream &operator<<(ostream &s, SegmentAnnotatedNode san)
{
	return s;
}

/**************************************************************************\
* Name      : operator>>
* Member of : SegmentAnnotatedNode (friend function)
* Purpose   : To define operator>> in SegmentAnnotatedNode class
* Returns   :    
* Parameters: 
*   s   - istream
*   san - SegmentAnnotatedNode
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
istream &operator>>(istream &s, SegmentAnnotatedNode san)
{
	return s;
}



/********SegmentArcCost****************************************************\
		
  	  
		               class SegmentArcCost


\**************************************************************************/
/**************************************************************************\
* Name      : SegmentArcCost
* Member of : SegmentArcCost
* Purpose   : constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentArcCost::SegmentArcCost()
{

}

/**************************************************************************\
* Name      : ~SegmentArcCost
* Member of : SegmentArcCost
* Purpose   : destructuctor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentArcCost::~SegmentArcCost()
{

}

/**************************************************************************\
* Name      : show
* Member of : SegmentArcCost
* Purpose   : Writes object data in console
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 20.04.00
* Modified  :
\**************************************************************************/
SegmentArcCost::show()
{
    cout << "d_affinity : " << d_affinity << endl;
}

/********SegmentArcAnnotation**********************************************\
		
  	  
		               class SegmentArcAnnotation


\**************************************************************************/
/**************************************************************************\
* Name      : SegmentArcAnnotation
* Member of : SegmentArcAnnotation
* Purpose   : constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentArcAnnotation::SegmentArcAnnotation()
{

}

/**************************************************************************\
* Name      : ~SegmentArcAnnotation
* Member of : SegmentArcAnnotation
* Purpose   : destructuctor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentArcAnnotation::~SegmentArcAnnotation()
{

}

/**************************************************************************\
* Name      : show
* Member of : SegmentArcAnnotation
* Purpose   : Writes object data in console
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 20.04.00
* Modified  :
\**************************************************************************/
SegmentArcAnnotation::show()
{
    cout << "d_type : "; // << d_type << endl;
    switch (d_type){
    case ARC_TYPE_PERONA:
        {
            cout << "PERONA" << endl;
            cout << " d_d0: "     << d_perona.d_d0 << endl; 
            cout << " d_theta0: " << d_perona.d_theta0 << endl; 
            cout << " d_delta: "  << d_perona.d_delta << endl; 
            cout << " d_dij: "    << d_perona.d_dij << endl; 
            cout << " d_alfai: "  << d_perona.d_alfai << endl; 
            cout << " d_alfaj: "  << d_perona.d_alfaj << endl; 
            cout << " d_proximity: "     << d_perona.d_proximity << endl; 
            cout << " d_collinearity: "  << d_perona.d_collinearity << endl; 
            cout << " d_cocircularity: " << d_perona.d_cocircularity << endl; 
        }
        break;
    case ARC_TYPE_PROX:
        {
            cout << "PROXIMITY" << endl;
            cout << " d_distance: " << d_proximal.d_dij << endl; 
        }
        break;
    case ARC_TYPE_PAR:
        {
            cout << "PARALLELISM" << endl;
            cout << " d_dij     : " << d_parallel.d_dij      << endl; 
            cout << " d_alfaij  : " << d_parallel.d_alfaij   << " (deg:" << d_parallel.d_alfaij*180.0/PI << ")" << endl; 
            cout << " d_overlap : " << d_parallel.d_overlap  << endl; 
        }
        break;
    case ARC_TYPE_COL:
        {
            cout << "COLLINEARITY" << endl;
            cout << " d_dij     : " << d_collinear.d_dij      << endl; 
            cout << " d_alfai   : " << d_collinear.d_alfai    << " (deg:" << d_collinear.d_alfai*180.0/PI << ")" << endl; 
            cout << " d_alfaj   : " << d_collinear.d_alfaj    << " (deg:" << d_collinear.d_alfaj*180.0/PI << ")" << endl;  
       }
        break;
    case ARC_TYPE_CONV:
        {
            cout << "CONVEXITY" << endl;
            cout << " d_dij     : " << d_convex.d_dij      << endl; 
            cout << " d_alfai   : " << d_convex.d_alfai    << " (deg:" << d_convex.d_alfai*180.0/PI << ")" << endl; 
            cout << " d_alfaj   : " << d_convex.d_alfaj    << " (deg:" << d_convex.d_alfaj*180.0/PI << ")" << endl;  
        }
        break;
    default:
        {
            cout << "UNDETERMINED" << endl;
        }
        break;
    }

}


/********SegmentAnnotatedArc***********************************************\
		
  	  
		               class SegmentAnnotatedArc


\**************************************************************************/
/**************************************************************************\
* Name      : SegmentAnnotatedArc
* Member of : SegmentAnnotatedArc
* Purpose   : constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentAnnotatedArc::SegmentAnnotatedArc()
{

}

/**************************************************************************\
* Name      : ~SegmentAnnotatedArc
* Member of : SegmentAnnotatedArc
* Purpose   : destructuctor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentAnnotatedArc::~SegmentAnnotatedArc()
{

}

/**************************************************************************\
* Name      : show
* Member of : SegmentAnnotatedArc
* Purpose   : Writes object data in console
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentAnnotatedArc::show()
{
    d_cost.show();
    d_annotation.show();
}

/********SegmentPUAmultigraph**********************************************\
		
  	  
		               class SegmentPUAmultigraph


\**************************************************************************/
/**************************************************************************\
* Name      : SegmentPUAmultigraph
* Member of : SegmentPUAmultigraph
* Purpose   : constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentPUAmultigraph::SegmentPUAmultigraph()
{

}

/**************************************************************************\
* Name      : ~SegmentPUAmultigraph
* Member of : SegmentPUAmultigraph
* Purpose   : destructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentPUAmultigraph::~SegmentPUAmultigraph()
{

}

/**************************************************************************\
* Name      : test
* Member of : 
* Purpose   : Test different approaches to do things with gw_action
* Returns   :    
* Parameters: 
*    gw         - GraphWin object
*    leda_point - point where mouse is clicked.
* Notes     : SegmentPUAmultigraph's free function
* Author    : GAC
* Date      : 17.04.00
* Modified  :
\**************************************************************************/
void test(GraphWin& gw, const leda_point&)
{ 
	leda_node lu,lv;
	leda_list<leda_node> selectedNodes;
    SegmentAnnotatedNode *u;

	lv  = gw.get_edit_node();
	int col = (gw.get_color(lv) + 1) % 16;
	gw.set_color(lv,leda_color(col));

    const leda_graph& G = gw.get_graph();
    selectedNodes = gw.get_selected_nodes();
	forall(lu,selectedNodes){
		u = (SegmentAnnotatedNode*)lu->data(0);
		u->show();
		printf("Cambio de color\n");
	}
	printf("paso\n");

//	u = G.inf(v);
 }

/**************************************************************************\
* Name      : redrawWindow
* Member of : SegmentMultiAHgraph
* Purpose   : redraws the segment window (when resize, refresh ,...)
* Returns   :    
* Parameters:
* Notes     :
* Author    : GAC
* Date      : 20.04.00
* Modified  :
\**************************************************************************/
CGALpSegmentVector globalpSV; // Guarrerida española para pasar SegmentVector a
                              // esta función.

void redrawWindow(leda_window *W)
{
    W->clear();
    *W << globalpSV;
}

/**************************************************************************\
* Name      : showSegmentWindow
* Member of : 
* Purpose   : Implements add_node_menu for showing segment window
* Returns   :    
* Parameters: 
*    gw         - GraphWin object
*    leda_point - point where mouse is clicked.
* Notes     : SegmentPUAmultigraph's free function
* Author    : GAC
* Date      : 17.04.00
* Modified  :
\**************************************************************************/
void showSegmentWindow(GraphWin& gw /*, const leda_point&*/)
{ 
    leda_node lu;
	leda_list<leda_node> selectedNodes;
    const leda_graph& G = gw.get_graph();

    SegmentAnnotatedNode u;
    SegmentNodeValue SNV;
    SegmentNodeValue::iterator SNVit;

    CGALSegment *pS;
//    CGALpSegmentVector pSV;
    CGALpSegmentVector::iterator pSVit;

    //Set initial vector of segment pointers (globalpSV)
    //Segments are initializaed with leda_blue color
    forall_nodes(lu,G) {
		u = *(SegmentAnnotatedNode*)lu->data(0);
        SNV = u.d_value;
        for (SNVit = SNV.begin();SNVit != SNV.end(); SNVit++){
            pS = *SNVit;
            pS->d_color = leda_blue;
            globalpSV.push_back(pS);            
        }
	}


    //Selected nodes are set with leda_red color
    selectedNodes = gw.get_selected_nodes();
	forall(lu,selectedNodes){
		u = *(SegmentAnnotatedNode*)lu->data(0);
        SNV = u.d_value;
        for (SNVit = SNV.begin();SNVit != SNV.end(); SNVit++){
            pS = *SNVit;
            pSVit = find(globalpSV.begin(), globalpSV.end(), pS);
            (*pSVit)->d_color = leda_red;
        }
    }

    //Display results
    leda_window W(300,300,"Segments");
    W.set_bg_color(leda_white);
//  W.set_fg_color(leda_blue);
    W.init(0,255,0);
//  W.set_show_coordinates(true);
    W.set_redraw(redrawWindow);
    W.display(10,10);
    W.redraw();

    W.message("click to proceed");
    W.read_mouse();

}


/**************************************************************************\
* Name      : showSegmentAnnotatedNode
* Member of : 
* Purpose   : Implements gw_action for showing SegmentAnnotatedNode information
* Returns   :    
* Parameters: 
*    gw         - GraphWin object
*    leda_point - point where mouse is clicked.
* Notes     : SegmentPUAmultigraph's free function
* Author    : GAC
* Date      : 17.04.00
* Modified  :
\**************************************************************************/
void showSegmentAnnotatedNode(GraphWin& gw, const leda_point&)
{ 
	leda_node lu;
    SegmentAnnotatedNode *u;

	lu  = gw.get_edit_node();
    gw.deselect_all_nodes();
    gw.select(lu);
	u = (SegmentAnnotatedNode*)lu->data(0);
	printf("SegmentAnnotatedNode\n====================\n");
	u->show();
	printf("\n");
    showSegmentWindow(gw);
}

void showSegmentAnnotatedArc(GraphWin& gw, const leda_point&)
{ 
	leda_edge le;
    SegmentAnnotatedArc *e;

	le  = gw.get_edit_edge();
	e = (SegmentAnnotatedArc*)le->data(0);
	printf("SegmentAnnotatedArc\n====================\n");
	e->show();
	printf("\n");
}


/**************************************************************************\
* Name      : Edit
* Member of : SegmentPUAmultigraph
* Purpose   : Displays a graphical output of the graph
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentPUAmultigraph::edit()
{
	int xwin,ywin;

	xwin = 650;
	ywin = 500;

    GraphWin gw(*this,xwin,ywin,"Department of System Engineering and Automation. University of Malaga");
    gw.set_zoom_objects(true);
	gw.set_animation_steps(0);
	gw.message(leda_string("Segment Plain Undirected Annotated graph"));
    gw.set_bg_color(leda_white);

    //Node related
    gw.set_node_label_font(roman_font,8);
	gw.set_node_width(10);
    gw.set_node_height(10);
	gw.set_node_label_type(user_label);	

    //Edge related
    gw.set_edge_width(1);

    // MENUS
    // gw.set_default_menu(M_COMPLETE & ~M_LAYOUT & ~M_OPTIONS & ~M_HELP & ~M_WINDOW);
    //gw.add_node_menu("show segments",showSegmentWindow);
    int menu1 = gw.add_menu("Segments");
    gw.add_simple_call(showSegmentWindow,"show",menu1);

    //ACTIONS
    //gw.set_action(A_LEFT | A_NODE | A_SHIFT, showSegmentAnnotatedNode);
    gw.set_action(A_LEFT | A_NODE, showSegmentAnnotatedNode);
    gw.set_action(A_LEFT | A_NODE | A_CTRL, test);
    gw.set_action(A_LEFT | A_EDGE, showSegmentAnnotatedArc);


    //SET NODE LABELS
    SegmentAnnotatedNode *u;
    leda_node lu;
    leda_string s;
    forall_nodes(lu,*this) {
		//string set_label(node v, string s, bool adjust=false);
		u = (SegmentAnnotatedNode*)lu->data(0);
		leda_string s("%i",u->d_annotation.d_label);
        gw.set_label(lu, s, false);
	}

    //SET EDGE COLORS
    SegmentAnnotatedArc *e;
    leda_edge le;
    double level;
    int r,g,b;
    forall_edges(le,*this){
       e = (SegmentAnnotatedArc*)le->data(0);

        switch (e->d_annotation.d_type){
        case SegmentArcAnnotation::ARC_TYPE_PERONA:
            {
                gw.set_color(le,leda_brown);
            }
            break;
        case SegmentArcAnnotation::ARC_TYPE_PROX:
            {
                level = 1.0-(e->d_cost.d_affinity);
                Level2Color (level,r,g,b,ORANGE);
                leda_color c(r,g,b); //Don't run c.set_rgb(r,g,b);
                gw.set_color(le,c);
            }
            break;
        case SegmentArcAnnotation::ARC_TYPE_PAR:
            {           
                level = 1.0-(e->d_cost.d_affinity);
                Level2Color (level,r,g,b,RED);
                leda_color c(r,g,b); //Don't run c.set_rgb(r,g,b);
                gw.set_color(le,c);
            }
            break;
        case SegmentArcAnnotation::ARC_TYPE_COL:
            {
                level = 1.0-(e->d_cost.d_affinity);
                Level2Color (level,r,g,b,GREEN);
                leda_color c(r,g,b); //Don't run c.set_rgb(r,g,b);
                gw.set_color(le,c);
            }
            break;
        case SegmentArcAnnotation::ARC_TYPE_CONV:
            {
                level = 1.0-(e->d_cost.d_affinity);
                Level2Color (level,r,g,b,BLUE);
                leda_color c(r,g,b); //Don't run c.set_rgb(r,g,b);
                gw.set_color(le,c);
            }
            break;
        default:
            {
                gw.set_color(le,leda_yellow);
            }
            break;
        }
    }
    gw.display();
 	gw.place_into_win();
	gw.edit();

}


SegmentPUAmultigraph::Level2Color(double level,int &r, int &g, int &b, Colormap cm){

    Line lr,lg,lb;
    double rymin,rymax,gymin,gymax,bymin,bymax;

    double xmin,xmax;

    switch (cm){
    case RED:
        {
            rymin = 200.0;
            rymax = 248.0;
            gymin = 27.0;
            gymax = 224.0;
            bymin = 27.0;
            bymax = 224.0;
        }
        break;
    case GREEN:
        {
            rymin = 30.0;
            rymax = 240.0;
            gymin = 154.0;
            gymax = 221.0;
            bymin = 30.0;
            bymax = 240.0;
        }
        break;
    case BLUE:
        {
            rymin = 12.0;
            rymax = 233.0;
            gymin = 12.0;
            gymax = 233.0;
            bymin = 140.0;
            bymax = 240.0;
        }
        break;
    case ORANGE:
        {
            rymin = 250.0;
            rymax = 255.0;
            gymin = 174.0;
            gymax = 255.0;
            bymin = 0.0;
            bymax = 250.0;
        }
        break;
    default:
        {
        }
        break;
    }
 
    xmin = 0.0;
    xmax = 1.0;

    lr.Set(xmin,rymin,xmax,rymax);
    lg.Set(xmin,gymin,xmax,gymax);
    lb.Set(xmin,bymin,xmax,bymax);
    r = lr.m()*level+lr.n();
    g = lg.m()*level+lg.n();
    b = lb.m()*level+lb.n();
}

/**************************************************************************\
* Name      : s
* Member of : SegmentPUAmultigraph
* Purpose   : Builds a new abstracted graph.
* Returns   : a boolean value indicating if abstraction process was sucessful
*             (if a new graph was built)   
* Parameters: 
*    newGraph - the new abstracted graph
* Notes     :
* Author    : GAC
* Date      : 18.04.00
* Modified  :
\**************************************************************************/
bool SegmentPUAmultigraph::s(SegmentPUAmultigraph &newGraph){
	//TO DO: call to clustering process
	return true;
}

/**************************************************************************\
* Name      : hideEdgesOfType
* Member of : SegmentPUAmultigraph
* Purpose   : It hides edges of determinated types
* Returns   : *this 
* Parameters: 
*    type - type of edge
* Notes     :
* Author    : GAC
* Date      : 21.04.00
* Modified  :
\**************************************************************************/
SegmentPUAmultigraph &SegmentPUAmultigraph::hideEdgesOfType(SegmentArcAnnotation::PerceptualSuit type){
    leda_edge le;
    SegmentAnnotatedArc *e;

    forall_edges(le,*this){
        e = (SegmentAnnotatedArc*)le->data(0);

        if (e->d_annotation.d_type == type) {
            hide_edge(le);
        }
    }
    return *this;
}

/**************************************************************************\
* Name      : restoreEdgesOfType
* Member of : SegmentPUAmultigraph
* Purpose   : It restores edges of determinated types
* Returns   : *this 
* Parameters: 
*    type - type of edge
* Notes     :
* Author    : GAC
* Date      : 21.04.00
* Modified  :
\**************************************************************************/
SegmentPUAmultigraph &SegmentPUAmultigraph::restoreEdgesOfType(SegmentArcAnnotation::PerceptualSuit type){
    leda_edge le;
    SegmentAnnotatedArc *e;

    forall_edges(le,*this){
        e = (SegmentAnnotatedArc*)le->data(0);

        if (e->d_annotation.d_type == type) {
            restore_edge(le);
        }
    }
    return *this;
}

/**************************************************************************\
* Name      : affinityPerona
* Member of : SegmentPUAmultigraph
* Purpose   : Computes Perona's affinity function
* Returns   : *this 
* Parameters: 
*   d0      : reference distance below which two points are thought to be similar
*             and beyond which two points are thought to be dissimilar
*   theta0  : scaling constant between PI/2 and PI/10
*   delta   : scaling constant between 1/2 and 1/4
*   dij     : Distance between midpoints of segments
*   alfai   : Angle between segment i and the segment between midpoints
*   alfaj   : Angle betwwen segment j and the segment between midpoints
* Notes     :
* Author    : GAC
* Date      : 21.04.00
* Modified  :
\**************************************************************************/
double SegmentPUAmultigraph::affinityPerona(double d0, 
                                            double theta0, 
                                            double delta, 
                                            double dij,
                                            double alfai,
                                            double alfaj){
    double A; // distance related term;
    double B; // collinearity related term;
    double C; // cocircularity related term;
    double affinity;

    A = (dij*dij)/(d0*d0);
    B = (2-cos(2*alfai)-cos(2*alfaj))/(1-cos(2*theta0));
    C = (1-cos(2*alfai - 2*alfaj))/(1-cos(2*delta*theta0));

    affinity = exp(-A-B-C);
/*
    cout << "d0       : " << d0 << endl;
    cout << "theta0   : " << theta0 << endl;
    cout << "delta    : " << delta << endl;
    cout << "dij      : " << dij << endl;
    cout << "alfai    : " << alfai << endl;
    cout << "alfaj    : " << alfaj << endl;
    cout << "A        : " << A << endl;
    cout << "B        : " << B << endl;
    cout << "C        : " << C << endl;
    cout << "affinity : " << affinity << endl;
    cout << "===============================\n";
*/
    return affinity;
}

/**************************************************************************\
* Name      : affinityProximity
* Member of : SegmentPUAmultigraph
* Purpose   : Computes the distance realated term of Perona's affinity function
* Returns   : Affinity (see the code below) 
* Parameters: 
*   d0      : reference distance below which two points are thought to be similar
*   dij     : Distance between midpoints of segments
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
double SegmentPUAmultigraph::affinityProximity(double d0,double dij){
    double term;
    double affinity;

    term     = (dij*dij)/(d0*d0);
    affinity = exp(-term);

    return affinity;
}

/**************************************************************************\
* Name      : affinityCollinearity
* Member of : SegmentPUAmultigraph
* Purpose   : Computes the collinearity realated term of Perona's affinity function
* Returns   : Affinity (see the code below) 
* Parameters: 
*   theta0  : scaling constant between PI/2 and PI/10
*   alfai   : Angle between segment i and the segment between midpoints
*   alfaj   : Angle betwwen segment j and the segment between midpoints
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
double SegmentPUAmultigraph::affinityCollinearity(double theta0,double alfai,double alfaj){
    double term;
    double affinity;

    term = (2-cos(2*alfai)-cos(2*alfaj))/(1-cos(2*theta0));
    affinity = exp(-term);

    return affinity;
}

/**************************************************************************\
* Name      : affinityCocircularity
* Member of : SegmentPUAmultigraph
* Purpose   : Computes the cocircularity realated term of Perona's affinity function
* Returns   : Affinity (see the code below) 
* Parameters: 
*   theta0  : scaling constant between PI/2 and PI/10
*   delta   : scaling constant between 1/2 and 1/4
*   alfai   : Angle between segment i and the segment between midpoints
*   alfaj   : Angle betwwen segment j and the segment between midpoints
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
double SegmentPUAmultigraph::affinityCocircularity(double theta0,double delta,double alfai,double alfaj){
    double term;
    double affinity;

    term     = (1-cos(2*alfai - 2*alfaj))/(1-cos(2*delta*theta0));
    affinity = exp(-term);

    return affinity;
}

/**************************************************************************\
* Name      : affinityParallelism
* Member of : SegmentPUAmultigraph
* Purpose   : Computes the parallelism related term of a similar Perona's affinity function
* Returns   : Affinity (see the code below) 
* Parameters: 
*   theta0  : scaling constant between PI/2 and PI/10
*   delta   : scaling constant between 1/2 and 1/4
*   alfai   : Angle between segment i and the segment between midpoints
*   alfaj   : Angle betwwen segment j and the segment between midpoints
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
double SegmentPUAmultigraph::affinityParallelism(double theta0,double delta,double alfaij){
    double term;
    double affinity;

    term     = (1-cos(2*alfaij))/(1-cos(2*delta*theta0));
    affinity = exp(-term);

    return affinity;
}

/**************************************************************************\
* Name      : setPeronaArcs
* Member of : SegmentPUAmultigraph
* Purpose   : Set Perona relations (arcs) in the SegmentPUAmultigraph
* Returns   : *this   
* Parameters: 
*   d0      : reference distance below which two points are thought to be similar
*             and beyond which two points are thought to be dissimilar
*   theta0  : scaling constant between PI/2 and PI/10
*   delta   : scaling constant between 1/2 and 1/4
* Notes     :
* Author    : GAC
* Date      : 02.05.00
* Modified  :
\**************************************************************************/
/*
SegmentPUAmultigraph &SegmentPUAmultigraph::setPeronaArcs(double d0, double theta0, double delta){
    vector<Image::Segment*> pSegmentSet;
	map<Image::Segment*,leda_node> MNode;

    Image::Segment Si,Sj,Sij;
    vector<Image::Segment*>::iterator svit1,svit2;

   	leda_node lu,lv;
    leda_edge le;

    SegmentAnnotatedNode u,v;
    SegmentAnnotatedArc  e;

    double dij,alfai,alfaj;

    //Extraction of abstract segments
    forall_nodes(lu,*this){
        u=inf(lu);
        pSegmentSet.push_back(u.d_annotation.d_abstractSegment);
		MNode[u.d_annotation.d_abstractSegment]=lu;
    }

	//Edge creation process
	for (svit1 = pSegmentSet.begin(); svit1 != pSegmentSet.end(); svit1++){
		Si  = (**svit1);
		for (svit2 = svit1+1; svit2 != pSegmentSet.end(); svit2++){
			Sj  = (**svit2);

            Sij.Set(Si.MidPoint(),Sj.MidPoint());

            alfai = Si.ShortAngle(Sij);
            alfaj = Sj.ShortAngle(Sij);

			//Calculo la distancia entre los puntos medios de S1aux y S2aux
			dij = Sij.Mod();

            lu = MNode[*svit1];
			lv = MNode[*svit2];
            le = new_edge(lu,lv);

            //AnnotatedArc::d_cost
            e.d_cost.d_affinity = affinityPerona(d0,theta0,delta,dij,alfai,alfaj);

            //AnnotatedArc::d_annotation
            e.d_annotation.d_type = SegmentArcAnnotation::ARC_TYPE_PERONA;
            e.d_annotation.d_perona.d_d0      = d0;
            e.d_annotation.d_perona.d_theta0  = theta0;
            e.d_annotation.d_perona.d_delta   = delta;
            e.d_annotation.d_perona.d_alfai   = alfai;
            e.d_annotation.d_perona.d_alfaj   = alfaj;
            e.d_annotation.d_perona.d_dij     = dij;
            e.d_annotation.d_perona.d_proximity     = affinityProximity    (d0,dij);
            e.d_annotation.d_perona.d_collinearity  = affinityCollinearity (theta0,alfai,alfaj);
            e.d_annotation.d_perona.d_cocircularity = affinityCocircularity(theta0,delta,alfai,alfaj);

            assign(le,e);
		}
	}
    return *this;
}
*/

/**************************************************************************\
* Name      : setParallelArcs
* Member of : SegmentPUAmultigraph
* Purpose   : Set parallel relations (arcs) in the SegmentPUAmultigraph
* Returns   : *this   
* Parameters: 
*   d0      : reference distance below which two points are thought to be similar
*             and beyond which two points are thought to be dissimilar
*   theta0  : scaling constant between PI/2 and PI/10
*   delta   : scaling constant between 1/2 and 1/4
* Notes     :
* Author    : GAC
* Date      : 02.05.00
* Modified  :
\**************************************************************************/
SegmentPUAmultigraph &SegmentPUAmultigraph::setParallelArcs(double d0, double theta0, double delta){

    leda_list<leda_node> NodeSet;

    vector<leda_node> nv;
    vector<leda_node>::iterator lnvit1,lnvit2;

    Image::Segment S1,S2,S1aux,S2aux,S1S2,AuxS;
    Point2D S1A,S1B,S2A,S2B;
    Point2D S2AinS1,S2BinS1,S1AinS2,S1BinS2;

   	leda_node lu,lv;
    leda_edge le;

    SegmentAnnotatedNode u,v;
    SegmentAnnotatedArc  e;

    double dij,alfaij,Overlap;

    //Due to problems with the bad implementation of leda iterators,
    //a copy to STL vector is carried out
    NodeSet = all_nodes();
    nv.resize(NodeSet.size());
	copy(NodeSet.begin(),NodeSet.end(),nv.begin());


	//Edge creation process
	for (lnvit1 = nv.begin(); lnvit1 != nv.end(); lnvit1++){
        u=inf(*lnvit1); //*lnvit1 is a leda_node, son inf(*lnvit1) is a AnnotatedNode
        S1 = u.d_annotation.d_abstractSegment.GetImageSegment();
		S1A = S1.p();
		S1B = S1.q();
		for (lnvit2 = lnvit1+1; lnvit2 != nv.end(); lnvit2++){
            v=inf(*lnvit2);
            S2 = v.d_annotation.d_abstractSegment.GetImageSegment();
			S2A = S2.p();
			S2B = S2.q();
			//Si S1 y S2 forman un angulo menor que MaxAngle ...
            alfaij = S1.Line::Angle(S2);
			if (alfaij>HALF_PI) alfaij = PI-alfaij;

			//Trazo la perpendicular a S2 por cada uno de sus extremos
			//y obtengo los puntos de corte con S1
			//Hago lo mismo con S1 sobre S2
			S2AinS1 = S1.Intersection(S2.PerpLine(S2A));
			S2BinS1 = S1.Intersection(S2.PerpLine(S2B));
			S1AinS2 = S2.Intersection(S1.PerpLine(S1A));
			S1BinS2 = S2.Intersection(S1.PerpLine(S1B));

			S1aux = S1;
            if (S1A.Distance(S2AinS1) > S1aux.Mod()) S1aux = Image::Segment(0,S1A,S2AinS1);
			if (S1A.Distance(S2BinS1) > S1aux.Mod()) S1aux = Image::Segment(0,S1A,S2BinS1);
			if (S1B.Distance(S2AinS1) > S1aux.Mod()) S1aux = Image::Segment(0,S1B,S2AinS1);
			if (S1B.Distance(S2BinS1) > S1aux.Mod()) S1aux = Image::Segment(0,S1B,S2BinS1);

			S2aux = S2;
			if (S2A.Distance(S1AinS2) > S2aux.Mod()) S2aux = Image::Segment(0,S2A,S1AinS2);
			if (S2A.Distance(S1BinS2) > S2aux.Mod()) S2aux = Image::Segment(0,S2A,S1BinS2);
			if (S2B.Distance(S1AinS2) > S2aux.Mod()) S2aux = Image::Segment(0,S2B,S1AinS2);
			if (S2B.Distance(S1BinS2) > S2aux.Mod()) S2aux = Image::Segment(0,S2B,S1BinS2);

			//Calculo la distancia entre los puntos medios de S1aux y S2aux
			dij = fabs(S1.MidPoint().Distance(S2.MidPoint()));

			//Calculo el solapamiento entre S1 y la proyección de S2 sobre S1
            if (S1.Overlap(Image::Segment(0,S2AinS1,S2BinS1),S1S2)){
                Overlap = S1S2.Mod();

                double affinityDistanceRelatedTerm = affinityProximity(d0,dij);
                double affinityParallelRelatedTerm = affinityParallelism(theta0,delta,alfaij);

                //AnnotatedArc::d_cost
                e.d_cost.d_affinity = affinityDistanceRelatedTerm * affinityParallelRelatedTerm;

                if (e.d_cost.d_affinity >= 0.1){

                    lu = *lnvit1;
			        lv = *lnvit2;
                    le = new_edge(lu,lv);

                    //AnnotatedArc::d_annotation
                    e.d_annotation.d_type = SegmentArcAnnotation::ARC_TYPE_PAR;
                    e.d_annotation.d_parallel.d_dij      = dij;
                    e.d_annotation.d_parallel.d_alfaij   = alfaij;
                    e.d_annotation.d_parallel.d_overlap  = Overlap;

                    assign(le,e);
                }
            }
            else {
                Overlap = 0.0;
            }

		}
	}
    return *this;
}

/**************************************************************************\
* Name      : setCollinearArcs
* Member of : SegmentPUAmultigraph
* Purpose   : Set collinear relations (arcs) in the SegmentPUAmultigraph
* Returns   : *this   
* Parameters: 
*   d0      : reference distance below which two points are thought to be similar
*             and beyond which two points are thought to be dissimilar
*   theta0  : scaling constant between PI/2 and PI/10
*   delta   : scaling constant between 1/2 and 1/4
* Notes     :
* Author    : GAC
* Date      : 02.05.00
* Modified  :
\**************************************************************************/
SegmentPUAmultigraph &SegmentPUAmultigraph::setCollinearArcs(double d0, double theta0, double delta){

    leda_list<leda_node> NodeSet;

    vector<leda_node> nv;
    vector<leda_node>::iterator lnvit1,lnvit2;

    Image::Segment S1,S2,S12;
    Point2D S1A,S1B,S2A,S2B;
    Point2D S2AinS1,S2BinS1,S1AinS2,S1BinS2;

   	leda_node lu,lv;
    leda_edge le;

    SegmentAnnotatedNode u,v;
    SegmentAnnotatedArc  e;

    double dij,alfai,alfaj;

    //Due to problems with the bad implementation of leda iterators,
    //a copy to STL vector is carried out
    NodeSet = all_nodes();
    nv.resize(NodeSet.size());
	copy(NodeSet.begin(),NodeSet.end(),nv.begin());


	//Edge creation process
	for (lnvit1 = nv.begin(); lnvit1 != nv.end(); lnvit1++){
        u=inf(*lnvit1); //*lnvit1 is a leda_node, son inf(*lnvit1) is a AnnotatedNode
        S1 = u.d_annotation.d_abstractSegment.GetImageSegment();
		S1A = S1.p();
		S1B = S1.q();
		for (lnvit2 = lnvit1+1; lnvit2 != nv.end(); lnvit2++){
            v=inf(*lnvit2);
            S2 = v.d_annotation.d_abstractSegment.GetImageSegment();
			S2A = S2.p();
			S2B = S2.q();


			//Trazo la perpendicular a S2 por cada uno de sus extremos
			//y obtengo los puntos de corte con S1
			//Hago lo mismo con S1 sobre S2
			S2AinS1 = S1.Intersection(S2.PerpLine(S2A));
			S2BinS1 = S1.Intersection(S2.PerpLine(S2B));
			S1AinS2 = S2.Intersection(S1.PerpLine(S1A));
			S1BinS2 = S2.Intersection(S1.PerpLine(S1B));

			//Estudio si alguna de las proyecciones de los dos extremos de S2 
			//estan entre los extremos de S1
			//o si alguna de las proyecciones de los dos extremos de S1 estan
			//entre los extremos de S2
			//Si no se solapan los segmentos ...
			if (!(S1.Contains(S2AinS1) ||
				  S1.Contains(S2BinS1) || 
				  S2.Contains(S1AinS2) ||
				  S2.Contains(S1BinS2) )) {

                dij = fabs(S1.EndPointDistance(S2));

                S12.Set(S1.MidPoint(),S2.MidPoint());

                alfai = S1.ShortAngle(S12);
                alfaj = S2.ShortAngle(S12);

                double affinityDistanceRelatedTerm  = affinityProximity(d0,dij);
                double affinityCollinearRelatedTerm = affinityCollinearity(theta0,alfai,alfaj);

                //AnnotatedArc::d_cost
                e.d_cost.d_affinity = affinityDistanceRelatedTerm * affinityCollinearRelatedTerm;

                if (e.d_cost.d_affinity >= 0.1){
                    lu = *lnvit1;
			        lv = *lnvit2;
                    le = new_edge(lu,lv);


                    //AnnotatedArc::d_annotation
                    e.d_annotation.d_type = SegmentArcAnnotation::ARC_TYPE_COL;
                    e.d_annotation.d_collinear.d_dij      = dij;
                    e.d_annotation.d_collinear.d_alfai    = alfai;
                    e.d_annotation.d_collinear.d_alfaj    = alfaj;

                    assign(le,e);
                }
            }
		}
	}
    return *this;
}

/**************************************************************************\
* Name      : setConvexArcs
* Member of : SegmentPUAmultigraph
* Purpose   : Set convex relations (arcs) in the SegmentPUAmultigraph
* Returns   : *this   
* Parameters: 
*   d0      : reference distance below which two points are thought to be similar
*             and beyond which two points are thought to be dissimilar
*   theta0  : scaling constant between PI/2 and PI/10
*   delta   : scaling constant between 1/2 and 1/4
* Notes     :
* Author    : GAC
* Date      : 02.05.00
* Modified  :
\**************************************************************************/
SegmentPUAmultigraph &SegmentPUAmultigraph::setConvexArcs(double d0, double theta0, double delta){

    leda_list<leda_node> NodeSet;

    vector<leda_node> nv;
    vector<leda_node>::iterator lnvit1,lnvit2;

    vector<double> DistVector;
	vector<double>::iterator Dit;

    Image::Segment S1,S2,S12,SA,SB;
    Point2D S1A,S1B,S2A,S2B;
    Point2D S2AinS1,S2BinS1,S1AinS2,S1BinS2;

   	leda_node lu,lv,lw;
    leda_edge le;

    SegmentAnnotatedNode u,v;
    SegmentAnnotatedArc  e;

    double dij,alfai,alfaj;

    bool areMutuallyConvex;
    double maxNoConvexityThreshold = 1.0;
    bool hasAdjNode; //Does it have adjacent nodes


    //Due to problems with the bad implementation of leda iterators,
    //a copy to STL vector is carried out
    NodeSet = all_nodes();
    nv.resize(NodeSet.size());
	copy(NodeSet.begin(),NodeSet.end(),nv.begin());


	//Edge creation process
	for (lnvit1 = nv.begin(); lnvit1 != nv.end(); lnvit1++){
        u=inf(*lnvit1); //*lnvit1 is a leda_node, so inf(*lnvit1) is an AnnotatedNode
        S1 = u.d_annotation.d_abstractSegment.GetImageSegment();
		S1A = S1.p();
		S1B = S1.q();
		for (lnvit2 = lnvit1+1; lnvit2 != nv.end(); lnvit2++){
            v=inf(*lnvit2);
            S2 = v.d_annotation.d_abstractSegment.GetImageSegment();
			S2A = S2.p();
			S2B = S2.q();

            //To add a convex relation (arc) there must be no other type
            //of relation such as parallelism, collinearity, etc.
            //hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_CONV);
            hasAdjNode = false;
            forall_adj_nodes(lw,*lnvit1){
                hasAdjNode = hasAdjNode || (lw == *lnvit2);
            }
            if (!hasAdjNode){

                areMutuallyConvex = false;
                    SA=Image::Segment(0,S1A,S1B);
                    SB=Image::Segment(0,S2A,S2B);
                    areMutuallyConvex = areMutuallyConvex || areConvex(SA,SB,maxNoConvexityThreshold);
                if (!areMutuallyConvex) {
                    SA=Image::Segment(0,S1A,S1B);
                    SB=Image::Segment(0,S2B,S2A);
                    areMutuallyConvex = areMutuallyConvex || areConvex(SA,SB,maxNoConvexityThreshold);
                }
                if (!areMutuallyConvex) {
                    SA=Image::Segment(0,S1B,S1A);
                    SB=Image::Segment(0,S2A,S2B);
                    areMutuallyConvex = areMutuallyConvex || areConvex(SA,SB,maxNoConvexityThreshold);
                }
                if (!areMutuallyConvex) {
                    SA=Image::Segment(0,S1B,S1A);
                    SB=Image::Segment(0,S2B,S2A);
                    areMutuallyConvex = areMutuallyConvex || areConvex(SA,SB,maxNoConvexityThreshold);
                }

			    //Si los dos segmentos son mutuamente convexos ...
			    if (areMutuallyConvex){
				    dij = S1.EndPointDistance(S2);

                    S12.Set(S1.MidPoint(),S2.MidPoint());

                    alfai = S1.ShortAngle(S12);
                    alfaj = S2.ShortAngle(S12);

                    double affinityDistanceRelatedTerm  = affinityProximity(d0,dij);
                    double affinityConvexRelatedTerm    = affinityCocircularity(theta0,delta,alfai,alfaj);

                    //AnnotatedArc::d_cost
                    e.d_cost.d_affinity = affinityDistanceRelatedTerm * affinityConvexRelatedTerm;

                    if (e.d_cost.d_affinity >= 0.1){
                        lu = *lnvit1;
			            lv = *lnvit2;
                        le = new_edge(lu,lv);


                        //AnnotatedArc::d_annotation
                        e.d_annotation.d_type = SegmentArcAnnotation::ARC_TYPE_CONV;
                        e.d_annotation.d_convex.d_dij      = dij;
                        e.d_annotation.d_convex.d_alfai    = alfai;
                        e.d_annotation.d_convex.d_alfaj    = alfaj;

                        assign(le,e);
                    }
                }
            }
		}
	}

//Components extraction process
    multimap<int,leda_node> mmapComponents; //Multimap of components. Each node (leda_node) has a int number
                                            //meaning the index of the component to which it belongs
    multimap<int,leda_node>::iterator mmapCit1; //Iterator to run over the mmapComponents
    pair<multimap<int,leda_node>::iterator,
         multimap<int,leda_node>::iterator> mmapCitPair;  //Pair of iterators. It will indicate the range in mmapComponent whose leda_nodes
                                                          //belong to a component in the graph (*this)
    leda_node_array<int> comp_num(*this); //leda_node_array containing nodes of *this graph
    int n; //Number of components of *this graph
    int i;

    //We hide all other arcs considering only convex arcs
    hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_COL);
    hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_PAR);
    hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_PROX);
    //Components extraction
    n = COMPONENTS(*this,comp_num); 
cout << "Numero de componentes: " << n << endl;
    restore_all_edges();

    //We build the mmapComponents multimap
    forall_nodes(lu,*this){
        mmapComponents.insert(pair<int const,leda_node>(comp_num[lu],lu));
    }
    //We select only components with more than two nodes (segments) because
    //a convex group must to have at least three or more segments
    for (i=0;i<n;i++){
        if (mmapComponents.count(i) <= 2) mmapComponents.erase(i);
    }
for (i=0;i<n;i++){
    cout << "componente: " << i << " tiene: " << mmapComponents.count(i) << endl;
}

    //Convex groups extraction

//    multimap<leda_node,Image::Segment> mmapNodeSegments;
//    multimap<leda_node,Image::Segment>::iterator mmapNSit1,mmapNSit2;
//    pair<multimap<leda_node,Image::Segment>::iterator,
//         multimap<leda_node,Image::Segment>::iterator> mmapNSitPair;


//    leda_node SGlu,SGlv;
    Image::SegmentVector SV; //Segment vector with the original segment set of *this graph plus the same set
                             //of segments in opposite directions
    UGRAPH<Image::Segment,double> SG; //Segment graph containing a node for each segment in SV

    //For each graph component with more than one node, i.e., for each
    //subgraph whose nodes are abstract segments and arcs are convex relations
    for (i=0;i<n;i++){
        if (mmapComponents.count(i)>2){
            mmapCitPair = mmapComponents.equal_range(i);

            //We make a directed parametrized graph
            //SV.clear();
            SG.clear();

            for (mmapCit1 = mmapCitPair.first;
                 mmapCit1 != mmapCitPair.second;
                 mmapCit1++) {
                //For each node of component i
                lu = (*mmapCit1).second;    //(*mmapCit1)             is a pair<int,leda_node>
                                            //(*mmapCit1).second      is a leda_node
                u  = inf(lu);               //inf((*mmapCit1).second) is a SegmentAnnotatedNode
cout << u.d_annotation.d_abstractSegment;
                
                //I get the d_abstractSegment of that node
                S1 = u.d_annotation.d_abstractSegment.GetImageSegment();
                //A second segment equal than S1 but in the opposite direction is created
		        S1A = S1.p();
		        S1B = S1.q();
                S2 = S1;
                S2.Set(S1B,S1A);

                //Two segments are added to the SV segment vector
                SV.push_back(S1);
                SV.push_back(S2);

                //A pair of nodes, one for each segment, is added to the SG graph
                lu = SG.new_node();
                SG.assign(lu,S1);
                lu = SG.new_node();
                SG.assign(lu,S2);

            }

	        //Edge creation process of the SG parametrized graph

            //Due to problems with the bad implementation of leda iterators,
            //a copy to STL vector is carried out
            NodeSet.clear(); //leda_list<leda_node> NodeSet --> declared on top of this function
            nv.clear();      //vector<leda_node> nv --> declared on top of this function
            NodeSet = SG.all_nodes();
            nv.resize(NodeSet.size());
	        copy(NodeSet.begin(),NodeSet.end(),nv.begin());

	        for (lnvit1 = nv.begin(); lnvit1 != nv.end(); lnvit1++){
                S1 = SG.inf(*lnvit1);
		        S1A = S1.p();
		        S1B = S1.q();

		        for (lnvit2 = lnvit1+1; lnvit2 != nv.end(); lnvit2++){
                    S2  = SG.inf(*lnvit2);
			        S2A = S2.p();
			        S2B = S2.q();

                    hasAdjNode = false; //Declared on top of this function (does it have adjacent nodes?)
                    forall_adj_nodes(lw,*lnvit1){
                        hasAdjNode = hasAdjNode || (lw == *lnvit2);
                    }
                    if (!hasAdjNode){

                        areMutuallyConvex = areConvex(S1,S2,maxNoConvexityThreshold);

			            //If both segments are mutually convex ...
			            if (areMutuallyConvex){
				            dij = S1.EndPointDistance(S2);

                            S12.Set(S1.MidPoint(),S2.MidPoint());

                            alfai = S1.ShortAngle(S12);
                            alfaj = S2.ShortAngle(S12);

                            //We compute the affinity based on Proximity and Cocircularity
                            double affinityDistanceRelatedTerm  = affinityProximity(d0,dij);
                            double affinityConvexRelatedTerm    = affinityCocircularity(theta0,delta,alfai,alfaj);
                            double affinity = affinityDistanceRelatedTerm * affinityConvexRelatedTerm;

                            // ... and the affinity is greater than a threshold
                            if (affinity >= 0.1){
                                lu = *lnvit1;
			                    lv = *lnvit2;
                                //Finally we add the arc with the affinity value
                                le = SG.new_edge(lu,lv);
                                SG.assign(le,affinity);
                            }

                        }
                    }
		        }
	        }

GraphWin gw(SG,650,500,"Hola");
//Node related
gw.set_node_label_font(roman_font,8);
gw.set_node_width(10);
gw.set_node_height(10);
gw.set_node_label_type(index_label);	
//Edge related
gw.set_edge_width(1);
gw.display();
gw.edit();
cout << endl;
SV.Show();

        //For each graph cycles are extracted. Cycles are considered as convex groups


        }
    }

    //Buscar Loops y verificar que realmente son Convex Loops

    return *this;
}



/**************************************************************************\
* Name      : areConvex
* Member of : SegmentPUAmultigraph
* Purpose   : Set convex relations (arcs) in the SegmentPUAmultigraph
* Returns   : 
*    true if S1 and S2 are convex   
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 21.04.00
* Modified  :
\**************************************************************************/
bool SegmentPUAmultigraph::areConvex(Image::Segment S1,Image::Segment S2,double maxNoConvexityThreshold){
    Point2D S1A,S1B,S2A,S2B;
    bool S1IsConvexWithS2,S2IsConvexWithS1;
    bool InTheSameLine,AreMutuallyConvex;

    S1A = S1.p();
	S1B = S1.q();
	S2A = S2.p();
	S2B = S2.q();

	//Los dos segmentos son mutuamente convexos cuando los extremos
	//de S2 estan a la derecha (semiplano negativo) de S1 y cuando los
	//extremos de S1 estan a la derecha (semiplano negativo) de S2...
	// y cuando no son el mismo segmento ...
	// ni son colinenales

	if (S1.IsInNegRightSide(S2A) && S1.IsInNegRightSide(S2B))
		S2IsConvexWithS1 = true;
	else if (S1.IsInNegRightSide(S2A) && S1.IsNearNegRightSide(S2B,maxNoConvexityThreshold))
		S2IsConvexWithS1 = true;
	else if (S1.IsNearNegRightSide(S2A,maxNoConvexityThreshold) && S1.IsInNegRightSide(S2B))
		S2IsConvexWithS1 = true;
	else
		S2IsConvexWithS1 = false;

	if (S2.IsInNegRightSide(S1A) && S2.IsInNegRightSide(S1B))
		S1IsConvexWithS2 = true;
	else if (S2.IsInNegRightSide(S1A) && S2.IsNearNegRightSide(S1B,maxNoConvexityThreshold))
		S1IsConvexWithS2 = true;
	else if (S2.IsNearNegRightSide(S1A,maxNoConvexityThreshold) && S2.IsInNegRightSide(S1B))
		S1IsConvexWithS2 = true;
	else
		S1IsConvexWithS2 = false;

	InTheSameLine = (fabs(S1.Pow(S2A))<1.0e-5) && (fabs(S1.Pow(S2B))<1.0e-5);

	AreMutuallyConvex = ( S2IsConvexWithS1				&&
						  S1IsConvexWithS2				&&
						  !InTheSameLine				
						);
    return AreMutuallyConvex;
}


/**************************************************************************\
* Name      : setProximalArcs
* Member of : SegmentPUAmultigraph
* Purpose   : Set proximal relations (arcs) in the SegmentPUAmultigraph
* Returns   : *this   
* Parameters: 
*   d0      : reference distance below which two points are thought to be similar
*             and beyond which two points are thought to be dissimilar
*   theta0  : scaling constant between PI/2 and PI/10
*   delta   : scaling constant between 1/2 and 1/4
* Notes     :
* Author    : GAC
* Date      : 02.05.00
* Modified  :
\**************************************************************************/
SegmentPUAmultigraph &SegmentPUAmultigraph::setProximalArcs(double d0, double theta0, double delta){

    leda_list<leda_node> NodeSet;

    vector<leda_node> nv;
    vector<leda_node>::iterator lnvit1,lnvit2;

    Image::Segment S1,S2,S12;
    Point2D S1A,S1B,S2A,S2B;
    Point2D S2AinS1,S2BinS1,S1AinS2,S1BinS2;

   	leda_node lu,lv,lw;
    leda_edge le;

    SegmentAnnotatedNode u,v;
    SegmentAnnotatedArc  e;

    double dij,alfai,alfaj;

    bool hasAdjNode;

    //Due to problems with the bad implementation of leda iterators,
    //a copy to STL vector is carried out
    NodeSet = all_nodes();
    nv.resize(NodeSet.size());
	copy(NodeSet.begin(),NodeSet.end(),nv.begin());

    //hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_CONV);

	//Edge creation process
	for (lnvit1 = nv.begin(); lnvit1 != nv.end(); lnvit1++){
        u=inf(*lnvit1); //*lnvit1 is a leda_node, son inf(*lnvit1) is a AnnotatedNode
        S1 = u.d_annotation.d_abstractSegment.GetImageSegment();
		S1A = S1.p();
		S1B = S1.q();
		for (lnvit2 = lnvit1+1; lnvit2 != nv.end(); lnvit2++){
            v=inf(*lnvit2);
            S2 = v.d_annotation.d_abstractSegment.GetImageSegment();
			S2A = S2.p();
			S2B = S2.q();

            //To add a proximity relation (arc) there must be no other type
            //of relation such as parallelism, collinearity, etc.
            hasAdjNode = false;
            forall_adj_nodes(lw,*lnvit1){
                hasAdjNode = hasAdjNode || (lw == *lnvit2);
            }
            if (!hasAdjNode){

                dij = fabs(S1.EndPointDistance(S2));

                double affinityDistanceRelatedTerm  = affinityProximity(d0,dij);

                //AnnotatedArc::d_cost
                e.d_cost.d_affinity = affinityDistanceRelatedTerm;

                if (e.d_cost.d_affinity >= 0.1){
                    lu = *lnvit1;
			        lv = *lnvit2;
                    le = new_edge(lu,lv);


                    //AnnotatedArc::d_annotation
                    e.d_annotation.d_type = SegmentArcAnnotation::ARC_TYPE_PROX;
                    e.d_annotation.d_collinear.d_dij      = dij;

                    assign(le,e);
                }
            }
		}
	}
    restore_all_edges();

    return *this;
}



/**************************************************************************\
* Name      : setProximalArcs
* Member of : SegmentPUAmultigraph
* Purpose   : Set proximity relations (arcs) in the SegmentPUAmultigraph
* Returns   : *this   
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 21.04.00
* Modified  :
\**************************************************************************/
/*
SegmentPUAmultigraph &SegmentPUAmultigraph::setProximalArcs(double maxDistance,double d0){

    vector<Image::Segment*> pSegmentSet;
	map<Image::Segment*,leda_node> MNode;

    Image::Segment S1,S2,S1aux,S2aux,S1S2,AuxS,SbetwnMidPoints;
    vector<Image::Segment*>::iterator svit1,svit2;
    Point2D S1A,S1B,S2A,S2B;
    Point2D S2MidPoint;
    Point2D S2AinS1,S2BinS1,S1AinS2,S1BinS2;

    vector<double> DistVector;
	vector<double>::iterator Dit;

   	leda_node lu,lv,lw;
    leda_edge le;

    SegmentAnnotatedNode u,v;
    SegmentAnnotatedArc  e;

    double Distance;

    //Extraction of abstract segments
    forall_nodes(lu,*this){
        u=inf(lu);
        pSegmentSet.push_back(u.d_annotation.d_abstractSegment);
		MNode[u.d_annotation.d_abstractSegment]=lu;
    }

	//Edge creation process
	for (svit1 = pSegmentSet.begin(); svit1 != pSegmentSet.end(); svit1++){
		S1  = (**svit1);
		S1A = S1.p();
		S1B = S1.q();
		for (svit2 = svit1+1; svit2 != pSegmentSet.end(); svit2++){
			S2  = (**svit2);
			S2A = S2.p();
			S2B = S2.q();

			DistVector.clear();
			DistVector.push_back(S1A.Distance(S2A));
			DistVector.push_back(S1A.Distance(S2B));
			DistVector.push_back(S1B.Distance(S2A));
			DistVector.push_back(S1B.Distance(S2B));

			Dit = min_element(DistVector.begin(), DistVector.end()) ;
			Distance = *Dit;
			if (Distance <= maxDistance){
				//SbetwnMidPoints.Set(S1.MidPoint(),S2.MidPoint());
				//Distance = SbetwnMidPoints.Mod();

				double AffProximity  = ((Distance*Distance)/(d0*d0));
				if (AffProximity<DoubleEpsilon)  AffProximity  = 0.0;
				AffProximity = exp(-AffProximity);

                lu = MNode[*svit1];
                lv = MNode[*svit2];
                
                //To add a proximity relation (arc) there must be no other type
                //of relation such as parallelism, collinearity, convexity, etc.
                hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_CONV);
                bool luHasAdjNode = false;
                forall_adj_nodes(lw,lu){
                    luHasAdjNode = luHasAdjNode || (lw == lv);
                }

                if (!luHasAdjNode){
                    le = new_edge(lu,lv);

                    //AnnotatedArc::d_cost
                    e.d_cost.d_affinity = AffProximity;

                    //AnnotatedArc::d_annotation
                    e.d_annotation.d_type = SegmentArcAnnotation::ARC_TYPE_PROX;
                    e.d_annotation.d_proximal.d_distance = Distance;

                    assign(le,e);
                }
                restore_all_edges();
            }
        }
    }

    return *this;
}
*/

/********SegmentMultiAHgraphArcCost****************************************\
		
  	  
		               class SegmentMultiAHgraphArcCost


\**************************************************************************/
/**************************************************************************\
* Name      : SegmentMultiAHgraphArcCost
* Member of : SegmentMultiAHgraphArcCost
* Purpose   : constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentMultiAHgraphArcCost::SegmentMultiAHgraphArcCost()
{

}

/**************************************************************************\
* Name      : ~SegmentMultiAHgraphArcCost
* Member of : SegmentMultiAHgraphArcCost
* Purpose   : destructuctor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentMultiAHgraphArcCost::~SegmentMultiAHgraphArcCost()
{

}

/********SegmentMultiAHgraphArcAnnotation**********************************\
		
  	  
		               class SegmentMultiAHgraphArcAnnotation


\**************************************************************************/
/**************************************************************************\
* Name      : SegmentMultiAHgraphArcAnnotation
* Member of : SegmentMultiAHgraphArcAnnotation
* Purpose   : constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentMultiAHgraphArcAnnotation::SegmentMultiAHgraphArcAnnotation()
{

}

/**************************************************************************\
* Name      : ~SegmentMultiAHgraphArcAnnotation
* Member of : SegmentMultiAHgraphArcAnnotation
* Purpose   : destructuctor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentMultiAHgraphArcAnnotation::~SegmentMultiAHgraphArcAnnotation()
{

}


/********SegmentMultiAHgraphAnnotatedArc***********************************\
		
  	  
		               class SegmentMultiAHgraphAnnotatedArc


\**************************************************************************/
/**************************************************************************\
* Name      : SegmentMultiAHgraphAnnotatedArc
* Member of : SegmentMultiAHgraphAnnotatedArc
* Purpose   : constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentMultiAHgraphAnnotatedArc::SegmentMultiAHgraphAnnotatedArc()
{

}

/**************************************************************************\
* Name      : ~SegmentMultiAHgraphAnnotatedArc
* Member of : SegmentMultiAHgraphAnnotatedArc
* Purpose   : destructuctor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentMultiAHgraphAnnotatedArc::~SegmentMultiAHgraphAnnotatedArc()
{

}


/********SegmentMultiAHgraph***********************************************\
		
  	  
		               class SegmentMultiAHgraph


\**************************************************************************/
/**************************************************************************\
* Name      : SegmentMultiAHgraph
* Member of : SegmentMultiAHgraph
* Purpose   : constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentMultiAHgraph::SegmentMultiAHgraph()
{

}

/**************************************************************************\
* Name      : ~SegmentMultiAHgraph
* Member of : SegmentMultiAHgraph
* Purpose   : destructuctor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 16.04.00
* Modified  :
\**************************************************************************/
SegmentMultiAHgraph::~SegmentMultiAHgraph()
{

}

/**************************************************************************\
* Name      : menuExpandAll_SegmentPUAmultigraph
* Member of : 
* Purpose   : Implements gw_action for showing SegmentAnnotatedNode information
* Returns   :    
* Parameters: 
*    gw         - GraphWin object
*    leda_point - point where mouse is clicked.
* Notes     : SegmentMultiAHgraph's free function
* Author    : GAC
* Date      : 17.04.00
* Modified  :
\**************************************************************************/
void menuExpandAll_SegmentPUAmultigraph(GraphWin& gw, const leda_point&)
{ 
	leda_node lu;
    SegmentMultiAHgraphAnnotatedNode *u;

	lu  = gw.get_edit_node();
	u = (SegmentMultiAHgraphAnnotatedNode*)lu->data(0);
    u->d_value.restore_all_edges();
    u->d_value.edit();
}

/**************************************************************************\
* Name      : menuExpandParallelism_SegmentPUAmultigraph
* Member of : 
* Purpose   : Implements gw_action for showing SegmentAnnotatedNode information
* Returns   :    
* Parameters: 
*    gw         - GraphWin object
*    leda_point - point where mouse is clicked.
* Notes     : SegmentMultiAHgraph's free function
* Author    : GAC
* Date      : 17.04.00
* Modified  :
\**************************************************************************/
void menuExpandParallelism_SegmentPUAmultigraph(GraphWin& gw, const leda_point&)
{ 
	leda_node lu;
    SegmentMultiAHgraphAnnotatedNode *u;

	lu  = gw.get_edit_node();
	u = (SegmentMultiAHgraphAnnotatedNode*)lu->data(0);
    u->d_value.restore_all_edges();
    //Hago esto porque a mi no me funciona el G.restore_edge(edge e)
    //en cambio, si funciona G.restore_all_edges()
    u->d_value.hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_COL);
    u->d_value.hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_PROX);
    u->d_value.hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_CONV);

    u->d_value.edit();
}

/**************************************************************************\
* Name      : menuExpandCollinearity_SegmentPUAmultigraph
* Member of : 
* Purpose   : Implements gw_action for showing SegmentAnnotatedNode information
* Returns   :    
* Parameters: 
*    gw         - GraphWin object
*    leda_point - point where mouse is clicked.
* Notes     : SegmentMultiAHgraph's free function
* Author    : GAC
* Date      : 17.04.00
* Modified  :
\**************************************************************************/
void menuExpandCollinearity_SegmentPUAmultigraph(GraphWin& gw, const leda_point&)
{ 
	leda_node lu;
    SegmentMultiAHgraphAnnotatedNode *u;

	lu  = gw.get_edit_node();
	u = (SegmentMultiAHgraphAnnotatedNode*)lu->data(0);
    u->d_value.restore_all_edges();
    //Hago esto porque a mi no me funciona el G.restore_edge(edge e)
    //en cambio, si funciona G.restore_all_edges()
    u->d_value.hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_PAR);
    u->d_value.hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_PROX);
    u->d_value.hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_CONV);

    u->d_value.edit();
}

/**************************************************************************\
* Name      : menuExpandConvexity_SegmentPUAmultigraph
* Member of : 
* Purpose   : Implements gw_action for showing SegmentAnnotatedNode information
* Returns   :    
* Parameters: 
*    gw         - GraphWin object
*    leda_point - point where mouse is clicked.
* Notes     : SegmentMultiAHgraph's free function
* Author    : GAC
* Date      : 17.04.00
* Modified  :
\**************************************************************************/
void menuExpandConvexity_SegmentPUAmultigraph(GraphWin& gw, const leda_point&)
{ 
	leda_node lu;
    SegmentMultiAHgraphAnnotatedNode *u;

	lu  = gw.get_edit_node();
	u = (SegmentMultiAHgraphAnnotatedNode*)lu->data(0);
    u->d_value.restore_all_edges();
    //Hago esto porque a mi no me funciona el G.restore_edge(edge e)
    //en cambio, si funciona G.restore_all_edges()
    u->d_value.hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_PAR);
    u->d_value.hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_PROX);
    u->d_value.hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_COL);

    u->d_value.edit();
}

/**************************************************************************\
* Name      : menuExpandProximity_SegmentPUAmultigraph
* Member of : 
* Purpose   : Implements gw_action for showing SegmentAnnotatedNode information
* Returns   :    
* Parameters: 
*    gw         - GraphWin object
*    leda_point - point where mouse is clicked.
* Notes     : SegmentMultiAHgraph's free function
* Author    : GAC
* Date      : 17.04.00
* Modified  :
\**************************************************************************/
void menuExpandProximity_SegmentPUAmultigraph(GraphWin& gw, const leda_point&)
{ 
	leda_node lu;
    SegmentMultiAHgraphAnnotatedNode *u;

	lu  = gw.get_edit_node();
	u = (SegmentMultiAHgraphAnnotatedNode*)lu->data(0);
    u->d_value.restore_all_edges();
    //Hago esto porque a mi no me funciona el G.restore_edge(edge e)
    //en cambio, si funciona G.restore_all_edges()
    u->d_value.hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_PAR);
    u->d_value.hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_CONV);
    u->d_value.hideEdgesOfType(SegmentArcAnnotation::ARC_TYPE_COL);

    u->d_value.edit();
}

/**************************************************************************\
* Name      : showSegmentAnnotatedNode
* Member of : 
* Purpose   : Implements gw_action for showing SegmentAnnotatedNode information
* Returns   :    
* Parameters: 
*    gw         - GraphWin object
*    leda_point - point where mouse is clicked.
* Notes     : SegmentPUAmultigraph's free function
* Author    : GAC
* Date      : 17.04.00
* Modified  :
\**************************************************************************/
void showSegmentMultiAHgraphParameters(GraphWin& gw, const leda_point&)
{ 
	leda_node lu;
    SegmentPUAmultigraph *u;

	lu  = gw.get_edit_node();
    gw.deselect_all_nodes();
    gw.select(lu);
	u = (SegmentPUAmultigraph*)lu->data(0);
	printf("SegmentPUAmultigraph\n====================\n");
	//u->show();
	printf("\n");
}

/**************************************************************************\
* Name      : edit
* Member of : SegmentMultiAHgraph
* Purpose   : Displays the graph corresponding to the hierarchy
* Returns   :    
* Parameters:
* Notes     :
* Author    : GAC
* Date      : 19.04.00
* Modified  :
\**************************************************************************/
SegmentMultiAHgraph::edit()
{
	int xwin,ywin;

	xwin = 650;
	ywin = 500;

    GraphWin gw(*this,xwin,ywin,"Department of System Engineering and Automation. University of Malaga");
	gw.set_node_shape(rectangle_node);
	gw.set_node_label_font(roman_font,10);
	gw.set_node_width(46);
    gw.set_node_height(16);
	gw.set_edge_width(1);
    gw.set_zoom_objects(true);
	gw.set_animation_steps(0);
	gw.message(leda_string("Segment MultiAHgraph"));
	gw.set_node_label_type(index_label);

    //ACTIONS
    //gw.set_action(A_LEFT | A_NODE | A_SHIFT, showSegmentAnnotatedNode);
    gw.set_action(A_LEFT | A_NODE, showSegmentMultiAHgraphParameters);

    // MENUS
    gw.add_node_menu("expand all",menuExpandAll_SegmentPUAmultigraph);
    gw.add_node_menu("expand parallelism" ,menuExpandParallelism_SegmentPUAmultigraph);
    gw.add_node_menu("expand collinearity",menuExpandCollinearity_SegmentPUAmultigraph);
    gw.add_node_menu("expand convexity"   ,menuExpandConvexity_SegmentPUAmultigraph);
    gw.add_node_menu("expand proximity"   ,menuExpandProximity_SegmentPUAmultigraph);
//  gw.set_node_index_format("level: %i");

    gw.display();
	gw.place_into_win();
	gw.edit();
}

/**************************************************************************\
* Name      : setL0
* Member of : SegmentMultiAHgraph
* Purpose   : Set level 0 in the MultiAHgraph
* Returns   :    
* Parameters: 
*    InitialSegmentSet - It's a segment vector originated in a Image class
* Notes     :
* Author    : GAC
* Date      : 17.04.00
* Modified  :
\**************************************************************************/

SegmentMultiAHgraph &SegmentMultiAHgraph::setL0(Image::SegmentVector &initialSegmentSet){
    multimap<unsigned int, SegmentMultiAHgraphNodeAnnotation::ParallelParametersStruct>::iterator   parIt1,parIt2;
    multimap<unsigned int, SegmentMultiAHgraphNodeAnnotation::CollinearParametersStruct>::iterator  colIt1;
    multimap<unsigned int, SegmentMultiAHgraphNodeAnnotation::ConvexParametersStruct>::iterator     convIt1;
    multimap<unsigned int, SegmentMultiAHgraphNodeAnnotation::ProximalParametersStruct>::iterator   proxIt1;

    SegmentMultiAHgraphNodeAnnotation::ParallelParametersStruct  parallelParameters;
    SegmentMultiAHgraphNodeAnnotation::CollinearParametersStruct collinearParameters;
    SegmentMultiAHgraphNodeAnnotation::ConvexParametersStruct    convexParameters;
    SegmentMultiAHgraphNodeAnnotation::ProximalParametersStruct  proximityParameters;

    pair<multimap<unsigned int, SegmentMultiAHgraphNodeAnnotation::ParallelParametersStruct>::iterator,
         multimap<unsigned int, SegmentMultiAHgraphNodeAnnotation::ParallelParametersStruct>::iterator>  parRangeItPair;
    pair<multimap<unsigned int, SegmentMultiAHgraphNodeAnnotation::CollinearParametersStruct>::iterator,
         multimap<unsigned int, SegmentMultiAHgraphNodeAnnotation::CollinearParametersStruct>::iterator> colRangeItPair;
    pair<multimap<unsigned int, SegmentMultiAHgraphNodeAnnotation::ConvexParametersStruct>::iterator,
         multimap<unsigned int, SegmentMultiAHgraphNodeAnnotation::ConvexParametersStruct>::iterator>    convRangeItPair;
    pair<multimap<unsigned int, SegmentMultiAHgraphNodeAnnotation::ProximalParametersStruct>::iterator,
         multimap<unsigned int, SegmentMultiAHgraphNodeAnnotation::ProximalParametersStruct>::iterator>  proxRangeItPair;

    unsigned int level;


//Initializing SegmentMultiAHgraph
//================================
    Image::SegmentVector::iterator isvit1;
    Image::Segment S1;

    segmentSet.clear();
    segmentSetCGAL.clear();
//    clear();

	//store initialSegmentSet parameter in the private variable
	segmentSet.resize(initialSegmentSet.size());
	copy(initialSegmentSet.begin(),initialSegmentSet.end(),segmentSet.begin());

   	for (isvit1 = initialSegmentSet.begin(); isvit1 != initialSegmentSet.end(); isvit1++){
		S1 = (*isvit1);
        segmentSetCGAL.push_back(CGALSegment(
                                    CGALPoint(S1.p().x(),S1.p().y()),
                                    CGALPoint(S1.q().x(),S1.q().y()),
                                    S1.Label,leda_blue));
    }

cout << segmentSetCGAL;
//==================================

    level = 0;

    //Mientras haya parametros del nivel level
    while ((d_parallelParameters.count(level)  > 0) &&
           (d_collinearParameters.count(level) > 0) &&
           (d_convexParameters.count(level)    > 0) &&
           (d_proximalParameters.count(level)  > 0) 
          ){
        
        parRangeItPair = d_parallelParameters.equal_range(level);

   	    for (parIt1 = parRangeItPair.first; parIt1 != parRangeItPair.second; parIt1++){
		    parallelParameters = (*parIt1).second;
            cout << "(" << level << ")" << "parallelParameters.d0     :" << parallelParameters.d0     << endl;
            cout << "(" << level << ")" << "parallelParameters.delta  :" << parallelParameters.delta  << endl;
            cout << "(" << level << ")" << "parallelParameters.theta0 :" << parallelParameters.theta0 << endl;
            cout << "------" << endl;

            colRangeItPair = d_collinearParameters.equal_range(level);

   	        for (colIt1 = colRangeItPair.first; colIt1 != colRangeItPair.second; colIt1++){
		        collinearParameters = (*colIt1).second;
                cout << "  (" << level << ")" << "collinearParameters.d0     :" << collinearParameters.d0     << endl;
                cout << "  (" << level << ")" << "collinearParameters.delta  :" << collinearParameters.delta  << endl;
                cout << "  (" << level << ")" << "collinearParameters.theta0 :" << collinearParameters.theta0 << endl;
                cout << "------" << endl;

                convRangeItPair = d_convexParameters.equal_range(level);

   	            for (convIt1 = convRangeItPair.first; convIt1 != convRangeItPair.second; convIt1++){
		            convexParameters = (*convIt1).second;
                    cout << "    (" << level << ")" << "convexParameters.d0     :" << convexParameters.d0     << endl;
                    cout << "    (" << level << ")" << "convexParameters.delta  :" << convexParameters.delta  << endl;
                    cout << "    (" << level << ")" << "convexParameters.theta0 :" << convexParameters.theta0 << endl;
                    cout << "------" << endl;

                    proxRangeItPair = d_proximalParameters.equal_range(level);

   	                for (proxIt1 = proxRangeItPair.first; proxIt1 != proxRangeItPair.second; proxIt1++){
		                proximityParameters = (*proxIt1).second;
                        cout << "      (" << level << ")" << "proximityParameters.d0     :" << proximityParameters.d0     << endl;
                        cout << "      (" << level << ")" << "proximityParameters.delta  :" << proximityParameters.delta  << endl;
                        cout << "      (" << level << ")" << "proximityParameters.theta0 :" << proximityParameters.theta0 << endl;
                        cout << "------" << endl;

                        addL0(parallelParameters,collinearParameters,convexParameters,proximityParameters); //Crear Nodo (Crear SegmentPUAmultigraph)

                    }
                }
            }
        }
        ++level;
    }


    return *this;
}


SegmentMultiAHgraph &SegmentMultiAHgraph::addL0(SegmentMultiAHgraphNodeAnnotation::ParallelParametersStruct  parallelParameters,
                                                SegmentMultiAHgraphNodeAnnotation::CollinearParametersStruct collinearParameters,
                                                SegmentMultiAHgraphNodeAnnotation::ConvexParametersStruct    convexParameters,
                                                SegmentMultiAHgraphNodeAnnotation::ProximalParametersStruct  proximityParameters
                                               ){
    SegmentAnnotatedNode u,v;
    SegmentPUAmultigraph L0; //Level 0 -> plain undirected multigraph
    SegmentMultiAHgraphAnnotatedNode n;

   	leda_node lu;

    CGALSegmentVector::iterator svit;
    unsigned int counter;


    //Node creation process (this process will be done by clustering process in the next abstraction phases)
    counter = 1;
	for (svit = segmentSetCGAL.begin(); svit != segmentSetCGAL.end(); svit++){
        u.d_value.clear();
        u.d_value.push_back(&(*svit)); 
        u.d_annotation.d_label = counter;
        u.d_annotation.d_abstractSegment = *svit;
//        lu = L0.new_node(); //u is a SegmentAnnotatedNode / AnnotatedNode<NodeValueType,NodeAnnotationType>
//        L0.assign(lu,u);
        lu = n.d_value.new_node(); //u is a SegmentAnnotatedNode / AnnotatedNode<NodeValueType,NodeAnnotationType>
        n.d_value.assign(lu,u);
        ++counter;
	}

//    L0.setParallelArcs (parallelParameters.d0,  parallelParameters.theta0,  parallelParameters.delta);
//    L0.setCollinearArcs(collinearParameters.d0, collinearParameters.theta0, collinearParameters.delta);
//    L0.setConvexArcs   (convexParameters.d0,    convexParameters.theta0,    convexParameters.delta);
//    L0.setProximalArcs (proximityParameters.d0, proximityParameters.theta0, proximityParameters.delta);

    n.d_value.setParallelArcs (parallelParameters.d0,  parallelParameters.theta0,  parallelParameters.delta);
    n.d_value.setCollinearArcs(collinearParameters.d0, collinearParameters.theta0, collinearParameters.delta);
    n.d_value.setConvexArcs   (convexParameters.d0,    convexParameters.theta0,    convexParameters.delta);
    n.d_value.setProximalArcs (proximityParameters.d0, proximityParameters.theta0, proximityParameters.delta);


  //Adding ground node, i.e., ground hierarchical level
    lu = new_node();
//    assign(n.d_value,L0);
    assign(lu,n);

    return *this;
}

/**************************************************************************\
* Name      : generateAbstraction
* Member of : SegmentMultiAHgraph
* Purpose   : It generates the following level of abstraction
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 21.04.00
* Modified  :
\**************************************************************************/
SegmentMultiAHgraph &SegmentMultiAHgraph::generateAbstraction(){
   	leda_node lu;
    SegmentPUAmultigraph *plevelG; //Level 0 -> plain undirected multigraph
    SegmentPUAmultigraph levelG;

    unsigned int parametersLevel;
    unsigned int previousNumberOfNodes;

    parametersLevel = 1;

    do {
        previousNumberOfNodes = number_of_nodes();
        forall_nodes(lu,*this){
            if (adj_nodes(lu).size()==0){
                cout << "new abstraction " << endl;

            }
        }
        ++parametersLevel;
        cout << "New level-nodes generated: " << number_of_nodes()-previousNumberOfNodes << endl;
    } while (number_of_nodes()>previousNumberOfNodes);

//        nodeCreation();
//        edgeCreation();

//   		plevelG = (SegmentPUAmultigraph*)lu->data(0);

        //type u = inf(lu); //In this way, we get a new node type u with a copy of 
                            //data in lu
        //type *u = (type*)lu->data(0); //In this way, we get a reference to the data
        //in lu
/*
        //maxDistance = 30.0;
        //minDistance = 0.0;
        //maxAngle    = 5.0*ONE_GRADE_IN_RAD;
        plevelG->setParallelArcs(30.0,0.0,5.0*ONE_GRADE_IN_RAD);

        //maxDistance         = 10.0;
        //maxAngle            = 5.0*ONE_GRADE_IN_RAD
        //maxParallelDistance = 5.0;
        plevelG->setCollinearArcs(10.0,5.0*ONE_GRADE_IN_RAD,5.0);

        //maxDistance             = 10.0;
        //maxNoConvexityThreshold = 2.0;
        plevelG->setConvexArcs(10.0,1.0);

        //maxDistance         = 10.0;
        //d0p                 = 2.0;
        plevelG->setProximalArcs(10.0,2.0);
*/
 
    return *this;
}

/**************************************************************************\
* Name      : nodeCreation
* Member of : SegmentMultiAHgraph
* Purpose   : It generates nodes of the new node-level of abstraction
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 21.04.00
* Modified  :
\**************************************************************************/
SegmentPUAmultigraph SegmentMultiAHgraph::nodeCreation(SegmentPUAmultigraph &baseG){

    SegmentPUAmultigraph G;
    return G;
}


