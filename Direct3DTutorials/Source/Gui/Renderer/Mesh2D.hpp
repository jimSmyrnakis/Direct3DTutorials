#pragma once
#include "../../Core.hpp"
#include <memory>
namespace JSGraphicsEngine3D {
	namespace Gui {
		enum class AttributeType {
			FLOAT32 ,
			FLOAT16
		};

		struct Attribute {
			uint8_t			Count;
			AttributeType	Type;
			uint8_t			Size; // size of this struct
			bool            Normalize; // true if you want the data to be normalized in the range -1 to 1
		};

		struct GuiData {
			float*					Data;
			uint32_t				Size;
			Attribute*				Attributes;
			uint8_t					AttributesCount;
			uint16_t*				IndexData;
			uint32_t				IndexSize;
		};

		
		class Mesh2D {
		private:
			Mesh2D(std::shared_ptr<GuiData> data );
			Mesh2D(const Mesh2D& cp) = delete;
			Mesh2D& operator=(const Mesh2D& cp) = delete;
			~Mesh2D(void);

		public:

			void Bind(void);
			void UnBind(void);

		public:
			static void Destroy(Mesh2D* ptr);
			static Mesh2D* Create(std::shared_ptr<GuiData> data);

		private:

			std::shared_ptr<GuiData>		m_Data;
			uint32_t						m_IndexBufferId;
			uint32_t						m_VertexBufferId;
			uint32_t						m_VAOId;

		};
	}
}