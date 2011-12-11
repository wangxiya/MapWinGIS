//********************************************************************************************************
//File name: Extents.cpp
//Description:  Implementation of CExtents.
//********************************************************************************************************
//The contents of this file are subject to the Mozilla Public License Version 1.1 (the "License"); 
//you may not use this file except in compliance with the License. You may obtain a copy of the License at 
//http://www.mozilla.org/MPL/ 
//Software distributed under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF 
//ANY KIND, either express or implied. See the License for the specificlanguage governing rights and 
//limitations under the License. 
//
//The Original Code is MapWindow Open Source. 
//
//The Initial Developer of this version of the Original Code is Daniel P. Ames using portions created by 
//Utah State University and the Idaho National Engineering and Environmental Lab that were released as 
//public domain in March 2004.  
//
//Contributor(s): (Open source contributors should list themselves and their modifications here). 
//3-28-2005 dpa - Identical to public domain version.
//********************************************************************************************************

#include "stdafx.h"
#include "Extents.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CExtents
STDMETHODIMP CExtents::SetBounds(double xMin, double yMin, double zMin, double xMax, double yMax, double zMax)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	xmin = xMin;
	xmax = xMax;
	ymin = yMin;
	ymax = yMax;
	zmin = zMin;
	zmax = zMax;

	double tmp;
	if( xmin > xmax )
	{	tmp = xmax;
		xmax = xmin;
		xmin = tmp;
	}
	if( ymin > ymax )
	{	tmp = ymax;
		ymax = ymin;
		ymin = tmp;
	}
	if( zmin > zmax )
	{	tmp = zmax;
		zmax = zmin;
		zmin = tmp;
	}

	return S_OK;
}

STDMETHODIMP CExtents::GetBounds(double * xMin, double * yMin, double * zMin, double * xMax, double * yMax, double * zMax)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*xMin = xmin;
	*xMax = xmax;
	*yMin = ymin;
	*yMax = ymax;
	*zMin = zmin;
	*zMax = zmax;

	return S_OK;
}


STDMETHODIMP CExtents::get_xMin(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = xmin;
	return S_OK;
}

STDMETHODIMP CExtents::get_xMax(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = xmax;
	return S_OK;
}

STDMETHODIMP CExtents::get_yMin(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = ymin;
	return S_OK;
}

STDMETHODIMP CExtents::get_yMax(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = ymax;
	return S_OK;
}

STDMETHODIMP CExtents::get_zMin(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = zmin;
	return S_OK;
}

STDMETHODIMP CExtents::get_zMax(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = zmax;
	return S_OK;
}

STDMETHODIMP CExtents::get_mMin(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = mmin;

	return S_OK;
}

STDMETHODIMP CExtents::get_mMax(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = mmax;

	return S_OK;
}

STDMETHODIMP CExtents::GetMeasureBounds(double *mMin, double *mMax)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*mMin = mmin;
	*mMax = mmax;

	return S_OK;
}

STDMETHODIMP CExtents::SetMeasureBounds(double mMin, double mMax)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mmin = mMin;
	mmax = mMax;

	double tmp;
	if( mmin > mmax )
	{	tmp = mmax;
		mmax = mmin;
		mmin = tmp;
	}

	return S_OK;
}

//*********************************************************************
//*	 Extents2Shape()				              
//*********************************************************************
// Creates polygon shape which is equivalent to the input extents
// return shape pointer on success, or NULL otherwise
 IShape* CExtents::ToShape()
{
	double xMin, xMax, yMin, yMax, zMin, zMax;
	this->GetBounds(&xMin,&yMin,&zMin,&xMax,&yMax,&zMax);
	
	IShape* shp = NULL;
	long PartIndex = 0;
	VARIANT_BOOL vbretval;
	
	CoCreateInstance(CLSID_Shape,NULL,CLSCTX_INPROC_SERVER,IID_IShape,(void**)&shp);
	shp->put_ShapeType(SHP_POLYGON);
	shp->InsertPart(0, &PartIndex, &vbretval);
	
	IPoint* pnt = NULL;
	
	for (long i = 0; i<=4; i++)
	{
		m_factory.pointFactory->CreateInstance(NULL, IID_IPoint, (void**)&pnt);
		//CoCreateInstance(CLSID_Point,NULL,CLSCTX_INPROC_SERVER,IID_IPoint,(void**)&pnt);

		if (i == 0 || i ==4)
		{	
			pnt->put_X(xMin);
			pnt->put_Y(yMin);
		}
		else if (i ==1)
		{
			pnt->put_X(xMax);
			pnt->put_Y(yMin);
		}
		else if (i ==2)
		{
			pnt->put_X(xMax);
			pnt->put_Y(yMax);
		}
		else if (i ==3)
		{
			pnt->put_X(xMin);
			pnt->put_Y(yMax);
		}

		shp->InsertPoint(pnt, &i, &vbretval);
		pnt->Release();
	}
	return shp;
}