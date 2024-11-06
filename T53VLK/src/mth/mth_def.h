/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_def.h
 * PURPOSE     : Animation project.
 *               3D math declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_def_h_
#define __mth_def_h_

#ifndef WIN32
#define WIN32
#include <commondf.h>
#undef WIN32
#else
#include <commondf.h>
#endif
#define BOOL bool

#pragma warning(disable : 4244 4996 4049 4217 6031)

#include <cmath>

/* Value of mathematical constants */
#define PI 3.14159265358979323846
#define EX 2.71828182845904523536
#define FI 1.61803398874989484820 

/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

/* Radians to degrees conversion */
#define R2D(A) (((A) * 180.0) / PI)
#define Redian2Degree(a) R2D(a)

/* Base float point types */
typedef DOUBLE DBL;
typedef FLOAT FLT;

/* Project math namespace */
namespace mth 
{
  /* Default math classes templates */
  template<typename Type> class vec2;
  template<typename Type> class vec3;
  template<typename Type> class vec4;
  template<typename Type> class matr;    
  template<typename Type> class camera;  
} /* end of 'mth' namespace */

#endif /* __mth_def_h_ */

/* END OF 'mth_def.h' FILE */
