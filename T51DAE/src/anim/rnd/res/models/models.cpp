/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : model.cpp
 * PURPOSE     : Animation project.
 *               material sample module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 05.10.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "tigl.h"

tigl::model & tigl::model::CreateModel( const std::string &FileName )
{
  material *M;
  tigl::shader *shd;
  shd = Rnd->ShdCreate("model");
  M = Rnd->MtlCreate("Emerald", vec3(0.0215, 0.1745, 0.0215), vec3(0.07568, 0.61424, 0.07568), vec3(0.633, 0.727811, 0.633), 76.8, 1, shd);
  
  std::fstream f(FileName, std::fstream::in | std::fstream::binary);

  f.seekg(0, std::fstream::end);
  INT flen = (INT)f.tellg();
  f.seekg(0, std::fstream::beg);

  std::vector<BYTE> mem;
  mem.resize(flen);
  BYTE *ptr = mem.data();

  f.read((CHAR *)mem.data(), flen);

  rdr rd(ptr);

  DWORD sign;
  rd(&sign);
  if (sign != *(DWORD *)"G3DM")
  {
    delete &mem;
  }
  rd(&NumOfPrims);                                                                                                                                            

  INT NoofP = NumOfPrims, NoofM = 0, NoofT = 0;
  rd(&NoofM);
  rd(&NoofT);
  
  /* Load primitives */
  std::vector<INT> prims_mtl;
  prims_mtl.resize(NoofP);
  Prims.resize(NoofP);
  for (INT i = 0; i < NoofP; i++)
  {
    INT nv = 0, ni = 0;

    rd(&nv);
    rd(&ni);
    rd(&prims_mtl[i]);

    std::vector<vertex::vert> V;
    V.resize(nv);

    std::vector<INT> I;
    I.resize(ni);

    rd(&V[0], nv);
    rd(&I[0], ni);

    //for (INT j = 0; j < nv; j++)
    //{
    //  V[j].P = matr::Identity().VectorPointTransform(V[j].P);
    //  V[j].N = matr::Identity().TransformNormal(V[j].N);
    //}

    topology::trimesh T(V, I);
    
    Prims[i] = Rnd->PrimCreate<vertex::vert>(T);
  }
  /* Stored material structure */
  struct STORE_MATERIAL
  {
    CHAR Name[300]; // Material name

    /* Illumination coefficients */ 
    vec3 Ka, Kd, Ks; // Ambient, diffuse, specular coefficients
    FLT Ph;            // Phong power coefficient
    FLT Trans;         // Transparency factor
    INT Tex[8];        // Texture references

    // Shader string
    CHAR ShaderStr[300];
    INT Shader;        // Shader index (not used)
  }; /* End of 'STORE_MATERIAL' struct */
  
  STORE_MATERIAL * store_mtls;
  store_mtls = (STORE_MATERIAL *)ptr, ptr += sizeof(STORE_MATERIAL) * NoofM;

  std::vector<material *> mtls;
  mtls.resize(NoofM);
  for (INT i = 0; i < NoofM; i++)                 
  {
    mtls[i] = Rnd->MtlCreate(FileName + "::" + store_mtls[i].Name, store_mtls[i].Ka,store_mtls[i].Kd,store_mtls[i].Ks,store_mtls[i].Ph,store_mtls[i].Trans, shd);
  }

  std::vector<texture *> texs;
  texs.resize(NoofT);

  for (INT i = 0; i < NoofT; i++)                 
  {
    CHAR Name[300]; 
    INT W, H, C, size;
    rd(Name, 300);
    rd(&W);

    rd(&H); 
    rd(&C);
    
    size = W * H * C;
    BYTE *Data = new BYTE[size];
    rd(Data, size);
    
    texs[i] = Rnd->CreateTexture(FileName + "::" + store_mtls[i].Name, W, H, C, Data);
  }

  // Correct material texture references
  for (INT i = 0; i < NoofM; i++)
    for (INT t = 0; t < 8; t++)
      if (store_mtls[i].Tex[t] != -1)
        mtls[i]->Tex[t] = texs[store_mtls[i].Tex[t]];



  // Correct primitives material references
  for (INT i = 0; i < NoofP; i++)
    if (prims_mtl[i] != -1)
      Prims[i]->Mtl = mtls[prims_mtl[i]];

  return *this;
}

VOID tigl::model::ModelDraw( matr World )
{
  INT i;
  matr m = World;

  /* Draw all nontransparent primitives */ 
  for (i = 0; i < NumOfPrims; i++)
    Rnd->Draw(Prims[i], m);

}

/* END OF 'models.cpp' FILE */