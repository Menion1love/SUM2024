/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : input.h
 * PURPOSE     : Animation project.
 *               Input declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __input_h_
#define __input_h_

#include "keyboard.h"
#include "mouse.h"

/* Project namespace */
namespace tigl
{
  /* Input representation type */
  class input : public keyboard, public mouse
  {
  public:
    /* Default constructor */
    explicit input( VOID )
    {
    } /* End of 'input' function */

    /* Initialization of input function.
     * ARGUMENTS: 
     *    - window context:
     *       HWND hWnd;
     * RETURNS: None.
     */
    input( HWND &hWnd )
    {
      tigl::mouse::Init(hWnd);
      tigl::keyboard();
    } /* End of 'Init' function */

    /* Reset of input function.
     * ARGUMENTS: 
     *    - window context:
     *       HWND hWnd;
     * RETURNS: None.
     */
    VOID Reset( VOID )
    {
      tigl::keyboard::Reset();
      tigl::mouse::Reset();
    } /* End of 'Reset' function */

    /* Response of input function.
     * ARGUMENTS: 
     *    - mouse wheel count:
     *       INT &MouseWheel;
     * RETURNS: None.
     */
    VOID Response( INT &MouseWheel )
    {
      tigl::keyboard::Response();
      tigl::mouse::Response(MouseWheel);
     } /* End of 'Responce' function */
  }; /* End of 'input' class */
} /* end of 'tigl' namespace */

#endif /* __input_h_ */

/* END OF 'input.h' FILE */
