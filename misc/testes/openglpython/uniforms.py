import glfw
from OpenGL.GL import * # type: ignore
import OpenGL.GL.shaders as shaders
import numpy as np
import ctypes    
from shader import *

vertices = [
    [-0.8, -0.8],
    [ 0.8, -0.8],
    [ 0.8,  0.8],
    [-0.8,  0.8]
]

faces = [
    [0, 1, 2],
    [0, 2, 3]
]

colors = [
    [1, 0, 0],
    [0, 1, 0],
    [0, 0, 1],
    [1, 1, 0],
    [1, 0, 1],
    [0, 1, 1],
]

active_color = 0

def change_color():
    global active_color

    active_color = (active_color + 1) % len(colors) 

qtd_faces = len(faces)
qtd_vertices = len(vertices)
vao_id = int()
my_shader = None

def init():
    global vertices
    global vao_id
    global my_shader
    global faces

    glClearColor(1, 1, 1, 1)

    vao_id = glGenVertexArrays(1)
    glBindVertexArray(vao_id)

    tam_float = np.dtype(np.float32).itemsize
    vertices = np.array(vertices, np.float32)
    vbo_id = glGenBuffers(1)
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id)
    glBufferData(GL_ARRAY_BUFFER, vertices.nbytes, vertices, GL_STATIC_DRAW)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, tam_float * 2, ctypes.c_void_p(0))
    glEnableVertexAttribArray(0)

    faces = np.array(faces, np.uint32)
    ebo_id = glGenBuffers(1)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.nbytes, faces, GL_STATIC_DRAW)

    glBindBuffer(GL_ARRAY_BUFFER, 0)
    glBindVertexArray(0)

    my_shader = Shader("vertexshader.vert", "fragmentshader.frag");

def render():
    glClear(GL_COLOR_BUFFER_BIT)

    my_shader.bind() # pyright: ignore[reportOptionalMemberAccess]
    glBindVertexArray(vao_id)
    my_shader.setUniform("color", colors[active_color][0], colors[active_color][1], colors[active_color][2]) # pyright: ignore[reportOptionalMemberAccess]
    glDrawElements(GL_TRIANGLES, qtd_faces * 3, GL_UNSIGNED_INT, None)
    glBindVertexArray(0)
    my_shader.unbind() # pyright: ignore[reportOptionalMemberAccess]

def keyboard(window, key, scancode, action, mods):
    if action == glfw.RELEASE:
        if key == glfw.KEY_ESCAPE: glfw.set_window_should_close(window, True)
        if key == glfw.KEY_SPACE:  change_color()
        
def main():
    glfw.init()
    window = glfw.create_window(480, 480, "Teste", None, None)
    glfw.make_context_current(window)
    glfw.set_key_callback(window, keyboard)

    init()

    while not glfw.window_should_close(window):
        glfw.poll_events()
        render()
        glfw.swap_buffers(window)
    glfw.terminate()

if __name__ == "__main__":
   main() 