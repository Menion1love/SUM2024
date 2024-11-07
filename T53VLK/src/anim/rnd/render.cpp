/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : render.cpp
 * PURPOSE     : Animation project.
 *               Render handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 31.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#include "tivk.h"

/* Inittialization render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::render::Init( VOID )
{
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};
  
  /* Create context */
  hDC = GetDC(hWnd);

  /* Pfd initialization */
  pfd.nSize =  sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(hDC, &pfd);
  
  DescribePixelFormat(hDC, i, sizeof(pfd),&pfd);
  SetPixelFormat(hDC, i, &pfd);

  /* Camaera parameters */
  Cam.Size = 0.1f;
  Cam.ProjDist = 1.0f;
  Cam.FarClip = 1200.0f;
  Cam.SetLocAtUp(vec3(30), vec3(0, 0, 0));

  VlkCore.Init();
  buffer::ubo_camera Data {};

  Data.MatrP = matr::Identity();
  Data.MatrV = matr::Identity();
  Data.MatrVP = matr::Identity();

  CamBuf = BufferCreate<buffer::ubo_camera>(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, &Data, 1, 2);

  Viewport = VkViewport
  {
    .x = 0,
    .y = static_cast<FLT>(VlkCore.FrameH),
    .width = static_cast<FLT>(VlkCore.FrameW),
    .height = -static_cast<FLT>(VlkCore.FrameH),
    .minDepth = 0,
    .maxDepth = 1,
  };
  Scissor = VkRect2D
  {
    .offset = {0, 0},
    .extent = {VlkCore.FrameW, VlkCore.FrameH}
  };
} /* End of 'tivk::render::Init' function */

/* Resize projection function.
 * ARGUMENTS: 
 *   - new frame parameters:
 *       INT NewFrameW, NewFrameH;
 * RETURNS: None.
 */
VOID tivk::render::Resize( INT NewFrameW, INT NewFrameH )
{
  Cam.Resize(NewFrameW, NewFrameH);
  VlkCore.ResizeSwapchain(NewFrameW, NewFrameH);
} /* End of 'tivk::render::Resize' function */

/* Inittialization render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::render::FrameStart( VOID )
{
  VlkCore.BeginRenderPass();
  Viewport = VkViewport
  {
    .x = 0,
    .y = static_cast<FLT>(VlkCore.FrameH),
    .width = static_cast<FLT>(VlkCore.FrameW),
    .height = -static_cast<FLT>(VlkCore.FrameH),
    .minDepth = -1,
    .maxDepth = 1,
  };
  Scissor = VkRect2D
  {
    .offset = {0, 0},
    .extent = {VlkCore.FrameW, VlkCore.FrameH}
  };
  vkCmdSetViewport(VlkCore.CommandBuffer, 0, 1, &Viewport);
  vkCmdSetScissor(VlkCore.CommandBuffer, 0, 1, &Scissor);

  
  buffer::ubo_camera Data
  {
    .MatrVP   = Cam.VP,
    .MatrV    = Cam.View,
    .MatrP    = Cam.Proj, 
    .CamLoc   = vec4(Cam.Loc, 1),
    .CamRight = vec4(Cam.Right, 1),
    .CamUp    = vec4(Cam.Up, 1),
    .CamDir   = vec4(Cam.Dir, 1),
    .FrameWHProjSizeDist = vec4(Cam.FrameW, Cam.FrameH, Cam.Size, Cam.ProjDist),
  };

  CamBuf->UpdateBuffer(&Data);
  VlkCore.UpdateDescriptorSet(CamBuf);

} /* End of 'tivk::render::FrameStart' function */

/* Inittialization render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::render::FrameEnd( VOID )
{
  VlkCore.EndRenderPass();
} /* End of 'tivk::render::FrameEnd' function */

/* Primitive draw function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       prim *Pr;
 *   - transformation matrix:
 *       const matr &World;
 * RETURNS: None.
 */
VOID tivk::render::Draw( const prim *Pr, const matr &World )
{
  matr
    w = World * Pr->Transform,
    winv = w.Inverse().Transpose(),
    wvp = w * Cam.VP;
  
  /* Primive UBO update */
  tivk::buffer::ubo_prim PrimData {wvp, w, winv};

  Pr->PrimBuf->UpdateBuffer(&PrimData);

  VlkCore.UpdateDescriptorSet(Pr->PrimBuf);

  vkCmdBindPipeline(VlkCore.CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, Pr->Mtl->Shd->Pipeline);
  VkDeviceSize p[] = {0};

  vkCmdBindDescriptorSets(VlkCore.CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, Pr->Mtl->Shd->PipelineLayout, 0, 1, &VlkCore.DescriptorSet, 0, nullptr);

  vkCmdBindVertexBuffers(VlkCore.CommandBuffer, 0, 1, &Pr->VertexBuffer->Buffer, p);
  if (Pr->NumOfIndexes == 0)
    vkCmdDraw(VlkCore.CommandBuffer, Pr->NumOfElements, 1, 0, 0);
  else
  {
    vkCmdBindIndexBuffer(VlkCore.CommandBuffer, Pr->IndexBuffer->Buffer, p[0], VK_INDEX_TYPE_UINT32);
    vkCmdDrawIndexed(VlkCore.CommandBuffer, Pr->NumOfIndexes, 1, 0, 0, 0);
  }
} /* End of 'tivk::render::Draw' function */

/* END OF 'render.cpp' FILE */
