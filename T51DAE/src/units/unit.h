/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : unitrs.h
 * PURPOSE     : Animation project.
 *               Unit samples declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 01.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
                 
#ifndef __unit_h_
#define __unit_h_

#include "def.h"

/* Project namespace */
namespace tigl
{
  class anim;
  /* Unit representation type */
  class unit 
  {
  public:
    /* Unit inter frame events handle function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     * RETURNS: None.
     */
    virtual VOID Response( anim *Ani )
    {
    } /* End of 'Response' function */
 
    /* Unit render function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     * RETURNS: None.
     */
    virtual VOID Render( anim *Ani )
    {            
    } /* End of 'Render' function */

    /* Unit deinitialization function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     * RETURNS: None.
     */
    virtual ~unit( VOID )
    {
    } /* End of '~unit' function */
  }; /* End of 'unit' class */
} /* end of 'tigl' namespace */

#endif /* __unit_h_ */

/* END OF 'unit.h' FILE */
