/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : keyboard.h
 * PURPOSE     : Animation project.
 *               Keyboard declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __keyboard_h_
#define __keyboard_h_

/* Project namespace */
namespace tigl
{
  /* Keyboard representation type */
  class keyboard
  {
  private:
     BYTE 
      KeysOld[256];   /* Old keys state */
  public:
    /* Input parameters */
    BYTE 
      Keys[256],      /* Keys state */
      KeysClick[256]; /* Clicked keys state */

    /* Default constructor */
    keyboard( VOID ) 
    {
      GetKeyboardState(Keys);
      for (INT i = 0; i < 256; i++)
        Keys[i] >>= 7;
 
      memcpy(KeysOld, Keys, 256);

    } /* End of 'keyboard' function */

    /* Response of keyboard input function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      GetKeyboardState(Keys);
      for (INT i = 0; i < 256; i++)
      { 
        Keys[i] >>= 7;
        KeysClick[i] = Keys[i] && !KeysOld[i];
      }
      memcpy(KeysOld, Keys, 256);
    } /* End of 'Response' function */
    
    /* Reset of keyboard input function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Reset( VOID )
    {
      for (INT i = 0; i < 256; i++)
      {
        KeysOld[i] = 0;
        Keys[i] = 0;
        KeysClick[i] = 0;
      }
    }/* End of 'Reset' function */
  }; /* End of 'keyboard' class */
} /* end of 'tigl' namespace */

#endif /* __keyboard_h_ */

/* END OF 'keyboard.h' FILE */