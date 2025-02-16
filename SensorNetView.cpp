// SensorNetView.cpp : implementation of the CSensorNetView class
//

#include "stdafx.h"
#include "SensorNet.h"

#include "SensorNetDoc.h"
#include "SensorNetView.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSensorNetView

IMPLEMENT_DYNCREATE(CSensorNetView, CFormView)

BEGIN_MESSAGE_MAP(CSensorNetView, CFormView)
	//{{AFX_MSG_MAP(CSensorNetView)
	ON_BN_CLICKED(IDC_BUTTON_DISTRIBUTION_SUBMIT, OnButtonDistributionSubmit)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(ID_BUTTON_Hienbien, OnBUTTONHienbien)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_Hienbien, OnUpdateBUTTONHienbien)
	ON_COMMAND(ID_TREE, OnTree)
	ON_UPDATE_COMMAND_UI(ID_TREE, OnUpdateTree)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSensorNetView construction/destruction

CSensorNetView::CSensorNetView()
	: CFormView(CSensorNetView::IDD)
{

	//{{AFX_DATA_INIT(CSensorNetView)

	m_Radian = 20.0f;
	m_NumberOfSensors = 1628;
	m_FieldHeight = 300;
	m_FieldWidth = 300;

	//}}AFX_DATA_INIT
	// TODO: add construction code here

	m_ViewType = -3;
	
	m_Thinning = true;
	int i;

	ifstream is;
	is.open("topo.txt");

	is >> m_FieldWidth >> m_FieldHeight;
	is >> m_Radian;
	is >> m_NumberOfSensors;

	for (i = 0; i < m_NumberOfSensors; i++)
		is >> m_Sensors[i].x  >> m_Sensors[i].y;
	 

	is.close();


	is.open("boundary.txt");
	is >> m_NumberOfSensors;
	int tmp;
	for (i = 0; i < m_NumberOfSensors; i++) {
		is >> tmp;
		if (tmp == 1) m_Selected2[i] = true;
		else m_Selected2[i] = false;
	}

	is.close();
}



CSensorNetView::~CSensorNetView()
{
}

void CSensorNetView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSensorNetView)
	DDX_Text(pDX, IDC_EDIT_RADIAN, m_Radian);
	DDV_MinMaxFloat(pDX, m_Radian, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT_NUMBER_OF_SENSORS, m_NumberOfSensors);
	DDV_MinMaxLong(pDX, m_NumberOfSensors, 0, 80000);
	DDX_Text(pDX, IDC_EDIT_FIELD_HEIGHT, m_FieldHeight);
	DDV_MinMaxInt(pDX, m_FieldHeight, 10, 1000);
	DDX_Text(pDX, IDC_EDIT_FIELD_WIDTH, m_FieldWidth);
	DDV_MinMaxInt(pDX, m_FieldWidth, 10, 1000);
	//}}AFX_DATA_MAP
}

BOOL CSensorNetView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CSensorNetView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CSensorNetView printing

BOOL CSensorNetView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSensorNetView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSensorNetView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSensorNetView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CSensorNetView diagnostics

#ifdef _DEBUG
void CSensorNetView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSensorNetView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSensorNetDoc* CSensorNetView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSensorNetDoc)));
	return (CSensorNetDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSensorNetView message handlers

void CSensorNetView::DistributeSensors()
{
	//Khoi dong bo sinh ngau nhien
	srand(2*m_NumberOfSensors);

	//Sinh ngau nhien toa do cac sensor, va danh dau khong chon
	long i;
	
	for (i = 0; i < m_NumberOfSensors; i++)
	{	
		m_Sensors[i].x = rand()%m_FieldWidth + 20;
		m_Sensors[i].y = rand()%m_FieldHeight + 20;
	}

	m_TopoChanged = false;
	ComputeAll();

}


void CSensorNetView::Compute(long source)
{
		long isoLevel[MAX_NUMBER_OF_SENSORS];
		long queue[MAX_NUMBER_OF_SENSORS];
		long i, j, k;
		float r2 = m_Radian*m_Radian;
		

		//Khoi tao 
		for (i = 0; i < m_NumberOfSensors; i++)
		{
			isoLevel[i] = MAX_NUMBER_OF_SENSORS; //Chua xet, muc lon nhat
		}

		isoLevel[source] = 0; //j la nut phat
		queue[0] = source;

		//Xac dinh muc cho cac nut		
		i = j = 0; //Cho j tang truoc

		while (i <= j)
		{
			for (k = 0; k < m_NumberOfSensors; k++)
				if (isoLevel[k] == MAX_NUMBER_OF_SENSORS) //k chua xet
					if (distance2(m_Sensors[k], m_Sensors[queue[i]]) <= r2) // k la lang gieng cua queue[i]

					{
						isoLevel[k] = isoLevel[queue[i]] + 1;
						j++;
						queue[j] = k;	
					}

			i++;

			if (isoLevel[queue[j]] > 2) break; //Chi can muc 2
		}


		long NOQN = j+1;

		if (isoLevel[queue[NOQN-1]] < 2) //Khong co 2-lang gieng
		{
			m_Selected[source] = true;
			return;
		}


		//Xet cac 2-lang gieng
		int left, right;

		for (i = 0; i < NOQN; i++)
		if (isoLevel[queue[i]] == 2) //bat dau 2-lang gieng
		{
			left = i;
			break;
		}

		if (left == NOQN-1) //co duy nhat 1 2-lang gieng
		{
			m_Selected[source] = true;
			return;
		}

		for (i = left+1; i < NOQN; i++)
		if (isoLevel[queue[i]] != 2) //Het 2-lang gieng
		{
			right = i;
			break;
		}



		//Kiem tra tinh lien thong vong cua do thi 2-lang gieng
		//Tu nut queue[left], lan theo 1 chieu, 
		//neu khong di het cac nut 2-lang gieng thi 
		long q2[1000];
		long l2[1000];

		
		//Khoi tao
		for (i = left; i < right; i++)
			l2[i] = MAX_NUMBER_OF_SENSORS;

		l2[left] = 0;
		q2[left] = left;

		i = j = left;

		//Phan muc theo beacon cuc bo queue[left]

		while (i <= j) //xet diem queue[q2[i]]
		{
			for (k = left; k < right; k++)
				if (l2[k] == MAX_NUMBER_OF_SENSORS)  //Nut nay chua xet
					if (distance2(m_Sensors[queue[k]], m_Sensors[queue[q2[i]]]) <= r2)
				{
						l2[k] = l2[q2[i]]+1;
						j++;
						q2[j] = k;		
				}

			i++;
		}

		m_MB[source] = false;
		bool selected = false;

		//Kiem tra tinh lien thong cua do thi 2-neighbors

		for (i = left; i < right; i++)
		if (l2[i] == MAX_NUMBER_OF_SENSORS)
		{
			selected = true; //Khong lien thong, nut dang xet gan nhieu holes
			m_MB[source] =true;
			break;
		}


		//Trong truong hop do thi 2-neighbor lien thong,
		//kiem tra no tao thanh 1 vong
		
		if (selected == false)
		{
			//Tim nut 3-neighbor dau tien
			for (i = left; i < right; i++)
				if (l2[i] == 3) break;

			//Neu khong co nut nao nhu vay, 2-lang gieng khong the tao vong
			//nut dang xet gan hole
			if (i >= right) selected = true;
			else
			{
				//kiem tra xem co may cum 3-neighbor
				long q3[1000];
				q3[0] = i;
				i = j = 0;

				//Xoa 1 cum 3-neighbor
				while (i <= j)
				{
					for (k = left; k < right; k++)
						if (l2[k] == 3)
							if (distance2(m_Sensors[queue[k]], m_Sensors[queue[q3[i]]]) <= r2)
							{
								j++;
								q3[j] = k;
								l2[k] = -1; //Xoa dot 1
							}
					i++;
				}

				//Kiem tra xem con cum 3 thu 2 khong
				for (i = left; i < right; i++)
					if (l2[i] == 3) break;

				if (i >= right) selected = true; //Khong con cum 3 nao chung to cac 2-neighbor khong tao thanh vong
				else
				{
					//Kiem tra tinh khep cua vong
					//bang cach lan tu ben 3 sang ben -1 theo mot nua hinh tron
					//lan den dau dat -2 den do

					q3[0] = i;
					i = j = 0;

					bool reached = false;

					while (i <= j)
					{
						for (k = left; k < right; k++)
							if (l2[k] >= 3 || l2[k] == -1)
								if (distance2(m_Sensors[queue[k]], m_Sensors[queue[q3[i]]]) <= r2)
								{
									j++;
									q3[j] = k;

									if (l2[k] == -1)  //Da den duoc dich
									{
										reached = true;
										break;
									}

									l2[k] = -2; //Xoa dot 2
								}

						if (reached) break;
						i++;
					}

					//Den duoc dich, chung to vong kin
					if (!reached) selected = true;

				}	
			}	
		}

		m_Selected[source] = selected;
}



void CSensorNetView::ComputeAll()
{
	long i, j;
	float inner, outer;

	double r2 = (double)m_Radian*m_Radian;

	//Tim bien
	for (i = 0; i < m_NumberOfSensors; i++)
	{
		m_Selected[i] = false; //La bien
		Compute(i);
	}


	//Lam mong bien
	for (i = 0; i < m_NumberOfSensors; i++)
	{
		m_Selected2[i] = m_Selected[i];

		if (m_Thinning)
		{
			if (m_Selected[i]) //Nut gan bien, muc 1
			{
				inner = outer = 0.0f;

				for (j = 0; j < m_NumberOfSensors; j++)
					if (distance2(m_Sensors[i], m_Sensors[j]) <= r2) //La lang gieng
						if (m_Selected[j]) inner = inner + 1.0f; //So nut gan bien
						else outer = outer + 1.0f; //So nut khong gan bien

				if (outer/inner < 0.1f) m_Selected2[i] = true; //Thuc su gan bien
				else m_Selected2[i] = false;
			}
		}
	}


	//Tim cac nut SB2
	for (i = 0; i < m_NumberOfSensors; i++) m_SB2[i] = false;

	for (i = 0; i < m_NumberOfSensors; i++)
		if (m_Selected2[i] && m_MB[i])
			for (j = 0; j < m_NumberOfSensors; j++)
				if (m_Selected2[j] && !m_MB[i] && distance2(m_Sensors[j], m_Sensors[i]) <= r2)
				{
					m_SB2[j] = true;
				}

	


}

void CSensorNetView::OnButtonDistributionSubmit() 
{
	//Nhan tham so do nguoi dung nhap vao
	UpdateData(TRUE);

	//Sinh ngau nghien cac sensor
	DistributeSensors();


	//Ve lai
	Invalidate();	
}

double CSensorNetView::distance2(long x1, long y1, long x2, long y2)
{
	double dx = (double)(x2-x1);
	double dy = (double)(y2-y1);
	return (dx*dx + dy*dy);
}

double CSensorNetView::distance2(SENSOR s1, SENSOR s2)
{
	double dx = (double)(s2.x - s1.x);
	double dy = (double)(s2.y - s1.y);
	return (dx*dx + dy*dy);
}


bool CSensorNetView::InTheSameIsoLevelComponent(long *id1, long *id2, long *isoLevel)
{
	//sensors id1, id2
	if (isoLevel[*id1] != isoLevel[*id2]) return false;

	float r2 = m_Radian*m_Radian;
	long i, j, k, q[200], t[200];


	for (i = 0; i < m_NumberOfSensors; i++) t[i] = 0;

	q[0] = *id1;
	i = j = 0;

	while (i <= j)
	{
		for (k = 0; k < m_NumberOfSensors; k++)
			if (t[k] == 0 && isoLevel[k] == isoLevel[*id1] && distance2(m_Sensors[q[i]], m_Sensors[k]) <= r2)
			{
				t[k] = 1;
				j++;
				q[j] = k;

				if (k == *id2) return true;
			}

		i++;
	}

	return false;
}



int CSensorNetView::hopcount(long src, long  dest)
{
	int q[MAX_NUMBER_OF_SENSORS];
	int hc[MAX_NUMBER_OF_SENSORS];
	long i, j, k;
	float r2 = m_Radian*m_Radian;
		

	for (i = 0; i < m_NumberOfSensors; i++)
	{
		hc[i] = MAX_NUMBER_OF_SENSORS; //Chua xet, muc lon nhat
	}

	q[0] = src;
	i = j = 0;
	hc[src] = 0;


	while (i <= j)
	{
		for (k = 0; k < m_NumberOfSensors; k++)
			if (hc[k] == MAX_NUMBER_OF_SENSORS) //chua xet k
			if (distance2(m_Sensors[q[i]], m_Sensors[k]) <= r2)
			{
				hc[k] = hc[q[i]] + 1;
				j++;
				q[j] = k;

				if (k == dest) return hc[dest];
			}

		i++;

	}




	return hc[dest];
}




void CSensorNetView::OnDraw(CDC* pDC) 
{
	int r = 2;
	float r2 = m_Radian*m_Radian;

	

		long i, j;

		//Tat ca cac lien ket
			CPen myPen1;
			myPen1.CreatePen(0, 1, RGB(200, 200, 64));	
			pDC->SelectObject(myPen1);

			for (i = 0; i < m_NumberOfSensors; i++)
				for (j = i+1; j < m_NumberOfSensors; j++)
				{
					if (distance2(m_Sensors[i], m_Sensors[j]) <= r2)
					{
						pDC->MoveTo(m_Sensors[i]);
						pDC->LineTo(m_Sensors[j]);
					}
				}
	

		CPen myPen2;
		myPen2.CreatePen(0, 1, RGB(0, 0, 0));	
		pDC->SelectObject(myPen2);

		//Cac nut khong gan bien
		for (i = 0; i < m_NumberOfSensors; i++)
			if (! m_Selected2[i])
				pDC->Ellipse(m_Sensors[i].x - r, m_Sensors[i].y - r, m_Sensors[i].x + r, m_Sensors[i].y + r);

		
		CPen pen4sb1;
		pen4sb1.CreatePen(0, 1, RGB(255, 0, 0));	
		pDC->SelectObject(pen4sb1);
		r = 2;

		//Cac nut bien
		for (i = 0; i < m_NumberOfSensors; i++)
			if (m_Selected2[i])
			{
				pDC->Ellipse(m_Sensors[i].x - r, m_Sensors[i].y - r, m_Sensors[i].x + r, m_Sensors[i].y + r);
			}


	
	
}


void CSensorNetView::OnLButtonDown(UINT nFlags, CPoint point) 
{

	
	CFormView::OnLButtonDown(nFlags, point);
}

////////////////////////////////////////////////
//Chon cong cu


//Chon them 1 nut
void CSensorNetView::OnFileNew() 
{	
	m_ViewType = -1;
	Invalidate();
}

void CSensorNetView::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	if (m_ViewType == -1) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);	
}

//Chon them nhieu nut
void CSensorNetView::OnFileOpen() 
{
	m_ViewType = -2;
	Invalidate();
}

void CSensorNetView::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	if (m_ViewType == -2) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}

//Chon xoa nut
void CSensorNetView::OnFileSave() 
{
	m_ViewType = -3;
	Invalidate();
}

void CSensorNetView::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	if (m_ViewType == -3) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


//Chon xet vung anh huong cua mot nut
void CSensorNetView::OnEditCut() 
{
	m_ViewType = 0;
	Invalidate();
}

void CSensorNetView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	if (m_ViewType == 0) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}

void CSensorNetView::OnBUTTONHienbien() 
{
	m_ViewType = 1;

	if (m_TopoChanged) 
	{
		m_TopoChanged = false;
		ComputeAll(); //Tinh lai bien
	}
	
	Invalidate();
	
}

void CSensorNetView::OnUpdateBUTTONHienbien(CCmdUI* pCmdUI) 
{
	if (m_ViewType == 1) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
	
}


void CSensorNetView::OnTree() 
{
	m_ViewType = 2;

	if (m_TopoChanged) 
	{
		m_TopoChanged = false;
		ComputeAll(); //Tinh lai bien
	}

	Invalidate();
	
}

void CSensorNetView::OnUpdateTree(CCmdUI* pCmdUI) 
{
	if (m_ViewType == 2) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
	
}

