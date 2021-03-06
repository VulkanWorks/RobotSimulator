//--------------------------------------------------
// Robot Simulator
// vertexBuffer.cpp
// Date: 06/07/2020
// By Breno Cunha Queiroz
//--------------------------------------------------
#include "vertexBuffer.h"

VertexBuffer::VertexBuffer(Device* device, std::vector<Vertex> vertices):
	Buffer(device, sizeof(vertices[0])*vertices.size(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
{
}

VertexBuffer::~VertexBuffer()
{

}
