/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : models.h
 * PURPOSE     : Animation project.
 *               Models declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 04.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __models_h_
#define __models_h_

#include "../resources_def.h"

 /* Project namespace */
namespace tigl
{
  /* Unstructured data file reader class */
  class rdr
  {
  private:
    // Memory pointer reference
    BYTE *&Ptr;

  public:
    /* Class constructor.
      * ARGUMENTS:
      *   - reference to memory pointer:
      *       BYTE *&PtrRef;
      */
    rdr( BYTE *&PtrRef ) : Ptr(PtrRef)
    {
    } /* End of 'rdr' function */

    /* Read data function.
      * ARGUMENT:
      *   - read data pointer:
      *       type *Data;
      *   - read data count:
      *       INT Count;
      * RETURNS: None.
      */
    template<typename type>
      VOID operator()( type *Data, const INT Count = 1 )
      {
        if (Count == 1)
          *Data = *(type *)Ptr, Ptr += sizeof(type);
        else
          memcpy(Data, Ptr, sizeof(type) * Count), Ptr += sizeof(type) * Count;
      }
  }; /* End of 'rdr' class */

  /* Primitive handle class */
  class model : public resource
  {
    friend class render;
  public:
    INT NumOfPrims; /* Number of primitives in array */  
    std::vector<tigl::prim *> Prims; /* Array of primitives */
    matr Trans;     /* Common transformation matrix */
    
    model( VOID )
    {
    }

    model & CreateModel( const std::string &FileName );

    /* Draw array of primitives function.
     * ARGUMENTS:
     *   - pointer to primitives structure:            
     *       th4PRIMS *Prs;
     *   - global transformation matrix:
     *       MATR World;
     * RETURNS: None.
     */
    VOID ModelDraw( matr World );
  }; /* End of 'buffer_manager' class */

  class model_manager : public resource_manager<model>
  {

  public:
    model_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'buffer_manager' function */

    model * ModelCreate( const std::string &NewName )
    {
      model *m = resource_manager::Add(model());
      m->CreateModel(NewName);
      return m;
    }

  }; /* End of 'primitive_manager' class */
} /* end of 'tigl' namespace */

#endif /* __models_h_ */

/* END OF 'models.h' FILE */ 



