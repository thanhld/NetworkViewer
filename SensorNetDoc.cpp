// SensorNetDoc.cpp : implementation of the CSensorNetDoc class
//

#include "stdafx.h"
#include "SensorNet.h"

#include "SensorNetDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSensorNetDoc

IMPLEMENT_DYNCREATE(CSensorNetDoc, CDocument)

BEGIN_MESSAGE_MAP(CSensorNetDoc, CDocument)
	//{{AFX_MSG_MAP(CSensorNetDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSensorNetDoc construction/destruction

CSensorNetDoc::CSensorNetDoc()
{

}

CSensorNetDoc::~CSensorNetDoc()
{
}

BOOL CSensorNetDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSensorNetDoc serialization

void CSensorNetDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSensorNetDoc diagnostics

#ifdef _DEBUG
void CSensorNetDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSensorNetDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSensorNetDoc commands
