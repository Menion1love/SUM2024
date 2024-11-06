/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : u_test.cpp
 * PURPOSE     : Animation project.
 *               Test unit sample module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 01.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
                 
#include "tivk.h"

/* Project namespace */
namespace tivk
{
  class u_sky : public tivk::unit
  {
  public:
    tivk::material *M;
    tivk::prim *pr; 
    tivk::shader *shd;
    /* Unit initialization function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     */
    u_sky( anim *Ani )
    {
      const std::vector<INT> ind;

      const std::vector<vertex::vert> v = {{ {1, 1, 1}, {1, 1}, {1, 1, 1}, {1, 1, 1, 1} }};

      topology::base<vertex::vert> T(prim_type::POINTS, v, ind);
      image Image("bin/textures/sky10.bmp");

      VkImage a;
      VkImageView b; 
      VkDeviceMemory m;
      Ani->VlkCore.ImageCreate(a, b, m, Image.W, Image.H, 1, 0, 
        , VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, Image.Pixels.data(), Image.Pixels.size(), 1); 
      Ani->VlkCore.UpdateDescriptorSet(Ani->VlkCore.Stage);
      shd = Ani->ShdCreate("skysphere");
      M = Ani->MtlCreate("Emerald", vec3(0.0215, 0.1745, 0.0215), vec3(0.07568, 0.61424, 0.07568), vec3(0.633, 0.727811, 0.633), 76.8, 1, shd, {});
      pr = Ani->PrimCreate(T, M);
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
      Ani->Draw(pr, matr::Scale(vec3(0.08)) * matr::RotateY(Ani->Time * 45));
    } /* End of 'Render' function */
    
    /* Unit initialization function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     */
    ~u_sky( VOID ) override
    {
    } /* End of '~u_test' function */
  }; /* End of 'u_test' class */
} /* end of 'tivk' namespace*/

/* Register unit to stock by name */
static tivk::anim::unit_register<tivk::u_sky> _("Sky");

/* END OF 'u_test.cpp' FILE */
