/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : main.cpp
 * PURPOSE     : Animation project.
 *               Matrix declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_matr_h_
#define __mth_matr_h_

#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* Matrix representation type */
  template<typename Type>
    class matr
    {
    private:
    public: 
      Type A[4][4]; // Matrix body

      /* Default constructor */
      matr( VOID )
      {
      } /* End of 'matr' function */

      /* Matrix from sixteen arguments constructor.
       * ARGUMENTS:
       *   - new argumets componentr:
       *       Type a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;
       */
      matr( Type a1, Type a2, Type a3, Type a4,
            Type b1, Type b2, Type b3, Type b4,
            Type c1, Type c2, Type c3, Type c4,
            Type d1, Type d2, Type d3, Type d4)
      {
        A[0][0] = a1, A[0][1] = a2, A[0][2] = a3, A[0][3] = a4;
        A[1][0] = b1, A[1][1] = b2, A[1][2] = b3, A[1][3] = b4;
        A[2][0] = c1, A[2][1] = c2, A[2][2] = c3, A[2][3] = c4;
        A[3][0] = d1, A[3][1] = d2, A[3][2] = d3, A[3][3] = d4;
      } /* End of 'matr' function */
      
      /* Matrix from array constructor.
       * ARGUMENTS:
       *   - array with argumets componentr:
       *       Type B[4][4];
       */
      matr( Type B[4][4] ) 
      {
        for (INT i = 0; i < 4; i++)
          for (INT j = 0; j < 4; j++)
            A[i][j] = B[i][j];
      } /* End of 'matr' function */

      /* Matrix identity function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) identity matrix.
       */
      static matr Identity( VOID )
      {
        matr<Type> M(
          1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          0, 0, 0, 1);
        return M;
      } /* End of 'Identity' function */
      
      /* Matrix rotate on x axis function.
       * ARGUMENTS: 
       *   - angel in degrees:
       *       Type AngleInDegree;
       * RETURNS:
       *   (matr) rotated matrix.
       */
      static matr RotateX( Type AngleInDegree )
      {
        Type co = cos(D2R(AngleInDegree)), si = sin(D2R(AngleInDegree));
        matr<Type> M(
          1, 0, 0, 0,
          0, co, si, 0,
          0, -si, co, 0,
          0, 0, 0, 1);
        return M;
      } /* End of 'RotateX' function */
      
      /* Matrix rotate on y axis function.
       * ARGUMENTS: 
       *   - angel in degrees:
       *       Type AngleInDegree;
       * RETURNS:
       *   (matr) rotated matrix.
       */
      static matr RotateY( Type AngleInDegree )
      {
        Type co = cos(D2R(AngleInDegree)), si = sin(D2R(AngleInDegree));
        matr<Type> M(
          co, 0, -si, 0,
          0, 1, 0, 0,
          si, 0, co, 0,
          0, 0, 0, 1);
        return M;
      } /* End of 'RotateY' function */
      
      /* Matrix rotate on z axis function.
       * ARGUMENTS: 
       *   - angel in degrees:
       *       Type AngleInDegree;
       * RETURNS:
       *   (matr) rotated matrix.
       */
      static matr RotateZ( Type AngleInDegree )
      {
        Type co = cos(D2R(AngleInDegree)), si = sin(D2R(AngleInDegree));
        matr<Type> M(
          co, si, 0, 0,
          -si, co, 0, 0,
          0, 0, 1, 0,
          0, 0, 0, 1);
        return M;
      } /* End of 'RotateX' function */
      
      /* Matrix rotate on vector axis function.
       * ARGUMENTS: 
       *   - angel in degrees:
       *       Type AngleInDegree; 
       *   - vector to set axis:
       *       vec3 <Type> V;
       * RETURNS:
       *   (matr) rotated matrix.
       */
      static matr Rotate( Type AngleInDegree, vec3 <Type> V )
      {
        Type co = cos(D2R(AngleInDegree)), si = sin(D2R(AngleInDegree));
        vec3 <Type> V1;
        V1 = V.Normalizing();
  
        matr<Type> M(
          co + V1.x * V1.x * (1 - co), V1.y * V1.x * (1 - co) + V1.z * si, V1.x * V1.z * (1 - co) - V1.y * si, 0,
          V1.y * V1.x * (1 - co) - V1.z * si, co + V1.y * V1.y * (1 - co), V1.y * V1.z * (1 - co) + V1.x * si, 0,
          V1.x * V1.z * (1 - co) + V1.y * si, V1.y * V1.z * (1 - co) - V1.x * si, co + V1.z * V1.z * (1 - co), 0,
          0, 0, 0, 1);
        return M;
      } /* End of 'RotateX' function */
      
      /* Matrix scale function.
       * ARGUMENTS: 
       *   - vector with scale parameters:
       *       vec3 <Type> v;
       * RETURNS:
       *   (matr) scaled matrix.
       */
      static matr Scale( vec3 <Type> V )
      {
        matr<Type> M(
          V.x, 0, 0, 0,
          0, V.y, 0, 0,
          0, 0, V.z, 0,
          0, 0, 0, 1);
        return M;
      } /* End of 'Scale' function */
      
      /* Matrix scale function.
       * ARGUMENTS: 
       *   - scale parameters:
       *       Type v1, v2, v3;
       * RETURNS:
       *   (matr) scaled matrix.
       */
      static matr Scale( Type v1, Type v2, Type v3 )
      {
        matr<Type> M(                 
          v1, 0, 0, 0,
          0, v2, 0, 0,
          0, 0, v3, 0,
          0, 0, 0, 1);
        return M;
      } /* End of 'Scale' function */
      
      /* Matrix translate function.
       * ARGUMENTS: 
       *   - vector with translating parameters:
       *       vec3 <Type> v;
       * RETURNS:
       *   (matr) translated matrix.
       */
      static matr Translate( vec3 <Type> V )
      {
        matr<Type> M(
          1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          V.x, V.y, V.z, 1);
        return M;
      } /* End of 'Translate' function */
      
      /* Matrix translate function.
       * ARGUMENTS: 
       *   - translate parameters:
       *       Type v1, v2, v3;
       * RETURNS:
       *   (matr) translated matrix.
       */
      static matr Translate( Type v1, Type v2, Type v3 )
      {
        matr<Type> M(                 
          0, 0, 0, 0,
          0, 0, 0, 0,
          0, 0, 0, 0,
          v1, v2, v3, 1);
        return M;
      } /* End of 'Translate' function */
      
      /* Matrix transpose function.
       * ARGUMENTS: None. 
       * RETURNS:
       *   (matr) transposed matrix.
       */
      matr Transpose( VOID ) 
      {
        matr r = Identity();

        for (INT i = 0; i < 4; i++)
          for (INT j = 0; j < 4; j++)
            r.A[i][j] = A[j][i];

        return r.A;
      } /* End of 'Transpose' function */
      
      /* Matrix transform to vector function.
       * ARGUMENTS:
       *   - vector to transform:
       *       VEC V;
       * RETURNS:
       *   (VEC) result vector.
       */
      vec3 <Type>TransformVector( vec3 <Type>V )
      {
        return vec3(V[0] * A[0][0] + V[1] * A[1][0] + V[2] * A[2][0],
                      V[0] * A[0][1] + V[1] * A[1][1] + V[2] * A[2][1],
                      V[0] * A[0][2] + V[1] * A[1][2] + V[2] * A[2][2]);
      } /* End of 'TransformVector' function */

      /* Matrix4x3 transform to vector point function.
       * ARGUMENTS:
       *   - vector to transform:
       *       VEC V;
       *   - matrix to transform:
       *       MATR M;
       * RETURNS:
       *   (VEC) result vector.
       */
      vec3 <Type>VectorPointTransform( vec3 <Type>V )
      {
        return vec3<Type>(V[0] * A[0][0] + V[1] * A[1][0] + V[2] * A[2][0] + A[3][0],
                          V[0] * A[0][1] + V[1] * A[1][1] + V[2] * A[2][1] + A[3][1],
                          V[0] * A[0][2] + V[1] * A[1][2] + V[2] * A[2][2] + A[3][2]);
      } /* End of 'VectorPointTransform' function */

      /* Matrix4x3 transform to vector point function.
       * ARGUMENTS:
       *   - vector to transform:
       *       VEC V;
       *   - matrix to transform:
       *       MATR M;
       * RETURNS:
       *   (VEC) result vector.
       */
      vec3 <Type>TransformNormal( vec3 <Type>V )
      {
        matr <Type> m(A);
 
        return m.Inverse().Transpose().TransformVector(V);
      } /* End of 'TransformNormal' function */

      /* Vector by matrix multiplication (with homogenious devide) function.
       * ARGUMENTS:
       *   - source vector:
       *       VEC V;
       *   - multiplied matrix:
       *       MATR M;
       * RETURNS:
       *   (VEC) result vector.
       */
       static vec3 <Type> Transform4x4( vec3 <Type> V)
       { 
         Type w = V[0] * A[0][3] + V[1] * A[1][3] + V[2] * A[2][3] + A[3][3];
         
         return vec3<Type>((V[0] * A[0][0] + V[1] * A[1][0] + V[2] * A[2][0] + A[3][0]) / w,
                           (V[0] * A[0][1] + V[1] * A[1][1] + V[2] * A[2][1] + A[3][1]) / w,
                           (V[0] * A[0][2] + V[1] * A[1][2] + V[2] * A[2][2] + A[3][2]) / w);
       }  /* End of 'VecMulMatr' function */

      /* Multiplication of two matrix function.
       * ARGUMENTS: 
       *   - matrix for multiplication;
       *       const matr &m; 
       * RETURNS:
       *   (matr) result matrix.
       */
      matr operator*( const matr &m ) const 
      {
        matr r(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        for (INT i = 0; i < 4; i++)
          for (INT j = 0; j < 4; j++)
            for (INT k = 0; k < 4; k++)
              r.A[i][j] += A[i][k] * m.A[k][j];
 
        return r;
      } /* End of 'operator*' function */
      

      /* Find determination of matrix3x3 function.
       * ARGUMENTS: 
       *   - matrix3x3 values;
       *       Type A11, A12, A13, 
       *            A21, A22, A23,
       *            A31, A32, A33; 
       * RETURNS:
       *   (Type) result determination.
       */
      Type Determ3x3( Type A11, Type A12, Type A13, 
                      Type A21, Type A22, Type A23,
                      Type A31, Type A32, Type A33 ) 
      {
        return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
               A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
      } /* End of 'MatrDeterm3x3' function */

      /* Find determination of matrix function.
       * ARGUMENTS: None. 
       * RETURNS:
       *   (Type) result determination.
       */
      Type operator!( VOID ) 
      {
        return
            +A[0][0] * Determ3x3(A[1][1], A[1][2], A[1][3],
                                 A[2][1], A[2][2], A[2][3],
                                 A[3][1], A[3][2], A[3][3]) +
            -A[0][1] * Determ3x3(A[1][0], A[1][2], A[1][3],
                                 A[2][0], A[2][2], A[2][3],
                                 A[3][0], A[3][2], A[3][3]) +
            +A[0][2] * Determ3x3(A[1][0], A[1][1], A[1][3],
                                 A[2][0], A[2][1], A[2][3],
                                 A[3][0], A[3][1], A[3][3]) +
            -A[0][3] * Determ3x3(A[1][0], A[1][1], A[1][2],
                                 A[2][0], A[2][1], A[2][2],
                                 A[3][0], A[3][1], A[3][2]);
      } /* End of 'operator!' function */

      /* Find inverse matrix function.
       * ARGUMENTS: None. 
       * RETURNS:
       *   (MATR) inverse matrix.
       */
      matr Inverse( VOID ) 
      {
        Type det = !*this;
        matr r = Identity();
        INT i, j, 
          s[] = {1, -1},
          P[][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};
        if (det == 0)
          return r;
        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++)
            r.A[j][i] =
              s[(i + j) % 2] *
              Determ3x3(A[P[i][0]][P[j][0]], A[P[i][0]][P[j][1]], A[P[i][0]][P[j][2]],
                        A[P[i][1]][P[j][0]], A[P[i][1]][P[j][1]], A[P[i][1]][P[j][2]],
                        A[P[i][2]][P[j][0]], A[P[i][2]][P[j][1]], A[P[i][2]][P[j][2]]) / det;
        return r; 
      } /* End of 'Inverse' function */     

      /* Matrix look-at viewer setup function.
       * ARGUMENTS:
       *   - viewer position, look-at point, approximate up direction:
       *       VEC Loc, At, Up1;
       * RETURNS:
       *   (MATR) result matrix.
       */
      static matr View( vec3 <Type> Loc, vec3 <Type> Dir, vec3 <Type> Right, vec3 <Type> Up ) 
      {        
        matr m(
            Right.x, Up.x, -Dir.x, 0, Right.y, Up.y, -Dir.y, 0, Right.z, Up.z, -Dir.z, 0,
            -(Loc & Right), -(Loc & Up), Loc & Dir, 1);
        return m;
      } /* End of 'View' function */

      /* Matr frustum function.
       * ARGUMENTS:
       *   - points to view:
       *       FLT l, r, b, t, n, f; 
       * RETURNS: None;
       */
      static matr Frustum( Type l, Type r, Type b, Type t, Type n, Type f ) 
      {
        matr 
          h((2 * n) / (r - l), 0, 0, 0,
             0, (2 * n) / (t - b), 0, 0,
             (r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n), -1,
             0, 0, -((2 * n * f) / (f - n)), 0);
        return h;
      } /* End of 'Frustum' function */

      /* Matr orthogonalic function.
       * ARGUMENTS:
       *   - points to view:
       *       FLT Left, Right, Bottom, Top, Near, Far; 
       * RETURNS: None;
       */
      static matr Ortho( Type  Left, Type Right, Type Bottom, Type Top, Type Near, Type Far ) 
      {
        matr <Type>r = 
        {
          {
            {2 / (Right - Left), 0, 0, 0},
            {0, 2 / (Top - Bottom), 0, 0},
            {0, 0, 2 / (Far - Near), 0},
            {-((Right + Left) / (Right - Left)), -((Top + Bottom) / (Top - Bottom)), -((Far + Near) / (Far - Near)), 1},
          }
        };
  
        return r;
      } /* End of 'Ortho' function */

      operator Type*( VOID )
      {
        return A[0];
      }

      /* Print matrix to console function.
       * ARGUMENTS: None.
       * RETURNS: None;
       */
      VOID show( VOID ) 
      {
        matr m = *this;
        for (INT i = 0; i < 4; i++)
        {
          std::cout << "{";
          for (INT j = 0; j < 4; j++)
          {
            std::cout << m.A[i][j]; 
            if (j == 3)
              std::cout << "";
            else
              std::cout << ", ";
          }
          std::cout << "}" << std::endl;  
        }
      } /* End of 'show' function */

      FLT * toArray( VOID )
      {
        FLT *d = new FLT[16];

        for (INT i = 0; i < 4; i++)
          for (INT j = 0; j < 4; j++)
            d[i + j * 4] = A[i][j];

        return d;
      }
    }; /* End of 'matr' class */
} /* end of 'mth' namespace */

#endif /* __mth_h_ */

/* END OF 'mth.h' FILE */
