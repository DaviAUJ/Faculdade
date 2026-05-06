from OpenGL.GL import * # type: ignore
import OpenGL.GL.shaders as shaders

class Shader:
    shader_id = int()

    def __init__(self, vertex_shader_file_name, fragment_shader_file_name):
        vs_source = open(vertex_shader_file_name, "r").read()
        fs_source = open(fragment_shader_file_name, "r").read()

        vs_id = shaders.compileShader(vs_source, GL_VERTEX_SHADER)
        fs_id = shaders.compileShader(fs_source, GL_FRAGMENT_SHADER)
        self.shader_id = shaders.compileProgram(vs_id, fs_id)

    def bind(self):
        glUseProgram(self.shader_id)

    def unbind(self):
        glUseProgram(0)

    def setUniform(self, name, x, y=None, z=None, w=None):
        name_loc = glGetUniformLocation(self.shader_id, name)

        if   y == None: glUniform1f(name_loc, x)
        elif z == None: glUniform2f(name_loc, x, y)
        elif w == None: glUniform3f(name_loc, x, y, z)
        else:           glUniform4f(name_loc, x, y, z, w)