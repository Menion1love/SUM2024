/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : buffers.h
 * PURPOSE     : Animation project.
 *               Buffers declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 03.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __buffers_h_
#define __buffers_h_

#include "../resources_def.h"

/* Project namespace */
namespace tigl
{
  /* Primitive handle class */
  class buffer : public resource
  {
    friend class render;
  public:   
    /* UBO primitive representation type */
    class ubo_prim
    { 
    public:
      matr MatrWVP;
      matr MatrW;
      matr MatrWInv;
    };
    /* UBO primitive representation type */
    class ubo_camera
    { 
    public:
      matr MatrVP;
      matr MatrV;
      matr MatrP;
  
      vec4 CamLoc;
      vec4 CamRight;
      vec4 CamUp;
      vec4 CamDir;
      vec4 FrameWHProjSizeDist;
    };
    /* UBO primitive representation type */
    class ubo_sync
    { 
    public:
      vec4 TimeDeltaTimeGlobalTimeDeltaTime;
    };

    // OpenGL buffer Id
    UINT BufId = 0;

    // Binding point
    UINT BindingPoint = 0;
  
    // Number of buffer quads
    UINT BufSize = 0;

    /* Buffer create function.
     * ARGUMENTS:
     *   - buffer binding point:
     *       UINT BufBindingPoint;
     *   - buffer data:
     *       const data_type *Data;
     * RETURNS:
     *   (buffer &) self reference.
     */
    template<typename data_type>
      buffer & Create( UINT BufBindingPoint, const data_type *Data  = {} )
      {
        Free();
        BufSize = sizeof(data_type);
        if (BufSize == 0)
          return *this;

        BindingPoint = BufBindingPoint;

        glGenBuffers(1, &BufId);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, BufId);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(data_type), Data,
                     GL_DYNAMIC_DRAW);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        Apply();
        return *this;
      } /* End of 'Create' function */

    /* Buffer create function.
     * ARGUMENTS:
     *   - buffer binding point:
     *       UINT BufBindingPoint;
     *   - number of data elements:
     *       INT NumOfElements;
     *   - buffer data:
     *       const data_type *Data;
     * RETURNS:
     *   (buffer &) self reference.
     */
    template<typename data_type>
      buffer & Create( UINT BufBindingPoint, INT NumOfElements, 
                       const data_type *Data  = {} )
      {
//        Free();
        BufSize = sizeof(data_type) * NumOfElements;
        if (BufSize == 0)
          return *this;

        BindingPoint = BufBindingPoint;
        glGenBuffers(1, &BufId);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, BufId);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(data_type) * NumOfElements,
                     Data, GL_DYNAMIC_COPY);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        Apply();
        return *this;
      } /* End of 'Create' function */

    VOID Free( VOID )
    {
      glDeleteBuffers(1, &BufId);
    }

    /* Buffer update function.
     * ARGUMENTS:
     *   - buffer data:
     *       const data_type *Data;
     *   - start of elements update:
     *       INT Start;
     *   - length of elements, which will be updated:
     *       INT Size;
     * RETURNS: None.
     */
    template<typename data_type>
      VOID Update( const data_type *Data, INT Start = 0, INT Size = -1 )
      {  
        if (BufId == 0)
          return;
        if (Size < 0)
          Size = BufSize;
        if (Start < 0)
          Start = 0;
        if (Start + Size > BufSize)
          Size = BufSize - Start;
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, BufId);
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, Start, Size, Data);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
      } /* End of 'Update' finction */


    /* Apply buffer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Apply( VOID )
    {
      if (BufId != 0)
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BindingPoint, BufId);
    } /* End of 'Apply' function */
  };

  /* Shader manager */
  class buffer_manager : public resource_manager<buffer>
  {
    friend class render;
    buffer_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'buffer_manager' function */

  public:
  
    /* Create shader function.
     * ARGUMENTS:
     *   - shader file name prefix:
     *       const std::string &FileNamePrefix;
     * RETURNS:
     *   (shader *) created primitive interface.
     */
    template<typename data_type>
      buffer * BufferCreate( UINT BufBindingPoint, INT NumOfElements = -1, 
                       const data_type *Data = {} )
      {
        if (NumOfElements == -1)
          return resource_manager::Add(buffer().Create(BufBindingPoint, Data));
        return resource_manager::Add(buffer().Create(BufBindingPoint, NumOfElements, Data));
      } /* End of 'ShdCreate' function */

  }; /* End of 'buffer_manager' class */
} /* end of 'tigl' namespace */

#endif /* __buffers_h_ */

/* END OF 'buffers.h' FILE */ 

