/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : u_tex_sample.cpp
 * PURPOSE     : Animation project.
 *               Test unit sample module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 30.10.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "tivk.h"

/* Project namespace */
namespace tivk
{
  class u_tex_sample : public tivk::unit
  {
  public:
    tivk::material *M;
    tivk::prim *pr; 
    tivk::shader *shd {};
    tivk::texture *tex {};

    /* Unit initialization function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     */
    u_tex_sample( anim *Ani )
    {
      const std::vector<INT> ind = {0, 1, 2, 2, 1, 3};
      const std::vector<vertex::vert> v = 
      {
        {{-0.5, -0.5, 0}, {0, 0}, {0, 0, 1}, {1, 1, 1, 1}},
        {{0.5, -0.5, 0}, {1, 0}, {0, 0, 1}, {1, 1, 1, 1}},
        {{-0.5, 0.5, 0}, {0, 1}, {0, 0, 1}, {1, 1, 1, 1}}, 
        {{0.5, 0.5, 0}, {1, 1}, {0, 0, 1}, {1, 1, 1, 1}}, 
      };

      topology::trimesh<vertex::vert> T(v, ind);
      image Image("Zebra.bmp");
      Ani->VlkCore.Stage = Ani->BufferCreate<BYTE>(VK_BUFFER_USAGE_TRANSFER_SRC_BIT, Image.Pixels.data(), Image.Pixels.size(), 3); 
      VkImage a;
      VkImageView b; 
      VkDeviceMemory m;
      Ani->VlkCore.ImageCreate(a, b, m, Image.W, Image.H, 1, 0, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT, VK_IMAGE_LAYOUT_UNDEFINED, Image.Pixels.data(), Image.Pixels.size(), 1); 
      Ani->VlkCore.UpdateDescriptorSet(Ani->VlkCore.Stage);
      shd = Ani->ShdCreate("sample");
      M = Ani->MtlCreate("Emerald", vec3(0.0215, 0.1745, 0.0215), vec3(0.07568, 0.61424, 0.07568), vec3(0.633, 0.727811, 0.633), 76.8, 1, shd);
      pr = Ani->PrimCreate(T, M);
      Ani->VlkCore.Stage->Free();
    } /* End of 'u_control' function */

    /* Unit inter frame events handle function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani; ???
     * RETURNS: None.
     */
    VOID Response( anim *Ani ) override
    {
    } /* End of 'Response' function */
 
    /* Unit render function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani; ???
     * RETURNS: None.
     */
    VOID Render( anim *Ani ) override
    {
      //Ani->Draw(pr, matr::Scale(vec3(1.0)) * matr::RotateY(30 * Ani->Time));

    } /* End of 'Render' function */
    
    /* Unit initialization function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     */
    ~u_tex_sample( VOID ) override
    {
    } /* End of '~u_test' function */
  }; /* End of 'u_test' class */
} /* end of 'tivk' namespace*/

/* Register unit to stock by name */
static tivk::anim::unit_register<tivk::u_tex_sample > _("TexSample");

/* END OF 'u_test.cpp' FILE */
