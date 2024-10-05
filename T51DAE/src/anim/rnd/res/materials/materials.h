/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : materials.h
 * PURPOSE     : Animation project.
 *               Materials declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 02.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __materials_h_
#define __materials_h_

#include "../resources_def.h"
#include "../shaders/shaders.h"   
#include "../buffers/buffers.h"    
#include "../textures/textures.h"

/* Project namespace */
namespace tigl
{
  class render;
  /* Primitive handle class */
  class material : public resource
  {
  private:
    // Material buffer data type
    struct BUF_MTL
    {
      vec4 Ka;       // Ambient
      vec4 KdTrans;  // Diffuse + Transparency
      vec4 KsPh;     // Specular + Phong
      BOOL Tex[8] {};
    }; /* End of 'BUF_MTL' structure */

  public:
    // Material name
    std::string Name;

    // Illumination coefficients (anbient, diffuse, specular)
    vec3 Ka, Kd, Ks;
    // Phong coefficient and transparency value
    FLT Ph, Trans;
    // Shader pointer
    shader *Shd {};
    // Texture pointers
    texture *Tex[8] {};

    // Material data buffer
    buffer *BufferMtl {};

    /* Class default constructor */
    material( VOID )
    {
    } /* End of 'material' function */

    /* Class destructor */
    ~material( VOID )
    {
    } /* End of '~material' function */

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
    material & Create( const std::string &NewName,
                       const vec3 &NewKa = vec3(0.1),
                       const vec3 &NewKd = vec3(0.9),
                       const vec3 &NewKs = vec3(0.0),
                       FLT NewPh = 30, FLT NewTrans = 1,
                       shader *NewShd = nullptr,
                       std::initializer_list<texture *> Textures = {});

    /* Material destroy function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID )
    {
      Shd->Free();
      delete[] *Tex;
      ZeroMemory(this, sizeof(this));
    }

    /* Apply material function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (shader *) shader interface;
     */
    shader * Apply( VOID )
    {
      INT prg;

      /* Set shader program Id */
      prg = Shd->ProgId;
      
      if (prg <= 0)
        return 0;
 
      glUseProgram(prg);

      BUF_MTL Data;
      Data.Ka = vec4(Ka, 1);
      Data.KdTrans = vec4(Kd, Trans);
      Data.KsPh = vec4(Ks, Ph);

      /* Set shading parameters */
      BufferMtl->Apply();

      /* Set textures */
      for (INT i = 0 ; i < 8; i++)
      {
        if (Tex[i] != nullptr)
          if (Tex[i]->TexId != -1)
          {
            glActiveTexture(GL_TEXTURE0 + i);
            Tex[i]->Apply();
          }
      }

      return Shd;
    }

    /* Update material buffer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Update( VOID );
  };
   
  class material_manager : public resource_manager<material>
  {
    friend class render;
    material_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'buffer_manager' function */

  public:
     material * MtlCreate( const std::string &NewName,
                           const vec3 &NewKa = vec3(0.1),
                           const vec3 &NewKd = vec3(0.9),
                           const vec3 &NewKs = vec3(0.0),
                           FLT NewPh = 30, FLT NewTrans = 1,
                           shader *NewShd = nullptr,
                           std::initializer_list<texture *> Textures = {})
     {
       material *mtl = resource_manager::Add(material());
       mtl->Create(NewName, NewKa, NewKd, NewKs, NewPh, NewTrans, NewShd, Textures);
       return mtl;
     }

  }; /* End of 'primitive_manager' class */
} /* end of 'tigl' namespace */

#endif /* __materials_h_ */

/* END OF 'materials.h' FILE */ 
