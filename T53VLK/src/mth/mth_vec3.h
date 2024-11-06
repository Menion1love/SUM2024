/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_vec3.h
 * PURPOSE     : Animation project.
 *               3D vector declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* 3D vector representation type */
  template<typename Type>
    class vec3
    {
    public:
      Type x, y, z; // 3D vector's directions  
    
      /* Default constructor */
      vec3( VOID ) : x(0), y(0), z(0)
      {
      } /* End of 'vec3' function */

      /* 3D vector from three arguments constructor.
       * ARGUMENTS:
       *   - new argumets componentr:
       *       Type a, b, c;
       */
      vec3( Type a, Type b, Type c ) : x(a), y(b), z(c)
      {
      } /* End of 'vec3' function */
      
      /* 3D vector from one arguments constructor.
       * ARGUMENTS:
       *   - new argumet componentr:
       *       Type a;
       */
      explicit vec3( Type a ) : x(a), y(a), z(a)
      {
      } /* End of 'vec3' function */

      /* Sum of two vectors function.
       * ARGUMENTS:
       *   - vector to be add:
       *      const vec3 &c;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator+( const vec3 &c ) const 
      {
        return vec3(c.x + x, c.y + y, c.z + z); 
      } /* End of 'operator+' function */

      /* Add number function.
       * ARGUMENTS:
       *   - number to be add:
       *       const Type &c;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 & operator+=( const Type &c )
      {
        x += c;
        y += c;
        z += c;
        return *this; 
      } /* End of 'operator+=' function */

      /* Add vector function.
       * ARGUMENTS:
       *   - vector to be add to this vector:
       *       const vec3 &c;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 & operator+=( const vec3 &c )
      {
        x += c.x;
        y += c.y;
        z += c.z;
        return *this; 
      } /* End of 'operator+=' function */

      /* Subtraction of two vectors function.
       * ARGUMENTS:
       *   - vector to be sub:
       *      const vec3 &c;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator-( const vec3 &c ) const 
      {
        return vec3(x - c.x, y - c.y, z - c.z); 
      } /* End of 'operator-' function */

      /* Subtraction of two vectors function.
       * ARGUMENTS:
       *   - vector to be sub:
       *      const Type &c;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator-( const Type &c ) const 
      {
        return vec3(x - c, y - c, z - c); 
      } /* End of 'operator-' function */

      /* Create negative function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator-( void ) const 
      {
        return vec3(-x, -y, -z); 
      } /* End of 'operator-' function */
      
      /* Sub vector function.
       * ARGUMENTS:
       *   - vector to be sub:
       *       const vec3 &c;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 & operator-=( const vec3 &c )
      {
        x -= c.x;
        y -= c.y;
        z -= c.z;
        return *this; 
      } /* End of 'operator-=' function */

      /* Sub a number function.
       * ARGUMENTS:
       *   - number to be sub:
       *       const Type &c;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 & operator-=( const Type &c )
      {
        x -= c;
        y -= c;
        z -= c;
        return *this; 
      } /* End of 'operator-=' function */

      /* Multiplication of two vectors function.
       * ARGUMENTS:
       *   - vector to be multiplication:
       *       const vec3 &c;                 
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator*( const vec3 &c ) const 
      {
        return vec3(x * c.x, y * c.y, z * c.z); 
      } /* End of 'operator*' function */

      /* Multiplication on number function.
       * ARGUMENTS:
       *   - vector to be multiplication:
       *       const Type &c;                 
       * RETURNS:
       *   (vec3) result vector.
       */   
      vec3 operator*( const Type &c ) const 
      {
        return vec3(x * c, y * c, z * c); 
      } /* End of 'operator*' function */
      
      /* Dot product of two vectors function.
       * ARGUMENTS:
       *   - vector to dot product:
       *       const vec3 &v;                 
       * RETURNS:
       *   (vec3) result vector.
       */                            
      Type operator&( const vec3 &v ) const 
      {
        return x * v.x + y * v.y + z * v.z;
      } /* End of 'operator&' function */
      
      /* Cross product of two vectors function.
       * ARGUMENTS:
       *   - vector to dot product:
       *       const vec3 &v;                 
       * RETURNS:
       *   (vec3) result vector.
       */                   
      vec3 operator%( const vec3 &c ) const 
      {
        return vec3(y * c.z - z * c.y, z * c.x - x * c.z, x * c.y - y * c.x); 
      } /* End of 'operator%' function */

      /* Multiplication on vector function.
       * ARGUMENTS:
       *   - vector to be multiplication:
       *       const vec3 &c;                 
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 & operator*=( const vec3 &c )
      {
        x *= c.x;
        y *= c.y;
        z *= c.z;
        return *this; 
      } /* End of 'operator*=' function */

      /* Multiplication on number function.
       * ARGUMENTS:
       *   - number to be multiplication:
       *       const Type &c;                 
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 & operator*=( const Type &c )
      {
        x *= c;
        y *= c;
        z *= c;
        return *this; 
      } /* End of 'operator*=' function */

      /* Division of vector on number function.
       * ARGUMENTS:
       *   - number to be multiplication:
       *       const Type &c;                 
       * RETURNS:
       *   (vec3) result vector.
       */   
      vec3 operator/( const Type &c ) const 
      {
        return vec3(x / c, y / c, z / c); 
      } /* End of 'operator/' function */
                            
      /* Division on number function.
       * ARGUMENTS:
       *   - number to be multiplication:
       *       const Type &c;                 
       * RETURNS:
       *   (vec3) result vector.
       */   
      vec3 & operator/=( const Type &c )
      {
        x /= c;
        y /= c;
        z /= c;
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
       *   (vec3) result vector.
       */  
      vec3 & Normalize( VOID )
      {
        Type len = *this & *this;

        if (len == 1 || len == 0)
          return *this;
        return *this /= sqrt(len);
      } /* End of 'Normalize' function */
      
      /* Normalizing function.
       * ARGUMENTS: None.                 
       * RETURNS:
       *   (vec3) pointer to normalized vector.
       */
      vec3 Normalizing( VOID ) const
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
       *   (vec3) zero vector.
       */  
      vec3 & Zero( VOID )
      {
        return *this = vec3(0);
      } /* End of 'Zero' function */
      
      /* Generate random vector function.
       * ARGUMENTS: None.                 
       * RETURNS:
       *   (vec3) random vector. (arguments from 0 to RAND_MAX)
       */  
      vec3 & Rnd0( VOID )
      {            
        return *this = vec3((Type)rand());
      } /* End of 'Rnd0' function */
      
      /* Generate random vector function.
       * ARGUMENTS: None.                 
       * RETURNS:
       *   (vec3) random vector. (arguments from 0 to 1)
       */
      static vec3 Rnd1( VOID )
      {
        return vec3((Type)rand() / RAND_MAX, (Type)rand() / RAND_MAX, (Type)rand() / RAND_MAX);
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
        else if (n == 2)
          return z;
        else
          return x;
      } /* End of 'operator[]' function */

      /* Get reflect by normal function.
       * ARGUMENTS: 
       *   - normal's vector:
       *       const vec3 &n;
       * RETURNS:
       *   (vec3) count of reflect.
       */
      vec3 Reflect( const vec3 &n ) const
      {
        return *this - (n * (n & *this) * 2.0);
      } /* End of 'Reflect' function */

      /* Find absolute of vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) absolute vector.
       */
      vec3 abs( VOID ) const
      {
        vec3 r = *this;
        if (r.x < 0)
          r.x = -r.x;
        if (r.y < 0)
          r.y = -r.y;
        if (r.z < 0)
          r.z = -r.z;
        return r;
      } /* End of 'abs' function */

      /* Get vector's components signs function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) signs of vector's components.
       */
      vec3 sign( VOID ) const
      {
        vec3 r = *this;

        if (r.x > 0)
          r.x = 1;
        else if (r.x == 0)
          r.x = 0;
        else
          r.x = -1;
        if (r.y > 0)
          r.y = 1;
        else if (r.y == 0)
          r.y = 0;
        else
          r.y = -1;
        if (r.z > 0)
          r.z = 1;
        else if (r.z == 0)
          r.z = 0;
        else
          r.z = -1;

        return r;
      } /* End of 'sign' function */

      /* Set step fuinction to 2 vectors function.
       * ARGUMENTS: 
       *   - second vector:
       *       const vec3 &n;
       * RETURNS:
       *   (vec3) result of step vector.
       */
      vec3 step( const vec3 &n ) const
      {
        vec3 res;
        if (n.x >= x)
          res.x = 1.0;
        else
          res.x = 0.0;
      
       if (n.y >= y)
          res.y = 1.0;
        else
          res.y = 0.0;

        if (n.z >= z)
          res.z = 1.0;
        else
          res.z = 0.0;

        return res;
       }  /* End of 'step' function */ 

      /* Print to console vector function.
       * ARGUMENTS: None. 
       * RETURNS: None.
       */
      VOID operator()( VOID ) 
      {
        std::cout << "vec3(" << x << ", " << y << ", " << z << ")" << std::endl; 
      } /* End of 'show' function */
    }; /* End of 'vec3' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec3_h_ */

/* END OF 'mth_vec3.h' FILE */