/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : anim.cpp
 * PURPOSE     : Animation project.
 *               Animation main handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 01.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#include "tigl.h"

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID tigl::anim::OnTimer( INT Id )
{
  Render(); 
} /* End of 'tigl::anim::OnTimer' function */ 

 /* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL tigl::anim::OnCreate( CREATESTRUCT *CS ) 
{
  SetTimer(win::hWnd, 47, 0, nullptr);
  tigl::render::Init();
  return TRUE;
} /* End of 'tigl::anim::OnCreate' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::anim::OnDestroy( VOID ) 
{
  KillTimer(win::hWnd, 47);
} /* End of 'tigl::anim::OnDestroy' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL tigl::anim::OnEraseBkgnd( HDC hDC ) 
{
  return TRUE;
} /* End of 'tigl::anim::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS:
 *   - window device context:
 *       HDC hDC;
 *   - paint message structure pointer:
 *       PAINTSTRUCT *PS;
 * RETURNS: None.
 */
VOID tigl::anim::OnPaint( HDC hDC, PAINTSTRUCT *Ps ) 
{                           
} /* End of 'tigl::anim::OnPaint' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT NewW, NewH;
 * RETURNS: None.
 */
VOID tigl::anim::OnSize( UINT State, INT NewW, INT NewH )
{
  tigl::render::Resize(NewW, NewH);
} /* End of 'tigl::anim::OnSize' function */

/* WM_ACTIVATE window message handle function.
 * ARGUMENTS:
 *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
 *       UINT Reason;
 *   - handle of active window:
 *       HWND hWndActDeact;
 *   - minimized flag:
 *       BOOL IsMinimized;
 * RETURNS: None.
 */
VOID tigl::anim::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized ) 
{
  SetActiveWindow(win::hWnd);
  SetForegroundWindow(win::hWnd); 
  SetFocus(win::hWnd);
  if (Reason == WA_INACTIVE)
  {
    IsActive = FALSE;
    IsInput = FALSE;
  }
  else
  {
    IsActive = TRUE;
    IsInput = TRUE;
  }
} /* End of 'tigl::anim::OnActivate' function */

 /* WM_LBUTTONDOWN, WM_RBUTTONDOWN, WM_MBUTTONDOWN window message handle function.
 * ARGUMENTS: 
 *   - was it double click or not
 *       BOOL IsDoubleClick;
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys; 
 * RETURNS: None.
 */
VOID tigl::anim::OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys ) 
{
} /* End of 'tigl::anim::OnButtonDown' function */

/* WM_LBUTTONUP, WM_RBUTTONUP, WM_MBUTTONUP,  window message handle function.
 * ARGUMENTS: 
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys; 
 * RETURNS: None.
 */
VOID tigl::anim::OnButtonUp( INT X, INT Y, UINT Keys ) 
{
} /* End of 'tigl::anim::OnButtonUp' function */

/* Render pipeline animation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::anim::Render( VOID )
{
  tigl::timer::Response();

  tigl::buffer::ubo_sync Sync;
 
  Sync.TimeDeltaTimeGlobalTimeDeltaTime = vec4(Time, DeltaTime, GlobalTime, GlobalDeltaTime);
  SyncUboBuf->Update(&Sync);

  if (IsActive)
    tigl::input::Response(MouseWheel);

  Units.Walk([&]( unit *Uni )
  {
    Uni->Response(this);
  });

  tigl::render::FrameStart();

  Units.Walk([&]( unit *Uni )
  {
    Uni->Render(this);
  });                   

  tigl::render::FrameEnd();
} /* End of 'tigl::anim::Render' function */
    
/* Exit animation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::anim::AnimExit( VOID )
{
  SendMessage(win::hWnd, WM_DESTROY, 0, 0);
} /* End of 'tigl::anim::AnimExit' function */
  
/* END OF 'anim.cpp' FILE */     