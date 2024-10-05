/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : primitives.cpp
 * PURPOSE     : Animation project.
 *               Primitives handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 05.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "tigl.h"

/* Update primitive vertex array function.
 * ARGUMENTS: None.
 * RETURNS: Non.
 */
VOID tigl::prim::UpdateVA( VOID ) const
{
  if (Mtl == nullptr || Mtl->Shd == nullptr)
    return;
  if (IsVAUpdated)
    return;
  IsVAUpdated = TRUE;

  // Activate vertex array
  glBindVertexArray(VA);
  // Activate vertex buffer
  glBindBuffer(GL_ARRAY_BUFFER, VBuf);

  // Setup data order due to vertex map
  for (auto &a : VertexMap)
    if (auto attr = Mtl->Shd->Attributes.find(a.first); attr != Mtl->Shd->Attributes.end())
    {
      glEnableVertexAttribArray(attr->second.Loc);
      /*                    layout,
       *                      components count,
       *                          type
       *                                    should be normalize,
       *                                           vertex structure size in
       *                                           bytes (stride),
       *                                               offset in bytes to
       *                                               field start */
      glVertexAttribPointer(attr->second.Loc,
                            attr->second.Components,
                            attr->second.IsFloat ? GL_FLOAT : GL_INT,
                            FALSE,
                            VertexStride,
                            reinterpret_cast<VOID *>((UINT_PTR)a.second));
    }
  // Disable vertex array
  glBindVertexArray(0);
} /* End of 'tigl::prim::UpdateVA' function */

/* Free primitive function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       prim *Pr;
 * RETURNS: None.
 *   (prim *) created primitive interface.
 */
VOID tigl::prim::Free( VOID )
{
  glBindVertexArray(VA);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &VBuf);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &VA);
  glDeleteBuffers(1, &IBuf);                   
  ZeroMemory(this, sizeof(this));
} /* End of 'tigl::prim::Free' function */


/* Load model function.
 * ARGUMENTS:
 *   - pointer to material for model:
 *       material *mtl;
 *   - name of file with model:
 *       const CHAR *FileName ;
 * RETURNS:
 *   (prim *) created primitive interface.
 */
tigl::prim * tigl::primitive_manager::LoadModel( material *mtl, const CHAR *FileName )
{
  FILE *F;
  std::vector<vertex::vert> V;
  std::vector<INT> I;
  INT size;
  INT nv = 0, nf = 0;
  static CHAR Buf[10000];

  if ((F = fopen(FileName, "r")) == nullptr)
    return nullptr;

  /* Count vertices and indices */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0;
      CHAR *ptr = Buf + 2, old = ' ';

      while (*ptr != 0)
        n += *ptr != ' ' && old == ' ', old = *ptr++;
      nf += n - 2;
    }

  size = sizeof(vertex::vert) * nv + sizeof(INT) * nf * 3;
  
  /* Read model data */
  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      FLT x, y, z;

      sscanf(Buf + 2, "%f %f %f", &x, &y, &z);
      nv++;
      V.push_back({{x, y, z}, {0, 0}, {0, 0, 0}, {0, 0, 0, 0}});
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, c = 0, c0 = 0, c1 = 0, c2 = 0;
      CHAR *ptr = Buf + 2, old = ' ';

      while (*ptr != 0)
      {
        if (*ptr != ' ' && old == ' ')
        {
          sscanf(ptr, "%d", &c);
          if (c < 0)
            c = nv + c;
          else
            c--;

          if (n == 0)
            c0 = c;
          else if (n == 1)
            c1 = c;
          else
          {
            nf += 3;
            /* add new triangle */
            I.push_back(c0);
            I.push_back(c1);
            I.push_back(c);
            c1 = c;
          }
          n++;
        }
        old = *ptr++;
      }
    }
  fclose(F);
  topology::trimesh<vertex::vert> T(V, I);
  T.EvalNormals();
  return PrimCreate(T, mtl);
} /* End of 'LoadModel' function */

/* END OF 'primitives.cpp' FILE */