// SensorNetDoc.h : interface of the CSensorNetDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SENSORNETDOC_H__8EFD88C9_2D12_4A87_98EA_AD4778EC883A__INCLUDED_)
#define AFX_SENSORNETDOC_H__8EFD88C9_2D12_4A87_98EA_AD4778EC883A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSensorNetDoc : public CDocument
{
protected: // create from serialization only
	CSensorNetDoc();
	DECLARE_DYNCREATE(CSensorNetDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSensorNetDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSensorNetDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSensorNetDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENSORNETDOC_H__8EFD88C9_2D12_4A87_98EA_AD4778EC883A__INCLUDED_)
