#include "Mesh2D.hpp"
#include "../glad/include/glad/glad.h"
#include "../ErrorInfo.hpp"
namespace JSGraphicsEngine3D {
	namespace Gui {

		GLenum GetOpenGLType(AttributeType type) {
			switch (type) {
			case AttributeType::FLOAT32:return GL_FLOAT;
			case AttributeType::FLOAT16:return GL_HALF_FLOAT;
			}

			JS_CORE_ASSERT(0, JS_ERROR_UNDEFINED_DATA_TYPE, "type is not a define enum value :( !!!");
			return GL_FLOAT;// although wrong but still 
		}

		void CheckGuiData(const GuiData& data) {
		#ifdef __JSDEBUG__
			
			//-- TODO - A well check on the data represantation if they get sence or not
		#endif

		}
		Mesh2D::Mesh2D(std::shared_ptr<GuiData>& data){
			CheckGuiData(*data);
			m_Data = data;
			// generate buffers
			GLCALL(glGenVertexArrays(1, &m_VAOId));
			GLCALL(glGenBuffers(1, &m_VertexBufferId));
			GLCALL(glGenBuffers(1, &m_IndexBufferId));

			// bind the vertex , index and vao
			GLCALL(glBindVertexArray(m_VAOId));
			GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId));
			GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId));
			
			//Set Data of the Vertex and Index Buffer
			GLCALL(glBufferData(GL_ARRAY_BUFFER, m_Data->Size, m_Data->Vertex, GL_STATIC_DRAW));
			GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Data->IndexSize, m_Data->IndexData, GL_STATIC_DRAW));

			//Get Stride
			uint32_t Stride = 0;
			for (uint8_t i = 0; i < m_Data->AttributesCount; i++) {
				Stride += m_Data->Attributes[i].Size;
			}

			//Set Attributes
			for (uint8_t i = 0; i < m_Data->AttributesCount; i++) {
				GLenum Type = GetOpenGLType(m_Data->Attributes[i].Type);
				
				
				GLCALL(glVertexAttribPointer(i, m_Data->Attributes[i].Count, Type,
					m_Data->Attributes[i].Normalize ? GL_TRUE : GL_FALSE,
					Stride, 0));
				
				GLCALL(glEnableVertexAttribArray(i));
			}

			//unbind them all
			GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
			GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			GLCALL(glBindVertexArray(0));

		}
		Mesh2D::~Mesh2D(void) {
			//unbind all currently bind buffers ? (That may produce errors in the future 
			GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
			GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			GLCALL(glBindVertexArray(0));
			GLCALL(glDeleteBuffers(1, &m_VertexBufferId));
			GLCALL(glDeleteBuffers(1, &m_IndexBufferId));
			GLCALL(glDeleteVertexArrays(1, &m_VAOId));

		}
		void Mesh2D::Bind(void) {
			// bind the vertex , index and vao
			GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId));
			GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId));
			GLCALL(glBindVertexArray(m_VAOId));
		}
		void Mesh2D::UnBind(void) {
			GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
			GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			GLCALL(glBindVertexArray(0));
		}
		void Mesh2D::Destroy(Mesh2D* ptr) {
			if (ptr)
			delete ptr;
		}
		Mesh2D* Mesh2D::Create(std::shared_ptr<GuiData>& data) {
			Mesh2D* ptr = new Mesh2D(data);
			JS_CORE_ASSERT_FATAL(ptr, JS_ERROR_NO_MEMORY, "No memory :( !!!");
			return ptr;
		}

		std::shared_ptr<GuiData> Mesh2D::GetData(void) const {
			return m_Data;
		}
	}
}