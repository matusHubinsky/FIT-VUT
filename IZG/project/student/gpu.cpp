/*!
 * @file
 * @brief This file contains implementation of gpu
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */

#include <student/gpu.hpp>


uint32_t ID32(VertexArray const &vao, uint32_t id)
{
  uint32_t*ind = (uint32_t*)vao.indexBuffer;
  return ind[id];
}


uint16_t ID16(VertexArray const &vao, uint32_t id)
{
  uint16_t*ind = (uint16_t*)vao.indexBuffer;
  return ind[id];
}


uint8_t ID8(VertexArray const &vao, uint32_t id)
{
  uint8_t*ind = (uint8_t*)vao.indexBuffer;
  return ind[id];
}


void setIndex(VertexArray const &vao, InVertex * inVertex, uint32_t id)
{
  if (vao.indexBuffer == nullptr)
  {
    inVertex -> gl_VertexID = id;
  }
  else if (vao.indexType == IndexType::UINT32)
  {
    inVertex -> gl_VertexID = ID32(vao, id);
  }
  else if (vao.indexType == IndexType::UINT16)
  {
    inVertex -> gl_VertexID = ID16(vao, id);
  }
  else if (vao.indexType == IndexType::UINT8)
  {
    inVertex -> gl_VertexID = ID8(vao, id);
  }
}


/*
void setAtributes(VertexAttrib const attrib[maxAttributes], InVertex * inVertex)
{
  for (uint32_t i = 0; i < maxAttributes; i++)
  {
    uint32_t ID = inVertex -> gl_VertexID;
    // AtribType FLOAT
    uint64_t stride = attrib[i].stride;
    uint64_t offest = attrib[i].offset;
    uint8_t * buf_ptr = (uint8_t *) attrib[i].bufferData;
    uint8_t * int_ptr;

    // if (...)

    int_ptr = buf_ptr + offset + stride*gl_VertexID
    
  }
}
*/

//! [drawImpl]
void drawImpl(GPUContext &ctx, uint32_t nofVertices)
{
  for (uint32_t i = 0; i < nofVertices; i++)
  {
    InVertex inVertex; 
    setIndex(ctx.vao, &inVertex, i);
    // setAtributes(ctx.vao.vertexAttrib, &inVertex);
    OutVertex outVertex;
    ctx.prg.vertexShader(outVertex, inVertex, ctx.prg.uniforms);
  }
  /// \todo Tato funkce vykreslí trojúhelníky podle daného nastavení.<br>
  /// ctx obsahuje aktuální stav grafické karty.
  /// Parametr "nofVertices" obsahuje počet vrcholů, který by se měl vykreslit (3 pro jeden trojúhelník).<br>
  /// Bližší informace jsou uvedeny na hlavní stránce dokumentace.
}
//! [drawImpl]

/**
 * @brief This function reads color from texture.
 *
 * @param texture texture
 * @param uv uv coordinates
 *
 * @return color 4 floats
 */
glm::vec4 read_texture(Texture const&texture,glm::vec2 uv){
  if(!texture.data)return glm::vec4(0.f);
  auto uv1 = glm::fract(uv);
  auto uv2 = uv1*glm::vec2(texture.width-1,texture.height-1)+0.5f;
  auto pix = glm::uvec2(uv2);
  //auto t   = glm::fract(uv2);
  glm::vec4 color = glm::vec4(0.f,0.f,0.f,1.f);
  for(uint32_t c=0;c<texture.channels;++c)
    color[c] = texture.data[(pix.y*texture.width+pix.x)*texture.channels+c]/255.f;
  return color;
}

/**
 * @brief This function clears framebuffer.
 *
 * @param ctx GPUContext
 * @param r red channel
 * @param g green channel
 * @param b blue channel
 * @param a alpha channel
 */
void clear(GPUContext&ctx,float r,float g,float b,float a){
  auto&frame = ctx.frame;
  auto const nofPixels = frame.width * frame.height;
  for(size_t i=0;i<nofPixels;++i){
    frame.depth[i] = 10e10f;
    frame.color[i*4+0] = static_cast<uint8_t>(glm::min(r*255.f,255.f));
    frame.color[i*4+1] = static_cast<uint8_t>(glm::min(g*255.f,255.f));
    frame.color[i*4+2] = static_cast<uint8_t>(glm::min(b*255.f,255.f));
    frame.color[i*4+3] = static_cast<uint8_t>(glm::min(a*255.f,255.f));
  }
}

