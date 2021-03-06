#ifndef tp_maps_BasicTexture_h
#define tp_maps_BasicTexture_h

#include "tp_maps/Texture.h"

#include "tp_utils/TPPixel.h"
#include "tp_utils/RefCount.h"

namespace tp_maps
{

//##################################################################################################
struct TextureData
{
  size_t w{0};
  size_t h{0};
  //Used for textures that have been padded to make them a power of 2.
  //These will be a value between 0.5f and 1.0f.
  float fw{1.0f};
  float fh{1.0f};
  const TPPixel* data{nullptr};

  //################################################################################################
  TextureData clone()const;

  //################################################################################################
  //! Clone the texture and pad to a power of 2
  TextureData clone2()const;

  //################################################################################################
  void destroy();
};

//##################################################################################################
class BasicTexture : public Texture
{
  TDP_REF_COUNT_OBJECTS("BasicTexture");
public:
  //################################################################################################
  BasicTexture(Map* map, const TextureData& image=TextureData());

  //################################################################################################
  ~BasicTexture() override;

  //################################################################################################
  void setImage(const TextureData& image);

  //################################################################################################
  bool imageReady()override;

  //################################################################################################
  GLuint bindTexture()override;

  //################################################################################################
  //! Creates and binds a texure with the given image
  /*!
  \param img: The bitmap image for the texture
  \param target: The target type (normally GL_TEXTURE_2D)
  \param format: The format (normally GL_RGBA)
  \param magFilterOption: The texture magnification function to use
  \param minFilterOption: The texture minifying function to use
  \return the id for the new texture
  */
  GLuint bindTexture(const TextureData& img,
                     GLenum target,
                     GLint format,
                     GLuint magFilterOption,
                     GLuint minFilterOption);

  //################################################################################################
  glm::vec2 textureDims()const override;

  //################################################################################################
  glm::vec2 imageDims()const override;

private:
  struct Private;
  Private* d;
  friend struct Private;
};

}

#endif
