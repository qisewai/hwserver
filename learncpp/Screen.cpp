#include "stdafx.h"
#include "Screen.h"


char Screen::get(pos left, pos top) const
{
	return contents[left * top + left];
}











