#pragma once

#include "../../Core.hpp"
#include "Glad/include/glad/glad.h"

namespace JSGraphicsEngine3D {
	
	enum class Filters0 { // for not mip map textures
		LINEAR , 
		NEAREST,

	};

	uint32_t GetOpenGLFilterValue(Filters0 fil) {
		switch (fil) {
		case Filters0::LINEAR: return GL_LINEAR;
		case Filters0::NEAREST:return GL_NEAREST;
		}
		JS_CORE_WARN(JS_WARNING_UNDEFINED_FILTER, "Undefined Texture Filter :( !!!");
		return GL_LINEAR;
	}

	uint32_t CreateDepthMapTexture(uint32_t width , uint32_t height , Filters0 Minification , Filters0 Magnification) {
		if (!height || !width) {
			JS_CORE_ASSERT(0, JS_ERROR_BAD_DIMENSIONS, "At CreateDepthMapTexture method width or height where zero !!!");
			return 0;
		}
		uint32_t TextureObjectName;
		
		
		glGenTextures(1, &TextureObjectName);
		if (TextureObjectName == 0) {
			JS_CORE_ASSERT(0, JS_ERROR_FAILED_GENERATE_TEXTURE, "At CreateDepthMapTexture failed to generate texture !!!");
			return 0;
		}

		glBindTexture(GL_TEXTURE_2D, TextureObjectName);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,	// the first mip map
			GL_DEPTH_COMPONENT,
			width,
			height,
			0 , // reserved
			GL_DEPTH_COMPONENT,
			GL_FLOAT ,
			nullptr 
		);

		GL_NEAREST;

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetOpenGLFilterValue(Magnification));
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetOpenGLFilterValue(Minification));

		return TextureObjectName;
	}

	void FramebufferDepthMapConfigure(uint32_t FramebufferObjectName , uint32_t DepthTextureObjectName) {
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferObjectName);
		glFramebufferTexture(GL_TEXTURE_2D, GL_DEPTH_ATTACHMENT, DepthTextureObjectName, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		JS_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
			JS_ERROR_FRAMEBUFFER_FAILED, "Failed to create the frame buffer for the depth map !!!");
	}
}