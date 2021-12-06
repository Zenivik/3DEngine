#pragma once
#include "Renderer.h"
#include "Resource\Resource.h"
#include <vector>

namespace nc
{
	class VertexBuffer : public Resource
	{
	public:
		virtual ~VertexBuffer();
		VertexBuffer();

		bool Load(const std::string& name, void* null = nullptr) override;

		void CreateVertexBuffer(GLsizei size, GLsizei vertexCount, void* data);
		void SetAttribute(int index, GLint size, GLsizei stride, size_t offset);

		void CreateIndexBuffer(GLenum indexType, GLsizei indexCount, void* data);

		virtual void Draw(GLenum primitiveType = GL_TRIANGLES);

		void Bind() { glBindVertexArray(vao); }

	protected:
		GLuint vao = 0; // vertex array object
		GLuint vbo = 0; // vertex buffer object

		GLuint ibo = 0; 		// index buffer object
		GLuint indexCount = 0;  	// number of indices in index buffer
		GLenum indexType = 0;	// data type of index (GLushort or GLuint)

		GLuint vertexCount = 0; // number of vertices in vertex buffer
	};
}
