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

#include "gif.h"

INT main( VOID )
{ 
  /* Catch mem hooks */
  read r("test.bin");
  lzw buf;
  gif g;
//  buf.Compress("orwell.txt", "text.txt");
//  buf.DeCompress("text.txt", "text.bin");
  g.ReadGif("1.gif");
}

/* END OF 'main.cpp' FILE */
