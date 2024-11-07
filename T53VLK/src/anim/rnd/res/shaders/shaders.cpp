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

#include "tivk.h"

/* Free shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tivk::shader::Free( VOID )
{
  if (PipelineLayout != VK_NULL_HANDLE)
    vkDestroyPipelineLayout(Rnd->VlkCore.Device, PipelineLayout, nullptr);

  if (Pipeline != VK_NULL_HANDLE)
    vkDestroyPipeline(Rnd->VlkCore.Device, Pipeline, nullptr);
}

/* Load text from file function.
 * ARGUMENTS:
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) loaded text (allocated through 'malloc') or NULL (if error is occured).
 */
std::vector<CHAR> tivk::shader::LoadTextFromFile( const std::string &FileName )
{
  std::fstream F;
  std::vector<CHAR> Data;
  F.open(FileName, std::fstream::in | std::fstream::binary);

  while (!F.eof())
    Data.push_back(F.get());
  
  Data.pop_back();

  return Data;
} /* End of 'tivk::shader::LoadTextFromFile' function */

/* Load shader function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (shader &) self reference.
 */
tivk::shader & tivk::shader::LoadShader( VOID )
{
  struct
  {
    std::string DefShaderName; /* Shader name */
    std::string Name;    /* Shader name */
    VkShaderStageFlagBits Stage;
  } shds[] =
  {
    {("shader.vert"), ("vert"), VK_SHADER_STAGE_VERTEX_BIT},
    {("shader.frag"), ("frag"), VK_SHADER_STAGE_FRAGMENT_BIT},
    {("shader.geom"), ("geom"), VK_SHADER_STAGE_GEOMETRY_BIT},
  };
  INT i, NoofS = sizeof(shds) / sizeof(shds[0]);

  std::vector<VkPipelineShaderStageCreateInfo> ShaderStages;

  //std::string CompileNameVert("glslc.exe " + Rnd->Path + "/bin/shaders/");
  //CompileNameVert += Name + "/shader.vert -o " + Rnd->Path + "/bin/shaders/" + Name + "/vert.spv";
  //
  //system(CompileNameVert.c_str());
  //
  //std::string CompileNameFrag("glslc.exe " + Rnd->Path + "/bin/shaders/");
  //CompileNameFrag += Name + "/shader.frag -o " + Rnd->Path + "/bin/shaders/" + Name + "/frag.spv";
  //system(CompileNameFrag.c_str());

  for (i = 0; i < NoofS; i++)
  {
    BOOL exist = std::filesystem::exists("bin/shaders/" + Name + "/" + shds[i].DefShaderName);
    
    if (exist)
    {
      std::vector<CHAR> Buf;
      VkShaderModule ShaderModule;
    
      std::string CompileNameVert("glslc.exe " + Rnd->Path + "/bin/shaders/");
      CompileNameVert += Name + "/" + shds[i].DefShaderName + " -o " + Rnd->Path + "/bin/shaders/" + Name + "/" + shds[i].Name + ".spv";

      system(CompileNameVert.c_str());

      Buf = LoadTextFromFile("bin/shaders/" + Name + "/" + shds[i].Name + ".spv");
    
      if (Buf.size() != 0)
      {
        VkShaderModuleCreateInfo Info
        {
          .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
          .codeSize = Buf.size(),
          .pCode = reinterpret_cast<const uint32_t *>(Buf.data()),
        };

        if (vkCreateShaderModule(Rnd->VlkCore.Device, &Info, nullptr, &ShaderModule) != VK_SUCCESS)
          std::cout << "Failed to create shader modules" << std::endl;

        VkPipelineShaderStageCreateInfo VertShdStageInfo {};

        VertShdStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        VertShdStageInfo.stage = shds[i].Stage;
        VertShdStageInfo.module = ShaderModule;
        VertShdStageInfo.pName = "main";

        ShaderStages.push_back(VertShdStageInfo);
      }
    }
  }

   VkVertexInputBindingDescription BindingDescr
  {
    .binding = 0,
    .stride = (UINT32)sizeof(vertex::vert),
    .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,  
  };
  
  std::array<VkVertexInputAttributeDescription, 4> AttribDescrs {};
 
  /* Position format */
  AttribDescrs[0].binding = 0;
  AttribDescrs[0].location = 0;
  AttribDescrs[0].format = VK_FORMAT_R32G32B32_SFLOAT;
  AttribDescrs[0].offset = 0;

  /* Texture coordinates format */
  AttribDescrs[1].binding = 0;
  AttribDescrs[1].location = 1;
  AttribDescrs[1].format = VK_FORMAT_R32G32_SFLOAT;
  AttribDescrs[1].offset = sizeof(vec3);

  /* Normal format */
  AttribDescrs[2].binding = 0;
  AttribDescrs[2].location = 2;
  AttribDescrs[2].format = VK_FORMAT_R32G32B32_SFLOAT;
  AttribDescrs[2].offset = sizeof(vec3) + sizeof(vec2);

  /* Color format */
  AttribDescrs[3].binding = 0;
  AttribDescrs[3].location = 3;
  AttribDescrs[3].format = VK_FORMAT_R32G32B32A32_SFLOAT;
  AttribDescrs[3].offset = sizeof(vec3) + sizeof(vec2) + sizeof(vec3);  
  
  VkPipelineVertexInputStateCreateInfo VertInputInfo 
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
    .vertexBindingDescriptionCount = 1,
    .pVertexBindingDescriptions = &BindingDescr,
    .vertexAttributeDescriptionCount = AttribDescrs.size(),
    .pVertexAttributeDescriptions = AttribDescrs.data(),
  };

  std::vector<VkDynamicState> DynamicStates
  {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR
  };
  
  VkPipelineDynamicStateCreateInfo DSCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
    .dynamicStateCount = (UINT32)DynamicStates.size(),
    .pDynamicStates = DynamicStates.data(),
  };
  
  VkViewport Vp
  {
    .width = static_cast<float>(Rnd->VlkCore.FrameW),
    .height = static_cast<float>(Rnd->VlkCore.FrameH),
    .minDepth = 0,
    .maxDepth = 1,
  };
  VkRect2D Sc
  {
    .offset = {0, 0},
    .extent = {Rnd->VlkCore.FrameW, Rnd->VlkCore.FrameH},
  };
  VkPipelineViewportStateCreateInfo VpCreateInfo 
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
    .viewportCount = 1,
    .pViewports = &Rnd->Viewport,
    .scissorCount = 1,
    .pScissors = &Rnd->Scissor,
  };

  VkPipelineRasterizationStateCreateInfo RastCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
    .polygonMode = VK_POLYGON_MODE_FILL,
    .cullMode = 0,
    .frontFace = VK_FRONT_FACE_CLOCKWISE,
    .lineWidth = 1.0f,
  };

  VkPipelineDepthStencilStateCreateInfo DepthStencil
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
    .depthTestEnable = VK_TRUE,
    .depthWriteEnable = VK_TRUE,
    .depthCompareOp = VK_COMPARE_OP_LESS,
    .depthBoundsTestEnable = VK_FALSE,
    .stencilTestEnable = VK_FALSE,
  };

  VkPipelineMultisampleStateCreateInfo MSCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
    .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
    .sampleShadingEnable = VK_FALSE,                                  
    .minSampleShading = 1.0f,
  };

  VkPipelineColorBlendAttachmentState BlendAttachState
  {
    .blendEnable = VK_FALSE,
    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT |                     // Определяет цветовые компоненты,
                      VK_COLOR_COMPONENT_G_BIT |                     // которые в итоге запишутся в буфер кадра.
                      VK_COLOR_COMPONENT_B_BIT |                     // В данном случае - все.
                      VK_COLOR_COMPONENT_A_BIT,
  };
  
  VkPipelineColorBlendStateCreateInfo BlendCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
    .logicOpEnable = VK_FALSE,                                        // Есть ли необходимость в
    .attachmentCount = 1,
    .pAttachments = &BlendAttachState,
  };
  VkPipelineInputAssemblyStateCreateInfo IACreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
    .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
    .primitiveRestartEnable = VK_FALSE,
  };

  VkPipelineLayoutCreateInfo PipelineLayoutInfo
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
    .setLayoutCount = 1, 
    .pSetLayouts = &Rnd->VlkCore.DescriptorSetLayout,
  };

  if (vkCreatePipelineLayout(Rnd->VlkCore.Device, &PipelineLayoutInfo, nullptr, &PipelineLayout) != VK_SUCCESS)
    std::cout << "Failed to create pipeline layout" << std::endl;

  VkGraphicsPipelineCreateInfo PipelineCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
    .stageCount = (UINT32)ShaderStages.size(),
    .pStages = ShaderStages.data(),
    .pVertexInputState = &VertInputInfo,
    .pInputAssemblyState = &IACreateInfo,
    .pViewportState = &VpCreateInfo,
    .pRasterizationState = &RastCreateInfo,
    .pMultisampleState = &MSCreateInfo,
    .pDepthStencilState = &DepthStencil,
    .pColorBlendState = &BlendCreateInfo,
    .pDynamicState = &DSCreateInfo,
    .layout = PipelineLayout, 
    .renderPass = Rnd->VlkCore.RenderPass,
    .subpass = 0,
  };
  
  if (vkCreateGraphicsPipelines(Rnd->VlkCore.Device, VK_NULL_HANDLE, 1, &PipelineCreateInfo, nullptr, &Pipeline) != VK_SUCCESS)
    std::cout << "Failed to create graphics pipeline" << std::endl;

  return *this;
} /* End of 'tivk::shader::LoadShader' function */

/* END OF 'shaders.cpp' FILE */ 
