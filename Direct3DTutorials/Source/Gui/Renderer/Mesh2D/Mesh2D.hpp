#pragma once
#include "../../../Core.hpp"
#include <memory>
namespace JSGraphicsEngine3D {
	namespace Gui {
		enum class AttributeType {
			FLOAT32 ,
			FLOAT16
		};

		struct Attribute {
			uint8_t			Count;		// number of elements per attribute
			AttributeType	Type;		// type of each element
			uint8_t			Size;		// size of this struct
			bool            Normalize;	// true if you want the data to be normalized in the range -1 to 1
		};

		struct GuiData {
			void*					Vertex;			// the vertex buffer
			uint32_t				Size;			// Size of the vertex buffer
			Attribute*				Attributes;		// attributes that each vertex have
			uint8_t					AttributesCount;// the number of these attribute per vertex
			uint16_t*				IndexData;		// index buffer data (must exists)
			uint16_t				IndexSize;		// the size of this buffer
		};

		
		class Mesh2D {
		public:
			Mesh2D(std::shared_ptr<GuiData>& data );
			Mesh2D(const Mesh2D& cp) = delete;
			Mesh2D& operator=(const Mesh2D& cp) = delete;
			~Mesh2D(void);

		public:

			void Bind(void);
			void UnBind(void);

			std::shared_ptr<GuiData> GetData(void) const;

		public:
			static void Destroy(Mesh2D* ptr);
			static Mesh2D* Create(std::shared_ptr<GuiData>& data);

		private:

			std::shared_ptr<GuiData>		m_Data;
			uint32_t						m_IndexBufferId;
			uint32_t						m_VertexBufferId;
			uint32_t						m_VAOId;

		};
	}
}