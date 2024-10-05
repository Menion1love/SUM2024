/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : textures.cpp
 * PURPOSE     : Animation project.
 *               Textures handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 05.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 

#include "tigl.h"

/* Texture create function.
 * ARGUMENTS:
 *   - texture name:
 *       const std::string &NewName;
 *   - image size:
 *       INT NewW, NewH;
 *   - components count:
 *       INT BytesPerPixel;
 *   - image pixel data:
 *       VOID *Pixels;
 * RETURNS:
 *   (texture &) self reference.
 */
tigl::texture & tigl::texture::Create( const std::string &NewName, INT NewW, INT NewH,
                                       INT BytesPerPixel, BYTE *Pixels, BOOL IsMips )
  {
    INT mips;
    
    glGenTextures(1, &TexId);
    glBindTexture(GL_TEXTURE_2D, TexId);
  
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
    mips = log(NewW > NewH ? NewW : NewH) / log(2);
    mips = mips < 1 ? 1 : mips;
  
    glTexStorage2D(GL_TEXTURE_2D, mips, BytesPerPixel == 4 ? GL_RGBA8 : BytesPerPixel == 3 ? GL_RGB8 : GL_R8, NewW, NewH);
  
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, NewW, NewH, GL_BGRA, GL_UNSIGNED_BYTE, Pixels);
                                                    
    glGenerateMipmap(GL_TEXTURE_2D);
  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
    glBindTexture(GL_TEXTURE_2D, 0);
    W = NewW;
    H = NewH;
    return *this;
  } /* End of 'Create' function */

/* Texture create function.
 * ARGUMENTS:
 *   - texture file name:
 *       const std::string &FileName;
 * RETURNS:
 *   (texture &) self reference.
 */
tigl::texture & tigl::texture::Create( const std::string &FileName )
{
  image img(FileName);

  return Create(FileName, img.W, img.H, 4, img.RowsB[0][0], TRUE);
} /* End of 'Create' function */

/* Apply texture function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::texture::Apply( VOID )
{
  glBindTexture(GL_TEXTURE_2D, TexId);
} /* End of 'Apply' function */    

/* END OF 'textures.cpp' FILE */