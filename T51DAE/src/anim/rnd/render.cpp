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
 
#include "tigl.h"

#include <wglew.h>
#include <gl/wglext.h>

/* Debug output function.
 * ARGUMENTS:
 *   - source APi or device:
 *       UINT Source;
 *   - error type:
 *       UINT Type;
 *   - error message id:
 *       UINT Id, 
 *   - message severity:
 *       UINT severity, 
 *   - message text length:
 *       INT Length, 
 *   - message text:
 *       CHAR *Message, 
 *   - user addon parameters pointer:
 *       VOID *UserParam;
 * RETURNS: None.
 */
VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                             INT Length, const CHAR *Message,
                             const VOID *UserParam )
{
  INT len = 0;
  static CHAR Buf[10000];
 
  /* Ignore non-significant error/warning codes */
  if (Id == 131169 || Id == 131185 || Id == 131218 || Id == 131204)
    return;
  len += sprintf(Buf + len, "Debug message (%i) %s\n", Id, Message);
 
  switch (Source)
  {
  case GL_DEBUG_SOURCE_API:
    len += sprintf(Buf + len, "Source: API\n");
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    len += sprintf(Buf + len, "Source: Window System\n");
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    len += sprintf(Buf + len, "Source: Shader Compiler\n");
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    len += sprintf(Buf + len, "Source: Third Party\n");
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    len += sprintf(Buf + len, "Source: Application\n");
    break;
  case GL_DEBUG_SOURCE_OTHER:
    len += sprintf(Buf + len, "Source: Other\n");
    break;
  }
 
  len += sprintf(Buf + len, "\n");
 
  switch (Type)
  {
  case GL_DEBUG_TYPE_ERROR:
    len += sprintf(Buf + len, "Type: Error");
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    len += sprintf(Buf + len, "Type: Deprecated Behaviour");
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    len += sprintf(Buf + len, "Type: Undefined Behaviour");
    break; 
  case GL_DEBUG_TYPE_PORTABILITY:
    len += sprintf(Buf + len, "Type: Portability");
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    len += sprintf(Buf + len, "Type: Performance");
    break;
  case GL_DEBUG_TYPE_MARKER:
    len += sprintf(Buf + len, "Type: Marker");
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP:
    len += sprintf(Buf + len, "Type: Push Group");
    break;
  case GL_DEBUG_TYPE_POP_GROUP:
    len += sprintf(Buf + len, "Type: Pop Group");
    break;
  case GL_DEBUG_TYPE_OTHER:
    len += sprintf(Buf + len, "Type: Other");
    break;
  }
  len += sprintf(Buf + len, "\n");
 
  switch (Severity)
  {
  case GL_DEBUG_SEVERITY_HIGH:
    len += sprintf(Buf + len, "Severity: high");
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    len += sprintf(Buf + len, "Severity: medium");
    break;
  case GL_DEBUG_SEVERITY_LOW:
    len += sprintf(Buf + len, "Severity: low");
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    len += sprintf(Buf + len, "Severity: notification");
    break;
  }
 
  len += sprintf(Buf + len, "\n\n");
 
  OutputDebugString(Buf);
} /* End of 'glDebugOutput' function */

/* Inittialization render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::render::Init( VOID )
{
  INT i;
  UINT nums;
  PIXELFORMATDESCRIPTOR pfd = {0};
  HGLRC hRC;
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB */
    0
  };
  
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

  hGLRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hGLRC);

  /* Glew check */
  if (glewInit() != GLEW_OK)
    exit(0);

  wglSwapIntervalEXT(0);

  /* OpenGL parameters */
  wglChoosePixelFormatARB(hDC, PixelAttribs, NULL, 1, &i, &nums);
  hRC = wglCreateContextAttribsARB(hDC, NULL, ContextAttribs);

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(hGLRC);

  hGLRC = hRC;
  wglMakeCurrent(hDC, hGLRC);

#ifndef NDEBUG
  
  OutputDebugString((LPCSTR)glGetString(GL_VERSION));
  OutputDebugString("\n");
  OutputDebugString((LPCSTR)glGetString(GL_VENDOR));
  OutputDebugString("\n");
  OutputDebugString((LPCSTR)glGetString(GL_RENDERER));
  OutputDebugString("\n");

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(glDebugOutput, NULL);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE,
    0, NULL, GL_TRUE);
#endif /* NDEBUG */

  /* Create UBO buffers */
  PrimUboBuf = BufferCreate<buffer::ubo_prim>  (0);
  CamUboBuf  = BufferCreate<buffer::ubo_camera>(1);
  SyncUboBuf = BufferCreate<buffer::ubo_sync>  (2);
  
  /* Create sky sphere */
  SkyTex = CreateTexFromFile("bin/textures/sky10.bmp");

  /* GL parameters and enables */
  glClearColor(0.8, 0.37, 0.6, 1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);
  glEnable(GL_BLEND);            
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  Cam.Size = 0.1f;
  Cam.ProjDist = 1.0f;
  Cam.FarClip = 1200.0f;
  Cam.SetLocAtUp(vec3(30), vec3(0, 0, 0));
} /* End of 'tigl::render::Init' function */

/* Resize projection function.
 * ARGUMENTS: 
 *   - new frame parameters:
 *       INT NewFrameW, NewFrameH;
 * RETURNS: None.
 */
VOID tigl::render::Resize( INT NewFrameW, INT NewFrameH )
{
  Cam.Resize(NewFrameW, NewFrameH);
  glViewport(0, 0, NewFrameW, NewFrameH);
  tigl::buffer::ubo_camera Data;
  Data.CamDir   = vec4(Cam.Dir, 1);
  Data.CamLoc   = vec4(Cam.Loc, 1);
  Data.CamRight = vec4(Cam.Right, 1);
  Data.CamUp    = vec4(Cam.Up, 1);
  Data.MatrP    = Cam.Proj; 
  Data.MatrV    = Cam.View;
  Data.MatrVP   = Cam.VP;
  Data.FrameWHProjSizeDist = vec4(NewFrameW, NewFrameH, Cam.Size, Cam.ProjDist);
  CamUboBuf->Update(&Data);
} /* End of 'tigl::render::Resize' function */

/* Inittialization render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::render::FrameStart( VOID )
{
  tigl::buffer::ubo_camera Data;    
  Data.CamDir   = vec4(Cam.Dir, 1);
  Data.CamLoc   = vec4(Cam.Loc, 1);
  Data.CamRight = vec4(Cam.Right, 1);
  Data.CamUp    = vec4(Cam.Up, 1);
  Data.MatrP    = Cam.Proj; 
  Data.MatrV    = Cam.View;
  Data.MatrVP   = Cam.VP;
  Data.FrameWHProjSizeDist = vec4(Cam.FrameW, Cam.FrameH, Cam.Size, Cam.ProjDist);
  CamUboBuf->Update(&Data);
  tigl::shader_manager::UpdateShaders();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} /* End of 'tigl::render::FrameStart' function */

/* Inittialization render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::render::FrameEnd( VOID )
{
  glFinish();
  SwapBuffers(hDC);
} /* End of 'tigl::render::FrameEnd' function */

/* Primitive draw function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       prim *Pr;
 *   - transformation matrix:
 *       const matr &World;
 * RETURNS: None.
 */
VOID tigl::render::Draw( const prim *Pr, const matr &World )
{
  matr
    w = World * Pr->Transform,                                                                     
    winv = w.Inverse().Transpose(),
    wvp = w * Cam.VP;             
  
  INT gl_prim_type = Pr->Type == prim_type::TRIMESH ? GL_TRIANGLES :
                     Pr->Type == prim_type::STRIP ? GL_TRIANGLE_STRIP :
                     GL_POINTS;
               
  /* Primive UBO update */
  tigl::buffer::ubo_prim PrimData;
  PrimData.MatrW = w;
  PrimData.MatrWInv = winv;
  PrimData.MatrWVP = wvp;
  PrimUboBuf->Update(&PrimData);
  
  /* Vertex buffer update */
  Pr->UpdateVA();

  if (Pr->Mtl->Shd->ProgId == 0)
    return;

  /* Update material buffer and use program */
  Pr->Mtl->Apply();

  /* Init sky texture */
  glActiveTexture(GL_TEXTURE0 + 8);
  SkyTex->Apply();

  /* Draw */
  glBindVertexArray(Pr->VA);
  if (Pr->IBuf == 0)
    glDrawArrays(gl_prim_type, 0, Pr->NumOfElements);
  else
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(gl_prim_type, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
  glUseProgram(0);

} /* End of 'tigl::render::Draw' function */

/* END OF 'render.cpp' FILE */     