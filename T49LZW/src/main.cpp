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
  //SetDbgMemHooks();

  read bufr("test.bin");
  write bufw("text.txt");
  lzw buf;
  buf.Compress("orwell.txt", "text.txt");
  std::cout << "Compress done!" << std::endl;
  //buf.DeCompress("text.txt", "test.res");
}

/* END OF 'main.cpp' FILE */
