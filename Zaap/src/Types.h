#pragma once

#include <string>
#include <memory>
#include "system/za_ptr.h"

typedef std::string String;
// <Type>
//      za_ptr
//
// <Descritpion>
//      This is a link to "std::shared_ptr". I use a link because I
//      may try to implement my own smart_prt at some point and to be honest
//      I just think that za_ptr sounds better ;P.
template<typename T>
using za_ptr_ = zaap::ZAPtrWrapper<T>;

template<typename T>
using za_ptr = std::shared_ptr<T>;

typedef unsigned int        uint;
typedef unsigned char       byte;

typedef signed char         int8;
typedef signed short        int16;
typedef signed int          int32;
typedef signed __int64      int64;

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned __int64    uint64;