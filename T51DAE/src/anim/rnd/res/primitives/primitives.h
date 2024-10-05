/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : primitives.h
 * PURPOSE     : Animation project.
 *               Resources declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 05.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __primitives_h_
#define __primitives_h_

#include "../resources_def.h"
#include "../materials/materials.h"
#include "topology.h"

/* Project namespace */
namespace tigl
{
  /* Primitive handle class */
  class prim : public resource
  {
    friend class render;
    friend class primitive_manager;
  private:
    prim_type Type {};    // Primitive type
    UINT VA {};           // Primitive vertex array
    UINT VBuf {};         // Vertex buffer
    UINT IBuf {};         // Index buffer
    UINT NumOfElements {}; // Number of elements for OpenGL
    matr Transform {};    // Primitive transformation matrix

    mutable BOOL IsVAUpdated = FALSE; // Vertex array update flag

    // Vertex parameters map (vertex attribute field, offset)
    std::map<std::string, INT> VertexMap;
    INT VertexStride {};  // Vertex stride in bytes

  public:
    material *Mtl {};     // Material pointer
    vec3
      Min {},             // Minimal primitive position
      Max {};             // Maximal primitive position

    
    /* Primitive creation function.
     * ARGUMENTS:
     *   - topology base reference:
     *       const topology::base &T;
     * RETURNS:
     *   (prim &) self reference.
     */
    template <class vertex>
      prim & Create( material *mtl, const topology::base<vertex> &T )
      {
        Free();
        Mtl = mtl;
        Type = T.Type;
        Transform = matr::Identity();
        NumOfElements = 0;
        VertexStride = sizeof(vertex);

        if constexpr (requires{vertex::P;})
          VertexMap["InPosition"] =
            reinterpret_cast<INT_PTR>(&((vertex *)0)->P);
        if constexpr (requires{vertex::T;})
          VertexMap["InTexCoord"] =
            reinterpret_cast<INT_PTR>(&((vertex *)0)->T);
        if constexpr (requires{vertex::N;})
          VertexMap["InNormal"] =
            reinterpret_cast<INT_PTR>(&((vertex *)0)->N);
        if constexpr (requires{vertex::C;})
          VertexMap["InColor"] =
            reinterpret_cast<INT_PTR>(&((vertex *)0)->C);
        if constexpr (requires{vertex::Tangent;})
          VertexMap["InTangent"] =
            reinterpret_cast<INT_PTR>(&((vertex *)0)->Tangent);
        if constexpr (requires{vertex::Bitangent;})
          VertexMap["InBitangent"] =
            reinterpret_cast<INT_PTR>(&((vertex *)0)->Bitangent);
        if (T.V.size() == 0 && T.I.size() == 0)
        {
          // Empty primitive
          Max = Min = vec3(0);
          return *this;
        }

        // Create OpenGL vertex array
        glGenVertexArrays(1, &VA);
        if (T.V.size() != 0)
        {
          // Collect min-max info
          if constexpr (requires{vertex::P;})
          {
            Min = Max = T.V[0].P;
            //for (auto vrt : T.V)
            //  Min = vrt.P.Min(Min), Max = vrt.P.Max(Max);
          }
          // Create OpenGL buffer
          glGenBuffers(1, &VBuf);
          // Activate vertex buffer
          glBindBuffer(GL_ARRAY_BUFFER, VBuf);
          // Store vertex data
          glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * T.V.size(),
                       T.V.data(), GL_STATIC_DRAW);
        } // vertex buffer creation

        // Indices
        if (T.I.size() > 0)
        {
          if (T.V.size() != 0)
          {
            // Create OpenGL buffer
            glGenBuffers(1, &IBuf);
            // Activate index buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
            // Store index data
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * T.I.size(),
                         &T.I[0], GL_STATIC_DRAW);
            // Disable index array
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
          }
          NumOfElements = (INT)T.I.size();
        }
        else
          NumOfElements = (INT)T.V.size();
        return *this;
      } /* End of 'Create' function */

      /* Update primitive vertex array function.
     * ARGUMENTS: None.
     * RETURNS: Non.
     */
    VOID UpdateVA( VOID ) const;

    /* Free primitive function.
     * ARGUMENTS:
     *   - primitive pointer:
     *       prim *Pr;
     * RETURNS: None.
     *   (prim *) created primitive interface.
     */
    VOID Free( VOID );
  };

  /* Primitive manager */
  class primitive_manager : public resource_manager<prim>
  {
  public:
    friend class render;

    primitive_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'buffer_manager' function */

    /* Create primitive function.
     * ARGUMENTS:
     *   - topology base reference:
     *       const topology::base &Tpl;
     * RETURNS:
     *   (prim *) created primitive interface.
     */
    template<class vertex_type>
      prim * PrimCreate( const topology::base<vertex_type> &Tpl = {}, material *mtl = nullptr )
      {
        return resource_manager::Add(prim().Create(mtl, Tpl));
      } /* End of 'PrimCreate' function */
    
    /* Create primitive function.
     * ARGUMENTS:
     *   - primitive type:
     *       const topology::base &Tpl;
     * RETURNS:
     *   (prim *) created primitive interface.
     */  
    prim * PrimCreate( material *mtl, prim_type Type, 
                   const std::vector<vertex::vert> &V = {}, const std::vector<INT> &Ind = {} )
    {      
      topology::trimesh<vertex::vert> T(V, Ind);

      return PrimCreate(T, mtl);
    } /* End of 'PrimCreate' function */

    /* Load model function.
     * ARGUMENTS:
     *   - pointer to material for model:
     *       material *mtl;
     *   - name of file with model:
     *       const CHAR *FileName ;
     * RETURNS:
     *   (prim *) created primitive interface.
     */
    prim * LoadModel( material *mtl, const CHAR *FileName );

    /* Free primitive function.
     * ARGUMENTS:
     *   - primitive pointer:
     *       prim *Pr;
     * RETURNS: None.
     *   (prim *) created primitive interface.
     */                                                       
    VOID PrimFree( prim *Pr )
    {
      resource_manager::Delete(Pr);
    } /* End of 'PrimFree' function */
  }; /* End of 'primitive_manager' class */
} /* end of 'tigl' namespace */

#endif /* __primitives_h_ */

/* END OF 'primitives.h' FILE */ 
