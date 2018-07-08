#pragma once

class Uncopyable
{
protected:
	Uncopyable() {}
	virtual ~Uncopyable() {}
private:
	Uncopyable & operator=(const Uncopyable&) = delete;
	Uncopyable& operator=(const Uncopyable&&) = delete;
	Uncopyable& operator=(const Uncopyable) = delete;
	Uncopyable& operator=(const Uncopyable*) = delete;
	Uncopyable(const Uncopyable*) = delete;
	Uncopyable(const Uncopyable&) = delete;
	Uncopyable(const Uncopyable&&) = delete;
};