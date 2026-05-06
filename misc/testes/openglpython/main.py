import glfw
from OpenGL.GL import * # type: ignore
import OpenGL.GL.shaders as shaders
import numpy as np
import ctypes    

vertices = [
    [-0.8, -0.8, 1.0, 0.0, 0.0],
    [ 0.0, -0.8, 1.0, 1.0, 0.0],
    [-0.4,  0.0, 1.0, 0.0, 1.0],
    [ 0.0, -0.8, 1.0, 1.0, 0.0],
    [ 0.8, -0.8, 0.0, 1.0, 0.0],
    [ 0.4,  0.0, 0.0, 1.0, 1.0],
    [-0.4,  0.0, 1.0, 0.0, 1.0],
    [ 0.4,  0.0, 0.0, 1.0, 1.0],
    [ 0.0,  0.8, 0.0, 0.0, 1.0],
]

qtd_vertices = len(vertices)
vao_id = int()
shader_id = int()

def init():
    global vertices
    global vao_id
    global shader_id

    glClearColor(1, 1, 1, 1)

    vao_id = glGenVertexArrays(1)
    glBindVertexArray(vao_id)

    tam_float = np.dtype(np.float32).itemsize;
    vertices = np.array(vertices, np.dtype(np.float32))
    vbo_id = glGenBuffers(1)
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id)
    glBufferData(GL_ARRAY_BUFFER, vertices.nbytes, vertices, GL_STATIC_DRAW)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, tam_float * 5, ctypes.c_void_p(0))
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, tam_float * 5, ctypes.c_void_p(2 * tam_float))
    glEnableVertexAttribArray(0)
    glEnableVertexAttribArray(1)

    glBindBuffer(GL_ARRAY_BUFFER, 0)
    glBindVertexArray(0)

    vs_source = open("vertexshader.vert").read()
    fs_source = open("fragmentshader.frag").read()

    vs_id = shaders.compileShader(vs_source, GL_VERTEX_SHADER)
    fs_id = shaders.compileShader(fs_source, GL_FRAGMENT_SHADER)
    shader_id = shaders.compileProgram(vs_id, fs_id)

    #vs_id = glCreateShader(GL_VERTEX_SHADER)
    #glShaderSource(vs_id, vs_source)
    #glCompileShader(vs_id)
    #if not glGetShaderiv(vs_id, GL_COMPILE_STATUS):
    #    info = glGetShaderInfoLog(vs_id)
    #    raise Exception(f"Erro de compilação no vertex shader: {info}")

    #fs_id = glCreateShader(GL_VERTEX_SHADER)
    #glShaderSource(fs_id, fs_source)
    #glCompileShader(fs_id)
    #if not glGetShaderiv(fs_id, GL_COMPILE_STATUS):
    #    info = glGetShaderInfoLog(fs_id)
    #    raise Exception(f"Erro de compilação no fragment shader: {info}")

    #shader_id = glCreateProgram()
    #glAttachShader(shader_id, vs_id)
    #glAttachShader(shader_id, fs_id)
    #glLinkProgram(shader_id)


def render():
    glClear(GL_COLOR_BUFFER_BIT)

    glUseProgram(shader_id)
    glBindVertexArray(vao_id)
    glDrawArrays(GL_TRIANGLES, 0, qtd_vertices)
    glBindVertexArray(0)
    glUseProgram(0)

def main():
    glfw.init()
    window = glfw.create_window(480, 480, "Teste", None, None)
    glfw.make_context_current(window)
    init()

    while not glfw.window_should_close(window):
        glfw.poll_events()
        render()
        glfw.swap_buffers(window)
    glfw.terminate()

if __name__ == "__main__":
   main() 