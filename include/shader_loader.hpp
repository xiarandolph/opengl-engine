#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class ShaderLoader {
public:
    ShaderLoader();
    ~ShaderLoader();
    GLuint create_program(char* vertex_shader_filename, char* fragment_shader_filename);

private:
    std::string read_shader_from_file(char* filename);
    GLuint create_shader(GLenum shader_type, std::string source, char* shader_name);
};