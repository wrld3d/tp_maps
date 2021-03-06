#ifndef tp_maps_Shader_h
#define tp_maps_Shader_h

#include "tp_maps/Globals.h"

#include "lib_platform/Polyfill.h"

#include <functional>

namespace tp_maps
{
enum class ShaderType
{
  Render,
  Picking
};

}

TP_ENUM_HASH(tp_maps::ShaderType)

namespace tp_maps
{
class Map;
class ShaderPointer;

//##################################################################################################
//! The base class for shaders.
/*!
This allows the map to cache shaders.
*/
class TP_MAPS_SHARED_EXPORT Shader
{
  friend class Map;
public:
  //################################################################################################
  Shader();

  //################################################################################################
  virtual ~Shader();

  //################################################################################################
  void compile(const char* vertexShaderStr,
               const char* fragmentShaderStr,
               const std::function<void(GLuint)>& bindLocations,
               const std::function<void(GLuint)>& getLocations,
               ShaderType shaderType = ShaderType::Render);

  //################################################################################################
  virtual void use(ShaderType shaderType = ShaderType::Render);

  //################################################################################################
  GLuint loadShader(const char* shaderSrc, GLenum type);

  //################################################################################################
  bool error()const;

private:
  //################################################################################################
  void invalidate();

private:
  struct Private;
  Private* d;
  friend struct Private;
  friend class ShaderPointer;
  mutable std::vector<ShaderPointer*> m_pointers;
};

//##################################################################################################
class ShaderPointer
{
  friend class Shader;
  const Shader* m_shader;
public:
  //################################################################################################
  ShaderPointer(const Shader* shader);

  //################################################################################################
  ~ShaderPointer();

  //################################################################################################
  const Shader* shader() const;
};

}

#endif
