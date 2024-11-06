/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : u_ctrl.cpp
 * PURPOSE     : Animation project.
 *               Unit sample control module.
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
  class u_control: public tivk::unit
  {
  public:

    /* Unit initialization function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     */
    u_control( anim *Ani )
    {
      /* Text handle */
    } /* End of 'u_control' function */

    /* Unit inter frame events handle function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani; ???
     * RETURNS: None.
     */
    VOID Response( anim *Ani ) override
    {
      if (Ani->Keys[VK_LSHIFT])
      {
        FLT Dist = !(Ani->Cam.At - Ani->Cam.Loc),
            cosT = (Ani->Cam.Loc.y - Ani->Cam.At.y) / Dist,
            sinT = sqrt(1 - cosT * cosT),
            plen = Dist * sinT,
            cosP = (Ani->Cam.Loc.z - Ani->Cam.At.z) / plen,
            sinP = (Ani->Cam.Loc.x - Ani->Cam.At.x) / plen,
            Azi = R2D(atan2(sinP, cosP)),
            Elev = R2D(atan2(sinT, cosT));
      
        Azi += Ani->GlobalDeltaTime * 3 * (-10.0 * Ani->Keys[VK_LBUTTON] * Ani->Mdx + 47.0 * (Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]));
 
        Elev += Ani->GlobalDeltaTime * 2 * (20.0 * Ani->Keys[VK_LBUTTON] * Ani->Mdy + 47.0 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]));

        if (Elev < 0.08)
           Elev = 0.08;
        else if (Elev > 178.90)
           Elev = 178.90;
 
        Dist += (1.0 + Ani->Keys[VK_RCONTROL] * -50.0) * (0.07 * Ani->Mdz + Ani->GlobalDeltaTime * 35.0 * (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR]));

        if (Dist < 0.1)
          Dist = 0.1;

        /* Camera handle */
        if (Ani->Keys[VK_RBUTTON])
        {
          FLT Wp, Hp, sx, sy;
          vec3 dv;

          Wp = Ani->Cam.Size;
          Hp = Ani->Cam.Size;
          if (Ani->Cam.FrameW > Ani->Cam.FrameH)
            Wp *= (FLT)Ani->Cam.FrameW / Ani->Cam.FrameH;
          else
            Hp *= (FLT)Ani->Cam.FrameH / Ani->Cam.FrameW;
       
          sx = -Ani->Mdx * Wp / Ani->Cam.FrameW * Dist / Ani->Cam.ProjDist;
          sy = Ani->Mdy * Hp / Ani->Cam.FrameH * Dist / Ani->Cam.ProjDist;
      
          dv = Ani->Cam.Right * sx + Ani->Cam.Up * sy;
          Ani->Cam.At = Ani->Cam.At + dv;
          Ani->Cam.Loc = Ani->Cam.Loc + dv;
        }

        /* Camera set */
        Ani->Cam.SetLocAtUp((matr::RotateX(Elev) * matr::RotateY(Azi) *matr::Translate(Ani->Cam.At)).VectorPointTransform(vec3(0, Dist, 0)),
                  Ani->Cam.At);
        //std::cout << "CamLoc: ";
        //Ani->Cam.Loc.show();   
        //std::cout << " CamAt: ";
        //Ani->Cam.At.show();
        //std::cout << std::endl;
      }
      
      if (Ani->Keys[VK_ESCAPE])
        Ani->AnimExit(); 
      if (Ani->KeysClick[VK_F11])
        Ani->FlipFullScreen();
    } /* End of 'Response' function */
 
    /* Unit render function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani; ???
     * RETURNS: None.
     */
    VOID Render( anim *Ani ) override
    { 
    } /* End of 'Render' function */
    
    /* Unit initialization function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     */
    ~u_control( VOID ) override
    {
    } /* End of '~u_control' function */
  }; /* End of 'u_control' class */
} /* end of 'tivk' namespace*/

/* Register unit to stock by name */
static tivk::anim::unit_register<tivk::u_control> _("Control");

/* END OF 'u_ctrl.cpp' FILE */
