#pragma once

#include <queue>
#include "../Commons/TMessageObject.h"

// CMyEdit

class CChatEdit : public CEdit
{
	DECLARE_DYNAMIC(CChatEdit)

public:
	CChatEdit();
	virtual ~CChatEdit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	inline void setChatType(const TChat::property_chat chatType) {	m_chatType = chatType;	}
	inline void setWhispee(const tetris::t_unique unique) {	m_whispee = unique;	}

	CString GetEditText();
	void sendChatMessage();

protected:
	DECLARE_MESSAGE_MAP()

private:
	tetris::t_unique m_whispee;
	TChat::property_chat m_chatType;
	std::queue<pair<const char*, size_t>> m_messageQ;
};



