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
 
#include "tivk.h"

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID tivk::anim::OnTimer( INT Id )
{
  Render(); 
} /* End of 'tivk::anim::OnTimer' function */ 

 /* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL tivk::anim::OnCreate( CREATESTRUCT *CS ) 
{
  SetTimer(win::hWnd, 47, 0, nullptr);
  tivk::render::Init();
  return TRUE;
} /* End of 'tivk::anim::OnCreate' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::anim::OnDestroy( VOID ) 
{
  KillTimer(win::hWnd, 47);
} /* End of 'tivk::anim::OnDestroy' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL tivk::anim::OnEraseBkgnd( HDC hDC ) 
{
  return TRUE;
} /* End of 'tivk::anim::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS:
 *   - window device context:
 *       HDC hDC;
 *   - paint message structure pointer:
 *       PAINTSTRUCT *PS;
 * RETURNS: None.
 */
VOID tivk::anim::OnPaint( HDC hDC, PAINTSTRUCT *Ps ) 
{
} /* End of 'tivk::anim::OnPaint' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT NewW, NewH;
 * RETURNS: None.
 */
VOID tivk::anim::OnSize( UINT State, INT NewW, INT NewH )
{
  tivk::render::Resize(NewW, NewH);
} /* End of 'tivk::anim::OnSize' function */

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
VOID tivk::anim::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized ) 
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
} /* End of 'tivk::anim::OnActivate' function */

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
VOID tivk::anim::OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys ) 
{
} /* End of 'tivk::anim::OnButtonDown' function */

/* WM_LBUTTONUP, WM_RBUTTONUP, WM_MBUTTONUP,  window message handle function.
 * ARGUMENTS: 
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys; 
 * RETURNS: None.
 */
VOID tivk::anim::OnButtonUp( INT X, INT Y, UINT Keys ) 
{
} /* End of 'tivk::anim::OnButtonUp' function */

/* Render pipeline animation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::anim::Render( VOID )
{
  tivk::timer::Response();


  if (IsActive)
    tivk::input::Response(MouseWheel);

  Units.Walk([&]( unit *Uni )
  {
    Uni->Response(this);
  });

  tivk::render::FrameStart();

  Units.Walk([&]( unit *Uni )
  {
    Uni->Render(this);
  });

  tivk::render::FrameEnd();
} /* End of 'tivk::anim::Render' function */
    
/* Exit animation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::anim::AnimExit( VOID )
{
  SendMessage(win::hWnd, WM_DESTROY, 0, 0);
} /* End of 'tivk::anim::AnimExit' function */
  
/* END OF 'anim.cpp' FILE */     