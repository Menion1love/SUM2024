/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_vec2.h
 * PURPOSE     : Animation project.
 *               2D vector declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_vec2_h_
#define __mth_vec2_h_
  
#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* 3D vector representation type */
  template<typename Type>
    class vec2
    {
    public:
      Type x, y; // 2D vector's directions  
    
      /* Default constructor */
      vec2( VOID ) : x(0), y(0)
      {
      } /* End of 'vec2' function */

      /* 2D vector from two arguments constructor.
       * ARGUMENTS:
       *   - new argumets componentr:
       *       Type a, b;
       */
      vec2( Type a, Type b ) : x(a), y(b)
      {
      } /* End of 'vec2' function */
      
      /* 2D vector from one arguments constructor.
       * ARGUMENTS:
       *   - new argumet componentr:
       *       Type a;
       */
      explicit vec2( Type a ) : x(a), y(a)
      {
      } /* End of 'vec2' function */

      /* Sum of two vectors function.
       * ARGUMENTS:
       *   - vector to be add:
       *      const vec2 &c;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator+( const vec2 &c ) const 
      {
        return vec2(c.x + x, c.y + y); 
      } /* End of 'operator+' function */

      /* Add number function.
       * ARGUMENTS:
       *   - number to be add:
       *       const Type &c;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 & operator+=( const Type &c )
      {
        x += c;
        y += c;
        return *this; 
      } /* End of 'operator+=' function */

      /* Add vector function.
       * ARGUMENTS:
       *   - vector to be add to this vector:
       *       const vec2 &c;
       * RETURNS:
       *   (vec2) result vector.
       */
       vec2 & operator+=( const vec2 &c )
       {
         x += c.x;
         y += c.y;
         return *this; 
       } /* End of 'operator+=' function */

      /* Subtraction of two vectors function.
       * ARGUMENTS:
       *   - vector to be sub:
       *      const vec2 &c;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator-( const vec2 &c ) const 
      {
        return vec2(x - c.x, y - c.y); 
      } /* End of 'operator-' function */

      /* Create negative function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator-( void ) const 
      {
        return vec2(-x, -y); 
      } /* End of 'operator-' function */
      
      /* Sub vector function.
       * ARGUMENTS:
       *   - vector to be sub:
       *       const vec2 &c;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 & operator-=( const vec2 &c )
      {
        x -= c.x;
        y -= c.y;
        return *this; 
      } /* End of 'operator-=' function */

      /* Sub a number function.
       * ARGUMENTS:
       *   - number to be sub:
       *       const Type &c;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 & operator-=( const Type &c )
      {
        x -= c;
        y -= c;
        return *this; 
      } /* End of 'operator-=' function */

      /* Multiplication of two vectors function.
       * ARGUMENTS:
       *   - vector to be multiplication:
       *       const vec2 &c;                 
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator*( const vec2 &c ) const 
      {
        return vec2(x * c.x, y * c.y); 
      } /* End of 'operator*' function */

      /* Multiplication on number function.
       * ARGUMENTS:
       *   - vector to be multiplication:
       *       const Type &c;                 
       * RETURNS:
       *   (vec2) result vector.
       */   
      vec2 operator*( const Type &c ) const 
      {
        return vec2(x * c, y * c); 
      } /* End of 'operator*' function */
      
      /* Dot product of two vectors function.
       * ARGUMENTS:
       *   - vector to dot product:
       *       const vec2 &v;                 
       * RETURNS:
       *   (vec2) result vector.
       */                               
      Type operator&( const vec2 &v ) const {
        return x * v.x + y * v.y;
      } /* End of 'operator&' function */
      
      /* Multiplication on vector function.
       * ARGUMENTS:
       *   - vector to be multiplication:
       *       const vec2 &c;                 
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 & operator*=( const vec2 &c )
      {
        x *= c.x;
        y *= c.y;
        return *this; 
      } /* End of 'operator*=' function */

      /* Multiplication on number function.
       * ARGUMENTS:
       *   - number to be multiplication:
       *       const Type &c;                 
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 & operator*=( const Type &c )
      {
        x *= c;
        y *= c;
        return *this; 
      } /* End of 'operator*=' function */

      /* Division of vector on number function.
       * ARGUMENTS:
       *   - number to be multiplication:
       *       const Type &c;                 
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator/( const Type &c ) const 
      {
        return vec2(x / c, y / c); 
      } /* End of 'operator/' function */
                            
      /* Division on number function.
       * ARGUMENTS:
       *   - number to be multiplication:
       *       const Type &c;                 
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 & operator/=( const Type &c )
      {
        x /= c;
        y /= c;
        return *this; 
      } /* End of 'operator/=' function */

      /* Get length of vector function.
       * ARGUMENTS: None.                 
       * RETURNS:
       *   (Type) result length.
       */
      Type operator!( void ) const 
      {
        Type d = *this & *this;
        if (d == 1 || d == 0)
          return d;
        return sqrt(d);
      } /* End of 'operator!' function */

      /* Normalize function.
       * ARGUMENTS: None.                 
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 & Normalize( VOID )
      {
        Type len = *this & *this;

        if (len == 1 || len == 0)
          return *this;
        return *this /= sqrt(len);
      } /* End of 'Normalize' function */
      
      /* Normalizing function.
       * ARGUMENTS: None.                 
       * RETURNS:
       *   (vec2) pointer to normalized vector.
       */
      vec2 Normalizing( VOID ) const
      {
        Type len = *this & *this;

        if (len == 1 || len == 0)
          return *this;
        return *this / sqrt(len);
      } /* End of 'Normalizing' function */ 
      
      /* Get length in square of vector function.
       * ARGUMENTS: None.                 
       * RETURNS:
       *   (Type) result length in square.
       */
      Type Length2( VOID ) const 
      {
        return *this & *this;
      } /* End of 'Length2' function */
      
      /* Generate zero vector function.
       * ARGUMENTS: None.                 
       * RETURNS:
       *   (vec2) zero vector.
       */
      vec2 & Zero( VOID )
      {
        return *this = vec2(0);
      } /* End of 'Zero' function */
      
      /* Generate random vector function.
       * ARGUMENTS: None.                 
       * RETURNS:
       *   (vec2) random vector. (arguments from 0 to RAND_MAX)
       */
      vec2 & Rnd0( VOID )
      {            
        return *this = vec2((Type)rand());
      } /* End of 'Rnd0' function */
      
      /* Generate random vector function.
       * ARGUMENTS: None.                 
       * RETURNS:
       *   (vec2) random vector. (arguments from 0 to 1)
       */
      vec2 & Rnd1( VOID )
      {
        return * this = vec2((Type)rand() / RAND_MAX);
      } /* End of 'Rnd1' function */
      
      /* Get one of vector's arguments function.
       * ARGUMENTS: 
       *   - index of vector's argument:
       *       const int n;
       * RETURNS:
       *   (Type) argumnet.
       */
      Type operator[]( const int n ) const
      {
        if (n == 0)
          return x;
        else if (n == 1)
          return y;
        else
          return x;
      } /* End of 'operator[]' function */
  
      /* Print to console vector function.
       * ARGUMENTS: None. 
       * RETURNS: None.
       */
      VOID operator()( VOID ) 
      {
        std::cout << "vec2(" << x << ", " << y << ")" << std::endl; 
      } /* End of 'show' function */
    }; /* End of 'vec2' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec2_h_ */

/* END OF 'mth_vec2.h' FILE */
