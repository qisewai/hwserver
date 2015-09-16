#pragma once

#include <iostream>
#include <string>


class Screen {

public:
	typedef std::string::size_type pos;

	Screen(pos w, pos h, char c) :
		width(w),
		height(h),
		contents(w * h, c) {}
	char get() const
	{
		return contents[cursor];
	}
	inline char get(pos w, pos h) const;
	inline Screen &set(pos left, pos top, char c);
	inline Screen &set(char c);

	Screen &display(std::ostream &os)
	{
		do_display(os);
		return *this;
	}

	const Screen &display(std::ostream &os) const
	{
		do_display(os);
		return *this;
	}


	Screen &move(pos w, pos h);


private:

	pos cursor = 0;
	pos height = 0, width = 0;
	std::string contents;

	void do_display(std::ostream &os) const {os << contents;}

};



inline Screen &Screen::move(pos left, pos top)
{
	cursor = left * top + left;

	return *this;
}


Screen &Screen::set(pos left, pos top, char c)
{
	contents[left * top + left] = c;
	return *this;
}

Screen &Screen::set(char c)
{
	contents[cursor] = c;

	return *this;
}




