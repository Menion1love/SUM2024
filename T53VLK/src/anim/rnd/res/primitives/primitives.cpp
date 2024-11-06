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

#include "tivk.h"

/* Free primitive function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::prim::Free( VOID )
{
  IndexBuffer->Free();
  VertexBuffer->Free();
  PrimBuf->Free();
  Mtl->Free();
  ZeroMemory(this, sizeof(this));
} /* End of 'tivk::prim::Free' function */

template <class vertex>
  tivk::prim & tivk::prim::Create( material *mtl, const topology::base<vertex> &T )
  {
    /* Set deafult parameters */
    Mtl = mtl;
    Transform = matr::Identity();
    NumOfElements = T.V.size();
    NumOfIndexes = T.I.size();

    /* Create vertex and index buffers */
    VertexBuffer = Rnd->BufferCreate(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, T.V.data(), NumOfElements);
    IndexBuffer = Rnd->BufferCreate(VK_BUFFER_USAGE_INDEX_BUFFER_BIT, T.I.data(), NumOfIndexes);

    tivk::buffer::ubo_prim PrimData {};

    PrimBuf = Rnd->BufferCreate<buffer::ubo_prim>(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, &PrimData);

    return *this;
  } /* End of 'Create' function */

/* Load model function.
 * ARGUMENTS:
 *   - pointer to material for model:
 *       material *mtl;
 *   - name of file with model:
 *       const CHAR *FileName ;
 * RETURNS:
 *   (prim *) created primitive interface.
 */
tivk::prim * tivk::primitive_manager::LoadModel( material *mtl, const CHAR *FileName )
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