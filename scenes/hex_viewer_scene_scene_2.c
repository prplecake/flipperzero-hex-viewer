#include "../hex_viewer.h"
#include "../helpers/hex_viewer_custom_event.h"
#include "../helpers/hex_viewer_haptic.h"
#include "../helpers/hex_viewer_led.h"
#include "../views/hex_viewer_scene_2.h"

void hex_viewer_scene_2_callback(HexViewerCustomEvent event, void* context) {
    furi_assert(context);
    HexViewer* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, event);
}

void hex_viewer_scene_scene_2_on_enter(void* context) {
    furi_assert(context);
    HexViewer* app = context;
    hex_viewer_scene_2_set_callback(app->hex_viewer_scene_2, hex_viewer_scene_2_callback, app);
    view_dispatcher_switch_to_view(app->view_dispatcher, HexViewerViewIdScene2);
}

bool hex_viewer_scene_scene_2_on_event(void* context, SceneManagerEvent event) {
    HexViewer* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        switch(event.event) {
            case HexViewerCustomEventScene2Left:
            case HexViewerCustomEventScene2Right:
                break;
            case HexViewerCustomEventScene2Up:
            case HexViewerCustomEventScene2Down:
                break;
            case HexViewerCustomEventScene2Back:
                notification_message(app->notification, &sequence_reset_red);
                notification_message(app->notification, &sequence_reset_green);
                notification_message(app->notification, &sequence_reset_blue);
                if(!scene_manager_search_and_switch_to_previous_scene(
                    app->scene_manager, HexViewerSceneMenu)) {
                        scene_manager_stop(app->scene_manager);
                        view_dispatcher_stop(app->view_dispatcher);
                    }
                consumed = true;
                break;
        }
    }

    return consumed;
}

void hex_viewer_scene_scene_2_on_exit(void* context) {
    HexViewer* app = context;
    UNUSED(app);
}

