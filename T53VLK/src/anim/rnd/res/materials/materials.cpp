/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : u_material.cpp
 * PURPOSE     : Animation project.
 *               material sample module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 05.10.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "tivk.h"

/* Material creation function.
 * ARGUMENTS:
 *   - material name:
 *       const std::string &NewName;
 *   - illumination coefficients (ambient. diffuse, specular):
 *       const color3 &NewKa, &NewKd, &NewKs;
 *   - Phong shininess coefficient:
 *       FLT NewPh;
 *   - transparency coefficient:
 *       FLT NewTrans;
 *   - shader pointer:
 *       shader *NewShd;
 *   - textures list:
 *       std::initializer_list<texture *> Textures;
 * RETURNS:
 *   (material &) self reference.
 */
tivk::material & tivk::material::Create( const std::string &NewName,
                                   const tivk::vec3 &NewKa,
                                   const tivk::vec3 &NewKd,
                                   const tivk::vec3 &NewKs,
                                   FLT NewPh, FLT NewTrans,
                                   tivk::shader *NewShd,
                                   std::initializer_list<texture *> Textures)
{
  INT i = 0;
  BUF_MTL Data {};

  BufferMtl = Rnd->BufferCreate<BUF_MTL>(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, &Data, 1, 1);

  this->Name = NewName;
  this->Ka = NewKa;    
  this->Kd = NewKd;
  this->Ks = NewKs;    
  this->Ph = NewPh;
  this->Trans = NewTrans;
  this->Shd = NewShd;

  Data.Ka = vec4(NewKa, 1);
  Data.KdTrans = vec4(NewKd, NewTrans);
  Data.KsPh = vec4(NewKs, NewPh);

  for (auto &t : Textures)
  {
    if (i >= 8)
      return *this;
    Data.Tex[i] = 1;
    Tex[i++] = t;
  }

  BufferMtl->UpdateBuffer(&Data);
  Rnd->VlkCore.UpdateDescriptorSet(BufferMtl);

  return *this;
} /* End of 'Create' function */

/* END OF 'material.cpp' FILE */