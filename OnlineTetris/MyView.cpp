
// MyView.cpp : CMyView Ŭ������ ����
//



#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "OnlineTetris.h"
#endif

#include "MyDoc.h"
#include "MyView.h"
#include "ServerDialog.h"
#include "MyEdit.h"
#include "MySocket.h"
#include "OptionDialog.h"
#include "TUser.h"
#include "MyButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyView::OnFilePrintPreview)

	ON_COMMAND(_MENU_SERVER, &CMyView::OnMenuServer)
	ON_UPDATE_COMMAND_UI(_MENU_SERVER, &CMyView::OnUpdateMenuServer)
	ON_BN_CLICKED(1003, ReadyBtnClicked)
	ON_BN_CLICKED(1004, StartBtnClicked)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()

	ON_COMMAND(_BGM, &CMyView::OnBgm)
	ON_UPDATE_COMMAND_UI(_BGM, &CMyView::OnUpdateBgm)
	ON_COMMAND(ID_32800, &CMyView::On32800)
END_MESSAGE_MAP()

// CMyView ����/�Ҹ�

CMyView::CMyView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	Edt_InputEdit = NULL;
	pDoc = NULL;
	pServerDlg = NULL;
	pOptionDlg = NULL;
	Btn_Ready = Btn_Start = NULL;
	
}

CMyView::~CMyView()
{

}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	Mainpen.CreatePen( PS_SOLID,3, RGB(171,242,0));
	Subpen.CreatePen( PS_SOLID,4, RGB(128,128,128));
	HoleBrush.CreateStockObject( NULL_BRUSH);
	BkBrush.CreateSolidBrush( RGB(0,0,0));

	GameRect[0] = CRect( SX_MAIN, SY_MAIN, SX_MAIN + MAIN_WIDTH +5, SY_MAIN + MAIN_HEIGHT+5);
	
	
	GameRect[1] = CRect( SX_MAIN + MAIN_WIDTH + (1*GAME_SPACE) + ((1-1)*SUB_WIDTH), SY_MAIN,
						 SX_MAIN + MAIN_WIDTH + (1*GAME_SPACE) + (1*SUB_WIDTH) , SY_MAIN + SUB_HEIGHT);

	GameRect[2] = CRect( SX_MAIN + MAIN_WIDTH + (2*GAME_SPACE) + ((2-1)*SUB_WIDTH), SY_MAIN,
						 SX_MAIN + MAIN_WIDTH + (2*GAME_SPACE) + (2*SUB_WIDTH) , SY_MAIN + SUB_HEIGHT);

	GameRect[3] = CRect( SX_MAIN + MAIN_WIDTH + (3*GAME_SPACE) + ((3-1)*SUB_WIDTH), SY_MAIN,
						 SX_MAIN + MAIN_WIDTH + (3*GAME_SPACE) + (3*SUB_WIDTH) , SY_MAIN + SUB_HEIGHT);

	GameRect[4] = CRect( SX_MAIN + MAIN_WIDTH + (1*GAME_SPACE) + ((1-1)*SUB_WIDTH), SY_MAIN+ SUB_HEIGHT + GAME_SPACE,
						 SX_MAIN + MAIN_WIDTH + (1*GAME_SPACE) + (1*SUB_WIDTH) , SY_MAIN + SUB_HEIGHT*2 + GAME_SPACE);

	GameRect[5] = CRect( SX_MAIN + MAIN_WIDTH + (2*GAME_SPACE) + ((2-1)*SUB_WIDTH), SY_MAIN+ SUB_HEIGHT + GAME_SPACE,
						 SX_MAIN + MAIN_WIDTH + (2*GAME_SPACE) + (2*SUB_WIDTH) , SY_MAIN + SUB_HEIGHT*2 + GAME_SPACE);

	GameRect[6] = CRect( SX_MAIN + MAIN_WIDTH + (3*GAME_SPACE) + ((3-1)*SUB_WIDTH), SY_MAIN+ SUB_HEIGHT + GAME_SPACE,
						 SX_MAIN + MAIN_WIDTH + (3*GAME_SPACE) + (3*SUB_WIDTH) , SY_MAIN + SUB_HEIGHT*2 + GAME_SPACE);



	return CView::PreCreateWindow(cs);
}


void CMyView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	if( pDoc == NULL){
		pDoc = GetDocument();
		pDoc->pView = this;
	}
	if( pServerDlg == NULL){
		pServerDlg = new ServerDialog;
		pServerDlg->Create( _DLG_SERVER);
		pServerDlg->pView = this;
		pServerDlg->pDoc = pDoc;
	}
	if( pOptionDlg == NULL){
		pOptionDlg = new OptionDialog;
		pOptionDlg->pDoc= pDoc;
	}

	if(Btn_Start == NULL)
		Btn_Start = new CMyButton;
	
	if(Btn_Ready == NULL)
		Btn_Ready = new CMyButton;

	int cx = SX_MAIN + GAME_SPACE*4 + MAIN_WIDTH + SUB_WIDTH*3 ;

	Edt_ChatEdit.Create( WS_BORDER | WS_CHILD | WS_VISIBLE  | ES_MULTILINE | WS_VSCROLL, CRect( cx,  SY_MAIN , cx+CHAT_WIDTH, SY_MAIN + CHAT_HEIGHT)
		, this , 1000);

	if(Edt_InputEdit == NULL){
		Edt_InputEdit = new CMyEdit();
		Edt_InputEdit->Create( WS_BORDER | WS_CHILD | WS_VISIBLE , CRect(cx, SY_MAIN + CHAT_HEIGHT+10, cx+CHAT_WIDTH, SY_MAIN + CHAT_HEIGHT + INPUT_HEIGHT)
		, this , 1001);
	}

	int cy =  SY_MAIN + CHAT_HEIGHT + INPUT_HEIGHT + 10;
	Lst_EnterList.Create( LBS_STANDARD | WS_HSCROLL | WS_CHILD | WS_VISIBLE , CRect( cx , cy, cx + ENTERLIST_WIDTH , cy + ENTERLIST_HEIGHT),this, 1002);

	Btn_Ready->Create( _T("�غ�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON , 
		CRect( SX_MAIN + MAIN_WIDTH + GAME_SPACE*4 + SUB_WIDTH*3 , 
				SY_MAIN + MAIN_HEIGHT , 
				SX_MAIN + MAIN_WIDTH + GAME_SPACE*4 + SUB_WIDTH*3 + BTN_WIDTH,  
				SY_MAIN + MAIN_HEIGHT + 10 + BTN_HEIGHT
			),
		this, 1003);

	cy = SY_MAIN + MAIN_HEIGHT + 10 + BTN_HEIGHT + 10;
	Btn_Start->Create( _T("�����ϱ�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_DISABLED,
		CRect( SX_MAIN + MAIN_WIDTH + GAME_SPACE*4 + SUB_WIDTH*3
		, cy 
		, SX_MAIN + MAIN_WIDTH + GAME_SPACE*4 + SUB_WIDTH*3 + BTN_WIDTH  
		, cy + BTN_HEIGHT 
		),
		this, 1004);


	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

// CMyView �׸���

void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDC=GetDC();
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	CBitmap *pOldBitmap, bitmap;

	memDC.CreateCompatibleDC(pDC);
	bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pOldBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
	memDC.PatBlt(0,0, rect.Width(), rect.Height(), WHITENESS);
	
	DrawImage(&memDC);

	pDC->BitBlt(0,0, rect.Width(), rect.Height(), &memDC, 0,0,SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	ReleaseDC(pDC);
	bitmap.DeleteObject();




	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}

void CMyView::VirtualDraw(){

	CDC *pDC=GetDC();
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	CBitmap *pOldBitmap, bitmap;

	memDC.CreateCompatibleDC(pDC);
	bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pOldBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
	memDC.PatBlt(0,0, rect.Width(), rect.Height(), WHITENESS);
	
	DrawImage(&memDC);

	pDC->BitBlt(0,0, rect.Width(), rect.Height(), &memDC, 0,0,SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	ReleaseDC(pDC);
	bitmap.DeleteObject();




}

void CMyView::DrawImage(CDC *pDC){
	
	CImage WinBg;
	CImage MainBg;
	CImage SubBg;
	CImage NextBg;
	CImage MainDeadBg;
 	CImage SubDeadBg;
	CImage WinImg;
	CImage ReadyImg;
	
	CFont IdFont;

	ReadyImg.LoadFromResource( AfxGetInstanceHandle() , _READY);
	WinImg.LoadFromResource(  AfxGetInstanceHandle(), _WIN);

	MainDeadBg.LoadFromResource( AfxGetInstanceHandle(),  _MAINDEADBK);
	SubDeadBg.LoadFromResource( AfxGetInstanceHandle(),  _SUBDEADBK);

	WinBg.LoadFromResource( AfxGetInstanceHandle(), _WINBG10);
	WinBg.BitBlt( pDC->m_hDC,0,0);

	MainBg.LoadFromResource(AfxGetInstanceHandle(), _MAINBG);
	MainBg.BitBlt( pDC->m_hDC, SX_MAIN, SY_MAIN);
	
	SubBg.LoadFromResource( AfxGetInstanceHandle(), _SUBBG);
	SubBg.BitBlt( pDC->m_hDC, SX_MAIN+MAIN_WIDTH+GAME_SPACE , SY_MAIN);
	SubBg.BitBlt( pDC->m_hDC, SX_MAIN+MAIN_WIDTH+GAME_SPACE*2 + SUB_WIDTH , SY_MAIN);
	SubBg.BitBlt( pDC->m_hDC, SX_MAIN+MAIN_WIDTH+GAME_SPACE*3 + SUB_WIDTH*2 , SY_MAIN);
	SubBg.BitBlt( pDC->m_hDC, SX_MAIN+MAIN_WIDTH+GAME_SPACE , SY_MAIN + SUB_HEIGHT + GAME_SPACE);
	SubBg.BitBlt( pDC->m_hDC, SX_MAIN+MAIN_WIDTH+GAME_SPACE*2 + SUB_WIDTH , SY_MAIN + SUB_HEIGHT + GAME_SPACE);
	SubBg.BitBlt( pDC->m_hDC, SX_MAIN+MAIN_WIDTH+GAME_SPACE*3 + SUB_WIDTH*2 , SY_MAIN + SUB_HEIGHT + GAME_SPACE);

	NextBg.LoadFromResource( AfxGetInstanceHandle() , _NEXTBK);
	NextBg.BitBlt( pDC->m_hDC, SX_MAIN + MAIN_WIDTH - NextBg.GetWidth() , SY_MAIN + MAIN_HEIGHT + 10);

	IdFont.CreatePointFont(150, _T("a���������B"));
	pDC->SelectObject(&IdFont);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor( RGB(0,255,0));

	POINT c;

	if( pDoc != NULL && !pDoc->Start && !pDoc->End){

		POSITION pos = pDoc->Client_UserList.GetHeadPosition();
		TUser *user = NULL;
		int idx=-1;
		while(pos != NULL){
			user = (TUser *)pDoc->Client_UserList.GetNext(pos);
			idx = user->GetOrder();

			switch( idx){

				case 1:
					if( user->GetReady())						
						ReadyImg.TransparentBlt( pDC->m_hDC, SX_MAIN+ ReadyImg.GetWidth()/10, (SY_MAIN+MAIN_HEIGHT)/2, ReadyImg.GetWidth(), ReadyImg.GetHeight(), RGB(0,255,255));				
					
					pDC->TextOutW( SX_MAIN + MAIN_WIDTH/2-10 , SY_MAIN-20, user->GetUserName());
					break;

				case 2:
					if( user->GetReady())						
						ReadyImg.TransparentBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE + ReadyImg.GetWidth()/10, (SY_MAIN+MAIN_HEIGHT)/2, 
												ReadyImg.GetWidth()*0.6 , ReadyImg.GetHeight()*0.6, RGB(0,255,255));
					

					pDC->TextOutW( SX_MAIN + MAIN_WIDTH +GAME_SPACE + SUB_WIDTH/2-10 , SY_MAIN-20, user->GetUserName());
					break;

				case 3:
					if( user->GetReady())
						ReadyImg.TransparentBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE*(idx-1) + SUB_WIDTH + ReadyImg.GetWidth()/10, (SY_MAIN+MAIN_HEIGHT)/2, 
													ReadyImg.GetWidth()*0.6 , ReadyImg.GetHeight()*0.6, RGB(0,255,255));
					

					pDC->TextOutW( SX_MAIN + MAIN_WIDTH +GAME_SPACE*(idx-1) + SUB_WIDTH*1.5 -10 , SY_MAIN-20, user->GetUserName());
					break;
				case 4:
					if( user->GetReady())
						ReadyImg.TransparentBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE*(idx-1) + SUB_WIDTH*2+ ReadyImg.GetWidth()/10, (SY_MAIN+MAIN_HEIGHT)/2, 
											ReadyImg.GetWidth()*0.6 , ReadyImg.GetHeight()*0.6, RGB(0,255,255));
					

					pDC->TextOutW( SX_MAIN + MAIN_WIDTH +GAME_SPACE*(idx-1) + SUB_WIDTH*2.5 -10 , SY_MAIN-20, user->GetUserName());
					break;
				case 5:
					if( user->GetReady())
						ReadyImg.TransparentBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE + ReadyImg.GetWidth()/10, MAIN_HEIGHT + (SY_MAIN+MAIN_HEIGHT)/2, 
													ReadyImg.GetWidth()*0.6 , ReadyImg.GetHeight()*0.6, RGB(0,255,255));
					

					pDC->TextOutW( SX_MAIN + MAIN_WIDTH +GAME_SPACE + SUB_WIDTH/2-10 , SY_MAIN + MAIN_HEIGHT - 20, user->GetUserName());
					break;
			}
		
			
		}
	}//before start 


	if(pDoc != NULL && (pDoc->Start || pDoc->End)){
		CImage MainFigure;
		CImage GhostFigure;
	
		//main�� �̸����
		pDC->TextOutW( SX_MAIN + MAIN_WIDTH/2-10 , SY_MAIN-20, pDoc->Name);

		switch(ME->FG.NextFigure){

			case LMINO:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() , _LMINO);
				break;
			case JMINO:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() ,_JMINO);				
				break;
			case OMINO:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() ,_OMINO);
				break;
			case TMINO:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() ,_TMINO);
				break;
			case SMINO:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() ,_SMINO);
				break;
			case ZMINO:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() ,_ZMINO);
				break;
			case IMINO:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() ,_IMINO);
				break;
			default:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() ,_TMINO);
				break;
		}

		for(int i=0 ; i < 4 ; i++)
			for(int l=0 ; l < 2 ; l++){
				if( ME->NextFigureBoard[i][l] == 1)
					MainFigure.BitBlt( pDC->m_hDC,  SX_MAIN + MAIN_WIDTH - NextBg.GetWidth() + MAIN_SIZE*l,  SY_MAIN + MAIN_HEIGHT + 10 + MAIN_SIZE*i);
			}

			MainFigure.Destroy();

		switch(ME->FG.Figure){

			case LMINO:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() , _LMINO);
				GhostFigure.LoadFromResource( AfxGetInstanceHandle() , _LMINO);
				break;
			case JMINO:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() ,_JMINO);
				GhostFigure.LoadFromResource( AfxGetInstanceHandle() , _JMINO);
				break;
			case OMINO:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() ,_OMINO);
				GhostFigure.LoadFromResource( AfxGetInstanceHandle() , _OMINO);
				break;
			case TMINO:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() ,_TMINO);
				GhostFigure.LoadFromResource( AfxGetInstanceHandle() , _TMINO);
				break;
			case SMINO:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() ,_SMINO);
				GhostFigure.LoadFromResource( AfxGetInstanceHandle() , _SMINO);
				break;
			case ZMINO:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() ,_ZMINO);
				GhostFigure.LoadFromResource( AfxGetInstanceHandle() , _ZMINO);
				break;
			case IMINO:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() ,_IMINO);
				GhostFigure.LoadFromResource( AfxGetInstanceHandle() , _IMINO);
				break;
			default:
				MainFigure.LoadFromResource( AfxGetInstanceHandle() ,_TMINO);
				GhostFigure.LoadFromResource( AfxGetInstanceHandle() , _TMINO);
				break;

		}	

		

		//������ ���� �׸���
			
		for(int i=0 ; i < FG_FIXEDNUM ; i++){
			c = ME->FG.FgInfo[i];
			MainFigure.BitBlt( pDC->m_hDC, SX_MAIN + MainFigure.GetWidth()*(c.x) , SY_MAIN+MainFigure.GetHeight()*(c.y));
		}
		MainFigure.Destroy();

		//�������� �׸���
		if(pDoc->Ghost){
			for(int i=0 ; i < FG_FIXEDNUM ; i++){
				c = ME->GhostFG.FgInfo[i];
				GhostFigure.AlphaBlend( pDC->m_hDC, SX_MAIN + GhostFigure.GetWidth()*(c.x) , SY_MAIN+GhostFigure.GetHeight()*(c.y),90);
			}
			GhostFigure.Destroy();
		}

		//������ ���� �׸���
		for(int i=0; i < VERNUM ; i++){
			for(int l=0; l < HORNUM ; l++)
			{
				if(ME->FixedBoard[i][l]!=0)
				{
					switch(ME->FixedBoard[i][l])
					{
						case TMINO:
							MainFigure.LoadFromResource(AfxGetInstanceHandle() ,_TMINO);
							break;
						case LMINO:
							MainFigure.LoadFromResource(AfxGetInstanceHandle() ,_LMINO);
							break;
						case JMINO:
							MainFigure.LoadFromResource(AfxGetInstanceHandle() ,_JMINO);
							break;
						case OMINO:
							MainFigure.LoadFromResource(AfxGetInstanceHandle() ,_OMINO);
							break; 
						case SMINO:
							MainFigure.LoadFromResource(AfxGetInstanceHandle() ,_SMINO);
							break;
						case ZMINO:
							MainFigure.LoadFromResource(AfxGetInstanceHandle() ,_ZMINO);
							break;
						case IMINO:
							MainFigure.LoadFromResource(AfxGetInstanceHandle() ,_IMINO);							
							break;
						default:
							MainFigure.LoadFromResource(AfxGetInstanceHandle() ,_TMINO);
							break;
					}
					MainFigure.BitBlt( pDC->m_hDC, SX_MAIN+ MainFigure.GetWidth()*l, SY_MAIN+MainFigure.GetHeight()*i);
										
					MainFigure.Destroy();
				}//if								
			}//for
		}//for	
		

	if(!ME->GetSurvive())
		MainDeadBg.AlphaBlend(pDC->m_hDC, SX_MAIN , SY_MAIN, 90 ,AC_SRC_OVER);
		
		


		//----------------------------�����̹����׸���(�ڱⲨ ��)-------------------------------------//
		

		CImage SubFigure;
		CImage SubMoveFigure;

		POSITION pos = pDoc->Client_UserList.GetHeadPosition();
		TUser *user = NULL;
		int idx=-1;
		while(pos != NULL){
			user = (TUser *)pDoc->Client_UserList.GetNext(pos);
			idx = user->GetOrder();
			if(user->GetUserName().Compare( pDoc->Name)==0)
				continue;

			//�̸� ���
			switch(idx){

				case 2:
					pDC->TextOutW( SX_MAIN + MAIN_WIDTH+ GAME_SPACE + SUB_WIDTH/4 , SY_MAIN-20, user->GetUserName());	
					break;
				case 3:
					pDC->TextOutW( SX_MAIN  + MAIN_WIDTH + SUB_WIDTH + SUB_WIDTH/4 + GAME_SPACE*2 , SY_MAIN-20, user->GetUserName());	
					break;
				case 4:
					pDC->TextOutW( SX_MAIN + MAIN_WIDTH + SUB_WIDTH*2 + SUB_WIDTH/4 , SY_MAIN-20, user->GetUserName());	
					break;
				case 5:
					pDC->TextOutW( SX_MAIN + MAIN_WIDTH/2-10 + MAIN_WIDTH+ GAME_SPACE , SY_MAIN-20 + MAIN_HEIGHT, user->GetUserName());	
					break;
				case 6:
					pDC->TextOutW( SX_MAIN + MAIN_WIDTH/2-10 + MAIN_WIDTH+ SUB_WIDTH +GAME_SPACE*2 , SY_MAIN-20 + MAIN_HEIGHT , user->GetUserName());	
					break;
				case 7:
					pDC->TextOutW( SX_MAIN + MAIN_WIDTH/2-10 + MAIN_WIDTH+ SUB_WIDTH*2 +GAME_SPACE*3 , SY_MAIN-20 + MAIN_HEIGHT , user->GetUserName());	
					break;

				break;
			}//switck
			

			//Ŭ���̾�Ʈ�� �����̴� ������ ����� �Ǵ�
			switch(user->FG.Figure){
				case LMINO:
					SubMoveFigure.LoadFromResource( AfxGetInstanceHandle() , _SUBL);
					break;
				case JMINO:
					SubMoveFigure.LoadFromResource( AfxGetInstanceHandle() ,_SUBJ);
					break;
				case OMINO:
					SubMoveFigure.LoadFromResource( AfxGetInstanceHandle() ,_SUBO);
					break;
				case TMINO:
					SubMoveFigure.LoadFromResource( AfxGetInstanceHandle() ,_SUBT);
					break;
				case SMINO:
					SubMoveFigure.LoadFromResource( AfxGetInstanceHandle() ,_SUBS);
					break;
				case ZMINO:
					SubMoveFigure.LoadFromResource( AfxGetInstanceHandle() ,_SUBZ);
					break;
				case IMINO:
					SubMoveFigure.LoadFromResource( AfxGetInstanceHandle() ,_SUBI);
					break;
				default:
					SubMoveFigure.LoadFromResource( AfxGetInstanceHandle() ,_SUBT);
					break;


			}
			//Ŭ���̾�Ʈ�� ��ȣ�� �´� ��ġ�� ���
			for(int i=0 ; i < FG_FIXEDNUM ; i++){
				c = user->FG.FgInfo[i];
				switch(user->GetOrder()){
					case 2:
						SubMoveFigure.BitBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE + SubMoveFigure.GetWidth()*c.x, SY_MAIN+SubMoveFigure.GetHeight()*c.y);//
						break;

					case 3:
						SubMoveFigure.BitBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE*2 + SUB_WIDTH + SubMoveFigure.GetWidth()*c.x, SY_MAIN+SubMoveFigure.GetHeight()*c.y);//
						break;
					case 4:
						SubMoveFigure.BitBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE*3 + SUB_WIDTH*2 + SubMoveFigure.GetWidth()*c.x, SY_MAIN+SubMoveFigure.GetHeight()*c.y);//
						break;	
					case 5:
						SubMoveFigure.BitBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE + SubMoveFigure.GetWidth()*c.x, SY_MAIN+MAIN_HEIGHT + GAME_SPACE + SubMoveFigure.GetHeight()*c.y);//
						break;	
					case 6:
						SubMoveFigure.BitBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE*2 + SUB_WIDTH + SubMoveFigure.GetWidth()*c.x, SY_MAIN+MAIN_HEIGHT + GAME_SPACE + SubMoveFigure.GetHeight()*c.y);//
						break;
					case 7 :
						SubMoveFigure.BitBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE*3 + SUB_WIDTH*2 + SubMoveFigure.GetWidth()*c.x, SY_MAIN+MAIN_HEIGHT + GAME_SPACE + SubMoveFigure.GetHeight()*c.y);//
						break;	

				}
			}
			SubMoveFigure.Destroy();
			SubFigure.Destroy();

			//Ŭ���̾�Ʈ �������� ������ ������ � ������ �Ǵ�
			for(int i=0; i < VERNUM ; i++){
				for(int l=0; l < HORNUM ; l++)
				{
					if(user->StateBoard[i][l]!=0)
					{
						switch(user->StateBoard[i][l])
						{
							case TMINO:
								SubFigure.LoadFromResource(AfxGetInstanceHandle() ,_SUBT);
								break;
							case LMINO:
								SubFigure.LoadFromResource(AfxGetInstanceHandle() ,_SUBL);
								break;
							case JMINO:
								SubFigure.LoadFromResource(AfxGetInstanceHandle() ,_SUBJ);
								break;
							case OMINO:
								SubFigure.LoadFromResource(AfxGetInstanceHandle() ,_SUBO);
								break; 
							case SMINO:
								SubFigure.LoadFromResource(AfxGetInstanceHandle() ,_SUBS);
								break;
							case ZMINO:
								SubFigure.LoadFromResource(AfxGetInstanceHandle() ,_SUBZ);
								break;
							case IMINO:
								SubFigure.LoadFromResource(AfxGetInstanceHandle() ,_SUBI);
								break;
							default:
								SubFigure.LoadFromResource(AfxGetInstanceHandle() ,_SUBT);
								break;
						}
						

						//Ŭ���̾�Ʈ���� ������ �ǴܵǸ� �ش���ġ �׸���.
					switch(idx){

						case 2:							
							SubFigure.BitBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE + SubFigure.GetWidth()*l, SY_MAIN+SubFigure.GetHeight()*i);//
							break;

						case 3:
							SubFigure.BitBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE*2 + SUB_WIDTH + SubFigure.GetWidth()*l, SY_MAIN+SubFigure.GetHeight()*i);				
							break;
						case 4:
							SubFigure.BitBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE*3 +SUB_WIDTH*2 + SubFigure.GetWidth()*l, SY_MAIN+SubFigure.GetHeight()*i);						
							break;
						case 5:
							SubFigure.BitBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE + SubFigure.GetWidth()*l, SY_MAIN + MAIN_HEIGHT + GAME_SPACE +SubFigure.GetHeight()*i);											
							break;
						case 6:
							SubFigure.BitBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH +  GAME_SPACE*2 + SUB_WIDTH + + SubFigure.GetWidth()*l, SY_MAIN + MAIN_HEIGHT + GAME_SPACE +SubFigure.GetHeight()*i);				
							
							break;
						case 7:
							SubFigure.BitBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH +  GAME_SPACE*2 + SUB_WIDTH*2 + + SubFigure.GetWidth()*l, SY_MAIN + MAIN_HEIGHT + GAME_SPACE +SubFigure.GetHeight()*i);				
							break;
						default:
							;
						}//swtich


					}//if

					SubFigure.Destroy();
				}//for
			}//for

			//Ŭ���̾�Ʈ�� ������ ������ó��
			if(!user->GetSurvive()){
				switch(idx){
					case 2:							
						SubDeadBg.AlphaBlend( pDC->m_hDC, SX_MAIN + GAME_SPACE + MAIN_WIDTH, SY_MAIN, 90);
				
						break;
					case 3:
						SubDeadBg.AlphaBlend( pDC->m_hDC, SX_MAIN + GAME_SPACE*2 + SUB_WIDTH + MAIN_WIDTH, SY_MAIN, 90);
						break;
					case 4:
						SubDeadBg.AlphaBlend( pDC->m_hDC, SX_MAIN + GAME_SPACE*3 + SUB_WIDTH*2 + MAIN_WIDTH, SY_MAIN, 90);
						break;
					case 5:
						SubDeadBg.AlphaBlend( pDC->m_hDC, SX_MAIN + GAME_SPACE + MAIN_WIDTH , SY_MAIN + GAME_SPACE + MAIN_HEIGHT, 90);
						break;
					case 6:
						SubDeadBg.AlphaBlend( pDC->m_hDC, SX_MAIN + GAME_SPACE*2 + MAIN_WIDTH + SUB_WIDTH , SY_MAIN+ GAME_SPACE + MAIN_HEIGHT, 90);
							
						break;
					case 7:
						SubDeadBg.AlphaBlend( pDC->m_hDC, SX_MAIN + GAME_SPACE*3+ MAIN_WIDTH + SUB_WIDTH*2 , SY_MAIN+ GAME_SPACE + MAIN_HEIGHT, 90);
						break;
					default:
						;
				}//swtich
			}
			
		}//while

		if(pDoc->End ){

			POSITION pos = pDoc->Client_UserList.GetHeadPosition();
			TUser *user = NULL;
			while( pos != NULL){

				user = (TUser *)pDoc->Client_UserList.GetNext(pos);

				if(user->GetSurvive()){
					switch(user->GetOrder()){									
						case 1:											
							WinImg.TransparentBlt( pDC->m_hDC, SX_MAIN+ WinImg.GetWidth()/10, (SY_MAIN+MAIN_HEIGHT)/2, WinImg.GetWidth(), WinImg.GetHeight(), RGB(0,255,255));				
							break;
						case 2:										
							WinImg.TransparentBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE + WinImg.GetWidth()/10, (SY_MAIN+MAIN_HEIGHT)/2, 
														WinImg.GetWidth()*0.6 , WinImg.GetHeight()*0.6, RGB(0,255,255));	
							break;
						case 3:					
							WinImg.TransparentBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE*2 + SUB_WIDTH + WinImg.GetWidth()/10, (SY_MAIN+MAIN_HEIGHT)/2, 
														WinImg.GetWidth()*0.6 , WinImg.GetHeight()*0.6, RGB(0,255,255));
							break;
						case 4:					
							WinImg.TransparentBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE*3+ SUB_WIDTH*2+ WinImg.GetWidth()/10, (SY_MAIN+MAIN_HEIGHT)/2, 
												WinImg.GetWidth()*0.6 , WinImg.GetHeight()*0.6, RGB(0,255,255));
							break;
						case 5:
						
							WinImg.TransparentBlt( pDC->m_hDC, SX_MAIN+ MAIN_WIDTH + GAME_SPACE + WinImg.GetWidth()/10, MAIN_HEIGHT + (SY_MAIN+MAIN_HEIGHT)/2, 
															WinImg.GetWidth()*0.6 , WinImg.GetHeight()*0.6, RGB(0,255,255));				
							break;


					}//switch			
				}//if getsurvive

				//������ ������ �¸����� �ܿ��� ��� ������ó��
				else{
					switch(user->GetOrder()){

						case 1:
							SubDeadBg.AlphaBlend( pDC->m_hDC, SX_MAIN, SY_MAIN, 90);
							break;

						case 2:							
							SubDeadBg.AlphaBlend( pDC->m_hDC, SX_MAIN + GAME_SPACE + MAIN_WIDTH, SY_MAIN, 90);
				
							break;
						case 3:
							SubDeadBg.AlphaBlend( pDC->m_hDC, SX_MAIN + GAME_SPACE*2 + SUB_WIDTH + MAIN_WIDTH, SY_MAIN, 90);
							break;
						case 4:
							SubDeadBg.AlphaBlend( pDC->m_hDC, SX_MAIN + GAME_SPACE*3 + SUB_WIDTH*2 + MAIN_WIDTH, SY_MAIN, 90);
							break;
						case 5:
							SubDeadBg.AlphaBlend( pDC->m_hDC, SX_MAIN + GAME_SPACE + MAIN_WIDTH , SY_MAIN + GAME_SPACE + MAIN_HEIGHT, 90);
							break;
						case 6:
							SubDeadBg.AlphaBlend( pDC->m_hDC, SX_MAIN + GAME_SPACE*2 + MAIN_WIDTH + SUB_WIDTH , SY_MAIN+ GAME_SPACE + MAIN_HEIGHT, 90);
							
							break;
						case 7:
							SubDeadBg.AlphaBlend( pDC->m_hDC, SX_MAIN + GAME_SPACE*3+ MAIN_WIDTH + SUB_WIDTH*2 , SY_MAIN+ GAME_SPACE + MAIN_HEIGHT, 90);
							break;
						default:
							;
					}//swtich		

				}//else

			}//while

		}//if end

	}//if start

	
}


// CMyView �μ�


void CMyView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

//void CMyView::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

//void CMyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
//{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
//}


// CMyView ����

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyView �޽��� ó����

void CMyView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if( nIDEvent == TIMER_TETRIS){

		if(ME == NULL)
			return;

		TUser::FIGURE *fg = &(ME->FG);
		POINT c;
		int i=0;
		for(i=0 ; i < FG_FIXEDNUM ; i++){
			c = fg->FgInfo[i];
			if( c.y+1 == VERNUM || ME->GameBoard[ c.y+1 ][ c.x ] == 1){
				SetFigure();
				CreateFigure();
				break;
			}

		}
		if( i == FG_FIXEDNUM)
			MoveToDown();
	
		VirtualDraw();
	}

	else if( nIDEvent == TIMER_SENDMAPSTATE && ME->GetSurvive() && ( pDoc->Open || pDoc->Enter) ){
		pDoc->m_mySocket->Sendmapstate();
		VirtualDraw();
	}

	else if( nIDEvent == TIMER_NEXTLEVEL){
		pDoc->LineRemain++;
		
		if(pDoc->LineRemain % 10 ==0){
			pDoc->m_mySocket->SendLine(1, true);
		}
	}
	
	CView::OnTimer(nIDEvent);
}


void CMyView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	

	if(pDoc->Start && ME->GetSurvive() ){

		if(ME == NULL){
			MessageHandler(-1);
			return ;
		}
		TUser::FIGURE *fg = &(ME->FG);
		POINT c;

		if( nChar == VK_SPACE){
			bool chk = false;
			int l=0;
			//���� ������ ���� ���ؼ� ���� ���� ���� ã�´�.
			while(fg->end.y < VERNUM){
			
				for(l=0 ; l < FG_FIXEDNUM ; l++){
					c = ME->FG.FgInfo[l];
					//�ٴ��̳� ������ ����
					if(c.y == VERNUM-1 || ME->GameBoard[ c.y+1 ][ c.x ] == 1){
						SetFigure();
						CreateFigure();
						goto brk;
					}
				}

				MoveToDown();
				

			}		
		}//VK_SPACE

		else if( nChar == VK_LEFT){
			if(fg->end.x==0 )
				goto brk;


			int i=0;
			for(i=0 ; i < FG_FIXEDNUM ; i++){
				c = fg->FgInfo[i];	
				if( ME->GameBoard[ c.y ][ c.x-1] ==1)
					break;
			}
			if(i==FG_FIXEDNUM)
				MoveToLeft();

			ME->GhostFG  = ME->FG;
			SetGhostFigure();

		}//vk_left	

		else if( nChar == VK_RIGHT ){
			if(fg->end.x + fg->Width == HORNUM)
				goto brk;

			int i=0;
			for(i=0 ; i < FG_FIXEDNUM ; i++){
				c = fg->FgInfo[i];	
				if( ME->GameBoard[ c.y ][ c.x+1] ==1)
					break;
			}
			if(i==FG_FIXEDNUM)
				MoveToRight();
			
			if(pDoc->Ghost){
				ME->GhostFG  = ME->FG;
				SetGhostFigure();
			}
		}//vk_right

		else if(  nChar == VK_DOWN ){
	
			int i=0;
			for(i=0 ; i < FG_FIXEDNUM ; i++){
				c = fg->FgInfo[i];
				if( c.y+1 == VERNUM || ME->GameBoard[ c.y+1 ][ c.x ] == 1){
					SetFigure();
					CreateFigure();
					break;
				}

			}
			if( i == FG_FIXEDNUM)
				MoveToDown();

			if(pDoc->Ghost){
				ME->GhostFG  = ME->FG;
				SetGhostFigure();
			}

		}//vk_down


		else if( nChar == VK_UP ){
			POINT c= ME->FG.end;
			TUser::FIGURE backup;
			backup.dir = fg->dir;
			backup.end = fg->end;
			backup.Figure = fg->Figure;
			backup.Height = fg->Height;
			backup.Width = fg->Width;
			backup.NextFigure = fg->NextFigure;

			switch(fg->Figure){

					case JMINO:
						switch(fg->dir){
							case 1:	

								fg->FgInfo[0].x = c.x;
								fg->FgInfo[0].y = c.y;
								fg->FgInfo[1].x = c.x+1;
								fg->FgInfo[1].y = c.y;
								fg->FgInfo[2].x = c.x+1;
								fg->FgInfo[2].y = c.y-1;
								fg->FgInfo[3].x = c.x+1;
								fg->FgInfo[3].y = c.y-2;
								fg->Height=3;
								fg->Width=2;
								fg->dir=2;

								break;
							case 2:
								fg->FgInfo[0].x = c.x+1;
								fg->FgInfo[0].y = c.y;
								fg->FgInfo[1].x = c.x+1;
								fg->FgInfo[1].y = c.y-1;
								fg->FgInfo[2].x = c.x;
								fg->FgInfo[2].y = c.y-1;
								fg->FgInfo[3].x = c.x-1;
								fg->FgInfo[3].y = c.y-1;

								fg->Height=2;
								fg->Width=3;
								fg->end.x-=1;
								fg->dir=3;
								break;
							case 3:								
								fg->FgInfo[0].x = c.x+1;
								fg->FgInfo[0].y = c.y-1;
								fg->FgInfo[1].x = c.x+2;
								fg->FgInfo[1].y = c.y-1;
								fg->FgInfo[2].x = c.x+1;
								fg->FgInfo[2].y = c.y;
								fg->FgInfo[3].x = c.x+1;
								fg->FgInfo[3].y = c.y+1;

								fg->Height=3;
								fg->Width=2;
								fg->end.y+=1;
								fg->end.x+=1;
								fg->dir=4;
								break;
							case 4:
								fg->FgInfo[0].x = c.x;
								fg->FgInfo[0].y = c.y-2;
								fg->FgInfo[1].x = c.x;
								fg->FgInfo[1].y = c.y-1;
								fg->FgInfo[2].x = c.x+1;
								fg->FgInfo[2].y = c.y-1;
								fg->FgInfo[3].x = c.x+2;
								fg->FgInfo[3].y = c.y-1;

								fg->Height=2;
								fg->Width=3;
								fg->end.y-=1;
								fg->dir=1;
								break;
						}
						break;
					case LMINO:
						switch(fg->dir){
							case 1:
								fg->FgInfo[0].x = c.x-1;
								fg->FgInfo[0].y = c.y;
								fg->FgInfo[1].x = c.x;
								fg->FgInfo[1].y = c.y;
								fg->FgInfo[2].x = c.x+1;
								fg->FgInfo[2].y = c.y;
								fg->FgInfo[3].x = c.x+1;
								fg->FgInfo[3].y = c.y-1;
								fg->end.x-=1;
								fg->Height=2;
								fg->Width=3;
								
								fg->dir=2;
								break;
							case 2:
								fg->FgInfo[0].x = c.x+1;
								fg->FgInfo[0].y = c.y-1;
								fg->FgInfo[1].x = c.x+2;
								fg->FgInfo[1].y = c.y-1;
								fg->FgInfo[2].x = c.x+2;
								fg->FgInfo[2].y = c.y;
								fg->FgInfo[3].x = c.x+2;
								fg->FgInfo[3].y = c.y+1;
								fg->Height=3;
								fg->Width=2;
								fg->end.x+=1;
								fg->end.y+=1;
								fg->dir=3;
								break;
							case 3:
								fg->FgInfo[0].x = c.x;
								fg->FgInfo[0].y = c.y-2;
								fg->FgInfo[1].x = c.x;
								fg->FgInfo[1].y = c.y-1;
								fg->FgInfo[2].x = c.x+1;
								fg->FgInfo[2].y = c.y-2;
								fg->FgInfo[3].x = c.x+2;
								fg->FgInfo[3].y = c.y-2;
								fg->end.y-=1;
								fg->Height=2;
								fg->Width=3;
								
								fg->dir=4;
								break;
							case 4:
								fg->FgInfo[0].x = c.x;
								fg->FgInfo[0].y = c.y;
								fg->FgInfo[1].x = c.x+1;
								fg->FgInfo[1].y = c.y;
								fg->FgInfo[2].x = c.x;
								fg->FgInfo[2].y = c.y-1;
								fg->FgInfo[3].x = c.x;
								fg->FgInfo[3].y = c.y-2;
								fg->Height=3;
								fg->Width=2;
								fg->dir=1;
								break;
						}
						break;
					case OMINO:
						break;
					case TMINO:
						switch(fg->dir){
							case 1:
								fg->FgInfo[0].x = c.x;
								fg->FgInfo[0].y = c.y;
								fg->FgInfo[1].x = c.x+1;
								fg->FgInfo[1].y = c.y;
								fg->FgInfo[2].x = c.x+1;
								fg->FgInfo[2].y = c.y-1;
								fg->FgInfo[3].x = c.x+1;
								fg->FgInfo[3].y = c.y+1;
								fg->end.y+=1;
								fg->Height=3;
								fg->Width=2;
								fg->dir=2;
								break;
							case 2:
								fg->FgInfo[0].x = c.x;
								fg->FgInfo[0].y = c.y-1;
								fg->FgInfo[1].x = c.x+1;
								fg->FgInfo[1].y = c.y;
								fg->FgInfo[2].x = c.x+1;
								fg->FgInfo[2].y = c.y-1;
								fg->FgInfo[3].x = c.x+2;
								fg->FgInfo[3].y = c.y-1;
								fg->Height=2;
								fg->dir=3;
								fg->Width=3;
								break;
							case 3:
								fg->FgInfo[0].x = c.x+1;
								fg->FgInfo[0].y = c.y;
								fg->FgInfo[1].x = c.x+1;
								fg->FgInfo[1].y = c.y-1;
								fg->FgInfo[2].x = c.x+1;
								fg->FgInfo[2].y = c.y-2;
								fg->FgInfo[3].x = c.x+2;
								fg->FgInfo[3].y = c.y-1;
								fg->end.x+=1;
								fg->Height=3;
								fg->dir=4;
								fg->Width=2;
								break;
							case 4:
								fg->FgInfo[0].x = c.x-1;
								fg->FgInfo[0].y = c.y-1;
								fg->FgInfo[1].x = c.x;
								fg->FgInfo[1].y = c.y-1;
								fg->FgInfo[2].x = c.x+1;
								fg->FgInfo[2].y = c.y-1;
								fg->FgInfo[3].x = c.x;
								fg->FgInfo[3].y = c.y-2;
								fg->end.y-=1;
								fg->end.x-=1;
								fg->Height=2;
								fg->Width=3;
								fg->dir=1;
								break;
						}
						break;
					case SMINO:
						switch(fg->dir){
							case 1:
								fg->FgInfo[0].x = c.x;
								fg->FgInfo[0].y = c.y;
								fg->FgInfo[1].x = c.x+1;
								fg->FgInfo[1].y = c.y;
								fg->FgInfo[2].x = c.x+1;
								fg->FgInfo[2].y = c.y-1;
								fg->FgInfo[3].x = c.x+2;
								fg->FgInfo[3].y = c.y-1;
								fg->Height=2;
								fg->Width=3;
								fg->dir=2;
								break;
							case 2:								
								fg->FgInfo[0].x = c.x+1;
								fg->FgInfo[0].y = c.y;
								fg->FgInfo[1].x = c.x+1;
								fg->FgInfo[1].y = c.y-1;
								fg->FgInfo[2].x = c.x;
								fg->FgInfo[2].y = c.y-1;
								fg->FgInfo[3].x = c.x;
								fg->FgInfo[3].y = c.y-2;
								fg->Height=3;
								fg->Width=2;
								fg->dir=1;
								break;
						}
						break;
					case ZMINO:
						switch(fg->dir){
							case 1:
								fg->FgInfo[0].x = c.x;
								fg->FgInfo[0].y = c.y-1;
								fg->FgInfo[1].x = c.x+1;
								fg->FgInfo[1].y = c.y-1;
								fg->FgInfo[2].x = c.x+1;
								fg->FgInfo[2].y = c.y;
								fg->FgInfo[3].x = c.x+2;
								fg->FgInfo[3].y = c.y;
								fg->Height=2;
								fg->Width=3;
								fg->dir=2;
								break;
							case 2:
								fg->FgInfo[0].x = c.x+1;
								fg->FgInfo[0].y = c.y;
								fg->FgInfo[1].x = c.x+1;
								fg->FgInfo[1].y = c.y+1;
								fg->FgInfo[2].x = c.x+2;
								fg->FgInfo[2].y = c.y-1;
								fg->FgInfo[3].x = c.x+2;
								fg->FgInfo[3].y = c.y;
								fg->Height=3;
								fg->Width=2;
								fg->dir=1;
								break;
						}
						break;
					case IMINO:
						switch(fg->dir){
							case 1:
								if(fg->end.x==0)
									MoveToRight();					
								else if(fg->end.x>HORNUM-3){
									MoveToLeft();
									MoveToLeft();
								}
								fg->FgInfo[0].x = c.x-2;
								fg->FgInfo[0].y = c.y-1;
								fg->FgInfo[1].x = c.x-1;
								fg->FgInfo[1].y = c.y-1;
								fg->FgInfo[2].x = c.x;
								fg->FgInfo[2].y = c.y-1;
								fg->FgInfo[3].x = c.x+1;
								fg->FgInfo[3].y = c.y-1;
								fg->Height=1;
								fg->Width=4;
								fg->dir=2;
								fg->end.x-=2;
								fg->end.y-=1;
								break;
							case 2:
								
								fg->FgInfo[0].x = c.x+2;
								fg->FgInfo[0].y = c.y;
								fg->FgInfo[1].x = c.x+2;
								fg->FgInfo[1].y = c.y-1;
								fg->FgInfo[2].x = c.x+2;
								fg->FgInfo[2].y = c.y-2;
								fg->FgInfo[3].x = c.x+2;
								fg->FgInfo[3].y = c.y+1;
								fg->Height=4;
								fg->Width=1;
								fg->dir=1;
								fg->end.x+=2;
								fg->end.y+=1;
								break;
						}
						break;
					default:
						break;
				}//switch

				if(CheckDup(backup)){
					fg->dir = backup.dir;
					fg->end = backup.end;
					memcpy( fg->FgInfo , backup.FgInfo , sizeof(POINT)*FG_FIXEDNUM);
					fg->Figure = backup.Figure;
					fg->Height = backup.Height;
					fg->NextFigure= backup.NextFigure;
					fg->Width = backup.Width;
				}

			if(pDoc->Ghost){
				ME->GhostFG  = ME->FG;
				SetGhostFigure();
			}

		}//vk up

		VirtualDraw();
	}//if start

	brk:
	


	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMyView::MessageHandler(int msg){

	switch(msg){

		case SUCC_SERVEROPEN:
			MessageBox( _T("���������� �����Ͽ����ϴ�"));
			break;
		case FAIL_SERVEROPEN:
			MessageBox( _T("���������� �����Ͽ����ϴ�!"));
			break;
		case PREUSE_PORT:
			MessageBox( _T("��Ʈ�� �̹� �����ֽ��ϴ�!"));
			break;
		case SUCC_SERVERCONN:
			MessageBox( _T("���ӿ� �����Ͽ����ϴ�!"));
			break;
		case FAIL_SERVERCONN:
			MessageBox( _T("���ӿ� �����Ͽ����ϴ�!"));
			break;
		case EXCESS_ENTER:
			MessageBox( _T("���� ������ �� �̻� ���� �� �� �����ϴ�"));
			break;
		case FAIL_ACCEPT:
			MessageBox( _T("Ŭ���̾�Ʈ�� ���ӿ�û�� ���� ���߽��ϴ�"));
			break;
		case FAIL_SENDMSG:
			MessageBox( _T("�޼����� �����µ� �����Ͽ����ϴ�"));
			break;
		case DUP_ID:
			MessageBox( _T("���̵� �ߺ��˴ϴ�. ���̵� �ٲپ� �ٽ� �����ϼ���"));
			break;
		case NOT_OPENNENTER:
			MessageBox( _T("������ �������� �ʾҰų� ������ �������� �ʾҽ��ϴ�."));
			break;
		case CLOSE_SERVER:
			MessageBox( _T("������ �������ϴ�!"));
			break;
		default:
			MessageBox( _T("�� �� ���� ���� �߻�!"));



	}

}

void CMyView::ReadyBtnClicked(){

	if(!pDoc->Open && !pDoc->Enter){
		MessageHandler(NOT_OPENNENTER);
		return ;
	}



	if(pDoc->Ready){
		pDoc->Ready = false;
		send_ready.ready = false;
	}
	else{
		pDoc->Ready = true;
		send_ready.ready = true;
	}

	pDoc->m_mySocket->Sendready();

}



void CMyView::StartBtnClicked(){

	if(pDoc->End){
		pDoc->m_mySocket->SendRestart();
		return;
	}

	if(pDoc->Open == false && pDoc->Enter == false){
		MessageHandler(NOT_ALLREADY);
		return;
	}
	else{

		if(pOptionDlg->DoModal() == IDOK){
			pDoc->Server_ProceeStart();
			Btn_Ready->EnableWindow(false);
			Btn_Start->EnableWindow(false);
		}
	}
	
}

void CMyView::OnMenuServer()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(!pDoc->Enter && !pDoc->Open){
		if(pServerDlg != NULL){
			pServerDlg->ShowWindow(SW_SHOW);
		}
		else{
			pServerDlg = new ServerDialog;
			pServerDlg->Create( _DLG_SERVER);
			pServerDlg->pView = this;
			pServerDlg->pDoc = pDoc;
			pServerDlg->ShowWindow(SW_SHOW);

		}
	}
}

void CMyView::OnUpdateMenuServer(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if(!pDoc->Open && !pDoc->Enter)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}

void CMyView::SetMap(int i){

	
	if(ME==NULL){
		MessageHandler(FAIL_FINDNAME);
		return;
	}

	//�ƹ��ų� ���ý�
	if(i==5)
		i = rand()%5;

	int temp=0;

	switch(i){
		
		case 0:
			for(int i=0 ; i < HORNUM ; i++){
				for(int l=VERNUM-1 ; l >= VERNUM-1-temp ; l--){
					ME->GameBoard[l][i] = 1;
					ME->FixedBoard[l][i] = rand()%FG_KINDNUM+2;
				}
				temp +=2;
			}
			ME->GameBoard[VERNUM-1][0]=0;
			ME->FixedBoard[VERNUM-1][0]=0;
			break;
		case 1:
			for(int i=0 ; i < HORNUM/2 ; i++){
				for(int l=VERNUM-1 ; l >= VERNUM-1-temp ; l--)
					{
						ME->FixedBoard[l][(HORNUM-1)-i] = ME->FixedBoard[l][i] = rand()%FG_KINDNUM+2;
						ME->GameBoard[l][i] = ME->GameBoard[l][(HORNUM-1)-i] =1;
					}
				temp+=2;		
			}
			ME->GameBoard[VERNUM-1][0]=0;
			ME->GameBoard[VERNUM-1][HORNUM-1]=0;
			ME->FixedBoard[VERNUM-1][0]=0;
			ME->FixedBoard[VERNUM-1][HORNUM-1]=0;
			break;

		case 2:
			for(int i=0 ; i<HORNUM ; i++){
				temp = rand()%(VERNUM-10)+10;
				for(int l= temp ; l < temp+6 ; l++){
					ME->GameBoard[l][i] = 1;
					ME->FixedBoard[l][i] = rand()%FG_KINDNUM+2;
				}
			}
			break;			

		case 3:{
			temp=7;
			int i,l=0;
			while(temp>=0){
				int i=temp;
				int l=VERNUM-1;

				for( ; l>=0 && i<HORNUM ; l--, i++){
					ME->GameBoard[l][i]=1;
					ME->FixedBoard[l][i] = rand()%FG_KINDNUM+2;
				}

				temp-=3;
			}

			i=0;
			l=22;
			for( ; l>=0 && i<HORNUM ; l--, i++){
				ME->GameBoard[l][i]=1;
				ME->FixedBoard[l][i] = rand()%FG_KINDNUM+2;
			}

			i=0;
			l=19;
			for( ; l>=0 && i<HORNUM ; l--, i++){
				ME->GameBoard[l][i]=1;
				ME->FixedBoard[l][i] = rand()%FG_KINDNUM+2;
			}
			break;
		 }
		case 4:
			for(int i=0 ; i<HORNUM ; i++){
				for(int l=10 ; l < VERNUM ; l++){
					if(rand()%2){
						ME->GameBoard[l][i] = 1;
						ME->FixedBoard[l][i] = rand()%FG_KINDNUM+2;
					}
				}
			}
			break;

		case 6:
			for(int i=0 ; i < HORNUM ; i++)
				for(int l=VERNUM-1 ; l > VERNUM-5 ; l--){
					ME->GameBoard[l][i] = 1;
					ME->FixedBoard[l][i] = rand()%FG_KINDNUM+2;
				}

				ME->GameBoard[24][1] = 0;
				ME->FixedBoard[24][1] = 0;
				ME->GameBoard[23][0] = 0;
				ME->FixedBoard[23][0] = 0;
				ME->GameBoard[22][7] = 0;
				ME->FixedBoard[22][7] = 0;
				ME->GameBoard[24][9] = 0;
				ME->FixedBoard[24][9] = 0;
				ME->GameBoard[24][9] = 0;
				ME->FixedBoard[24][9] = 0;
				ME->GameBoard[21][7] = 0;
				ME->FixedBoard[21][7] = 0;
				ME->GameBoard[20][7] = 0;
				ME->FixedBoard[20][7] = 0;
			break;

		default:
			break;
	}

	ME->GameBoard[24][0] = 0;
	ME->FixedBoard[24][0] = 0;
}

//���� �� ������ ���� �ٸ� �������� �������� �ڽ��� ���� �����ϰ� �׷�����.
void CMyView::ProcessMapState(CMyDoc::ON_MAPSTATE *map){

	TUser *user= NULL;
	CString name( map->name , map->namelen);
	if( name != pDoc->Name){
		user = pDoc->Client_NameToTUser(name);
		memcpy(user->StateBoard, map->board, sizeof(map->board));
		memcpy(user->FG.FgInfo , map->figure , sizeof(POINT)*FG_FIXEDNUM);
		user->FG.Figure = map->kindfigure;
	}

}

bool CMyView::CreateFigure(void){
	
	if(ME == NULL)
		return false;

	for(int i=0 ; i < 4 ; i++)
		for(int l=0 ; l<2 ; l++)
			ME->NextFigureBoard[i][l]=0;


	ME->FG.Figure = ME->FG.NextFigure;
	
	//�� ó�� ���������� ����.
	if(ME->FG.NextFigure == -1)
		switch(rand()%FG_KINDNUM+2){

			case LMINO:
				ME->FG.Figure = LMINO;
				break;
			case JMINO:
				ME->FG.Figure = JMINO;
				break;
			case OMINO:
				ME->FG.Figure = OMINO;
				break;
			case TMINO:
				ME->FG.Figure = TMINO;
				break;
			case SMINO:
				ME->FG.Figure = SMINO;
				break;
			case ZMINO:
				ME->FG.Figure = ZMINO;
				break;
			case IMINO:
				ME->FG.Figure = IMINO;
				break;
			default:
				ME->FG.Figure = TMINO;
				break;
		}

	switch(rand()%FG_KINDNUM+2){

			case LMINO:
				ME->FG.NextFigure = LMINO;
				ME->NextFigureBoard[3][0]=1;
				ME->NextFigureBoard[3][1]=1;
				ME->NextFigureBoard[2][1]=1;
				ME->NextFigureBoard[1][1]=1;
				break;
			case JMINO:
				ME->FG.NextFigure = JMINO;
				ME->NextFigureBoard[3][0]=1;
				ME->NextFigureBoard[3][1]=1;
				ME->NextFigureBoard[2][0]=1;
				ME->NextFigureBoard[1][0]=1;
				break;
			case OMINO:
				ME->FG.NextFigure = OMINO;
				ME->NextFigureBoard[3][0]=1;
				ME->NextFigureBoard[3][1]=1;
				ME->NextFigureBoard[2][1]=1;
				ME->NextFigureBoard[2][0]=1;
				break;
			case TMINO:
				ME->FG.NextFigure = TMINO;
				ME->NextFigureBoard[3][0]=1;
				ME->NextFigureBoard[2][0]=1;
				ME->NextFigureBoard[1][0]=1;
				ME->NextFigureBoard[2][1]=1;
				break;
			case SMINO:
				ME->FG.NextFigure = SMINO;
				ME->NextFigureBoard[1][0]=1;
				ME->NextFigureBoard[2][0]=1;
				ME->NextFigureBoard[2][1]=1;
				ME->NextFigureBoard[3][1]=1;
				break;
			case ZMINO:
				ME->FG.NextFigure = ZMINO;
				ME->NextFigureBoard[3][0]=1;
				ME->NextFigureBoard[2][0]=1;
				ME->NextFigureBoard[2][1]=1;
				ME->NextFigureBoard[1][1]=1;
				break;
			case IMINO:
				ME->FG.NextFigure = IMINO;
				ME->NextFigureBoard[3][1]=1;
				ME->NextFigureBoard[2][1]=1;
				ME->NextFigureBoard[1][1]=1;
				ME->NextFigureBoard[0][1]=1;
				break;
			default:
				ME->FG.NextFigure = TMINO;
				ME->NextFigureBoard[3][0]=1;
				ME->NextFigureBoard[2][0]=1;
				ME->NextFigureBoard[1][0]=1;
				ME->NextFigureBoard[2][1]=1;
				break;
		}


	switch(ME->FG.Figure){

		case LMINO:
			ME->FG.FgInfo[0].y=0;
			ME->FG.FgInfo[0].x=4;
			ME->FG.FgInfo[1].y=1;
			ME->FG.FgInfo[1].x=4;
			ME->FG.FgInfo[2].y=2;
			ME->FG.FgInfo[2].x=4;
			ME->FG.FgInfo[3].y=2;
			ME->FG.FgInfo[3].x=5;
			ME->FG.end.x=4;
			ME->FG.end.y=2;
			ME->FG.Height=3;
			ME->FG.dir = 1;
			ME->FG.Width=2;	
			break;
		case JMINO:
			ME->FG.FgInfo[0].y=0;
			ME->FG.FgInfo[0].x=5;
			ME->FG.FgInfo[1].y=1;
			ME->FG.FgInfo[1].x=5;
			ME->FG.FgInfo[2].y=2;
			ME->FG.FgInfo[2].x=5;
			ME->FG.FgInfo[3].y=2;
			ME->FG.FgInfo[3].x=4;
			ME->FG.end.x=4;
			ME->FG.end.y=2;
			ME->FG.Height=3;
			ME->FG.dir = 2;
			ME->FG.Width =2 ;
			break;
		case OMINO:
			ME->FG.FgInfo[0].y=0;
			ME->FG.FgInfo[0].x=4;
			ME->FG.FgInfo[1].y=0;
			ME->FG.FgInfo[1].x=5;
			ME->FG.FgInfo[2].y=1;
			ME->FG.FgInfo[2].x=4;
			ME->FG.FgInfo[3].y=1;
			ME->FG.FgInfo[3].x=5;
			ME->FG.end.x=4;
			ME->FG.end.y=1;
			ME->FG.Height=2;
			ME->FG.dir = 0;
			ME->FG.Width=2;
			break;
		case ZMINO:
			ME->FG.FgInfo[0].y=0;
			ME->FG.FgInfo[0].x=5;
			ME->FG.FgInfo[1].y=1;
			ME->FG.FgInfo[1].x=4;
			ME->FG.FgInfo[2].y=1;
			ME->FG.FgInfo[2].x=5;
			ME->FG.FgInfo[3].y=2;
			ME->FG.FgInfo[3].x=4;
			ME->FG.end.x=4;
			ME->FG.end.y=2;
			ME->FG.dir = 1;
			ME->FG.Width=2;
			ME->FG.Height = 3;
			break;
		case SMINO:		
			ME->FG.FgInfo[0].y=0;
			ME->FG.FgInfo[0].x=4;
			ME->FG.FgInfo[1].y=1;
			ME->FG.FgInfo[1].x=5;
			ME->FG.FgInfo[2].y=1;
			ME->FG.FgInfo[2].x=4;
			ME->FG.FgInfo[3].y=2;
			ME->FG.FgInfo[3].x=5;
			ME->FG.end.x=4;
			ME->FG.end.y=2;
			ME->FG.dir = 1;
			ME->FG.Width=2;
			ME->FG.Height = 3;
			break;
		case IMINO:
			ME->FG.FgInfo[0].y=0;
			ME->FG.FgInfo[0].x=5;
			ME->FG.FgInfo[1].y=1;
			ME->FG.FgInfo[1].x=5;
			ME->FG.FgInfo[2].y=2;
			ME->FG.FgInfo[2].x=5;
			ME->FG.FgInfo[3].y=3;
			ME->FG.FgInfo[3].x=5;
			ME->FG.end.x=5;
			ME->FG.end.y=3;
			ME->FG.dir=1;
			ME->FG.Width=1;
			ME->FG.Height = 4;
			break;
		case TMINO:
			ME->FG.FgInfo[0].y=0;
			ME->FG.FgInfo[0].x=4;
			ME->FG.FgInfo[1].y=1;
			ME->FG.FgInfo[1].x=3;
			ME->FG.FgInfo[2].y=1;
			ME->FG.FgInfo[2].x=4;
			ME->FG.FgInfo[3].y=1;
			ME->FG.FgInfo[3].x=5;
			ME->FG.end.x=3;
			ME->FG.end.y=1;
			ME->FG.dir=1;
			ME->FG.Width=3;
			ME->FG.Height = 2;
			break;
		default:
			ME->FG.FgInfo[0].y=0;
			ME->FG.FgInfo[0].x=4;
			ME->FG.FgInfo[1].y=1;
			ME->FG.FgInfo[1].x=3;
			ME->FG.FgInfo[2].y=1;
			ME->FG.FgInfo[2].x=4;
			ME->FG.FgInfo[3].y=1;
			ME->FG.FgInfo[3].x=5;
			ME->FG.end.x=3;
			ME->FG.end.y=1;
			ME->FG.dir=1;
			ME->FG.Width=3;
			ME->FG.Height = 2;
	}
	
	//������ ������ �̹� ������ ������ ��ģ�ٸ� ���� ��
	POINT c;
	for(int i=0 ; i < FG_FIXEDNUM ; i++){
		c = ME->FG.FgInfo[i];

		if( ME->GameBoard[ c.y][c.x] !=0){
			SetGameover();
			return 0;
		}
	}

	if(pDoc->Ghost){
		ME->GhostFG  = ME->FG;
		SetGhostFigure();
	}

	return 0;
}

void CMyView::SetFigure()
{

	TUser::FIGURE *fg = &(ME->FG);
	POINT c;

	for(int i=0 ; i < FG_FIXEDNUM ; i++){
		c = ME->FG.FgInfo[i];
		ME->GameBoard[ c.y ][ c.x ] = 1;
		ME->FixedBoard[ c.y ][ c.x ] = fg->Figure;
	}

	CheckLineDestroy();

}

void CMyView::SetGhostFigure()
{

	TUser::FIGURE *fg = &(ME->GhostFG);
	POINT c;

	int l=0;
	while(fg->end.y < VERNUM ){
		for(l=0 ; l < FG_FIXEDNUM ; l++){
			c = fg->FgInfo[l];
			//�ٴ��̳� ������ ����
			if(c.y == VERNUM-1 || ME->GameBoard[ c.y+1 ][ c.x ] == 1){
				break;
			}
		}
		if(l!=FG_FIXEDNUM)
			break;

		MoveToGhostDown();
	}
}

//�������� �������� �뺸
void CMyView::SetGameover(){

	ME->SetSurvive(false);
	pDoc->End=true;
	pDoc->Start=false;
	KillTimer(TIMER_TETRIS);
	KillTimer(TIMER_SENDMAPSTATE);
	pDoc->m_mySocket->SendDead();

}

bool CMyView::CheckLineDestroy(){

	int Bingo=0;
	static int Combo=0;
	int LineNum=0;
	int final_line=0;
	int final_ver=0;
	bool des=false;

	for(int i=0 ; i< VERNUM ; i++){

		for(int l=0 ; l< HORNUM ; l++)
			if(ME->GameBoard[i][l]==1)
				Bingo++;

		//������ ���� �߰ߵǸ� ���������� ����� �Ʒ��� ����´�
		if(Bingo == HORNUM)
		{
			des = true;
			final_line=i;
			for (int m = i - 1; m > 0; m--)
			{
				for (int n = 0; n < HORNUM; n++) 
				{
					ME->GameBoard[m + 1][n] = ME->GameBoard[m][n];
					ME->FixedBoard[m + 1][n] = ME->FixedBoard[m][n];
					ME->GameBoard[m][n] = 0;
					ME->FixedBoard[m][n] = 0;
				}
			}
		}
		Bingo=0;
	}

	if(des){
		Combo++;
		//���������� ������ ���� �Ʒ��� ��� �ִٸ� �ش� ���� �������� �Ʒ��� ������.
		for(int i=0 ; i < HORNUM ; i++){
			if(ME->FixedBoard[final_line+1][i] != 1){
				//�� ���� ����� �˻�
				for(int l=final_line+1 ; l < VERNUM ; l++)
					if(ME->FixedBoard[l][i] == 1){
						final_ver=l;
						break;
					}
			}

			for(int l=final_line ; l < final_ver ; l++){
				ME->FixedBoard[l+1][i] = ME->FixedBoard[l][i];
				ME->FixedBoard[l][i] = 0;
				ME->GameBoard[l+1][i] = ME->GameBoard[l][i];
				ME->GameBoard[l][i] = 0;
				//cs
			}
		}
	}
	else
		Combo=0;


	if(Combo>=COMBONUM && des){
		pDoc->m_mySocket->SendLine(ADDCOMBOLINE, false);

	}

	return true;
}

//�̹� ������ ����(fixed board)�� ��ġ���� ����
bool CMyView::CheckDup(TUser::FIGURE backup){

	POINT c;

	//���� ����ü�� ���� �� ������ ���� ���ش�
	switch(backup.Figure){

		case LMINO:
			if(backup.dir==1 && backup.end.x==0){
				MoveToRight();
				return false;
			}
			else if(backup.dir==3 && backup.end.x + 1== HORNUM-1){
				MoveToLeft();
				return false;
			}
			break;
		case JMINO:
			if(backup.dir==2 && backup.end.x==0){
				MoveToRight();
				return false;
			}
			else if(backup.dir==4 && backup.end.x +1 == HORNUM-1){
				MoveToLeft();
				return false;
			}
			break;
		case TMINO:
			if(backup.dir ==2 && backup.end.x+1 == HORNUM-1){
				MoveToLeft();
				return false;
			}
			else if(backup.dir == 4 && backup.end.x == 0){
				MoveToRight();
				return false;
			}
			break;
		case IMINO:
			if(backup.dir == 1 && backup.end.x == 0){
				MoveToRight();
				MoveToRight();
				return false;
			}
			else if(backup.dir ==1 && backup.end.x == HORNUM-1){
				MoveToLeft();
				return false;
			}
			break;

	}

	
	for(int i=0 ; i < FG_FIXEDNUM ; i ++){
		c = ME->FG.FgInfo[i];
		//���� ������ ��ġ���� �˻�
		if( ME->GameBoard[ c.y ][ c.x ] == 1)
			return true;
		//������ �������� �˻�
		if(c.x < 0 || c.x >= HORNUM)
			return true;
	}


	return false;
}

void CMyView::MoveToDown(){

	if(ME == NULL)
		return;

	TUser::FIGURE *fg = &(ME->FG);
	

	for(int i=0 ; i < FG_FIXEDNUM ; i++)
		fg->FgInfo[i].y+=1;
	

	fg->end.y+=1;
}

void CMyView::MoveToGhostDown(){

	if(ME == NULL)
		return;

	TUser::FIGURE *fg = &(ME->GhostFG);
	

	for(int i=0 ; i < FG_FIXEDNUM ; i++)
		fg->FgInfo[i].y+=1;
	

	fg->end.y+=1;
}


void CMyView::MoveToRight(){

	if(ME == NULL)
		return;

	for(int i=0 ; i < FG_FIXEDNUM ; i++)
		ME->FG.FgInfo[i].x+=1;

	ME->FG.end.x+=1;

}

void CMyView::MoveToLeft(){
	
	
	if(ME == NULL)
		return;

	for(int i=0 ; i < FG_FIXEDNUM ; i++)
		ME->FG.FgInfo[i].x-=1;

	ME->FG.end.x-=1;
}

void CMyView::AddLine(int num){

	////������ ������ �̹� �־��ٸ� ���� ��.
	//for(int l=0 ; l <num ; l++){
	//	for(int i=0 ; i < HORNUM ; i++)
	//		if(ME->GameBoard[l][i] == 1){
	//			SetGameover();
	//			return;
	//		}
	//}

	for(int i=0 ; i<VERNUM-num ; i++){
		for(int l=0 ; l<HORNUM ; l++){
			ME->GameBoard[i][l] =ME-> GameBoard[i+1][l];
			ME->FixedBoard[i][l] = ME->FixedBoard[i+1][l];
		}
	}

	for(int i=VERNUM-num ; i <25 ; i++){
		for(int l=0 ; l < HORNUM ; l++){
			if(rand()%3){
				ME->GameBoard[i][l] = 1;
				ME->FixedBoard[i][l] = rand()%FG_KINDNUM+2;		
			}
			else{
				ME->GameBoard[i][l] = 0;
				ME->FixedBoard[i][l] =0;		
			}
		}
		
	}

	if(pDoc->Ghost){
		ME->GhostFG  = ME->FG;
		SetGhostFigure();
	}

	VirtualDraw();
}

void CMyView::OnBgm()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(pDoc->Bgm){
		PlaySound(NULL, AfxGetInstanceHandle(),  NULL);
	}
	else{
		int bgm = rand()%BGM_NUM;
		switch(bgm){

			case 0:
				
				PlaySound( MAKEINTERSOURCE(_LOGINSKA), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
				break;
			case 1:

				PlaySound( MAKEINTERSOURCE(_BRADINSKY), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
				break;
			case 2:

				PlaySound( MAKEINTERSOURCE(_BRADINSKY), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
				break;
			case 3:

				PlaySound( MAKEINTERSOURCE(_TROIKA), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
				break;
			case 4:

				PlaySound( MAKEINTERSOURCE(_KALINKA), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
				break;
		}
	
	}

	pDoc->Bgm = !pDoc->Bgm;
}

void CMyView::OnUpdateBgm(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if(pDoc->Bgm){
		pCmdUI->SetText(_T("����"));
	}
	else
		pCmdUI->SetText(_T("����ϱ�"));
}


void CMyView::On32800()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	StartBtnClicked();

}


BOOL CMyView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.



	return CView::PreTranslateMessage(pMsg);
}
