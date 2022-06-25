#include <fstream>
#include <sstream>
#include "glcraft.hpp"

Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) noexcept(false) {
    GLuint vertexShader = _buildShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
    GLuint fragmentShader = _buildShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

    _program = glCreateProgram();

    if (_program == GL_FALSE) {
        throw std::exception("Can't create shader program");
    }

    glAttachShader(_program, vertexShader);
    glAttachShader(_program, fragmentShader);

    glLinkProgram(_program);

    GLint linked = GL_FALSE;

    glGetProgramiv(_program, GL_LINK_STATUS, &linked);

    if (linked == GL_FALSE) {
        GLsizei log_length = 0;

        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &log_length);

        auto message = std::make_unique<GLchar>(log_length);
        glGetProgramInfoLog(_program, log_length, NULL, message.get());

        throw std::exception(message.get());
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint Shader::_buildShader(GLenum shaderType, const char* source) noexcept(false) {
    GLuint shader = glCreateShader(shaderType);

    if (!shader) {
        throw std::exception(shaderType == GL_VERTEX_SHADER ? "Can't create vertex shader" : "Can't create fragment shader");
    }

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint compiled;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (compiled != GL_TRUE) {
        GLsizei log_length = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

        auto message = std::make_unique<GLchar>(log_length);
        glGetShaderInfoLog(shader, log_length, NULL, message.get());

        throw std::exception(message.get());
    }

    return shader;
}

void Shader::use() const {
    glUseProgram(_program);
}

void Shader::setValue(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(_program, name.c_str()), (int)value);
}

void Shader::setValue(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(_program, name.c_str()), value);
}

void Shader::setValue(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(_program, name.c_str()), value);
}

void Shader::setValueMatrix4x4(const std::string &name, const float* matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, matrix);
}

Shader::~Shader() {
    if (_program != GL_FALSE) {
        glDeleteProgram(_program);
    }
}

std::string __openFile(const std::string& path) {
    std::ifstream s(path);
    std::stringstream ss;
    ss << s.rdbuf();
    return ss.str();
}

std::unique_ptr<Shader> Shader::fromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile) noexcept(false) {
    std::string vertexShader = __openFile(vertexShaderFile);
    std::string fragmentShader = __openFile(fragmentShaderFile);

    return std::make_unique<Shader>(vertexShader, fragmentShader);
}