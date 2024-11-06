/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_vec4.h
 * PURPOSE     : Animation project.
 *               4D vector declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_vec4_h_
#define __mth_vec4_h_

#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* 4D vector representation type */
  template<typename Type>
    class vec4
    {
    public:                    
      Type x, y, z, w; // 4D vector's directions  
    
      /* Default constructor */
      vec4( VOID ) : x(0), y(0), z(0), w(0)
      {
      } /* End of 'vec4' function */

      /* 4D vector from four arguments constructor.
       * ARGUMENTS:
       *   - new argumets componentr:
       *       Type a, b, c, d;
       */
      vec4( Type a, Type b, Type c, Type d ) : x(a), y(b), z(c), w(d)
      {
      } /* End of 'vec2' function */

      /* 4D vector from four arguments constructor.
       * ARGUMENTS:
       *   - new argumets componentr:
       *       Type a, b, c, d;
       */
      vec4( vec3<Type> a, Type d ) : x(a.x), y(a.y), z(a.z), w(d)
      {
      } /* End of 'vec2' function */
      
      /* 4D vector from one arguments constructor.
       * ARGUMENTS:
       *   - new argumet componentr:
       *       Type a;
       */
      explicit vec4( Type a ) : x(a), y(a), z(a), w(a)
      {
      } /* End of 'vec4' function */

      /* Sum of two vectors function.
       * ARGUMENTS:
       *   - vector to be add:
       *      const vec4 &c;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator+( const vec4 &c ) const 
      {
        return vec4(c.x + x, c.y + y, c.z + z, c.w + w); 
      } /* End of 'operator+' function */

      /* Add number function.
       * ARGUMENTS:
       *   - number to be add:
       *       const Type &c;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 & operator+=( const Type &c )
      {
        x += c;
        y += c;
        z += c;
        w += c;
        return *this; 
      } /* End of 'operator+=' function */

      /* Add vector function.
       * ARGUMENTS:
       *   - vector to be add to this vector:
       *       const vec4 &c;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 & operator+=( const vec4 &c )
      {
        x += c.x;
        y += c.y;
        z += c.z;
        w += c.w;
        return *this; 
      }/* End of 'operator+=' function */

      /* Subtraction of two vectors function.
       * ARGUMENTS:
       *   - vector to be sub:
       *      const vec4 &c;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator-( const vec4 &c ) const 
      {
        return vec4(x - c.x, y - c.y, z - c.z, w - c.z); 
      } /* End of 'operator-' function */

      /* Create negative function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator-( void ) const 
      {
        return vec4(-x, -y, -z, -w); 
      } /* End of 'operator-' function */
      
      /* Sub vector function.
       * ARGUMENTS:
       *   - vector to be sub:
       *       const vec4 &c;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 & operator-=( const vec4 &c )
      {
        x -= c.x;
        y -= c.y;
        z -= c.z; 
        w -= c.w;
        return *this; 
      } /* End of 'operator-=' function */

      /* Sub a number function.
       * ARGUMENTS:
       *   - number to be sub:
       *       const Type &c;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 & operator-=( const Type &c )
      {
        x -= c;
        y -= c;
        z -= c;
        w -= c;
        return *this; 
      } /* End of 'operator-=' function */

      /* Multiplication of two vectors function.
       * ARGUMENTS:
       *   - vector to be multiplication:
       *       const vec4 &c;                 
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator*( const vec4 &c ) const 
      {
        return vec4(x * c.x, y * c.y, z * c.z, z * c.w); 
      } /* End of 'operator*' function */

      /* Multiplication on number function.
       * ARGUMENTS:
       *   - vector to be multiplication:
       *       const Type &c;                 
       * RETURNS:
       *   (vec4) result vector.
       */   
      vec4 operator*( const Type &c ) const 
      {
        return vec4(x * c, y * c, z * c, w * c); 
      } /* End of 'operator*' function */
      
      /* Dot product of two vectors function.
       * ARGUMENTS:
       *   - vector to dot product:
       *       const vec4 &v;                 
       * RETURNS:
       *   (vec4) result vector.
       */                               
      Type operator&( const vec4 &v ) const {
        return x * v.x + y * v.y + z * v.z + w * v.w;
      } /* End of 'operator&' function */
      
      /* Multiplication on vector function.
       * ARGUMENTS:
       *   - vector to be multiplication:
       *       const vec4 &c;                 
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 & operator*=( const vec4 &c )
      {
        x *= c.x;
        y *= c.y;
        z *= c.z;        
        w *= c.w;
        return *this; 
      } /* End of 'operator*=' function */

      /* Multiplication on number function.
       * ARGUMENTS:
       *   - number to be multiplication:
       *       const Type &c;                 
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 & operator*=( const Type &c )
      {
        x *= c;
        y *= c;
        z *= c;           
        w *= c;
        return *this; 
      } /* End of 'operator*=' function */

      /* Division of vector on number function.
       * ARGUMENTS:
       *   - number to be multiplication:
       *       const Type &c;                 
       * RETURNS:
       *   (vec4) result vector.
       */ 
      vec4 operator/( const Type &c ) const 
      {
        return vec4(x / c, y / c, z / c, w / c); 
      } /* End of 'operator/' function */
                            
      /* Division on number function.
       * ARGUMENTS:
       *   - number to be multiplication:
       *       const Type &c;                 
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 & operator/=( const Type &c )
      {
        x /= c;
        y /= c;
        z /= c;
        w /= c;
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
       *   (vec4) result vector.
       */
      vec4 & Normalize( VOID )
      {
        Type len = *this & *this;

        if (len == 1 || len == 0)
          return *this;
        return *this /= sqrt(len);
      } /* End of 'Normalize' function */
      
      /* Normalizing function.
       * ARGUMENTS: None.                 
       * RETURNS:
       *   (vec4) pointer to normalized vector.
       */
      vec4 Normalizing( VOID ) const
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
       *   (vec4) zero vector.
       */
      vec4 & Zero( VOID )
      {
        return *this = vec4(0);
      } /* End of 'Zero' function */
      
      /* Generate random vector function.
       * ARGUMENTS: None.                 
       * RETURNS:
       *   (vec4) random vector. (arguments from 0 to RAND_MAX)
       */
      vec4 & Rnd0( VOID )
      {            
        return *this = vec4((Type)rand());
      } /* End of 'Rnd0' function */
      
      /* Generate random vector function.
       * ARGUMENTS: None.                 
       * RETURNS:
       *   (vec4) random vector. (arguments from 0 to 1)
       */
      vec4 & Rnd1( VOID )
      {
        return * this = vec4((Type)rand() / RAND_MAX);
      } /* End of 'Rnd1' function */
      
      /* Get one of vector's arguments function.
       * ARGUMENTS: 
       *   - index of vector's argument:
       *       const int n;
       * RETURNS:
       *   (Type) argumnet.
       */
      Type operator[]( const Type n ) const
      {
        if (n == 0)
          return x;
        else if (n == 1)
          return y;
        else if (n == 2)
          return z;
        else
          return x;
      }  /* End of 'operator[]' function */
      
      /* Print to console vector function.
       * ARGUMENTS: None. 
       * RETURNS: None.
       */
      VOID show( VOID ) 
      {
        std::cout << "{" << x << ", " << y << ", " << z << ", " << w << "}" << std::endl; 
      } /* End of 'show' function */
    }; /* End of 'vec4' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec4_h_ */

/* END OF 'mth_vec4.h' FILE */
