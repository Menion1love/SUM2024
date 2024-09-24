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

#define TERM 256
#define CLEAR 257
#define MAX_BITS 12 
#define MAX (1 << MAX_BITS)

/* Bits class */
class write
{
public:
  std::fstream BitF;
  uint8_t BitAccum = 0;
  INT BitPos = 8;

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
  VOID bits( INT count, INT value );

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
  std::map<std::pair<INT, INT>, INT> dict; 
  std::map<INT, std::pair<INT, INT>> dedict;
  struct Dictory
  {
    INT Pref;
    INT Suf;
  } table[MAX];

  INT START_BITS = 8; 
  INT Code = 258; 

  VOID Compress( std::string Name, std::string Name1 )
  {
    read reader(Name);
    write writer(Name1);
    INT Cur = reader.bits(START_BITS);
    INT Next = 0;
    dict.insert({{TERM, TERM}, 256});
    dict.insert({{CLEAR, CLEAR}, 257});
    while (Cur != -1)
    {
      Next = reader.bits(START_BITS);
      auto s = dict.find({Cur, Next});
      if (s != dict.end())
        Cur = s->second;
      else
      {
        if (Next == 0)
        {
          dict.insert({{Cur, Next}, TERM});
          return;
        }
        dict.insert({{Cur, Next}, Code});
        dedict.insert({Code++, {Cur, Next}});
        writer.bits(START_BITS, (CHAR)Cur);
        //table[Code].Pref = Cur;
        //table[Code].Pref = Next;
        Cur = Next;
      }    
    }

  }
  
  VOID DeCompress( std::string Name, std::string Name1 )
  {
    read reader(Name);
    write writer(Name1);
    INT DeCode = 0;
    
    while ((DeCode = reader.bits(START_BITS)) != -1)
    {
      CHAR Stack[MAX] {};

      INT i = 0;
      while (DeCode < 255)
      {
        Stack[i++] = dedict.find(DeCode)->second.first;
        DeCode = dedict.find(DeCode)->second.first;
      }
      Stack[i++] = DeCode;
      while (i-- > 0)
        writer.bits(START_BITS, Stack[i]);
    }
  }
};

/* END OF 'lzw.h' FILE */
