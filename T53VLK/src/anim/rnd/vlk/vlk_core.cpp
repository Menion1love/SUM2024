/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_core.cpp
 * PURPOSE     : Animation project.
 *               Vulkan core module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 27.10.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "tivk.h"
#include "anim/rnd/vlk/vlk_core.h"
#include "anim/rnd/render.h"

#pragma comment(lib, "vulkan-1.lib")

/* Creating vulkan instance function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::CreateInstance( VOID )
{
  VkApplicationInfo AppInfo 
  {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pApplicationName = "T53VLK",
    .applicationVersion = 1,
    .apiVersion = VK_MAKE_VERSION(1, 3, 0),   
  };
  
  VkInstanceCreateInfo InstanceCreateInfo 
  {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pApplicationInfo = &AppInfo,
  };

  std::vector<const CHAR *> InstanceExtensionNames 
  {
    "VK_KHR_surface",
    "VK_KHR_win32_surface",
#if _DEBUG
    "VK_EXT_debug_utils",
#endif /* _DEBUG */
  };
  InstanceCreateInfo.enabledExtensionCount = (UINT32)InstanceExtensionNames.size();
  InstanceCreateInfo.ppEnabledExtensionNames = InstanceExtensionNames.data();

  std::vector<const CHAR *> EnabledLayersNames
  {
    "VK_LAYER_KHRONOS_validation",
  };
  
  uint32_t cnt; 
  std::vector<VkLayerProperties> Vklp;
  vkEnumerateInstanceLayerProperties(&cnt, nullptr);
  Vklp.resize(cnt);
  vkEnumerateInstanceLayerProperties(&cnt, Vklp.data());

  for (auto l : Vklp)
    std::cout << l.layerName << std::endl;


  InstanceCreateInfo.enabledLayerCount = (UINT32)EnabledLayersNames.size();
  InstanceCreateInfo.ppEnabledLayerNames = EnabledLayersNames.data();

  VkValidationFeaturesEXT ValidationFeatures 
  {
    .sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
  };
  std::vector<VkValidationFeatureEnableEXT> ValidationFeaturesEnable
  {
    VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,    
    VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT   
  };
  ValidationFeatures.enabledValidationFeatureCount = (UINT32)ValidationFeaturesEnable.size();
  ValidationFeatures.pEnabledValidationFeatures = ValidationFeaturesEnable.data();

  InstanceCreateInfo.pNext = &ValidationFeatures;

  VkDebugReportCallbackCreateInfoEXT DebugReportCallbackInfo {};
  DebugReportCallbackInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;

  DebugReportCallbackInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
  DebugReportCallbackInfo.pNext = nullptr;
  DebugReportCallbackInfo.flags =
    VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
    VK_DEBUG_REPORT_WARNING_BIT_EXT |
    VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
    VK_DEBUG_REPORT_ERROR_BIT_EXT |
    VK_DEBUG_REPORT_DEBUG_BIT_EXT;
  DebugReportCallbackInfo.pfnCallback = [](
    VkDebugReportFlagsEXT Flags,
    VkDebugReportObjectTypeEXT ObjectType,
    UINT64 Object,
    UINT_PTR Location,
    INT32 MessageCode,
    const CHAR *LayerPrefix,
    const CHAR *Message,
    VOID *UserData) -> VkBool32
  {
    WORD Error = 0x0C, Warning = 0x0D, Perfomance = 0x06, Info = 0x0B;

    if ((Flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) != 0)
      return VK_FALSE;
    std::string Res;

    if ((Flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) != 0)
      Res += "INFO", SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Info);
    if ((Flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) != 0)
      Res += "WARNING", SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Warning);
    if ((Flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) != 0)
      Res += "PERFORMANCE", SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Perfomance);
    if ((Flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) != 0)
      Res += "ERROR", SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Error);

    Res += std::string("{") + LayerPrefix + "} " + Message + "\n";
    OutputDebugString(Res.c_str());
    std::cout << Res.c_str();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    return VK_FALSE;
  };
  DebugReportCallbackInfo.pUserData = nullptr;

  ValidationFeatures.pNext = &DebugReportCallbackInfo;

  if (vkCreateInstance(&InstanceCreateInfo, nullptr, &this->Instance) != VK_SUCCESS)
    std::cout << "failed to create instance!" << std::endl;
} /* End of 'tivk::vlk::CreateInstance' function */

/* Creating vulkan device function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::CreateDevice( VOID )
{
  UINT32 QueueFamilyCount;

  vkGetPhysicalDeviceQueueFamilyProperties(PhysDevice, &QueueFamilyCount, nullptr); 

  VkDeviceQueueCreateInfo QueueInfo
  {
    .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0,
    .queueFamilyIndex = 0,
    .queueCount = QueueFamilyCount,
    .pQueuePriorities = nullptr
  };
 
  std::vector<const CHAR *> ExtensionNames
  {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
  };

  // Print supported extensions
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);

  std::cout << "Available extensions:" << std::endl;

  // Print info about supported extensions
  uint32_t extensionCount = 0;

  // Get number of extensions supported
  vkEnumerateInstanceExtensionProperties ( nullptr, &extensionCount, nullptr );

  std::vector<VkExtensionProperties> extensions(extensionCount);

  // Get actual extensions properties
  vkEnumerateInstanceExtensionProperties ( nullptr, &extensionCount, extensions.data () );

  for ( const auto& extension : extensions ) 
    std::cout << "\t" << extension.extensionName << std::endl;

  // Now get info about supported debug layers
  uint32_t layerCount;

  // Get number of supported layers
  vkEnumerateInstanceLayerProperties ( &layerCount, nullptr );

  // Allocate memory for layers properties
  std::vector<VkLayerProperties> availableLayers ( layerCount );

  // Get actual properties
  vkEnumerateInstanceLayerProperties ( &layerCount, availableLayers.data () );

  // Print supported extensions
  std::cout << "available layers:" << std::endl;

  for ( auto& layerProperties : availableLayers )
    std::cout << '\t' << layerProperties.layerName << std::endl;

  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);

  VkPhysicalDeviceFeatures DeviceFeatures;

  vkGetPhysicalDeviceFeatures(PhysDevice, &DeviceFeatures);

  VkDeviceCreateInfo DeviceInfo
  {
    .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0,
    .queueCreateInfoCount = 1,
    .pQueueCreateInfos = &QueueInfo,
    .enabledLayerCount = 0,
    .ppEnabledLayerNames = nullptr,
    .enabledExtensionCount = static_cast<uint32_t>(ExtensionNames.size()),
    .ppEnabledExtensionNames = ExtensionNames.data(),
    .pEnabledFeatures = &DeviceFeatures
  };

  vkCreateDevice(PhysDevice, &DeviceInfo, nullptr, &Device);

  vkGetDeviceQueue(Device, 0, 0, &GraphicsQueue);
} /* End of 'tivk::vlk::CreateDevice' function */

/* Creating vulkan physical device function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::CreatePhysDevice( VOID )
{
  std::vector<VkPhysicalDevice> PhysDevices;
  UINT32 PhysicalDeviceCount = 0;
  UINT32 BestMem = 0;

  if (vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, nullptr) != VK_SUCCESS)
    return;

  PhysDevices.resize(PhysicalDeviceCount);
  if (vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, PhysDevices.data()) != VK_SUCCESS)
    return;

  VkPhysicalDevice PhysDevice = VK_NULL_HANDLE;
  for (VkPhysicalDevice &Device : PhysDevices)
  {
    std::vector<VkQueueFamilyProperties> QueueFamilies;
    UINT32 QueueFamilyCount = 0;
  
    VkPhysicalDeviceProperties DeviceProperties;
    vkGetPhysicalDeviceProperties(Device, &DeviceProperties);

    VkPhysicalDeviceFeatures DeviceFeatures;
    vkGetPhysicalDeviceFeatures(Device, &DeviceFeatures);

    // Print whether it is descrete or embedded
    std::cout << DeviceProperties.deviceName << (DeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ? " discrete" : " embedded" ) << std::endl;

    // Print geometry shaders support
    if (DeviceFeatures.geometryShader)
      std::cout << "Gemeotry shaders supported" << std::endl;

    // Print tessellation shaders support
    if (DeviceFeatures.tessellationShader)
      std::cout << "Tessellation shaders supported" << std::endl;  

    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, nullptr);

    QueueFamilies.resize(QueueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, QueueFamilies.data());

    INT IsCompatible = 0;

    for (auto Queue : QueueFamilies)
    {
      std::cout << "\tCount " << Queue.queueCount;

      if (Queue.queueFlags &  VK_QUEUE_GRAPHICS_BIT )
        std::cout << " Graphics";

      if (Queue.queueFlags & VK_QUEUE_COMPUTE_BIT )
        std::cout << " Compute";

      if (Queue.queueFlags & VK_QUEUE_TRANSFER_BIT )
        std::cout << " Transfer";

      std::cout << std::endl;

      if (
        (Queue.queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
        (Queue.queueFlags & VK_QUEUE_TRANSFER_BIT) &&
        (Queue.queueFlags & VK_QUEUE_COMPUTE_BIT))
        IsCompatible = 1;
    }

    if (IsCompatible)
    {
      VkPhysicalDeviceMemoryProperties PhysDeviceMem;
      UINT32 Mem = 0;

      vkGetPhysicalDeviceMemoryProperties(Device, &PhysDeviceMem);

      // Print info about all found types and heaps
      std::cout << "Memory properties:" << std::endl;
      std::cout << "\tmemoryTypeCount " << PhysDeviceMem.memoryTypeCount << std::endl;

      std::cout << "memoryHeapCount " << PhysDeviceMem.memoryHeapCount << std::endl;


      for (INT i = 0; i < PhysDeviceMem.memoryHeapCount; i++)
      {
        std::cout << "\t Heap " << i << ": ";

        std::cout << "\tSize " << PhysDeviceMem.memoryHeaps[i].size;
        
        // Heap belongs to device-only memory
        if (PhysDeviceMem.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT )
          std::cout << " device local, ";

        // For logical device representing more than one physical device
        if (PhysDeviceMem.memoryHeaps[i].flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT )
          std::cout << " multi instance ";

        std::cout << std::endl;

        Mem += PhysDeviceMem.memoryHeaps[i].size;
      }
      if (Mem > BestMem)
      {
        PhysDevice = Device;
        BestMem = Mem;
      }
    }
    std::cout << std::endl;
  }
  
  if (PhysDevice == VK_NULL_HANDLE)
  {
    std::cout << "Failed to create physical device!!" << std::endl;
    return;
  }

  this->PhysDevice = PhysDevice;
} /* End of 'tivk::vlk::CreateInstance' function */

/* Creating vulkan surface function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::CreateSurface( VOID )
{
  VkWin32SurfaceCreateInfoKHR SurfaceCreateInfo 
  {
    .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
    .flags = 0,
    .hinstance = GetModuleHandle(nullptr),
    .hwnd = hWndRef,
  };
  
  if (vkCreateWin32SurfaceKHR(Instance, &SurfaceCreateInfo, nullptr, &this->Surface) != VK_SUCCESS)
    std::cout << "Failed to create surface!!" << std::endl;
} /* End of 'tivk::vlk::CreateInstance' function */

/* Creating vulkan Swapchain function.
 * ARGUMENTS: 
 *   - frame sizes:
 *       uint32_t FrameW, FrameH;
 *   - current swapchain KHR:
 *       VkSwapchainKHR CurSwapchain;
 * RETURNS: None.
 */
VOID tivk::vlk::CreateSwapchain( uint32_t FrameW, uint32_t FrameH, VkSwapchainKHR CurSwapchain )
{
  VkSurfaceCapabilitiesKHR SurfaceCapabilities {};

  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysDevice, Surface, &SurfaceCapabilities);

  FrameW = FrameW < SurfaceCapabilities.minImageExtent.width ? SurfaceCapabilities.minImageExtent.width : (FrameW > SurfaceCapabilities.maxImageExtent.width ? SurfaceCapabilities.maxImageExtent.width : FrameW);
  FrameH = FrameH < SurfaceCapabilities.minImageExtent.height ? SurfaceCapabilities.minImageExtent.height : (FrameH > SurfaceCapabilities.maxImageExtent.height ? SurfaceCapabilities.maxImageExtent.height : FrameH);

  this->FrameW = FrameW;
  this->FrameH = FrameH; 

  VkSwapchainCreateInfoKHR SwapchainCreateInfo 
  {
    .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
    .flags = 0,
    .surface = Surface,
    .minImageCount = 2,
    .imageFormat = VK_FORMAT_R8G8B8A8_SRGB,
    .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
    .imageExtent = 
    {
      .width = FrameW,
      .height = FrameH
    },
    .imageArrayLayers = 1,
    .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
    .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
    .queueFamilyIndexCount = 0,
    .pQueueFamilyIndices = nullptr,
    .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
    .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR, 
    .presentMode = VK_PRESENT_MODE_FIFO_KHR,
    .clipped = VK_TRUE,
    .oldSwapchain = CurSwapchain,
  };
  
  if (vkCreateSwapchainKHR(Device, &SwapchainCreateInfo, nullptr, &Swapchain) != VK_SUCCESS)
  {
    std::cout << "Failed to create Swapchain!!" << std::endl;
    return;
  }

  std::vector<VkImage> SwapchainImages;

  UINT32 SwapchainImagesCount;
  if (vkGetSwapchainImagesKHR(Device, Swapchain, &SwapchainImagesCount, nullptr) != VK_SUCCESS)
    return;

  SwapchainImages.resize(SwapchainImagesCount);
  SwapchainImageViews.resize(SwapchainImagesCount);

  if (vkGetSwapchainImagesKHR(Device, Swapchain, &SwapchainImagesCount, &SwapchainImages[0]) != VK_SUCCESS)
    return;

  for (INT i = 0; i < SwapchainImagesCount; i++) 
  {
    VkImageViewCreateInfo ImageViewCreateInfo 
    {
      .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
      .image = SwapchainImages[i],
      
      .viewType = VK_IMAGE_VIEW_TYPE_2D,
      .format = VK_FORMAT_R8G8B8A8_SRGB,
      .components =
      {
        .r = VK_COMPONENT_SWIZZLE_IDENTITY,
        .g = VK_COMPONENT_SWIZZLE_IDENTITY,
        .b = VK_COMPONENT_SWIZZLE_IDENTITY,
        .a = VK_COMPONENT_SWIZZLE_IDENTITY,
      },

      .subresourceRange =
      {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .baseMipLevel = 0,
        .levelCount = 1,
        .baseArrayLayer = 0,
        .layerCount = 1,
      },
    };
  
    if (vkCreateImageView(Device, &ImageViewCreateInfo, nullptr, &SwapchainImageViews[i]) != VK_SUCCESS)
      return;
  }

  VkDeviceMemory Memory;

  ImageCreate(DepthImage, DepthImageView, Memory, FrameW, FrameH, 0, 0, VK_FORMAT_D32_SFLOAT, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_IMAGE_LAYOUT_UNDEFINED);
} /* End of 'tivk::vlk::CreatesSwapchain' function */

/* Creating vulkan Swapchain function.
 * ARGUMENTS: 
 *   - new frame sizes:
 *       uint32_t NewFrameW, NewFrameH;
 * RETURNS: None.
 */
VOID tivk::vlk::ResizeSwapchain( uint32_t NewFrameW, uint32_t NewFrameH )
{
  vkDeviceWaitIdle(Device);

  for (INT i = 0; i < FrameBuffers.size(); i++)
    vkDestroyFramebuffer(Device, FrameBuffers[i], nullptr);

  for (INT i = 0; i < SwapchainImageViews.size(); i++)
    vkDestroyImageView(Device, SwapchainImageViews[i], nullptr);

  VkSwapchainKHR OldSwapchain = Swapchain;
  CreateSwapchain(NewFrameW, NewFrameH, OldSwapchain);
  vkDestroySwapchainKHR(Device, OldSwapchain, nullptr);
  CreateFrameBuffers();
} /* End of  'tivk::vlk::ResizeSwapchain' function */

/* Creating vulkan render pass function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::CreateRenderPass( VOID )
{

  VkAttachmentDescription AttachmentDescription
  {
    .flags = 0,
    
    .format = VK_FORMAT_R8G8B8A8_SRGB,
    .samples = VK_SAMPLE_COUNT_1_BIT,
    .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
    .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
    .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
    .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
    .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
    .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
  };

  VkAttachmentDescription DepthDescription
  {
    .flags = 0,
    
    .format = VK_FORMAT_D32_SFLOAT,
    .samples = VK_SAMPLE_COUNT_1_BIT,
    .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
    .storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
    .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
    .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
    .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
    .finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
  };

  VkAttachmentReference DepthAttachmaentRef
  {
    .attachment = 1,
    .layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
  };
  
  VkAttachmentReference ColorAttachmentReference
  {
    .attachment = 0,
    .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
  };
  
  VkSubpassDescription SubpassDescription
  {
    .flags = 0,
    .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
    .inputAttachmentCount = 0,
    .pInputAttachments = nullptr,
    .colorAttachmentCount = 1,
    .pColorAttachments = &ColorAttachmentReference,
    .pResolveAttachments = nullptr,
    .pDepthStencilAttachment = &DepthAttachmaentRef,
    .preserveAttachmentCount = 0,
    .pPreserveAttachments = nullptr,
  };
  
  VkSubpassDependency SubpassDependency
  {
    .srcSubpass = VK_SUBPASS_EXTERNAL,
    .dstSubpass = 0,
    .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
    .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
    .srcAccessMask = 0,
    .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
    .dependencyFlags = 0,
  };


  std::array<VkAttachmentDescription, 2> att = {AttachmentDescription, DepthDescription};

  VkRenderPassCreateInfo CreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0,
    .attachmentCount = static_cast<uint32_t>(att.size()),
    .pAttachments = att.data(),
    .subpassCount = 1,
    .pSubpasses = &SubpassDescription,
    .dependencyCount = 1,
    .pDependencies = &SubpassDependency,
  };

  if (vkCreateRenderPass(Device, &CreateInfo, nullptr, &RenderPass) != VK_SUCCESS)
    std::cout << "Failed to create render pass!!" << std::endl;
} /* End of 'tivk::vlk::CreateRenderPass' function */

/* Creating vulkan frame buffers function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::CreateFrameBuffers( VOID )
{
  FrameBuffers.resize(SwapchainImageViews.size());

  for (INT i = 0; i < SwapchainImageViews.size(); i++)
  {
    std::array<VkImageView, 2> Attachments = 
    {
      SwapchainImageViews[i],
      DepthImageView
    };
  
    VkFramebufferCreateInfo FrameBufferCreateInfo
    {
      .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
      .renderPass = RenderPass,
      .attachmentCount = static_cast<uint32_t>(Attachments.size()),
      .pAttachments = Attachments.data(),
      .width = FrameW,
      .height = FrameH,
      .layers = 1,
    };
  
    if (vkCreateFramebuffer(Device, &FrameBufferCreateInfo, nullptr, &FrameBuffers[i]) != VK_SUCCESS)
      return;
  }
} /* End of 'tivk::vlk::CreateFrameBuffers' function */

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
VOID tivk::vlk::ImageCreate( VkImage &Image, VkImageView &ImageView, VkDeviceMemory &Memory,
                     INT W, INT H, BOOL IsColor, BOOL IsCube,
                     VkFormat Format, VkImageUsageFlags UsageFlags, VkImageLayout Layout,
                     const VOID *PixelsData, UINT PixelsDataSize, UINT MipCount )
{
  if (MipCount < 1)
    MipCount = 1;
  
  // Create vulkan image
  VkImageCreateInfo ImageCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
    .imageType = VK_IMAGE_TYPE_2D,
    .format = Format,
    .extent {.width = (UINT)W, .height = (UINT)H, .depth = 1 },
    .mipLevels = MipCount,
    .arrayLayers = IsCube ? 6U : 1U,
    .samples = VK_SAMPLE_COUNT_1_BIT,
    .tiling = VK_IMAGE_TILING_OPTIMAL,
    .usage = UsageFlags,
    .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    .initialLayout = Layout,
  };
  vkCreateImage(Device, &ImageCreateInfo, nullptr, &Image);
   
  // Allocate vulkan image memory and bind to Image
  VkMemoryRequirements MemoryRequirements;
  vkGetImageMemoryRequirements(Device, Image, &MemoryRequirements);
  VkMemoryPropertyFlags Flags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  VkPhysicalDeviceMemoryProperties PhysDeviceMemoryProperties;
  vkGetPhysicalDeviceMemoryProperties(PhysDevice, &PhysDeviceMemoryProperties);
  UINT memory_type_index = -1;
  for (UINT i = 0; i < PhysDeviceMemoryProperties.memoryTypeCount; i++)
  {
    const auto &Type = PhysDeviceMemoryProperties.memoryTypes[i];
    if ((MemoryRequirements.memoryTypeBits & (1 << i)) && (Type.propertyFlags & Flags) == Flags)
    {
      memory_type_index = i;
      break;
    }
  }

  VkMemoryAllocateInfo MemoryAllocateInfo
  {
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .allocationSize = MemoryRequirements.size,
    .memoryTypeIndex = memory_type_index,
  };
  vkAllocateMemory(Device, &MemoryAllocateInfo, nullptr, &Memory);
  vkBindImageMemory(Device, Image, Memory, 0);

  // Create image view
  VkImageViewCreateInfo ImageViewCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
    .image = Image,
    .viewType = VK_IMAGE_VIEW_TYPE_2D,
    .format = Format,
    .components = {.r = VK_COMPONENT_SWIZZLE_IDENTITY, .g = VK_COMPONENT_SWIZZLE_IDENTITY, .b = VK_COMPONENT_SWIZZLE_IDENTITY, .a = VK_COMPONENT_SWIZZLE_IDENTITY},
    .subresourceRange
    {
      .aspectMask = VkImageAspectFlags(IsColor ? VK_IMAGE_ASPECT_COLOR_BIT : VK_IMAGE_ASPECT_DEPTH_BIT), 
      .baseMipLevel = 0,
      .levelCount = MipCount,
      .baseArrayLayer = 0,
      .layerCount = IsCube ? 6U : 1U,
    }
  };
  vkCreateImageView(Device, &ImageViewCreateInfo, nullptr, &ImageView);

   if (PixelsData != nullptr)
   {
     Stage->UpdateBuffer(PixelsData);

     // Copy through command buffer
     VkCommandBufferBeginInfo CommandBufferBeginInfo
     {
       .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
       .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
     };
     vkBeginCommandBuffer(CommandBuffer, &CommandBufferBeginInfo);
 
     // Create transfer barrier
     VkImageMemoryBarrier ImageMemoryBarrier1
     {
      .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
      .srcAccessMask = VK_ACCESS_HOST_WRITE_BIT,
      .dstAccessMask = 0,
      .oldLayout = Layout,
      .newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
      .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      .image = Image,
      .subresourceRange
       {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .baseMipLevel = 0,
        .levelCount = MipCount,
        .baseArrayLayer = 0,
        .layerCount = 1,
       },
     };
     vkCmdPipelineBarrier(CommandBuffer, 
       VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_HOST_BIT, 0, 0, nullptr, 0, nullptr, 1, &ImageMemoryBarrier1);
 
    // Copy buffer to image
     VkBufferImageCopy Region
      { 
      .bufferOffset = 0,
      .bufferRowLength = (UINT)W,
      .bufferImageHeight = (UINT)H,
      .imageSubresource
      {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .mipLevel = 0,
        .baseArrayLayer = 0,
        .layerCount = 1,
      },
      .imageOffset {.x = 0, .y = 0, .z = 0},
      .imageExtent {.width = (UINT)W, .height = (UINT)H, .depth = 1},
    };
    vkCmdCopyBufferToImage(CommandBuffer, Stage->Buffer, Image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &Region);
 
    // Create transfer barrier
    VkImageMemoryBarrier ImageMemoryBarrier2
    {
      .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
      .srcAccessMask = VK_ACCESS_HOST_WRITE_BIT,
      .dstAccessMask = 0,
      .oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
      .newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
      .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      .image = Image,
      .subresourceRange
      {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .baseMipLevel = 0,
        .levelCount = MipCount,
        .baseArrayLayer = 0,
        .layerCount = 1,
      },
    };
    vkCmdPipelineBarrier(CommandBuffer,
      VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_HOST_BIT, 0, 
      0, nullptr, 0, nullptr, 1, &ImageMemoryBarrier2);
 
    vkEndCommandBuffer(CommandBuffer);
    VkPipelineStageFlags PipelineStageFlags[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    VkSubmitInfo SubmitInfo
    {
      .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
      .waitSemaphoreCount = 0,
      .pWaitDstStageMask = PipelineStageFlags,
      .commandBufferCount = 1,
      .pCommandBuffers = &CommandBuffer,
    };

    vkQueueSubmit(GraphicsQueue, 1, &SubmitInfo, Fence);
    vkWaitForFences(Device, 1, &Fence, VK_TRUE, UINT64_MAX);
    vkResetFences(Device, 1, &Fence);
  }
}  /* End of 'tivk::vlk::ImageCreate' function */

/* Creating vulkan command pool function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::CreateCommandPool( VOID )
{
  queue_family_indices Indices = GetQueueFamilyIndices(PhysDevice);
  VkCommandPoolCreateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, 
    .queueFamilyIndex = Indices.GraphicsFamily
  };

  vkCreateCommandPool(Device, &Info, nullptr, &CommandPool);
} /* End of 'tivk::vlk::CreateCommandPool' function */

/* Creating vulkan command buffer function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::CreateTransferBuffer( VOID )
{
  VkCommandBufferAllocateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
    .commandPool = CommandPool,
    .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
    .commandBufferCount = 1,
  };
  
  vkAllocateCommandBuffers(Device, &Info, &TransferCommandBuffer);
} /* End of 'tivk::vlk::CreateCommandBuffer' function */

/* Creating vulkan command buffer function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::CreateCommandBuffer( VOID )
{
  VkCommandBufferAllocateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
    .commandPool = CommandPool,
    .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
    .commandBufferCount = 1
  };
  
  vkAllocateCommandBuffers(Device, &Info, &CommandBuffer);
  
  VkFenceCreateInfo FenceInfo
  {
    .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
    .flags = 0
  };

  vkCreateFence(Device, &FenceInfo, nullptr, &Fence);
} /* End of 'tivk::vlk::CreateCommandBuffer' function */

/* Begin vulkan render pass function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::BeginRenderPass( VOID )
{
  std::array<VkClearValue, 2> ClearValues {};

  ClearValues[0].color = {{0.3f, 0.47f, 0.8f, 1.0f}};
  ClearValues[1].color = {{1.0f, 1.0f, 1.0f, 1.0f}};

  if (vkResetFences(Device, 1, &Fence) != VK_SUCCESS)
    std::cout << 1;

  vkAcquireNextImageKHR(Device, Swapchain, UINT64_MAX, {}, Fence, &RenderInd);
  vkWaitForFences(Device, 1, &Fence, TRUE, UINT64_MAX);

  vkResetCommandBuffer(CommandBuffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

  VkCommandBufferBeginInfo BeginInfo
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    .flags = 0,
    .pInheritanceInfo = nullptr,
  };
  vkBeginCommandBuffer(CommandBuffer, &BeginInfo);

  VkRenderPassBeginInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
    .renderPass = RenderPass,
    .framebuffer = FrameBuffers[RenderInd],
    .renderArea =
    {
      .offset = 
      {
        .x = 0,
        .y = 0
      },
      .extent = 
      {
        .width = FrameW,
        .height = FrameH
      }
    },
    .clearValueCount = static_cast<UINT32>(ClearValues.size()),
    .pClearValues = ClearValues.data()
  };  

  vkCmdBeginRenderPass(CommandBuffer, &Info, VK_SUBPASS_CONTENTS_INLINE);
} /* End of 'tivk::vlk::BeginRenderPass' function */

/* End vulkan render pass function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::EndRenderPass( VOID )
{
   vkCmdEndRenderPass(CommandBuffer);
   vkEndCommandBuffer(CommandBuffer);

   if (vkResetFences(Device, 1, &Fence) != VK_SUCCESS)
     std::cout << 1;

   VkSubmitInfo SubmitInfo
   {
     .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
     .pWaitDstStageMask = nullptr,
     .commandBufferCount = 1,
     .pCommandBuffers = &CommandBuffer,
     .signalSemaphoreCount = 0,
     .pSignalSemaphores = nullptr,
   };
   if (vkQueueSubmit(GraphicsQueue, 1, &SubmitInfo, Fence) != VK_SUCCESS)
     std::cout << "wait";
   vkWaitForFences(Device, 1, &Fence, TRUE, UINT64_MAX);

   VkPresentInfoKHR PresentInfo
   {
     .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
     .waitSemaphoreCount = 0,
     .pWaitSemaphores = nullptr,
     .swapchainCount = 1,
     .pSwapchains = &Swapchain,
     .pImageIndices = &RenderInd,
   };
   vkQueuePresentKHR(GraphicsQueue, &PresentInfo);
} /* End of 'tivk::vlk::EndRenderPass' function */

/* Create descriptor set function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::CreateDescriptorSet( VOID )
{
   std::vector<VkDescriptorPoolSize> PoolSizes {};

   PoolSizes.resize(2);

   PoolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; 
   PoolSizes[0].descriptorCount = 1;
   
   PoolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
   PoolSizes[1].descriptorCount = 8;

  VkDescriptorPoolCreateInfo PoolCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
    .maxSets = 100,
    .poolSizeCount = (UINT)PoolSizes.size(),
    .pPoolSizes = PoolSizes.data(),
  };

  VkDescriptorPool DescriptorPool;
  
  if (vkCreateDescriptorPool(Device, &PoolCreateInfo, nullptr, &DescriptorPool) != VK_SUCCESS)
    std::cout << "Failed to create descriptor pool" << std::endl;

  VkDescriptorSetLayoutBinding DescriptorSetLayoutBindings[]
  {
    /* Unifrom Buffer */
    {
      .binding = 0,
      .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
      .descriptorCount = 1,
      .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
      .pImmutableSamplers = nullptr
    },
    {
      .binding = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
      .descriptorCount = 1,
      .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
      .pImmutableSamplers = nullptr
    },
    {
      .binding = 2,
      .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
      .descriptorCount = 1,
      .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
      .pImmutableSamplers = nullptr
    },
    {
      .binding = 3,
      .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
      .descriptorCount = 1,
      .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
      .pImmutableSamplers = nullptr,
    }
  };
  
  VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO, 
    .flags = 0,
    .bindingCount = (UINT32)std::size(DescriptorSetLayoutBindings),
    .pBindings = DescriptorSetLayoutBindings,
  };
  
  vkCreateDescriptorSetLayout(
    Device,
    &DescriptorSetLayoutCreateInfo, 
    nullptr,
    &DescriptorSetLayout
  ); 

  VkDescriptorSetAllocateInfo AllocInfo
  {
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
    .descriptorPool = DescriptorPool,
    .descriptorSetCount = 1,
    .pSetLayouts = &DescriptorSetLayout,
  };

  VkSamplerCreateInfo SamplerInfo
  {
    .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO, 
    .magFilter = VK_FILTER_LINEAR,
    .minFilter = VK_FILTER_LINEAR,
    .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
    .addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
    .addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
    .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
    .borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
  };

  vkCreateSampler(Device, &SamplerInfo, nullptr, &GraphicsSampler);
 
  if (vkAllocateDescriptorSets(Device, &AllocInfo, &DescriptorSet) != VK_SUCCESS)
    std::cout << "Failed to create descriptor sets" << std::endl;
} /* End of 'tivk::vlk::CreateDescriptorSet' function */

/* Update descriptor set with buffer function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::UpdateDescriptorSet( texture *Tex )
{
  std::array<VkWriteDescriptorSet, 1> DescriptorWrites {{}};

  DescriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  DescriptorWrites[0].dstSet = DescriptorSet;                             
  DescriptorWrites[0].dstBinding = 3;                           
  DescriptorWrites[0].dstArrayElement = 0;                                
  DescriptorWrites[0].descriptorCount = 1;  
  VkDescriptorImageInfo ImageInfo
  {
      .sampler = GraphicsSampler,
      .imageView = Tex->ImageView,
      .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
  };
  DescriptorWrites[0].pImageInfo = &ImageInfo;
  DescriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER; 

  vkUpdateDescriptorSets(Device, (UINT)DescriptorWrites.size(), DescriptorWrites.data(), 0, nullptr);
} /* End of 'tivk::vlk::CreateDescriptorSet' function */

/* Update descriptor set with buffer function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::UpdateDescriptorSet( buffer *Buf )
{
  std::array<VkWriteDescriptorSet, 1> DescriptorWrites {{}};

  DescriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  DescriptorWrites[0].dstSet = DescriptorSet;                             
  DescriptorWrites[0].dstBinding = Buf->BindingPoint;                           
  DescriptorWrites[0].dstArrayElement = 0;                                
  DescriptorWrites[0].descriptorCount = 1;  
  
  VkDescriptorBufferInfo BufferInfo
  {
    .buffer = Buf->Buffer,
    .offset = 0,
    .range = Buf->BufSize, 
  };

  DescriptorWrites[0].pBufferInfo = &BufferInfo;
  DescriptorWrites[0].descriptorType = Buf->UsageFlag == VK_BUFFER_USAGE_STORAGE_BUFFER_BIT ? VK_DESCRIPTOR_TYPE_STORAGE_BUFFER : VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; 
  vkUpdateDescriptorSets(Device, (UINT)DescriptorWrites.size(), DescriptorWrites.data(), 0, nullptr);
} /* End of 'tivk::vlk::InitDescriptorSet' function */

/* Inittialization vulkan function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::Init( VOID )
{
  CreateInstance();
  CreatePhysDevice();
  CreateDevice();
  CreateSurface();
  CreateCommandPool();
  CreateCommandBuffer();
  CreateSwapchain(30, 47);
  CreateRenderPass();
  CreateFrameBuffers();
  CreateTransferBuffer();
  CreateDescriptorSet();
} /* End of 'tivk::vlk::CreateInstance' function */

/* Deinittialization vulkan function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::vlk::Close( VOID )
{
  vkDestroyImage(Device, DepthImage, nullptr);
  vkDestroyImageView(Device, DepthImageView, nullptr);
  vkDestroyDescriptorSetLayout(Device, DescriptorSetLayout, nullptr);

  vkDestroyDescriptorSetLayout(Device, DescriptorSetLayout, nullptr);
  vkDestroyCommandPool(Device, CommandPool, nullptr);

  for (VkFramebuffer FrameBuffer : FrameBuffers)
    vkDestroyFramebuffer(Device, FrameBuffer, nullptr);

  vkDestroyRenderPass(Device, RenderPass, nullptr); 

  for (INT i = 0; i < SwapchainImageViews.size(); i++)
    vkDestroyImageView(Device, SwapchainImageViews[i], nullptr);

  vkDestroySwapchainKHR(Device, Swapchain, nullptr);
  vkDestroySurfaceKHR(Instance, Surface, nullptr);
  vkDestroyDevice(Device, nullptr);
  vkDestroyInstance(Instance, nullptr);
} /* End of 'tivk::vlk::CreateInstance' function */

/* END OF 'vlk_core.cpp' FILE */
