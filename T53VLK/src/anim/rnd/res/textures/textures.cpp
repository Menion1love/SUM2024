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
 

#include "tivk.h"

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
tivk::texture & tivk::texture::Create( const std::string &NewName, INT NewW, INT NewH,
                                       INT BytesPerPixel, BYTE *Pixels, BOOL IsMips )
  {
    
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
tivk::texture & tivk::texture::Create( const std::string &FileName )
{
  image img(FileName);

  Rnd->VlkCore.Stage = Rnd->BufferCreate<BYTE>(VK_BUFFER_USAGE_TRANSFER_SRC_BIT, img.Pixels.data(), img.Pixels.size(), 3); 
  Rnd->VlkCore.ImageCreate(this->Image, this->ImageView, this->TextureMemory, img.W, img.H, 1, 0, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT, VK_IMAGE_LAYOUT_UNDEFINED, img.Pixels.data(), img.Pixels.size(), 1); 
  this->W = img.W; 
  this->H = img.H; 

  Rnd->VlkCore.UpdateDescriptorSet(this);
  Rnd->VlkCore.Stage->Free();
  return *this;
} /* End of 'Create' function */

/* Apply texture function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::texture::Apply( VOID )
{
} /* End of 'Apply' function */    

/* END OF 'textures.cpp' FILE */