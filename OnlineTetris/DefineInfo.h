
enum USER_MSG{

	SUCC_SERVEROPEN=0,
	FAIL_SERVEROPEN,
	PREUSE_PORT,
	SUCC_SERVERCONN,
	FAIL_SERVERCONN,
	EXCESS_ENTER,
	FAIL_ACCEPT,
	NOT_READY,
	FAIL_SENDMSG,
	FAIL_FINDNAME,
	DUP_ID,
	NOT_OPENNENTER,
	NOT_ALLREADY,
	CLOSE_SERVER
};

enum CLIENT_MSG{
	//클라이언트가 받을 메세지
	PER_NAME=100,
	SEND_MESSAGE,
	ADD_USERS,
	ON_READY,
	EXIT_USER,
	FAIL_ENTER,
	START_SIGNAL,
	END_SIGNAL,
	RESTART_SIGNAL,
	ON_MAPSTATES,
	ON_MAPSTATE,
	ON_ADDLINE

};


enum SERVER_MSG{
	//서버가 받을 메세지
	ON_NAME=300,
	ON_MESSAGE,
	PER_READY,
	BC_MAPSTATES,		//BROADCAST
	BC_MAPSTATE,
	BC_DEAD,
	BC_ADDLINE,
	BC_RESTART
};

enum MAP{
	STAIRWAY =0,
	PYRAMID,
	RAIN,
	LINE,
	RANDOMFIG,
	RANDOMSEL,
	
};

enum TETRIS_FIGURE{
	 JMINO=2,	
	 LMINO,
	 OMINO,
	 TMINO,	
	 SMINO,
	 ZMINO,
	 IMINO,
	 GMINO,
};

enum ETC{
	TOLEFT=0,
	TORIGHT
};

////////////////////////////////////////////////////////////////////////////////
//길이정의
#define WIN_WIDTH			1250	//윈도우 화면 크기
#define	WIN_HEIGHT			1000
#define MAIN_WIDTH			250		//메인테트리스 화면 크기
#define MAIN_HEIGHT			625
#define	SUB_WIDTH			160
#define	SUB_HEIGHT			400
#define	CHAT_WIDTH			250
#define	CHAT_HEIGHT			400
#define INPUT_WIDTH			250
#define INPUT_HEIGHT		30
#define	GAME_SPACE			50		//게임화면 간 간격
#define ENTERLIST_WIDTH		250		//리스트 길이
#define ENTERLIST_HEIGHT	150
#define BTN_WIDTH		200
#define BTN_HEIGHT		50
#define MAIN_SIZE		25			//메인테트리스 조각크기	
#define SUB_SIZE		16			//서브테트리스 조각크기(다른사람꺼)

//위치 정의
#define	SX_MAIN	30
#define	SY_MAIN	30

//크기, 갯수정의	
#define MAX_ENTER		6
#define ID_LEN			12
#define HEADER_NUM		3
#define MSG_LEN			1024
#define FG_KINDNUM		7		//도형의 종류는 7개
#define FG_FIXEDNUM		4		//모든 종류의 도형갯수는 4개
#define BGM_NUM			5
#define ADDCOMBOLINE	1		//콤보일때 상대방에게 추가될 라인
#define COMBONUM		3		//콤보의 최소 줄 수

#define VERNUM	25				//테트리스게임창의 열갯수
#define HORNUM	10

//기타정의
#define PORTNUM	7000
#define TIMER_TETRIS		1
#define	TIMER_SENDMAPSTATE	2
#define SENDTIME			50		//timer
#define TIMER_NEXTLEVEL		3


//소리
#pragma comment(lib, "winmm")
#include <MMSystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



#define MAKEINTERSOURCE(i)(LPWSTR)((DWORD)((WORD)(i)))