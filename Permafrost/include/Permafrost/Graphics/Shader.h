#pragma once

#include <glm/glm.hpp>

#include "Permafrost/Core/CommonTypes.h"

enum ShaderType
{
    Invalid = 0,
    Vertex,
    TesselationControl, TesselationEvaluation,
    Geometry, Fragment,
    Compute
};

u32 GLShaderType(ShaderType ShaderType);

/// Represents a single uniform in the program
struct ShaderUniform
{
    std::string Name;
    u32         Index;
    u32         Location;
    u32         Size;
    u32         Type;
};

/// Represents a single attribute in the vertex shader
struct ShaderAttribute
{
    std::string     Name;
    u32             Index;
    u32             Size;
    u32             Type;
};

using ShaderSources         = std::unordered_map<ShaderType, std::string>;
using ShaderCompilationLogs = std::unordered_map<std::string, std::string>;
using ShaderCompileStatuses = std::unordered_map<std::string, bool>;
using ShaderUniforms        = std::unordered_map<std::string, ShaderUniform>;
using ShaderAttributes      = std::unordered_map<std::string, ShaderAttribute>;


class Shader
{
public:
    Shader();
    ~Shader();

    void Debug() const;
    bool Compile(const std::string& Filename);
    bool Compile(const ShaderSources& Sources);

    void Bind() const;
    
    inline bool                         IsCompiled() const { return Compiled; }
    inline bool                         IsValid() const { return Valid; }
    inline bool                         IsLinked() const { return Linked; }
    inline const ShaderCompilationLogs& GetCompilationLog() const { return CompilationLog; }
    inline const ShaderCompileStatuses& GetCompilationStatus() const { return CompilationStatus; }
    inline const ShaderUniforms&        GetShaderUniforms() const { return ShaderUniforms; }
    inline const std::string&           GetLinkingLog() const { return LinkingLog; }
    inline const std::string&           GetValidationLog() const { return ValidationLog; }


    void SetUniform(const std::string& Name, i32                Value);
    void SetUniform(const std::string& Name, f32                Value);
    void SetUniform(const std::string& Name, const glm::vec2&   Value);
    void SetUniform(const std::string& Name, const glm::vec3&   Value);
    void SetUniform(const std::string& Name, const glm::vec4&   Value);
    void SetUniform(const std::string& Name, const glm::mat3&   Value);
    void SetUniform(const std::string& Name, const glm::mat4&   Value);

private:
    u32                     Handle;

    //Shader Metadata
    ShaderCompilationLogs   CompilationLog;
    ShaderCompileStatuses   CompilationStatus;
    ShaderUniforms          ShaderUniforms;
    ShaderAttributes        ShaderAttributes;
    bool                    Compiled;
    std::string             LinkingLog;
    bool                    Linked;
    std::string             ValidationLog;
    bool                    Valid;

};