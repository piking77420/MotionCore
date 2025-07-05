#ifndef SHADER_H
#define SHADER_H

#include <unordered_map>
#include "math/toolbox_typedef.hpp"
#include "glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "math/complex.hpp"


class Shader
{
private:
    static constexpr uint32_t NULL_PROGRAMM = std::numeric_limits<uint32_t>::max();
public:

    Shader() = default;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath, bool fromMemory = false);
    
    Shader(Shader& other) 
    {
        if (other.m_Id != NULL_PROGRAMM)
        {
            m_Id = other.m_Id;
            other.m_Id = NULL_PROGRAMM;
        }
    }

    Shader(Shader&& other) noexcept
    {
        if (other.m_Id != NULL_PROGRAMM)
        {
            m_Id = other.m_Id;
            other.m_Id = NULL_PROGRAMM;
        }
    }
    
    ~Shader();

    Shader& operator=(Shader&& other) noexcept
    {
        if (other.m_Id != NULL_PROGRAMM)
        {
            m_Id = other.m_Id;
            other.m_Id = NULL_PROGRAMM;
        }

        return *this;
    }
        
    // activate the shader
    // ------------------------------------------------------------------------
    void Use() const;
 
    // utility uniform functions
    // ------------------------------------------------------------------------
    void SetBool(const std::string &name, bool value) const
    {         
        glUniform1i(GetUniformCacheId(name), (int)value); 
    }
    // ------------------------------------------------------------------------
    void SetInt(const std::string &name, int value) const
    { 
        glUniform1i(GetUniformCacheId(name), value); 
    }
    // ------------------------------------------------------------------------
    void SetFloat(const std::string &name, float value) const
    { 
        glUniform1f(GetUniformCacheId(name), value); 
    }
    // ------------------------------------------------------------------------
    void SetVec2(const std::string &name, const Tbx::Vector2f &value) const
    { 
        glUniform2fv(GetUniformCacheId(name), 1, &value[0]); 
    }
    void SetVec2(const std::string &name, float x, float y) const
    { 
        glUniform2f(GetUniformCacheId(name), x, y); 
    }
    // ------------------------------------------------------------------------
    void SetVec3(const std::string &name, const Tbx::Vector3f &value) const
    { 
        glUniform3fv(GetUniformCacheId(name), 1, &value[0]); 
    }
    void SetVec3(const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(GetUniformCacheId(name), x, y, z); 
    }
    // ------------------------------------------------------------------------
    void SetVec4(const std::string &name, const Tbx::Vector4f &value) const
    { 
        glUniform4fv(GetUniformCacheId(name), 1, &value[0]); 
    }
    void SetVec4(const std::string &name, float x, float y, float z, float w) const
    {
        int32_t loc = GetUniformCacheId(name);
        glUniform4f(loc, x, y, z, w); 
    }
    // ------------------------------------------------------------------------
    void SetMat2(const std::string &name, const Tbx::Matrix2x2f& mat) const
    {
        glUniformMatrix2fv(GetUniformCacheId(name), 1, GL_FALSE, &mat[0]);
    }
    // ------------------------------------------------------------------------
    void SetMat3(const std::string &name, const Tbx::Matrix3x3f& mat) const
    {
        glUniformMatrix3fv(GetUniformCacheId(name), 1, GL_FALSE, &mat[0]);
    }
    // ------------------------------------------------------------------------
    void SetMat4(const std::string &name, const Tbx::Matrix4x4f &mat) const
    {
        glUniformMatrix4fv(GetUniformCacheId(name), 1, GL_FALSE, &mat[0]);
    }

private:
    
    uint32_t m_Id = NULL_PROGRAMM;

    mutable std::unordered_map<std::string, int32_t> m_UniformLocationCache;

    int32_t GetUniformCacheId(const std::string& uniforString) const;
    
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
#endif