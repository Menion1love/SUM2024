/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : shaders.cpp
 * PURPOSE     : Animation project.
 *               Shaders handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 05.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "tigl.h"

/* Save text to log file function.
 * ARGUMENTS:
 *   - text 1 to save:
 *       const std::string &Stage;
 *   - text 2 to save:
 *       const std::string &Text;
 * RETURNS: None.
 */
VOID tigl::shader::Log( const std::string &Stage, const std::string &Text )
{
  std::ofstream("bin/shaders/~SHD{tigl}30.LOG", std::ios_base::app) <<
    Name << "\n" << Stage << ":\n" << Text << "\n";
} /* End of 'tigl::shader::Log' function */

/* Load text from file function.
 * ARGUMENTS:
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) loaded text (allocated through 'malloc') or NULL (if error is occured).
 */
std::string tigl::shader::LoadTextFromFile( const std::string &FileName )
{
  std::fstream F;

  F.open(FileName, std::fstream::in);

  return std::string((std::istreambuf_iterator<char>(F)),
                 std::istreambuf_iterator<char>());
} /* End of 'tigl::shader::LoadTextFromFile' function */

/* Free shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::shader::Free( VOID )
{
  UINT shds[5] {};
  INT n, i;

  if (ProgId == 0 || !glIsProgram(ProgId))
    return;
  glGetAttachedShaders(ProgId, 5, &n, shds);

  /* Delete shaders */
  for (i = 0; i < n; i++)
    if (shds[i] != 0 && glIsShader(shds[i]))
    {
      glDetachShader(ProgId, shds[i]);
      glDeleteShader(shds[i]);
    }

  /* Delete program */
  glDeleteProgram(ProgId);
  ProgId = 0;
} /* End of 'tigl::shader::Free' function */

/* Load shader function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (shader &) self reference.
 */
tigl::shader & tigl::shader::LoadShader( VOID )
{
  INT prg = 0, txt_common_size = 0, bufline_size = 0;
  std::string txt {}, com_df{}, com_df_li{};
  BOOL isok = TRUE;

  struct
  {
    std::string Name;   /* Shader name */
    INT Type;     /* Shader OpenGL type (see GL_***_SHADER) */
    std::string Define; /* Mandatory define and shader version */
    INT Id;       /* Result shader OpenGL Id */
  } shds[] =
  {
    {("vert"), GL_VERTEX_SHADER,          ("#version 460\n#define VERTEX_SHADER 1\n")},
    {("frag"), GL_FRAGMENT_SHADER,        ("#version 460\n#define FRAGMENT_SHADER 1\n")},
    {("geom"), GL_GEOMETRY_SHADER,        ("#version 460\n#define GEOMETRY_SHADER 1\n")},
    {("ctrl"), GL_TESS_CONTROL_SHADER,    ("#version 460\n#define TESS_CONTROL_SHADER 1\n")},
    {("eval"), GL_TESS_EVALUATION_SHADER, ("#version 460\n#define TESS_EVALUATION_SHADER 1\n")},
  };
  INT i, res, NoofS = sizeof(shds) / sizeof(shds[0]);
  std::string Buf1[300], BufLine[10][102], Buf[3000];

   
  //com_df_li = "#line 1 \"commondf.glsl\"\n";     
  com_df = LoadTextFromFile("bin/shaders/includes/commondf.glsl");
  /* Skip '#version' line */
  for (i = 0; i < NoofS; i++)
  {
    txt.clear();             
    txt += shds[i].Define;                                                    
    txt += com_df;
    txt += ("\n#line 1 \"" +  Name + ("/") + shds[i].Name + (".glsl") + "\"\n");
    txt += LoadTextFromFile(("bin/shaders/") + Name + ("/") + shds[i].Name + (".glsl"));
    
    if (txt.c_str() == (shds[i].Define + com_df + "\n#line 1 \"" +  Name + ("/") + shds[i].Name + (".glsl") + "\"\n"))
    {
      if (i >= 2)
        continue;
      Log(shds[i].Name, "Error load file");
      isok = FALSE;
      break;
    }
    /* Create shader */
    if ((shds[i].Id = glCreateShader(shds[i].Type)) == 0)
    {
      Log(shds[i].Name, "Error shader creation");
      isok = FALSE;
      break;
    }
    /* Send text to shader for compile */
    /* Attach text to shader  */
    const CHAR *Src[] = {txt.c_str()};
    glShaderSource(shds[i].Id, 1, Src, nullptr);
    
    /* Compile shader */
    glCompileShader(shds[i].Id);
    glGetShaderiv(shds[i].Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      CHAR Deb[3000];

      glGetShaderInfoLog(shds[i].Id, sizeof(Buf), &res, Deb);
      Log(shds[i].Name, Deb);
      isok = FALSE;
      break;
    }
  }

  /* Create program */
  if (isok)
    if ((prg = glCreateProgram()) == 0)
    {
      
      Log(shds[i].Name, reinterpret_cast<GLchar *>(Buf));
      Log("PROG", "Error program creation");
      isok = FALSE;
    }
    else
    {
      /* Attach shaders to program */
      for (i = 0; i < NoofS; i++)
        if (shds[i].Id != 0)
          glAttachShader(prg, shds[i].Id);

      /* Link program */
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        CHAR Deb[3000];

        glGetProgramInfoLog(prg, sizeof(Buf), &res, Deb);
        Log("PROG", Deb);
        isok = FALSE;
      }
    }

  if (!isok)
  {
    /* Handle errors */

    /* Delete shaders */
    for (i = 0; i < NoofS; i++)
      if (shds[i].Id != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shds[i].Id);
        glDeleteShader(shds[i].Id);
      }
    /* Delete program */
    if (prg != 0)
      glDeleteProgram(prg);
    prg = 0;
  }               
  this->ProgId = prg;
  UpdateInfo();

  
  return *this;
} /* End of 'tigl::shader::LoadShader' function */

/* Update shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::shader::Update( VOID )
{
  static BOOL A = FALSE, B = FALSE;

  if (Watcher.IsChanged())
  {
      Free();
      LoadShader();
      Watcher.StartWatch("bin/shaders/" + Name);
  }
} /* End of 'tigl::shader::Update' function */

/* Update shader internal data info function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tigl::shader::UpdateInfo( VOID )
{
  static std::map<INT, std::tuple<std::string, INT, BOOL, INT>> attr_types
  {
    {GL_FLOAT, {"float", 1, TRUE, 0}},
    {GL_FLOAT_VEC2, {"vec2", 2, TRUE, 0}},
    {GL_FLOAT_VEC3, {"vec3", 3, TRUE, 0}},
    {GL_FLOAT_VEC4, {"vec4", 4, TRUE, 0}},
    {GL_FLOAT_MAT2, {"mat2", 4, TRUE, 2}},
    {GL_FLOAT_MAT3, {"mat3", 9, TRUE, 3}},
    {GL_FLOAT_MAT4, {"mat4", 16, TRUE, 4}},
    {GL_FLOAT_MAT2x3, {"mat2x3", 6, TRUE, 2}},
    {GL_FLOAT_MAT2x4, {"mat2x4", 8, TRUE, 2}},
    {GL_FLOAT_MAT3x2, {"mat3x2", 6, TRUE, 3}},
    {GL_FLOAT_MAT3x4, {"mat3x4", 12, TRUE, 3}},
    {GL_FLOAT_MAT4x2, {"mat4x2", 8, TRUE, 4}},
    {GL_FLOAT_MAT4x3, {"mat4x3", 12, TRUE, 4}},
    {GL_INT, {"int", 1, FALSE, 0}},
    {GL_INT_VEC2, {"ivec2", 2, FALSE, 0}},
    {GL_INT_VEC3, {"ivec3", 3, FALSE, 0}},
    {GL_INT_VEC4, {"ivec4", 4, FALSE, 0}},
    {GL_UNSIGNED_INT, {"uint", 1, FALSE, 0}},
    {GL_UNSIGNED_INT_VEC2, {"uvec2", 2, FALSE, 0}},
    {GL_UNSIGNED_INT_VEC3, {"uvec3", 3, FALSE, 0}},
    {GL_UNSIGNED_INT_VEC4, {"uvec4", 4, FALSE, 0}},
  };

  // <functional>
  std::vector<std::tuple<INT,
                         std::function<INT( INT, const CHAR * )>,
                         std::function<VOID( UINT, UINT, INT, INT *, INT *,
                                             GLenum *, CHAR * )>,
                         std::map<std::string, ATTR_INFO>&>> data
  {
    {GL_ACTIVE_ATTRIBUTES, glGetAttribLocation, glGetActiveAttrib, Attributes},
    {GL_ACTIVE_UNIFORMS, glGetUniformLocation, glGetActiveUniform, Uniforms},
  };

  // Fill shader attributes/uniforms info
  for (auto d : data)
  {
    INT Count;
    glGetProgramiv(ProgId, std::get<0>(d), &Count);
    std::get<3>(d).clear();
    for (INT i = 0; i < Count; i++)
    {
      CHAR name[300];
      INT size;
      GLenum type;

      std::get<2>(d)(ProgId, i, sizeof(name), nullptr, &size, &type, name);
      auto attr_info = attr_types[type];
      INT loc = std::get<1>(d)(ProgId, name);

      std::get<3>(d)[name] =
      {
        std::get<0>(attr_info),
        std::get<1>(attr_info),
        std::get<2>(attr_info),
        std::get<3>(attr_info),
        loc
      };
    }
  }

  INT CountSSBO;
  glGetProgramInterfaceiv(ProgId, GL_SHADER_STORAGE_BLOCK, GL_ACTIVE_RESOURCES,
                          &CountSSBO);
  SSBOBuffers.clear();
  for (INT i = 0; i < CountSSBO; i++)
  {
    CHAR name[300];
    glGetProgramResourceName(ProgId, GL_SHADER_STORAGE_BLOCK,
                             i, sizeof(name), nullptr, name);
    INT idx = glGetProgramResourceIndex(ProgId, GL_SHADER_STORAGE_BLOCK, name);

    GLenum prop[] {GL_BUFFER_BINDING};
    INT bind;
    glGetProgramResourceiv(ProgId, GL_SHADER_STORAGE_BLOCK,
                           idx, 1, prop, 1, NULL, &bind);
    SSBOBuffers[name] = {name, idx, bind};
  }
  
  INT CountUniformBlocks;                                                      
  glGetProgramiv(ProgId, GL_ACTIVE_UNIFORM_BLOCKS, &CountUniformBlocks);       
  std::map<std::string, std::tuple<std::string, INT, INT, INT>> Blocks;        
  for (INT i = 0; i < CountUniformBlocks; i++)                                 
  {                                                                            
    CHAR name[300];                                                            
    glGetActiveUniformBlockName(ProgId, i, sizeof(name), nullptr, name);       
                                                                               
    INT idx = glGetUniformBlockIndex(ProgId, name);                            
    INT size;                                                                  
    glGetActiveUniformBlockiv(ProgId, idx, GL_UNIFORM_BLOCK_DATA_SIZE, &size); 
    INT bind;                                                                  
    glGetActiveUniformBlockiv(ProgId, idx, GL_UNIFORM_BLOCK_BINDING, &bind);   
    Blocks[name] = {name, idx, size, bind};                                    
  }                                                                            
} /* End of 'tigl::shader::UpdateInfo' function */

/* END OF 'shaders.cpp' FILE */ 
