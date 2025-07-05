#include "shader.h"

#include "glad/glad.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath, bool fromMemory)
{
    const char* vShaderCode = nullptr;
    const char * fShaderCode = nullptr;
    
    if (!fromMemory)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();		
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();			
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        vShaderCode = vertexCode.c_str();
        fShaderCode = fragmentCode.c_str();
    }
    else
    {
        vShaderCode = vertexPath;
        fShaderCode = fragmentPath;
    }
      
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        m_Id = glCreateProgram();
        glAttachShader(m_Id, vertex);
        glAttachShader(m_Id, fragment);
        glLinkProgram(m_Id);
        checkCompileErrors(m_Id, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);

}

Shader::~Shader()
{
    if (m_Id != NULL_PROGRAMM)
    {
        glDeleteProgram(m_Id);
        m_Id = NULL_PROGRAMM;
    }
}

void Shader::Use() const
{
    if (m_Id == NULL_PROGRAMM)
    {
        std::cout << "ERROR::SHADER::PROGRAM" << '\n';
        return;
    }
    
    glUseProgram(m_Id); 
}

int32_t Shader::GetUniformCacheId(const std::string& uniforString) const
{
    auto it = m_UniformLocationCache.find(uniforString);
    if (it != m_UniformLocationCache.end())
    {
        return it->second;
    }

    const int32_t loc = glGetUniformLocation(m_Id, uniforString.c_str());
    m_UniformLocationCache[uniforString] = loc;
    return loc;
}
