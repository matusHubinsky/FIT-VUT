#ifdef VERTEX_SHADER
//#define MAKE_STUDENT_RELEASE
#line 3

precision highp float;

uniform mat4 view;
uniform mat4 proj;

flat out int matrialId;

uniform highp float iTime;

mat4 rotationMatrix(float angle)
{
    float s = sin(angle);
    float c = cos(angle);
    mat4 res = mat4(1);
    res[0][0]=c;
    res[0][2]=s;
    res[2][0]=-s;
    res[2][2]=c;
    return res;
}

void drawCube(int ID, int material)
{
  uint indices[] = uint[](
    0u,1u,2u,2u,1u,3u,
    4u,5u,6u,6u,5u,7u,
    0u,4u,2u,2u,4u,6u,
    1u,5u,3u,3u,5u,7u,
    0u,1u,4u,4u,1u,5u,
    2u,3u,6u,6u,3u,7u
  );

  if (ID >= indices.length()) return;

  vec3 pos;
  for(uint i = 0u; i < 3u; i++) pos[i] = float((indices[ID] >> i) & 1u);

  matrialId = material;
  gl_Position = proj*view*rotationMatrix(iTime)*vec4(pos*2.f-1.f,1.f);
}

/*
void drawPyramid(int ID, int material)
{
  matrialId = material;
  const vec3 pyramid[] = vec3[] (

    vec3(0.0f, 0.0f, 0.0f),
    vec3(0.5f, 0.5f, 0.5f),
    vec3(0.0f, 1.0f, 0.0f),

    vec3(0.0f, 0.0f, 0.0f),
    vec3(0.5f, 0.5f, 0.5f),
    vec3(1.0f, 0.0f, 0.0f),

    vec3(1.0f, 0.0f, 1.0f),
    vec3(0.5f, 0.5f, 5.0f),
    vec3(1.0f, 1.0f, 1.0f),

    vec3(0.0f, 1.0f, 1.0f),
    vec3(0.5f, 0.5f, 5.0f),
    vec3(1.0f, 1.0f, 1.0f) 
    
    );

  gl_Position = proj*view*rotationMatrix(iTime)*vec4(vec3(pyramid), 1.0f);
}
*/

void main()
{
  gl_Position = vec4(0.f,0.f,0.f,1.f);

  drawCube(gl_VertexID, 0);
  // drawPyramid(gl_VertexID + 36, 1);
}
#endif



#ifdef FRAGMENT_SHADER

precision highp float;
precision highp float;

flat in int matrialId;

out highp vec4 fColor;

void main()
{
  if (matrialId == 0) fColor = vec4(1.0f, 1.0f, 0.0f, 1.f); // dom
  if (matrialId == 1) fColor = vec4(1.0f, 0.0f, 0.0f, 1.f); // strecha
}
#endif