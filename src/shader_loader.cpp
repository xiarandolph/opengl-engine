#include "shader_loader.hpp"
#include <iostream>
#include <fstream>
#include <vector>

ShaderLoader::ShaderLoader() {}

ShaderLoader::~ShaderLoader() {}

GLuint ShaderLoader::create_program(char* vertex_shader_filename, char* fragment_shader_filename) {
    std::string vertex_shader_src = read_shader_from_file(vertex_shader_filename);
    std::string fragment_shader_src = read_shader_from_file(fragment_shader_filename);

    GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_shader_src, "vertex shader");
    GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_shader_src, "fragment shader");

    int link_res = 0;
    // create program handle, attach shaders, link
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_res);
    if (link_res == GL_FALSE) {
        int log_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> log(log_length);
        glGetProgramInfoLog(program, log_length, NULL, &log[0]);
        std::cerr << "error: shader loader linking program" << std::endl << &log[0] << std::endl;
        return 0;
    }

    //glDetachShader(program, )

    // tag shaders for deletion
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

std::string ShaderLoader::read_shader_from_file(char* filename) {
    std::ifstream in(filename);
    if (!in.good()) {
        std::cerr << "error: could not read file " << filename << std::endl;
        std::terminate();
    }

    in.seekg(0, std::ios::end);
    std::size_t size = in.tellg();
    std::string shader_code(size, ' ');
    in.seekg(0);
    in.read(&shader_code[0], size);
    in.close();
    std::cout << "*****************\n" << shader_code << "**********" << std::endl;
    return shader_code;
}

GLuint ShaderLoader::create_shader(GLenum shader_type, std::string source, char* shader_name) {
    int res = 0;

    GLuint shader = glCreateShader(shader_type);
    const char* shader_code_ptr = source.c_str();
    const int shader_code_size = source.size();

    glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &res);

    if (res == GL_FALSE) {
        int log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> log(log_length);
        glGetShaderInfoLog(shader, log_length, NULL, &log[0]);
        std::cerr << "error: compiling shader: " << shader_name << std::endl << &log[0] << std::endl;
        return 0;
    }
    return shader;
}