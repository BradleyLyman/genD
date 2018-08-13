#include <glad/glad.h>

#include "Shader.hpp"

#include <memory>

using namespace tetra;
using namespace std;

Shader::CompileError::CompileError(const string& msg) : runtime_error{msg} {}

Shader::Shader(Shader&& from) : id{0}, source{}
{
  swap(id, from.id);
  swap(source, from.source);
}

Shader::Shader(const std::string& source, Shader::Type type)
  : id{glCreateShader(static_cast<GLenum>(type))}, source{source}
{
}

Shader& Shader::operator=(Shader&& from)
{
  swap(id, from.id);
  return *this;
}

Shader::~Shader() { glDeleteShader(id); }

void Shader::compile()
{
  setSource();
  glCompileShader(handle());
  if (failedToCompile()) {
    throwCompileError();
  }
}

void Shader::setSource()
{
  const GLchar* src = source.data();
  glShaderSource(handle(), 1, &src, nullptr);
}

bool Shader::failedToCompile()
{
  GLint status = GL_FALSE;
  glGetShaderiv(handle(), GL_COMPILE_STATUS, &status);
  return !status;
}

void Shader::throwCompileError()
{
  GLint logSize = 0;
  glGetShaderiv(handle(), GL_INFO_LOG_LENGTH, &logSize);

  auto buffer = make_unique<char[]>(logSize);
  glGetShaderInfoLog(handle(), logSize, &logSize, buffer.get());

  throw CompileError(
    "Error " + string(buffer.get()) + " for shader: '" + source + "'");
}

GLuint Shader::handle() const { return id; }