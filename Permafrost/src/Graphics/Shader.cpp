#include "Permafrost/Graphics/Shader.h"

#include <fstream>
#include <glad/glad.h>

#include "Permafrost/Core/Log.h"

unsigned int GLShaderType(ShaderType ShaderType)
{
    switch (ShaderType)
    {
        case ShaderType::Vertex:                return GL_VERTEX_SHADER;
        case ShaderType::TesselationControl:    return GL_TESS_CONTROL_SHADER;
        case ShaderType::TesselationEvaluation: return GL_TESS_EVALUATION_SHADER;
        case ShaderType::Geometry:              return GL_GEOMETRY_SHADER;
        case ShaderType::Fragment:              return GL_FRAGMENT_SHADER;
        case ShaderType::Compute:               return GL_COMPUTE_SHADER;
    }
    return GL_FALSE;
}

static std::string ShaderTypeToString(GLenum ShaderType)
{
    switch (ShaderType)
    {
        case GL_VERTEX_SHADER:          return "Vertex";
        case GL_TESS_CONTROL_SHADER:    return "TesselationControl";
        case GL_TESS_EVALUATION_SHADER: return "TesselationEvaluation";
        case GL_GEOMETRY_SHADER:        return "Geometry";
        case GL_FRAGMENT_SHADER:        return "Fragment";
        case GL_COMPUTE_SHADER:         return "Compute";
    }
    return "Unknown";
}

static std::string GLSLTypeToString(GLenum GlslType)
{
    switch (GlslType)
    {
        case GL_FLOAT:              return "Float";
        case GL_FLOAT_VEC2:         return "Float2";
        case GL_FLOAT_VEC3:         return "Float3";
        case GL_FLOAT_VEC4:         return "Float4";
        case GL_INT:                return "Int";
        case GL_INT_VEC2:           return "Int2";
        case GL_INT_VEC3:           return "Int3";
        case GL_INT_VEC4:           return "Int4";
        case GL_UNSIGNED_INT:       return "UInt";
        case GL_UNSIGNED_INT_VEC2:  return "UInt2";
        case GL_UNSIGNED_INT_VEC3:  return "UInt3";
        case GL_UNSIGNED_INT_VEC4:  return "UInt4";
        case GL_FLOAT_MAT3:         return "Mat3";
        case GL_FLOAT_MAT4:         return "Mat4";
        case GL_SAMPLER_2D:         return "Texture";
    }
    return "Unknown";
}

Shader::Shader()
    : Handle(0)
    , Compiled(false)
    , Linked(false)
    , Valid(false)
{
    Handle = glCreateProgram();
}

Shader::~Shader()
{
    glDeleteProgram(Handle);
}

void Shader::Debug() const
{
    LOG_DEBUG("Shader(Compiled = {0}, Linked = {1}, Validated = {2})",
            IsCompiled(),
            IsLinked(),
            IsValid()
    );

    //Debug Compilation Errors
    if (!IsCompiled())
    {
        LOG_DEBUG("Compilation Status:");
        for (auto& Entry : CompilationStatus)
        {
            const std::string& ShaderType   = Entry.first;
            const std::string& InfoLog      = CompilationLog.at(ShaderType);
            LOG_DEBUG("{0} Shader({1}) : {2}",
                    ShaderType,
                    Entry.second ? " OK " : "FAIL",
                    InfoLog.empty() ? "No Info Log" : InfoLog
            );
        }
    }

    //Debug Linking Errors
    if (IsCompiled() && !IsLinked())
    {
        LOG_DEBUG("Linking Error : {0}", LinkingLog.empty() ? "No Info Log" : LinkingLog);
    }

    if (IsCompiled() && IsLinked() && !IsValid())
    {
        LOG_DEBUG("Validation Error : {0}", ValidationLog.empty() ? "No Info Log" : ValidationLog);
    }
}

bool Shader::Compile(const std::string& Filename)
{
    std::ifstream File(Filename);
    if (!File.is_open())
    {
        LOG_ERROR("Failed to open file '{0}'. Not found ?", Filename);
        return false;
    }

    ShaderSources Sources;
    ShaderType ShaderType = ShaderType::Invalid;
    std::string line;

    //Read line by line
    while (std::getline(File, line))
    {
        //Special comment handling (consume them and update the shader section)
        if (line.rfind("//Vertex Shader", 0) == 0)                  { ShaderType = ShaderType::Vertex               ; continue; }
        if (line.rfind("//TesselationControl Shader", 0) == 0)      { ShaderType = ShaderType::TesselationControl   ; continue; }
        if (line.rfind("//TesselationEvaluation Shader", 0) == 0)   { ShaderType = ShaderType::TesselationEvaluation; continue; }
        if (line.rfind("//Geometry Shader", 0) == 0)                { ShaderType = ShaderType::Geometry             ; continue; }
        if (line.rfind("//Fragment Shader", 0) == 0)                { ShaderType = ShaderType::Fragment             ; continue; }
        if (line.rfind("//Compute Shader", 0) == 0)                 { ShaderType = ShaderType::Compute              ; continue; }

        //Not a Section declaration Comment
        if (ShaderType != ShaderType::Invalid)
            Sources[ShaderType] += line + "\n";
    }
    return Compile(Sources);
}

bool Shader::Compile(const ShaderSources& ShaderSources)
{
    //Clear metadata
    CompilationLog.clear();
    CompilationStatus.clear();
    ShaderUniforms.clear();
    ShaderAttributes.clear();
    Compiled = false;
    Linked   = false;
    Valid    = false;

    //Compile each shader
    std::vector<unsigned int> Shaders;
    for (auto& ShaderSource : ShaderSources)
    {
        unsigned int ShaderType = GLShaderType(ShaderSource.first);
        const GLchar* Source    = ShaderSource.second.c_str();

        //Create Shader
        unsigned int Shader     = glCreateShader(ShaderType);
        Shaders.push_back(Shader);

        //Compile Shader
        glShaderSource(Shader, 1, &Source, 0);
        glCompileShader(Shader);
        //Fetch Compilation info
        {
            GLint maxLength = 0;
            glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> info_log = std::vector<GLchar>(maxLength);
            glGetShaderInfoLog(Shader, maxLength, &maxLength, &info_log[0]);
            //Fetch Compilation Status
            GLint IsCompiled = GL_FALSE;
            glGetShaderiv(Shader, GL_COMPILE_STATUS, &IsCompiled);
            
            //Store logs & compile status into the shader
            std::string ShaderTypeString        = ShaderTypeToString(ShaderType);
            CompilationLog[ShaderTypeString]    = std::string(info_log.begin(), info_log.end());
            CompilationStatus[ShaderTypeString] = IsCompiled == GL_TRUE;
        }
    }

    //Check for successful shader compilations
    Compiled = true;
    for (auto& shaderCompilation : CompilationStatus)
    {
        if (!shaderCompilation.second)
        {
            Compiled = false;
            break;
        }
    }

    //Linking phase
    if (Compiled)
    {
        //Attach shaders to program
        for (unsigned int shader : Shaders)
        {
            glAttachShader(Handle, shader);
        }

        //Link Program
        glLinkProgram(Handle);
        //Fetch linking info
        {
            GLint IsLinked = GL_FALSE;
            glGetProgramiv(Handle, GL_LINK_STATUS, &IsLinked);
            GLint maxLength = 0;
            glGetProgramiv(Handle, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> info_log = std::vector<GLchar>(maxLength);
            glGetProgramInfoLog(Handle, maxLength, &maxLength, &info_log[0]);

            LinkingLog  = std::string(info_log.begin(), info_log.end());
            Linked      = IsLinked == GL_TRUE;
        }

        //Detatch shaders from program
        for (unsigned int shader : Shaders)
        {
            glDetachShader(Handle, shader);
        }
    }

    //Validation phase
    if (Linked)
    {
        //Validate program
        glValidateProgram(Handle);
        //Fetch validation info
        {
            GLint IsValid = GL_FALSE;
            glGetProgramiv(Handle, GL_VALIDATE_STATUS, &IsValid);
            GLint maxLength = 0;
            glGetProgramiv(Handle, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> info_log = std::vector<GLchar>(maxLength);
            glGetProgramInfoLog(Handle, maxLength, &maxLength, &info_log[0]);

            ValidationLog   = std::string(info_log.begin(), info_log.end());
            Valid           = IsValid == GL_TRUE;
        }
    }

    //Query for active uniforms
    if (Valid)
    {
        //Fetch Uniforms
        GLint UniformCount;
        glGetProgramiv(Handle, GL_ACTIVE_UNIFORMS, &UniformCount);
        for (int Index = 0; Index < UniformCount; Index++)
        {
            //Read active uniform data
            GLchar  Name[256];
            GLsizei NameLength;
            GLsizei Size;
            GLenum  Type;
            glGetActiveUniform(Handle, Index, sizeof(Name), &NameLength, &Size, &Type, Name);
            //Store data into the ShaderUniforms
            ShaderUniform Uniform;
            Uniform.Index = Index;
            Uniform.Location = glGetUniformLocation(Handle, Name);
            Uniform.Name  = std::string(Name);
            Uniform.Size  = Size;
            Uniform.Type  = Type;
            ShaderUniforms[Uniform.Name] = Uniform;
        }

        //Fetch Attributes
        GLint AttributeCount;
        glGetProgramiv(Handle, GL_ACTIVE_ATTRIBUTES, &AttributeCount);
        for (int Index = 0; Index < AttributeCount; Index++)
        {
            //Read active attribute data
            GLchar  Name[256];
            GLsizei NameLength;
            GLsizei Size;
            GLenum  Type;
            glGetActiveAttrib(Handle, Index, sizeof(Name), &NameLength, &Size, &Type, Name);
            //Store data into the ShaderUniforms
            ShaderAttribute Attribute;
            Attribute.Index = Index;
            Attribute.Name  = std::string(Name);
            Attribute.Size  = Size;
            Attribute.Type  = Type;
            ShaderAttributes[Attribute.Name] = Attribute;
        }
    }
    
    //Delete shaders
    for (unsigned int Shader : Shaders)
    {
        glDeleteShader(Shader);
    }

    return Valid;
}

void Shader::Bind() const
{
    glUseProgram(Handle);
}


void Shader::SetUniform(const std::string& Name, int Value)
{
    auto Uniform = ShaderUniforms.find(Name);
    if (Uniform == ShaderUniforms.end())
    {
        LOG_WARNING("Uniform {0} doesn't exist or is inactive.", Name);
        return;
    }
    unsigned int Location = Uniform->second.Location;
    
    glUniform1i(Location, Value);
}

void Shader::SetUniform(const std::string& Name, float Value)
{
    auto uniform = ShaderUniforms.find(Name);
    if (uniform == ShaderUniforms.end())
    {
        LOG_WARNING("Uniform {0} doesn't exist or is inactive.", Name);
        return;
    }
    unsigned int Location = uniform->second.Location;

    glUniform1f(Location, Value);
}

void Shader::SetUniform(const std::string& Name, const glm::vec2& Value)
{
    auto uniform = ShaderUniforms.find(Name);
    if (uniform == ShaderUniforms.end())
    {
        LOG_WARNING("Uniform {0} doesn't exist or is inactive.", Name);
        return;
    }
    unsigned int Location = uniform->second.Location;

    glUniform2f(Location, Value.x, Value.y);
}

void Shader::SetUniform(const std::string& Name, const glm::vec3& Value)
{
    auto uniform = ShaderUniforms.find(Name);
    if (uniform == ShaderUniforms.end())
    {
        LOG_WARNING("Uniform {0} doesn't exist or is inactive.", Name);
        return;
    }
    unsigned int Location = uniform->second.Location;

    glUniform3f(Location, Value.x, Value.y, Value.z);
}

void Shader::SetUniform(const std::string& Name, const glm::vec4& Value)
{
    auto uniform = ShaderUniforms.find(Name);
    if (uniform == ShaderUniforms.end())
    {
        LOG_WARNING("Uniform {0} doesn't exist or is inactive.", Name);
        return;
    }
    unsigned int Location = uniform->second.Location;
    glUniform4f(Location, Value.x, Value.y, Value.z, Value.w);
}

void Shader::SetUniform(const std::string& Name, const glm::mat3& Value)
{
    auto uniform = ShaderUniforms.find(Name);
    if (uniform == ShaderUniforms.end())
    {
        LOG_WARNING("Uniform {0} doesn't exist or is inactive.", Name);
        return;
    }
    unsigned int Location = uniform->second.Location;

    glUniformMatrix3fv(Location, 1, GL_FALSE, &Value[0][0]);
}

void Shader::SetUniform(const std::string& Name, const glm::mat4& Value)
{
    auto uniform = ShaderUniforms.find(Name);
    if (uniform == ShaderUniforms.end())
    {
        LOG_WARNING("Uniform {0} doesn't exist or is inactive.", Name);
        return;
    }
    unsigned int Location = uniform->second.Location;
    glUniformMatrix4fv(Location, 1, GL_FALSE, &Value[0][0]);
}