/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_core.h
 * PURPOSE     : Animation project.
 *               Vulkan core declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 27.10.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __vlk_core_h_
#define __vlk_core_h_

#include "def.h"


/* Project namespace */
namespace tivk
{
  /* Vulkan representation type */
  class vlk 
  {
  private:
    /* Referens to window */
    HWND &hWndRef;

  public:
    /* Frame sizes */
    uint32_t FrameW, FrameH; 

    /* Vulkan window instance */
    VkInstance Instance {};

    /* Vulkan surface */
    VkSurfaceKHR Surface {};

    /* Physical device */
    VkPhysicalDevice PhysDevice {};

    /* Current logical device */
    VkDevice Device {};

    /* Current device */
    VkSwapchainKHR Swapchain {};

    /* Vulkan depth image */
    VkImage DepthImage;

    /* Vulkan depth image view */
    VkImageView DepthImageView;
    
    /* Vulkan debug */
    VkDebugUtilsMessengerEXT DebugExt;

    /* Swapchain images */
    std::vector<VkImageView> SwapchainImageViews;

    /* Vulkan frame buffers */  
    std::vector<VkFramebuffer> FrameBuffers {}; 

    /* Vulkan render pass */  
    VkRenderPass RenderPass {};

    /* Vilkan queues */
    VkQueue GraphicsQueue {};
    
    /* Transfer queue */
    VkQueue TransferQueue {};

    /* Graphics sampler */
    VkSampler GraphicsSampler {};
    
    /* Cubemap sampler */
    VkSampler CubemapSampler {};

    /* Command pool */
    VkCommandPool CommandPool {};
    
    /* Command buffer */
    VkCommandBuffer CommandBuffer {};
    
    /* Command buffer */
    VkCommandBuffer TransferCommandBuffer {};

    VkFence Fence {};

    VkShaderModule ShaderModule {};

    uint32_t RenderInd = 0;

    /* VUlkan descriptor set */
    VkDescriptorSet DescriptorSet {};

    VkDescriptorSetLayout DescriptorSetLayout {};

    buffer *Stage {};

    /* Default constructor */
    vlk( HWND &hWnd ) : hWndRef(hWnd)
    {
    } /* End of 'vlk' function */
    
    struct queue_family_indices
    {
      UINT32 GraphicsFamily;
      UINT32 PresentFamily;
    };

    queue_family_indices GetQueueFamilyIndices( VkPhysicalDevice PhysicalDevice )
    {
      UINT32 QueueFamilyCount = 0;

      vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyCount, nullptr);
      std::vector<VkQueueFamilyProperties> QueueFamilyProperties {QueueFamilyCount};
      vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyCount, QueueFamilyProperties.data());

      queue_family_indices Indices {};
      for (UINT32 i = 0; i < QueueFamilyCount; i++)
      {
        if ((QueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0)
          Indices.GraphicsFamily = i;
    
        VkBool32 PresentSupport = VK_FALSE;
        vkGetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice, i, Surface, &PresentSupport);
        if (PresentSupport == VK_TRUE)
          Indices.PresentFamily = i;
      }

      return Indices;
    }

    /* Creating vulkan instance function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID CreateInstance( VOID );

    /* Creating vulkan device function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID CreateDevice( VOID );
    
    /* Creating vulkan physical device function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID CreatePhysDevice( VOID );
    
    /* Creating vulkan surface function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID CreateSurface( VOID );
    
    /* End vulkan render pass function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID EndRenderPass( VOID );
    
    /* Create descriptor set function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID CreateDescriptorSet( VOID );
    
    /* Create descriptor set function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID UpdateDescriptorSet( buffer *Buf );

    /* Update descriptor set with buffer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID UpdateDescriptorSet( texture *Tex );

    /* Vulkan image creation function.
     * ARGUMENTS:
     *   - vulkan image handle output reference:
     *       VkImage &Image;
     *   - vulkan image view handle output reference:
     *       VkImageView &ImageView;
     *   - vulkan image memory handle output reference:
     *       VkDeviceMemory &Memory;
     *   - image size:
     *       INT W, H;
     *   - image color flag (otherwise Image is depth buffer):
     *       BOOL IsColor,
     *   - cube map flag (create 6 layers and 'PixelData' contain 6 joined same size images):
     *       BOOL IsCube,
     *   - vulkan image Format (see VK_FORMAT_***):
     *       VkFormat Format;
     *   - vulkan image usage flags bitwise combination (VK_IMAGE_USAGE_***):
     *       VkImageUsageFlags UsageFlags;
     *   - vulkan image layout (see VK_IMAGE_LAYOUT_***):
     *       VkImageLayout Layout;
     *   - image pixel data:
     *       const VOID *PixelsData;
     *   - image pixel data size (in bytes):
     *       UINT PixelsDataSize;
     *   - number of mipmaps to be create:
     *       UINT MipCount;
     * RETURNS: None.
     */
    VOID ImageCreate( VkImage &Image, VkImageView &ImageView, VkDeviceMemory &Memory,
                         INT W, INT H, BOOL IsColor, BOOL IsCube,
                         VkFormat Format, VkImageUsageFlags UsageFlags, VkImageLayout Layout,
                         const VOID *PixelsData = nullptr, UINT PixelsDataSize = 0, UINT MipCount = 1 );

    /* Creating vulkan Swapchain function.
     * ARGUMENTS: 
     *   - frame sizes:
     *       uint32_t FrameW, FrameH;
     * RETURNS: None.
     */
    VOID CreateSwapchain( uint32_t FrameW, uint32_t FrameH, VkSwapchainKHR CurSwapchain = VK_NULL_HANDLE );

    /* Creating vulkan command pool function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID CreateCommandPool( VOID );

    /* Creating vulkan command buffer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID CreateCommandBuffer( VOID );

    /* Creating vulkan Swapchain function.
     * ARGUMENTS: 
     *   - new frame sizes:
     *       uint32_t NewFrameW, NewFrameH;
     * RETURNS: None.
     */
    VOID ResizeSwapchain( uint32_t NewFrameW, uint32_t NewFrameH );

    /* Creating vulkan render pass function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID CreateRenderPass( VOID );

    /* Begin vulkan render pass function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID BeginRenderPass( VOID );

    /* Creating vulkan frame buffers function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID CreateFrameBuffers( VOID );

    /* Creating vulkan tarnsfer buffer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID CreateTransferBuffer( VOID );

    /* Inittialization vulkan function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID );
    
    /* Deinittialization vulkan function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID );
  }; /* End of 'vlk' class */
} /* end of 'tivk' namespace */

#endif /* __vlk_core_h_ */

/* END OF 'vlk_core.h' FILE */