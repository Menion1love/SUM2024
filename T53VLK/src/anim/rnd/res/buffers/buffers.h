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
namespace tivk
{
  /* Primitive handle class */
  class buffer : public resource
  {
  private:
    friend class render;
    
    /* Allocated mamory for buffer */
    VkDeviceMemory Memory;   
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

    // Material buffer data type
    struct BUF_MTL
    {
      vec4 Ka;       // Ambient
      vec4 KdTrans;  // Diffuse + Transparency
      vec4 KsPh;     // Specular + Phong
      BOOL Tex[8] {};
    }; /* End of 'BUF_MTL' structure */
    
    // Core of vulkan buffer
    VkBuffer Buffer;

    // Buffers's binding point in shader
    INT BindingPoint;
    
    VkBufferUsageFlags UsageFlag;

    // Number of buffer quads
    UINT BufSize = 0;

    /* Buffer create function.
     * ARGUMENTS:
     *   - buffer usage flag:
     *       VkBufferUsageFlags Flags;
     *   - buffer data:
     *       const data_type *Data;
     *   - number of data elements:
     *       INT NumOfElements;
     * RETURNS:
     *   (buffer &) self reference.
     */
    buffer & CreateBuffer( VkBufferUsageFlags Flags, INT Size, const INT *Data = {} );

    buffer & UpdateBufferLow( const INT *Data = {}, INT NumOfElements = 1 );

    template <class type_data>
      buffer * UpdateBuffer( const type_data *Data = {}, INT NumOfElements = 1 )
        {
          INT *Pointer = new INT[BufSize];
          memcpy(Pointer, Data, BufSize);

          UpdateBufferLow(Pointer, BufSize);

          delete[] Pointer;
          return this;
        } /* End of 'BufferCreate' function */

    VOID Free( VOID );
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
    template <class type_data>
      buffer * BufferCreate( VkBufferUsageFlags Flags, 
                         const type_data *Data = {}, INT NumOfElements = 1, INT Binding = 0 )
        {
          buffer *b = resource_manager::Add(buffer());

          b->BindingPoint = Binding;
          b->UsageFlag = Flags;
          UINT Size = sizeof(type_data) * NumOfElements;
          INT *Pointer = new INT[Size];
          memcpy(Pointer, Data, Size);

          b->CreateBuffer(Flags, Size, Pointer);

          delete[] Pointer;
          return b;
        } /* End of 'BufferCreate' function */


  }; /* End of 'buffer_manager' class */
} /* end of 'tivk' namespace */

#endif /* __buffers_h_ */

/* END OF 'buffers.h' FILE */ 

