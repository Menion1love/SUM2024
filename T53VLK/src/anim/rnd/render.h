/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : render.h
 * PURPOSE     : Animation project.
 *               Render declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 05.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __render_h_
#define __render_h_

#define VK_USE_PLATFORM_WIN32_KHR

#include <vulkan.h>

#include "res/resources.h"
#include "vlk/vlk_core.h"

/* Project namespace */
namespace tivk
{
  /* Render representation type */
  class render : public primitive_manager, public shader_manager, public material_manager, public buffer_manager, public texture_manager, public model_manager
  {
  private:
    HWND &hWnd;   /* Render window handle */

  public:
    std::string Path;
    vlk VlkCore;
    HDC hDC;     /* Work window memory device context */

    camera Cam;
    buffer *CamBuf;

    VkViewport Viewport {};
    VkRect2D Scissor {};

    /* Render constructor function.
     * ARGUMENTS:
     *   - windows context:
     *       HWND &WindowHandle;
     */
    render( HWND &WindowHandle ) : hWnd(WindowHandle), hDC(nullptr), buffer_manager(*this), shader_manager(*this),
      texture_manager(*this), material_manager(*this), primitive_manager(*this), model_manager(*this), VlkCore(hWnd)
    {
      CHAR Buf[1000];
      GetCurrentDirectory(sizeof(Buf), Buf);

      Path += Buf;
    } /* End of 'render' function */
    
    /* Inittialization render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID );

    /* Inittialization render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameStart( VOID );

    /* Inittialization render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameEnd( VOID );
    
    /* Resize projection function.
     * ARGUMENTS: 
     *   - new frame parameters:
     *       INT NewFrameW, NewFrameH;
     * RETURNS: None.
     */
    VOID Resize( INT NewFrameW, INT NewFrameH );

    /* Render destructor.
     * ARGUMENTS: None.
     */
    ~render( VOID )
    {
      VlkCore.Close();
      ReleaseDC(tivk::render::hWnd, hDC);
    } /* End of '~render' funcftion */

    /* Primitive draw function.
     * ARGUMENTS:
     *   - primitive pointer:
     *       prim *Pr;
     *   - transformation matrix:
     *       const matr &World;
     * RETURNS: None.
     */
    VOID Draw( const prim *Pr, const matr &World );

  }; /* End of 'render' class */
} /* end of 'tivk' namespace */

#endif /* __render_h_ */

/* END OF 'render.h' FILE */