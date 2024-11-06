/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : u_test.cpp
 * PURPOSE     : Animation project.
 *               Test unit sample module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 01.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
                 
#include "tivk.h"

/* Project namespace */
namespace tivk
{
  class u_model : public tivk::unit
  {
  public:
    tivk::model *Model;
    /* Unit initialization function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     */
    u_model( anim *Ani )
    {
      Model = Ani->ModelCreateFromDae("bin/models/Zebra.dae");
    } /* End of 'u_control' function */

    /* Unit inter frame events handle function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani; ???
     * RETURNS: None.
     */
    VOID Response( anim *Ani ) override
    {
    } /* End of 'Response' function */
 
    /* Unit render function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani; ???
     * RETURNS: None.
     */
    VOID Render( anim *Ani ) override
    {
      Model->ModelDraw(matr::Scale(vec3(0.1)) * matr::RotateY(0));
    } /* End of 'Render' function */
    
    /* Unit initialization function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     */
    ~u_model( VOID ) override
    {
    } /* End of '~u_test' function */
  }; /* End of 'u_test' class */
} /* end of 'tivk' namespace*/

/* Register unit to stock by name */
static tivk::anim::unit_register<tivk::u_model> _("Model");

/* END OF 'u_test.cpp' FILE */
