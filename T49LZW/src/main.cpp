/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : main.cpp
 * PURPOSE     : Lempel-Ziv-Welch project.
 *               Main module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 17.09.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "lzw.h"
#include "def.h"

INT main( VOID )
{ 
  /* Catch mem hooks */
  SetDbgMemHooks();

  read w("test.bin");
//  write w1("text.txt");
  std::cout << w.bits(8) << " ";
  std::cout << w.bits(8) << " ";
  std::cout << w.bits(8) << " ";
//  std::cout << w.bits(6) << " ";

}

/* END OF 'main.cpp' FILE */
