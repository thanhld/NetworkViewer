// SensorNetView.h : interface of the CSensorNetView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SENSORNETVIEW_H__7DE3BDD4_AF69_455C_9344_0239892A800E__INCLUDED_)
#define AFX_SENSORNETVIEW_H__7DE3BDD4_AF69_455C_9344_0239892A800E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_NUMBER_OF_SENSORS 10000
#define SENSOR POINT


class CSensorNetView : public CFormView
{
protected: // create from serialization only
	CSensorNetView();
	DECLARE_DYNCREATE(CSensorNetView)

public:
	//{{AFX_DATA(CSensorNetView)
	enum { IDD = IDD_SENSORNET_FORM };
	float	m_Radian;
	long	m_NumberOfSensors;
	int		m_FieldHeight;
	int		m_FieldWidth;
	//}}AFX_DATA

// Attributes
public:
	CSensorNetDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSensorNetView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSensorNetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSensorNetView)
	afx_msg void OnButtonDistributionSubmit();
	afx_msg void OnFileNew();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONHienbien();
	afx_msg void OnUpdateBUTTONHienbien(CCmdUI* pCmdUI);
	afx_msg void OnTree();
	afx_msg void OnUpdateTree(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnBtype();
	afx_msg void OnUpdateBtype(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	void ComputeAll();
	double distance2(long x1, long y1, long x2, long y2);
	double distance2(SENSOR s1, SENSOR s2);
	void Compute(long source);
	void DistributeSensors();
	int hopcount(long, long);
	long LCA(long, long);
	bool InTheSameIsoLevelComponent(long*, long *, long *);
				
	SENSOR m_Sensors[MAX_NUMBER_OF_SENSORS];	// (Vi tri) Cac sensor
	bool m_Selected[MAX_NUMBER_OF_SENSORS];		// (true neu nut nam gan bien)
	bool m_Selected2[MAX_NUMBER_OF_SENSORS];	// (true neu nut nam gan bien)
	bool m_MB[MAX_NUMBER_OF_SENSORS];			// MB
	bool m_SB2[MAX_NUMBER_OF_SENSORS];		// SB2
	bool m_Thinning;							// Co lam mong bien hay khong
	bool m_TopoChanged;							// Topo da thay doi
	int  m_ViewType;							//
	
	
	
						


};

#ifndef _DEBUG  // debug version in SensorNetView.cpp
inline CSensorNetDoc* CSensorNetView::GetDocument()
   { return (CSensorNetDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENSORNETVIEW_H__7DE3BDD4_AF69_455C_9344_0239892A800E__INCLUDED_)
