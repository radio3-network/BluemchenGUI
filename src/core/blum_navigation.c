#include <Arduino.h>
#include <lvgl.h>
#include "blum_global.h"
#include "../utils/utils.h"

/*

    This file provides support for navigation trees.

    When the user clicks on the menus, this is the
    functionality that permits to "go back" between
    screens.

    It depends at an HashMap that includes all
    active screens, using the screen title as key.

    The HashMap is updated every time a new window
    is created at blum_widgets createWindow()
    

    // bring the screen forward
    lv_obj_move_foreground(settingsWindow);


    // update the icons
    static void statusBarBackButton(){
        lv_label_set_text(labelSettingsButton, LV_SYMBOL_LEFT);
    }

    static void statusBarSettingsButton(){
        lv_label_set_text(labelSettingsButton, LV_SYMBOL_SETTINGS);
    }

    // update the title
    statusBarTextUpdate(title);

static void statusBarTextUpdate(const char* text){
    lv_label_set_text(statusTextLabel, text );
}


*/





static int navGetNextFreeIndex(){
    return StringArray_size(indexData);
}

static void navDelete(int indexNumber){
    StringArray_delete(indexData, indexNumber);
}

/**
 * The beginning. Starts with the home window
*/
static void navClean(){
    
    if(indexData != NULL){
        StringArray_destroy(indexData);
    }
    // create a new index
    indexData = StringArray_create(max_navigation_count);
    // reset the icon for settings
    lv_label_set_text(labelSettingsButton, LV_SYMBOL_SETTINGS);
}

static void navNew(const char *title){
    // add it to memory
    StringArray_add(indexData, title);

    int i = StringArray_size(indexData) - 1;
    const char * key = StringArray_get(indexData, i);
    
    // change the title on the status bar
    lv_label_set_text(statusTextLabel, title);
    // add the appropriate icon
    if(i == 0){
        lv_label_set_text(labelSettingsButton, LV_SYMBOL_SETTINGS);
    }else{
        lv_label_set_text(labelSettingsButton, LV_SYMBOL_LEFT);
    }
    
}

static void navGoBack(){

    int i = StringArray_size(indexData) - 2;
    const char * key = StringArray_get(indexData, i);


    // using the window name, get the window object
    lv_obj_t * win = (lv_obj_t*) HashMapGet(mapWindows, key);
    // bring this window object to the foreground
    lv_obj_move_foreground(win);
    // update the label
    lv_label_set_text(statusTextLabel, key);

    // delete the current index memory
    navDelete(i+1);
    
}

