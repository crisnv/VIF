#include "cv.h"
#include "highgui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>


#include <iostream>
#include <cstdio>


#include "wx/wx.h"
#include <vector>

#include "fotografia.h"

using namespace std;
using namespace cv;



//haarcascade_fullbody.xml
//haarcascade_lowerbody.xml
//haarcascade_mcs_upperbody.xml
//haarcascade_upperbody.xml

#define NUM_CASCADES	1//6

String cascadeName[NUM_CASCADES] ={
"detectores/haarcascade_frontalface_alt2.xml",
/*
"detectores/haarcascade_frontalface_alt.xml",
"detectores/haarcascade_frontalface_default.xml",
"detectores/haarcascade_frontalface_alt_tree.xml",
"detectores/lbpcascade_frontalface.xml",
"detectores/haarcascade_profileface.xml"
*/
};

#define NUM_NESTEDCASCADES	10//6

String nestedCascadeName[NUM_NESTEDCASCADES] ={
"detectores/haarcascade_eye_tree_eyeglasses.xml",
"detectores/haarcascade_eye.xml",
"detectores/haarcascade_lefteye_2splits.xml",
"detectores/haarcascade_righteye_2splits.xml",
"detectores/haarcascade_mcs_righteye.xml",
"detectores/haarcascade_mcs_lefteye.xml",
"detectores/haarcascade_mcs_eyepair_big.xml",
"detectores/haarcascade_mcs_eyepair_small.xml",
"detectores/haarcascade_mcs_mouth.xml",
"detectores/haarcascade_mcs_nose.xml"
};

CascadeClassifier	cascade[NUM_CASCADES], 
					nestedCascade[NUM_NESTEDCASCADES];


static CvScalar colors[] = 
{
    {{0,0,255}},
    {{0,128,255}},
    {{0,255,255}},
    {{0,255,0}},
    {{255,128,0}},
    {{255,255,0}},
    {{255,0,0}},
    {{255,0,255}}
};



void detectFacesFromFile(char *filename, vector<retang> &v, wxImage *wximg){

	if(wximg == NULL)
		return ;

	int iw =wximg->GetWidth();
	int ih =wximg->GetHeight();
		
	unsigned char *data = wximg->GetData();
	IplImage *cvImg = cvCreateImage(cvSize(iw,ih), IPL_DEPTH_8U , 3);
	for(int y=0; y<ih; y++){
		for(int x=0; x<iw; x++){

			cvImg->imageData[ x*3 +y*cvImg->widthStep] = wximg->GetRed(x,y );
			cvImg->imageData[ x*3 +y*cvImg->widthStep +1] = wximg->GetGreen( x,y );
			cvImg->imageData[ x*3 +y*cvImg->widthStep +2] = wximg->GetBlue( x,y );
				//data[x+y*iw]; 

		}
	}
	/*
	cvShowImage("teste", cvImg);
	cvWaitKey(0);
	*/

	int i=0;
	int approved = Fotografia::e_brandNew; 
	int nameOrigin = Fotografia::e_nameOriginUnknown;
    double t = 0.0;
	double scale = 1.0;
	retang r2;

	Mat smallImgROI;
	vector<Rect> faces;
	vector<Rect> nestedObjects;

	/*
	if(filename ==NULL){
		return ;
	}
	IplImage *cvImg =cvLoadImage( filename, CV_LOAD_IMAGE_GRAYSCALE );//1 );
	if( cvImg == NULL ){
		return ;
	}
	*/

	double scale0 = 1.0;
	/*
	while( (cvImg->width>=1600) 
		&& (cvImg->height>=1200)){
	*/
	while( (cvImg->width>=1000) 
		&& (cvImg->height>=800))
	{
	
			scale0 *=2.0;
			IplImage *iplimg2 = cvCreateImage( cvSize((int)((cvImg->width*50)/100) , (int)((cvImg->height*50)/100) ),
			cvImg->depth, cvImg->nChannels);

		cvResize(cvImg,iplimg2, CV_INTER_CUBIC);
		cvReleaseImage(&cvImg);
		cvImg = iplimg2;
	}
	

	cv::Mat img =cvImg;		
	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );
	int fn=0;
    cvtColor( img, gray, CV_BGR2GRAY );
    resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    equalizeHist( smallImg, smallImg );

	for(int c=0; c<NUM_CASCADES;c++){
	    
		t = (double)cvGetTickCount();
		cascade[c].detectMultiScale( smallImg, faces,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			|CV_HAAR_SCALE_IMAGE
			,
			Size(30, 30) );
		t = (double)cvGetTickCount() - t;
		printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );
		for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
		{
    		approved = 0;
			nestedObjects.clear();
			for(int nc=0; nc<NUM_NESTEDCASCADES && (!approved) ;nc++){
			
				if( nestedCascade[nc].empty() )
					continue;
				smallImgROI = smallImg(*r);
				
				nestedCascade[nc].detectMultiScale( smallImgROI, nestedObjects,
					1.1, 2, 0
					//|CV_HAAR_FIND_BIGGEST_OBJECT
					//|CV_HAAR_DO_ROUGH_SEARCH
					//|CV_HAAR_DO_CANNY_PRUNING
					|CV_HAAR_SCALE_IMAGE
					,Size(4, 4)
//					Size(30, 30)
					);

				if(nestedObjects.size()>0)
				{
					approved=1;
					break;
				}
			}
			if(approved){
				r2.x = scale0* r->x*scale;
				r2.y = scale0* r->y*scale;
				r2.w = scale0* r->width*scale;
				r2.h = scale0* r->height*scale;
				r2.approved = false;
				r2.nome[0]='\0';
				//se a face for unica
				for( fn=0; fn<v.size(); fn++){
					if(r2.x == v[fn].x 
					&& r2.y == v[fn].y 
					&& r2.w == v[fn].w 
					&& r2.h == v[fn].h )
						break;
				}
				if(fn>=v.size())
					v.push_back(r2);
			}
		}  
		
		
	}
	
	
	cvReleaseImage( &cvImg);
}

int Fotografia::LoadDetectionCascades(void)
{
	for(int c=0; c<NUM_CASCADES; c++){
		if( !cascade[c].load( cascadeName[c] ) )
		{
			cerr << "ERROR: Could not load classifier cascade" << endl;
			return -1;
		}
	}
	for(int nc=0; nc<NUM_NESTEDCASCADES; nc++){
		if( !nestedCascade[nc].load( nestedCascadeName[nc] ) ){
                cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
		}
	}
	
	return 0;
}
void Fotografia::DetectFaces( wxImage *wximg){
	
	char filename[128];
	sprintf_s(filename,128,"%s\\%s",m_dirname, m_imgname);
	detectFacesFromFile(filename, m_bbfaces, wximg);
	
#ifdef _DEBUG
	wxLogMessage("Encontrou %d bb", m_bbfaces.size());
#endif
	

}
