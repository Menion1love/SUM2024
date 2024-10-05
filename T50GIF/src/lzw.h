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

#include "def.h"

#define TERM 256
#define CLEAR 257
#define MAX_BITS 12
#define START_BITS 9
#define MAX (1 << MAX_BITS)

/* Bits class */
class write
{
public:
  std::ofstream BitF;
  uint8_t BitAccum = 0;
  INT BitPos = 8;

  /* Write constructor function.
   * ARGUMENTS:
   *   - file name for open:
   *       std::string Name;
   */
  write( std::string Name )
  {
    BitF.open(Name, std::ios_base::binary);
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
   *    - number of writing bit:
   *       INT count;                    
   *    - bit's value:
   *       INT value;
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
  std::ifstream BitF;    // File for reading       
  uint8_t BitAccum = 0; // Bit accumulator
  INT BitPos = 0;       // Position of current byte
  uint8_t BitSave = 0;  // Bit to save

  /* Read constructor function.
   * ARGUMENTS:
   *   - file name for open:
   *       std::string Name;
   */
  read( std::string Name )
  {
    BitF.open(Name, std::ios_base::binary);
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
  
  INT bits2( INT count );

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
  std::map<std::pair<INT, INT>, INT> dictMap; // Dictory map

  INT PASS_BITS = 0; // Number of passing bits
  INT Code = 258;    // Current code in dictory

  /* Compress file by lzw to file.
   * ARGUMENTS: 
   *    - file name for reading:
   *       std::string Name;
   *    - file name for writing:
   *       std::string Name1;
   * RETURNS: None.
   */
  VOID Compress( std::string Name, std::string Name1 )
  {
    read reader(Name);   
    write writer(Name1);
    INT Cur = reader.bits(8);
    INT Next = 0;
    dictMap.insert({{TERM, TERM}, TERM});
    dictMap.insert({{CLEAR, CLEAR}, CLEAR});
    INT CurBits = START_BITS; 
    while (Cur != -1)
    {
      Next = reader.bits(8);
      auto s = dictMap.find({Cur, Next});
      if (s != dictMap.end())
        Cur = s->second;
      else
      {
        dictMap.insert({{Cur, Next}, Code++});
        writer.bits(CurBits, Cur);
        Cur = Next;

        if (Code == (1 << CurBits))
        {
          CurBits++;
          if (CurBits > MAX_BITS)
          {
            writer.bits(CurBits - 1, CLEAR);
            Code = CLEAR + 1;
            CurBits = START_BITS;
            dictMap.clear();
          }
        }
        //else
        //{
        //}
      } 
    }
    if (Code == (1 << CurBits))
    {
      CurBits++;
      if (CurBits > MAX_BITS)
      {
        writer.bits(CurBits - 1, TERM);
      }
    }
    else 
      writer.bits(CurBits, TERM);
  } /* End of 'Compress' function */

  /* DeCompress file by lzw to file.
   * ARGUMENTS: 
   *    - file name for reading:
   *       std::string Name;
   *    - file name for writing:
   *       std::string Name1;
   * RETURNS: None.
   */
  VOID DeCompress( std::string Name, std::string Name1 )
  {
    read reader(Name);
    write writer(Name1);
    INT Cur = 0, Next = 0;
    
    static struct DecDict
    {
      INT Pf;
      INT Sf;
    } Dict[MAX] {};

    INT StackSize = 0;

    static CHAR Stack[MAX] {};

    INT CurBits = START_BITS;

    Next = reader.bits2(CurBits);
    writer.bits(8, Next);
    Cur = Next;
    Code = CLEAR + 1;

    while (Cur != -1)
    {
      Next = reader.bits2(CurBits);
      if (Next != -1)
      {
        if (Next == CLEAR)
        {
          Code = CLEAR + 1;
          CurBits = START_BITS;
          Cur = reader.bits2(CurBits);
          writer.bits(8, Cur);
        }
        else 
        { 
          INT DeCode = Next;
          StackSize = 0;
  
          if (Next >= Code)
            DeCode = Cur, StackSize = 1;
  
          while (DeCode > CLEAR)
          {
            Stack[StackSize++] = Dict[DeCode].Sf;
            DeCode = Dict[DeCode].Pf;
          }
  
          Stack[StackSize++] = DeCode;
  
          if (Next >= Code)
            Stack[0] = Stack[StackSize - 1];
  
          for (INT i = StackSize - 1; i >= 0; i--)
            writer.bits(8, Stack[i]);
  
          Dict[Code++] = {Cur, Stack[StackSize - 1]};
  
          if (Code + 1 == (1 << CurBits) && CurBits < MAX_BITS)
            CurBits++;

          Cur = Next;

        }
      }
      else 
        Cur = Next;
      }
  }
};

/* END OF 'lzw.h' FILE */
