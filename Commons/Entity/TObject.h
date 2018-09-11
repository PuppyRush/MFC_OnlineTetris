#pragma once

#include <memory>
#include <functional>
#include <unordered_map>
#include <queue>

#include "../TAtomic.h"
#include "../TType.h"
#include "../TMessageObject.h"
#include "../DefineInfo.h"


class TObject
{
public:
	virtual ~TObject() {}

	void send(const TMessageObject& msg);

	inline const bool operator==(const TObject& object) const noexcept
	{	return this->getUnique() == object.getUnique();}

	inline const bool operator!=(const TObject& object) const noexcept
	{	return this->getUnique() != object.getUnique();}

	inline const tetris::t_unique getUnique() const noexcept
	{ return m_unique;	}


protected:
	TObject();

	std::unordered_map<tetris::t_msgidx, std::function<void(const TMessageObject&)>> m_messageCaller;

	void updateUnique(const SERVER_MSG msgtype, const tetris::t_unique unique);
	virtual void registryMessage() = 0;
	bool isRegsiteMessage(const tetris::t_msgidx msgidx);
	void addCaller(const std::pair<tetris::t_msgidx, std::function<void(const TMessageObject&)>> key_value);

private:
	tetris::t_unique m_unique;

	const void _switchingMessage(const tetris::t_msgidx, const TMessageObject& msg);
};