/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : topology.h
 * PURPOSE     : Animation project.
 *               Primitive topology declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 05.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __topology_h_
#define __topology_h_

#include "../resources_def.h"

namespace tivk
{
  /* Primitive shape representation type */
  enum struct prim_type
  {
    TRIMESH, /* Triangle mesh */
    POINTS,  /* Points collection */
    STRIP    /* Strip of triangles */
  }; /* End of 'prim_type' enum */

  /* Vertex collection namespace */
  namespace vertex
  {
    /* Standard vertex representation type */
    struct vert
    {
      vec3 P;  /* Vertex position */
      vec2 T;  /* Vertex texture coordinates */
      vec3 N;  /* Normal at vertex */
      vec4 C;  /* Vertex color */
    }; /* End of 'std' structure */

    /* The only point vertex representation type */
    struct point
    {
      vec3 P;  /* Vertex position */
    }; /* End of 'point' structure */

  } /* end of 'vertex' namespace */

  class prim;

  /* Topology structures namespase */
  namespace topology
  {
    /* Base topology class */
    template<class vertex_type>
      class base
      {
        friend class prim;  
      protected:
        prim_type Type = prim_type::TRIMESH;

        /* Vertex array */
        std::vector<vertex_type> V;
        /* Index array */
        std::vector<INT> I;

      public:   
        /* Class default constructor */
        base( VOID )
        {
        } /* End of 'base' function */

        /* Class constructor.
         * ARGUMENTS:
         *   - primitive type:
         *       prim_type NewType;
         *   - vertex array:
         *       const std::vector<vertex_type> &NewV;
         *   - index array:
         *       const std::vector<INT> &NewI;
         */
        base( prim_type NewType,
              const std::vector<vertex_type> &NewV = {},
              const std::vector<INT> &NewI = {} ) :
          Type(NewType), V(NewV), I(NewI)
        {
        } /* End of 'base' function */
      }; /* End of 'base' class */

    /* Trimesh topology class */
    template<class vertex_type>
      class trimesh : public base<vertex_type>
      {
      public:
        /* Class constructor.
         * ARGUMENTS:
         *   - vertex array:
         *       const std::vector<vertex> &NewV;
         *   - index array:
         *       const std::vector<INT> &NewI;
         */
        trimesh( const std::vector<vertex_type> &NewV,
                 const std::vector<INT> &NewI = {} ) :
          base<vertex_type>(prim_type::TRIMESH, NewV, NewI)
        {
        } /* End of 'trimesh' function */

        /* Eval normals for topology function.
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        VOID EvalNormals( VOID )
        {   
          for (INT i = 0; i < base<vertex_type>::V.size(); i++)
            base<vertex_type>::V[i].N = vec3(0);

          for (INT i = 0; i < base<vertex_type>::I.size(); i += 3)
          {
            INT
              n0 = base<vertex_type>::I[i], n1 = base<vertex_type>::I[i + 1], n2 = base<vertex_type>::I[i + 2];
            vec3
              p0 = base<vertex_type>::V[n0].P,
              p1 = base<vertex_type>::V[n1].P,
              p2 = base<vertex_type>::V[n2].P,
              N = ((p1 - p0) % (p2 - p0)).Normalizing();
 
            base<vertex_type>::V[n0].N += N;
            base<vertex_type>::V[n1].N += N;
            base<vertex_type>::V[n2].N += N;
          }
 
          for (INT i = 0; i < base<vertex_type>::V.size(); i++)
            base<vertex_type>::V[i].N = base<vertex_type>::V[i].N.Normalizing();

        } /* End of 'EvalNormals' function */
      }; /* End of 'trimesh' class */
  } /* end of 'topology' namespace */
} /* end of 'tivk' namespace */

#endif /* __topology_h_ */