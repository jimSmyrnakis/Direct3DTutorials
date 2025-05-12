#include "DrawableButton.hpp"

static const char* vsource = R"(#version 430 core
layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec3 vColor;

out vec3 iColor;
out vec3 pos;
void main()
 {
	iColor = vColor;
	pos = vec3(vPosition , 1 );
	gl_Position = vec4(pos , 1);
 })";

static const char* fsource = R"(
#version 430 core
layout (location = 0) out vec4 fColor;
in vec3 iColor;
in vec3 pos;
void main(){
	fColor = vec4(pos.xy , 0.0f , 1.0);
})";


namespace JSGraphicsEngine3D {
	namespace Gui {

		bool					isInitiallize = false;
		std::shared_ptr<Shader> g_ButtonShader;
		std::shared_ptr<GuiData> g_ButtonData;
		std::shared_ptr<Mesh2D> g_ButtonMesh2D;

		float ButtonVertexBuffer[] = {
			-1.0f , +1.0f , 0.0f , 1.0f , 0.0f ,
			+1.0f , +1.0f , 1.0f , 1.0f , 0.0f ,
			+1.0f , -1.0f , 1.0f , 0.0f , 0.0f ,
			-1.0f , -1.0f , 0.0f , 0.0f , 0.0f 

		};

		uint16_t ButtonIndexBuffer[] = {
			0 , 1, 2 ,
			0,2,3
		};

		void InitButton(void) {
			if (isInitiallize) return;

			// Create Button Mesh Data
			g_ButtonData = std::make_shared<GuiData>();
			g_ButtonData->Vertex = ButtonVertexBuffer;
			g_ButtonData->Size = sizeof(ButtonVertexBuffer);
			g_ButtonData->IndexData = ButtonIndexBuffer;
			g_ButtonData->IndexSize = sizeof(ButtonIndexBuffer);

			g_ButtonData->Attributes = new Attribute[2];
			g_ButtonData->AttributesCount = 2;

			//vertices attribute
			g_ButtonData->Attributes[0].Count = 2; // x,y
			g_ButtonData->Attributes[0].Normalize = false;
			g_ButtonData->Attributes[0].Size = 2 * sizeof(float);
			g_ButtonData->Attributes[0].Type = AttributeType::FLOAT32;

			// color attribute
			g_ButtonData->Attributes[1].Count = 3; // r,g,b
			g_ButtonData->Attributes[1].Normalize = false;
			g_ButtonData->Attributes[1].Size = 3 * sizeof(float);
			g_ButtonData->Attributes[1].Type = AttributeType::FLOAT32;

			// Create Mesh
			g_ButtonMesh2D = std::make_shared<Mesh2D>(g_ButtonData);

			// Create Shader
			g_ButtonShader = std::make_shared<Shader>(vsource, fsource);
			

		}
		DrawableButton::DrawableButton(void) {
			InitButton();
			m_Drawable = Drawable::Create(g_ButtonMesh2D, g_ButtonShader);
		}

		DrawableButton::~DrawableButton(void) {
			Drawable::Destroy(m_Drawable);
		}

		Drawable& DrawableButton::GetDrawable(void) const { return *m_Drawable; }
		
	}
}