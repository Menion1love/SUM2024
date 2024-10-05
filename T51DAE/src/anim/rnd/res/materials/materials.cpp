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

#include "tigl.h"

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
tigl::material & tigl::material::Create( const std::string &NewName,
                                   const tigl::vec3 &NewKa,
                                   const tigl::vec3 &NewKd,
                                   const tigl::vec3 &NewKs,
                                   FLT NewPh, FLT NewTrans,
                                   tigl::shader *NewShd,
                                   std::initializer_list<texture *> Textures)
{
  INT i = 0;
  BUF_MTL Data;
  Data.Ka = vec4(NewKa, 1);
  Data.KdTrans = vec4(NewKd, NewTrans);
  Data.KsPh = vec4(NewKs, NewPh);

  this->Name = NewName;
  this->Ka = NewKa;    
  this->Kd = NewKd;
  this->Ks = NewKs;    
  this->Ph = NewPh;
  this->Trans = NewTrans;
  this->Shd = NewShd;

  BufferMtl = Rnd->BufferCreate<BUF_MTL>(3, sizeof(Data), &Data);
  for (auto &t : Textures)
  {
    if (i >= 8)
      return *this;
    Data.Tex[i] = 1;
    Tex[i++] = t;
  }

  return *this;
} /* End of 'Create' function */

/* END OF 'material.cpp' FILE */