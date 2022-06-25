#ifndef GLCRAFT_SHADER_HPP
#define GLCRAFT_SHADER_HPP


class Shader {
private:
    GLuint _program;

    static GLuint _buildShader(GLenum shaderType, const char* source) noexcept(false);
public:
    Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) noexcept(false);
    ~Shader();

    void use() const;
    void setValue(const std::string &name, bool value) const;
    void setValue(const std::string &name, int value) const;
    void setValue(const std::string &name, float value) const;
    void setValueMatrix4x4(const std::string &name, const mat4x4 matrix) const;

    static std::unique_ptr<Shader> fromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile) noexcept(false);
};


#endif //GLCRAFT_SHADER_HPP
