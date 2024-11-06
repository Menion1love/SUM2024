/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mouse.h
 * PURPOSE     : Animation project.
 *               Mouse declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __mouse_h_
#define __mouse_h_

/* Project namespace */
namespace tivk
{
  /* Mouse representation type */
  class mouse
  {  
  private:
    HWND MousehWnd; // Mouse window context
  public:
    INT 
      Mx,  // Mouse X coordination 
      My,  // Mouse Y coordination 
      Mz,  // Mouse Z coordination 
      Mdx, // Mouse dX coordination
      Mdy, // Mouse dY coordination
      Mdz; // Mouse dZ coordination
    
    /* Default constructor */
    mouse( VOID )
    {
      Mx = My = Mz = Mdx = Mdy = Mdz = 0;
    } /* End of 'mouse' function */

    /* Initialization of mouse input function.
     * ARGUMENTS: 
     *    - window context:
     *       HWND hWnd;
     * RETURNS: None.
     */
    VOID Init( HWND &hWnd )
    {
      POINT pt;
      MousehWnd = hWnd;
      GetCursorPos(&pt);
      ScreenToClient(MousehWnd, &pt);

      Mdx = pt.x - Mx;
      Mdy = pt.y - My;
  
      Mx = pt.x;
      My = pt.y;

      Mdz = 0;
      Mz = 0;
    } /* End of 'Init' function */

    /* Response of mouse input function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( INT &MouseWheel )
    {
      POINT pt;

      GetCursorPos(&pt);
      ScreenToClient(MousehWnd, &pt);

      Mdx = pt.x - Mx;
      Mdy = pt.y - My;
  
      Mx = pt.x;
      My = pt.y;

      Mdz = MouseWheel;
      Mz += MouseWheel;
      MouseWheel = 0;
    } /* End of 'Response' function */

    /* Reset of mouse input function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Reset( VOID )
    {
      Mdx = 0;
      Mdy = 0;
      Mx = 0;
      My = 0;
      Mdz = 0;
      Mz = 0;
    } /* End of 'Reset' function */
  }; /* End of 'mouse' class */
} /* end of 'tivk' namespace */

#endif /* __mouse_h_ */

/* END OF 'mouse.h' FILE */