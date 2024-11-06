/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : model.cpp
 * PURPOSE     : Animation project.
 *               material sample module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 22.10.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "tivk.h"

class str
{
public:
  const CHAR* Ptr;

  str( const CHAR* NewStr = nullptr )  : Ptr(NewStr)
  {    
  }    
       
  str( const  str&  NewStr ) : Ptr (NewStr.Ptr)
  {    
  }    
       
  str( str && NewStr )  noexcept : Ptr (NewStr.Ptr)
  {
    NewStr.Ptr = nullptr;
  }

  ~str( VOID ) noexcept
  {
  }

  str & operator=( const str& NewStr )
  {
    Ptr = NewStr.Ptr;
    return *this;
  }

  str& operator=( const CHAR* NewStr )
  {
    Ptr = NewStr;
    return *this;
  }

  const str operator<( const CHAR* NewStr )
  {
    return *this;
  }

  const str operator<<( const CHAR* NewStr )
  {
    return *this;
  }

};

/* Expand hash function for 'str' string type */
template <>
/* 'hash' specialization for 'str' */
struct std::hash<str>
{
  /* Hash evaluation for 'str' type function.
   * ARGUMENTS:
   *   - string value:
   *       const str &Key;
   * RETURNS:
   *   (size_t) result hash value.
   */
  UINT operator()( const str& Key ) const noexcept
  {
#if defined(_WIN64)
    constexpr UINT _FNV_offset_basis = 14695981039346656037ULL;
    constexpr UINT _FNV_prime = 1099511628211ULL;
#else // defined(_WIN64)
    constexpr UINT _FNV_offset_basis = 2166136261U;
    constexpr UINT _FNV_prime = 16777619U;
#endif // defined(_WIN64)
    UINT val{ _FNV_offset_basis };
    if (Key.Ptr == nullptr)
      return val;
    for (UINT i = 0; i < 262144 && Key.Ptr[i] != 0; i++)
    {
      val ^= static_cast<UINT>(Key.Ptr[i]);
      val *= _FNV_prime;
    }
    return val;
  } /* End of 'operator()' function */
}; /* End of 'hash' structure */

namespace tivk 
{
  /* Tag represenation type */
  class tag
  {
  public:
    /* Name of tag */
    str Name;

    /* Self close tag's flag */
    INT IsSelfClose = 0;

    /* Map of all tag's arguments*/
    std::map<UINT, str> args;

    /* Inner tags */
    std::vector<tag> tags;

    /* Tag's content */
    str content;

    ~tag(VOID)
    {
      tags.clear();
      args.clear();
    }

  }; /* End of 'tag' class */

  /* Xml class */
  class xml
  {
  private:
  public:
    /* File text */
    CHAR* txt;

    /* Len of xml file */
    INT len;

    /* Source of xml (Header tag COLLADA) */
    tag Source;
    /* Xml constructor function.
     * ARGUMENTS:
     *   - file name for open:
     *       std::string Name;
     */
    xml( VOID ) : txt(nullptr), len(0)
    {
    } /* End of 'xml' function */

    VOID ParseNode( tag *Node )
    {
      while (TRUE)
      {
        CHAR* Cur = &*txt++;

        if ((*Cur >= '0' && *Cur <= '9') || (*Cur >= 'A' && *Cur <= 'Z') || (*Cur >= 'a' && *Cur <= 'z') || *Cur == '-')
        {
          ParseData(Node, Cur);
          while (*txt++ != '>')
            ;
          break;
        }
        else if (*Cur == '<')
        {
          CHAR* Next = &*txt++;

          if (*Next != '/')
          {
            tag n;

            ParseTag(&n, Next);

            if (!n.IsSelfClose)
              ParseNode(&n);

            Node->tags.push_back(n);
          }
          else
          {
            while (*txt++ != '>') 
              ;
            break;
          }
        }
      }
    }

    VOID ParseData( tag *Tag, CHAR *First )
    {
      CHAR Cur;

      while (TRUE)
      {
        Cur = *txt;
        if (Cur == '<')
        {
          *txt = 0;
          break;
        }
        else
          *txt++;
      }
      *txt = 0;

      Tag->content = First;
    }

    VOID ParseTag( tag *Tag, CHAR *First )
    {
      CHAR Cur = 0;

      if (First == nullptr)
        First = &*txt++;

      while (TRUE)
      {
        Cur = *txt;
        if (Cur == '>' || Cur == ' ')
        {
          *txt = 0;
          break;
        }
        else
          *txt++;
      }

      Tag->Name = First;

      if (Cur == '>')
        return;

      Cur = *txt++;
      while (Cur != '>')
      {
        std::hash<str> tmp;

        CHAR* F, * S;

        F = &*txt;
        while (TRUE)
        {
          Cur = *txt;
          if (Cur == '=')
          {
            *txt = 0;
            break;
          }
          else
            *txt++;
        }
        Cur = *txt++;

        if (Cur != '"')
        {
          Cur = *txt++;
          S = &*txt;
          while (TRUE)
          {
            Cur = *txt;
            if (Cur == '"')
            {
              *txt = 0;
              break;
            }
            else
              *txt++;
          }

          Cur = *++txt;

          if (Cur == '/')
          {
            Tag->IsSelfClose = 1;
            Tag->args.insert({ tmp(str(F)), S });
            break;
          }
          Tag->args.insert({ tmp(str(F)), S });
        }
        else
        {
          Cur = *txt++;

          if (Cur == '/')
          {
            Tag->IsSelfClose = 1;
            Tag->args.insert({ tmp(str(F)), nullptr });
            break;
          }
          Tag->args.insert({ tmp(str(F)), nullptr });
        }
      }
    }

    VOID ReadXML( std::string FileName )
    {
      CHAR Cur = 0, Sign[2], Next = 0;
      std::ifstream XmlFile;

      XmlFile.open(FileName, std::ios_base::binary);
      if (!XmlFile.is_open())
      {
        std::cout << "File not opened" << std::endl;
        return;
      }

      XmlFile.seekg(0, std::fstream::end);
      len = XmlFile.tellg();
      XmlFile.seekg(0, std::fstream::beg);

      XmlFile.read((CHAR*)&Sign, 2);
      if (Sign[0] == '<' && Sign[1] == '?')
      {
        INT nlen = 3;
        while (Cur != '>')
          XmlFile.read((CHAR*)&Cur, 1), nlen++;
        len -= nlen;
        txt = new CHAR[len];
        XmlFile.read(txt, len);
      }
      else
      {
        txt = new CHAR[len];
        XmlFile.seekg(0, std::fstream::beg);
        XmlFile.read(txt, len);
      }
      while (*txt++ != '<')
        ;
      ParseTag(&Source, nullptr);
      ParseNode(&Source);
    }
  }; /* End of 'xml' class */
}

tivk::model & tivk::model::CreateModelDae( const std::string& FileName )
{
  material* M;
  tivk::shader* shd;
  shd = Rnd->ShdCreate("model");
  M = Rnd->MtlCreate("Emerald", vec3(0.0215, 0.1745, 0.0215), vec3(0.07568, 0.61424, 0.07568), vec3(0.633, 0.727811, 0.633), 76.8, 1, shd);
  xml m;
  tag n;
  INT npr = 0;
  std::hash<str> tmp;

  struct DaeMtl
  {
    /* ID of dae material */
    const CHAR *id;

    /* Url to effect */
    const CHAR *Url;

    /* Phong coefficients */
    vec4 Ka, Kd, Ks;
    FLOAT Ph;
    INT Trans;

    texture *Tex;

    const CHAR *TexName;
  };
  
  m.ReadXML(FileName);

  std::vector<DaeMtl> Mtls;

  for (INT i = 0; i < m.Source.tags.size(); i++)
    if (strcmp(m.Source.tags[i].Name.Ptr, "library_materials") == 0)
    { 
      n = m.Source.tags[i];
      break;
    }

  for (auto mtl : n.tags)
  {
    DaeMtl CurMtl {};
    
    auto a = mtl.args.find(tmp(str("id")));
    const CHAR* id = a->second.Ptr;

    CurMtl.id = id;
    
    auto b = mtl.tags[0].args.find(tmp(str("url")));
    const CHAR* url = b->second.Ptr + 1;

    CurMtl.Url = url;

    Mtls.push_back(CurMtl);
  }

  for (INT i = 0; i < m.Source.tags.size(); i++)
    if (strcmp(m.Source.tags[i].Name.Ptr, "library_effects") == 0)
    {
      n = m.Source.tags[i];
      break;
    }

  for (auto eff : n.tags)
  {
    auto a = eff.args.find(tmp(str("id")));
    const CHAR* id = a->second.Ptr;

    for (INT i = 0; i < Mtls.size(); i++)
    {
      if (strcmp(Mtls[i].Url, id) == 0)
      {
        for (auto params : eff.tags[0].tags)
        {
          if (strcmp(params.Name.Ptr, "technique") == 0)
          {
            for (auto coef : params.tags[0].tags)
            {
              if (strcmp(coef.tags[0].Name.Ptr, "color") == 0)
              {
                const CHAR * t = coef.tags[0].content.Ptr;
                INT i = 0;
                vec4 data {};

                while (TRUE)
                {
                  CHAR* err;
                  FLOAT
                    x = strtod(t, &err);
                  
                  data.x = x;

                  if (err == nullptr || err == t)
                    break;
                  t = err;

                  x = strtod(t, &err);
                  
                  data.y = x;

                  if (err == nullptr || err == t)
                    break;
                  t = err;

                  x = strtod(t, &err);
                  
                  data.z = x;

                  if (err == nullptr || err == t)
                    break;
                  t = err;

                  x = strtod(t, &err);
                  
                  data.w = x;

                  if (err == nullptr || err == t)
                    break;
                  break;
                }

                if (strcmp(coef.Name.Ptr, "ambient") == 0)
                  Mtls[i].Ka.x = data.x, Mtls[i].Ka.y = data.y, Mtls[i].Ka.z = data.z;
                else if (strcmp(coef.Name.Ptr, "diffuse") == 0)     
                  Mtls[i].Kd.x = data.x, Mtls[i].Kd.y = data.y, Mtls[i].Kd.z = data.z;
                else if (strcmp(coef.Name.Ptr, "specular") == 0)    
                  Mtls[i].Ks.x = data.x, Mtls[i].Ks.y = data.y, Mtls[i].Ks.z = data.z;
                else if (strcmp(coef.Name.Ptr, "transparency") == 0)
                  Mtls[i].Trans = data.z;
                else if (strcmp(coef.Name.Ptr, "shininess") == 0)
                  Mtls[i].Ph = data.x;
              }
            }
          }
          if (strcmp(params.Name.Ptr, "newparam") == 0)
          {
            auto a = params.args.find(tmp(str("sid")));
            const CHAR* sid = a->second.Ptr;
            tag t = params.tags[0];

            if (strcmp(t.Name.Ptr, "surface") == 0)
              Mtls[i].TexName = params.tags[0].tags[0].content.Ptr;
          }
        }
      }
    }  
  }

  //for (INT i = 0; i < m.Source.tags.size(); i++)
  //  if (strcmp(m.Source.tags[i].Name.Ptr, "library_images") == 0)
  //  {
  //    n = m.Source.tags[i];
  //    break;
  //  }
  //
  //for (auto im : n.tags)
  //{
  //  auto a = im.args.find(tmp(str("id")));
  //  const CHAR* id = a->second.Ptr;
  //  
  //  for (INT i = 0; i < Mtls.size(); i++)
  //  {
  //    if (Mtls[i].TexName != nullptr)
  //      if (strcmp(Mtls[i].TexName, id) == 0)
  //        Mtls[i].Tex = Rnd->CreateTexFromFile(im.tags[0].content.Ptr);
  //  }
  //}




  for (INT i = 0; i < m.Source.tags.size(); i++)
    if (strcmp(m.Source.tags[i].Name.Ptr, "library_geometries") == 0)
    {
      n = m.Source.tags[i];
      break;
    }

  /* Geometry represenataion type */
  struct Geometry
  {
    /* Hashtag name */
    const CHAR* Name;

    /* Geometry data (in floats) */
    std::vector<vec4> Data4;
    std::vector<vec3> Data3;
    std::vector<vec2> Data2;

    INT IsVertexSem = 0;
    INT Offset;

    enum semantic : INT
    {
      POSITION = 0,
      NORMAL = 1,
      TEXCOORD = 2,
      COLOR = 3,
      REP = -1,
    };

    semantic type;

    /* Count of data */
    INT Count;

    /* Stratight for data */
    INT Stride;
  }; /* End of 'Geometry' struct */

  for (auto geoms : n.tags)
  {
    std::vector<Geometry> geom;

    for (auto mesh : geoms.tags[0].tags)
    {
      if (strcmp(mesh.Name.Ptr, "source") == 0)
      {
        tag
          fltarr = mesh.tags[0],
          acs = mesh.tags[1].tags[0];
        Geometry g;

        auto a = acs.args.find(tmp(str(" stride")));
        g.Stride = strtod(a->second.Ptr, nullptr);

        auto b = acs.args.find(tmp(str(" count")));
        g.Count = strtod(b->second.Ptr, nullptr);

        auto c = mesh.args.find(tmp(str("id")));
        g.Name = c->second.Ptr;

        const CHAR* t = fltarr.content.Ptr;

        if (g.Stride == 2)
          while (TRUE)
          {
            CHAR* err;
            FLOAT
              x = strtod(t, &err);

            t = err;
            FLOAT
              y = strtod(t, &err);
            
            if (err == nullptr || err == t)
              break;

            t = err;
            g.Data2.push_back(vec2(x, y));
          }
        else if (g.Stride == 3)
          while (TRUE)
          {
            CHAR* err;
            FLOAT
              x = strtod(t, &err);

            t = err;
            FLOAT
              y = strtod(t, &err);
            
            t = err;
            FLOAT 
              z = strtod(t, &err);
            
            if (err == nullptr || err == t)
              break;
            
            t = err;
            g.Data3.push_back(vec3(x, y, z));
          }
        else
          while (TRUE)
          {
            CHAR* err;
            FLOAT x = strtod(t, &err);
            t = err;
            FLOAT y = strtod(t, &err);
            t = err;
            FLOAT z = strtod(t, &err);
            t = err;
            FLOAT w = strtod(t, &err);
            
            if (err == nullptr || err == t)
              break;

            t = err;
            g.Data4.push_back(vec4(x, y, z, w));
          }
        geom.push_back(g);
      }
      else if (strcmp(mesh.Name.Ptr, "vertices") == 0)
      {
        INT IsTexCoord = 0, IsColor = 0;;
        for (auto inps : mesh.tags)
        {
          std::hash<str> tmp;
          
          Geometry::semantic tip = Geometry::POSITION;

          auto a = inps.args.find(tmp(str("semantic")));
          const CHAR* sem = a->second.Ptr;

          if (strcmp(sem, "POSITION") == 0)
            tip = Geometry::POSITION;
          else if (strcmp(sem, "NORMAL") == 0)
            tip = Geometry::NORMAL;
          else if (strcmp(sem, "COLOR") == 0)
            tip = Geometry::COLOR;
          else if (strcmp(sem, "TEXCOORD") == 0)
            tip = Geometry::TEXCOORD;

          auto b = inps.args.find(tmp(str(" source")));
          const CHAR* sour = b->second.Ptr + 1;

          for (INT g = 0; g < geom.size(); g++)
            if (strcmp(sour, geom[g].Name) == 0)
            {
              if ((tip == Geometry::TEXCOORD && IsTexCoord) || (tip == Geometry::COLOR && IsColor))
              {
                geom[g].type = Geometry::REP, geom[g].IsVertexSem = 1;
                break;
              }
              
              if (tip == Geometry::COLOR)
                IsColor = 1;
              if (tip == Geometry::TEXCOORD)
                IsTexCoord = 1;

              geom[g].type = tip, geom[g].IsVertexSem = 1;
              break;
            }
        }
      }
      else if (strcmp(mesh.Name.Ptr, "triangles") == 0)
      {
        INT IsTexCoord = 0, IsColor = 0;
        for (auto inps : mesh.tags)
        {
          if (strcmp(inps.Name.Ptr, "p") == 0)
          {
            const CHAR* t = inps.content.Ptr;
            
            std::vector<vertex::vert> vertexes;
            std::vector<INT> indices;
            
            INT m = geom[0].Offset;

            for (INT ma = 1; ma < geom.size(); ma++)
              if (m < geom[ma].Offset)
                m = geom[ma].Offset;

            while (TRUE)
            {
              CHAR *err = nullptr;
              vertex::vert v {};
              INT end = 0;

              for (INT j = 0; j < m + 1; j++)
              {
                INT x = strtod(t, &err);
              
                if (err == nullptr || err == t)
                {
                  end = 1;
                  break;
                }
                t = err;

                for (INT g = 0; g < geom.size(); g++)
                {
                  if (j == geom[g].Offset)
                    switch (geom[g].type)
                    {
                    case Geometry::POSITION:
                      v.P = geom[g].Data3[x];
                      break;
                    case Geometry::NORMAL:
                      v.N = geom[g].Data3[x];
                      break;
                    case Geometry::COLOR:
                      v.C = geom[g].Data4[x];
                      break;
                    case Geometry::TEXCOORD:
                      v.T = geom[g].Data2[x];
                      break;
                    case Geometry::REP:
                      break;
                    }
                }
              }
              if (end)
                break;
    
              vertexes.push_back(v);
            }

            auto MtName = mesh.args.find(tmp(str("material")));
            const CHAR* MtlName = MtName->second.Ptr;
              
            for (auto Mt : Mtls)
              if (strcmp(Mt.id, MtlName) == 0)
              {
                M = Rnd->MtlCreate(MtlName,
                  vec3(Mt.Ka.x, Mt.Ka.y, Mt.Ka.z),
                  vec3(Mt.Kd.x, Mt.Kd.y, Mt.Kd.z),
                  vec3(Mt.Ks.x, Mt.Ks.y, Mt.Ks.z),
                  Mt.Ph, Mt.Trans, shd);
              }
            topology::trimesh T(vertexes, indices);
            std::cout << vertexes.size() << " " << indices.size() << std::endl;
            prim *pr = Rnd->PrimCreate<vertex::vert>(T);
            pr->Mtl = M;
            this->Prims.push_back(pr);
          }
          else
          { 
            std::hash<str> tmp;

            auto a = inps.args.find(tmp(str("semantic")));
            const CHAR* sem = a->second.Ptr;

            auto b = inps.args.find(tmp(str(" source")));
            const CHAR* sour = b->second.Ptr + 1;

            auto c = inps.args.find(tmp(str(" offset")));
            INT off = strtod(c->second.Ptr, nullptr);

            if (strcmp(sem, "VERTEX") == 0)
            {
              for (INT g = 0; g < geom.size(); g++)
                if (geom[g].IsVertexSem)
                  geom[g].Offset = off;
            }
            else
            {
              Geometry::semantic tip = Geometry::POSITION;

              if (strcmp(sem, "POSITION") == 0)
                tip = Geometry::POSITION;
              else if (strcmp(sem, "NORMAL") == 0)
                tip = Geometry::NORMAL;
              else if (strcmp(sem, "COLOR") == 0)
                tip = Geometry::COLOR;
              else if (strcmp(sem, "TEXCOORD") == 0)
                tip = Geometry::TEXCOORD;

              for (INT g = 0; g < geom.size(); g++)
                if (strcmp(sour, geom[g].Name) == 0)
                {
                  geom[g].Offset = off;
                  if ((tip == Geometry::TEXCOORD && IsTexCoord) || (tip == Geometry::COLOR && IsColor)) 
                  {
                    geom[g].type = Geometry::REP;
                    break;
                  }
                  if (tip == Geometry::COLOR)
                    IsColor = 1;
                  if (tip == Geometry::TEXCOORD)
                    IsTexCoord = 1;

                  geom[g].type = tip;
                  break;
                }
            }
          }
        }
      }
    }
   }
  this->NumOfPrims = this->Prims.size();
  this->Trans = matr::Identity();
  return *this;
}

tivk::model & tivk::model::CreateModel( const std::string &FileName )
{
  material *M;
  tivk::shader *shd;
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

VOID tivk::model::ModelDraw( matr World )
{
  INT i;
  matr m = World;

  /* Draw all nontransparent primitives */ 
  for (i = 0; i < NumOfPrims; i++)
    Rnd->Draw(Prims[i], m);

}

/* END OF 'models.cpp' FILE */