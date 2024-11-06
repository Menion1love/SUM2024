/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : shaders.h
 * PURPOSE     : Animation project.
 *               Shaders declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 05.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __shaders_h_
#define __shaders_h_

#include "../resources_def.h"

/* Project namespace */
namespace tivk
{
  /* Shader handle class */
  class shader : public resource
  {
    friend class render;
  private:
    /* Save text to log file function.
     * ARGUMENTS:
     *   - text 1 to save:
     *       const std::string &Stage;
     *   - text 2 to save:
     *       const std::string &Text;
     * RETURNS: None.
     */
    VOID Log( const std::string &Stage, const std::string &Text );

    /* Load text from file function.
     * ARGUMENTS:
     *   - file name:
     *       CHAR *FileName;
     * RETURNS:
     *   (CHAR *) loaded text (allocated through 'malloc') or NULL (if error is occured).
     */
    std::vector<CHAR> LoadTextFromFile( const std::string &FileName );

  public:
    // Shader name
    std::string Name;

    /* Vulkan pipeline */
    VkPipeline Pipeline {};

    /* Vulkan pipeline layout */
    VkPipelineLayout PipelineLayout {};

    /* Free shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

    /* Load shader function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (shader &) self reference.
     */
    shader & LoadShader( VOID );

    /* Class default constructor */
    shader( VOID )
    {
      
    } /* End of 'shader' function */;

    /* Class constructor.
     * ARGUMENTS:
     *   - shader file name prefix:
     *       const std::string &FileNamePrefix;
     */
    shader( const std::string &FileNamePrefix )
    {
      this->Name = FileNamePrefix;
    } /* End of 'vigl::shader::shader' function */

    /* Class destructor */
    ~shader( VOID )
    {
    } /* End of '~shader' function */

    /* Update shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Update( VOID );

    /* Update shader internal data info function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID UpdateInfo( VOID );

  };

  /* Shader manager */
  class shader_manager : public resource_manager<shader>
  {
    friend class render;
    /* Class constructor.
     * ARGUMENTS:
     *   - render instance reference:
     *       render &Rnd;
     */
    shader_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'shader_manager' function */

  public:
    /* Create shader function.
     * ARGUMENTS:
     *   - shader file name prefix:
     *       const std::string &FileNamePrefix;
     * RETURNS:
     *   (shader *) created primitive interface.
     */
    shader * ShdCreate( const std::string &FileNamePrefix )
    {
      shader *shd = resource_manager::Add(shader(FileNamePrefix));
      shd->LoadShader();
      return shd;
    } /* End of 'ShdCreate' function */

    /* Class destructor */
    ~shader_manager( VOID )
    {
    } /* End of '~shader_manager' function */
    
    /* Update all shaders in stock function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID UpdateShaders( VOID )
    {
   } /* End of 'UpdateShaders' function */
  }; /* End of 'shader_manager' class */
} /* end of 'tivk' namespace */

#endif /* __shaders_h_ */

/* END OF 'shaders.h' FILE */ 
