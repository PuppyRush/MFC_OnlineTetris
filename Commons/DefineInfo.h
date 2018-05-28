
#define CSTRTCH (LPSTR)(LPCTSTR) 

typedef enum USER_MSG
{

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

typedef enum CLIENT_MSG
{
	//Ŭ���̾�Ʈ�� ���� �޼���
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


typedef enum SERVER_MSG
{
	//������ ���� �޼���
	ON_NAME=300,
	ON_MESSAGE,
	PER_READY,
	BC_MAPSTATES,		//BROADCAST
	BC_MAPSTATE,
	BC_DEAD,
	BC_ADDLINE,
	BC_RESTART
};

typedef enum MAP
{
	STAIRWAY =0,
	PYRAMID,
	RAIN,
	LINE,
	RANDOMFIG,
	RANDOMSEL,
	
};

typedef enum TETRIS_FIGURE
{
	 JMINO=2,	
	 LMINO,
	 OMINO,
	 TMINO,	
	 SMINO,
	 ZMINO,
	 IMINO,
	 GMINO,
};

typedef enum ETC
{
	TOLEFT=0,
	TORIGHT
};

////////////////////////////////////////////////////////////////////////////////
//��������
#define WIN_WIDTH			1250	//������ ȭ�� ũ��
#define	WIN_HEIGHT			1000
#define MAIN_WIDTH			250		//������Ʈ���� ȭ�� ũ��
#define MAIN_HEIGHT			625
#define	SUB_WIDTH			160
#define	SUB_HEIGHT			400
#define	CHAT_WIDTH			250
#define	CHAT_HEIGHT			400
#define INPUT_WIDTH			250
#define INPUT_HEIGHT		30
#define	GAME_SPACE			50		//����ȭ�� �� ����
#define ENTERLIST_WIDTH		250		//����Ʈ ����
#define ENTERLIST_HEIGHT	150
#define BTN_WIDTH		200
#define BTN_HEIGHT		50
#define MAIN_SIZE		25			//������Ʈ���� ����ũ��	
#define SUB_SIZE		16			//������Ʈ���� ����ũ��(�ٸ������)

//��ġ ����
#define	SX_MAIN	30
#define	SY_MAIN	30

//ũ��, ��������	
#define MAX_ENTER		6
#define ID_LEN			12
#define HEADER_NUM		2
#define MSG_LEN			1024
#define FG_KINDNUM		7		//������ ������ 7��
#define FG_FIXEDNUM		4		//��� ������ ���������� 4��
#define BGM_NUM			5
#define ADDCOMBOLINE	1		//�޺��϶� ���濡�� �߰��� ����
#define COMBONUM		3		//�޺��� �ּ� �� ��

#define VERNUM	25				//��Ʈ��������â�� ������
#define HORNUM	10

//��Ÿ����
#define PORTNUM	7000
#define TIMER_TETRIS		1
#define	TIMER_SENDMAPSTATE	2
#define SENDTIME			50		//timer
#define TIMER_NEXTLEVEL		3




