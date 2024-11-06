#include "tivk.h"

tivk::buffer & tivk::buffer::CreateBuffer( VkBufferUsageFlags Flags, INT Size, const INT *Data )
{
  BufSize = Size;
  
  if (BufSize == 0)
    return *this;
  
  VkBufferCreateInfo BufInfo 
  {
    .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
    .size = BufSize,
    .usage = Flags, 
    .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
  };
  
  vkCreateBuffer(Rnd->VlkCore.Device, &BufInfo, nullptr, &Buffer);
  
  VkDescriptorBufferInfo VertexBufferInfo 
  {
    .buffer = Buffer,
    .offset = 0,
    .range = BufSize,
  };
  
  VkMemoryRequirements MemoryRequirements;
  vkGetBufferMemoryRequirements(Rnd->VlkCore.Device, Buffer, &MemoryRequirements);
  
  VkPhysicalDeviceMemoryProperties MemoryProperties;
  vkGetPhysicalDeviceMemoryProperties(Rnd->VlkCore.PhysDevice, &MemoryProperties);
  
  INT Ind = 0;
  
  for (UINT i = 0; i < MemoryProperties.memoryTypeCount; i++)
  {
    const auto &Type = MemoryProperties.memoryTypes[i];
  
    if ((MemoryRequirements.memoryTypeBits & (1 << i)) && (Type.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)   
    {
      Ind = i;
      break;
    }
  }
  
  VkMemoryAllocateInfo MemoryInfo
  {
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .allocationSize = MemoryRequirements.size,
    .memoryTypeIndex = static_cast<uint32_t>(Ind),
  };
  vkAllocateMemory(Rnd->VlkCore.Device, &MemoryInfo, nullptr, &Memory);
  
  if (vkBindBufferMemory(Rnd->VlkCore.Device, Buffer, Memory, 0) != VK_SUCCESS)
    std::cout << "Failed to bind memory to vertex buffer" << std::endl;
  
  VOID *MapPointer;
  vkMapMemory(Rnd->VlkCore.Device, Memory, 0, BufSize, 0, &MapPointer);
  memcpy(MapPointer, Data, BufSize);
  
  vkUnmapMemory(Rnd->VlkCore.Device, Memory);
  return *this;

}

tivk::buffer & tivk::buffer::UpdateBufferLow( const INT *Data, INT NumOfElements )
{
  VOID *MapPointer;
  vkMapMemory(Rnd->VlkCore.Device, Memory, 0, BufSize, 0, &MapPointer);
  memcpy(MapPointer, Data, BufSize);
  
  vkUnmapMemory(Rnd->VlkCore.Device, Memory);
  return *this;
}

VOID tivk::buffer::Free( VOID )
{
  /* Destroy buffer */
  if (Buffer != VK_NULL_HANDLE)
    vkDestroyBuffer(Rnd->VlkCore.Device, Buffer, nullptr);
  
  if (Memory != VK_NULL_HANDLE)
    vkFreeMemory(Rnd->VlkCore.Device, Memory, nullptr);
}