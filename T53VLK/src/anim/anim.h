/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : anim.h
 * PURPOSE     : Animation project.
 *               Animation declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 05.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __anim_h_
#define __anim_h_

#include "win/win.h"
#include "input/input.h"
#include "input/timer.h"      
#include "rnd/render.h"                                          
#include "units/unit.h"

/* Project namespace */
namespace tivk
{
  /* Animation representation type */
  class anim : public win, public input, public timer, public unit, public render
  {
  private:
    /* Animation units stock */
    stock<unit *> Units;
  public:

    /* Class constructor */
    anim( VOID ) : win(), input(win::hWnd), render(win::hWnd)  
    {
      tivk::win::Create();
    } /* End of 'anim' function */

    /* Class destructor */
    ~anim( VOID )
    {
      /* Delete all system units */
      Units.Walk([]( unit *Uni )
      {
        delete Uni;
      });
    } /* End of '~anim' function */

    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    VOID OnTimer( INT Id ) override;

    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID OnSize( UINT State, INT NewW, INT NewH ) override;

    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    BOOL OnCreate( CREATESTRUCT *CS ) override;
  
    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnDestroy( VOID ) override;
  
    /* WM_ERASEBKGND window message handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS:
     *   (BOOL) TRUE if background is erased, FALSE otherwise.
     */
    BOOL OnEraseBkgnd( HDC hDC ) override;
    
    /* WM_PAINT window message handle function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     *   - paint message structure pointer:
     *       PAINTSTRUCT *PS;
     * RETURNS: None.
     */
    VOID OnPaint( HDC hDC, PAINTSTRUCT *Ps ) override;

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
    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized ) override;

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
    VOID OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys ) override;
  
    /* WM_LBUTTONUP, WM_RBUTTONUP, WM_MBUTTONUP,  window message handle function.
     * ARGUMENTS: 
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys; 
     * RETURNS: None.
     */
    VOID OnButtonUp( INT X, INT Y, UINT Keys ) override;

    /* Render animation function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID );
    
    /* Exit animation function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID AnimExit( VOID );
 
    /* Simple unit add to stock by name function.
     * ARGUMENTS:
     *   - name of unit to add:
     *       const std::string &UnitName;                 
     * RETURNS:
     *   (anim) anim with new stock params.
     */
    anim & operator<<( const std::string &UnitName )
    {
      if (UnitNames.find(UnitName) != UnitNames.end())
        *this << UnitNames[UnitName](this);
      return *this;
    } /* End of 'operator<<' function */

    /* Simple unit add to stock function.
     * ARGUMENTS:
     *   - unit to add:
     *       unit *Uni;                 
     * RETURNS:
     *   (anim) anim with new stock.
     */
    anim & operator<<( unit *Uni )
    {
      Units << Uni;
      return *this;
    } /* End of 'operator<<' function */

//    static std::map<const std::string, unit * (*)( VOID )> UnitNames;
    inline static std::map<const std::string, unit * ((*)( anim *Ani ))> UnitNames;

    /* Unit register representation type */
    template<typename unit_type>
      class unit_register
      {
      private:
        /* Create unit for register function.
         * ARGUMENTS: None.
         * RETURNS:
         *   (unit *) pointer to unit.
         */
        static unit * Create( anim *Ani )
        {
          return new unit_type(Ani); 
        } /* End of 'Create' function */

      public:
        /* Register unit to stock function.
         * ARGUMENTS: 
         *   - name of unit to register:
         *       const std::string &UnitName
         */
        unit_register( const std::string &UnitName )
        {
          UnitNames[UnitName] = Create;
        } /* End of 'unit_register' function */
      }; /* End of 'unit_register' class */
  }; /* End of 'anim' class */
} /* end of 'tivk' namespace */

#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */