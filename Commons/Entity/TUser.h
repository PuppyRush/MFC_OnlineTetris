#pragma once

#include <memory>
#include <string>

#include "TChat.h"
#include "TSocket.h"
#include "TObject.h"
#include "../TProperty.h"
#include "../structs.h"

class TetrisUser : public TObject
{
public:

	enum class property
	{
		Min = 5,
		Max = 10
	};

	int GameBoard[25][10], FixedBoard[25][10], NextFigureBoard[4][2];
	int StateBoard[25][10];
	FIGURE FG;
	FIGURE GhostFG;

	virtual ~TetrisUser() {}

	inline bool operator< (const TetrisUser &user)
	{
		return this->m_order < user.getOrder();
	}

	inline const std::string getUserName() const noexcept  { return m_name; }
	inline const bool getReady() const noexcept  { return m_isReady; }
	inline const int getOrder() const noexcept { return m_order; }
	inline const bool getSurvive() const noexcept { return m_isSurvive; }

	inline void setSurvive(const bool n) noexcept { m_isSurvive = n; }
	inline void setOrder(const int idx) noexcept { m_order = idx; }
	inline void setName(const std::string name) { m_name = name; }
	inline void setReady(const bool rdy) noexcept { m_isReady = rdy; }

	void removeFilter(const tetris::t_unique);
	void addFilter(const tetris::t_unique);
	void add(const std::string str);
	void addWhisper(const std::string str);
	void clear();

protected:
	TetrisUser();

private:
	int m_order;
	std::string m_name;
	IPString m_ip;
	bool m_isReady;
	bool m_isSurvive;
	std::shared_ptr<TChat> m_chat;

	
};
