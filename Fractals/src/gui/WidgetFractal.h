#pragma once

#include <QLabel>
#include "ui_WidgetFractal.h"

#include <qopenglwidget.h>
#if defined(__OSX__)
#include <OpenGL/glew.h>
#else
#include <gl/GL.h>
#endif

class WidgetFractal : public QLabel
{
	Q_OBJECT

public:
	WidgetFractal(QWidget *parent = Q_NULLPTR);
	~WidgetFractal();

	void setDragMode(bool drag) { myIsDragMode = drag;}

signals:
	void signalRightButtonDrawFractal(int startX, int startY, int endX, int endY, float angle);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent * event) override;

private:
	Ui::WidgetFractal ui;

	bool myIsPressed;
	int myStartX;
	int myStartY;
	int myEndX;
	int myEndY;

	bool myIsDragMode;
	QPoint myLastMousePos;
	QPoint myPixmapOffset;
	double myAngle;
	int myButtonPressed;
	QPoint myFirstMousePos;
};

//class WidgetFractal2 : public QOpenGLWidget
//{
//public:
//	WidgetFractal2(QWidget *parent) : QOpenGLWidget(parent) { }
//
//protected:
//	void initializeGL() override
//	{
//		/* Generate an identifier */
//		glGenTextures(1, &myId);
//	}
//
//	void paintGL() override
//	{
//		glBindTexture(m_glType, myId);
//
//		Bitmap *bitmap = getBitmap();
//
//		uint8_t *ptr = bitmap->getUInt8Data() +
//			bitmap->getBytesPerPixel() * (offset.x + offset.y * bitmap->getWidth());
//
//		glPixelStorei(GL_UNPACK_ROW_LENGTH, bitmap->getWidth());
//		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//		glTexSubImage2D(m_glType, 0, offset.x, offset.y, size.x, size.y,
//			m_format, m_dataFormat, ptr);
//		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
//
//		//// Draw the scene:
//		//QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
//		//f->glClear(GL_COLOR_BUFFER_BIT);
//		//...
//	}
//	
//	protected:
//		GLuint myId;
//	
//	};

//class WidgetFractal2 : public QOpenGLWidget
//{
//public:
//	WidgetFractal2(QWidget *parent) : QOpenGLWidget(parent) { }
//
//protected:
//	void initializeGL() override
//	{
//		if (m_fbType == ENone)
//			Log(ETrace, "Uploading a texture : %s", toString().c_str());
//		else
//			Log(ETrace, "Creating a framebuffer : %s", toString().c_str());
//
//		if (m_samples > 1) {
//			int maxSamples = 1;
//			if (GLEW_ARB_texture_multisample)
//				glGetIntegerv(GL_MAX_SAMPLES_EXT, &maxSamples);
//			if (m_samples > maxSamples) {
//				Log(EWarn, "Attempted to create a multisample framebuffer "
//					"with an unsupported number of samples (requested=%i, supported=%i)",
//					m_samples, maxSamples);
//				m_samples = maxSamples;
//			}
//		}
//
//
//		/* Generate an identifier */
//		glGenTextures(1, &myId);
//
//		/* Bind to the texture */
//		glBindTexture(m_glType, m_id);
//
//		/* Set the texture filtering / wrapping modes
//		(don't do this for multisample textures)*/
//		if (!((m_fbType & EColorBuffer) && m_samples > 1))
//			configureTexture(); /* Multisample textures don't have these parameters */
//
//		if (m_fbType == ENone) {
//			Assert(m_samples == 1);
//			refresh();
//		}
//		else {
//			/* Create the FBO and bind it */
//			glGenFramebuffersEXT(1, &m_fboId);
//			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fboId);
//
//			AssertEx(glIsFramebufferEXT(m_fboId), "Creating an FBO failed");
//			bool depthAsTexture = m_fbType & EDepthBuffer;
//
//			switch (m_fbType) {
//			case EColorAndDepthBuffer:
//			case EColorBuffer: {
//				if (m_type == ETexture2D) {
//					if (!depthAsTexture) {
//						glGenRenderbuffersEXT(1, &m_depthId);
//						glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_depthId);
//						if (m_samples == 1)
//							glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT,
//								GL_DEPTH_COMPONENT32, m_size.x, m_size.y);
//						else
//							glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT,
//								m_samples, GL_DEPTH_COMPONENT32, m_size.x, m_size.y);
//						glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,
//							GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_depthId);
//					}
//					else {
//						glGenTextures(1, &m_depthId);
//						glBindTexture(m_glType, m_depthId);
//						configureTexture();
//						glTexParameteri(m_glType, GL_TEXTURE_COMPARE_MODE, GL_NONE);
//						glTexParameteri(m_glType, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
//						if (m_samples == 1)
//							glTexImage2D(m_glType, 0, GL_DEPTH_COMPONENT32, m_size.x, m_size.y,
//								0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
//						else
//							glTexImage2DMultisample(m_glType,
//								m_samples, GL_DEPTH_COMPONENT32, m_size.x, m_size.y, GL_FALSE);
//						glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
//							GL_DEPTH_ATTACHMENT, m_glType, m_depthId, 0);
//						glBindTexture(m_glType, m_id);
//					}
//
//					if (m_samples == 1)
//						glTexImage2D(m_glType, 0, m_internalFormat, m_size.x, m_size.y,
//							0, m_format, m_dataFormat, NULL);
//					else
//						glTexImage2DMultisample(m_glType,
//							m_samples, m_internalFormat, m_size.x, m_size.y, GL_FALSE);
//
//					if (isMipMapped())
//						glGenerateMipmapEXT(m_glType);
//
//					glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
//						GL_COLOR_ATTACHMENT0_EXT, m_glType, m_id, 0);
//				}
//				else if (m_type == ETextureCubeMap) {
//					Assert(m_size.x == m_size.y && math::isPowerOfTwo(m_size.x));
//					Assert(m_fbType == EColorBuffer);
//					Assert(m_samples == 1);
//
//					for (int i = 0; i<6; i++)
//						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, m_internalFormat,
//							m_size.x, m_size.y, 0, m_format, m_dataFormat, NULL);
//
//					if (isMipMapped())
//						glGenerateMipmapEXT(m_glType);
//
//					if (depthAsTexture) {
//						/* Generate an identifier */
//						glGenTextures(1, &m_depthId);
//						glBindTexture(m_glType, m_depthId);
//						glTexParameteri(m_glType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//						glTexParameteri(m_glType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//						for (int i = 0; i<6; i++)
//							glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT32,
//								m_size.x, m_size.y, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
//
//						if (GLEW_EXT_geometry_shader4)
//							activateSide(-1);
//						else
//							activateSide(0);
//					}
//					else {
//						glGenRenderbuffersEXT(1, &m_depthId);
//						glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_depthId);
//						glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT,
//							GL_DEPTH_COMPONENT32, m_size.x, m_size.y);
//						glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,
//							GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_depthId);
//						activateSide(0);
//					}
//				}
//				else {
//					Log(EError, "Unsupported texture type!");
//				}
//			}
//							   break;
//			case EDepthBuffer:
//				Assert(m_samples == 1);
//				if (m_depthMode == ECompare) {
//					glTexParameteri(m_glType, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
//					glTexParameteri(m_glType, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
//				}
//
//				if (m_type == ETexture2D) {
//					/* Allocate the texture memory */
//					glTexImage2D(m_glType, 0, m_internalFormat,
//						m_size.x, m_size.y, 0, GL_DEPTH_COMPONENT,
//						m_dataFormat, NULL);
//
//					/* Attach the texture as a depth target */
//					glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
//						GL_DEPTH_ATTACHMENT_EXT, m_glType, m_id, 0);
//				}
//				else if (m_type == ETextureCubeMap) {
//					Assert(m_size.x == m_size.y && math::isPowerOfTwo(m_size.x));
//					for (int i = 0; i<6; i++)
//						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, m_internalFormat,
//							m_size.x, m_size.y, 0, m_format, m_dataFormat, NULL);
//
//					if (GLEW_EXT_geometry_shader4)
//						activateSide(-1);
//					else
//						activateSide(0);
//				}
//				else {
//					Log(EError, "Unsupported texture type!");
//				}
//
//				glDrawBuffer(GL_NONE);
//				glReadBuffer(GL_NONE);
//				break;
//			default:
//				Log(EError, "Invalid render buffer type!");
//			}
//
//			GLenum errorStatusID = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
//			std::string errorStatus;
//			switch (errorStatusID) {
//			case GL_FRAMEBUFFER_COMPLETE_EXT: break;
//			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
//				errorStatus = "Incomplete attachment"; break;
//			case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
//				errorStatus = "Unsupported framebuffer format"; break;
//			case GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT:
//				errorStatus = "Incomplete framebuffer - duplicate attachment"; break;
//			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
//				errorStatus = "Incomplete framebuffer - missing attachment"; break;
//			case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
//				errorStatus = "Incomplete framebuffer - invalid dimensions"; break;
//			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
//				errorStatus = "Incomplete framebuffer - no draw buffer"; break;
//			case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
//				errorStatus = "Incomplete framebuffer - invalid formats"; break;
//			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
//				errorStatus = "Incomplete framebuffer - no readbuffer"; break;
//			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT:
//				errorStatus = "Incomplete multisample framebuffer"; break;
//			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
//				errorStatus = "Incomplete layer targets"; break;
//			default:
//				errorStatus = "Unknown error status"; break;
//			}
//			if (!errorStatus.empty())
//				Log(EError, "FBO Error 0x%x: %s!\nFramebuffer configuration: %s",
//					errorStatusID, errorStatus.c_str(), toString().c_str());
//
//			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, GL_NONE);
//		}
//
//		glBindTexture(m_glType, GL_NONE);
//		// Set up the rendering context, load shaders and other resources, etc.:
//		QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
//		f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		...
//	}
//
//	void resizeGL(int w, int h) override
//	{
//		// Update projection matrix and other size related settings:
//		m_projection.setToIdentity();
//		m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
//		...
//	}
//
//	void paintGL() override
//	{
//		glBindTexture(m_glType, m_id);
//
//		Bitmap *bitmap = getBitmap();
//
//		uint8_t *ptr = bitmap->getUInt8Data() +
//			bitmap->getBytesPerPixel() * (offset.x + offset.y * bitmap->getWidth());
//
//		glPixelStorei(GL_UNPACK_ROW_LENGTH, bitmap->getWidth());
//		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//		glTexSubImage2D(m_glType, 0, offset.x, offset.y, size.x, size.y,
//			m_format, m_dataFormat, ptr);
//		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
//
//		//// Draw the scene:
//		//QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
//		//f->glClear(GL_COLOR_BUFFER_BIT);
//		//...
//	}
//
//protected:
//	GLuint myId;
//
//};
