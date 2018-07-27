#include <sway/glx11/canvas.h>
#include <boost/format.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

static s32_t fbAttributes[] = {
	GLX_RENDER_TYPE, GLX_RGBA_BIT,
	GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
	GLX_RED_SIZE, 1,
	GLX_GREEN_SIZE, 1,
	GLX_BLUE_SIZE, 1,
	GLX_ALPHA_SIZE, 0,
	GLX_DEPTH_SIZE, 0,
	GLX_STENCIL_SIZE, 0,
	GLX_CONFIG_CAVEAT, GLX_NONE,
	GLX_DOUBLEBUFFER, true,
	0
};

Canvas::Canvas(boost::shared_ptr<XScreenConnection> connection, const WindowInitialParams & params) : XWindow(connection) {
	s32_t numConfigs;
	GLXFBConfig * configs, config;
	configs = glXChooseFBConfig(connection->getDisplay(), connection->getScreenNumber(), fbAttributes, &numConfigs);
	if (configs && (numConfigs > 0)) {
		config = _chooseBestSuitable(connection, configs, numConfigs);
		XFree(configs);
	}
	
	createDummy(glXGetVisualFromFBConfig(connection->getDisplay(), config), params);
	setSizeHints(params.sizes, params.resizable);
	setTitle(boost::str(boost::format("Sway // %1%") % params.title).c_str());
	setPosition(
		params.fullscreen ? 0 : (connection->getDisplaySize().getW() - params.sizes[core::detail::toUnderlying(WindowSize_t::kOrigin)].getW()) / 2,
		params.fullscreen ? 0 : (connection->getDisplaySize().getH() - params.sizes[core::detail::toUnderlying(WindowSize_t::kOrigin)].getH()) / 2);

	_context = boost::make_shared<GlxContext>(connection, (XWindow *) this);
	_context->createLegacy(config);
}

Canvas::~Canvas() {
	// Empty
}

void Canvas::handleCreateNotifyEvent(const XEvent & event) {
	// Empty
}

void Canvas::handleConfigureNotifyEvent(const XEvent & event) {
	// Empty
}

void Canvas::handleExposeEvent(const XEvent & event) {
	// Empty
}

void Canvas::handleFocusInEvent(const XEvent & event) {
	// Empty
}

void Canvas::handleFocusOutEvent(const XEvent & event) {
	// Empty
}

boost::shared_ptr<GlxContext> Canvas::getContext() {
	return _context;
}

GLXFBConfig Canvas::_chooseBestSuitable(boost::shared_ptr<XScreenConnection> connection, GLXFBConfig * configs, s32_t numConfigs) {
	s32_t bestScore = DONT_CARE, bestNumSamples = DONT_CARE;
	
	for (s32_t i = 0; i < numConfigs; ++i) {
		GlxVisualAttributes attrs = _getMultisampleAttributes(connection, configs[i]);
		if (bestScore < 0 || (attrs.numMultisample && (attrs.numSamples > bestNumSamples)))
	 		bestScore = i, bestNumSamples = attrs.numSamples;
	}

	return configs[bestScore];
}

GlxVisualAttributes Canvas::_getMultisampleAttributes(boost::shared_ptr<XScreenConnection> connection, GLXFBConfig config) {
	lpcstr_t extensions = glXQueryExtensionsString(connection->getDisplay(), connection->getScreenNumber());
	GlxVisualAttributes attrs;

	if (extensions && strstr(extensions, "GLX_ARB_multisample")) {
		glXGetFBConfigAttrib(connection->getDisplay(), config, GLX_SAMPLE_BUFFERS_ARB, &attrs.numMultisample);
		glXGetFBConfigAttrib(connection->getDisplay(), config, GLX_SAMPLES_ARB, &attrs.numSamples);
	}
	else {
		attrs.numMultisample = 0;
		attrs.numSamples = 0;
	}

	return attrs;
}

NAMESPACE_END(glx11)
NAMESPACE_END(sway)
