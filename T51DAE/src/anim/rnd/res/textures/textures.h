/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : textures.h
 * PURPOSE     : Animation project.
 *               Textures declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               TH4.
 * LAST UPDATE : 05.08.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __textures_h_
#define __textures_h_
                             
#include "../resources_def.h"
#include "../images/images.h"

/* Project namespace */
namespace tigl
{
  /* Texture handle class */
  class texture : public resource
  {
    friend class render;
  public:   
    public:
    // Texture name
    std::string Name;

    // Image size
    INT W = 0, H = 0;

    // OpenGL texture Id
    UINT TexId = 0;

    /* Class default constructor */
    texture( VOID )
    {
    } /* End of 'texture' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - texture file name:
     *       const std::string &FileName;
     */
    texture( const std::string &FileName ) : Name(FileName)
    {
    } /* End of 'texture' function */

    /* Texture create function.
     * ARGUMENTS:
     *   - texture name:
     *       const std::string &NewName;
     *   - image size:
     *       INT NewW, NewH;
     *   - components count:
     *       INT BytesPerPixel;
     *   - image pixel data:
     *       VOID *Pixels;
     * RETURNS:
     *   (texture &) self reference.
     */
    texture & Create( const std::string &NewName, INT NewW, INT NewH,
                      INT BytesPerPixel, BYTE *Pixels, BOOL IsMips = TRUE );

    /* Texture create function.
     * ARGUMENTS:
     *   - texture file name:
     *       const std::string &FileName;
     * RETURNS:
     *   (texture &) self reference.
     */
    texture & Create( const std::string &FileName );

    /* Apply texture function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Apply( VOID );
  }; /* End of 'texture' class */

  /* Texture manager */
  class texture_manager : public resource_manager<texture>
  {
    texture_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'buffer_manager' function */

    friend class render;
  public:
    /* Texture create from file function.
     * ARGUMENTS:
     *   - texture file name:
     *       const std::string &FileName;
     * RETURNS:
     *   (texture *) texture pointer.
     */
    texture * CreateTexFromFile( const std::string &FileName )
    {                                       

       return resource_manager::Add(texture().Create(FileName)); 
    } /* End of 'CreateTexFromFile' function */

    /* Texture create function.
     * ARGUMENTS:
     *   - texture name:
     *       const std::string &NewName;
     *   - image size:
     *       INT NewW, NewH;
     *   - components count:
     *       INT BytesPerPixel;
     *   - image pixel data:
     *       VOID *Pixels;
     * RETURNS:
     *   (texture &) self reference.
     */
    texture * CreateTexture( const std::string &FileName, INT NewW, INT NewH,
                      INT BytesPerPixel, BYTE *Pixels, BOOL IsMips = TRUE )
    {                        
       texture *tc = resource_manager::Add(texture());
       tc->Create(FileName, NewW, NewH, BytesPerPixel, Pixels, IsMips);
       return tc; 
    } /* End of 'CreateTexture' function */
  }; /* End of 'texture_manager' class */
} /* end of 'tigl' namespace */

#endif /* __textures_h_ */

/* END OF 'textures.h' FILE */ 
