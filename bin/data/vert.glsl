#version 150

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec4 instanceColor;
in vec2 texcoord;


uniform sampler2D tex;
out vec4 color;
out vec2 texCoordVarying;

void main(){
    texCoordVarying = texcoord;
    float x = ((mod(gl_VertexID,256)/256));
    float y = (((gl_VertexID/256.)/256.));
    float d = pow(2,16);
    vec4 prex = texture(tex, vec2(x,y) );
    vec4 prey = texture(tex, vec2(x+0.5,y) );
    vec4 prez = texture(tex, vec2(x,y +0.5) );
    float xf = (prex.r/d) +  (prex.g ) +  ((prex.b * d));
    float yf = (prey.r/d) +  (prey.g ) +  ((prey.b * d));
    float zf = (prez.r/d) +  (prez.g ) +  ((prez.b * d));

     vec4 pre = vec4(xf,yf,zf,1);
    vec4 t = pre * vec4(1000,1000,1000,1);
    vec4 pos = vec4(t.x , t.y, t.z,position.w);

    color = texture(tex, vec2(x +0.5,y +0.5) );
	gl_Position = modelViewProjectionMatrix * pos;

}
