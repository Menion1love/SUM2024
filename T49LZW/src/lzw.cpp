/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : lzw.cpp
 * PURPOSE     : Lempel-Ziv-Welch project.
 *               Main algorithm module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 19.09.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "lzw.h"

/* Read some bits.
 * ARGUMENTS: 
 *    - value of writing bit:
 *       INT value;
 * RETURNS: None.
 */
VOID write::bit( INT value )
{
  BitAccum |= value << BitPos--; 
  if (BitPos < 0)
  {
    BitF.write(&BitAccum, 1);
    BitAccum = 0;
    BitPos = 7;
  }
} /* End of 'read' function */

/* Write some bits.
 * ARGUMENTS: 
 *
 *
 * RETURNS: None.
 */
VOID write::bits( INT count, INT * value )
{
  for (INT i = 0; i < count; i++)
    bit(value[i]);
} /* End of 'write' function */

/* Read one bit.
 * ARGUMENTS: None. 
 * RETURNS: 
 *    (INT) bit value.
 */
INT read::bit( VOID )
{
  if (!BitF.eof())
  {

    if (BitPos < 0)
    {
      BitPos = 7;
      BitF.read((CHAR *)&BitAccum, 1);
    }
    return (BitAccum >>  BitPos--) & 1;
  }
  return 0;
} /* End of 'read' function */

/* Write one bits.
 * ARGUMENTS: 
 *    - number of reading bits:
 *       INT count; 
 * RETURNS: 
 *   (INT) values of reading bits.
 */
INT read::bits( INT count )
{
  INT res;

/*  INT res = 0;
  uint8_t tmpBit = 0;
  
  if (BitF.eof())
    return -1;
  
  if (BitPos < count)
  {
    BitF.read((CHAR *)&tmpBit, 1);
  }
  if (tmpBit != 0)
  {
      BitPos += count;
      BitSave = tmpBit >> (8 - BitPos);

      tmpBit <<= (BitPos - count - 2);
      BitAccum = tmpBit + BitSave;
  }
  else
  {
    BitSave <<= (8 - BitPos);
    BitAccum += BitSave;
  }


  CHAR maskBit = (1 << count) - 1;

  res = BitAccum & maskBit;
  BitAccum >>= count;
  BitPos -= count;
  return res;
  */
} /* End of 'write' function */

/* END OF 'lzw.cpp' FILE */ 
