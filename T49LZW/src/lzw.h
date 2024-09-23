/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : lzw.h
 * PURPOSE     : Lempel-Ziv-Welch project.
 *               Definiton algorithm module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 17.09.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <map>
#include "def.h"

/* Bits class */
class write
{
public:
  std::fstream BitF;
  CHAR BitAccum = -1000;
  INT BitPos = 7;

  /* Write constructor function.
   * ARGUMENTS:
   *   - file name for open:
   *       std::string Name;
   */
  write( std::string Name )
  {
    BitF.open(Name, std::fstream::out);
    if (!BitF.is_open()) {
      std::cout << "File not opened" << std::endl;
      return;
    }
  } /* End of 'write' function */

  /* Read some bits.
   * ARGUMENTS: 
   *    - value of writing bit:
   *       INT value;
   * RETURNS: None.
   */
  VOID bit( INT value );

  /* Write some bits.
   * ARGUMENTS: 
   *
   *
   * RETURNS: None.
   */
  VOID bits( INT count, INT * value );

  /* Write destructor.
   * ARGUMENTS: None.
   */
  ~write( VOID )
  {
    if (BitF.is_open())
      BitF.close();
  } /* End of '~write' function */
}; /* End of 'bits' class */

/* Bit class */
class read
{
public:
  std::fstream BitF;           
  uint8_t BitAccum = 0;
  INT BitPos = 0;
  uint8_t BitSave = 0;

  /* Read constructor function.
   * ARGUMENTS:
   *   - file name for open:
   *       std::string Name;
   */
  read( std::string Name )
  {
    BitF.open(Name, std::fstream::in);
    if (!BitF.is_open()) {
      std::cout << "File not opened" << std::endl;
      return;
    }
  } /* End of 'read' function */

  /* Read one bits.
   * ARGUMENTS: None. 
   * RETURNS: 
   *    (INT) bit value.
   */
  INT bit( VOID );

  /* Write one bits.
   * ARGUMENTS: 
   *    - number of reading bits:
   *       INT count;
   * RETURNS: 
   *   (INT) values of reading bits.
   */
  INT bits( INT count );
  
  /* Read destructor.
   * ARGUMENTS: None.
   */
  ~read( VOID )
  {
    if (BitF.is_open())
      BitF.close();
  } /* End of 'read' function */
}; /* End of 'bit' class */

class lzw
{
public:
  std::map<INT, std::string> m; 

  VOID Compress( std::string Name, std::string Name1 )
  {
    read reader(Name);
    write writer(Name);
    INT Cur;
    
    while ((Cur = reader.bits(6)) != -1)
    {
      INT Next = reader.bits(6);
      //if (Cur == Next)
        

    }
  }

};

/* END OF 'lzw.h' FILE */
