// MyButton.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "OnlineTetris.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{

}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()



// CMyButton �޽��� ó�����Դϴ�.




void CMyButton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if( nIDCtl = 1003){
		MessageBox( _T("aa"));

	}


	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
