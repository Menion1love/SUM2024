/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_cam.h
 * PURPOSE     : Animation project.
 *               Camera declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_cam_h_
#define __mth_cam_h_

#include "mth_def.h"

/* Math library namespace */
namespace mth
{
  /* Space camera handle class */
  template<typename type>
    class camera
    {
    public:
      vec3<type>
        Loc,            // camera location
        Dir, Up, Right, // basis camera directions
        At;             // camera focused point    
      type
        ProjDist,       // near project plane distance
        FarClip,        // far project plane distance
        Size,           // inner project plane rectangle size
        Wp, Hp;         // project plane size
      INT
        FrameW, FrameH; // Camera frame size in pixels
      matr<type>
        View,           // view matrix
        Proj,           // projection matrix
        VP;             // View and Proj matrix production

      /* Default constructor */             
      camera( VOID ) :
        Loc(0, 0, 5), Dir(0, 0, -1), Up(0, 1, 0), Right(1, 0, 0), At(0, 0, 0),
        ProjDist(0.1), FarClip(500), Size(0.1), FrameW(30), FrameH(30)
      {
        UpdateProj();
      } /* End of 'camera' function */

      /* Set projection parameters function.
       * ARGUMENTS: 
       *   - new size of projection:
       *       type NewSize; 
       *   - new distance of projection:
       *       type NewProjDist;
       *   - new far clip of projection: 
       *       type NewFarClip;
       * RETURNS: 
       *   (camera) camera with new params.
       */
      camera & SetProj( type NewSize, type NewProjDist, type NewFarClip )
      {                                                                                                                                                                                           
        ProjDist = NewProjDist;
        Size = NewSize;
        FarClip = NewFarClip;

        UpdateProj();
        return *this;
      } /* End of 'SetProj' function */
       
      /* Set new frame size parameters function.
       * ARGUMENTS: 
       *   - new width and height of frame:
       *       INT NewFrameW, NewFrameH; 
       * RETURNS: 
       *   (camera) camera with new params.
       */
      camera & Resize( INT NewFrameW, INT NewFrameH )
      {
        FrameW = NewFrameW;
        FrameH = NewFrameH;
                      
        UpdateProj();
        return *this;
      } /* End of 'Resize' function */
      
      /* Set camera parameters function.
       * ARGUMENTS: 
       *   - look parameter:
       *       const vec3<type> &L; 
       *   - at parameter:
       *       const vec3<type> &A;
       *   - up parameter: 
       *       const vec3<type> &U;
       * RETURNS: 
       *   (camera) camera with new params.
       */
      camera & SetLocAtUp( const vec3<type> &L, const vec3<type> &A, const vec3<type> &U = vec3<type>(0, 1, 0))
      {
        matr<type> b;
        Loc = L;
        At = A;
        Up = U;
        Dir = (At - Loc).Normalizing();
        Right = (Dir % Up).Normalizing();
        Up = Right % Dir;
        View = b.View(Loc, Dir, Right, Up);
        UpdateProj();
        return *this;
      } /* End of 'SetLocAtUp' function */
      
    private:
      /* Update projection's parameters function.
       * ARGUMENTS: None. 
       * RETURNS: None. 
       */
      VOID UpdateProj( VOID )
      {
        matr<type> b;
        type rx = Size, ry = Size;
        if (FrameW > FrameH)
          rx *= (type)FrameW / FrameH;
        else
          ry *= (type)FrameH / FrameW;

        Proj = b.Frustum(-rx / 2, rx / 2, -ry / 2, ry / 2, ProjDist, FarClip);
        VP = View * Proj; 
      } /* End of 'UpdateProj' function */
    }; /* End of 'camera' class */
} /* end of 'mth' namespace */

#endif /* __mth_cam_h_ */

/* END OF 'mth_cam.h' FILE */