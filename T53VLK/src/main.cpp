/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : main.cpp
 * PURPOSE     : Animation project.
 *               Main startup module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 27.10.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "tivk.h"

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                    CHAR *CmdLine, INT CmdShow )
{
  /* Create console */
  AllocConsole();
  SetConsoleTitle("lol");
  HWND hCnsWnd = GetConsoleWindow();
  RECT rc;
  GetWindowRect(hCnsWnd, &rc);
  MoveWindow(hCnsWnd, 102, 0, 800, 300, TRUE);
  std::freopen("CONOUT$", "w", stdout);
  system("@chcp 1251 > nul");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xfc);

  /* Catch mem hooks */
  SetDbgMemHooks();

  std::vector<std::thread> Ths;
  
  for (INT i = 0; i < 1; i++)
    Ths.push_back(std::thread([hInstance]( VOID )
    {
      tivk::anim MyAnim1;
      MyAnim1 << "Control" << "Model" << "TexSample";
      MyAnim1.Run();
    }));
  for (auto &t : Ths)
    t.join();

  /* Create animation */
} /* End of 'WinMain' function */

/* END OF 'main.cpp' FILE */

    