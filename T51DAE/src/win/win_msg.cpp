/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : win_msg.cpp
 * PURPOSE     : Animation project.
 *               Message crackers windows module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "tigl.h"

/* WM_KEYDOWN window message handle function.
 * ARGUMENTS:
 *   - key data in wparam:
 *       WPARAM wParam;
 * RETURNS: None.
 */
VOID tigl::win::OnkeyDown( WPARAM wParam ) 
{
} /* End of 'tigl::win::OnKeyDown' function */

/* WM_KEYUP window message handle function.
 * ARGUMENTS:
 *   - key data in wparam:
 *       WPARAM wParam;
 * RETURNS: None.
 */
VOID tigl::win::OnKeyUp( WPARAM wParam )
{
} /* End of 'tigl::win::OnKeyUp' function */
  
/* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL tigl::win::OnCreate( CREATESTRUCT *CS )
{
  return TRUE;
} /* End of 'tigl::win::OnCreate' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::win::OnDestroy( VOID )
{
} /* End of 'tigl::win::OnDestroy' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT NewW, NewH;
 * RETURNS: None.
 */
VOID tigl::win::OnSize( UINT State, INT NewW, INT NewH )
{
} /* End of 'tigl::win::OnSize' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL tigl::win::OnEraseBkgnd( HDC hDC )
{
  return TRUE;
} /* End of 'tigl::win::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS:
 *   - window device context:
 *       HDC hDC;
 *   - paint message structure pointer:
 *       PAINTSTRUCT *PS;
 * RETURNS: None.
 */
VOID tigl::win::OnPaint( HDC hDC, PAINTSTRUCT *PS )
{
} /* End of 'tigl::win::OnPaint' function */ 

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
VOID tigl::win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{ 
} /* End of 'tigl::win::OnActivate' function */

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID tigl::win::OnTimer( INT Id ) 
{
} /* End of 'tigl::win::OnTimer' function */

/* WM_DROPFILES window message handle function.
 * ARGUMENTS:
 *   - handle to an internal structure describing the dropped files:
 *       HDROP hDrop;
 * RETURNS: None.
 */
VOID tigl::win::OnDropFiles( HDROP hDrop )
{
} /* End of 'tigl::win::OnDropFiles' function */

/* WM_NOTIFY window message handle function.
 * ARGUMENTS:
 *   - control identifier:
 *       INT Id;
 *   - notification header depended to control type:
 *       NMHDR *NoteHead;
 * RETURNS:
 *   (LRESULT) return value depended to notification.
 */
LRESULT tigl::win::OnNotify( INT Id, NMHDR *NoteHead )
{
  return 0;
} /* End of 'tigl::win::OnNotify' function */

/* WM_COMMAND window message handle function.
 * ARGUMENTS:
 *   - item (menu or accelerator) or control window identifier:
 *       INT Id;
 *   - control window handle:
 *       HWND hWndCtl;
 *   - notification: 0 - menu, 1 - accelerator, otherwise -
 *     depended to control (like BM_CLICKED):
 *       UINT CodeNotify;
 * RETURNS: None.
 */
VOID tigl::win::OnCommand( INT Id, HWND hWndCtl, UINT CodeNotify )
{
} /* End of 'tigl::win::OnCommand' function */

/* WM_DRAWITEM window message handle function.
 * ARGUMENTS:
 *   - control identifier (for menu - 0):
 *       INT Id;
 *   - draw item information structure pointer:
 *       DRAWITEMSTRUCT *DrawItem;
 * RETURNS: None.
 *   (LRESULT) return value depended to notification.
 */
VOID tigl::win::OnDrawItem( INT Id, DRAWITEMSTRUCT *DrawItem )
{
} /* End of 'tigl::win::OnDrawItem' function */

/* WM_HSCROLL message handle function.
 * ARGUMENTS:
 *   - handle of scroll window or nullptr for window scroll bars:
 *       HWND hWndCtl;
 *   - scrool bar request code (see SB_***):
 *       UINT Code;
 *   - schroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
 *       INT Pos;
 * RETURNS: None.
 */
VOID tigl::win::OnHScroll( HWND hWndCtl, UINT Code, INT Pos )
{
} /* End of 'tigl::win::OnHScroll' function */

/* WM_VSCROLL message handle function.
 * ARGUMENTS:
 *   - handle of scroll window or nullptr for window scroll bars:
 *       HWND hWndCtl;
 *   - scrool bar request code (see SB_***):
 *       UINT Code;
 *   - schroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
 *       INT Pos;
 * RETURNS: None.
 */
VOID tigl::win::OnVScroll( HWND hWndCtl, UINT Code, INT Pos )
{
} /* End of 'tigl::win::OnVScroll' function */

/* WM_MENUSELECT window message handle function.
 * ARGUMENTS:
 *   - handle of menu:
 *       HMENU hMenu;
 *   - submenu item ID or submenu index
 *       INT Item;
 *   - handle of popup menu if selected popup submenu:
 *       HMENU hMenuPopup;
 *   - menu item flags (see MF_***):
 *       UINT Flags;
 * RETURNS: None.
 */
VOID tigl::win::OnMenuSelect( HMENU hMenu, INT Item, HMENU hMenuPopup, UINT Flags )
{
} /* End of 'tigl::win::OnMenuSelect' function */

/* WM_INITMENUPOPUP window message handle function.
 * ARGUMENTS:
 *   - handle of popup menu:
 *       HMENU hMenu;
 *   - submenu item position:
 *       UINT Item;
 *   - window system menu flag:
 *       BOOL IsSystemMenu;
 * RETURNS: None.
 */
VOID tigl::win::OnInitMenuPopup( HMENU hMenu, UINT Item, BOOL IsSystemMenu )
{
} /* End of 'tigl::win::OnInitMenuPopup' function */

/* WM_EXITSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::win::OnExitSizeMove( VOID )
{
  IsInput = FALSE;
} /* End of 'tigl::win::OnExitSizeMove' function */

/* WM_MOUSEWHEEL window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse wheel relative delta value:
 *       INT Z;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID tigl::win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
  MouseWheel += Z;
} /* End of 'tigl::win::OnMouseWheel' function */
   
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
VOID tigl::win::OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys )
{
} /* End of 'tigl::win::OnButtonDown' function */

/* WM_LBUTTONUP, WM_RBUTTONUP, WM_MBUTTONUP,  window message handle function.
 * ARGUMENTS: 
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys; 
 * RETURNS: None.
 */
VOID tigl::win::OnButtonUp( INT X, INT Y, UINT Keys )
{
} /* End of 'tigl::win::OnButtonUp' function */

/* WM_EXITSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::win::OnMouseMove( INT X, INT Y, UINT Keys )
{
} /* End of 'tigl::win::OnMouseMove' function */

/* WM_ENTERSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::win::OnEnterSizeMove( VOID )
{
  IsInput = TRUE;
} /* End of 'tigl::win::OnEnterSizeMove' function */

/* Window message universal handle function.
 * Should be returned 'DefWindowProc' call result.
 * ARGUMENTS:
 *   - message type (see WM_***):
 *      UINT Msg;
 *   - message 'word' parameter:
 *      WPARAM wParam;
 *   - message 'long' parameter:
 *      LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
LRESULT tigl::win::OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam )
{
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'tigl::win::OnMessage' function */

/* Window dispatch run function 
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::win::Run( VOID ) 
{                   
  MSG msg;

  while (TRUE)
  {
    /* Check message at window message queue */
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      if (msg.message == WM_QUIT)
        break;
      else
      {
        /* Displatch message to window */
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    else
    {
      Idle();
    }
  }
} /* End of 'tigl::win::Run' function */
                     
/* END OF 'win_msg.cpp' FILE */
