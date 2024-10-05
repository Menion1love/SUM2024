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
  struct HEADER_INFO
  {
    // 0..2 bits - bits per pixel (- 1)
    BYTE BPP : 3;
    // 3 bit – not used
    BYTE Unused : 1;
    // 4..6 bits - color resolution (- 1)
    BYTE ColorResolution : 3;
    // 7 bit     - global color table presence flag
    BYTE GlobalPaletteFlag : 1;
  } Info;
  BYTE BackgroundColor; // Backgound color index
  BYTE Reserved;        // Not used (0)
}; /* End of 'HEADER' structure */
#pragma pack(pop)
class gif
{
public:
  std::vector<BYTE> DeCompressGIF( std::string File, INT StartBits, INT S, INT W, INT H )
  {    
    read reader(File);
    for (INT i = 0; i < S; i++)
      std::cout << (CHAR)reader.BitF.get();
    INT Cur = 0, Next = 0, Code = 0, pos = 0;
    std::vector<BYTE> Data;
    Data.resize(W * H * 8);
    static struct DecDict
    {
      INT Pf;
      INT Sf;
    } Dict[MAX] {};

    INT StackSize = 0;

    static CHAR Stack[MAX] {};

    INT CurBits = 9;

    Next = reader.bits2(CurBits);
    Data[pos++] = Next;
    Cur = Next;
    Code = CLEAR + 1;

    while (!reader.BitF.eof())
    {
      Next = reader.bits2(CurBits);
      if (Next != -1)
      {
        if (Next == CLEAR)
        {
          Code = CLEAR + 1;
          CurBits = 9;
          Cur = reader.bits2(CurBits);
          Data[pos++] = Cur;
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
            if (Stack[i] != 0)
              Data[pos++] = Stack[i];
 

          Dict[Code++] = {Cur, Stack[StackSize - 1]};
  
          if (Code + 1 == (1 << CurBits) && CurBits < MAX_BITS)
            CurBits++;

          Cur = Next;
        }
      }
      else 
        Cur = Next;
      }
    return Data;
  }
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
    INT SizeOfCurFile = 0;
    f.read((CHAR *)&Head, sizeof(Head));
    SizeOfCurFile += sizeof(Head);
    if (std::string(Head.Sign, Head.Sign + 6) != "GIF87a" &&
        std::string(Head.Sign, Head.Sign + 6) != "GIF89a")
      return;
 
    UINT BitsPerPixel = (Head.Info.BPP & 7) + 1, ColorBits = ((Head.Info.ColorResolution >> 4) & 7) + 1;
    BOOL IsGlobalColorTable = (Head.Info.GlobalPaletteFlag);

    std::array<BYTE [3], 256> GlobalPalette {};
 
    if (IsGlobalColorTable)
    {
      f.read((CHAR *)GlobalPalette.data(), 3 * (1 << BitsPerPixel));
      SizeOfCurFile += 3 * (1 << BitsPerPixel);
    }
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
        f.read((CHAR *)&ih.Info, sizeof(ih.Info));
        SizeOfCurFile += sizeof(ih.Info);
        UINT
          BitsPerPixel = (ih.Info.BPP & 7) + 1;
        BOOL
          IsInterlaced = (ih.Info.ColorResolution >> 6) & 1,
          IsLocalColorTable = (ih.Info.GlobalPaletteFlag >> 7);
 
        std::array<BYTE [3], 256> LocalPalette;
 
        if (IsLocalColorTable)
        {
          SizeOfCurFile += 3 * (1 << BitsPerPixel);

          f.read((CHAR *)LocalPalette.data(), 3 * (1 << BitsPerPixel));
        }
        else
          LocalPalette = GlobalPalette;
 
        BYTE ImageCodeSize;
        f.read((CHAR *)&ImageCodeSize, 1);
        SizeOfCurFile += 1;
        f.close();
        std::vector<BYTE> EndData;
        //do
        //{
        //  f.read((CHAR *)&Size, 1);
        //  if (f.gcount() != 1 || Size == 0)
        //    break;
        //  INT buf_pos = InData.size();
        //  InData.resize(buf_pos + Size);
        //  f.read((CHAR *)&InData[buf_pos], Size);
        //}  while (Size != 0);

        EndData = DeCompressGIF(File, BitsPerPixel, SizeOfCurFile, Head.W, Head.H);
        f.open(File, std::ios_base::binary);
      }
      else if (ch == '!')
      {
        BYTE ExtCode;
        f.read((CHAR *)&ExtCode, 1);
        SizeOfCurFile += 1;
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
