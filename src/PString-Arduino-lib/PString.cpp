/*
  PString.cpp - Lightweight printable string class
  Copyright (c) 2009-2012 Mikal Hart.  All right reserved.
  Copyright (c) 2020 Abhijit Bose (@boseji) 
      - v3.0.1 - Modifications to advance Hex printing functions

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "PString.h"

void PString::begin()
{
  _cur = _buf;
  if (_size > 0)
    _buf[0] = '\0';
}

#if defined(ARDUINO) && ARDUINO >= 100
size_t PString::write(uint8_t b)
#else
void PString::write(uint8_t b)
#endif
{
  if (_cur + 1 < _buf + _size)
  {
    *_cur++ = (char)b;
    *_cur = '\0';
#if defined(ARDUINO) && ARDUINO >= 100
		return 1;
#endif
	}

#if defined(ARDUINO) && ARDUINO >= 100
	return 0;
#endif
}

int PString::format(char *str, ...) 
{ 
  va_list argptr;  
  va_start(argptr, str); 
  int ret = vsnprintf(_cur, _size - (_cur - _buf), str, argptr);
  if (_size)
     while (*_cur) 
        ++_cur;
  return ret;
}

void PString::printHexByte(uint8_t data) {
    static const char map[]={"0123456789ABCDEF"};
    print(map[(uint8_t)((data&0xF0)>>4)]);
    print(map[(uint8_t)(data&0x0F)]);
}

void PString::printHexBuffer(char* buf, size_t size) {
  for(size_t i = 0; i < size ; i++) {
    printHexByte((uint8_t)buf[i]);
  }
}

void PString::printHexBufferArr(char* buf, size_t size) {
  for(size_t i = 0; i < size ; i++) {
    print(F(" 0x"));
    printHexByte((uint8_t)buf[i]);
    print(',');
  }
}
