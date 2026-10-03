#include "glib.h"

#include "ScreenCaptureError.h"


GQuark pengui_screencapture_error_quark()
{
    return g_quark_from_static_string("pengui-screencapture-error-quark");
}
