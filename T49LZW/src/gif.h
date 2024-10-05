/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : gif.h
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

#include <format>
#include <array>
#include "def.h"
#include "lzw.h"

#pragma pack(push, 1)
/* GIF file header structure */
struct HEADER
{
  CHAR Sign[6];         // GIF file signature 'GIF8?a'
  WORD W, H;            // Image size
  BYTE Info;
  BYTE BackgroundColor; // Backgound color index
  BYTE Reserved;        // Not used (0)
}; /* End of 'HEADER' structure */

#pragma pack(pop)
class gif
{
public:
  /* Compress file by lzw to file.
   * ARGUMENTS: 
   *    - file name for reading:
   *       std::string Name;
   *    - file name for writing:
   *       std::string Name1;
   * RETURNS: None.
   */
  VOID ReadGif( std::string File )
  {
    // Read GIF header
    std::ifstream f(File, std::ios_base::binary);
    HEADER Head;
    f.read((CHAR *)&Head, sizeof(Head));
    if (std::string(Head.Sign, Head.Sign + 6) != "GIF87a" &&
        std::string(Head.Sign, Head.Sign + 6) != "GIF89a")
      return;
 
    UINT BitsPerPixel = (Head.Info & 7) + 1, ColorBits = ((Head.Info >> 4) & 7) + 1;
    BOOL IsGlobalColorTable = (Head.Info >> 7);

    std::array<BYTE [3], 256> GlobalPalette {};
 
    if (IsGlobalColorTable)
      f.read((CHAR *)GlobalPalette.data(), 3 * (1 << BitsPerPixel));

    while (TRUE)
    {
      CHAR ch;
 
      if (!f.get(ch))
        break;
 
      if (ch == ';')
        break;
      else if (ch == ',')
      {
        HEADER ih;
        f.read((CHAR *)&ih, sizeof(ih));
        UINT
          BitsPerPixel = (ih.Info & 7) + 1;
        BOOL
          IsInterlaced = (ih.Info >> 6) & 1,
          IsLocalColorTable = (ih.Info >> 7);
 
        std::array<BYTE [3], 256> LocalPalette;
 
        if (IsLocalColorTable)
          f.read((CHAR *)LocalPalette.data(), 3 * (1 << BitsPerPixel));
        else
          LocalPalette = GlobalPalette;
 
        BYTE ImageCodeSize;
        
        f.read((CHAR *)&ImageCodeSize, 1);
        std::vector<BYTE> InData;
        std::vector<BYTE> EndData;

        EndData.resize(Head.W * Head.H);
        BYTE Size;
        
        do
        {
          f.read((CHAR *)&Size, 1);
          if (f.gcount() != 1 || Size == 0)
            break;
          INT buf_pos = InData.size();
          InData.resize(buf_pos + Size);
          f.read((CHAR *)&InData[buf_pos], Size);
        }  while (Size != 0);

        INT p = 0;
        std::vector<BYTE> BitData {};
        BitData.resize(InData.size() * 8);

        for (INT i = 0; i < InData.size(); i++)
          for (INT j = 0; j < 8; j++)
            BitData[p++] |= (InData[i] >> j) & 1;
        INT Cur = 0, Next = 0, Code = 0, pos = 0, Bpos = 0;
        INT clear = 2 << ImageCodeSize;

        static struct DecDict
        {
          INT Pf;
          INT Sf;
        } Dict[MAX] {};

        INT StackSize = 0;

        static CHAR Stack[MAX] {};

        INT CurBits = ImageCodeSize + 1;
        Code = clear + 1;
        
        for (INT i = 0; i < CurBits; i++)
          Next |= BitData[Bpos + i];
        Bpos += CurBits;
        EndData[pos++] = Next;
        Cur = Next;

        while (Bpos < InData.size() * 8)
        {
          for (INT i = 0, Next = 0; i < CurBits; i++)
            Next |= BitData[Bpos + i];
          Bpos += CurBits;
          if (Next == clear)
          {
            Code = clear;
            CurBits = ImageCodeSize;
            for (INT i = 0, Next = 0; i < CurBits; i++)
              Cur |= BitData[Bpos + i];
            Bpos += CurBits;

//            Cur = reader.bits2(CurBits);
            EndData[pos++] = Cur;
          }
          else 
          { 
            INT DeCode = Next;
            StackSize = 0;
  
            if (Next >= Code)
              DeCode = Cur, StackSize = 1;
  
            while (DeCode > clear)
            {
              Stack[StackSize++] = Dict[DeCode].Sf;
              DeCode = Dict[DeCode].Pf;
            }
  
            Stack[StackSize++] = DeCode;
  
            if (Next >= Code)
              Stack[0] = Stack[StackSize - 1];

            for (INT i = StackSize - 1; i >= 0; i--)
            {
              std::cout << Stack[i];

              EndData[pos++] = Stack[i];
            }
           
            Dict[Code++] = {Cur, Stack[StackSize - 1]};
  
            if (Code + 1 == (1 << CurBits) && CurBits < MAX_BITS)
              CurBits++;

            Cur = Next;
          }
        }
        std::cout << 1;
      }
      else if (ch == '!')
      {
        BYTE ExtCode;
        f.read((CHAR *)&ExtCode, 1);
        BYTE Size;
        do
        {
          f.read((CHAR *)&Size, 1);
          if (f.gcount() != 1)
            break;
          f.seekg(Size, std::ios_base::cur);
        } while (Size != 0);
      }
      else 
        break;
    }
  }
};
