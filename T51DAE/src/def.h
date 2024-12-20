/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : def.h
 * PURPOSE     : Animation project.
 *               Common declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __def_h_
#define __def_h_

/* Debug memory allocation support */
// #ifdef _DEBUG
// #  define _CRTDBG_MAP_ALLOC
// #  include <crtdbg.h>
// #  define SetDbgMemHooks() \
//   _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF |  _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
// static struct __Dummy
// {
//   /* Structure constructor */
//   __Dummy( void )
//   {
//     SetDbgMemHooks();
//   } /* End of '__Dummy' constructor */
// } __oops;
// #endif /* _DEBUG */
// 
// #ifdef _DEBUG
// #  ifdef _CRTDBG_MAP_ALLOC
// #    define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
// #  endif /* _CRTDBG_MAP_ALLOC */
// #endif /* _DEBUG */


#include <map>
#include <vector>
#include <iostream>
#include <iterator>
#include <fstream>
#include <functional>
#include <thread>
#include <mutex>

#include "mth/mth.h"

/* 64 bit integer data type */
typedef long long INT64;
typedef unsigned long long UINT64;

/* Project namespace */
namespace tigl 
{
  /* Math types definitions */
  typedef mth::vec2<FLT> vec2;   
  typedef mth::vec3<FLT> vec3;
  typedef mth::vec4<FLT> vec4;
  typedef mth::matr<FLT> matr;
  typedef mth::camera<FLT> camera;
} /* end of 'tigl' namespace */

/* Stock representation type */
template<typename T>
  class stock : public std::vector<T>
  {
  public:
    stock & operator<<( const T &X )
    {
      this->push_back(X);
      return *this;
    }
    template<class WalkType>
      void Walk( WalkType Walk )
      {
        for (auto &x : *this)
          Walk(x);
      }
  }; /* End of 'stock' class */

#endif /* __def_h_ */

/* END OF 'def.h' FILE */

