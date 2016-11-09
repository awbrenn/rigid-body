//varying vec3 vertex_color;
//
//void main() {
//  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
//  vertex_color = gl_Vertex.xyz;
//}

varying vec3 normal;
varying vec3 position;

void main() {
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
  normal = gl_Normal;
  position = gl_Vertex.xyz;
}