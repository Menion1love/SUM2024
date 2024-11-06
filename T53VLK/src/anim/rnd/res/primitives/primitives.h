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
namespace tivk
{
  /* Primitive handle class */
  class prim : public resource
  {
    friend class render;
    friend class primitive_manager;
  private:
    UINT NumOfElements {}; // Number of elements for OpenGL    
    UINT NumOfIndexes {};  // Number of elements for OpenGL
    matr Transform {};     // Primitive transformation matrix

    buffer *VertexBuffer;
    buffer *IndexBuffer;

  public:
    material *Mtl {};     // Material pointer

    buffer *PrimBuf;

    /* Primitive creation function.
     * ARGUMENTS:
     *   - topology base reference:
     *       const topology::base &T;
     * RETURNS:
     *   (prim &) self reference.
     */
    template <class vertex>
      prim & Create( material *mtl, const topology::base<vertex> &T );

    /* Free primitive function.
     * ARGUMENTS: None.
     * RETURNS: None.
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
        prim *pr = resource_manager::Add(prim());
        pr->Create(mtl, Tpl);
        return pr;
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
} /* end of 'tivk' namespace */

#endif /* __primitives_h_ */

/* END OF 'primitives.h' FILE */ 
