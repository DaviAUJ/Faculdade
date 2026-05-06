#version 460

layout(location = 0) in vec2 a_pos;

out vec3 f_cor;

void main() {
   gl_Position = vec4(a_pos, 0.0f, 1.0f);
}