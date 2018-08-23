#pragma once

#include <memory>
#include <string>

#include "TSocket.h"
#include "TType.h"
#include "TAtomic.h"
#include "TObject.h"
#include "TSwitchingMessage.h"
#include "structs.h"
#include "TObjectContainer.h"

class TetrisUser : public TObject, public TMessenger
{
public:
	int GameBoard[25][10], FixedBoard[25][10], NextFigureBoard[4][2];
	int StateBoard[25][10];
	FIGURE FG;
	FIGURE GhostFG;

	virtual ~TetrisUser() {}

	inline bool operator< (const TetrisUser &user)
	{
		return this->m_order < user.getOrder();
	}

	virtual const bool operator!=(const TetrisUser &user) const
	{
		return m_unique != user.getUnique();
	}

	inline const std::string getUserName() const noexcept  { return m_name; }
	inline const bool getReady() const noexcept  { return m_isReady; }
	inline const int getOrder() const noexcept { return m_order; }
	inline const bool getSurvive() const noexcept { return m_isSurvive; }
	inline const tetris::t_userUnique getUnique() const noexcept { return m_unique; }

	inline void setSurvive(const bool n) noexcept { m_isSurvive = n; }
	inline void setOrder(const int idx) noexcept { m_order = idx; }
	inline void setName(const std::string name) { m_name = name; } 
	inline void setReady(const bool rdy) noexcept { m_isReady = rdy; }

	inline static const tetris::t_userUnique newUnique() noexcept
	{
		static TAtomic<tetris::t_userUnique> m_unique;
		return m_unique.newUnique();
	}

protected:
	explicit TetrisUser(const tetris::t_userUnique unique);
	TetrisUser();

private:
	tetris::t_userUnique m_unique;
	int m_order;
	std::string m_name;
	IPString m_ip;
	bool m_isReady;
	bool m_isSurvive;
};
